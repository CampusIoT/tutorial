# NTRIP Client

## Setup

* Wio Terminal
* Grove Cable
* ZED-F9P module : we use the [Mikrobus one](https://www.digikey.fr/fr/products/detail/mikroelektronika/MIKROE-4456/13662957)
* GPS outdoor antenna : we use [this one](https://www.digikey.fr/fr/products/detail/u-blox/ANN-MB-00-00/9817928).

* A Wifi access point (for the NTRIPServer)

Connect the ZED-F9P module to the I2C Grove Connector of the WioTerminal

    pin 1 - Yellow (for example, SCL on I2C Grove Connectors)
    pin 2 - White (for example, SDA on I2C Grove Connectors)
    pin 3 - Red - VCC on all Grove Connectors
    pin 4 - Black - GND on all Grove Connectors

## Configuration

Set the credentials in the file `secrets.h`.

Configure the mount point you want to get data from.  "CRO2" (which is located in Crolles, France)

Uncomment `#define CENTIPEDE 1` line to enable Centipede caster instead of RTK2GO caster

## Casters

### Centipede

TODO

### RTK2GO

RTK2Go works well and is free

### Emlid

[Emlid Caster](https://emlid.com/ntrip-caster/) also works well and is free 

## Console output

### For Centipede `CRO2` mount point 

```console
Press any key to start NTRIP Client.
Press any key to start NTRIP Client.
Press any key to start NTRIP Client.
Press any key to start NTRIP Client.
Press any key to start NTRIP Client.
Subscribing to Caster. Press key to stop
Opening socket to caster.centipede.fr
Connected to caster.centipede.fr: 2101
Requesting NTRIP Data from mount point CRO2
Sending credentials: xxxx
serverRequest size: 581 of 512 bytes available
Sending server request:
GET /CRO2 HTTP/1.0
User-Agent: NTRIP SparkFun u-blox Client v1.0
⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮

Caster timed out!
Press any key to start NTRIP Client.
Press any key to start NTRIP Client.
Subscribing to Caster. Press key to stop
Opening socket to caster.centipede.fr
Connected to caster.centipede.fr: 2101
Requesting NTRIP Data from mount point CRO2
Sending credentials: xxxx
serverRequest size: 138 of 512 bytes available
Sending server request:
GET /CRO2 HTTP/1.0
User-Agent: NTRIP SparkFun u-blox Client v1.0
⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮


Caster responded with: ICY 200 OK


Connected to caster.centipede.fr
RTCM3 message: len=100 type=1004 : Extended L1&L2 GPS RTK Observables --> RTCM pushed 100 bytes to ZED
Not a RTCM3 messages. Discard 992 bytes
RTCM3 message: len=1560 type=1004 : Extended L1&L2 GPS RTK Observables --> RTCM pushed 1560 bytes to ZED
Not a RTCM3 messages. Discard 202 bytes
RTCM3 message: len=100 type=1004 : Extended L1&L2 GPS RTK Observables --> RTCM pushed 100 bytes to ZED
Not a RTCM3 messages. Discard 992 bytes
RTCM3 message: len=100 type=1004 : Extended L1&L2 GPS RTK Observables --> RTCM pushed 100 bytes to ZED
Not a RTCM3 messages. Discard 992 bytes
RTCM3 message: len=100 type=1004 : Extended L1&L2 GPS RTK Observables --> RTCM pushed 100 bytes to ZED
Not a RTCM3 messages. Discard 992 bytes
RTCM3 message: len=1560 type=1004 : Extended L1&L2 GPS RTK Observables --> RTCM pushed 1560 bytes to ZED
Not a RTCM3 messages. Discard 84 bytes
RTCM3 message: len=100 type=1004 : Extended L1&L2 GPS RTK Observables --> RTCM pushed 100 bytes to ZED
Not a RTCM3 messages. Discard 992 bytes
RTCM3 message: len=1092 type=1004 : Extended L1&L2 GPS RTK Observables --> RTCM pushed 1092 bytes to ZED
RTCM3 message: len=100 type=1004 : Extended L1&L2 GPS RTK Observables --> RTCM pushed 100 bytes to ZED
Not a RTCM3 messages. Discard 1037 bytes
RTCM3 message: len=459 type=1020 : GLONASS ephemerides --> RTCM pushed 459 bytes to ZED
RTCM3 message: len=1560 type=1004 : Extended L1&L2 GPS RTK Observables --> RTCM pushed 1560 bytes to ZED
Not a RTCM3 messages. Discard 84 bytes
RTCM3 message: len=100 type=1004 : Extended L1&L2 GPS RTK Observables --> RTCM pushed 100 bytes to ZED
Not a RTCM3 messages. Discard 992 bytes
RTCM3 message: len=840 type=1042 : Beidou ephemerides --> RTCM pushed 840 bytes to ZED
Not a RTCM3 messages. Discard 992 bytes
RTCM3 message: len=100 type=1004 : Extended L1&L2 GPS RTK Observables --> RTCM pushed 100 bytes to ZED
```

### For rtk2go `bldr_SparkFun1` mount point 

```console
Opening socket to rtk2go.com
Connected to rtk2go.com: 2101
Requesting NTRIP Data from mount point bldr_SparkFun1
Sending credentials: didier.donsez@gmail.com:
serverRequest size: 591 of 512 bytes available
Sending server request:
GET /bldr_SparkFun1 HTTP/1.0
User-Agent: NTRIP SparkFun u-blox Client v1.0
⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮⸮

Caster responded with: ICY 200 OK

Connected to rtk2go.com
RTCM3 message: len=486 type=1074 : GPS MSM4 --> RTCM pushed 486 bytes to ZED
RTCM3 message: len=25 type=1005 : Stationary RTK Reference Station ARP --> RTCM pushed 25 bytes to ZED
RTCM3 message: len=486 type=1074 : GPS MSM4 --> RTCM pushed 486 bytes to ZED
RTCM3 message: len=25 type=1005 : Stationary RTK Reference Station ARP --> RTCM pushed 25 bytes to ZED
RTCM3 message: len=486 type=1074 : GPS MSM4 --> RTCM pushed 486 bytes to ZED
RTCM3 message: len=25 type=1005 : Stationary RTK Reference Station ARP --> RTCM pushed 25 bytes to ZED
RTCM3 message: len=486 type=1074 : GPS MSM4 --> RTCM pushed 486 bytes to ZED
RTCM3 message: len=25 type=1005 : Stationary RTK Reference Station ARP --> RTCM pushed 25 bytes to ZED
RTCM3 message: len=496 type=1074 : GPS MSM4 --> RTCM pushed 496 bytes to ZED
RTCM3 message: len=25 type=1005 : Stationary RTK Reference Station ARP --> RTCM pushed 25 bytes to ZED
```

