# Arduino BSP's for WisBlock RAK11300

## Install Arduino BSP

https://github.com/RAKWireless/RAKwireless-Arduino-BSP-Index

Copy https://raw.githubusercontent.com/RAKwireless/RAKwireless-Arduino-BSP-Index/main/package_rakwireless_index.json and paste it into the `File > Preferences > Additional Boards Manager URLs`.

Search `RAK11300` into `Tools > Board > Boards Manager` and Install BSP.

Select `RAK11300` into `Tools > Board > RAKwireless RP Boards`

Select the serial port;

## Build, Upload and Run

Turn Pico in UF2 mode : leave Boot button pressed while plug the USB connector (Note: remove the battery connector if it is plugged).

Build and upload a sketch from `File > Examples > Examples for Wisblock RAK11300` fitting with your sensors and your future application. Have a glance at [IO](https://github.com/RAKWireless/RAK-RP-Arduino/tree/main/libraries/RAK_examples/examples/RAK11300/IO), [Solutions](https://github.com/RAKWireless/RAK-RP-Arduino/tree/main/libraries/RAK_examples/examples/RAK11300/Solutions) and [Sensors](https://github.com/RAKWireless/RAK-RP-Arduino/tree/main/libraries/RAK_examples/examples/RAK11300/Sensors).

Open the Serial console (Baudrate `115200`).


## Battery level

Open, Build and Upload the skeich `File > Examples > Examples for Wisblock RAK11300 > RAK11300 Read Battery Level`

```
=====================================
RAK11300 Battery test
=====================================
The ADC value is:2772
The battery voltage is: 4124.39 V
The ADC value is:2795
The battery voltage is: 4158.61 V
LIPO = 4158.61 mV (93%)  Battery 239
The ADC value is:2894
The battery voltage is: 4305.91 V
LIPO = 4305.91 mV (115%)  Battery 39
The ADC value is:2759
The battery voltage is: 4105.05 V
LIPO = 4105.05 mV (85%)  Battery 218
...
```


