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

> You can also install [STM32CubeProgrammer software for all STM32](https://www.st.com/en/development-tools/stm32cubeprog.html)

### Applications for Serial Console

* [Putty for Windows](https://www.putty.org/)
* `minicom`, `tio`, `pyterm` on MacOS/Linux

#### Console with `tio`

Open the serial console of the board
```bash
brew install tio
tio -L
tio -b 115200 -m INLCRNL /dev/tty.usbserial-142xxx
```

## Introduction about RIOT

* [Getting Started](https://riot-os.github.io/riot-course/slides/02-getting-started/#1)
* [RIOT Basics](https://riot-os.github.io/riot-course/slides/03-riot-basics/#1)

> All the supported CPU are in the [directory `cpu`](https://github.com/RIOT-OS/RIOT/tree/master/cpu)

```bash
cd ~/github/RIOT-OS/RIOT/cpu
ls -al
```

> All the supported boards are in the [directory `boards`](https://github.com/RIOT-OS/RIOT/tree/master/boards)

```bash
cd ~/github/RIOT-OS/RIOT/boards
ls -al
```

> All the supported sensors drivers are in the [directory `drivers`](https://github.com/RIOT-OS/RIOT/tree/master/drivers)

```bash
cd ~/github/RIOT-OS/RIOT/drivers
ls -al
```


## Boards and shields for the workshop

### MCU boards

* STM Nucleo STM32 F446RE, F401RE, F411RE, L152RE, L073RZ, L053R8 ...
* [STM STM32F746G-DISCO](https://www.st.com/en/evaluation-tools/32f746gdiscovery.html)
* [STM P-Nucleo STM32WB55](https://www.st.com/en/evaluation-tools/p-nucleo-wb55.html)
* [STM B-L475E-IOT01A](https://www.st.com/en/evaluation-tools/b-l475e-iot01a.html)
* [STM B-U585I-IOT02A](https://www.st.com/en/evaluation-tools/b-u585i-iot02a.html)
* [Sparkfun Raspberry RP2040](https://www.sparkfun.com/products/18721)
* [Espressif ESP32 Wroom Dev Kit](https://www.espressif.com/en/products/devkits)

### MCU Boards with a LoRa transceiver

* [STM B-L072Z-LRWAN1](https://www.st.com/en/evaluation-tools/b-l072z-lrwan1.html)
* [IMST iM880a](https://github.com/CampusIoT/tutorial/tree/master/im880a)
* Seeedstudio LoRa E5 [Dev](https://stm32python.gitlab.io/fr-version-lora/lora-e5-dev.html)/[Mini]() (STM32WL55 included) requires a STLink programmer
* [STM NUCLEO-WL55JC](https://www.st.com/en/evaluation-tools/nucleo-wl55jc.html) (STM32WL55 included)

### Sensors and Actuators

* Shield MEMS IKS01Ax
* [Grove Base Shield (for Arduino)](https://www.seeedstudio.com/Base-Shield-V2.html)
* [Grove Sensor Modules](https://wiki.seeedstudio.com/Grove/)

<!-- ![Grove Basic Shield](images/grove-shield.png) -->

![Grove Basic Shield](images/base_shield_v2.png)

![Boards and shields for the tutorial](images/boards.jpg)

### IoT Communications

#### LoRa/LoRaWAN

* Shield Semtech LoRa [SX1272MB2DAS](https://os.mbed.com/components/SX1272MB2xAS/) with SX1272 (868MHz only)
* Shield Semtech LoRa [SX1276MB1MAS](https://os.mbed.com/components/SX1276MB1xAS/) with SX1276 (433MHz and 868MHz)

#### Ultra Wide Band

* [Qorvo DWM 1001](https://github.com/CampusIoT/tutorial/tree/master/qorvo_dwm1001)

## Lesson #1: Hello world and Shell

Configure your board (`nucleo-f411re`, `nucleo-f446re`, `nucleo-l152re`, `nucleo-l073rz`, `p-nucleo-wb55`, `stm32f746g-disco`, `lora-e5-dev`, `b-l072z-lrwan1`, `dwm1001`, `rpi-pico` ...) according to the model into the [supported list](https://github.com/RIOT-OS/RIOT/tree/master/boards).
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

With `lora-e5-dev` boards
```
Help: Press s to start test, r to print it is ready
START
main(): This is RIOT! (Version: 2022.01-devel-217-g43bef)
On-board button test

 -- Available buttons: 2

 -- Try pressing buttons to test.

[SUCCESS]
Help: Press s to start test, r to print it is ready
START
main(): This is RIOT! (Version: 2022.01-devel-217-g43bef)
On-board button test

 -- Available buttons: 2

 -- Try pressing buttons to test.

[SUCCESS]
Pressed BTN0
Pressed BTN0
Pressed BTN0
```

## Lesson #3: MEMS and IMU

IKS01Ax shields provide several IMU and TH sensors from ST Microelectronic.

Check the version of the shield.

![iks01a3](images/iks01a3.jpg)

* Shield Nucleo [IKS01A1](https://www.st.com/en/ecosystems/x-nucleo-iks01a1.html) (sensors are LSM6DS0, LIS3MDL, LPS25HB, HTS221)
* Shield [Nucleo IKS01A2](https://www.st.com/en/ecosystems/x-nucleo-iks01a2.html) (sensors are LSM6DSL, LSM303AGR, LPS22HB, HTS221)
* Shield [Nucleo IKS01A3](https://www.st.com/en/ecosystems/x-nucleo-iks01a3.html) (sensors are LSM6DSO, LIS2MDL, LIS2DW12, LPS22HH, HTS221, STTS751)
* Board [B-L475E-IOT01A](https://www.st.com/en/evaluation-tools/b-l475e-iot01a.html) (sensors are MP34DT01, HTS221, LIS3MDL, LSM6DSL, LPS22HB, VL53L0X)
* Board [B-U585I-IOT02A]([https://www.st.com/en/evaluation-tools/b-l475e-iot01a.html](https://www.st.com/en/evaluation-tools/b-u585i-iot02a.html) (sensors are MP34DT01 microphones, IIS2MDCTR gyroscope, ISM330DHCX magnetometer, LPS22HH barometer, HTS221 humidity and temperature, VL53L5 time-of-flight, and VEML6030 ambient light)

### For HTS221 (capacitive digital relative humidity and temperature)
```bash
cd ~/github/RIOT-OS/RIOT/tests/driver_hts221
make BOARD=$BOARD flash term
```

```
main(): This is RIOT! (Version: 2023.04-devel-158-gd11a3)
Init HTS221 on I2C_DEV(0)
H: 39.2%, T: 23.5°C
H: 39.2%, T: 23.5°C
H: 39.2%, T: 23.5°C
H: 39.2%, T: 23.5°C
H: 42.6%, T: 25.1°C
...
H: 49.1%, T: 26.2°C
H: 54.8%, T: 25.4°C
H: 57.4%, T: 26.0°C
```

### For LPS22HH
LPS22HH is a MEMS pressure sensor, 260-1260 hPa absolute digital output barometer

```bash
cd ~/github/RIOT-OS/RIOT/tests/driver_lpsxxx
make BOARD=$BOARD DRIVER=lps22hh flash term
```

### For LPS22HB
LPS22HB is a MEMS pressure sensor, 260-1260 hPa absolute digital output barometer

```bash
cd ~/github/RIOT-OS/RIOT/tests/driver_lpsxxx
make BOARD=$BOARD DRIVER=lps22hb flash term
```

### For LPS25HB
LPS25HB is MEMS pressure sensor, 260-1260 hPa absolute digital output barometer

```bash
cd ~/github/RIOT-OS/RIOT/tests/driver_lpsxxx
make BOARD=$BOARD DRIVER=lps25hb flash term
```

### For LSM6DSL
LSM6DSL is a MEMS 3D accelerometer (±2/±4/±8/±16 g) and 3D gyroscope (±125/±245/±500/±1000/±2000 dps)

```bash
cd ~/github/RIOT-OS/RIOT/tests/driver_lsm6dsl
make BOARD=$BOARD flash term
```

### For LIS3MDL 
LIS3MDL is a MEMS 3D magnetometer (±4/ ±8/ ±12/ 16 gauss)

```bash
cd ~/github/RIOT-OS/RIOT/tests/driver_lis3mdl
make BOARD=$BOARD flash term
```

### For NXP LM75 
NXP LM75 is a temperature sensor (available on `lora-e5-dev` boards)

```bash
cd ~/github/RIOT-OS/RIOT/tests/driver_lm75
make BOARD=lora-e5-dev DRIVER=lm75a
```

```
main(): This is RIOT! (Version: 2022.01-devel-429-g70744)                       
Sensor test...                                                                  
Initialization...                                                               
Initialization succeeded                                                        
error setting Hyst and/or OS temps                                              
Set OS temp is 80.0ºC                                                          
Set HYST temp is 75.0ºC                                                        
20.0ºC                                                                         
Set OS temp is 80.0ºC                                                          
Set HYST temp is 75.0ºC                                                        
lm75: OS alert pin not connected or defined                                     
Error reading OS pin state                                                      
22.500ºC                                                                       
``` 

### For MAG3110 breakout (plug in an I2C connector of the Grove Basic Shield) 

```bash
cd ~/github/RIOT-OS/RIOT/tests/driver_mag3110
make BOARD=$BOARD
```

### For `a3g4250d` gyro (on DIP extension board)
```bash
cd ~/github/RIOT-OS/RIOT/tests/driver_l3gxxxx
gmake BOARD=$BOARD DRIVER=a3g4250d flash term
```

```
main(): This is RIOT! (Version: 2023.04-devel-158-gd11a3)
L3GXXXX gyroscope driver test application

Initializing L3GXXXX sensor
[OK]

gyro [dps] x:   +84, y:  +126, z:  +223
gyro [dps] x:   +14, y:    +4, z:    +8
gyro [dps] x:    +0, y:    +0, z:    +0
gyro [dps] x:    +0, y:    +0, z:    +0
gyro [dps] x:    +0, y:    +0, z:    +0
gyro [dps] x:    +0, y:    +0, z:    +0
gyro [dps] x:    +0, y:    +0, z:    +0
gyro [dps] x:    +0, y:    +0, z:    +0
gyro [dps] x:    +0, y:    +0, z:    +0
gyro [dps] x:    +0, y:    +0, z:    +0
gyro [dps] x:    +0, y:    +0, z:   +24
gyro [dps] x:   +16, y:    -3, z:   +13
gyro [dps] x:    +8, y:    +0, z:   -26
gyro [dps] x:    +1, y:    +0, z:   +27
```


> TODO : test for `drivers/lsm303agr`

## Lesson #4: SAUL ([[S]ensor [A]ctuator [U]ber [L]ayer](https://doc.riot-os.org/group__drivers__saul.html))

Keep the Nucleo IKS01Ax Shield onto your Nucleo board

```bash
cd ~/github/RIOT-OS/RIOT/tests/saul
make BOARD=$BOARD flash term
```


```
main(): This is RIOT! (Version: 2023.04-devel-158-gd11a3)
SAUL test application

Dev: LED(green)	Type: ACT_SWITCH
Data:	              0 

Dev: Button(B1 User)	Type: SENSE_BTN
Data:	              0 

##########################

```
Push the button

```
Dev: LED(green)	Type: ACT_SWITCH
Data:	              0 

Dev: Button(B1 User)	Type: SENSE_BTN
Data:	              1 

##########################

```

Edit `Makefile` in order to add the modules related to the sensors available onto the shield.

```Makefile
...
USEMODULE += lis3mdl
USEMODULE += hts221
USEMODULE += lsm6dsl
USEMODULE += lm75
USEMODULE += stts751
USEMODULE += lps25hb
...
```

```bash
cd ~/github/RIOT-OS/RIOT/tests/saul
make BOARD=$BOARD flash term
```

```
##########################
main(): This is RIOT! (Version: 2023.04-devel-158-gd11a3)
SAUL test application

Dev: LED(green)	Type: ACT_SWITCH
Data:	              0 

Dev: Button(B1 User)	Type: SENSE_BTN
Data:	              0 

Dev: hts221	Type: SENSE_TEMP
Data:	           24.0 °C

Dev: hts221	Type: SENSE_HUM
Data:	           41.9 %

```


For `lora-e5-dev` boards

```bash
cd ~/github/RIOT-OS/RIOT/tests/saul
make BOARD=lora-e5-dev
```

```
##########################
 
Dev: LED(red)	Type: ACT_SWITCH
Data:	              1 
 
Dev: Button(B1 Boot)	Type: SENSE_BTN
Data:	              0 
 
Dev: Button(B2 D0)	Type: SENSE_BTN
Data:	              0 
 
Dev: lm75	Type: SENSE_TEMP
Data:	          20.87 °C
```

## Lesson #5 : Analog GPIO

Connect the Grove Thumb Joystick to the A0 connector on the Grove Basic Shield (Pins are A0,A1)

![Grove Thumb Joystick](images/grove-thumb-joystick.jpg)

```bash
cd ~/github/RIOT-OS/RIOT/tests/periph_adc
make BOARD=$BOARD flash term
```

```
##########################
main(): This is RIOT! (Version: 2023.04-devel-158-gd11a3)

RIOT ADC peripheral driver test

This test will sample all available ADC lines once every 100ms with
a 10-bit resolution and print the sampled results to STDIO


Successfully initialized ADC_LINE(0)
Successfully initialized ADC_LINE(1)
Successfully initialized ADC_LINE(2)
Successfully initialized ADC_LINE(3)
Successfully initialized ADC_LINE(4)
Successfully initialized ADC_LINE(5)
Successfully initialized ADC_LINE(6)
ADC_LINE(0): 1023
ADC_LINE(1): 531
ADC_LINE(2): 96
ADC_LINE(3): 100
ADC_LINE(4): 112
ADC_LINE(5): 120
ADC_LINE(6): 82
ADC_LINE(0): 1023
ADC_LINE(1): 529
ADC_LINE(2): 98
ADC_LINE(3): 120
ADC_LINE(4): 133
ADC_LINE(5): 120
ADC_LINE(6): 82
```




```bash
cd ~/github/RIOT-OS/RIOT/tests/sys_arduino_analog
make BOARD=$BOARD flash term
```

```
TODO
```




## Lesson #6: LoRa/LoRaWAN communications

* https://riot-os.github.io/riot-course/slides/05-lorawan-with-riot/#1

Login on [CampusIoT LoRa Network Server](https://lns.campusiot.imag.fr/#/organizations/5/applications/258)

The username is `GuestSandbox` and the password is given during the workshop.

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

Show the LoRa trafic on the [local gateway console](https://lns.campusiot.imag.fr/#/organizations/5/gateways/353036201a003200/frames)

For NUCLEO-WL55JC1 boards (868 MHz)
```bash
cd ~/github/RIOT-OS/RIOT/tests/pkg_semtech-loramac/
make BOARD=nucleo-wl55jc LORA_DRIVER=sx126x_stm32wl flash term
```

For NUCLEO-WL55JC2 boards (433 MHz)
```bash
cd ~/github/RIOT-OS/RIOT/tests/pkg_semtech-loramac/
make BOARD=nucleo-wl55jc LORA_DRIVER=sx126x_stm32wl REGION=EU433 flash term
```

For Seeedstudio LoRa E5 board Dev and Mini (868 MHz)
```bash
cd ~/github/RIOT-OS/RIOT/tests/pkg_semtech-loramac/
make BOARD=lora-e5-dev LORA_DRIVER=sx126x_stm32wl flash term
```

For Nucleo Lxxx/Fxxx boards with the Semtech [SX1272MB2DAS](https://os.mbed.com/components/SX1272MB2xAS/) LoRa shield (868 MHz only)
```bash
cd ~/github/RIOT-OS/RIOT/tests/pkg_semtech-loramac/
make BOARD=$BOARD LORA_DRIVER=sx1272 flash term
```

For Nucleo Lxxx/Fxxx boards with the Semtech [SX1276MB1MAS](https://os.mbed.com/components/SX1276MB1xAS/) LoRa shield (868 MHz)
> HF antenna should be mounted
```bash
cd ~/github/RIOT-OS/RIOT/tests/pkg_semtech-loramac/
make BOARD=$BOARD LORA_DRIVER=sx1276 flash term
```

For Nucleo Lxxx/Fxxx boards with the Semtech [SX1276MB1MAS](https://os.mbed.com/components/SX1276MB1xAS/) LoRa shield (433 MHz)
> LF antenna should be mounted
```bash
cd ~/github/RIOT-OS/RIOT/tests/pkg_semtech-loramac/
make BOARD=$BOARD LORA_DRIVER=sx1276 REGION=EU433 flash term
```

For iM880 boards (868 MHz)
```bash
cd ~/github/RIOT-OS/RIOT/tests/pkg_semtech-loramac/
make BOARD=im880b LORA_DRIVER=sx1272 flash term
```

For [ST B-L072Z-LRWAN1 LoRa discovery board](https://www.st.com/en/evaluation-tools/b-l072z-lrwan1.html) (868 MHz only)
```bash
cd ~/github/RIOT-OS/RIOT/tests/pkg_semtech-loramac/
make BOARD=b-l072z-lrwan1 LORA_DRIVER=sx1276 flash term
```

> Default region is `EU868` (863-870 MHz). See [LoRaWAN Regional Parameters](https://lora-alliance.org/resource_hub/rp2-1-0-3-lorawan-regional-parameters/) for more information about countries regions.

> For testing purpose, it is possible to disable the duty-cycle restriction implemented in the MAC layer with the `DISABLE_LORAMAC_DUTYCYCLE` macro:
```
CFLAGS=-DDISABLE_LORAMAC_DUTYCYCLE LORA_REGION=EU868 LORA_DRIVER=sx1272 make ...
```

Show the help
```
> loramac
Usage: loramac <get|set|join|tx|link_check>
> loramac get
Usage: loramac get <deveui|appeui|appkey|appskey|nwkskey|devaddr|class|dr|adr|public|netid|tx_power|rx2_freq|rx2_dr|ul_cnt|ch_mask>
> loramac set
Usage: loramac set <deveui|appeui|appkey|appskey|nwkskey|devaddr|class|dr|adr|public|netid|tx_power|rx2_freq|rx2_dr|ul_cnt|ch_mask> <value>
```

Set the device EUI, the application EUI and application key of your LoRaWAN endpoint :
```
> loramac set deveui ABCDEF1200000001
> loramac set appeui ABCDEF1200FFFFFF
> loramac set appkey CAFEBABECAFEBABE0123456789ABCDEF
```

Save the device LoRaWAN configuration (EUIs and keys) in EEPROM (if provided by the microcontroller):
```
> loramac save
```

Switch the default datarate index (from 0 to 7 for `EU868`). Datarate `5` is for `SF7BW125`:
```
> loramac set dr 5
``` 

<!-- Switch the default txpower index (from 0 to 16). -->

Join a network using the OTAA procedure:
```
> loramac join otaa
Join procedure failed!
> loramac join otaa
Cannot join: dutycycle restriction
```
Retry later !
```
> loramac join otaa
Join procedure succeeded!
```


Get the allocated DevAddr:
```
> loramac get devaddr
FC00AC12
```
> The NetID of CampusIoT is `C0002B`, so endpoints devaddrs are between `FC00AC00` and `FC00AFFF`. [More NetIDs](https://www.thethingsnetwork.org/docs/lorawan/prefix-assignments/)

Switch to adaptive data rate (the LoRa network server will adapt the datarate and the txpower according the link budget after the next transmission):
```
> loramac set adr on
```

Send confirmable data on port 2 (cnf and port are optional):
```
> loramac tx This\ is\ RIOT! cnf 2
```

<!-- Get Datarate -->
<!-- Get TxPower -->

Perform a Link Check command (will be triggered in the next transmission):
```
> loramac link_check
```

Send unconfirmable data on port 3:
```
> loramac tx This\ is\ RIOT! uncnf 3
```

In the [endpoint console](https://lns.campusiot.imag.fr/#/organizations/5/applications/258), enqueue a downlink message [encoded in base64](https://www.rapidtables.com/web/tools/base64-encode.html) `RWNsaXBzZSBJb1QgRGF5cyAyMDIz`

![Downlink](images/downlink.png)

Send confirmable data on port 4:
```
> loramac tx This\ is\ RIOT! cnf 4
Data received: Eclipse IoT Days 2023, port: 14
```

Switch the default datarate index (from 0 to 7 for `EU868`). Datarate `0` is for `SF12BW125`:
```
> loramac set dr 0
``` 

Send unconfirmable data on port 5:
```
> loramac tx This\ is\ RIOT! uncnf 5
Data received: Eclipse IoT Days 2023, port: 15
```

<!-- Get Datarate -->
<!-- Get TxPower -->
> The LoRa network server adapts automatically the datarate.

## Lesson #7: UWB Ranging and positioning

* https://github.com/CampusIoT/tutorial/tree/master/qorvo_dwm1001#getting-started-with-riot 

## Lesson #8: GNSS module

TODO

## Lesson #9: Micro Python

TODO

## Lesson #10: RUST

TODO

## Lesson #11: Cryptography (ED25519)

https://github.com/thingsat/ecc_mcu_benchmarks


## Lesson #12: Secure Firmware Update (TODO)

This part requires a SDCard reader. New firmware is delivered on a SDCard 

## Extra

### SRF0x ultrasonic range sensor

Plug the SRF0x ultrasonic range sensor into a I2C commector of the Grove Basic Shield


```bash
cd ~/github/RIOT-OS/RIOT/tests/driver_srf02
make BOARD=$BOARD flash term
```

```bash
cd ~/github/RIOT-OS/RIOT/tests/driver_srf04
make BOARD=$BOARD flash term
```

```bash
cd ~/github/RIOT-OS/RIOT/tests/driver_srf08
make BOARD=$BOARD flash term
```


### Encoding payload

#### LPP Cayenne


#### CBOR


#### Protobuf

[See ../protobuf](../protobuf)
