# X-NUCLEO-IKS01A3

https://www.st.com/en/ecosystems/x-nucleo-iks01a3.html

* LSM6DSO: MEMS 3D accelerometer (±2/±4/±8/±16 g) + 3D gyroscope (±125/±250/±500/±1000/±2000 dps)
* LIS2MDL: MEMS 3D magnetometer (±50 gauss)
* LIS2DW12: MEMS 3D accelerometer (±2/±4/±8/±16 g)
* LPS22HH: MEMS pressure sensor, 260-1260 hPa absolute digital output barometer
* HTS221: capacitive digital relative humidity and temperature
* STTS751: Temperature sensor (–40 °C to +125 °C) 

## STML32Duino
TODO

## MBed
TODO

## FreeRTOS
TODO

## Zephyr


## RIOT OS

```bash
cd ~/github/RIOT-OS/RIOT/tests/periph/i2c
make BOARD=nucleo-f446re flash term
```

```
> ii2c_scan 0
Scanning I2C device 0...
addr not ack'ed = "-", addr ack'ed = "X", addr reserved = "R", error = "E"
     0 1 2 3 4 5 6 7 8 9 a b c d e f
0x00 R R R R R R R R R R R R R R - -
0x10 - - - - - - - - - X - - - - X -
0x20 - - - - - - - - - - - - - - - -
0x30 - - - - - - - - - - - - - - - -
0x40 - - - - - - - - - - - - - - - -
0x50 - - - - - - - - - - - - - X - X
0x60 - - - - - - - - - - - X - - - -
0x70 - - - - - - - - R R R R R R R R
```

```bash
cd ~/github/RIOT-OS/RIOT/tests/drivers/lpsxxx
export BOARD=nucleo-f446re
DRIVER=lps22hh make flash term
```


```
Test application for lps22hh pressure sensor

Initializing lps22hh sensor
Initialization failed
``



```bash
cd ~/github/RIOT-OS/RIOT/tests/drivers/hts221
export BOARD=nucleo-f446re
make flash term
```

```
Init HTS221 on I2C_DEV(0)
H: 49.8%, T: 19.6°C
H: 48.6%, T: 19.7°C
H: 48.5%, T: 19.7°C
H: 48.5%, T: 19.7°C
H: 48.6%, T: 19.8°C
```
