/*
  Use ESP32 WiFi to get RTCM data from RTK2Go (caster) as a Client
  By: SparkFun Electronics / Nathan Seidle
  Date: November 18th, 2021
  License: MIT. See license file for more information but you can
  basically do whatever you want with this code.

  This example shows how to obtain RTCM data from a NTRIP Caster over WiFi
  and push it over I2C to a ZED-F9x.
  It's confusing, but the Arduino is acting as a 'client' to a 'caster'. In this case we will
  use RTK2Go.com as our caster because it is free. See the NTRIPServer example to see how
  to push RTCM data to the caster.

  You will need to have a valid mountpoint available. To see available mountpoints go here: http://rtk2go.com:2101/

  This is a proof of concept to show how to connect to a caster via HTTP. Using WiFi for a rover
  is generally a bad idea because of limited WiFi range in the field.

  For more information about NTRIP Clients and the differences between Rev1 and Rev2 of the protocol
  please see: https://www.use-snip.com/kb/knowledge-base/ntrip-rev1-versus-rev2-formats/

  Feel like supporting open source hardware?
  Buy a board from SparkFun!
  ZED-F9P RTK2: https://www.sparkfun.com/products/16481
  RTK Surveyor: https://www.sparkfun.com/products/18443
  RTK Express: https://www.sparkfun.com/products/18442

  Hardware Connections:
  Plug a Qwiic cable into the GPS and a ESP32 Thing Plus
  If you don't have a platform with a Qwiic connection use the SparkFun Qwiic Breadboard Jumper (https://www.sparkfun.com/products/14425)
  Open the serial monitor at 115200 baud to see the output

  With WioTerminal, connect the ZED-F9P module to the I2C Grove Connector of the WioTerminal
    pin 1 - Yellow (for example, SCL on I2C Grove Connectors)
    pin 2 - White (for example, SDA on I2C Grove Connectors)
    pin 3 - Red - VCC on all Grove Connectors
    pin 4 - Black - GND on all Grove Connectors

CHANGES: Didier DONSEZ for Wio Terminal

*/

#define CENTIPEDE 1

#include "secrets.h"


#if defined(ARDUINO_ARCH_ESP32)
#include <WiFi.h>
#elif defined(ARDUINO_WIO_TERMINAL)
#include "rpcWiFi.h"
#else
#error "Only ESP32 and Wio Terminal are supported"
#endif

#include <SparkFun_u-blox_GNSS_Arduino_Library.h> //http://librarymanager/All#SparkFun_u-blox_GNSS
SFE_UBLOX_GNSS myGNSS;

//The ESP32 core has a built in base64 library but not every platform does
//We'll use an external lib if necessary.

#if defined(ARDUINO_ARCH_ESP32)
#include "base64.h" //Built-in ESP32 library
#elif defined(ARDUINO_WIO_TERMINAL)
/* 
 *  1) Download the ZIP file of the base64 library https://github.com/adamvr/arduino-base64
 *  2) Uncompress the ZIP file of the base64 library https://github.com/adamvr/arduino-base64
 *  3) Rename Base64.h in ArduinoBase64.h since there is a name conflict
 *  4) Edit Base64.cpp for changing Base64.h
 *  5) Compress the directory as a ZIP file
 *  6) Install the new ZIP file of the base64 library
*/
#include <ArduinoBase64.h>
#else
#error "Only ESP32 and Wio Terminal are supported"
#endif

//Global variables
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
long lastReceivedRTCM_ms = 0; //5 RTCM messages take approximately ~300ms to arrive at 115200bps
int maxTimeBeforeHangup_ms = 10000; //If we fail to get a complete RTCM frame after 10s, then disconnect from caster
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// RTCM3 Utilities

static void hexdump(const uint8_t* buf, const size_t len, const size_t linelen) {
  for(size_t i=0; i<len; i++){
     if(i%linelen==0) {
        Serial.println();
     }
     if (buf[i] < 0x10) Serial.print("0");
     Serial.print(buf[i], HEX);
     Serial.print(" ");
  }
  Serial.println();
}    

/* extract unsigned/signed bits ------------------------------------------------
* extract unsigned/signed bits from byte data
* args   : unsigned char *buff I byte data
*          int    pos    I      bit position from start of data (bits)
*          int    len    I      bit length (bits) (len<=32)
* return : extracted unsigned/signed bits
*-----------------------------------------------------------------------------*/
static unsigned int getbitu(const unsigned char *buff, int pos, int len)
{
    unsigned int bits=0;
    int i;
    for (i=pos;i<pos+len;i++) bits=(bits<<1)+((buff[i/8]>>(7-i%8))&1u);
    return bits;
}
static int getbits(const unsigned char *buff, int pos, int len)
{
    unsigned int bits=getbitu(buff,pos,len);
    if (len<=0||32<=len||!(bits&(1u<<(len-1)))) return (int)bits;
    return (int)(bits|(~0u<<len)); /* extend sign */
}

/*
 Dump type of RTCM3 message
*/

/* RTCM3 Type 1004: extended L1&L2 gps rtk observables ----------------------*/
/* RTCM3 Type 1005: stationary rtk reference station arp --------------------*/
/* RTCM3 Type 1006: stationary rtk reference station arp with height --------*/
/* RTCM3 Type 1007: antenna descriptor --------------------------------------*/
/* RTCM3 Type 1008: antenna descriptor & serial number ----------------------*/
/* RTCM3 Type 1009: L1-only glonass rtk observables -------------------------*/
/* RTCM3 Type 1010: extended L1-only glonass rtk observables ----------------*/
/* RTCM3 Type 1011: L1&L2 glonass rtk observables ---------------------------*/
/* RTCM3 Type 1012: extended L1&L2 glonass rtk observables ------------------*/
/* RTCM3 Type 1013: system parameters ---------------------------------------*/
/* RTCM3 Type 1019: gps ephemerides -----------------------------------------*/
/* RTCM3 Type 1020: glonass ephemerides -------------------------------------*/
/* RTCM3 Type 1021: helmert/abridged molodenski -----------------------------*/
/* RTCM3 Type 1022: moledenski-badekas transfromation -----------------------*/
/* RTCM3 Type 1023: residual, ellipoidal grid representation ----------------*/
/* RTCM3 Type 1024: residual, plane grid representation ---------------------*/
/* RTCM3 Type 1025: projection (types except LCC2SP,OM) ---------------------*/
/* RTCM3 Type 1026: projection (LCC2SP - lambert conic conformal (2sp)) -----*/
/* RTCM3 Type 1027: projection (type OM - oblique mercator) -----------------*/
/* RTCM3 Type 1030: network rtk residual ------------------------------------*/
/* RTCM3 Type 1031: glonass network rtk residual ----------------------------*/
/* RTCM3 Type 1032: physical reference station position information ---------*/
/* RTCM3 Type 1033: receiver and antenna descriptor -------------------------*/
/* RTCM3 Type 1034: gps network fkp gradient --------------------------------*/
/* RTCM3 Type 1035: glonass network fkp gradient ----------------------------*/
/* RTCM3 Type 1037: glonass network rtk ionospheric correction difference ---*/
/* RTCM3 Type 1038: glonass network rtk geometic correction difference ------*/
/* RTCM3 Type 1039: glonass network rtk combined correction difference ------*/
/* RTCM3 Type 1042/63: beidou ephemerides -----------------------------------*/
/* RTCM3 Type 1044: qzss ephemerides (ref [15]) -----------------------------*/
/* RTCM3 Type 1045: galileo F/NAV satellite ephemerides (ref [15]) ----------*/
/* RTCM3 Type 1046: galileo I/NAV satellite ephemerides (ref [17]) ----------*/

static void dump_rtcm3_type(const unsigned int type) {
  switch(type){
    case 1004:
      Serial.print("Extended L1&L2 GPS RTK Observables");
      break;
    case 1005:
      Serial.print("Stationary RTK Reference Station ARP");
      break;
    case 1019:
      Serial.print("GPS ephemerides");
      break;
    case 1020:
      Serial.print("GLONASS ephemerides");
      break;
    case 1042:
      Serial.print("Beidou ephemerides");
      break;
    case 1046:
      Serial.print("Galileo I/NAV satellite ephemerides (ref [17])");
      break;
    case 1074:
      Serial.print("GPS MSM4");
      break;
    case 1084:
      Serial.print("GLONASS MSM4");
      break;
    case 1094:
      Serial.print("Galileo MSM4");
      break;
    case 1124:
      Serial.print("BeiDou MSM4");
      break;
    case 1230:
      Serial.print("GLONASS L1 and L2 Code-Phase Biases");
      break;
    default:
      Serial.print("Unknown");
      break;
  }
}

static int dump_rtcm3(const uint8_t* buf, const size_t len)
{
    double tow;
    int ret=0,type=getbitu(buf,24,12),week;
    
    Serial.print("RTCM3 message: len=");
    Serial.print(len);
    Serial.print(" type=");
    Serial.print(type);
    Serial.print(" : ");
    dump_rtcm3_type(type);
}

// WiFi Utilities

void WifiScan(){
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

      Serial.println("scan start");
 
    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
            delay(10);
        }
    }
    Serial.println("");
}


void WifiConnect() {
  Serial.print("Connecting to local WiFi ");
  WiFi.begin((char*)ssid, (char*)password);
  while (WiFi.status() != WL_CONNECTED) {
    //WiFi.begin((char*)ssid, (char*)password);
    delay(1000);
    Serial.print(".");
  }
 
  Serial.print("\nWiFi connected with IP: ");
  Serial.println(WiFi.localIP());
}

// Main

void setup()
{
  Serial.begin(115200);
  Serial.println(F("NTRIP testing"));

  Wire.begin(); //Start I2C

  if (myGNSS.begin() == false) //Connect to the Ublox module using Wire port
  {
    Serial.println(F("u-blox GPS not detected at default I2C address. Please check wiring. Freezing."));
    while (1);
  }
  Serial.println(F("u-blox module connected"));

  myGNSS.setI2COutput(COM_TYPE_UBX); //Turn off NMEA noise
  myGNSS.setPortInput(COM_PORT_I2C, COM_TYPE_UBX | COM_TYPE_NMEA | COM_TYPE_RTCM3); //Be sure RTCM3 input is enabled. UBX + RTCM3 is not a valid state.

  myGNSS.setNavigationFrequency(1); //Set output in Hz.

  WifiScan();
  WifiConnect();

  while (Serial.available()) Serial.read();
}

void loop()
{
  if (Serial.available())
  {
    beginClient();
    while (Serial.available()) Serial.read(); //Empty buffer of any newline chars
  }

  Serial.println(F("Press any key to start NTRIP Client."));

  delay(1000);
}

//Connect to NTRIP Caster, receive RTCM, and push to ZED module over I2C
void beginClient()
{
  WiFiClient ntripClient;
  long rtcmCount = 0;

  Serial.println(F("Subscribing to Caster. Press key to stop"));
  delay(10); //Wait for any serial to arrive
  while (Serial.available()) Serial.read(); //Flush

  while (Serial.available() == 0)
  {
    //Connect if we are not already. Limit to 5s between attempts.
    if (ntripClient.connected() == false)
    {
      Serial.print(F("Opening socket to "));
      Serial.println(casterHost);

      if (ntripClient.connect(casterHost, casterPort) == false) //Attempt connection
      {
        Serial.println(F("Connection to caster failed"));
        return;
      }
      else
      {
        Serial.print(F("Connected to "));
        Serial.print(casterHost);
        Serial.print(F(": "));
        Serial.println(casterPort);

        Serial.print(F("Requesting NTRIP Data from mount point "));
        Serial.println(mountPoint);

        const int SERVER_BUFFER_SIZE  = 512;
        char serverRequest[SERVER_BUFFER_SIZE];

        snprintf(serverRequest, SERVER_BUFFER_SIZE, "GET /%s HTTP/1.0\r\nUser-Agent: NTRIP SparkFun u-blox Client v1.0\r\n",
                 mountPoint);

        char credentials[512];
        if (strlen(casterUser) == 0)
        {
          strncpy(credentials, "Accept: */*\r\nConnection: close\r\n", sizeof(credentials));
        }
        else
        {
          //Pass base64 encoded user:pw
          char userCredentials[sizeof(casterUser) + sizeof(casterUserPW) + 1]; //The ':' takes up a spot
          snprintf(userCredentials, sizeof(userCredentials), "%s:%s", casterUser, casterUserPW);

          Serial.print(F("Sending credentials: "));
          Serial.println(userCredentials);

#if defined(ARDUINO_ARCH_ESP32)
          //Encode with ESP32 built-in library
          base64 b;
          String strEncodedCredentials = b.encode(userCredentials);
          char encodedCredentials[strEncodedCredentials.length() + 1];
          strEncodedCredentials.toCharArray(encodedCredentials, sizeof(encodedCredentials)); //Convert String to char array
          snprintf(credentials, sizeof(credentials), "Authorization: Basic %s\r\n", encodedCredentials);
#elif defined(ARDUINO_WIO_TERMINAL)
          //Encode with nfriendly library
          int encodedLen = base64_enc_len(strlen(userCredentials));
          char encodedCredentials[encodedLen]; //Create array large enough to house encoded data
          base64_encode(encodedCredentials, userCredentials, strlen(userCredentials)); //Note: Input array is consumed
#else
#error "Only ESP32 and Wio Terminal are supported"
#endif
        }
        strncat(serverRequest, credentials, SERVER_BUFFER_SIZE);
        strncat(serverRequest, "\r\n", SERVER_BUFFER_SIZE);

        Serial.print(F("serverRequest size: "));
        Serial.print(strlen(serverRequest));
        Serial.print(F(" of "));
        Serial.print(sizeof(serverRequest));
        Serial.println(F(" bytes available"));

        Serial.println(F("Sending server request:"));
        Serial.println(serverRequest);
        ntripClient.write(serverRequest, strlen(serverRequest));

        //Wait for response
        unsigned long timeout = millis();
        while (ntripClient.available() == 0)
        {
          if (millis() - timeout > 5000)
          {
            Serial.println(F("Caster timed out!"));
            ntripClient.stop();
            return;
          }
          delay(10);
        }

        //Check reply
        bool connectionSuccess = false;
        char response[512];
        int responseSpot = 0;
        while (ntripClient.available())
        {
          if (responseSpot == sizeof(response) - 1) break;

          response[responseSpot++] = ntripClient.read();
          if (strstr(response, "200") > 0) //Look for 'ICY 200 OK'
            connectionSuccess = true;
          if (strstr(response, "401") > 0) //Look for '401 Unauthorized'
          {
            Serial.println(F("Hey - your credentials look bad! Check you caster username and password."));
            connectionSuccess = false;
          }
        }
        response[responseSpot] = '\0';

        Serial.print(F("Caster responded with: "));
        Serial.println(response);

        if (connectionSuccess == false)
        {
          Serial.print(F("Failed to connect to "));
          Serial.print(casterHost);
          Serial.print(F(": "));
          Serial.println(response);
          return;
        }
        else
        {
          Serial.print(F("Connected to "));
          Serial.println(casterHost);
          lastReceivedRTCM_ms = millis(); //Reset timeout
        }
      } //End attempt to connect
    } //End connected == false

    if (ntripClient.connected() == true)
    {
      uint8_t rtcmData[512 * 4]; //Most incoming data is around 500 bytes but may be larger
      rtcmCount = 0;

      //Print any available RTCM data
      while (ntripClient.available())
      {
        //Serial.write(ntripClient.read()); //Pipe to serial port is fine but beware, it's a lot of binary data
        rtcmData[rtcmCount++] = ntripClient.read();
        // TODO if rtcmCount > 512 * 4 then buffer overflow !!!!!!
        if (rtcmCount == sizeof(rtcmData)) break;
      }

      if (rtcmCount > 0)
      {
        lastReceivedRTCM_ms = millis();

        if(rtcmData[0]!=0xD3) {
          Serial.print(F("Not a RTCM3 messages. Discard "));
          Serial.print(rtcmCount);
          Serial.println(F(" bytes"));
        } else {
          dump_rtcm3(rtcmData, rtcmCount);
          Serial.print(F(" --> RTCM pushed "));
          Serial.print(rtcmCount);
          Serial.println(F(" bytes to ZED"));

          //Push RTCM to GNSS module over I2C
          myGNSS.pushRawData(rtcmData, rtcmCount, false);
#ifdef RTCM_HEXDUMP
          hexdump(rtcmData, rtcmCount, 32);
#endif
        }
      }
    }

    //Close socket if we don't have new data for 10s
    if (millis() - lastReceivedRTCM_ms > maxTimeBeforeHangup_ms)
    {
      Serial.println(F("RTCM timeout. Disconnecting..."));
      if (ntripClient.connected() == true)
        ntripClient.stop();
      return;
    }

    delay(10);
  }

  Serial.println(F("User pressed a key"));
  Serial.println(F("Disconnecting..."));
  ntripClient.stop();
}
