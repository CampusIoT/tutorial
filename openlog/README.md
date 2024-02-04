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

```
ls
read LOG00001.TXT
disk
```






