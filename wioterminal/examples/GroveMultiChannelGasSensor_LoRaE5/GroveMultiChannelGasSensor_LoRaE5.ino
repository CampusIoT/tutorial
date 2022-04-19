#include <TFT_eSPI.h>
#include <Multichannel_Gas_GMXXX.h>
#include <Wire.h>
GAS_GMXXX<TwoWire> gas;
 
TFT_eSPI tft; 
// Stock font and GFXFF reference handle
TFT_eSprite spr = TFT_eSprite(&tft);  // Sprite 

#define DEBUG_AT 1
#define SEND_PERIOD 60000
#define REJOIN_PERIOD 60000
#define CONFIRMED 1

#include <Arduino.h>

#ifndef LED_BUILTIN
#define LED_BUILTIN 8
#endif

#if defined(SEEED_WIO_TERMINAL)
// With Battery Chassis (Grove UART connector at the left side of the USB-C connector)
#define SerialE5 Serial1
#else
// The serial connection to the LoRa E5 Modem
#include <SoftwareSerial.h>
static const int RXPin = 16, TXPin = 17;
SoftwareSerial SerialE5(RXPin, TXPin);
#endif

static char recv_buf[512];
static bool is_exist = false;
static bool is_join = false;
static int led = 0;
 
static int at_send_check_response(char *p_ack, int timeout_ms, char *p_cmd, ...)
{
    int ch;
    int num = 0;
    int index = 0;
    int startMillis = 0;
    va_list args;
    memset(recv_buf, 0, sizeof(recv_buf));
    va_start(args, p_cmd);
    SerialE5.printf(p_cmd, args);
#if DEBUG_AT == 1                
    Serial.printf(p_cmd, args);
#endif
    va_end(args);
    delay(200);
    startMillis = millis();
 
    if (p_ack == NULL)
    {
        return 0;
    }
 
    do
    {
        while (SerialE5.available() > 0)
        {
            ch = SerialE5.read();
            recv_buf[index++] = ch;
#if DEBUG_AT == 1            
            Serial.print((char)ch);
#endif
            delay(2);
        }
 
        if (strstr(recv_buf, p_ack) != NULL)
        {
            return 1;
        }
 
    } while (millis() - startMillis < timeout_ms);
    return 0;
}
 
static void recv_prase(char *p_msg)
{
    if (p_msg == NULL)
    {
        return;
    }
    char *p_start = NULL;
    int data = 0;
    int rssi = 0;
    int snr = 0;
 
    p_start = strstr(p_msg, "RX");
    if (p_start && (1 == sscanf(p_start, "RX: \"%d\"\r\n", &data)))
    {
        Serial.println(data);
    }
 
    p_start = strstr(p_msg, "RSSI");
    if (p_start && (1 == sscanf(p_start, "RSSI %d,", &rssi)))
    {
        Serial.print("RSSI:");
        Serial.print(rssi);
    }
    p_start = strstr(p_msg, "SNR");
    if (p_start && (1 == sscanf(p_start, "SNR %d", &snr)))
    {
        Serial.print(" LSNR:");
        Serial.println(snr);
    }
}
 
void setupE5(void)
{
#if defined(SEEED_WIO_TERMINAL)
    delay(5000);
#endif
    Serial.println("===================");
    Serial.println("LoRaWAN TH Endpoint");
    Serial.println("===================");
 
    Serial.begin(115200);
 
    SerialE5.begin(9600);
    Serial.print("E5 LORAWAN TEST\r\n");
 
    if (at_send_check_response("+AT: OK", 100, "AT\r\n"))
    {
        is_exist = true;
        at_send_check_response("+LOG: ERROR", 1000, "AT+LOG=ERROR\r\n");
        // AT+LOG=DEBUG can overflow the buffer !!!!
        //at_send_check_response("+LOG: DEBUG", 1000, "AT+LOG=DEBUG\r\n");
        at_send_check_response("+ID: AppEui", 1000, "AT+ID\r\n");
        at_send_check_response("+MODE: LWOTAA", 1000, "AT+MODE=LWOTAA\r\n");
        at_send_check_response("+DR: EU868", 1000, "AT+DR=EU868\r\n");
        at_send_check_response("+DR: DR5", 1000, "AT+DR=5\r\n");
        at_send_check_response("+CH: NUM", 1000, "AT+CH=NUM,0-2\r\n");
        at_send_check_response("+KEY: APPKEY", 1000, "AT+KEY=APPKEY,\"2B7E151628AED2A6ABF7158809CF4F3C\"\r\n");
        at_send_check_response("+CLASS: A", 1000, "AT+CLASS=A\r\n");
        at_send_check_response("+PORT: 8", 1000, "AT+PORT=8\r\n");
        at_send_check_response("+ADR: ON", 1000, "AT+ADR=ON\r\n");
        delay(200);
        is_join = true;
    }
    else
    {
        is_exist = false;
        Serial.print("No E5 module found.\r\n");
    } 
}

static int CO;
static int C2H5CH;
static int NO2;
static int VOC;

static int lastMilli = 0;

void loopE5(void)
{
    if (is_exist)
    {
        int ret = 0;
        if (is_join)
        {
 
            ret = at_send_check_response("+JOIN: Network joined", 12000, "AT+JOIN\r\n");
            if (ret)
            {
                is_join = false;
                Serial.print("Network joined!\r\n\r\n");
            }
            else
            {
                at_send_check_response("+ID: AppEui", 1000, "AT+ID\r\n");
                Serial.print("Join failed!\r\n\r\n");
                delay(REJOIN_PERIOD);
            }
        }
        else
        {
            // TODO Send if button pushed
            
            int m = millis();
            if(m - lastMilli < SEND_PERIOD) {
              return;
            }
            lastMilli = m;
          
            char cmd[128];

            Serial.print("CO: ");
            Serial.print(CO);
            Serial.print(" ppm\t");
            Serial.print("C2H5CH: ");
            Serial.print(C2H5CH);
            Serial.print(" ppm\t");
            Serial.print("NO2: ");
            Serial.print(NO2);
            Serial.print(" ppm\t");
            Serial.print("VOC: ");
            Serial.print(VOC);
            Serial.println(" ppm");
            
#if CONFIRMED == 1
            sprintf(cmd, "AT+CMSGHEX=\"%04X%04X%04X%04X\"\r\n", (int)CO, (int)C2H5CH, (int)NO2, (int)VOC);
#else
            sprintf(cmd, "AT+MSGHEX=\"%04X%04X%04X%04X\"\r\n", (int)CO, (int)C2H5CH, (int)NO2, (int)VOC);
#endif
            ret = at_send_check_response("Done", 5000, cmd);
            if (ret)
            {
/*AT+CMSGHEX="00000000"
+CMSGHEX: Start
+CMSGHEX: Wait ACK
+CMSGHEX: FPENDING
+CMSGHEX: ACK Received
+CMSGHEX: RXWIN1, RSSI -82, SNR 14.0
+CMSGHEX: Done
*/            
                recv_prase(recv_buf);
                Serial.print("Send done!\r\n\r\n");
            }
            else
            {
/* TODO process when 
AT+CMSGHEX="00000000"
+CMSGHEX: Start
+CMSGHEX: Wait ACK
 */            
                Serial.print("Send failed!\r\n\r\n");
            }
            //delay(SEND_PERIOD);
        }
    }
    else
    {
        delay(1000);
    }
}


void setupGas() {
  // put your setup code here, to run once:
  tft.begin();
  tft.setRotation(3);
  spr.createSprite(tft.width(),tft.height()); 
  gas.begin(Wire, 0x08); // use the hardware I2C
}

void loopGas() {
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
  NO2 = val;
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
  C2H5CH = val;
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
  VOC = val;
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
  CO = val;
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


void setup() {
  setupGas();
  setupE5();
}

void loop() {
  loopGas();
  loopE5();
}
