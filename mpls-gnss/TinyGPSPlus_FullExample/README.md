# TinyGPS++ :: Full Example

The purpose of this example is the test of the communication of the ESP32 Wroom with a GPS module using the NMEA 0183 protocol.

This example requires the importation of two libraries into the Arduino IDE
* https://codeload.github.com/plerup/espsoftwareserial/zip/refs/heads/main
* https://codeload.github.com/mikalhart/TinyGPSPlus/zip/refs/heads/master

## Wiring

Warning: The default baudrate for [Grove-GPS](https://wiki.seeedstudio.com/Grove-GPS/) SIM28 is 9600. Check baudrates for [other common GNSS modules](https://github.com/CampusIoT/orbimote/blob/master/gnss_modules.md).

### Wiring for Grove GPS
The example has been tested with the [Grove-GPS](https://wiki.seeedstudio.com/Grove-GPS/) plugged into the UART Grove connector of the TinyGS 2G4 station.

This module is connected to the UART2 with the following wiring:

	White	<->	pin 16	(Rx ESP / Tx Module)
	Yellow 	<->	pin 17  (Tx ESP / Rx Module)
	Red 	<->	3.3V
	Black	<->	GND


### Wiring for XA1110 Mikrobus on Mikrobus 1

The example has been tested with the [SparkFun GPS Breakout - XA1110](https://learn.sparkfun.com/tutorials/sparkfun-gps-breakout---xa1110-qwiic-hookup-guide) plugged into the Mikrobus 1 slot of the TinyGS 2G4 station.

This module is connected to the UART2 with the following wiring:

## Build

Set the baudrate of the module

```c
...
static const uint32_t GPSBaud = 9600;
...
```

Set the coordinates of your POI (Point of Interest)

```c
...
static const double POI_LAT = 45.19262400425433, POI_LON = 5.759966075632675;
...
```

> For debugging baudrate, you can display the raw NMEA sentences by setting `DISPLAY_NMEA0183_SENTENCES` to `1` into the sketch.

```c
...
#define DISPLAY_NMEA0183_SENTENCES    1
...
```

> For removing the GNSS data baudrate, set `DISPLAY_GNSS_LINES` to `0` into the sketch.

```c
...
#define DISPLAY_GNSS_LINES    0
...
```

## Flash and Run

Configure the board `ESP32 Dev Module` and the port in `Tools`.

Compile the sketch `Sketch > Verify/Compile`

Upload the sketch `Sketch > Upload` on the board

Open the serial monitor `Tools > Serial monitor`


with `DISPLAY_NMEA0183_SENTENCES=1`
```
FullExample.ino
An extensive example of many interesting TinyGPS++ features
Testing TinyGPS++ library v. 1.0.2
by Mikal Hart

$PGACK,EPE,H=24.094191,V=17.598621*39
$GNGGA,173207.000,4510.940888,N,00544.128851,E,1,5,2.81,202.417,M,48.532,M,,*41
$GPGSA,A,3,08,02,04,,,,,,,,,,2.98,2.81,1.00*05
$GLGSA,A,3,84,71,,,,,,,,,,,2.98,2.81,1.00*1D
$GPGSV,3,1,11,01,80,008,18,03,66,261,,02,61,104,33,17,35,308,17*78
$GPGSV,3,2,11,08,24,172,23,32,24,045,,04,17,186,30,22,16,291,*76
$GPGSV,3,3,11,14,13,270,,28,10,086,16,31,04,111,*4E
$GLGSV,2,1,08,85,78,042,,70,75,183,,84,33,120,28,69,33,035,*69
$GLGSV,2,2,08,86,29,318,,71,26,204,33,77,07,332,,76,03,290,*6A
$GNRMC,173207.000,A,4510.940888,N,00544.128851,E,0.58,146.63,070425,,,A*78
$GNVTG,146.63,T,,M,0.58,N,1.07,K,A*2E
$PGACK,EPE,H=24.028019,V=17.599386*36
$GNGGA,173208.000,4510.940632,N,00544.129264,E,1,5,2.81,202.387,M,48.532,M,,*42
$GPGSA,A,3,08,02,04,,,,,,,,,,2.98,2.81,1.00*05
$GLGSA,A,3,84,71,,,,,,,,,,,2.98,2.81,1.00*1D
$GNRMC,173208.000,A,4510.940632,N,00544.129264,E,0.78,146.63,070425,,,A*77
$GNVTG,146.63,T,,M,0.78,N,1.45,K,A*2A
```

with `DISPLAY_GNSS_LINES=1`
```
FullExample.ino
An extensive example of many interesting TinyGPS++ features
Testing TinyGPS++ library v. 1.0.2
by Mikal Hart

Sats HDOP  Latitude   Longitude   Fix  Date       Time     Date Alt    Course Speed Card  Distance Course Card  Chars Sentences Checksum
           (deg)      (deg)       Age                      Age  (m)    --- from GPS ----  ----  to POI    ----  RX    RX        Fail
----------------------------------------------------------------------------------------------------------------------------------------
**** ***** ********** *********** **** ********** ******** **** ****** ****** ***** ***   ******** ****** ***   0     0         0        
0    0.0   ********** *********** **** 01/06/2080 00:30:22 394  ****** ****** ***** ***   ******** ****** ***   236   0         0        
...
5    2.8   45.183380  5.735302    559  04/07/2025 17:35:16 559  191.21 146.63 0.43  SSE   2        59.73  ENE   329   2         0        
5    2.8   45.183380  5.735305    215  04/07/2025 17:35:17 215  191.07 146.63 0.46  SSE   2        59.72  ENE   983   4         0        
5    2.8   45.183380  5.735305    562  04/07/2025 17:35:18 562  190.95 146.63 0.26  SSE   2        59.72  ENE   1312  6         0        
5    2.8   45.183384  5.735300    555  04/07/2025 17:35:19 555  190.86 146.63 0.09  SSE   2        59.74  ENE   1641  8         0        
5    2.8   45.183387  5.735298    563  04/07/2025 17:35:20 563  190.77 146.63 0.15  SSE   2        59.75  ENE   1970  10        0        
5    2.8   45.183387  5.735298    563  04/07/2025 17:35:21 563  190.66 146.63 0.30  SSE   2        59.75  ENE   2299  12        0        
5    2.8   45.183387  5.735303    222  04/07/2025 17:35:22 222  190.54 146.63 0.13  SSE   2        59.74  ENE   2955  14        0        
5    2.8   45.183387  5.735305    566  04/07/2025 17:35:23 566  190.44 146.63 0.13  SSE   2        59.74  ENE   3284  16        0        
5    2.8   45.183384  5.735311    569  04/07/2025 17:35:24 569  190.32 146.63 0.13  SSE   2        59.72  ENE   3613  18        0        
5    2.8   45.183380  5.735319    569  04/07/2025 17:35:25 569  190.20 146.63 0.22  SSE   2        59.71  ENE   3942  20        0        
```

![Grove GPS on the TinyGS 2G4 station](../exp32+grove-gps.jpg) 
![Mikrobus GPS on the TinyGS 2G4 station](../esp32+xa1110-mikrobus.jpg) 
