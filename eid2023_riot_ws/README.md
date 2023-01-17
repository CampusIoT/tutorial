# Eclipse IoT Day 2023 :: Workshop RIOT

RIOT OS is an realtime operating system for embedded systems and Internet of Things. It supports common ISA (ARM7, ESP32, RISC-V), MCU and prototyping boards. It provides drivers for common sensors.

The tutorial will follow some chapters of the [https://riot-os.github.io/riot-course/ RIOT Course]

https://riot-os.github.io/riot-course/slides/03-riot-basics/#1


## Installation

Follow the [Getting Started](https://doc.riot-os.org/getting-started.html) section of the wiki.

https://riot-os.github.io/riot-course/slides/02-getting-started/#1


Clone the RIOT repository

```bash
cd
mkdir -p ~/github/RIOT-OS
cd ~/github/RIOT-OS
git clone https://github.com/RIOT-OS/RIOT.git
cd RIOT
```

Installing building tools for ARM7 architecture since the boards used for the tutorial are STM32.

> On MacOS, use `brew` for the installation.

### Applications for Serial Console

* Putty for Windows
* minicom,tio,pyterm on MacOS/Linux

TODO

## Introduction about RIOT

* [Getting Started](https://riot-os.github.io/riot-course/slides/02-getting-started/#1)
* [RIOT Basics](https://riot-os.github.io/riot-course/slides/03-riot-basics/#1)

## Boards and shields

### MCU boards

* Nucleo STM32 Fxxx / Lxxx
* Nucleo STM32WB55
* Seeedstudio LoRa E5 [Dev](https://stm32python.gitlab.io/fr-version-lora/lora-e5-dev.html)/[Mini]() (STM32WL55 included) requires a STLink programmer
* [IMST iM880a](https://github.com/CampusIoT/tutorial/tree/master/im880a)
* Espressive ESP32 Wroom Dev Kit 
* Sparkfun PRaspberry RP2040

### Sensors and Actuators

* Shield MEMS IKS01Ax
* [Grove Base Shield (for Arduino)](https://www.seeedstudio.com/Base-Shield-V2.html)
* [Grove Sensor Modules](https://wiki.seeedstudio.com/Grove/)

### IoT Communications

#### LoRa/LoRaWAN

* Shield LoRa [SX1272](https://os.mbed.com/components/SX1272MB2xAS/) and [SX1276](https://os.mbed.com/components/SX1276MB1xAS/)

#### Ultra Wide Band

* [Qorvo DWM 1001](https://github.com/CampusIoT/tutorial/tree/master/qorvo_dwm1001)


## Lesson #1: Hello world and Shell


Configure your board (`nucleo-f411re`, `nucleo-f446re`, `nucleo-l152re`, `p-nucleo-wb55`, `lora-e5-dev` ...)
```bash
BOARD=your_board
```

```bash
cd ~/github/RIOT-OS/RIOT/examples/hello-world
make BOARD=$BOARD flash term
```

```bash
cd ~/github/RIOT-OS/RIOT/tests/shell
make BOARD=$BOARD flash term
```


## Lesson #2: Blink a LED (Hello world)

```bash
cd ~/github/RIOT-OS/RIOT/tests/leds
make BOARD=$BOARD flash term
```

## Lesson #2: Push a button

```bash
cd ~/github/RIOT-OS/RIOT/tests/buttons
make BOARD=$BOARD flash term
```

## Lesson #3: MEMS and IMU

Check the version of the shield

Shield Nucleo IKS01A1 (sensors are LSM6DS0, LIS3MDL, LPS25HB, HTS221)
* https://www.st.com/en/ecosystems/x-nucleo-iks01a1.html

LSM6DS0: MEMS 3D accelerometer (±2/±4/±8 g) + 3D gyroscope (±245/±500/±2000 dps)
LIS3MDL: MEMS 3D magnetometer (±4/ ±8/ ±12/ 16 gauss)
LPS25HB*: MEMS pressure sensor, 260-1260 hPa absolute digital output barometer
HTS221: capacitive digital relative humidity and temperature 


Shield Nucleo IKS01A2 (sensors are LSM6DSL, LSM303AGR, LPS22HB, HTS221)
* https://www.st.com/en/ecosystems/x-nucleo-iks01a2.html 


Shield Nucleo IKS01A3 (sensors are LSM6DSO, LIS2MDL, LIS2DW12, LPS22HH, HTS221, STTS751)
* https://stm32python.gitlab.io/fr-version-lora/micro_python_iks01a3.html
* https://www.st.com/en/ecosystems/x-nucleo-iks01a3.html


For HTS221 (capacitive digital relative humidity and temperature)
```bash
cd ~/github/RIOT-OS/RIOT/tests/driver_hts221
make BOARD=$BOARD flash term
```

For LPS22HH (MEMS pressure sensor, 260-1260 hPa absolute digital output barometer)
```bash
cd ~/github/RIOT-OS/RIOT/tests/driver_lpsxxx
make BOARD=$BOARD DRIVER=lps22hh flash term
```

For LPS22HB (MEMS pressure sensor, 260-1260 hPa absolute digital output barometer)
```bash
cd ~/github/RIOT-OS/RIOT/tests/driver_lpsxxx
make BOARD=$BOARD DRIVER=lps22hb flash term
```

For LPS25HB (MEMS pressure sensor, 260-1260 hPa absolute digital output barometer)
```bash
cd ~/github/RIOT-OS/RIOT/tests/driver_lpsxxx
make BOARD=$BOARD DRIVER=lps25hb flash term
```

For LSM6DSL (MEMS 3D accelerometer (±2/±4/±8/±16 g) and 3D gyroscope (±125/±245/±500/±1000/±2000 dps))
```bash
cd ~/github/RIOT-OS/RIOT/tests/driver_lsm6dsl
make BOARD=$BOARD flash term
```

For LIS3MDL (MEMS 3D magnetometer (±4/ ±8/ ±12/ 16 gauss))
```bash
cd ~/github/RIOT-OS/RIOT/tests/driver_lis3mdl
make BOARD=$BOARD flash term
```

> TODO : test for `drivers/lsm303agr`

## Lesson #4: SAUL ([[S]ensor [A]ctuator [U]ber [L]ayer](https://doc.riot-os.org/group__drivers__saul.html))

Keep the  Nucleo IKS01Ax Shield onto your Nucleo board

```bash
cd ~/github/RIOT-OS/RIOT/tests/saul
make BOARD=$BOARD flash term
```

For `lora-e5-dev`
```bash
TODO
```

Edit `Makefile` in order to add the modules related to the sensors available onto the shield.

```Makefile
...
USEMODULE += lis3mdl
USEMODULE += hts221
USEMODULE += lsm6dsl
USEMODULE += lm75
USEMODULE += stts751

USEMODULE += lpsxxx
# Add the sub driver
USEMODULE += lps25hb
...
```

```bash
cd ~/github/RIOT-OS/RIOT/tests/saul
make BOARD=$BOARD flash term
```

## Lesson #5: LoRa/LoRaWAN communications

* https://riot-os.github.io/riot-course/slides/05-lorawan-with-riot/#1
* https://stm32python.gitlab.io/fr-version-lora/lora.html 
* https://stm32python.gitlab.io/fr-version-lora/lora-e5-dev.html 
* https://stm32python.gitlab.io/fr-version-lora/lora-e5-mini.html 

Login on [CampusIoT LoRa Network Server](https://lns.campusiot.imag.fr/#/organizations/5/applications/258)

The username is GuestSandbox and the password is given during the workshop.

The Organisation is `SANDBOX`.

Several endpoints has been already provisioned in this [application](https://lns.campusiot.imag.fr/#/organizations/5/applications/258).

Choose one for setting the DEVEUI, APPEUI and APPKEY of your endpoint.
 
```
Name   DEVEUI            APPEUI           APPKEY
EID_01 ABCDEF1200000001  ABCDEF1200FFFFFF CAFEBABECAFEBABE0123456789ABCDEF 
EID_02 ABCDEF1200000002  ABCDEF1200FFFFFF CAFEBABECAFEBABE0123456789ABCDEF 
EID_03 ABCDEF1200000003  ABCDEF1200FFFFFF CAFEBABECAFEBABE0123456789ABCDEF 
EID_04 ABCDEF1200000004  ABCDEF1200FFFFFF CAFEBABECAFEBABE0123456789ABCDEF 
EID_05 ABCDEF1200000005  ABCDEF1200FFFFFF CAFEBABECAFEBABE0123456789ABCDEF 
EID_06 ABCDEF1200000006  ABCDEF1200FFFFFF CAFEBABECAFEBABE0123456789ABCDEF 
EID_07 ABCDEF1200000007  ABCDEF1200FFFFFF CAFEBABECAFEBABE0123456789ABCDEF 
EID_08 ABCDEF1200000008  ABCDEF1200FFFFFF CAFEBABECAFEBABE0123456789ABCDEF 
EID_09 ABCDEF1200000009  ABCDEF1200FFFFFF CAFEBABECAFEBABE0123456789ABCDEF 
EID_0A ABCDEF120000000A  ABCDEF1200FFFFFF CAFEBABECAFEBABE0123456789ABCDEF 
```

Show the LoRa trafic on the [local gateway console](https://lns.campusiot.imag.fr/#/organizations/5/gateways)


## Lesson #6: UWB Ranging and positioning

* https://github.com/CampusIoT/tutorial/tree/master/qorvo_dwm1001#getting-started-with-riot 


## Lesson #7: Micro Python
TODO

## Lesson #8: RUST
TODO

## Lesson #9: Cryptography (ED25519)

https://github.com/thingsat/ecc_mcu_benchmarks


### Lesson #10: Secure Firmware Update (TODO)

This part requires a SDCard reader. New firmware is delivered on a SDCard 
