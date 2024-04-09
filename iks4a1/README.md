# X-NUCLEO-IKS4A1 : Motion MEMS and environmental sensor expansion board for STM32 Nucleo


* LSM6DSO16IS: MEMS 3D accelerometer (±2/±4/±8/±16 g) + 3D gyroscope (±125/±250/±500/±1000/±2000 dps) with ISPU (Intelligent Processing Unit)
* LIS2MDL: MEMS 3D magnetometer (±50 gauss)
* LIS2DUXS12: Ultra low-power MEMS 3D accelerometer (±2/±4/±8/±16 g) with Qvar, AI, & anti-aliasing
* LPS22DF: Low-power and high-precision MEMS pressure sensor, 260-1260 hPa absolute digital output barometer
* [SHT40AD1B](https://sensirion.com/products/catalog/SHT40/)
* [STTS22H](https://www.st.com/en/mems-and-sensors/stts22h.html): Low-voltage, ultralow-power, 0.5 °C accuracy temperature sensor (–40 °C to +125 °C)
* LSM6DSV16X: MEMS 3D accelerometer (±2/±4/±8/±16 g) + 3D gyroscope (±125/±250/±500/±1000/±2000/±4000 dps) with embedded sensor fusion, AI, Qvar 

https://www.st.com/en/ecosystems/x-nucleo-iks4a1.html


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
0x10 - - - - - - - - - - - - - - X -
0x20 - - - - - - - - - - - - - - - -
0x30 - - - - - - - - X - - - - - - -
0x40 - - - - - - - - - - - - - - - -
0x50 - - - - - - - - - - - - - X - -
0x60 - - - - - - - - - - X X - - - -
0x70 - - - - - - - - R R R R R R R R

```
