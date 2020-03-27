# CampusIoT :: Riot OS :: Tutoriel

## RIOT OS
RIOT OS est un système d'exploitation pour les systèmes embarqués et les objets connectés. Il supporte de nombreux architectures, CPU, boards, composants (capteurs, actionneurs).


On s'intéresse à RIOT-OS car il offre: 

- plus de souplesse en terme de programmation (un OS, pile IP, support d'autres technologies wireless, timer, serial, ...)
- le support de [nombreuses plateformes](https://doc.riot-os.org/group__boards.html) et [cartes](https://github.com/RIOT-OS/RIOT/tree/master/boards/),
- beaucoup d'applicatifs
- ...

## Installation de RIOT OS

```bash
mkdir -p github/RIOT-OS
cd github/RIOT-OS
git clone git://github.com/RIOT-OS/RIOT.git
cd RIOT
RIOT_BASE=$(pwd)
```

Sur MacOS, récupérez une version récente de `make`
```
brew install make
PATH="/usr/local/opt/make/libexec/gnubin:$PATH"
```

## Cartes SODAQ Explorer

RIOT supporte la carte [SODAQ Explorer](https://doc.riot-os.org/group__boards__sodaq-explorer.html).

### Hello World
Build and flash
```bash
make BOARD=sodaq-explorer -C examples/hello-world flash
```

Build and flash
```bash
ls -al /dev/tty.*
minicom -s
```
### LoRaWAN
TODO


## Cartes IMST iM880a

RIOT supporte le module IMST [iM880b](https://doc.riot-os.org/group__boards__im880b.html).

### Build
```bash
cd RIOT/
git branch --set-upstream-to=origin/im880b_loramac im880b_loramac
git pull

cat ~/RIOT/tests/driver_sx127x/README.md
cat ~/RIOT/tests/driver_sx127x/main.c
make BOARD=im880b DRIVER=sx1272 -C tests/driver_sx127x PORT=/dev/ttyACM0 flash
ll ~/RIOT/tests/driver_sx127x/bin/im880b/tests_driver_sx127x.*

cat ~/RIOT/tests/pkg_semtech-loramac/README.md
cat ~/RIOT/tests/pkg_semtech-loramac/main.c
make BOARD=im880b LORA_DRIVER=sx1272 -C tests/pkg_semtech-loramac/ PORT=/dev/ttyACM0 flash
ll ~/RIOT/tests/pkg_semtech-loramac/bin/im880b/tests_pkg_semtech-loramac.*
```
### Run

```bash
TODO
```

## Cartes ESP 8266 Wemos
TODO

RIOT supporte les cartes à base d'[ESP8266](https://doc.riot-os.org/group__boards__esp8266.html).

## Cartes ESP32-LoRa Heltec
TODO

RIOT supporte les cartes à base d'[ESP32](https://doc.riot-os.org/group__boards__esp32.html).


## Cartes Feather LoRa
TODO

RIOT supporte les cartes [Feather d'Adafruit](https://github.com/RIOT-OS/RIOT/tree/master/boards/feather-m0).

## Cartes STM32 Nucleo et Discovery

RIOT supporte beaucoup de cartes [STM32 Nucleo et Discovery](https://github.com/CampusIoT/stm32-riotos-demos/blob/master/boards.md).


# References
* https://github.com/RIOT-OS/RIOT/tree/master/examples/lorawan
* https://github.com/aabadie/riot-course
* https://wireless-solutions.de/products/radiomodules/im880b-l
* https://github.com/fjmolinas/RIOT/tree/im880b_loramac



