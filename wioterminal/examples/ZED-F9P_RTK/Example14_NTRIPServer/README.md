# NTRIP Server

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

Uncomment `#define CENTIPEDE 1` line to enable Centipede caster instead of RTK2GO caster

## Casters

### Centipede

TODO

### RTK2GO

RTK2Go works well and is free

My Base's Caster Status Report http://rtk2go.com:2101/SNIP::MOUNTPT?baseName=GrenobleTinyGS

### Emlid

[Emlid Caster](https://emlid.com/ntrip-caster/) also works well and is free 


### Console output

```console
RTCM3 message: len=71 type=1084 : GLONASS MSM4

RTCM3 message: len=53 type=1094 : Galileo MSM4

RTCM3 message: len=69 type=1124 : BeiDou MSM4

RTCM3 message: len=115 type=1074 : GPS MSM4

RTCM3 message: len=71 type=1084 : GLONASS MSM4

RTCM3 message: len=53 type=1094 : Galileo MSM4

RTCM3 message: len=69 type=1124 : BeiDou MSM4

RTCM3 message: len=10 type=1230 : GLONASS L1 and L2 Code-Phase Biases

RTCM3 message: len=115 type=1074 : GPS MSM4

RTCM3 message: len=71 type=1084 : GLONASS MSM4

RTCM3 message: len=53 type=1094 : Galileo MSM4

RTCM3 message: len=69 type=1124 : BeiDou MSM4

RTCM3 message: len=115 type=1074 : GPS MSM4

RTCM3 message: len=71 type=1084 : GLONASS MSM4

RTCM3 message: len=53 type=1094 : Galileo MSM4

RTCM3 message: len=69 type=1124 : BeiDou MSM4

RTCM3 message: len=115 type=1074 : GPS MSM4

RTCM3 message: len=71 type=1084 : GLONASS MSM4

RTCM3 message: len=53 type=1094 : Galileo MSM4

RTCM3 message: len=69 type=1124 : BeiDou MSM4

RTCM3 message: len=115 type=1074 : GPS MSM4

RTCM3 message: len=71 type=1084 : GLONASS MSM4

RTCM3 message: len=53 type=1094 : Galileo MSM4

RTCM3 message: len=69 type=1124 : BeiDou MSM4

RTCM3 message: len=115 type=1074 : GPS MSM4

RTCM3 message: len=71 type=1084 : GLONASS MSM4

RTCM3 message: len=53 type=1094 : Galileo MSM4

RTCM3 message: len=69 type=1124 : BeiDou MSM4

RTCM3 message: len=115 type=1074 : GPS MSM4

RTCM3 message: len=71 type=1084 : GLONASS MSM4

RTCM3 message: len=53 type=1094 : Galileo MSM4

RTCM3 message: len=69 type=1124 : BeiDou MSM4

RTCM3 message: len=100 type=1074 : GPS MSM4

RTCM3 message: len=71 type=1084 : GLONASS MSM4

RTCM3 message: len=53 type=1094 : Galileo MSM4

RTCM3 message: len=69 type=1124 : BeiDou MSM4

RTCM3 message: len=100 type=1074 : GPS MSM4

RTCM3 message: len=71 type=1084 : GLONASS MSM4

RTCM3 message: len=53 type=1094 : Galileo MSM4

RTCM3 message: len=69 type=1124 : BeiDou MSM4

RTCM3 message: len=100 type=1074 : GPS MSM4

RTCM3 message: len=71 type=1084 : GLONASS MSM4

RTCM3 message: len=53 type=1094 : Galileo MSM4

RTCM3 message: len=69 type=1124 : BeiDou MSM4

RTCM3 message: len=100 type=1074 : GPS MSM4

RTCM3 message: len=57 type=1084 : GLONASS MSM4

RTCM3 message: len=53 type=1094 : Galileo MSM4

RTCM3 message: len=69 type=1124 : BeiDou MSM4

RTCM3 message: len=10 type=1230 : GLONASS L1 and L2 Code-Phase Biases


```