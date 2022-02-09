/*
   Air Quality Terminal 
   Author: Salman Faris
   Date: 01/09/2020
   Last Updates: 06/09/2020
*/


#include <TFT_eSPI.h>
#include <Multichannel_Gas_GMXXX.h>
#include <Wire.h>
#include "DHT.h"

GAS_GMXXX<TwoWire> gas;

TFT_eSPI tft;
TFT_eSprite spr = TFT_eSprite(&tft);  //sprite

unsigned int no2, c2h5ch, voc, co;


#define DHTPIN 0
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);




void setup() {
  Serial.begin(115200);
  tft.begin();
  tft.setRotation(3);

  gas.begin(Wire, 0x08);

  dht.begin();


  //Head
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(&FreeSansBoldOblique18pt7b);
  tft.setTextColor(TFT_WHITE);
  tft.drawString("Air Quality", 70, 10 , 1);

  //Line
  for (int8_t line_index = 0; line_index < 5 ; line_index++)
  {
    tft.drawLine(0, 50 + line_index, tft.width(), 50 + line_index, TFT_GREEN);
  }


  //VCO & CO Rect
  tft.drawRoundRect(5, 60, (tft.width() / 2) - 20 , tft.height() - 65 , 10, TFT_WHITE); // L1

  //VCO Text
  tft.setFreeFont(&FreeSansBoldOblique12pt7b);
  tft.setTextColor(TFT_RED);
  tft.drawString("VOC", 7 , 65 , 1);
  tft.setTextColor(TFT_GREEN);
  tft.drawString("ppm", 55, 108, 1);

  //CO Text
  tft.setFreeFont(&FreeSansBoldOblique12pt7b);
  tft.setTextColor(TFT_RED);
  tft.drawString("CO", 7 , 150 , 1);
  tft.setTextColor(TFT_GREEN);
  tft.drawString("ppm", 55, 193, 1);


  // Temp rect
  tft.drawRoundRect((tft.width() / 2) - 10  , 60, (tft.width() / 2) / 2 , (tft.height() - 65) / 2 , 10, TFT_BLUE); // s1

  tft.setFreeFont(&FreeSansBoldOblique9pt7b);
  tft.setTextColor(TFT_RED) ;
  tft.drawString("Temp", (tft.width() / 2) - 1  , 70 , 1); // Print the test text in the custom font
  tft.setTextColor(TFT_GREEN);
  tft.drawString("o", (tft.width() / 2) + 30, 95, 1);
  tft.drawString("C", (tft.width() / 2) + 40, 100, 1);


  //No2 rect
  tft.drawRoundRect(((tft.width() / 2) + (tft.width() / 2) / 2) - 5  , 60, (tft.width() / 2) / 2 , (tft.height() - 65) / 2 , 10, TFT_BLUE); // s2

  tft.setFreeFont(&FreeSansBoldOblique9pt7b);
  tft.setTextColor(TFT_RED);
  tft.drawString("NO2", ((tft.width() / 2) + (tft.width() / 2) / 2)   , 70 , 1); // Print the test text in the custom font
  tft.setTextColor(TFT_GREEN);
  tft.drawString("ppm", ((tft.width() / 2) + (tft.width() / 2) / 2) + 30 , 120, 1);

  //Humi Rect
  tft.drawRoundRect((tft.width() / 2) - 10 , (tft.height() / 2) + 30, (tft.width() / 2) / 2 , (tft.height() - 65) / 2 , 10, TFT_BLUE); // s3

  tft.setFreeFont(&FreeSansBoldOblique9pt7b);
  tft.setTextColor(TFT_RED) ;
  tft.drawString("Humi", (tft.width() / 2) - 1 , (tft.height() / 2) + 40 , 1); // Print the test text in the custom font
  tft.setTextColor(TFT_GREEN);
  tft.drawString("%", (tft.width() / 2) + 30, (tft.height() / 2) + 70, 1);



  //c2h5ch Rect
  tft.drawRoundRect(((tft.width() / 2) + (tft.width() / 2) / 2) - 5  , (tft.height() / 2) + 30, (tft.width() / 2) / 2 , (tft.height() - 65) / 2 , 10, TFT_BLUE); // s4


  tft.setFreeFont(&FreeSansBoldOblique9pt7b);
  tft.setTextColor(TFT_RED) ;
  tft.drawString("Ethyl", ((tft.width() / 2) + (tft.width() / 2) / 2)   , (tft.height() / 2) + 40 , 1); // Print the test text in the custom font
  tft.setTextColor(TFT_GREEN);
  tft.drawString("ppm", ((tft.width() / 2) + (tft.width() / 2) / 2) + 30 , (tft.height() / 2) + 90, 1);


}

void loop() {

  // VOC

  voc = gas.getGM502B();
  if (voc > 999) voc = 999;
  Serial.print("VOC: ");
  Serial.print(voc);
  Serial.println(" ppm");

  spr.createSprite(40, 30);
  spr.fillSprite(TFT_BLACK);
  spr.setFreeFont(&FreeSansBoldOblique12pt7b);
  spr.setTextColor(TFT_WHITE);
  spr.drawNumber(voc, 0, 0, 1);
  spr.pushSprite(15, 100);
  spr.deleteSprite();

  //CO

  co = gas.getGM702B();
  if (co > 999) co = 999;
  Serial.print("CO: ");
  Serial.print(co);
  Serial.println(" ppm");

  spr.createSprite(40, 30);
  spr.setFreeFont(&FreeSansBoldOblique12pt7b);
  spr.setTextColor(TFT_WHITE);
  spr.drawNumber(co, 0, 0, 1);
  spr.setTextColor(TFT_GREEN);
  spr.pushSprite(15, 185);
  spr.deleteSprite();

  //Temp

  float t = dht.readTemperature();
  //int tem = round(t);
  int tem = t;
  Serial.print("Temperature: ");
  Serial.print(tem);
  Serial.println( "*C");

  spr.createSprite(30, 30);
  spr.setFreeFont(&FreeSansBoldOblique12pt7b);
  spr.setTextColor(TFT_WHITE);
  spr.drawNumber(t, 0, 0, 1);
  spr.setTextColor(TFT_GREEN);
  spr.pushSprite((tft.width() / 2) - 1, 100);
  spr.deleteSprite();

  //NO2
  no2 = gas.getGM102B();
  if (no2 > 999) no2 = 999;
  Serial.print("NO2: ");
  Serial.print(no2);
  Serial.println(" ppm");

  spr.createSprite(45, 30);
  spr.setFreeFont(&FreeSansBoldOblique12pt7b);
  spr.setTextColor(TFT_WHITE);
  spr.drawNumber(no2, 0, 0, 1);
  spr.pushSprite(((tft.width() / 2) + (tft.width() / 2) / 2), 97);
  spr.deleteSprite();


  //Humidity
  float h = dht.readHumidity();
  if (h > 99) h = 99;
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println( "%");

  spr.createSprite(30, 30);
  spr.setFreeFont(&FreeSansBoldOblique12pt7b);
  spr.setTextColor(TFT_WHITE);
  spr.drawNumber(h, 0, 0, 1);
  spr.pushSprite((tft.width() / 2) - 1, (tft.height() / 2) + 67);
  spr.deleteSprite();

  //C2H5CH
  c2h5ch = gas.getGM302B();
  if (c2h5ch > 999) c2h5ch = 999;
  Serial.print("C2H5CH: ");
  Serial.print(c2h5ch);
  Serial.println(" ppm");

  spr.createSprite(45, 30);
  spr.setFreeFont(&FreeSansBoldOblique12pt7b);
  spr.setTextColor(TFT_WHITE);
  spr.drawNumber(c2h5ch, 0 , 0, 1);
  spr.pushSprite(((tft.width() / 2) + (tft.width() / 2) / 2), (tft.height() / 2) + 67);
  spr.deleteSprite();


  delay(2000);
}
