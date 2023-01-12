# RTK examples with Wio Terminal

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

## Sparkfun u-blox GNSS Library

Search and install the "[SparkFun u-blox GNSS](https://github.com/sparkfun/SparkFun_u-blox_GNSS_Arduino_Library)" library using the Arduino IDE library manager.

## Get Position Accuracy

Open the GetPositionAccuracy sketch (located under `File > SparkFun u-blox GNSS > ZED-F9P > Example1_GetPositionAccuracy`).

## NTRIP Server

As part of our ever growing Arduino u-blox GNSS library, we’ve added a NTRIP Server example (located under `File > SparkFun u-blox GNSS > ZED-F9P -> Example14_NTRIPServer`) or the modified[Example14_NTRIPServer](./Example14_NTRIPServer).

## NTRIP Client
[Example15_NTRIPClient](./Example15_NTRIPClient)

## TODOList
* [ ] [Use the PPS pin for a clock with nanosec-accuracy](https://forum.arduino.cc/t/pps-from-ultimate-gps-synch-with-arduino-uno/336683/2)

## Readings

* https://docs.sparkfun.com/SparkFun_RTK_Firmware/intro/
* https://docs.sparkfun.com/SparkFun_RTK_Firmware/permanent_base/
* https://github.com/sparkfun/SparkFun_u-blox_GNSS_Arduino_Library
* https://github.com/sparkfun/SparkFun_u-blox_GNSS_Arduino_Library/tree/main/examples/ZED-F9P
* https://centipede.fr/
* https://www.digikey.fr/fr/products/detail/mikroelektronika/MIKROE-4456/13662957
* https://www.digikey.fr/fr/products/detail/u-blox/ANN-MB-00-00/9817928
* https://igs.bkg.bund.de/ntrip/download
