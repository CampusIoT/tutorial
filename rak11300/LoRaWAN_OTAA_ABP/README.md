# Arduino BSP's for WisBlock RAK11300

## Install Arduino BSP

https://github.com/RAKWireless/RAKwireless-Arduino-BSP-Index

Copy https://raw.githubusercontent.com/RAKwireless/RAKwireless-Arduino-BSP-Index/main/package_rakwireless_index.json and paste it into the `File > Preferences > Additional Boards Manager URLs`.

Search `RAK11300` into `Tools > Board > Boards Manager` and Install BSP.

Select `RAK11300` into `Tools > Board > RAKwireless RP Boards`

Select the serial port;

## Select board

Turn Pico in UF2 mode : leave Boot button pressed while plug the USB connector.

Build and upload the shetck

Open the Serial console (Baudrate 115200): 

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