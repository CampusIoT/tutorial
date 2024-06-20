# AT Commands with Wio LoRa E5

[Specifications](https://files.seeedstudio.com/products/317990687/res/LoRa-E5%20AT%20Command%20Specification_V1.0%20.pdf)

* `<LF>` means the newline character. `<CR>` means carriage return
▪ Default UART configuration `"9600, 8, n,1"` (8 bits data, no parity, 1 stop bit)

```bash
brew install tio
tio -l
tio -b 9600 -m INLCRNL /dev/tty.usbXXX
```



```
2CF7F12024900138
+INFO: Input timeout
+ID: DevAddr, 32:30:84:63
+ID: DevEui, 2C:F7:F1:20:32:30:84:63
+ID: AppEui, 80:00:00:00:00:00:00:06

AT+ID
+ID: DevAddr, 24:90:01:38
+ID: DevEui, 2C:F7:F1:20:24:90:01:38
+ID: AppEui, 80:00:00:00:00:00:00:06

AT+MODE=LWOTAA

AT+KEY=APPKEY,1234567890ABCDEF1234567890ABCDEF

AT+DR

AT+JOIN

AT+MSG=HELLO

AT+MSGHEX=67020010

AT+MSGHEX=03670110056700FF
AT+MSGHEX=0167FFD7067104D2FB2E0000
AT+MSGHEX=018806765EF2960A0003E8

```

Cayenne LPP
* https://cayennelpp.eu/
* https://pypi.org/project/pycayennelpp/
* https://github.com/myDevicesIoT/CayenneLPP-Node
* https://packagist.org/packages/power-lan/cayenne-lpp

```

1: {
    gpsLocation : {
        latitude:42.3518,
        longitude:-87.9094,
        altitude:10
    }
}

+INFO: Input timeout
+ID: DevAddr, 24:90:01:38
+ID: DevEui, 2C:F7:F1:20:24:90:01:38
+ID: AppEui, 80:00:00:00:00:00:00:06

+INFO: Input timeout
+ID: DevAddr, 24:90:01:38

+INFO: Input timeout
+DR: DR0
+DR: EU868 DR0  SF12 BW125K 

+INFO: Input timeout
+MODE: LWABP

+INFO: Input timeout
+KEY: MANUAL

+INFO: Input timeout
+KEY: ERROR(-1)

+INFO: Input timeout
+MODE: ERROR(-12)

+INFO: Input timeout
+MODE: ERROR(-12)

+INFO: Input timeout
+MODE: LWOTAA

+INFO: Input timeout
+KEY: APPKEY 1234567890ABCDEF1234567890ABCDEF

+INFO: Input timeout
+ID: DevAddr, 24:90:01:38
+ID: DevEui, 2C:F7:F1:20:24:90:01:38
+ID: AppEui, 80:00:00:00:00:00:00:06

+INFO: Input timeout
+DR: DR0
+DR: EU868 DR0  SF12 BW125K 

+INFO: Input timeout
+JOIN: Start
+JOIN: NORMAL
+JOIN: Join failed
+JOIN: Done

+INFO: Input timeout
+JOIN: Start
+JOIN: NORMAL
+JOIN: Network joined
+JOIN: NetID C0002B DevAddr FC:00:AC:0B
+JOIN: Done

+INFO: Input timeout
+MSG: Start
+MSG: FPENDING
+MSG: RXWIN1, RSSI -101, SNR -16.0
+MSG: Done
```
