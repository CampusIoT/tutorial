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

### Console output

For Centipede `CRO2` mount point 

```console
RTCM3 message: len=100 type=1004 --> RTCM pushed 100 bytes to ZED
Not a RTCM3 messages. Discard 992 bytes
RTCM3 message: len=1092 type=1004 --> RTCM pushed 1092 bytes to ZED
RTCM3 message: len=100 type=1004 --> RTCM pushed 100 bytes to ZED
Not a RTCM3 messages. Discard 992 bytes
RTCM3 message: len=1198 type=1004 --> RTCM pushed 1198 bytes to ZED
RTCM3 message: len=100 type=1004 --> RTCM pushed 100 bytes to ZED
Not a RTCM3 messages. Discard 992 bytes
RTCM3 message: len=100 type=1004 --> RTCM pushed 100 bytes to ZED
Not a RTCM3 messages. Discard 992 bytes
RTCM3 message: len=100 type=1004 --> RTCM pushed 100 bytes to ZED
Not a RTCM3 messages. Discard 992 bytes
RTCM3 message: len=100 type=1004 --> RTCM pushed 100 bytes to ZED
Not a RTCM3 messages. Discard 992 bytes
RTCM3 message: len=100 type=1004 --> RTCM pushed 100 bytes to ZED
Not a RTCM3 messages. Discard 992 bytes
RTCM3 message: len=100 type=1004 --> RTCM pushed 100 bytes to ZED
Not a RTCM3 messages. Discard 992 bytes
RTCM3 message: len=100 type=1004 --> RTCM pushed 100 bytes to ZED
Not a RTCM3 messages. Discard 992 bytes
RTCM3 message: len=1092 type=1004 --> RTCM pushed 1092 bytes to ZED
RTCM3 message: len=100 type=1004 --> RTCM pushed 100 bytes to ZED
Not a RTCM3 messages. Discard 992 bytes
RTCM3 message: len=1198 type=1004 --> RTCM pushed 1198 bytes to ZED
RTCM3 message: len=100 type=1004 --> RTCM pushed 100 bytes to ZED
Not a RTCM3 messages. Discard 992 bytes

```