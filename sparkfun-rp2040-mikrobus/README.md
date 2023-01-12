# SparkFun RP2040 mikroBUS

[SparkFun RP2040 mikroBUS](https://www.sparkfun.com/products/18721) is a RP2040 board with 2 buttons, a RGB Led, a SD Card slot, a 16MB QSPI FlashRAM chip, a Mikrobus slot and a charging circuit for a LiPo battery ([Details](https://learn.sparkfun.com/tutorials/rp2040-mikrobus-development-board-hookup-guide/hardware-overview)).

## UF2 Booloader

https://learn.sparkfun.com/tutorials/rp2040-mikrobus-development-board-hookup-guide/uf2-bootloader

In normal mode
```bash
> lsusb
...
Bus 000 Device 004: ID 2e8a:0005 2e8a Board in FS mode  Serial: 000000000000
...
```

Push Boot button when plug the USB cable

In boot mode

```bash
> lsusb
...
Bus 000 Device 004: ID 2e8a:0003 2e8a RP2 Boot  Serial: E0C9125B0D9B
...
```

## Arduino

https://learn.sparkfun.com/tutorials/rp2040-mikrobus-development-board-hookup-guide/arduino-example

Install the `Arduino MBed OS RP2040 Boards`  through the Board Manager.

Open the `File > Examples > 01. Basics > Blink` sketch.

Compile and upload the `Blink` sketch.

The blue led blinks at 1 Hz


## C/C++ SDK
https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf

## Python SDK
https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-python-sdk.pdf

## RIOT OS
* https://doc.riot-os.org/group__boards__rpi__pico.html


## References

* https://learn.sparkfun.com/tutorials/rp2040-mikrobus-development-board-hookup-guide
* https://github.com/raspberrypi/pico-examples
* https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-python-sdk.pdf
* https://www.raspberrypi.com/documentation/microcontrollers/micropython.html
* https://docs.edgeimpulse.com/docs/development-platforms/officially-supported-mcu-targets/raspberry-pi-rp2040