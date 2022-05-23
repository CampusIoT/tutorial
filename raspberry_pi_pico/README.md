# Raspberry Pi Pico RP2040

[Raspberry Pi Pico RP2040](https://www.raspberrypi.com/documentation/microcontrollers/rp2040.html)

## Arduino

Ajoutez l'URL suivante `https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json` dans `Préférences > Gestionnaire de cartes supplémentaires`.

Cherchez `RP2040` dans le menu `Outils > Type de carte > Gestionnaire de carte`.

Choisissez la carte dans la liste `Outils > Type de carte > Gestionnaire de carte> Raspberry Pi RP2040 Boards`

Ouvrez l'exemple `Fichier > Exemples > 01.Basics > Blink`.

## RIOT OS

https://doc.riot-os.org/group__boards__rpi__pico.html

```bash
cd ~/github/RIOT_OS/RIOT/tests/leds
make BOARD=rpi-pico PROGRAMMER=openocd flash
```


## MicroPython

* https://www.raspberrypi.com/documentation/microcontrollers/rp2040.html#software-development
* https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-python-sdk.pdf
