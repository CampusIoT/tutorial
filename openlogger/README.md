# OpenLog

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

N.A.:
> J'ai lu en détail la doc (et lu le code), et il faut pas trop en demander à ce logger.
> Il y a un buffer de 512 octets en Rx et un de 255 octets pour l'écriture sur le sdcard. 
> J'ai regardé les benchmark des sdcards, même avec une bonne sdcard, au delà de 9600 bauds, on risque de perdre des données.
> Si on va plus vite sur le port série, il faut limiter le nombre de messages.
Pas catastrophique, mais il faut le prendre en compte.





