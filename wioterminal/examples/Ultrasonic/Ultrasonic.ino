#include "Ultrasonic.h" //include ultrasonic distance sensor library 
#include "TFT_eSPI.h" //include TFT LCD library 

TFT_eSPI tft; //initialize TFT LCD 

TFT_eSprite spr = TFT_eSprite(&tft); //initialize buffer
 
Ultrasonic ultrasonic(D0); //set ultrasonic distance sensor pin as D0

void setup()
{
  tft.begin(); //start TFT LCD
  tft.setRotation(3); //set screen rotation
  spr.createSprite(TFT_HEIGHT,TFT_WIDTH); //create buffer
  
}
void loop()
{
    spr.fillSprite(TFT_BLACK); //fill background 
    spr.setTextSize(2); //set text size 
    spr.setTextColor(TFT_YELLOW); //set text color 
    
    spr.drawString("Distance to Object", 55, 10); //draw text string 
    spr.drawFastHLine(40, 35, 240, TFT_DARKGREY); //draw horizontal line 
    
    spr.setTextColor(TFT_WHITE); 
    spr.drawString("- Centimeters: ", 20, 50);
    spr.drawString("- Inches: ", 20, 80);
    
    spr.drawNumber(ultrasonic.MeasureInCentimeters(), 200,50); //display distance in centimeters
    delay(50);
    spr.drawNumber(ultrasonic.MeasureInInches(), 130,80); //display distance in inches 
    
    spr.pushSprite(0,0); //push to LCD 
    delay(500);
}
