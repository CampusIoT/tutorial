#ifndef GNSS_CONFIG_H_
#define GNSS_CONFIG_H_

// Some GNSS module configurations https://github.com/CampusIoT/orbimote/blob/master/gnss_modules.md
#ifndef GNSS_XA1110
#define GNSS_XA1110      1
#endif

#if GNSS_XA1110 == 1
// XA1110 https://learn.sparkfun.com/tutorials/sparkfun-gps-breakout---xa1110-qwiic-hookup-guide/all
#define GNSS_BAUDRATE 9600;

#elif GROVE_GNSS_SIM28 == 1

#define GNSS_BAUDRATE 9600;

#elif GNSS_ZED_F9P == 1

#define GNSS_BAUDRATE 38400;

#else

#error GNSS Module is not defined

#endif










#endif // GNSS_CONFIG_H_

