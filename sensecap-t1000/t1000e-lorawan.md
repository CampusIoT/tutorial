# Seeedstudio SenseCAP T1000-E LoRaWAN

* https://www.seeedstudio.com/SenseCAP-Card-Tracker-T1000-E-for-LoRaWAN-p-6408.html
* https://wiki.seeedstudio.com/get_started_with_lorawan_tracker/



## Serial console

```bash
tio -b 115200 -m INLCRNL /dev/tty.usbmodemXXX
```

## SEEGER Studio

https://www.segger.com/downloads/embedded-studio/

## Custom firmwares

* https://github.com/Seeed-Studio/Seeed-Tracker-T1000-E-for-LoRaWAN-dev-board
* https://github.com/Seeed-Studio/Seeed-Tracker-T1000-E-for-LoRaWAN-dev-board/tree/main/apps/examples
* https://github.com/Seeed-Studio/Seeed-Tracker-T1000-E-for-LoRaWAN-dev-board/tree/main/firmware


    00_blinky - Led flash

    01_button - Print button event

    02_buzzer - Loop play sound

    03_sensor - Print temp/lux/battery value

    04_accelerometer - Print ax/ay/az/event value

    05_gnss - Print latitude/longitude value

    06_lorawan - Join through OTAA, send test data to LNS

    07_lorawan_sensor - Join through OTAA, read temp/lux/bat/ax/ay/az, send data to LNS

    08_lorawan_gnss - Join through OTAA, scan lat/lon, send data to LNS

    09_lorawan_wifi - Join through OTAA, scan WiFi MAC, send data to LNS

    10_lorawan_beacon - Join through OTAA, scan Beacon MAC, send data to LNS

    11_lorawan_tracker - Join through OTAA, scan GNSS/Wifi/Beacon, send data to LNS, config parameter through SenseCAP APP
