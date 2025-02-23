# OpenLogger

https://learn.sparkfun.com/tutorials/openlog-hookup-guide

## Branchement

Il faut croiser RX et TX

Fonctionne en 3V3

## LED

STAT1 - This blue indicator LED is attached to Arduino D5 (ATmega328 PD5) and toggles on/off when a new character is received. This LED blinks when Serial communication is functioning`.

## `tio`
```bash
tio -b 115200 -m INLCRNL /dev/tty.usbserial-xxx
```

## Config en mode logger

`config.txt`
```txt
115200,26,0,0,1,1,0
baud,escape,esc#,mode,verb,echo,ignoreRX
```

## Config en mode commande interactive
`config.txt`
```txt
115200,26,0,2,1,1,1
baud,escape,esc#,mode,verb,echo,ignoreRX
```

> NB: Config your terminal like `tio` with `CR+LF` for validating a command line ! 

```
ls
read LOG00001.TXT
disk
```

## Baudrate and SDCard

Il est recommandé que le port console soit configuré à 9600 bauds pour éviter la perte de caratères lors de l'écriture sur la carte SD.

Pour les firmwares avec RIOT OS, il faut redéfinir dans le Makefile `STDIO_UART_BAUDRATE` avec `CFLAGS += -DSTDIO_UART_BAUDRATE=9600`

N.A.:
> J'ai lu en détail la doc (et lu le code), et il faut pas trop en demander à ce logger.
> Il y a un buffer de 512 octets en Rx et un de 255 octets pour l'écriture sur le sdcard. 
> J'ai regardé les benchmark des sdcards, même avec une bonne sdcard, au delà de 9600 bauds, on risque de perdre des données.
> Si on va plus vite sur le port série, il faut limiter le nombre de messages.
Pas catastrophique, mais il faut le prendre en compte.

## OpenLog and GNSS modules

### Adafruit Ultimate GPS

[Adafruit Ultimate GPS](https://learn.adafruit.com/adafruit-ultimate-gps)

Baudrate is 9600

|OpenLog | GPS | Battery 3.6V |
| ------ | ---- | -------- | 
| `VCC` | `3.3V` | `RED` |
| `GND` | `GND` | `BLACK` |
| `RXI` | `TX` | `NC` |

> Warning: Do not power with LiPo cells : Voltage is too high (3.7V to 4.2V) ! High risk to destroy the GNSS module and the OpenLog

![](adafruit_ultimate_gps_openlog.jpg)
![](https://cdn-learn.adafruit.com/assets/assets/000/031/842/large1024/gps_746_topkit.jpg?1461187930)









