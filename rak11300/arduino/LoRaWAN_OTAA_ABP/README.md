# WisBlock RAK11300 :: LoRaWAN communications

[Install Arduino BSP](../README.md) 

## Build, Upload and Run

Build and upload the sketch.

Open the Serial console (Baudrate `115200`).

```
=====================================
Welcome to RAK11300 LoRaWan!!!
Type: OTAA
Region: EU868
=====================================
DevEUI: AC1F9FFFE6B96A
AppEUI: 00000000
AppKey: 3C2A813B72E53FD0662C5BB480E87B41
OTAA join failed!
Check your EUI's and Keys's!
Check if a Gateway is in range!
```

Register the device onto your favorite LNS with `DevEUI`, `AppEUI` and `AppKey`. The payload decoder is [here](./decoder.js)

Reset the board for rebooting.

```
=====================================
Welcome to RAK11300 LoRaWan!!!
Type: OTAA
Region: EU868
=====================================
DevEUI: AC1F9FFFE6B96A
AppEUI: 00000000
AppKey: 3C2A813B72E53FD0662C5BB480E87B41
OTAA Mode, Network Joined with devAddr FC00ACD1
NwkSkey: 76CD80F6914730D6CC97A339A95AEC1
AppSkey: 69D8FEBC60D3B05D8128F7A910EAD4C
Send now
send_lora_frame : enter
send_lora_frame : lmh_send
lmh_send ok count 1
TX finished
Send now
send_lora_frame : enter
send_lora_frame : lmh_send
lmh_send ok count 2
TX finished
LoRa Packet received on port 10, size:6, rssi:-53, snr:14, data:HELLO


```

## ToDoList

* [ ] add last Downlink RSSI and SNR into the Uplink text payload
* [ ] add LinkCheck
* [ ] print configured DR and TxPower
* [ ] retry progressively Join procedure with slower DRs and higher Tx Power.
* [ ] blink `LED_GREEN` and `LED_BLUE` when join, tx, rx ...
* [ ] add [GPS position](https://github.com/RAKWireless/WisBlock/blob/master/examples/RAK4630/solutions/GPS_Tracker/GPS_Tracker.ino) into the text message if GPS fixed
* [ ] add battery level. See sketches `File > Examples > Examples for Wisblock RAK11300 > RAK11300 Read Battery Level` and `File > Examples > Examples for Wisblock RAK11300 >  IO > RAK19006_WirelessCharger`
* [ ] format message according [AX25/APRS](https://github.com/thingsat/riot_modules/blob/main/apps/basic_mission/aprs.c)
* [ ] format message according Cayenne LPP