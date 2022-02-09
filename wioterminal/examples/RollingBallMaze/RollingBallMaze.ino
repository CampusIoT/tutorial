/* Wio Terminal Sprite Routines - see http://www.technoblogy.com/show?39DR

   David Johnson-Davies - www.technoblogy.com - 17th August 2020
   For Wio Terminal TFT display
   
   CC BY 4.0
   Licensed under a Creative Commons Attribution 4.0 International license: 
   http://creativecommons.org/licenses/by/4.0/
*/

#include <Adafruit_GFX.h>    // Core graphics library
#include <TFT_eSPI.h>        // Hardware-specific library for Wio Terminal
#include <SPI.h>
#include <Wire.h>

// Seeed Studio Wio Terminal
#define TFT_CS        69  // Chip select
#define TFT_RST       71  // Display reset
#define TFT_DC        66  // Display data/command select
#define TFT_BACKLIGHT 72  // Display backlight pin
#define TFT_MOSI      62  // Data out
#define TFT_SCLK      63  // Clock out

class Technoblogy_TFT : public TFT_eSPI {      
public:
  Technoblogy_TFT();
  uint16_t getPixel(uint16_t x, uint16_t y);
  void xorPixel(uint16_t x, uint16_t y, uint16_t color);
  void xorSprite(uint16_t x, uint16_t y, uint64_t sprite, uint16_t color);
  bool hitSprite(uint16_t x, uint16_t y, uint64_t sprite, uint16_t color);
  void moveSprite(uint16_t x, uint16_t y, uint64_t sprite, int dx, int dy, uint16_t color);
};

Technoblogy_TFT::Technoblogy_TFT()
    : TFT_eSPI() {}

Technoblogy_TFT tft = Technoblogy_TFT();

// Return the colour of the pixel at x, y
uint16_t Technoblogy_TFT::getPixel (uint16_t x, uint16_t y) {
  return readPixel(x,y);
}

// Plot a pixel at x, y by exclusive-ORing the colour with the display
void Technoblogy_TFT::xorPixel (uint16_t x, uint16_t y, uint16_t color) {
  uint16_t lastcolor = readPixel(x,y);
  drawPixel(x, y, color ^ lastcolor);
}

// Plot an 8x8 sprite at x, y by exclusive-ORing the colour with the display
void Technoblogy_TFT::xorSprite (uint16_t x0, uint16_t y0, uint64_t sprite, uint16_t color) {
  bool bit;
  if ((x0 >= 0) && (x0+7 < width()) && (y0 >= 0) && (y0+7 < height())) {
    for (int y=0; y<8; y++) {
      for (int x=0; x<8; x++) {
        bit = sprite>>(63 - x - y*8) & 1;
        if (bit) xorPixel(x0+x, y0+y, color);
      }
    }
  }
}

// Collision detection between an 8x8 sprite at x, y with a specified colour
bool Technoblogy_TFT::hitSprite (uint16_t x0, uint16_t y0, uint64_t sprite, uint16_t color) {
  uint16_t row[8];
  uint32_t col16;
  bool bit;
  if ((x0 >= 0) && (x0+7 < width()) && (y0 >= 0) && (y0+7 < height())) {
    for (int y=0; y<8; y++) {
      for (int x=0; x<8; x++) {
        col16 = readPixel(x0+x,y0+y);
        bit = sprite>>(63 - x - y*8) & 1;
        if (bit && (col16 == color)) {
          return true;
        }
      } 
    }
  }
  return false;
}

// Move a sprite from x, y by one pixel in any direction by exclusive-ORing only the changed pixels with the display
void Technoblogy_TFT::moveSprite(uint16_t x0, uint16_t y0, uint64_t sprite, int dx, int dy, uint16_t color) {
  int oldbit, newbit;
  if ((x0 >= 0) && (x0+7 < width()) && (y0 >= 0) && (y0+7 < height())) {
    dx = (dx > 0) - (dx < 0); dy = (dy > 0) - (dy < 0); 
    for (int y=0; y<10; y++) {
      for (int x=0; x<10; x++) {
        // Sprite's previous position
        int xs = x - 1, ys = y - 1;
        if (xs >= 0 && xs <= 7 && ys >=0 && ys <= 7) {
          oldbit = sprite>>(63 - ys*8 - xs) & 1;
        } else oldbit = 0;
        // Sprite's new position
        int xn = x - 1 - dx, yn = y - 1 - dy;
        if (xn >= 0 && xn <= 7 && yn >=0 && yn <= 7) {
          newbit = sprite>>(63 - yn*8 - xn) & 1;
        } else newbit = 0;
        if (oldbit != newbit) xorPixel(x0-1+x, y0-1+y, color);
      }
    }
  }
}

// Simple rolling ball maze using the Wio Terminal accelerometer **********************************************

// Accelerometer (LIS3DH)

const int LIS3DH = 0x18;

// Set sample rate; n = 2 is 10Hz
void lis3dhRate (int n) {
  Wire1.beginTransmission(LIS3DH);
  Wire1.write(0x20);
  Wire1.write(n<<4 | 7);
  Wire1.endTransmission(true);
}

// Read register; r = 0 is X, 1 is Y, 2 is Z
int lis3dhXYZ (int r) {
  Wire1.beginTransmission(LIS3DH);
  Wire1.write(0x28 + 2*r + 0x80);
  Wire1.endTransmission(false);
  Wire1.requestFrom(LIS3DH, 4);
  uint8_t lo = Wire1.read();
  uint8_t hi = Wire1.read();
  int d = lo | hi<<8;
  return d - ((d & 0x8000)<<1);
}

// The maze

const int Button1 = 30;    // Leftmost button above display
const int Speaker = 12;
const int Sens = 1024;     // Accelerometer sensitivity

const uint16_t goalCol = TFT_YELLOW;
const uint16_t mazeCol = 0xF80F;      // Red + some blue
const uint16_t ballCol = TFT_WHITE;
const uint16_t boardCol = TFT_BLACK;

const uint64_t Sprite = 0b\
00111100\
01111110\
11111111\
11111111\
11111111\
11111111\
01111110\
00111100;

const uint64_t Star = 0b\
00011000\
01011010\
00111100\
11111111\
11111111\
00111100\
01011010\
00011000;

const int tftWidth=320, tftHeight=240;
const int mx = 5, my = 7;             
const int mWidth = 22, mHeight = 16;
const int cellSize=12, gap=14;

// Directions N  E  W  S
int dx[4] = { 0, 1,-1, 0 };
int dy[4] = {-1, 0, 0, 1 };

int opposite (int dir) { return 3 - dir; }

int maxDepth, gx, gy;  // For defining the goal

void initMaze() {
  tft.fillScreen(TFT_BLACK);
  tft.fillRect(mx, my, gap*mWidth+2, gap*mHeight+2, mazeCol);
  tft.fillRect(mx+2, my+2, cellSize, cellSize, boardCol);
}

void drawMaze (int ax, int ay, int depth) {
  if (depth > maxDepth) { gx = ax; gy = ay; maxDepth = depth; }
  int r = random(4);
  for (int d=0; d<4; d++) {
    int dir = (d+r) % 4;
    int bx = ax + dx[dir], by = ay + dy[dir];
    int x = mx+bx*gap+2, y = my+by*gap+2;
    if (bx>=0 && bx<mWidth && by>=0 && by<mHeight && tft.getPixel(x,y)==mazeCol) {
      tft.fillRect(x, y, cellSize, cellSize, boardCol);
      x = mx+(ax+bx)*gap/2+2, y = my+(ay+by)*gap/2+2;
      tft.fillRect(x, y, cellSize, cellSize, boardCol);
      drawMaze(bx, by, depth++);
    }
  }
}

void setup() {
  tft.init();
  tft.setRotation(3);
  Wire1.begin();
  lis3dhRate(2);
  pinMode(Button1, INPUT_PULLUP);
}

void loop() {
  // New maze
  maxDepth = 0;
  initMaze();
  drawMaze(0,0,0);
  tft.xorSprite(mx+gx*gap+4, my+gy*gap+4, Star, goalCol);
  int x = mx+4, y = my+4, dx, dy, won = false;
  tft.xorSprite(x, y, Sprite, ballCol);
  while (digitalRead(Button1)) {
    // Move ball?
    int sx = -lis3dhXYZ(1) / Sens;
    int sy = lis3dhXYZ(0) / Sens;
    // Set dx and dy to -1, 0, or +1
    dx = (sx > 0) - (sx < 0);
    dy = (sy > 0) - (sy < 0);
    if (tft.hitSprite(x+dx, y, Sprite, mazeCol)) dx = 0;
    if (tft.hitSprite(x, y+dy, Sprite, mazeCol)) dy = 0;
    if (tft.hitSprite(x, y, Sprite, goalCol^ballCol) & !won) {
      for (int n=0; n<3; n++) { tone(Speaker, 880, 100); delay(200); }
      noTone(Speaker);
      won = true;
    }
    tft.moveSprite(x, y, Sprite, dx, dy, ballCol);
    x = x + dx; y = y + dy;
    delay(10);
  }
}
