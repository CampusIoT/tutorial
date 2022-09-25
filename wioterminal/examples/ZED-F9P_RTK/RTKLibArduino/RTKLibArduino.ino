

#include "rtklib.h"

void setup() {
  
  Serial.begin(115200); // You may need to increase this for high navigation rates!
  while (!Serial)
    ; //Wait for user to open terminal
  Serial.println(F("RTKLib for Arduino Example"));

}

/* Example of RTCM3 Type Message 1004: extended L1&L2 gps rtk observables ----------------------*/
/* Example of RTCM3 Type Message 1005: stationary rtk reference station arp --------------------*/
/* Example of RTCM3 Type Message 1006: stationary rtk reference station arp with height --------*/
/* Example of RTCM3 Type Message 1007: antenna descriptor --------------------------------------*/
/* Example of RTCM3 Type Message 1008: antenna descriptor & serial number ----------------------*/
/* Example of RTCM3 Type Message 1009: L1-only glonass rtk observables -------------------------*/
/* Example of RTCM3 Type Message 1010: extended L1-only glonass rtk observables ----------------*/
/* Example of RTCM3 Type Message 1011: L1&L2 glonass rtk observables ---------------------------*/
/* Example of RTCM3 Type Message 1012: extended L1&L2 glonass rtk observables ------------------*/
/* Example of RTCM3 Type Message 1013: system parameters ---------------------------------------*/
/* Example of RTCM3 Type Message 1019: gps ephemerides -----------------------------------------*/
/* Example of RTCM3 Type Message 1020: glonass ephemerides -------------------------------------*/
/* Example of RTCM3 Type Message 1021: helmert/abridged molodenski -----------------------------*/
/* Example of RTCM3 Type Message 1022: moledenski-badekas transfromation -----------------------*/
/* Example of RTCM3 Type Message 1023: residual, ellipoidal grid representation ----------------*/
/* Example of RTCM3 Type Message 1024: residual, plane grid representation ---------------------*/
/* Example of RTCM3 Type Message 1025: projection (types except LCC2SP,OM) ---------------------*/
/* Example of RTCM3 Type Message 1026: projection (LCC2SP - lambert conic conformal (2sp)) -----*/
/* Example of RTCM3 Type Message 1027: projection (type OM - oblique mercator) -----------------*/
/* Example of RTCM3 Type Message 1030: network rtk residual ------------------------------------*/
/* Example of RTCM3 Type Message 1031: glonass network rtk residual ----------------------------*/
/* Example of RTCM3 Type Message 1032: physical reference station position information ---------*/
/* Example of RTCM3 Type Message 1033: receiver and antenna descriptor -------------------------*/
/* Example of RTCM3 Type Message 1034: gps network fkp gradient --------------------------------*/
/* Example of RTCM3 Type Message 1035: glonass network fkp gradient ----------------------------*/
/* Example of RTCM3 Type Message 1037: glonass network rtk ionospheric correction difference ---*/
/* Example of RTCM3 Type Message 1038: glonass network rtk geometic correction difference ------*/
/* Example of RTCM3 Type Message 1039: glonass network rtk combined correction difference ------*/
/* Example of RTCM3 Type Message 1042/63: beidou ephemerides -----------------------------------*/
/* Example of RTCM3 Type Message 1044: qzss ephemerides (ref [15]) -----------------------------*/
/* Example of RTCM3 Type Message 1045: galileo F/NAV satellite ephemerides (ref [15]) ----------*/
/* Example of RTCM3 Type Message 1046: galileo I/NAV satellite ephemerides (ref [17]) ----------*/


void loop() {
  // put your main code here, to run repeatedly:

}
