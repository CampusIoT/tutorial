//Libraries
#include "Mouse.h" //mouse library 
#include "LIS3DHTR.h" //built-in accelerometer library 
#include "TFT_eSPI.h" //TFT LCD library 

//Initializations
LIS3DHTR <TwoWire> lis; //initialize accelerometer 
TFT_eSPI tft; //initialize TFT LCD 
TFT_eSprite spr = TFT_eSprite(&tft); //initialize buffer

int range = 25; //output range of X or Y movement (affects movement speed)       

int responseDelay = 2; //response delay of the mouse (in ms)

void setup() {
  //configure button and switch pins as inputs 
  pinMode(WIO_5S_UP, INPUT);
  pinMode(WIO_5S_DOWN, INPUT);
  pinMode(WIO_KEY_C, INPUT);
  pinMode(WIO_KEY_B, INPUT);
  
  Mouse.begin(); //start mouse control
  lis.begin(Wire1); //start accelerometer
  
  //Configure accelerometer 
  lis.setOutputDataRate(LIS3DHTR_DATARATE_25HZ); //data output rate (1Hz up to 5kHz)
  lis.setFullScaleRange(LIS3DHTR_RANGE_2G); //Scale range set to 2g (2,4,8,16g)

  tft.begin(); //start TFT LCD
  tft.setRotation(3); //set TFT LCD rotation 
  
}

void loop() {

  //Drawing UI on TFT LCD 
  spr.createSprite(TFT_HEIGHT,TFT_WIDTH); //create buffer
  spr.fillSprite(TFT_WHITE); //set background color 

  //Draw header title
  spr.fillRect(0,0,320,50,TFT_BLUE); //draw rectangle with fill color 
  spr.setTextSize(4); //set text size
  spr.setTextColor(TFT_WHITE); //set text color 
  spr.drawString("AIR MOUSE",50,10); //draw a text string 

  //Draw for scroll
  spr.setTextSize(3);
  spr.setTextColor(TFT_BLACK);
  spr.drawString("SCROLL",110,130);
  spr.drawTriangle(160,70,120,120,200,120,TFT_BLUE); //draw triangle with border
  spr.drawTriangle(160,210,120,160,200,160,TFT_BLUE);
  

  //draw for left and right mouse buttons
  spr.drawRect(0,50,100,190,TFT_DARKGREEN); //draw rectangle with border 
  spr.drawString("LEFT",15,130);
  spr.drawRect(220,50,100,190,TFT_DARKGREEN);
  spr.drawString("RIGHT",228,130); 
  
  spr.pushSprite(0,0); //push to LCD
  
  float x_values = lis.getAccelerationX(); //assign variable to store accleration in x-axis 
  float y_values = lis.getAccelerationY(); //assign variable to store accleration in y-axis 
  
  // calculate the movement distance based on the button and switch states
  int  xDistance = (-y_values) * range;
  int  yDistance = (x_values)  * range;

//mouse move 
  if ((xDistance != 0) || (yDistance != 0)) {   // if X or Y is non-zero, then move the mouse pointer
    Mouse.move(xDistance, yDistance, 0); //move the mouse pointer in x and y
  }
  
//mouse button left click 
  if (digitalRead(WIO_KEY_C) == LOW) { //detect left mouse button press
    if (!Mouse.isPressed(MOUSE_LEFT)) { //check whether left mouse button is pressed
      Mouse.click(MOUSE_LEFT); //click left mouse button 
    }

      spr.createSprite(TFT_HEIGHT,TFT_WIDTH); //create buffer
      spr.setTextSize(3);
      spr.setTextColor(TFT_WHITE);
      spr.fillRect(0,50,100,190,TFT_DARKGREEN);
      spr.drawString("LEFT",15,130);
      spr.pushSprite(0,0);
      spr.deleteSprite(); //clear buffer
      delay(100);
      
  }
  else {
    // if the left mouse button is pressed, release it
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT);
    }
  }

  
//mouse button right click 
  if (digitalRead(WIO_KEY_B) == LOW) { //detect right mouse button press
    if (!Mouse.isPressed(MOUSE_RIGHT)) { //check whether right mouse button is pressed
      Mouse.click(MOUSE_RIGHT); //click right mouse button 
    }
      spr.createSprite(TFT_HEIGHT,TFT_WIDTH); //create buffer
      spr.setTextSize(3);
      spr.setTextColor(TFT_WHITE);
      spr.fillRect(220,50,100,190,TFT_DARKGREEN);
      spr.drawString("RIGHT",228,130);
      spr.pushSprite(0,0);
      spr.deleteSprite(); //clear buffer
      delay(100);
  }

  else {
    // if the mouse is pressed, release it:
    if (Mouse.isPressed(MOUSE_RIGHT)) {
      Mouse.release(MOUSE_RIGHT);
    }
  }

//mouse scroll up
  if ((digitalRead(WIO_5S_UP) == LOW)) { //detect 5-way switch press and up switch 
    Mouse.move(0, 0, 1); //scroll up
    spr.createSprite(TFT_HEIGHT,TFT_WIDTH); //create buffer
    spr.fillTriangle(160,70,120,120,200,120,TFT_BLUE);
    spr.pushSprite(0,0);
    spr.deleteSprite(); //clear buffer
    delay(50);
  }

//mouse scroll down
  if ((digitalRead(WIO_5S_DOWN) == LOW)) { //detect 5-way switch press and down switch
    Mouse.move(0, 0, -1); //scroll down
    spr.createSprite(TFT_HEIGHT,TFT_WIDTH); //create buffer
    spr.fillTriangle(160,210,120,160,200,160,TFT_BLUE);
    spr.pushSprite(0,0);
    spr.deleteSprite(); //clear buffer
    delay(50);
  }
    
}
