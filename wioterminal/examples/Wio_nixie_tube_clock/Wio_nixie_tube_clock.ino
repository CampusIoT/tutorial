// Woi Terminal nixie tube clock : 2020.05.25 macsbug
//  https://macsbug.wordpress.com/2020/05/25/wio-nixie-tube-clock/
// M5Stack nixie tube clock      : 2019.06.16 macsbug
//  https://macsbug.wordpress.com/2019/06/16/m5stack-nixie-tube-clock/
// M5StickC Nixie tube Clock     : 2019.06.06 macsbug
//  https://macsbug.wordpress.com/2019/06/06/m5stickc-nixie-tube-clock/
// RTC DS3231 : https://wiki.52pi.com/index.php/Raspberry_Pi_Super_Capacitor_RTC(English)
// RTClib : https://www.arduinolibraries.info/libraries/rt-clib
// mode controll : 5 way switch
// mode 1 : yyyy_mmdd_hhmmss
// mode 2 : mmdd_hh_mmss
// mode 3 : mmdd_ss_hhmm
// rtc    : DS3231, SDA1 = 2, SCL1= 3;
#include <SPI.h>
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
#include <Wire.h>
#include "RTClib.h"
RTC_DS3231 rtc;
#include "vfd_18x34.c"   // font 18px34
#include "vfd_35x67.c"   // font 35x67
#include "vfd_70x134.c"  // font 70px134
#include "apple_35x41.c" // icon 35px41 
uint32_t targetTime = 0; // for next 1 second timeout
const uint8_t*n[] = { // vfd font 18x34
  vfd_18x34_0,vfd_18x34_1,vfd_18x34_2,vfd_18x34_3,vfd_18x34_4,
  vfd_18x34_5,vfd_18x34_6,vfd_18x34_7,vfd_18x34_8,vfd_18x34_9 };
const uint8_t*m[] = { // vfd font 35x67
  vfd_35x67_0,vfd_35x67_1,vfd_35x67_2,vfd_35x67_3,vfd_35x67_4,
  vfd_35x67_5,vfd_35x67_6,vfd_35x67_7,vfd_35x67_8,vfd_35x67_9,
  vfd_35x67_q,vfd_35x67_n };
const uint8_t*b[] = { // vfd font 70x134
  vfd_70x134_0,vfd_70x134_1,vfd_70x134_2,vfd_70x134_3,vfd_70x134_4,
  vfd_70x134_5,vfd_70x134_6,vfd_70x134_7,vfd_70x134_8,vfd_70x134_9,
  vfd_70x134_q,vfd_70x134_n };
const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
uint16_t yy;
uint8_t mn, dd, hh, mm, ss;
uint8_t md = 2; // mode 1, 2, 3
 
void setup() { 
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  pinMode(WIO_5S_PRESS, INPUT_PULLUP);
  Wire.begin(SDA1,SCL1); delay(10);
  rtc.begin(); 
  rtc.adjust(DateTime(__DATE__, __TIME__)); // Set the PC time
  // esp_timer_init();
  // wifi_setup();
  rtc_setup();  // Read the value of RTC
}

void loop() {
  // if (targetTime < esp_timer_get_time()/1000 ){
  DateTime now = rtc.now();
  yy = now.year();
  mn = now.month();
  dd = now.day();
  hh = now.hour();
  mm = now.minute();
  ss = now.second();
  if(digitalRead(WIO_5S_PRESS) == LOW){         // mode change
   if (md == 3){md = 1;tft.fillRect(1,1,317,236,TFT_BLACK);return;}
   if (md == 2){md = 3;tft.fillRect(1,1,317,236,TFT_BLACK);return;}
   if (md == 1){md = 2;tft.fillRect(1,1,317,236,TFT_BLACK);return;}
  }
  if ( md == 3 ){ hhmm();}             // yyyy,mm,dd,ss,hh,mm
  if ( md == 2 ){ yyyy_mmdd_hhmmss();} // yyyy,mm,dd,hh,mm,ss
  if ( md == 1 ){ mmss();}             // mm,ss
  // periodic_ntp(); 
  delay(500);
}

void rtc_setup(){
  DateTime now = rtc.now(); // time geting from RTC
  if (now.year() == 2165){  // rtc check
    tft.setCursor(20,200);tft.setTextColor(TFT_RED);
    tft.print("RTC not installed");delay(2000);
    tft.fillRect(1, 1, 317, 236, TFT_BLACK);
    }else{
    yy = now.year(); mn = now.month(); dd = now.day();
    hh = now.hour(); mm = now.minute(); ss = now.second();
    //Serial.printf("%d %d %d %d %d %d\n",yy,mn,dd,hh,mm,ss);
    tft.setCursor(20,200);tft.setTextColor(TFT_BLUE);
    tft.print("SET UP RTC");delay(2000);
    tft.fillRect(1, 1, 317, 236, TFT_BLACK);
  }
}

void yyyy_mmdd_hhmmss(){
  int y1 = (yy / 1000) % 10; int y2 = (yy / 100) % 10;
  int y3 = (yy /   10) % 10; int y4 = yy % 10;
  int ma = (mn /   10) % 10; int mb = mn % 10;
  int d1 = (dd /   10) % 10; int d2 = dd % 10;
  int h1 = (hh /   10) % 10; int h2 = hh % 10;
  int m1 = (mm /   10) % 10; int m2 = mm % 10;
  int s1 = (ss /   10) % 10; int s2 = ss % 10;

  //int p0 = 8; int x0 = 40; int t0 = 22; // icon
  //tft.pushImage( p0 + 0*x0, t0, 35,41, (uint16_t *)apple_35x41);

  int p1 = 80; int px1 = 40; int py1 = 5;
  tft.pushImage( p1 + 0*px1, py1, 35,67, (uint16_t *)m[y1]); 
  tft.pushImage( p1 + 1*px1, py1, 35,67, (uint16_t *)m[y2]);
  tft.pushImage( p1 + 2*px1, py1, 35,67, (uint16_t *)m[y3]);
  tft.pushImage( p1 + 3*px1, py1, 35,67, (uint16_t *)m[y4]);
  
  int p2 = 80; int px2 = 40; int py2 = 76;
  tft.pushImage( p2 + 0*px2, py2, 35,67, (uint16_t *)m[ma]);
  tft.pushImage( p2 + 1*px2, py2, 35,67, (uint16_t *)m[mb]);
  //tft.drawPixel(118,13, ORANGE); tft.drawPixel(119,23,ORANGE);
  tft.pushImage( p2 + 2*px2, py2, 35,67, (uint16_t *)m[d1]);
  tft.pushImage( p2 + 3*px2, py2, 35,67, (uint16_t *)m[d2]);

  int p3 = 2; int px3 = 40; int py3 = 150;
  tft.pushImage( p3 + 0*px3, py3, 35,67, (uint16_t *)m[h1]);
  tft.pushImage( p3 + 1*px3, py3, 35,67, (uint16_t *)m[h2]);
  tft.pushImage( p3 + 2*px3, py3, 35,67, (uint16_t *)m[10]);
  tft.pushImage( p3 + 3*px3, py3, 35,67, (uint16_t *)m[m1]);
  tft.pushImage( p3 + 4*px3, py3, 35,67, (uint16_t *)m[m2]);
  tft.pushImage( p3 + 5*px3, py3, 35,67, (uint16_t *)m[10]);
  tft.pushImage( p3 + 6*px3, py3, 35,67, (uint16_t *)m[s1]);
  tft.pushImage( p3 + 7*px3, py3, 35,67, (uint16_t *)m[s2]);
  
  if ( s1 == 0 && s2 == 0 ){ fade1();}
}

void mmss(){
  int ma = (mn / 10) % 10; int mb = mn % 10;
  int d1 = (dd / 10) % 10; int d2 = dd % 10;
  int h1 = (hh / 10) % 10; int h2 = hh % 10;
  int m1 = (mm / 10) % 10; int m2 = mm % 10;
  int s1 = (ss / 10) % 10; int s2 = ss % 10;

  int p0 = 8; int x0 = 40; int t0 = 22; // icon
  tft.pushImage( p0 + 0*x0, t0, 35,41, (uint16_t *)apple_35x41);

  int p2 = 65; int px2 = 40; int py2 = 10;
  tft.pushImage( p2 + 0*px2, py2, 35,67, (uint16_t *)m[ma]);
  tft.pushImage( p2 + 1*px2, py2, 35,67, (uint16_t *)m[mb]);
  //tft.drawPixel(118,13, ORANGE); tft.drawPixel(119,23,ORANGE);
  tft.pushImage( p2 + 2*px2, py2, 35,67, (uint16_t *)m[d1]);
  tft.pushImage( p2 + 3*px2, py2, 35,67, (uint16_t *)m[d2]);
  
  int p3 = 240; int px3 = 40; int py3 = 10;
  tft.pushImage( p3 + 0*px3, py3, 35,67, (uint16_t *)m[h1]);
  tft.pushImage( p3 + 1*px3, py3, 35,67, (uint16_t *)m[h2]);
  
  int p4 = 2; int px4 = 80; int py4 = 100;
  tft.pushImage( p4 + 0*px4   , py4, 70,134, (uint16_t *)b[m1]);
  tft.pushImage( p4 + 1*px4 -4, py4, 70,134, (uint16_t *)b[m2]);
  //tft.drawPixel(155,150, ORANGE); tft.drawPixel(155,190,ORANGE);
  tft.fillCircle(156,151,3,TFT_ORANGE);tft.fillCircle(156,191,3,TFT_ORANGE);
  tft.fillCircle(156,151,1,TFT_YELLOW);tft.fillCircle(156,191,1,TFT_YELLOW);
  tft.pushImage( p4 + 2*px4 +4, py4, 70,134, (uint16_t *)b[s1]);
  tft.pushImage( p4 + 3*px4   , py4, 70,134, (uint16_t *)b[s2]);

  if ( m1 == 0 && m2 == 0 ){ fade2();}
}

void hhmm(){
  int ma = (mn / 10) % 10; int mb = mn % 10;
  int d1 = (dd / 10) % 10; int d2 = dd % 10;
  int h1 = (hh / 10) % 10; int h2 = hh % 10;
  int m1 = (mm / 10) % 10; int m2 = mm % 10;
  int s1 = (ss / 10) % 10; int s2 = ss % 10;

  //int p0 = 8; int x0 = 40; int t0 = 22; // icon
  //tft.pushImage( p0 + 0*x0, t0, 35,41, (uint16_t *)apple_35x41);

  int p2 = 65; int px2 = 40; int py2 = 10;
  tft.pushImage( p2 + 0*px2, py2, 35,67, (uint16_t *)m[ma]);
  tft.pushImage( p2 + 1*px2, py2, 35,67, (uint16_t *)m[mb]);
  //tft.drawPixel(118,13, ORANGE); tft.drawPixel(119,23,ORANGE);
  tft.pushImage( p2 + 2*px2, py2, 35,67, (uint16_t *)m[d1]);
  tft.pushImage( p2 + 3*px2, py2, 35,67, (uint16_t *)m[d2]);
  
  int p3 = 240; int px3 = 40; int py3 = 10;
  tft.pushImage( p3 + 0*px3, py3, 35,67, (uint16_t *)m[s1]);
  tft.pushImage( p3 + 1*px3, py3, 35,67, (uint16_t *)m[s2]);
  
  int p4 = 2; int px4 = 80; int py4 = 100;
  tft.pushImage( p4 + 0*px4   , py4, 70,134, (uint16_t *)b[h1]);
  tft.pushImage( p4 + 1*px4 -4, py4, 70,134, (uint16_t *)b[h2]);
  //tft.drawPixel( 155,150, ORANGE); tft.drawPixel(155,190,ORANGE);
  tft.fillCircle(156,151,3,TFT_ORANGE);tft.fillCircle(156,191,3,TFT_ORANGE);
  tft.fillCircle(156,151,1,TFT_YELLOW);tft.fillCircle(156,191,1,TFT_YELLOW);
  tft.pushImage( p4 + 2*px4 +4, py4, 70,134, (uint16_t *)b[m1]);
  tft.pushImage( p4 + 3*px4   , py4, 70,134, (uint16_t *)b[m2]);

  if ( h1 == 0 && h2 == 0 ){ fade2();}
}

void fade1(){
  int p3 = 2; int px3 = 40; int py3 = 150;
  for ( int i = 0; i < 2; i++ ){
  tft.pushImage( p3 + 2*px3, py3, 35,67, (uint16_t *)m[11]);
  tft.pushImage( p3 + 5*px3, py3, 35,67, (uint16_t *)m[11]);
  delay(25);
  tft.pushImage( p3 + 2*px3, py3, 35,67, (uint16_t *)m[10]);
  tft.pushImage( p3 + 5*px3, py3, 35,67, (uint16_t *)m[10]);
  delay(25);
  }
}

void fade2(){
  int p3 = 2; int px3 = 40; int py3 = 150;
  for ( int i = 0; i < 2; i++ ){
  tft.fillCircle(156,151,3,TFT_BLACK);tft.fillCircle(156,191,3,TFT_BLACK);
  delay(25);
  tft.fillCircle(156,151,3,TFT_ORANGE);tft.fillCircle(156,191,3,TFT_ORANGE);
  delay(25);
  }
}
