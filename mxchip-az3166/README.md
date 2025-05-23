# MXCHIP AZ3166 :: Eclipse ThreadX tutorial

## Getting started

* https://microsoft.github.io/azure-iot-developer-kit/docs/get-started/
* https://docs.google.com/presentation/d/1ayCS_kEJaZaK10ZhFyCe2oNvr9sY4N8ieIZUfd-B3m0
* https://github.com/Eclipse-SDV-Hackathon-Chapter-Two/challenge-threadx-and-beyond
* https://github.com/MXCHIP/mbed-wifi-example
* https://testdocs.zerynth.com/latest/reference/boards/az3166/docs/

## Features

* Dimension : 77 x 52 x 7 mm. Weight : 19 grams
* EMW3166 (ST STM32F412(RG?) + Broadcom BCM43362) Wi-Fi module with 256K SRAM，1M+2M Byte SPI Flash
* DAP Link emulator
* Micro USB
* 3.3V DC-DC, maximum current 1.5A
* Codec, with microphone and earphone socket ([NAU88C10](https://www.nuvoton.com/export/resource-files/en-us--DS_NAU88C10_DataSheet_EN_Rev2.1.pdf))
* OLED, 128x64 ([SSD1306](https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf))
* 2 user button
* 1 RGB light
* 3 working status indicator
* Security encryption chip
* Infrared emitter
* Connecting finger extension interface

Sensors
* ST HTS221 : relative humidity and temperature.
* ST LPS22HB : absolute piezoresistive pressure sensor
* ST LIS2MDL : magnetometer
* ST LSM6DSL : 3D digital accelerometer and gyroscope

![mxchip-az3166](media/mxchip-az3166-01.jpg)

## Pinout 

* 2 analog pins (PA4 and PA5)
* 11 digital pins (PB3, PB6, PC13, PB10, PB2, PB7, PB13, PB14, PB15, PB8, PB9)
* I2C pins (PB8 and PB9)
* SPI pins (PB13, PB14, and PB15)
* 2 button pins (PA4 and PA10)
* 1 PWM pin (PB3)

![pinout](media/az3166_pin_io.jpg)

## Defaut demo

[factory_firmware.bin](factory_firmware.bin)

> The firmware can be flashed using the mass storage `AZ3166` ot [STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html)

```bash
tio -b 115200 -m INLCRNL /dev/tty.usbmodemXXXX
```

```
************************************************
** MXChip - Microsoft IoT Developer Kit **
************************************************
AP mode Wi-Fi AZ-c8934688xxxx started .
Soft AP AZ-c8934688xxxx is running...
Connect and visit "http://192.168.0.1/" to config the Wi-Fi settings.

************************************************
** MXChip - Microsoft IoT Developer Kit **
************************************************
You can 1. press Button A and reset to enter configuration mode.
        2. press Button B and reset to enter AP mode.

0) Freebox-xxxxxx	Signal: -43	Enc type: 4
1) FreeWifi_secure	Signal: -44	Enc type: 4

Wi-Fi Freebox-xxxxxx connected.
Time from pool.ntp.org, now is (UTC): Mon Jan  6 21:28:00 2025

>>> Failed to send telemetry data: Http fault.
>>> Failed to send telemetry data: Http fault.
```

## Notes for Arduino

* https://jeremylindsayni.wordpress.com/category/arduino/
* https://www.hanselman.com/blog/did-i-leave-the-garage-door-open-a-nocode-project-with-azure-iot-central-and-the-mxchip-devkit
* https://github.com/Azure/iot-central-firmware/tree/master/MXCHIP
* 


## Notes for Eclipse ThreadX (previouly Azure RTOS)

* https://github.com/eclipse-threadx/getting-started/blob/master/MXChip/AZ3166/readme.md
* https://github.com/MicrosoftDocs/azure-docs/blob/main/articles/iot/tutorial-devkit-mxchip-az3166-iot-hub.

```bash
cd ~/github/eclipse-threadx/getting-started/MXChip/AZ3166/tools
./rebuild.sh
```

## Notes for Zephyr

* https://docs.zephyrproject.org/latest/boards/mxchip/az3166_iotdevkit/doc/index.html

### Toolchain install (with Docker)

```bash
docker pull zephyrprojectrtos/zephyr-build:latest
```
 
## Notes for RIOT OS

### Drivers

```makefile

TODO

```


* https://github.com/fcgdam/RIOT_TTGOESP32_LORA_V1/tree/master/examples/RIOT_TTGO_OLED


## Expension boards

The AZ3166 had a 2x40 pin edge connector (40 pins on 51 mm) like [Microbit boards](https://github.com/microbit-foundation/microbit-v2-hardware/blob/main/V2.21/MicroBit_V2.2.1_nRF52820%20schematic.PDF) https://microbit.org

* https://kitronik.co.uk/products/5601b-edge-connector-breakout-board-for-bbc-microbit-pre-built
* https://www.sparkfun.com/sparkfun-qwiic-micro-bit-breakout-with-headers.html
* https://cdn.sparkfun.com/assets/f/d/1/6/5/Micro_Bit_Breakout.zip
* https://fr.aliexpress.com/item/4000151701085.html
