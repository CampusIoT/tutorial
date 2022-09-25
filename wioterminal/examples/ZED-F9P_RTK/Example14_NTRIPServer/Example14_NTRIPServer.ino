/*
  Use ESP32 WiFi to push RTCM data to RTK2Go (caster) as a Server
  By: SparkFun Electronics / Nathan Seidle
  Date: December 14th, 2020
  License: MIT. See license file for more information but you can
  basically do whatever you want with this code.

  This example shows how to gather RTCM data over I2C and push it to a casting service over WiFi.
  It's confusing, but the Arduino is acting as a 'server' to a 'caster'. In this case we will
  use RTK2Go.com as our caster because it is free. A rover (car, surveyor stick, etc) can
  then connect to RTK2Go as a 'client' and get the RTCM data it needs.

  You will need to register your mountpoint here: http://www.rtk2go.com/new-reservation/
  (They'll probably block the credentials we include in this example)

  To see if your mountpoint is active go here: http://rtk2go.com:2101/

  This is a proof of concept. Serving RTCM to a caster over WiFi is useful when you need to
  set up a high-precision base station.

  Feel like supporting open source hardware?
  Buy a board from SparkFun!
  ZED-F9P RTK2: https://www.sparkfun.com/products/16481
  RTK Surveyor: https://www.sparkfun.com/products/17369

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
#define WIO_TERMINAL 1
//#define CENTIPEDE 1


//#define BUF_HEXDUMP 1

#ifdef WIO_TERMINAL
#include "rpcWiFi.h"
#else 
#include <WiFi.h>
#endif

#include "secrets.h"
WiFiClient client;

#include <Wire.h> //Needed for I2C to GPS
#include "SparkFun_Ublox_Arduino_Library.h" //http://librarymanager/All#SparkFun_u-blox_GNSS
SFE_UBLOX_GPS myGPS;

//Basic Connection settings to RTK2Go NTRIP Caster - See secrets for mount specific credentials
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#ifdef CENTIPEDE
const char * casterHost = "caster.centipede.fr";
#else
const char * casterHost = "www.RTK2go.com";
#endif
const uint16_t casterPort = 2101;

#ifdef WIO_TERMINAL
const char * ntrip_server_name = "WioTerminal_RTK_Surveyor_Ublox_ZED-F9P";
#else
const char * ntrip_server_name = "SparkFun_RTK_Surveyor_Ublox_ZED-F9P";
#endif

long lastSentRTCM_ms = 0; //Time of last data pushed to socket
int maxTimeBeforeHangup_ms = 10000; //If we fail to get a complete RTCM frame after 10s, then disconnect from caster

uint32_t serverBytesSent = 0; //Just a running total
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

long lastReport_ms = 0; //Time of last report of bytes sent

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
    delay(500);
    Serial.print(".");
  }
 
  Serial.print("\nWiFi connected with IP: ");
  Serial.println(WiFi.localIP());
}

void setup()
{
  Serial.begin(115200); // You may need to increase this for high navigation rates!
  while (!Serial)
    ; //Wait for user to open terminal
  Serial.println(F("SparkFun u-blox Example"));
#ifdef WIO_TERMINAL
  Serial.printf("RTL8720 Firmware Version: %s\n", rpc_system_version());
#endif

  Wire.begin();

  //myGPS.enableDebugging(); // Uncomment this line to enable debug messages

  if (myGPS.begin() == false) //Connect to the u-blox module using Wire port
  {
    Serial.println(F("u-blox GPS not detected at default I2C address. Please check wiring. Freezing."));
    while (1)
      ;
  }


  WifiScan();
  WifiConnect();

  myGPS.setI2COutput(COM_TYPE_UBX | COM_TYPE_NMEA | COM_TYPE_RTCM3); //UBX+RTCM3 is not a valid option so we enable all three.

  myGPS.setNavigationFrequency(1); //Set output in Hz. RTCM rarely benefits from >1Hz.

  //Disable all NMEA sentences
  bool response = true;
  response &= myGPS.disableNMEAMessage(UBX_NMEA_GGA, COM_PORT_I2C);
  response &= myGPS.disableNMEAMessage(UBX_NMEA_GSA, COM_PORT_I2C);
  response &= myGPS.disableNMEAMessage(UBX_NMEA_GSV, COM_PORT_I2C);
  response &= myGPS.disableNMEAMessage(UBX_NMEA_RMC, COM_PORT_I2C);
  response &= myGPS.disableNMEAMessage(UBX_NMEA_GST, COM_PORT_I2C);
  response &= myGPS.disableNMEAMessage(UBX_NMEA_GLL, COM_PORT_I2C);
  response &= myGPS.disableNMEAMessage(UBX_NMEA_VTG, COM_PORT_I2C);

  if (response == false)
  {
    Serial.println(F("Failed to disable NMEA. Freezing..."));
    while (1);
  }
  else
  {
    Serial.println(F("NMEA disabled"));
  }

  // Enable necessary RTCM sentences
  // All types are listed here : https://www.use-snip.com/kb/knowledge-base/rtcm-3-message-list  
  //response &= myGPS.enableRTCMmessage(UBX_RTCM_1004, COM_PORT_I2C, 1); // Enable message 1004 (Extended L1&L2 GPS RTK Observables) to output through I2C, message every second
  response &= myGPS.enableRTCMmessage(UBX_RTCM_1005, COM_PORT_I2C, 1); // Enable message 1005 (Stationary RTK Reference Station ARP) to output through I2C, message every second
  response &= myGPS.enableRTCMmessage(UBX_RTCM_1074, COM_PORT_I2C, 1); // Enable message 1074 (GPS MSM4) to output through I2C, message every second
  response &= myGPS.enableRTCMmessage(UBX_RTCM_1084, COM_PORT_I2C, 1); // Enable message 1084 (GLONASS MSM4) to output through I2C, message every second
  response &= myGPS.enableRTCMmessage(UBX_RTCM_1094, COM_PORT_I2C, 1); // Enable message 1094 (Galileo MSM4) to output through I2C, message every second
  response &= myGPS.enableRTCMmessage(UBX_RTCM_1124, COM_PORT_I2C, 1); // Enable message 1124 (BeiDou MSM4) to output through I2C, message every second
  response &= myGPS.enableRTCMmessage(UBX_RTCM_1230, COM_PORT_I2C, 10); // Enable message 1230 (GLONASS L1 and L2 Code-Phase Biases) to output through I2C, message every 10 seconds

  if (response == false)
  {
    Serial.println(F("Failed to enable RTCM. Freezing..."));
    while (1);
  }
  else
    Serial.println(F("RTCM sentences enabled"));

  //-1280208.308,-4716803.847,4086665.811 is SparkFun HQ so...
  //Units are cm with a high precision extension so -1234.5678 should be called: (-123456, -78)
  //For more infomation see Example12_setStaticPosition
  //Note: If you leave these coordinates in place and setup your antenna *not* at SparkFun, your receiver
  //will be very confused and fail to generate correction data because, well, you aren't at SparkFun...
  //See this tutorial on getting PPP coordinates: https://learn.sparkfun.com/tutorials/how-to-build-a-diy-gnss-reference-station/all
  
  response &= myGPS.setStaticPosition(-128020830, -80, -471680384, -70, 408666581, 10); //With high precision 0.1mm parts
  if (response == false)
  {
    Serial.println(F("Failed to enter static position. Freezing..."));
    while (1);
  }
  else
    Serial.println(F("Static position set"));

  //You could instead do a survey-in but it takes much longer to start generating RTCM data. See Example4_BaseWithLCD
  //myGPS.enableSurveyMode(60, 5.000); //Enable Survey in, 60 seconds, 5.0m

  if (myGPS.saveConfiguration() == false) //Save the current settings to flash and BBR
    Serial.println(F("Module failed to save."));

  Serial.println(F("Module configuration complete"));
}

void loop()
{
  if (Serial.available()) beginServing();

  Serial.println(F("Press any key to start serving."));

  delay(1000);
}

void beginServing()
{
  Serial.println("Xmit to RTK2Go. Press any key to stop");
  delay(10); //Wait for any serial to arrive
  while (Serial.available()) Serial.read(); //Flush

  while (Serial.available() == 0)
  {
    //Connect if we are not already
    if (client.connected() == false)
    {
      Serial.printf("Opening socket to %s\n", casterHost);

      if (client.connect(casterHost, casterPort) == true) //Attempt connection
      {
        Serial.printf("Connected to %s:%d\n", casterHost, casterPort);

        const int SERVER_BUFFER_SIZE  = 512;
        char serverBuffer[SERVER_BUFFER_SIZE];

        snprintf(serverBuffer, SERVER_BUFFER_SIZE, "SOURCE %s /%s\r\nSource-Agent: NTRIP %s/%s\r\n\r\n",
                 mntpnt_pw, mntpnt, ntrip_server_name, "App Version 1.0");

        Serial.printf("Sending credentials:\n%s\n", serverBuffer);
        client.write(serverBuffer, strlen(serverBuffer));

        //Wait for response
        unsigned long timeout = millis();
        while (client.available() == 0)
        {
          if (millis() - timeout > 5000)
          {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
          }
          delay(10);
        }

        //Check reply
        bool connectionSuccess = false;
        char response[512];
        int responseSpot = 0;
        while (client.available())
        {
          response[responseSpot++] = client.read();
          if (strstr(response, "200") > 0) //Look for 'ICY 200 OK'
            connectionSuccess = true;
          if (responseSpot == 512 - 1) break;
        }
        response[responseSpot] = '\0';

        if (connectionSuccess == false)
        {
          Serial.printf("Failed to connect to %s: %s", casterHost, response);
        }
      } //End attempt to connect
      else
      {
        Serial.println("Connection to host failed");
      }
    } //End connected == false

    if (client.connected() == true)
    {
      delay(10);
      while (Serial.available()) Serial.read(); //Flush any endlines or carriage returns

      lastReport_ms = millis();
      lastSentRTCM_ms = millis();

      //This is the main sending loop. We scan for new ublox data but processRTCM() is where the data actually gets sent out.
      while (1)
      {
        if (Serial.available()) break;

        myGPS.checkUblox(); //See if new data is available. Process bytes as they come in.

        //Close socket if we don't have new data for 10s
        //RTK2Go will ban your IP address if you abuse it. See http://www.rtk2go.com/how-to-get-your-ip-banned/
        //So let's not leave the socket open/hanging without data
        if (millis() - lastSentRTCM_ms > maxTimeBeforeHangup_ms)
        {
          Serial.println("RTCM timeout. Disconnecting...");
          client.stop();
          return;
        }

        delay(10);

        //Report some statistics every 250
        if (millis() - lastReport_ms > 250)
        {
          lastReport_ms += 250;
          Serial.printf("\nTotal sent: %d\n", serverBytesSent);
        }
      }
    }

    delay(10);
  }

  Serial.println("User pressed a key");
  Serial.println("Disconnecting...");
  client.stop();

  delay(10);
  while (Serial.available()) Serial.read(); //Flush any endlines or carriage returns
}

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
 message 1004 (Extended L1&L2 GPS RTK Observables) 
 message 1005 (Stationary RTK Reference Station ARP) 
 message 1074 (GPS MSM4) 
 message 1084 (GLONASS MSM4) 
 message 1094 (Galileo MSM4) 
 message 1124 (BeiDou MSM4) 
 message 1230 (GLONASS L1 and L2 Code-Phase Biases)
*/
static void dump_rtcm3_type(const unsigned int type) {
  switch(type){
    case 1004:
      Serial.print("Extended L1&L2 GPS RTK Observables");
      break;
    case 1005:
      Serial.print("Stationary RTK Reference Station ARP");
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
    int ret=0,week;
    unsigned int type=getbitu(buf,24,12);

    if(buf[0]!=0xD3) {
      Serial.print("NOT a RTCM3 message: len=");
      Serial.print(len);
      ret=-1;
    } else {
      Serial.print("RTCM3 message: len=");
      Serial.print(len);
      Serial.print(" type=");
      Serial.print(type);
      Serial.print(" : ");
      dump_rtcm3_type(type);
      
      ret=0;
    }

    return ret;
}

uint8_t buf_for_rtcm3[256 * 4];
uint8_t buf_for_rtcm3_idx = 0;

//This function gets called from the SparkFun u-blox Arduino Library.
//As each RTCM byte comes in you can specify what to do with it
//Useful for passing the RTCM correction data to a radio, Ntrip broadcaster, etc.
void SFE_UBLOX_GPS::processRTCM(uint8_t incoming)
{
  if (client.connected() == true)
  {
    client.write(incoming); //Send this byte to socket
    serverBytesSent++;
    lastSentRTCM_ms = millis();

    if (myGPS.rtcmFrameCounter == 1) {
      if(buf_for_rtcm3_idx!=0){
        Serial.println();
        int ret = dump_rtcm3(buf_for_rtcm3, buf_for_rtcm3_idx);
        if(ret==-1) {
           Serial.println();
        } else {
           Serial.println();
        } 
#ifdef BUF_HEXDUMP
        hexdump(rtcmData, rtcmCount, 32);
#endif
      }
      buf_for_rtcm3_idx=0;
    }
    buf_for_rtcm3[buf_for_rtcm3_idx++]=incoming;

/*
    //Pretty-print the HEX values to Serial
    if (myGPS.rtcmFrameCounter == 1) {
      Serial.println("");
    }
    if ((myGPS.rtcmFrameCounter -1) % 16 == 0) {
      Serial.println("");
      //Serial.print( myGPS.rtcmFrameCounter );
      //Serial.print(" -");
    }
    Serial.print(" ");
    if (incoming < 0x10) Serial.print("0");
    Serial.print(incoming, HEX);
*/
  }
}
