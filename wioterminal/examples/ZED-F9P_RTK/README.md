# RTK examples with Wio Terminal


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


As part of our ever growing Arduino u-blox GNSS library, we’ve added a NTRIP Server example (located under ... -> examples -> ZED-F9P -> Example14_NTRIPServer).

Read
* https://docs.sparkfun.com/SparkFun_RTK_Firmware/intro/
* https://docs.sparkfun.com/SparkFun_RTK_Firmware/permanent_base/
* https://centipede.fr/
* https://www.digikey.fr/fr/products/detail/mikroelektronika/MIKROE-4456/13662957
* https://www.digikey.fr/fr/products/detail/u-blox/ANN-MB-00-00/9817928
