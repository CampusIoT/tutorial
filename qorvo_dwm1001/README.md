# Qorvo DWM1001

Ultra WideBand (UWB) is one of the technologies for indoor [Real-time locating systems (RTLS)](https://en.wikipedia.org/wiki/Real-time_locating_system) with centimeter accuracy. Ultra WideBand (UWB) measures how long it takes for a radio wave to get from the asset to the anchor or reference point. This is called time of flight (TOF). [more](https://www.pozyx.io/pozyx-academy/how-does-ultra-wideband-work).

Applications of indoor RTLS are : robotics/cobotics, industry 4.0 (smart factory), smart building maintenance, worker safety (danger zone alert), flying drone swarm's indoor positioning, sports, disable persons (Alzeimler), hospital (nursing trolley, stretcher, wheelchair ...) , entertaiment ([actors positioning](https://eliko.tech/case-study/tracking-actors-at-puy-du-fou-theme-park-in-france/) ...) RC car ...

The Qorvo/Decawave DWM1001 development board includes a DWM1001 module which is based on a Nordic nRF51832 microcontroller. This microcontroller is an ARM Cortex-M4 with 64KB of RAM and 512KB of flash memory. It also provides in integrated BLE radio. The DWM1001 module also contains an Ultra Wide Band transceiver for indoor ranging and geolocation.

https://www.mouser.fr/datasheet/2/412/DWM1001_DEV_Data_Sheet-1950462.pdf

![DWM1001 Dev Kit](dwm1001.jpg)

![DWN network](qorvo_network.jpg)

## Getting started

* https://www.qorvo.com/products/p/DWM1001-DEV#documents

* [DWM1001 Gateway Quick Deployment Guide](https://www.qorvo.com/products/d/da007973)
* [DWM1001 Firmware API Guide](https://www.qorvo.com/products/d/da007975)

* [Raspberry Pi 3B Image for DWM1001C](https://www.qorvo.com/extra/pim/da008480/DRTLS_raspbian_R2.0.zip)
* [Android Application (APK file)](https://www.qorvo.com/products/d/da007984)
* [DWM1001C Software and Documentation Pack](https://www.qorvo.com/products/d/da008479)

* [DW1000 Metrics for Estimation of NLOS Operating Conditions (Application Note APS006 Part 3) Rev 1.1 – 2016](https://www.qorvo.com/products/d/da008442)

### UART Shell

See Chapter 6 of [DWM1001 Firmware API Guide](https://www.qorvo.com/products/d/da007975):

Shell mode shares UART interface with Generic mode. DWM1001 starts by default in UART Generic
mode after reset. The Shell mode can be switched to by pressing ENTER twice within 1 second. The
Generic mode can be switched to by executing command “quit” when in Shell mode. Shell mode and
Generic mode can be switched back and forth.
Enter the Shell command and press “Enter” to execute the command. Press “Enter” without any
command in Shell mode to repeat the last command. The following sub-sections provides overview
of the Shell commands.

```
dwm> ?
Usage: <command> [arg0] [arg1]
Build-in commands:
** Command group: Base **
?: this help
help: this help
quit: quit
** Command group: GPIO **
gc: GPIO clear
gg: GPIO get
gs: GPIO set
gt: GPIO toggle
** Command group: SYS **
f: Show free memory on the heap
ps: Show running threads
pms: Show PM tasks
reset: Reboot the system
si: System info
ut: Show device uptime
frst: Factory reset
** Command group: SENS **
twi: General purpose TWI read
aid: Read ACC device ID
av: Read ACC values
** Command group: LE **
les: Show meas. and pos.
lec: Show meas. and pos. in CSV
lep: Show pos. in CSV
** Command group: UWBMAC **
nmg: Get node mode
nmp: Set mode to PN (passive)
nmo: Set mode to PN (off)
nma: Set mode to AN
nmi: Set mode to AIN
nmt: Set mode to TN
nmtl: Set mode to TN-LP
bpc: Toggle BW/TxPWR comp
la: Show AN list
stg: Get stats
stc: Clear stats
** Command group: API **
tlv: Send TLV frame
aurs: Set upd rate
aurg: Get upd rate
apg: Get pos
aps: Set pos
acas: Set anchor config
acts: Set tag config
** Tips **
Press Enter to repeat the last command
```

## Getting started with RIOT

* https://github.com/RIOT-OS/RIOT/blob/master/boards/dwm1001/doc.txt
* https://github.com/RIOT-OS/RIOT/blob/master/examples/twr_aloha/README.md

```bash
PROGRAMMER=openocd make BOARD=dwm1001 -C examples/hello-world flash
PROGRAMMER=openocd make BOARD=dwm1001 -C examples/twr_aloha flash
```


## Getting started with Zephyr

* https://github.com/RT-LOC/zephyr-dwm1001
* https://github.com/foldedtoad/dwm1001

## Getting started with Apache MyNewT

* https://github.com/Decawave/uwb-core

## Getting started with Arduino

https://github.com/thotro/arduino-dw1000

## Getting started with ROS

* https://forum.qorvo.com/t/robot-localization-using-dwm1001-for-ros-2/11992
* https://github.com/TIERS/ros-dwm1001-uwb-localization
* https://repositorio-aberto.up.pt/bitstream/10216/145742/2/593212.pdf
* https://researchrepository.wvu.edu/cgi/viewcontent.cgi?article=12337&context=etd
* https://github.com/TIERS/uwb-drone-dataset/blob/master/ros_nodes/dwm1001_interface/src/dwm1001_apiCommands.py
* 
## References
* https://www.pozyx.io/pozyx-academy/how-does-ultra-wideband-work
* https://github.com/Decawave
* https://github.com/Decawave/dwm1001-examples
* https://github.com/TIERS/dwm1001-uwb-firmware
* https://medium.com/garage-inside-garage/getting-started-with-ultra-wide-band-3d-positioning-dwm1000-and-dwm1001-modules-ba2f64e572b6
* https://developer.nordicsemi.com/nRF_Connect_SDK/doc/1.9.1/zephyr/boards/arm/decawave_dwm1001_dev/doc/index.html
* https://github.com/bsppbep/DWM1001-DEV
* https://github.com/TIERS/uwb-drone-dataset
* https://github.com/TIERS/dynamic-uwb-firmware
* https://github.com/TIERS/active-passive-uwb-ros
* https://github.com/TIERS/uwb-collaborative-sensing

### Video
* [MDEK Quick Start Guide](https://www.youtube.com/watch?v=hI8EaU5nOmI) 
* https://www.youtube.com/watch?v=emjC0HYd5gE
* https://www.youtube.com/watch?v=zA27p0Pj30U
* https://www.youtube.com/watch?v=6CNfgOF7ZPk
* [RC Car indoor positionning](https://www.youtube.com/watch?v=-JsLYsDf_n0)
* [Drone outdoor positionning](https://www.youtube.com/watch?v=mVLj2kUZXe0)
* [Drone indoor positionning](https://www.youtube.com/watch?v=7s3HGcX9zEw&t=321s)
* [Drone indoor positionning](https://www.youtube.com/watch?v=FVa_on1S_gg)
   
### PCB
* [DWM1001-DEV Schematic](https://www.qorvo.com/products/d/da007979)
* https://oshwlab.com/iforce2d/dwm1000-pro-mini

### Enclosures
* [DWM1001-DEV enclosures](https://gitlab.com/Inria-Chile/Atelier-Inria/dwm-rtls/-/tree/master/enclosures)

