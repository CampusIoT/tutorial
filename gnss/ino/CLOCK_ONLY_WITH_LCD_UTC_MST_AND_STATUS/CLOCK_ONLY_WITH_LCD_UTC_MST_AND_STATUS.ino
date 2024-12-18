//-----------------------------------------------------------------------------------------------
// based on  : clock2 : a GPS-based clock by w8bh.  >>>> COMPLETE <<<<<
//           : geek emeritus added 3 I2C 16x2 character LCD displays
// The time is displayed in local time & UTC, supplied by GPS and / or RTC if GPS is unavailable. 
// Local time automatically tracks daylight saving time for selected time zone.
// Time, GPS, and RTC status messages are displayed on the LCDs
// Author    : Bruce E. Hall, W8BH <bhall66@gmail.com>
// Target    : amended to Arduino UNO
// Platform  : Arduino 1.0.5, because upgrading on Ubuntu and RPi is frustrating at best
// Size      : 14016 bytes (of a 32,256 byte maximum) 
//
// NOTE      : This is Final part of a series on building a GPS-based LCD clock.
//           : Please refer to http://w8bh.net/avr/clock2.pdf for the entire series
//           : geek emeritus removed software interrupt, added SoftwareSerial and LCD via I2C
//           : EnableInterrupt clashes with SoftwareSerial
// Hardware  : Arduino Uno. The UNO has just enough RAM for this clock, if you add to it it becomes unstable 
//             3: 16X2 LCD modules with PCF_8574 I2C modules; UTC, MST and Status displays
//             GPS module
//             DS3231 RTC  at 0x68
// Wiring Uno: UNO "5V",  GPS, RTC, "VCC" from 5VDC bus
//             UNO "GND", GPS, RTC, "GND" from GND  bus
//             UNO "0" to GPS "RX"  // in the final version. 0 & 1 conflict with the USB port
//             UNO "1" to GPS "TX"  // the hardware Serial port is faster than software ports
//             UNO "2" to GPS "PPS" // one of 2 hardware interrupt pins on the UNO: INT0 
//             UNO "3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17" available
//             UNO "SDA" to RTC; LCDs; EEPROM "SDA" DO NOT USE PIN A4 AKA 18 FOR ANY OTHER PURPOSE
//             UNO "SCL" to RTC; LCDs; EEPROM "SCL" DO NOT USE PIN A5 AKA 19 FOR ANY OTHER PURPOSE
// ---------------------------------------------------------------------------------------------------
// GLOBAL DEFINES
#define SYNC_INTERVAL          10                       // time, in seconds, between GPS sync attempts
#define SYNC_TIMEOUT           60                       // time(sec) without GPS input before error
#define RTC_UPDATE_INTERVAL    SECS_PER_DAY             // time(sec) between RTC SetTime events

// INCLUDES
#include <SoftwareSerial.h>         // Multiple Serial https://github.com/PaulStoffregen/SoftwareSerial
#include <TimeLib.h>                // Time functions  https://github.com/PaulStoffregen/Time
#include <TinyGPS.h>                // GPS parsing     https://github.com/mikalhart/TinyGPS
#include <Wire.h>                   // I2C Library     https://github.com/PaulStoffregen/Wire
#include <LiquidCrystal_PCF8574.h>  // I2C for LCDs    https://github.com/arduino/Arduino/tree/master/libraries/LiquidCrystal
#include <DS1307RTC.h>              // DS1307/DS3231   https://github.com/PaulStoffregen/DS1307RTC

//  GLOBAL VARIABLES & OBJECTS
SoftwareSerial GPS(4, 3);                               // temporary FeedGpsParser source 
TinyGPS              gps;                               // GPS parser
time_t displayTime   = 0;                               // time that is currently displayed
time_t syncTime      = 0;                               // time of last GPS or RTC synchronization
time_t lastSetRTC    = 0;                               // time when the RTC was last set
volatile int pps     = 0;                               // GPS one-pulse-per-second flag
time_t dstStart      = 0;                               // start of DST in unix time
time_t dstEnd        = 0;                               // end of DST in unix time
bool gpsLocked       = false;                           // indicates recent sync with GPS
int currentYear      = 0;                               // used in initDST(int yr) to determine DST dates

LiquidCrystal_PCF8574 lcd1(0x3D);  // set the LCD address to 0x3D for a particular 16X2 LCD Module
LiquidCrystal_PCF8574 lcd2(0x3E);  // set the LCD address to 0x3E for a particular 16X2 LCD Module
LiquidCrystal_PCF8574 lcd3(0x3F);  // set the LCD address to 0x3F for a standard   16X2 LCD module

// --------------------------------------------------------------------------------------------------
// SERIAL MONITOR ROUTINES
// These routines print the date/time information to the serial monitor
// Serial monitor must be initialized in setup() before calling

/*void PrintDigit(int d)
{
  if (d<10) Serial.print('0');
  Serial.print(d);
}

void PrintTime(time_t t)                                // display time and date to serial monitor
{
    PrintDigit(month(t));  Serial.print("-");
    PrintDigit(day(t));    Serial.print("-");
    PrintDigit(year(t));   Serial.print(" ");
    PrintDigit(hour(t));   Serial.print(":");
    PrintDigit(minute(t)); Serial.print(":");
    PrintDigit(second(t)); Serial.println(" UTC");
}

void PrintDST()                                         // called by initDST

{
    Serial.print("DST starts at ");
    PrintTime(dstStart);
    Serial.print("DST ends at ");
    PrintTime(dstEnd);
}*/

// --------------------------------------------------------------------------------------------------
// DST & LOCAL TIME ROUTINES
// The following routines support automatic daylight saving time adjustment
// 
// Daylight Saving Time constants:
// Please set as UTC values according to current DST transition times
//
// Select timeZone offset according to your local time zone:

//const int timeZone = -5;                              // -5 (EST) Eastern Standard Time
//const int timeZone = -6;                              // -6 (CST) Central Standard Time 
const int timeZone   = -7;                              // -7 (MST) Mountain Standard Time 
//const int timeZone = -8;                              // -8 (PST) Pacific Standard Time 

#define DST_START_WEEK      2                           // Second Sunday
#define DST_START_MONTH     3                           // in March
#define DST_START_HOUR      7                           // at 2AM EST = 0700 UTC

#define DST_END_WEEK        1                           // First Sunday
#define DST_END_MONTH      11                           // in November
#define DST_END_HOUR        6                           // at 2AM EDT = 0600 UTC

time_t timeChange(int hr, int wk, int mo, int yr)
// returns unix time of DST transition according to hr, wk, mo, and yr 
// Routine first calculates time on first day of month, at specified time
// then adds number of days to first Sunday, then number of additional weeks
{
  tmElements_t tm;                                      // set up time elements struct
  tm.Year   = yr - 1970;                                // need unix year, not calendar year
  tm.Month  = mo;
  tm.Day    = 1;                                        // start on first day of month
  tm.Hour   = hr;                                       // use UTC hour, not local hour
  tm.Minute = 0;
  tm.Second = 0;
  time_t t = makeTime(tm);                              // convert to unix time
  int daysTillSunday = (8 - weekday(t)) % 7;            // how many days until first Sunday?
  t += (daysTillSunday + (wk-1)*7)*SECS_PER_DAY;        // adjust time for additional days
  return t;
}

void initDST(int yr)
// establish start and end times for DST in a given year.  Call at least once a year!
{
  dstStart = timeChange(DST_START_HOUR, DST_START_WEEK, DST_START_MONTH, yr);
  dstEnd   = timeChange(DST_END_HOUR,   DST_END_WEEK,   DST_END_MONTH,   yr);
  //printDST();
}

void UpdateDST()
// sets start/end times for DST
// assumes that current time is set in UTC
{
  int yr = year();                                      // what year is it?
  if (yr != currentYear)                                // a new year started, need new DST info
  {
    initDST(yr);                                        // find DST times for new year
    currentYear = yr;                                   // save current year     
  }
}

bool isDST(time_t t)                                    // returns TRUE if time is in DST window
 {
  return ((t >= dstStart) && (t < dstEnd));
 }

time_t LocalTime()                                      // returns local time, adjusted for DST
 {
  time_t t = now();                                     // get UTC time
  if (isDST(t)) t += SECS_PER_HOUR;                     // add DST correction
  t += (timeZone * SECS_PER_HOUR);                      // add timeZone correction
  return t;
 }

// --------------------------------------------------------------------------------------------------
//  RTC SUPPORT
//  These routines add the ability to get and /or set the time from an attached real-time-clock module
//  such as the DS1307 or the DS3231. The module should be connected to the I2C pins (SDA/SCL).

void PrintRTCstatus()
// send current RTC information to serial monitor 
{
    time_t t = RTC.get();
    if (t) 
    {
     lcd3.setCursor(0,1); lcd3.print("RTC^");
    } 
    else if (RTC.chipPresent()) 
    {  
     lcd3.setCursor(0,1); lcd3.print("RTCv");
    }
    else
    { 
     lcd3.setCursor(0,1); lcd3.print("RTCx");
    } 
}

void SetRTC(time_t t)                                    // called from UpdateRTC(); ManuallySetRTC();
{
  if (RTC.set(t))
  {
   lcd3.setCursor(12,0);
   lcd3.print("t2R^");
  }
  else 
  {
   lcd3.setCursor(12,0);
   lcd3.print("t2Rv");
  }
}

void ManuallySetRTC()
// Use this routine to manually set the RTC to a specific UTC time.
// Since time is automatically set from GPS, this routine is mainly for
// debugging purposes.  Change numeric constants to the time desired.
{
  tmElements_t tm;
  tm.Year   = 2019 - 1970;                              // Year in unix years
  tm.Month  = 1;
  tm.Day    = 22;
  tm.Hour   = 15;
  tm.Minute = 50;
  tm.Second = 30;
  SetRTC(makeTime(tm));                                 // set RTC to desired time
}

void UpdateRTC()                                        // called from SyncWithGPS
// keep the RTC time updated by setting it every (RTC_UPDATE_INTERVAL) seconds
// should only be called when system time is known to be good, such as in a GPS sync event
{
  time_t t = now();                                     // get current time
  if ((t-lastSetRTC) >= RTC_UPDATE_INTERVAL && gpsLocked == true )
  // do not updateRTC with system time; only update from GPS time
  {
    SetRTC(t);                                          // set RTC with current time
    lastSetRTC = t;                                     // remember time of this event
    lcd3.setCursor(8,0); lcd3.print("G2R^"); lcd3.setCursor(8,1);
    int d = day(t);    if (d<10) lcd3.print("0"); lcd3.print(d);
    int h = hour(t);   if (h<10) lcd3.print("0"); lcd3.print(h);  
    int m = minute(t); if (m<10) lcd3.print("0"); lcd3.print(m);  
    int s = second(t); if (s<10) lcd3.print("0"); lcd3.print(s);
  }
}

// --------------------------------------------------------------------------------------------------
// LCD SPECIFIC ROUTINES
// These routines are used to display time and /or date information on the LCD displays
// Assumes the presence of a global object "lcdX" of the type "LiquidCrystal_PCF8574" like this:
//    LiquidCrystal_PCF8574   lcdX(0x38); where 0x38 is the I2C address of the LCD to I2C module

void ShowDateUTC(time_t t)                              // LCD 1 UTC
{
  lcd1.setCursor(0, 0);
  
  int d = day(t); lcd1.print(" ");
  if (d<10) lcd1.print("0"); lcd1.print(d); lcd1.print(" ");
  
  int m = month(t); lcd1.print(monthShortStr(m)); lcd1.print(" ");
  
  int y = year(t)%100; lcd1.print("20"); if (y<10) lcd1.print("0"); lcd1.print(y); 
}

void ShowDateLocal(time_t LocalTime)                    // LCD 2 MST
{
  lcd2.setCursor(0, 0);
  
  int d = day(LocalTime); lcd2.print(" ");
  if (d<10) lcd2.print("0");   lcd2.print(d); lcd2.print(" ");  
  int m = month(LocalTime);    lcd2.print(monthShortStr(m)); lcd2.print(" ");  
  int y = year(LocalTime)%100; lcd2.print("20"); if (y<10) lcd2.print("0"); lcd2.print(y); 
}

void ShowTimeUTC(time_t t)                              // LCD 1 UTC
{
  lcd1.setCursor(0, 1);
  
  int h = hour(t);   if (h<10) lcd1.print("0"); lcd1.print(h); lcd1.print(":");  
  int m = minute(t); if (m<10) lcd1.print("0"); lcd1.print(m); lcd1.print(":");  
  int s = second(t); if (s<10) lcd1.print("0"); lcd1.print(s); lcd1.print(" "); lcd1.print("UTC");
}

 void ShowTimeLocal(time_t LocalTime)                   // LCD 2 MST
{
  lcd2.setCursor(0, 1);
  
  int h = hour(LocalTime);   if (h<10) lcd2.print("0"); lcd2.print(h); lcd2.print(":");  
  int m = minute(LocalTime); if (m<10) lcd2.print("0"); lcd2.print(m); lcd2.print(":");  
  int s = second(LocalTime); if (s<10) lcd2.print("0"); lcd2.print(s); lcd2.print(" ");
  
  if (isDST(LocalTime)) lcd2.print("MDT"); else lcd2.print("MST");  
}
 
void ShowDateTimeUTC(time_t t) // calls ShowDateUTC & ShowTimeUTC which print on LCD 1
 {
  ShowDateUTC(t);
  ShowTimeUTC(t);
 }

void ShowDateTimeLocal(time_t LocalTime) // calls ShowDateLocal & ShowTimeLocal which print on LCD 2
 {
  ShowDateLocal(LocalTime);
  ShowTimeLocal(LocalTime);
 }

// --------------------------------------------------------------------------------------------------
// TIME SYNCHRONIZATION ROUTINES
// These routines will synchronize time with GPS and/or RTC as necessary
// Sync with GPS occur when the 1pps interrupt signal from the GPS goes high.
// GPS synchronization events are attempted every (SYNC_INTERVAL) seconds.
// If a valid GPS signal is not received within (SYNC_TIMEOUT) seconds, the clock will synchronize 
// with RTC instead. The RTC time is updated with GPS data once every 24 hours.

void SyncWithGPS()                                      // called from SyncCheck
{
  int y; byte h,m,s,mon,d; unsigned long age;
  gps.crack_datetime(&y,&mon,&d,&h,&m,&s,NULL,&age);    // get time from GPS
  if (age<1000)                                         // dont use data older than 1 second
  {
   setTime(h,m,s,d,mon,y);                              // copy GPS time to system time
   adjustTime(1);                                       // 1pps signal = start of next second
   syncTime = now();                                    // remember time of this sync
   gpsLocked = true;                                    // set flag that time reflects GPS time
   UpdateRTC();                                         // update internal RTC clock periodically
   lcd3.setCursor(4,1);
   lcd3.print("GPS^");
  }
}

void SyncWithRTC()                                      // called from void setup
  {
   setTime(RTC.get());                                  // set system time from RTC
   syncTime = now();                                    // and remember time of this sync event
   lcd3.setCursor(0,0);                                 // announce System Time set from RTC
   lcd3.print("R2t^");
  }

void SyncCheck()                                        // called from void loop
// Manage synchronization of clock to GPS module
// First, check to see if it is time to synchronize
// Do time synchronization on the 1pps signal
// This call must be made frequently (keep in main loop)
{
  unsigned long timeSinceSync = now()-syncTime;          // how long has it been since last sync?
  
    if (pps && (timeSinceSync >= SYNC_INTERVAL))         // is it time to sync with GPS yet?
     {
     SyncWithGPS();                                      // yes, so attempt it.
     pps = 0;                                            // reset 1-pulse-per-second flag, regardless
     lcd3.setCursor(4,0); lcd3.print("G2t^");            // announce System Time set to GPS
     lcd3.setCursor(0,0); lcd3.print("R2tv");            // clear System Time set to RTC
     }
     
  if (timeSinceSync >= SYNC_TIMEOUT)                     // GPS sync has failed
     {
      gpsLocked = false;                                 // flag that clock is no longer in GPS sync
      lcd3.setCursor(4,1); lcd3.print("GPSv");           // announce GPS not locked
      lcd3.setCursor(4,0); lcd3.print("G2tv");           // clear G2t^
      SyncWithRTC();                                     // sync with RTC instead
     }
}

// --------------------------------------------------------------------------------------------------
// MAIN PROGRAM

void setup() 
{
  {
  lcd1.begin(16, 2); lcd1.clear(); lcd1.setBacklight(255); lcd1.setCursor(0, 0); // initialize UTC LCD display
  lcd2.begin(16, 2); lcd2.clear(); lcd2.setBacklight(255); lcd2.setCursor(0, 0); // initialize LocalTime LCD display
  lcd3.begin(16, 2); lcd3.clear(); lcd3.setBacklight(255); lcd3.setCursor(0, 0); // initialize Status LCD display
  }

  {
  Serial.begin(115200);                                 // set serial monitor rate to 115200 bps
  GPS.begin(9600);                                      // gps setup
  attachInterrupt( INT0, isr, RISING);                  // enable GPS 1pps hardware interrupt input on pin 2
  //ManuallySetRTC();
  PrintRTCstatus();                                     // show RTC diagnostics on the Serial Monitor
  SyncWithRTC();                                        // start clock with RTC data
  //initDST(2019);                                      // run once a year, before March
  }
}

void loop() 
{
  FeedGpsParser();                                      // decode incoming GPS data
  SyncCheck();                                          // synchronize to GPS or RTC
  UpdateDisplay();                                      // if time has changed, display it
}

void isr()                                              // INTERRUPT SERVICE REQUEST
{
  pps = 1;                                              // Flag the 1pps input signal
}

void FeedGpsParser() // feed currently available data from GPS module into tinyGPS parser
{
  while (GPS.available())                               // look for data from GPS module
  {
     char c = GPS.read();                               // read in all available chars   
     gps.encode(c);                                     // and feed chars to GPS parser
  }

}

void UpdateDisplay()                                    // called from void loop
//  Call this from the main loop
//  Updates display if time has changed
{
  time_t t = now();                                     // get the current time
  if (t != displayTime)                                 // has time changed?
  {
      UpdateDST();                                      // check DST status
      ShowDateTimeUTC(t);                               // Display the current UTC time
      ShowDateTimeLocal(LocalTime());                   // Display the current local time
      displayTime = t;                                  // save current display value
      //PrintTime(t);                                   // for debugging only
  }

}
