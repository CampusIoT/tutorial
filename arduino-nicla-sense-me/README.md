# Arduino Nicla Sense ME

La [carte Nicla Sense ME](https://store.arduino.cc/products/nicla-sense-me) combine une MCU Nordic nRF52832 avec 4 capteurs environnementaux de Bosch Sensortec : capteur de mouvement BHI260AP (avec IA intégrée), Magnétomètre BMM150, Capteur de pression BMP390, Capteur de gaz BME688 4 en 1 (avec pression, humidité et température). Elle communique en BLE via un module Bluetooth® ANNA B112.


![carte Nicla Sense ME](https://content.arduino.cc/assets/ABX00050-pinout.png)

## Démarrage avec Arduino IDE 1.8

https://docs.arduino.cc/hardware/nicla-sense-me

Il faut installer préalablement la carte dans l'IDE Arduino 1.8 via le grestionnaire de cartes en recherchant les cartes `Arduino Mbed OS Nicla Boards`.

### Test simple

Ouvrez le croquis d'exemple `Blink_Nicla`.

Sélectionnez le type de carte `Nicla Sense ME`.

Compilez et chargez le croquis.

## Démarrage avec RIOT OS

## Démarrage avec Zephyr OS

[TODO](https://docs.zephyrproject.org/3.2.0/boards/arm/arduino_nicla_sense_me/doc/index.html)

## Démarrage avec Edge Impulse

[TODO](https://docs.edgeimpulse.com/docs/development-platforms/officially-supported-mcu-targets/arduino-nicla-sense-me)

## Références
* [Manuel](https://docs.arduino.cc/static/9566019e357480c6f47f4978bd738d6a/ABX00050-datasheet.pdf)