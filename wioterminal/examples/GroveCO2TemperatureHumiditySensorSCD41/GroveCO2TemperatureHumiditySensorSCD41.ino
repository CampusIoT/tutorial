#include <SPI.h>
#include <Wire.h>
#include <TFT_eSPI.h>
#include <SensirionI2CScd4x.h>

#include "icon_thermometer.h"
#include "icon_humidity.h"
#include "icon_co2.h"


#define ENABLE_LOG 1

#if ENABLE_LOG==1
#include <Seeed_FS.h>
#include "SD/Seeed_SD.h"
#endif

#define CO2_THRESHOLD     (1200U)

#if ENABLE_LOG==1 
File myFile; //Intialise the file Class and named it myFile
#endif

SensirionI2CScd4x scd4x;
TFT_eSPI tft = TFT_eSPI();

unsigned int prev_time = 0;
bool alarm = false;

void printUint16Hex(uint16_t value) 
{
  Serial.print(value < 4096 ? "0" : "");
  Serial.print(value < 256 ? "0" : "");
  Serial.print(value < 16 ? "0" : "");
  Serial.print(value, HEX);
}

void printSerialNumber(uint16_t serial0, uint16_t serial1, uint16_t serial2) 
{
  Serial.print("Serial: 0x");
  printUint16Hex(serial0);
  printUint16Hex(serial1);
  printUint16Hex(serial2);
  Serial.println();
}

void setup() {

  Serial.begin(115200);
 
#if ENABLE_LOG==1
  Serial.print("Initializing SD card...");
  if (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("scd41.csv", FILE_APPEND); //Writing Mode
  if (!myFile) {
    // if the file didn't open, print an error:
    Serial.println("error opening scd41.csv");
  }
#endif

  pinMode(WIO_5S_PRESS, INPUT_PULLUP);
  pinMode(WIO_BUZZER, OUTPUT);
  pinMode(D0, OUTPUT); // Relay
  digitalWrite(D0, LOW);

  tft.init();
  tft.setRotation(3);
  tft.setTextFont(4);
  tft.fillScreen(TFT_BLACK);

  Wire.begin();
  uint16_t error;
  char errorMessage[256];

  scd4x.begin(Wire);

  // stop potentially previously started measurement
  error = scd4x.stopPeriodicMeasurement();
  if (error) {
    Serial.print("Error trying to execute stopPeriodicMeasurement(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
    tft.print(errorMessage);
  }

  uint16_t serial0;
  uint16_t serial1;
  uint16_t serial2;

  error = scd4x.getSerialNumber(serial0, serial1, serial2);
  if (error) {
    Serial.print("Error trying to execute getSerialNumber(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
    tft.print(errorMessage);
  } else {
    printSerialNumber(serial0, serial1, serial2);
  }

  // Start Measurement
  error = scd4x.startPeriodicMeasurement();
  if (error) {
    Serial.print("Error trying to execute startPeriodicMeasurement(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
    tft.print(errorMessage);
  }

  Serial.println("Waiting for first measurement... (5 sec)");
  tft.setCursor(100, 80);
  tft.print("Waiting...");
  delay(5000);
  tft.fillScreen(TFT_BLACK);
  tft.drawXBitmap(20, 20, icon_co2_bits, icon_co2_width, icon_co2_height, TFT_YELLOW);
  tft.drawXBitmap(20, 90, icon_therm_bits, icon_therm_width, icon_therm_height, TFT_RED);
  tft.drawXBitmap(20, 160, icon_hum_bits, icon_hum_width, icon_hum_height, TFT_CYAN);

}

uint16_t prev_co2 = 0;
void loop()
{

  unsigned long curr_time = millis();

  if ((curr_time - prev_time) > 5000) {
    prev_time = curr_time;

    uint16_t error;
    char errorMessage[256];

    // Read Measurement
    uint16_t co2;
    float temperature;
    float humidity;

    error = scd4x.readMeasurement(co2, temperature, humidity);
    if (error) {
      Serial.print("Error trying to execute readMeasurement(): ");
      errorToString(error, errorMessage, 256);
      Serial.println(errorMessage);
      tft.print(errorMessage);
    } else if (co2 == 0) {
      Serial.println("Invalid sample detected, skipping.");
    } else {
      if (co2 > CO2_THRESHOLD) {
        alarm = true;
      } else {
        alarm = false;
      }
      Serial.print("Co2:");
      Serial.print(co2);
      Serial.print("\t");
      Serial.print("Temperature:");
      Serial.print(temperature);
      Serial.print("\t");
      Serial.print("Humidity:");
      Serial.println(humidity);

 
#if ENABLE_LOG==1
  // if the file opened okay, write to it:
  if (myFile) {
      Serial.print(co2);
      Serial.print(";");
      Serial.print(temperature);
      Serial.print(";");
      Serial.print(humidity);
      Serial.println("\n");
  }
#endif 

      // clear previous value by setting black font color
      tft.setTextFont(6);
      tft.setCursor(90, 30);
      tft.setTextColor(TFT_BLACK, TFT_BLACK);
      tft.print(prev_co2);
      tft.setTextFont(4);
      tft.print("ppm");

      tft.setTextFont(6);
      tft.setCursor(90, 30);
      tft.setTextColor(TFT_YELLOW, TFT_BLACK);
      tft.print(co2);
      tft.setTextFont(4);
      tft.print("ppm");
      prev_co2 = co2;

      char temp[5];
      sprintf(temp, "%0.1f", temperature);
      tft.setCursor(90, 100);
      tft.setTextFont(6);
      tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.print(temp);
      tft.setTextFont(4);
      tft.print("`C");

      char hum[5];
      sprintf(hum, "%0.1f", humidity);
      tft.setCursor(90, 170);
      tft.setTextFont(6);
      tft.setTextColor(TFT_CYAN, TFT_BLACK);
      tft.print(hum);
      tft.setTextFont(4);
      tft.print("RH");
    }
  }


  if (digitalRead(WIO_5S_PRESS) == LOW) {
    alarm = false;
  }

  if (alarm) {
    analogWrite(WIO_BUZZER, 128);
    delay(1000);
    analogWrite(WIO_BUZZER, 0);
    delay(700);
    digitalWrite(D0, HIGH); // Relay Switch on
  } else {
    digitalWrite(D0, LOW); // Relay Switch off
  }

  delay(300);
}
