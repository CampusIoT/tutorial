# Google Coral Dev Board Micro

The [Google Coral Dev Board Micro](https://coral.ai/products/dev-board-micro/) is a microcontroller board with a dual-core MCU, Coral Edge TPU, a [Himax HM01B0 CMOS](https://www.himax.com.tw/products/cmos-image-sensor/always-on-vision-sensors/hm01b0/) color camera (324 x 324 px or QVGA (320 x 240 px); 110º diagonal FOV; ƒ/2.0 focal ratio; Fixed focus), a PDM microphone, user and reset buttons, four LEDs and 2 GPIO headers with 12 pins (digital, analog, and power pins).

With this board, you can build low-power systems with fast on-device inferencing for vision and audio ML applications. You
can also expand the hardware with custom add-on boards using the high-density board-to-board connectors.

The [firmware development platform](https://github.com/google-coral/coralmicro) is based on FreeRTOS with a CMake toolchain. It also includes support for development with Arduino. The FreeRTOS plateform for coralmicro includes APIs to use the Dev Board Micro's camera, microphone, and GPIOs, plus APIs for reading/writing files, creating RPC services, communicating across MCU cores, connecting to Wi-Fi (requires the Wireless Add-on board), and [TensorFlow Lite for Microcontrollers](https://github.com/tensorflow/tflite-micro) to execute ML and DL models on either the MCU or with acceleration on the Edge TPU. Bare-metal apps development with the [MCUXpresso SDK](https://mcuxpresso.nxp.com/en/welcome) is available but it is not documented by Google.

![Coral Dev Board Micro](images/coral-devboard-micro-01.jpg)

![Coral Dev Board Micro](images/micro-callouts.png)

![Coral Dev Board Micro Firmware Stack](images/coralmicro-sw-stack.png)

## Getting started

https://coral.ai/docs/dev-board-micro/get-started/#1-gather-requirements

## Build firmware with FreeRTOS

https://github.com/google-coral/coralmicro

## Build firmware with Arduino

https://coral.ai/docs/dev-board-micro/arduino/#1-gather-requirements

## UART communication

> `UART6_TX` and `UART6_RX` are configured for serial port communication and should not be used for other
purposes.

## I2C Sensor

TODO

Connect a Bosch Sensortec BME280 breakout to the I2C pins 

Install the Arduino lib https://www.arduinolibraries.info/libraries/bme280

The original driver is https://github.com/boschsensortec/BME280_driver

## LoRaWAN E5 Grove Modem

Connect the [LoRaWAN E5 modem](https://wiki.seeedstudio.com/Grove_LoRa_E5_New_Version/) to the UART pins (`UART6_TX` and `UART6_RX`).

TODO

## Add-ons

### Wifi Add-ons

https://coral.ai/docs/dev-board-micro/wireless-datasheet/

### PoE Add-ons

https://coral.ai/docs/dev-board-micro/poe-datasheet/

### Battery packs


### Power Profiling

[Power Profiler Kit II](https://www.mouser.fr/datasheet/2/297/Power_Profiler_Kit_II_PB_v1_0-1928294.pdf)

## Misc

### Enclosures & Cases

https://coral.ai/products/dev-board-micro-case/
