// https://files.seeedstudio.com/products/317990687/res/LoRa-E5%20AT%20Command%20Specification_V1.0%20.pdf

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

//#define DHTPIN 0 // what pin we're connected to
 
#ifdef DHTTYPE
#include "DHT.h"
// Uncomment whatever type you're using!
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);
#endif

#ifdef U8X8_SSD1306
#include <U8x8lib.h>
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/U8X8_PIN_NONE);
// U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // OLEDs without Reset of the Display
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
#ifdef U8X8_SSD1306
        u8x8.setCursor(2, 4);
        u8x8.print("led :");
#endif
        led = !!data;
#ifdef U8X8_SSD1306
        u8x8.print(led);
#endif
        if (led)
        {
            digitalWrite(LED_BUILTIN, LOW);
        }
        else
        {
            digitalWrite(LED_BUILTIN, HIGH);
        }
    }

 
    p_start = strstr(p_msg, "RSSI");
    if (p_start && (1 == sscanf(p_start, "RSSI %d,", &rssi)))
    {
        Serial.print("RSSI:");
        Serial.print(rssi);
#ifdef U8X8_SSD1306
        u8x8.setCursor(0, 6);
        u8x8.print("                ");
        u8x8.setCursor(2, 6);
        u8x8.print("rssi:");
        u8x8.print(rssi);
#endif
    }
    p_start = strstr(p_msg, "SNR");
    if (p_start && (1 == sscanf(p_start, "SNR %d", &snr)))
    {
        Serial.print(" LSNR:");
        Serial.println(snr);
#ifdef U8X8_SSD1306
        u8x8.setCursor(0, 7);
        u8x8.print("                ");
        u8x8.setCursor(2, 7);
        u8x8.print("snr :");
        u8x8.print(snr);
#endif
    }
}
 
void setup(void)
{
#if defined(SEEED_WIO_TERMINAL)
    delay(5000);
#endif
    Serial.println("===================");
    Serial.println("LoRaWAN TH Endpoint");
    Serial.println("===================");

#ifdef U8X8_SSD1306
    u8x8.begin();
    u8x8.setFlipMode(1);
    u8x8.setFont(u8x8_font_chroma48medium8_r);
#endif
 
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
 
    SerialE5.begin(9600);
    Serial.print("E5 LORAWAN TEST\r\n");
#ifdef U8X8_SSD1306
    u8x8.setCursor(0, 0);
#endif
 
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
#ifdef U8X8_SSD1306
        u8x8.setCursor(5, 0);
        u8x8.print("LoRaWAN");
#endif
        is_join = true;
    }
    else
    {
        is_exist = false;
        Serial.print("No E5 module found.\r\n");
#ifdef U8X8_SSD1306
        u8x8.setCursor(0, 1);
        u8x8.print("unfound E5 !");
#endif
    }
 
#ifdef DHTPIN
    dht.begin();
#endif
 
#ifdef U8X8_SSD1306
    u8x8.setCursor(0, 2);
    u8x8.setCursor(2, 2);
    u8x8.print("temp:");
 
    u8x8.setCursor(2, 3);
    u8x8.print("humi:");
 
    u8x8.setCursor(2, 4);
    u8x8.print("led :");
    u8x8.print(led);
#endif

}
 
void loop(void)
{
  
    float temp = 0;
    float humi = 0;
 
#ifdef DHTPIN
    temp = dht.readTemperature();
    humi = dht.readHumidity();
#endif
 
    Serial.print("Humidity: ");
    Serial.print(humi);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" *C");
 
#ifdef U8X8_SSD1306
    u8x8.setCursor(0, 2);
    u8x8.print("      ");
    u8x8.setCursor(2, 2);
    u8x8.print("temp:");
    u8x8.print(temp);
    u8x8.setCursor(2, 3);
    u8x8.print("humi:");
    u8x8.print(humi);
#endif 
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
            char cmd[128];
#if CONFIRMED == 1
            sprintf(cmd, "AT+CMSGHEX=\"%04X%04X\"\r\n", (int)temp, (int)humi);
#else
            sprintf(cmd, "AT+MSGHEX=\"%04X%04X\"\r\n", (int)temp, (int)humi);
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
            delay(SEND_PERIOD);
        }
    }
    else
    {
        delay(1000);
    }
}
