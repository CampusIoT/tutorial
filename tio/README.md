# Tio - a simple serial device I/O tool

https://github.com/tio/tio

## Installation

```bash
brew install tio
tio help
```

## Console

Open the serial console of the board (Groove UART connector to USB serial adapter)
```bash
tio -L
tio -b 115200 -m INLCRNL /dev/tty.usbserial-142xxx
```

