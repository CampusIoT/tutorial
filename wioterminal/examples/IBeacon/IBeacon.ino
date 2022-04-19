#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
TFT_eSPI tft = TFT_eSPI();       // Invoke custom library
TFT_eSprite spr = TFT_eSprite(&tft);  // Sprite 

#include "sys/time.h"
#include "BLEDevice.h"
#include "BLEBeacon.h"

BLEAdvertising *pAdvertising;
//struct timeval now;

#define BEACON_UUID           "11111111-1111-1111-1111-111111111111" // UUID 1 128-Bit (may use linux tool uuidgen or random numbers via https://www.uuidgenerator.net/)

void setBeacon() {

  BLEBeacon oBeacon = BLEBeacon();
  oBeacon.setManufacturerId(0x4C00); // fake Apple 0x004C LSB (ENDIAN_CHANGE_U16!)
  oBeacon.setProximityUUID(BLEUUID(BEACON_UUID));
  oBeacon.setMajor(0x007B);
  oBeacon.setMinor(0x01C8);
  BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();
  BLEAdvertisementData oScanResponseData = BLEAdvertisementData();
  
  oAdvertisementData.setFlags(0x04); // BR_EDR_NOT_SUPPORTED 0x04
  
  std::string strServiceData = "";
  
  strServiceData += (char)26;     // Len
  strServiceData += (char)0xFF;   // Type
  strServiceData += oBeacon.getData(); 
  oAdvertisementData.addData(strServiceData);
  
  pAdvertising->setAdvertisementData(oAdvertisementData);
  pAdvertising->setScanResponseData(oScanResponseData);
  pAdvertising->setAdvertisementType(GAP_ADTYPE_ADV_NONCONN_IND);
}

void setup() {

  tft.begin();
  tft.init();
  tft.setRotation(3);  
  tft.fillScreen(TFT_BLACK);
  
//  Serial.begin(115200);
  while(Serial){};

  // Create the BLE Device
  BLEDevice::init("");

  // Create the BLE Server

  pAdvertising = BLEDevice::getAdvertising();
  
  setBeacon();
   // Start advertising
  pAdvertising->start();
  Serial.println("Advertizing started...");
  delay(100);
  Serial.printf("in deep sleep\n");

  spr.fillSprite(TFT_BLACK);
  spr.createSprite(260, 100);
  spr.setTextColor(TFT_WHITE, TFT_BLACK);
  spr.setFreeFont(&FreeSansBoldOblique18pt7b);
//  spr.drawString("Ibeacon -TWO", 25, 70);
  spr.drawString("Ibeacon -ONE", 25, 70);
  spr.pushSprite(0, 0);
}

void loop() {
  delay(1000);
}
