// From https://www.hackster.io/luigi-morelli/lyapunov-fractals-with-seeeduino-wio-terminal-3126b3
#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library
TFT_eSprite spr = TFT_eSprite(&tft); //Instance of a Sprite

// Global variables
const int ClientWidth  = 320;
const int ClientHeight = 240;

int   n,a,b,cicli;

unsigned long PalColori[256];
unsigned long color;

float totale,x,r,lyap;
float a1,b1;
float dx,dy;
float xd,yd;
float Attrattore;
float MinX;
float MaxX;
float temp;
float e;

bool  pari;

void setup() {    
  tft.init();
  tft.setRotation(3);
  pinMode(WIO_5S_PRESS, INPUT_PULLUP);

  // Parameters initialization 
  cicli      = 3;
  Attrattore = 0.5;
  MinX       = -3.4028235E+38;              // Underflow FPU
  MaxX       = sqrt(3.4028235E+38) / 8;     // Overflow  FPU
  e          = exp(1.0);

  // Coordinates
  xd = 1.99;
  yd = 1.09;
  dx = 1.0/120;    // Num. Horz. pixels
  dy = 1.0/80;    // Num. vert. pixels  
}

void loop() {
  // Presentation
  start_screen();
  // Graph
  calc();
}

// Set color palette
void set_Palette() {
  // A palette of 128 shades is defined
  for (n = 0; n < 128; n++) 
    PalColori[n] = n*16;
}

void calc() {
  // Start timer
  // Set the graphic palette
  set_Palette();

  // Start algorithm
  // Inizio algoritmo
  pari  = true;
  b1 = yd;
  for (a = 0; a < ClientHeight; a++) {
    b1 = (b1 + dy);
    a1 = xd;
    for (b = 0; b < ClientWidth; b++) {
      a1 = (a1 + dx);
      totale = 0;
      x = Attrattore;

      // Generation of the matrix of interpolation
      for (n = 1; n <= cicli; n++) {
        if (pari) {
          r = a1;
          pari = false;
        }
        else
        {
          r = b1;
          pari = true;
        }

        // Calcolo x
        if ((x > MinX) && (x < MaxX)) 
            x =  r*x*(1-x);
        else if (x < MinX) 
                 x = abs(x);
             else
                 x = MaxX * MaxX;

        temp = abs (r-2*r*x);
        if (temp != 0)
          totale = totale + log(temp);
      }

      lyap = totale / cicli;
      if (lyap >= 0) 
        color = 0;
      else 
        color = 127 - (floor (abs (lyap*127)));

      // Draw a pixel
      if (color < 127)
      { 
        tft.drawPixel(b, a, PalColori[color]);
      }
      else 
        tft.drawPixel(b, a, PalColori[0]);
    }
  }  

  // Stop timer
  while (!keypressed());
}

void start_screen() {
  tft.fillScreen(TFT_GREEN);
    
  tft.setTextColor(TFT_BLACK); 
  tft.setTextSize(2);                   
  tft.drawString("Wio Lyapunov", 80, 40); 
  tft.setTextSize(1);
  tft.drawString("This code calculates the fractal set of Lyapunov", 5, 70);
  tft.drawString("Mario Markus and Benno Hess,University of Dortmund", 5, 90);  
  tft.drawString("were stydying the demolition method of carbohydrates", 5, 100);
  tft.drawString("by enzymes during digestive processes.", 5, 110);
  
  tft.drawString("Such method apply a well known formula due to", 5, 130);
  tft.drawString("the Russian mathematician Aleksandr M. Lyapunov", 5, 140); 
  tft.drawString("related to the \"index of chaos\" on a", 5, 150);
  tft.drawString("dynamic system.", 5, 160);

  tft.drawString("Press the paddle to continue...", 20, 220);

  while(!keypressed());

  tft.fillScreen(TFT_BLACK);
}

bool keypressed() {
  do {      
    delay(100);
  } while(digitalRead(WIO_5S_PRESS) != LOW);
  return true;  
}
