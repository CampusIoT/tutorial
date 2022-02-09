#include <TFT_eSPI.h>
#include <Multichannel_Gas_GMXXX.h>
#include <Wire.h>
GAS_GMXXX<TwoWire> gas;
 
TFT_eSPI tft; 
// Stock font and GFXFF reference handle
TFT_eSprite spr = TFT_eSprite(&tft);  // Sprite 
 
void setup() {
  // put your setup code here, to run once:
  tft.begin();
  tft.setRotation(3);
  spr.createSprite(tft.width(),tft.height()); 
  gas.begin(Wire, 0x08); // use the hardware I2C
}
 
void loop() {
  // put your main code here, to run repeatedly:
  int val;
  spr.fillSprite(TFT_BLACK);
  spr.setFreeFont(&FreeSansBoldOblique18pt7b); 
  spr.setTextColor(TFT_BLUE);
  spr.drawString("Gas Terminal", 60 - 15, 10 , 1);// Print the test text in the custom font
  for(int8_t line_index = 0;line_index < 5 ; line_index++)
  {
    spr.drawLine(0, 50 + line_index, tft.width(), 50 + line_index, TFT_GREEN);
  }
 
  spr.setFreeFont(&FreeSansBoldOblique9pt7b);                 // Select the font
  // GM102B NO2 sensor
  val = gas.getGM102B();
  if (val > 999) val = 999;
  spr.setTextColor(TFT_WHITE);
  spr.drawString("NO2:", 60 - 24, 100 -24 , 1);// Print the test text in the custom font
  spr.drawRoundRect(60 - 24,100,80,40,5,TFT_WHITE); 
  spr.setTextColor(TFT_WHITE);
  spr.drawNumber(val,60 - 20,100+10,1);
  spr.setTextColor(TFT_GREEN);
  spr.drawString("ppm", 60 + 12, 100+8, 1);
  // GM302B C2H5CH sensor
  val = gas.getGM302B();
  if (val > 999) val = 999;
  spr.setTextColor(TFT_WHITE);
  spr.drawString("C2H5CH:", 230 -24 , 100 - 24 , 1);// Print the test text in the custom font
  spr.drawRoundRect(230 - 24,100,80,40,5,TFT_WHITE);
  spr.setTextColor(TFT_WHITE);
  spr.drawNumber(val,230 - 20,100+10,1);
  spr.setTextColor(TFT_GREEN);
  spr.drawString("ppm", 230 + 12, 100+8, 1);
  // GM502B VOC sensor
  val = gas.getGM502B();
  if (val > 999) val = 999;
  spr.setTextColor(TFT_WHITE);
  spr.drawString("VOC:", 60 - 24, 180 -24 , 1);// Print the test text in the custom font
  spr.drawRoundRect(60 - 24,180,80,40,5,TFT_WHITE);
  spr.setTextColor(TFT_WHITE);
  spr.drawNumber(val,60 - 20,180+10,1);
  spr.setTextColor(TFT_GREEN);
  spr.drawString("ppm", 60 + 12, 180+8, 1);
  // GM702B CO sensor
  val = gas.getGM702B();
  if (val > 999) val = 999;
  spr.setTextColor(TFT_WHITE);
  spr.drawString("CO:", 230 -24 , 180 - 24, 1);// Print the test text in the custom font
  spr.drawRoundRect(230 - 24 ,180,80,40,5,TFT_WHITE);
  spr.setTextColor(TFT_WHITE);
  spr.drawNumber(val ,230 - 20 ,180+10,1);
  spr.setTextColor(TFT_GREEN);
  spr.drawString("ppm", 230 + 12, 180+8, 1);
 
  spr.pushSprite(0, 0);
  delay(100);
 
}
