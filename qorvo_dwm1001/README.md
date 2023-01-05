# Qorvo DWM1001

The Qorvo/Decawave DWM1001 development board includes a DWM1001 module which is based on a Nordic nRF51832 microcontroller. This microcontroller is an ARM Cortex-M4 with 64KB of RAM and 512KB of flash memory. It also provides in integrated BLE radio. The DWM1001 module also contains an Ultra Wide Band transceiver for indoor ranging and geolocation.

https://www.mouser.fr/datasheet/2/412/DWM1001_DEV_Data_Sheet-1950462.pdf


![DWM1001 Dev Kit](dwm1001.jpg)

![DWN network](qorvo_network.jpg)

## Getting started with RIOT

```bash
PROGRAMMER=openocd make BOARD=dwm1001 -C examples/hello-world flash
```
