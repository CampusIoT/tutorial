# Semtech LR1120 :: LoRa transceiver + GNSS/Wifi Sniffer

''The [LR1120](https://fr.semtech.com/products/wireless-rf/lora-edge/lr1120) is an ultra-low power device targeting global geolocation applications. It provides multi band LoRa® and Long Range - Frequency Hopping Spread Spectrum (LR-FHSS) communication over sub-GHz and 2.4GHz Industrial, Scientific and Medical (ISM) bands as well as licensed S-Band for satellites. It integrates a Cloud-native multi-constellation global navigation satellite system (GNSS) scanner and a passive Wi-Fi MAC address scanner, both leveraging Semtech’s LoRa Cloud™ services.''


Check the model of your LR1120 shield. Mine is [`LR1120MB1DIS` (868 MHz for the SubGhz interface)](https://fr.semtech.com/products/wireless-rf/lora-edge/lr1120dvk1tcks)

But we have designed this [Mikrobus board for LR1120](https://github.com/thingsat/lr1120_mikrobus/tree/main?tab=readme-ov-file#semtech-lr1120-mikrobus-board)

Two Github repositories are available:
* [SWSD003: LR11xx SDK](https://github.com/Lora-net/SWSD003)
* [SWSD001: LoRa Basics Modem SDK](https://github.com/Lora-net/SWSD001)


![LR1120MB1DIS](LR1120MB1DIS.jpg)

## Setup SWSD003 LR11xx SDK

`arm-none-eabi-gcc` suite should .be installed.

```bash
mkdir -p github/lora-net
cd github/lora-net/
git clone https://github.com/Lora-net/SWSD003
cd SWSD003/
```

## Console

Open the serial console of the Nucleo board

```bash
brew install tio
tio -L
tio -b 921600 -m INLCRNL /dev/tty.usbmodem142xxx
```

## Demonstrations SWSD003

Change default configuration into [`../common/apps_configuration.h`](../common/apps_configuration.h)

For instance :
```c
#define RF_FREQ_IN_HZ 868300000U
...
#define LORA_SYNCWORD 0x34  // 0x12 Private Network, 0x34 Public Network
```

### [Ping Pong](https://github.com/Lora-net/SWSD003/tree/master/lr11xx/apps/ping_pong)

The application will automatically set the device in Ping-Pong mode.

```bash
cd apps/ping_pong/
cd makefile/
make RADIO_SHIELD=LR1120MB1DIS
cp build/ping_pong.bin  /Volumes/NODE_L476RG/
```

### [LR-FHSS](https://github.com/Lora-net/SWSD003/tree/master/lr11xx/apps/lrfhss)

The application will automatically configure the device to transmit packets in LR-FHSS.

```bash
cd apps/lrfhss/
cd makefile/
make RADIO_SHIELD=LR1120MB1DIS
cp build/lrfhss.bin  /Volumes/NODE_L476RG/
```
### [CAD (Collision Avoidance Detection)](https://github.com/Lora-net/SWSD003/tree/master/lr11xx/apps/cad)

The chip performs the CAD operation in LoRa.

```bash
cd apps/cad/
cd makefile/
make RADIO_SHIELD=LR1120MB1DIS
cp build/cad.bin  /Volumes/NODE_L476RG/
```

### [sub-GHz band LoRa based Round-Trip Time of Flight (ranging)](https://github.com/Lora-net/SWSD003/tree/master/lr11xx/apps/rttof)

The sample code is used to perform a sub-GHz band LoRa based Round-Trip Time of Flight (ranging) measurement between two devices : a RTToF manager and a RTToF subordinate. 

```bash
cd apps/rttof/
cd makefile/
make RADIO_SHIELD=LR1120MB1DIS
cp build/rttof.bin  /Volumes/NODE_L476RG/
```
###  [Spectral scan](https://github.com/Lora-net/SWSD003/tree/master/lr11xx/apps/spectral_scan)

The application implements Spectral-Scan operation by setting the device in Rx continuous mode and regularly reading instantaneous RSSI one frequency channel after the other.

```bash
cd apps/spectral_scan/
cd makefile/
make RADIO_SHIELD=LR1120MB1DIS
cp build/spectral_scan.bin  /Volumes/NODE_L476RG/
```

### [Spectrum Display](https://github.com/Lora-net/SWSD003/tree/master/lr11xx/apps/spectrum_display)

The application implements Spectrum-Display operation by setting the device in Rx continuous mode and regularly reading instantaneous RSSI one frequency channel after the other.


### Wifi Scan

The application executes Wi-Fi Scans in a loop.
The Wi-Fi scans can be the following:
- Wi-Fi passive scan
- Wi-Fi passive scan time limit
- Wi-Fi passive scan country code
- Wi-Fi passive scan country code time limit

It prints results on the serial line on every scan termination.

First, change the WIFI_DEMO_TO_RUN macro in `main_wifi.h`.

```c
/**
 * @brief Selection of the demo to run.
 *
 * It must be one of wifi_demo_to_run_t enumeration :
 *  WIFI_SCAN,
 *  WIFI_SCAN_TIME_LIMIT,
 *  WIFI_SCAN_COUNTRY_CODE,
 *  WIFI_SCAN_COUNTRY_CODE_TIME_LIMIT
 */
#define WIFI_DEMO_TO_RUN ( WIFI_SCAN_TIME_LIMIT )

/**
 * @brief Wi-Fi channels to scan
 *
 * It is expressed as 16 bits mask of channels
 * 
 * 0x0421 = channels 1 - 6 - 11
 */
#define WIFI_CHANNEL_MASK ( 0x0421 )

/**
 * @brief Wi-Fi result formats
 *
 * Must be one of lr11xx_wifi_result_format_t
 *
 * @warning The possible value depends on the value provided in WIFI_SCAN_MODE:
 * WIFI_RESULT_FORMAT can be:
 *   - LR11XX_WIFI_RESULT_FORMAT_BASIC_COMPLETE or LR11XX_WIFI_RESULT_FORMAT_BASIC_MAC_TYPE_CHANNEL if WIFI_SCAN_MODE
 * is:
 *       - LR11XX_WIFI_SCAN_MODE_BEACON or
 *       - LR11XX_WIFI_SCAN_MODE_BEACON_AND_PKT
 *   - LR11XX_WIFI_RESULT_FORMAT_EXTENDED_FULL if WIFI_SCAN_MODE is:
 *       - LR11XX_WIFI_SCAN_MODE_FULL_BEACON or
 *       - LR11XX_WIFI_SCAN_MODE_UNTIL_SSID
 */
#define WIFI_RESULT_FORMAT ( LR11XX_WIFI_RESULT_FORMAT_BASIC_COMPLETE )
```

> About [Wifi channels](https://en.wikipedia.org/wiki/List_of_WLAN_channels)

Build and flash the firmware

```bash
cd apps/wifi/
cd makefile/
make RADIO_SHIELD=LR1120MB1DIS
cp build/wifi.bin  /Volumes/NODE_L476RG/
```

```console
INFO: ===== LR11xx Wi-Fi passive scan time limit example =====

INFO: LR11xx information:
INFO:   - Firmware = 0x0101
INFO:   - Hardware = 0x22
INFO:   - Type     = 0x02 (0x01 for LR1110, 0x02 for LR1120)

Wi-Fi example configuration:
  -> channel mask: 0x0421
  -> max result: 10
  -> scan mode: LR11XX_WIFI_SCAN_MODE_BEACON
  -> signal type: LR11XX_WIFI_TYPE_SCAN_B
  -> timeout per channel: 1000
  -> timeout per scan: 90
  -> max number of scan: 0

INFO: Interrupt flags = 0x00100000
INFO: Interrupt flags (after filtering) = 0x00100000
INFO: Wi-Fi scan done
== Scan #1 ==
Cummulative timings:
  -> Demodulation: 27267 us
  -> Capture: 12029 us
  -> Correlation: 736934 us
  -> Detection: 0 us
  => Total : 776230 us

Result 1/2
  -> MAC address: xx:xx:xx:xx:bf:c0
  -> Channel: LR11XX_WIFI_CHANNEL_1
  -> MAC origin: From gateway
  -> Signal type: LR11XX_WIFI_TYPE_RESULT_B
  -> Frame type: LR11XX_WIFI_FRAME_TYPE_MANAGEMENT
  -> Frame sub-type: 0x08
  -> FromDS/ToDS: false / false
  -> Phi Offset: -2461
  -> Timestamp: 64 us
  -> Beacon period: 100 TU

Result 2/2
  -> MAC address: xx:xx:xx:xx:9a:3f
  -> Channel: LR11XX_WIFI_CHANNEL_6
  -> MAC origin: From gateway
  -> Signal type: LR11XX_WIFI_TYPE_RESULT_B
  -> Frame type: LR11XX_WIFI_FRAME_TYPE_MANAGEMENT
  -> Frame sub-type: 0x08
  -> FromDS/ToDS: false / false
  -> Phi Offset: -1567
  -> Timestamp: 64 us
  -> Beacon period: 100 TU

```


###  GNSS

The application executes GNSS scans in a loop. It prints results on the serial line on every scan termination.

The GNSS assisted example needs the almanac to be up-to-date. If the almanacs are too old, the LR11xx chip is likely to detect less Satellite Vehicles. And if the almanacs are older than three months the LR11xx chip will not start a scanning operation and will return an error result `00 08` indicating the scan was not attempt because the almanacs are too old.

To update the almanacs consider using the [LR1110 EVK Demo Application](https://github.com/Lora-net/lr1110_evk_demo_app) and the python program `AlmanacUpdate` as described [here](https://github.com/Lora-net/lr1110_evk_demo_app#almanacupdate-usage). This process can be followed for both LR1110 and LR1120.


Change the [assistance position](https://www.openstreetmap.org/search?query=LIG%20grenoble#map=19/45.19030/5.76679) into `main_gnss.h`

```c
/**
 * @brief Assistance position latitude
 */
#define GNSS_ASSISTANCE_POSITION_LATITUDE ( 45.19030 )

/**
 * @brief Assistance position longitude
 */
#define GNSS_ASSISTANCE_POSITION_LONGITUDE ( 5.76679 )
```


```bash
cd apps/gnss/gnss_autonomous/
cd makefile/
make RADIO_SHIELD=LR1120MB1DIS
cp build/gnss.bin  /Volumes/NODE_L476RG/
```

```bash
cd apps/gnss/gnss_assisted/
cd makefile/
make RADIO_SHIELD=LR1120MB1DIS
cp build/gnss.bin  /Volumes/NODE_L476RG/
```


## Setup SWSD001 LoRa Basics Modem SDK

```bash
mkdir -p github/lora-net
cd github/lora-net/
git clone https://github.com/Lora-net/SWSD001
cd SWSD001/
```

##  Demonstations SWSD001 LoRa Basics Modem SDK

### Endpoint registration

Register the endpoint on your LoRaWAN Network Server (ie Chirpstack, TTN, Orange Liveobject ...) with:

```
DevEUI 1010101010123456
JoinEUI 10101010101FFFFF
AppKey 101010101012345610101010101FFFFF
```

### Application server setup

Start a Node-RED server and deploy the following flow : https://github.com/Lora-net/SWSD001/tree/master/apps/examples/application_server


```bash
cd SWSD001/
cd apps/examples/application_server
cp modem.json flows.json
npm install @semtech-wsp-apps/node-red-contrib-loracloud-utils
docker run -it -p 1880:1880 -v $PWD:/data --name app_nodered nodered/node-red:latest-minimal
```

Browse the Nodered console http://localhost:1880

### LoRaWAN class A endpoint

```bash
cd apps/examples/lorawan/
cd makefile/
gmake RADIO_BOARD=LR1120MB1DJS CRYPTO=SOFT EXTRAFLAGS='-DLORAWAN_DEVICE_EUI=\{0x10,0x10,0x10,0x10,0x10,0x12,0x34,0x56\} -DLORAWAN_JOIN_EUI=\{0x10,0x10,0x10,0x10,0x10,0x1F,0xFF,0xFF\} -DLORAWAN_APP_KEY=\{0x10,0x10,0x10,0x10,0x10,0x12,0x34,0x56,0x10,0x10,0x10,0x10,0x10,0x1F,0xFF,0xFF\} -DLORAWAN_APP_PORT=10 -DLORAWAN_CONFIRMED_MSG_ON=true -DAPP_TX_DUTYCYCLE=15'
cp build/lorawan.bin  /Volumes/NODE_L476RG/
```

Decode the payload by registering the decoder:

```javascript

// TODO

```


From the device console, enqueue a downlink with `base64` is `SGVsbG8gV29ybGQK` ('Hello World') and `port` is `22`.

```console
INFO: Request uplink
 User Tx LORa on FPort 10 

  *************************************
  * Send Payload  HOOK ID = 3
  *************************************
  Tx  LoRa at 86950 ms: freq:868300000, SF7, BW125, len 17 bytes 0 dBm, fcnt_up 9, toa = 52

  *************************************
  *  TX DONE
  *************************************

  Open RX1 for Hook Id = 3  RX1 LoRa at 87997 ms: freq:868300000, SF7, BW125, sync word = 0x34
  Timer will expire in 993 ms
 rx_packet_type = 1

  *************************************
  * Receive a Valid downlink RX1 for Hook Id = 3
  *************************************
Downlink frame  - (12 bytes):
 48 65 6C 6C 6F 20 57 6F 72 6C 64 0A
DL Port = 22 , DL SNR = 52 , DL RSSI = -33 , DL Freq = 868300000 , DL DR = 5 , DL Fpending Bit = 0 
INFO: ###### ===== TX DONE EVENT ==== ######
TX Done status: SMTC_MODEM_EVENT_TXDONE_CONFIRMED
INFO: Uplink count: 4
INFO: ###### ===== DOWNLINK EVENT ==== ######
Rx window: SMTC_MODEM_EVENT_DOWNDATA_WINDOW_RX1
Rx port: 22
Rx RSSI: -97
Rx SNR: 13
INFO: Downlink received:
INFO:   - LoRaWAN Fport = 22
INFO:   - Payload size  = 12
INFO:   - RSSI          = -97 dBm
INFO:   - SNR           = 13 dB
INFO:   - Rx window     = SMTC_MODEM_EVENT_DOWNDATA_WINDOW_RX1
Payload - (12 bytes):
 48 65 6C 6C 6F 20 57 6F 72 6C 64 0A
 ```



### Time sync (RTC)

This example demonstrates the synchronization of the endpoint's RTC according to the [App Clock Sync specification](https://lora-alliance.org/resource_hub/lorawan-application-layer-clock-synchronization-specification-v1-0-0/)

```bash
cd apps/examples/time_sync/
cd makefile/
gmake RADIO_BOARD=LR1120MB1DJS CRYPTO=SOFT EXTRAFLAGS='-DLORAWAN_DEVICE_EUI=\{0x10,0x10,0x10,0x10,0x10,0x12,0x34,0x56\} -DLORAWAN_JOIN_EUI=\{0x10,0x10,0x10,0x10,0x10,0x1F,0xFF,0xFF\} -DLORAWAN_APP_KEY=\{0x10,0x10,0x10,0x10,0x10,0x12,0x34,0x56,0x10,0x10,0x10,0x10,0x10,0x1F,0xFF,0xFF\} -DLORAWAN_APP_PORT=10 -DLORAWAN_CONFIRMED_MSG_ON=true -DAPP_TX_DUTYCYCLE=15'
cp build/time_sync.bin  /Volumes/NODE_L476RG/
```

Some LNS (such as Chirpstack) intercept [App Clock Sync](https://lora-alliance.org/resource_hub/lorawan-application-layer-clock-synchronization-specification-v1-0-0/) messages (`fport=199`) and reply with downlink messages. 

if the LNS supports [App Clock Sync](https://lora-alliance.org/resource_hub/lorawan-application-layer-clock-synchronization-specification-v1-0-0/), the trace looks like this:
```console
INFO: Application parameters:
INFO:   - Time synchronization service = SMTC_MODEM_TIME_MAC_SYNC
INFO:   - Automatic time synchronization interval = 900 s
INFO:   - Manual time synchronization interval = 130 s

...

  *************************************
  * Receive a Valid downlink RX1 for Hook Id = 3
  *************************************
Cmd device_time_ans_parser = b6 bc 49 50 51
SecondsSinceEpoch 1347009718, FractionalSecond 316
INFO: ###### ===== TIME EVENT ==== ######
Time: SMTC_MODEM_EVENT_TIME_VALID
INFO: Checking/printing local UTC time upon TIME reception
INFO: Current UTC time: Mon 2022-09-12 09:21:41 GMT
```


### LoRaWAN application sending asynchronous uplinks

```bash
cd apps/examples/lorawan/
cd makefile/
gmake RADIO_BOARD=LR1120MB1DJS CRYPTO=SOFT EXTRAFLAGS='-DLORAWAN_DEVICE_EUI=\{0x10,0x10,0x10,0x10,0x10,0x12,0x34,0x56\} -DLORAWAN_JOIN_EUI=\{0x10,0x10,0x10,0x10,0x10,0x1F,0xFF,0xFF\} -DLORAWAN_APP_KEY=\{0x10,0x10,0x10,0x10,0x10,0x12,0x34,0x56,0x10,0x10,0x10,0x10,0x10,0x1F,0xFF,0xFF\} -DLORAWAN_APP_PORT=10 -DLORAWAN_CONFIRMED_MSG_ON=true -DAPP_TX_DUTYCYCLE=15'
cp build/gnss.bin  /Volumes/NODE_L476RG/
```

```console
INFO: Use soft secure element for cryptographic functionalities

INFO: ###### ===== LoRa Basics Modem LoRaWAN Class A/C asynchronous demo application ==== ######

INFO: SDK version: v2.0.0
INFO: LoRaWAN version: 01.00.04.01
INFO: LoRa Basics Modem version: 03.02.04

```

### LoRaWAN application sending asynchronous LR-FHSS uplinks

This example requires LNS and gateways supporting LR-FHSS uplinks.

The ADR should enable LR-FHSS datarates DR8 and DR11 (see [Table 8 of section 2.4.3 in RP002-1.0.3 LoRaWAN® Regional Parameters](https://lora-alliance.org/wp-content/uploads/2021/05/RP002-1.0.3-FINAL-1.pdf))

```bash
cd apps/examples/lorawan_asynchronous/
cd makefile/
gmake RADIO_BOARD=LR1120MB1DJS CRYPTO=SOFT EXTRAFLAGS='-DLORAWAN_DEVICE_EUI=\{0x10,0x10,0x10,0x10,0x10,0x12,0x34,0x56\} -DLORAWAN_JOIN_EUI=\{0x10,0x10,0x10,0x10,0x10,0x1F,0xFF,0xFF\} -DLORAWAN_APP_KEY=\{0x10,0x10,0x10,0x10,0x10,0x12,0x34,0x56,0x10,0x10,0x10,0x10,0x10,0x1F,0xFF,0xFF\} -DLORAWAN_APP_PORT=10 -DLORAWAN_CONFIRMED_MSG_ON=true -DAPP_TX_DUTYCYCLE=15'
cp build/lorawan_asynchronous.bin  /Volumes/NODE_L476RG/
```

```console

INFO: Use soft secure element for cryptographic functionalities

INFO: ###### ===== LoRa Basics Modem LoRaWAN LR-FHSS asynchronous demo application ==== ######

INFO: SDK version: v2.0.0
INFO: LoRaWAN version: 01.00.04.01
INFO: LoRa Basics Modem version: 03.02.04

....


  *************************************
  * RX2 Timeout for Hook Id = 3
  *************************************
INFO: ###### ===== NEW LINK ADR EVENT ==== ######
WARN: No LR-FHSS datarates are available
```

### LoRa Basics Modem LoRaWAN Class B example

```bash
cd lorawan_class_b
TODO
```

### LoRa Basics Modem LoRaWAN Class C device with multicast
```bash
cd lorawan_multicast_class_c
TODO
```

### LoRa Basics Modem LoRaWAN Class B device with multicast
```bash
cd lorawan_multicast_class_b
TODO
```

## Other examples

```
almanac_update
application_server
dm_info
full_almanac_update
large_file_upload
stream
tx_rx_continuous
cad
lrfhss
spectrum_display
```

## TODO
* [ ] LoRa 2.4 GHz emitter / receiver
* [ ] LoRa 2.4 GHz ranging
* [ ] SBand SatCom

