/* ESP8266/32 Audio Spectrum Analyser on an SSD1306/SH1106 Display
 * The MIT License (MIT) Copyright (c) 2017 by David Bird. 
 * The formulation and display of an AUdio Spectrum using an ESp8266 or ESP32 and SSD1306 or SH1106 OLED Display using a Fast Fourier Transform
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files 
 * (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, but not to use it commercially for profit making or to sub-license and/or to sell copies of the Software or to 
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:  
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software. 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE 
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
 * See more at http://dsbird.org.uk 
*/
// Wio Audio Spectrum Display : 2020.05.28 macsbug
// https://macsbug.wordpress.com/2020/05/28/wio-audio-spectrum-display/
// GAIN ADJUST : GAIN UP = KEY_C(LEFT) , 5S_UP
// GAIN ADJUST : GAIN DOWN = KEY_B(RIGHT) , 5S_DOWN
// Audio Spectrum Display : 2017.12.31 macsbug
// https://macsbug.wordpress.com/2017/12/31/audio-spectrum-display-with-m5stack/
// https://github.com/tobozo/ESP32-8-Octave-Audio-Spectrum-Display/tree/wrover-kit
// https://github.com/G6EJD/ESP32-8266-Audio-Spectrum-Display
// https://github.com/kosme/arduinoFFT
// https://macsbug.wordpress.com/2017/12/31/audio-spectrum-display-with-m5stack/

#include "arduinoFFT.h"
arduinoFFT FFT = arduinoFFT();
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
#define SAMPLES 512  // Must be a power of 2
#define SAMPLING_FREQUENCY 40000 
// Hz, must be 40000 or less due to ADC conversion time.
// Determines maximum frequency that can be analysed by the FFT Fmax=sampleF/2.

struct eqBand {
  const char *freqname;
  uint16_t amplitude;
  int peak;
  int lastpeak;
  uint16_t lastval;
  unsigned long lastmeasured;
};

eqBand audiospectrum[8] = {
  //Adjust the amplitude values to fit your microphone
/*
  { "125Hz", 1000, 2,   0, 0, 0},
  { "250Hz", 500,  2,   0, 0, 0},
  { "500Hz", 300,  3,   0, 0, 0},
  { "1KHz",  250,  7,   0, 0, 0},
  { "2KHz",  200,  14,  0, 0, 0},
  { "4KHz",  100,  24,  0, 0, 0},
  { "8KHz",  50,   48,  0, 0, 0},
  { "16KHz", 25,   155, 0, 0, 0}
*/
  { "125Hz", 500, 0, 0, 0, 0},
  { "250Hz", 200, 0, 0, 0, 0},
  { "500Hz", 200, 0, 0, 0, 0},
  { "1KHz",  200, 0, 0, 0, 0},
  { "2KHz",  200, 0, 0, 0, 0},
  { "4KHz",  100, 0, 0, 0, 0},
  { "8KHz",  100, 0, 0, 0, 0},
  { "16KHz",  50, 0, 0, 0, 0}
};

unsigned int sampling_period_us;
unsigned long microseconds;
double vReal[SAMPLES];
double vImag[SAMPLES];
unsigned long newTime, oldTime;
uint16_t tft_width  = 320;
uint16_t tft_height = 240;
uint8_t bands = 8;
uint8_t bands_width = floor( tft_width / bands );
uint8_t bands_pad = bands_width - 10;
uint16_t colormap[255]; // color palette for the band meter (pre-fill in setup)
int gain = 32;

void setup() {
  tft.begin();
  tft.setRotation(3); 
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.setTextSize(1);
  pinMode(WIO_KEY_C,   INPUT_PULLUP);// LEFT
  pinMode(WIO_KEY_A,   INPUT_PULLUP);// CENTER
  pinMode(WIO_KEY_B,   INPUT_PULLUP);// RIGHT
  pinMode(WIO_5S_UP,   INPUT_PULLUP);
  pinMode(WIO_5S_DOWN, INPUT_PULLUP);
  pinMode(WIO_5S_LEFT, INPUT_PULLUP);
  pinMode(WIO_5S_RIGHT,INPUT_PULLUP);
  pinMode(WIO_5S_PRESS,INPUT_PULLUP);
  pinMode(WIO_MIC,     INPUT);
  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
  delay(2000);
  for(uint8_t i=0;i<tft_height;i++) {
    colormap[i] = tft.color565(tft_height-i*.5, i*1.1, 0);
  }
  for (byte band = 0; band <= 7; band++) {
    tft.setCursor(bands_width*band + 2, 0);
    tft.print(audiospectrum[band].freqname);
  }
}

void loop() {
  String cont = waitForcont();
  if ((cont=="5UP")   || (cont=="LEFT") ){gain++;tft.setCursor(5,10);tft.println(gain);}
  if ((cont=="5DOWN") || (cont=="RIGHT")){gain--;tft.setCursor(5,10);tft.println(gain);}
  for (int i = 0; i < SAMPLES; i++) {
    newTime = micros()-oldTime;
    oldTime = newTime;
    vReal[i] = analogRead(WIO_MIC) * gain; // A conversion takes about 1uS on an ESP32
    vImag[i] = 0;
    while (micros() < (newTime + sampling_period_us)) { 
      // do nothing to wait
    }
  }
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

  for (int i = 2; i < (SAMPLES/2); i++){ 
    // Don't use sample 0 and only first SAMPLES/2 are usable. 
    // Each array eleement represents a frequency and its value the amplitude.
    if (vReal[i] > 1500) { // Add a crude noise filter, 10 x amplitude or more
      byte bandNum = getBand(i);
      if(bandNum!=8) {
        displayBand(bandNum, (int)vReal[i]/audiospectrum[bandNum].amplitude);
      }
    }
  }
  
  long vnow = millis();
  for (byte band = 0; band <= 7; band++) {
    // auto decay every 50ms on low activity bands
    if(vnow - audiospectrum[band].lastmeasured > 50) {
      displayBand(band, audiospectrum[band].lastval>4 ? audiospectrum[band].lastval-4 : 0);
    }
    if (audiospectrum[band].peak > 0) {
      audiospectrum[band].peak -= 2;
      if(audiospectrum[band].peak<=0) {
        audiospectrum[band].peak = 0;
      }
    }
    // only draw if peak changed
    if(audiospectrum[band].lastpeak != audiospectrum[band].peak) {
      // delete last peak
     tft.drawFastHLine(bands_width*band,tft_height-audiospectrum[band].lastpeak,bands_pad,TFT_BLACK);
     audiospectrum[band].lastpeak = audiospectrum[band].peak;
     tft.drawFastHLine(bands_width*band, tft_height-audiospectrum[band].peak,
                   bands_pad, colormap[tft_height-audiospectrum[band].peak]);
    }
  } 
}

void displayBand(int band, int dsize){
  uint16_t hpos = bands_width*band;
  int dmax = 200;
  if(dsize>tft_height-10) {
    dsize = tft_height-10; // leave some hspace for text
  }
  if(dsize < audiospectrum[band].lastval) {
    // lower value, delete some lines
    tft.fillRect(hpos, tft_height-audiospectrum[band].lastval,
      bands_pad, audiospectrum[band].lastval - dsize, TFT_BLACK);
  }
  if (dsize > dmax) dsize = dmax;
  for (int s = 0; s <= dsize; s=s+4){
    tft.drawFastHLine(hpos,tft_height-s,bands_pad,colormap[tft_height-s]);
  }
  if (dsize > audiospectrum[band].peak) {
    audiospectrum[band].peak = dsize;
  }
  audiospectrum[band].lastval = dsize;
  audiospectrum[band].lastmeasured = millis();
}

byte getBand(int i) {
  if (i<=2 )             return 0;  //   125Hz
  if (i >3   && i<=5 )   return 1;  //   250Hz
  if (i >5   && i<=7 )   return 2;  //   500Hz
  if (i >7   && i<=15 )  return 3;  //  1000Hz
  if (i >15  && i<=30 )  return 4;  //  2000Hz
  if (i >30  && i<=53 )  return 5;  //  4000Hz
  if (i >53  && i<=200 ) return 6;  //  8000Hz
  if (i >200           ) return 7;  // 16000Hz
  return 8;
}

String waitForcont() {
  String cont = "";
  if (digitalRead(WIO_KEY_A)   ==LOW){cont="RIGHT" ;}else 
  if (digitalRead(WIO_KEY_B)   ==LOW){cont="MIDDLE";}else
  if (digitalRead(WIO_KEY_C)   ==LOW){cont="LEFT"  ;}else 
  if (digitalRead(WIO_5S_UP)   ==LOW){cont="5UP"   ;}else 
  if (digitalRead(WIO_5S_DOWN) ==LOW){cont="5DOWN" ;}else 
  if (digitalRead(WIO_5S_LEFT) ==LOW){cont="5LEFT" ;}else 
  if (digitalRead(WIO_5S_RIGHT)==LOW){cont="5RIGHT";}else 
  if (digitalRead(WIO_5S_PRESS)==LOW){cont="5CLICK";}else 
  if (cont != ""){return cont;}
}
