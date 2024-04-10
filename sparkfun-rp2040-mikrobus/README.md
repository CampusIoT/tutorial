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

Push Boot button when plug the USB cable in order to set the board in `boot` mode.

```bash
cd ~/github/RIOT-OS/RIOT/tests/leds
if [ "$(uname)" == "Darwin" ]; then
ELF2UF2_MOUNT_PATH=/Volumes/RPI-RP2 make BOARD=rpi-pico flash
else
make BOARD=rpi-pico flash
fi
```

## References

* https://learn.sparkfun.com/tutorials/rp2040-mikrobus-development-board-hookup-guide
* https://github.com/raspberrypi/pico-examples
* https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-python-sdk.pdf
* https://www.raspberrypi.com/documentation/microcontrollers/micropython.html
* https://docs.edgeimpulse.com/docs/development-platforms/officially-supported-mcu-targets/raspberry-pi-rp2040


## For SX1280 Lambda80 Module

```h
#if BOARD_RPI2040_SPARKFUN == 1

/*
    GPIO 02: SCK
    GPIO 03: MOSI (COPI)
    GPIO 04: MISO (CIPO)
    GPIO 05: CS

    GPIO 06: SDA
    GPIO 07/23: SCL

    GPIO 0: TX
    GPIO 01: RX

    GPIO 13: RST
    GPIO 16: PWM
    GPIO 17: INT
    GPIO 26: AN

*/
// SPI
#define PIN_SPI_MISO  (4u)
#define PIN_SPI_MOSI  (3u)
#define PIN_SPI_SCK   (2u)
    
#define NSS       5                                   //select pin on LoRa device
#define SCK       2                                  //SCK on SPI3
#define MISO      3                                  //MISO on SPI3 
#define MOSI      4                                  //MOSI on SPI3 

#define AN_0      26
#define RESET_0   13
#define PWM_0     16
#define INT_0     17

#if defined(MODULE_SX1280_LAMBDA80)

/*
Lambda80C module
AN  <-> DIO1
INT <-> Busy
PWM <-> DIO2
*/
#define DIO1  AN_0                                //DIO1 pin on LoRa device, used for RX and TX done 
//#define DIO2  PWM_0                               //DIO2 pin on LoRa device, normally not used so set to -1 
#define DIO2  -1                                //DIO2 pin on LoRa device, normally not used so set to -1 
#define RFBUSY  INT_0                               //busy line
#define NRESET  RESET_0                     //reset pin on LoRa device

#else
#error Unknown module
#endif

#else
#error Unknown board
#endif
```
