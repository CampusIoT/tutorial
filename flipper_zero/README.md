# Flipper Zero

## Description
[Flipper Zero](https://flipperzero.one) is an useful endpoint with with 128x64 px LCD screen (ST7567), a SDCard slot, and multi Comm/RF interfaces : IrDA, BLE 5.4, NFC (ST25R3916), RFID 125KHz, SubGHz radio (CC1101), iButton ...) . An extension port enables for [prototyping extensions](https://shop.flipperzero.one/products/proto-boards).

The CPU model is a [STM32WB55RG](https://www.st.com/en/microcontrollers-microprocessors/stm32wb55rg.html) which it is partially supported by [RIOT](https://api.riot-os.org/group__boards__p-nucleo-wb55.html).


![Flipper Zero](./images/flipper_zero-01.jpg)

## Getting started

### [CLI](https://docs.flipper.net/development/cli)

Use `minicom`, `tio` or Putty with baudrate 230400 bps.

```bash
tio -b 230400 -m INLCRNL /dev/tty.usbmodemflip_Oldishol1
```

Or open https://lab.flipper.net/cli in Chrome

```console

              _.-------.._                    -,
          .-"```"--..,,_/ /`-,               -,  \ 
       .:"          /:/  /'\  \     ,_...,  `. |  |
      /       ,----/:/  /`\ _\~`_-"`     _;
     '      / /`"""'\ \ \.~`_-'      ,-"'/ 
    |      | |  0    | | .-'      ,/`  /
   |    ,..\ \     ,.-"`       ,/`    /
  ;    :    `/`""\`           ,/--==,/-----,
  |    `-...|        -.___-Z:_______J...---;
  :         `                           _-'
 _L_  _     ___  ___  ___  ___  ____--"`___  _     ___
| __|| |   |_ _|| _ \| _ \| __|| _ \   / __|| |   |_ _|
| _| | |__  | | |  _/|  _/| _| |   /  | (__ | |__  | |
|_|  |____||___||_|  |_|  |___||_|_\   \___||____||___|

Welcome to Flipper Zero Command Line Interface!
Read the manual: https://docs.flipper.net/development/cli
Run `help` or `?` to list available commands

Firmware version: 0.98.3 0.98.3 (8b19d32c built on 12-02-2024)

>: help
Commands available:
!                             led
?                             loader
bt                            log
crypto                        nfc
date                          onewire
device_info                   power
factory_reset                 ps
free                          rfid
free_blocks                   start_rpc_session
gpio                          storage
help                          subghz
i2c                           sysctl
ikey                          update
info                          uptime
input                         vibro
ir                            
>: nfc
Other application is running, close it first
>: date
2024-03-11 17:10:35 1
>: subghz
Usage:
subghz <cmd> <args>
Cmd list:
        chat <frequency:in Hz> <device: 0 - CC1101_INT, 1 - CC1101_EXT>  - Chat with other Flippers
        tx <3 byte Key: in hex> <frequency: in Hz> <te: us> <repeat: count> <device: 0 - CC1101_INT, 1 - CC1101_EXT>     - Transmitting key
        rx <frequency:in Hz> <device: 0 - CC1101_INT, 1 - CC1101_EXT>    - Receive
        rx_raw <frequency:in Hz>         - Receive RAW
        decode_raw <file_name: path_RAW_file>    - Testing
        tx_from_file <file_name: path_file> <repeat: count> <device: 0 - CC1101_INT, 1 - CC1101_EXT>     - Transmitting from file

>: gpio
Usage:
gpio <cmd> <args>
Cmd list:
        mode <pin_name> <0|1>    - Set gpio mode: 0 - input, 1 - output
        set <pin_name> <0|1>     - Set gpio value
        read <pin_name>  - Read gpio value

>: device_info
device_info_major             : 2
device_info_minor             : 4
hardware_model                : Flipper Zero
...
protobuf_version_major        : 0
protobuf_version_minor        : 22

>: input
Usage:
input <cmd> <args>
Cmd list:
        dump                     - dump input events
        send <key> <type>        - send input event

>: uptime
Uptime: 3h53m43s
>: vibro
vibro: illegal option -- 
usage: vibro <1|0>
>: vibro 1

>: vibro 0

>: ir
Usage:
        ir rx [raw]
        ir tx <protocol> <address> <command>
        <command> and <address> are hex-formatted
        Available protocols: NEC NECext NEC42 NEC42ext Samsung32 RC6 RC5 RC5X SIRC SIRC15 SIRC20 Kaseikyo RCA
        Raw format:
        ir tx RAW F:<frequency> DC:<duty_cycle> <sample0> <sample1>...
        Frequency (10000 - 56000), Duty cycle (0 - 100), max 512 samples
        ir decode <input_file> [<output_file>]
        ir universal <remote_name> <signal_name>
        ir universal list <remote_name>
        Available universal remotes: tv audio ac projector

>: storage
Usage:
storage <cmd> <path> <args>
The path must start with /int or /ext
Cmd list:
        info     - get FS info
        format   - format filesystem
        list     - list files and dirs
        tree     - list files and dirs, recursive
        remove   - delete the file or directory
        read     - read text from file and print file size and content to cli
        read_chunks      - read data from file and print file size and content to cli, <args> should contain how many bytes you want to read in block
        write    - read text from cli and append it to file, stops by ctrl+c
        write_chunk      - read data from cli and append it to file, <args> should contain how many bytes you want to write
        copy     - copy file to new file, <args> must contain new path
        rename   - move file to new file, <args> must contain new path
        mkdir    - creates a new directory
        md5      - md5 hash of the file
        stat     - info about file or dir
        timestamp        - last modification timestamp

>: storage info
Usage:
storage <cmd> <path> <args>
The path must start with /int or /ext
Cmd list:
        info     - get FS info
        format   - format filesystem
        list     - list files and dirs
        tree     - list files and dirs, recursive
        remove   - delete the file or directory
        read     - read text from file and print file size and content to cli
        read_chunks      - read data from file and print file size and content to cli, <args> should contain how many bytes you want to read in block
        write    - read text from cli and append it to file, stops by ctrl+c
        write_chunk      - read data from cli and append it to file, <args> should contain how many bytes you want to write
        copy     - copy file to new file, <args> must contain new path
        rename   - move file to new file, <args> must contain new path
        mkdir    - creates a new directory
        md5      - md5 hash of the file
        stat     - info about file or dir
        timestamp        - last modification timestamp

>: storage info /ext
Label: FLIPPER
Type: FAT32
15449088KiB total
15438336KiB free
74J` USD   v1.0
SN:401d0002 02/2017

>: storage info /int
Label: Oldishol
Type: LittleFS
228KiB total
204KiB free

>: power
Usage:
power <cmd> <args>
Cmd list:
        off      - shutdown power
        reboot   - reboot
        reboot2dfu       - reboot to dfu bootloader
        5v <0 or 1>      - enable or disable 5v ext

>: crypto
Usage:
crypto <cmd> <args>
Cmd list:
        encrypt <key_slot:int> <iv:hex>  - Using key from secure enclave and IV encrypt plain text with AES256CBC and encode to hex
        decrypt <key_slot:int> <iv:hex>  - Using key from secure enclave and IV decrypt hex encoded encrypted with AES256CBC data to plain text
        has_key <key_slot:int>   - Check if secure enclave has key in slot
        store_key <key_slot:int> <key_type:str> <key_size:int> <key_data:hex>    - Store key in secure enclave. !!! NON-REVERSABLE OPERATION - READ MANUAL FIRST !!!

>: 
```


## Project ideas

* CAN Bus commander
* LoRaWAN Field Test Device (LoRa SPI/UART module + GNSS UART/I2C module)
* Mikrobus x2 (SPI,I2C,UART) + Grove extension board

## References

* https://flipperzero.one
* https://github.com/flipperdevices/flipperzero-firmware
* [Awesome links](https://github.com/djsime1/awesome-flipperzero)

### PCBs

* [flipperzero-protoboards-kicad](https://github.com/lomalkin/flipperzero-protoboards-kicad)
* [Flipper-Zero-module-PCB](https://github.com/Didgitalpunk/Flipper-Zero-module-PCB)
