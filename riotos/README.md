# CampusIoT :: Riot OS :: Tutoriel

## RIOT OS
[RIOT OS](http://www.riot-os.org/) est un système d'exploitation temps-réel pour les systèmes embarqués et les objets connectés. Il supporte de nombreux architectures, CPU, boards, composants (capteurs, actionneurs).

On s'intéresse à RIOT-OS car il offre: 

- plus de souplesse en terme de programmation (un OS, pile IP, support d'autres technologies wireless, timer, serial, ...)
- le support de [nombreuses plateformes](https://doc.riot-os.org/group__boards.html) et [cartes](https://github.com/RIOT-OS/RIOT/tree/master/boards/), [périphériques](https://github.com/RIOT-OS/RIOT/tree/master/drivers) ...
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

Open serial terminal (115200 8N1 No Hardware Flow Control, No Software Flow Control)
```bash
ls -al /dev/tty.*
minicom -s
```

### MicroPython
Build and flash
```bash
make BOARD=sodaq-explorer -C examples/micropython flash
```

Open serial terminal (115200 8N1 No Hardware Flow Control, No Software Flow Control)
```bash
ls -al /dev/tty.*
minicom -s
```

### LoRa (RN2483)
```bash
cd ~/github/RIOT-OS/RIOT
make BOARD=sodaq-explorer -C tests/driver_rn2xx3 flash
```

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

```bash
make BOARD=feather-m0 DRIVER=sx1276 -C ~/github/RIOT-OS/riot-course/exercises/riot-lorawan/simple/.solution flash
```



## Cartes STM32 Nucleo et Discovery

RIOT supporte beaucoup de cartes [STM32 Nucleo et Discovery](https://github.com/CampusIoT/stm32-riotos-demos/blob/master/boards.md).

### Hello World
Build and flash
```bash
make BOARD=nucleo-f411re -C examples/hello-world flash
```

Open serial terminal (115200 8N1 No Hardware Flow Control, No Software Flow Control)
```bash
ls -al /dev/tty.*
minicom -s
```

### MicroPython
Build and flash
```bash
make BOARD=nucleo-f411re -C examples/micropython flash
```

Open serial terminal (115200 8N1 No Hardware Flow Control, No Software Flow Control)
```bash
ls -al /dev/tty.*
minicom -s
```

## Cartes STM32 Nucleo et Carte fille Semtech LoRa SX127xMB

Deux cartes d'évaluation des transceivers LoRa SX1272 et SX1276 sont proposées par Semtech :
* [SX1272MB2xAS](https://os.mbed.com/components/SX1272MB2xAS/)
* [SX1276MB1xAS](https://os.mbed.com/components/SX1276MB1xAS/)

### Simple LoRa Shell

Plugin the Nucleo LRWAN1 kit : Nucleo L073RZ + [SX1272MB2xAS)](https://os.mbed.com/components/SX1272MB2xAS/) with the USB cable.

Build and flash
```bash
make BOARD=nucleo-l073rz DRIVER=sx1272 -C tests/driver_sx127x flash
```
Open serial terminal (115200 8N1 No Hardware Flow Control, No Software Flow Control)
```bash
ls -al /dev/tty.*
minicom -s
```

Enter the command lines:
```
help
setup
setup 125 7 5
syncword get
syncword set 34
channel get
channel set 868100000
send Hello_World
```

Sniff the output of a LoRa gateway
```
1585324959114,MSG,gateway/0016c00100002123/rx,{"rxInfo":{"mac":"0016c00100002123","timestamp":1222392710,"frequency":868100000,"channel":0,"rfChain":1,"crcStatus":1,"codeRate":"4/5","rssi":-66,"loRaSNR":13.8,"size":6,"dataRate":{"modulation":"LORA","spreadFactor":7,"bandwidth":125},"board":0,"antenna":0},"phyPayload":"SGVsbG9fV29ybGQA"}
```

Decode the phyPayload properties
```bash
echo SGVsbG9fV29ybGQA | base64 -d
```
Result is :
```
Hello_World
```



### Simple LoRaWAN Shell

Plugin the Nucleo LRWAN1 kit : Nucleo L073RZ + [SX1272MB2xAS)](https://os.mbed.com/components/SX1272MB2xAS/) with the USB cable.

Build and flash
```bash
make BOARD=nucleo-l073rz DRIVER=sx1272 -C tests/pkg_semtech-loramac flash
```
Open serial terminal (115200 8N1 No Hardware Flow Control, No Software Flow Control)
```bash
ls -al /dev/tty.*
minicom -s
```

#### OTAA
Enter the command lines:
```
help
loramac                               
loramac get
loramac get deveui
loramac get appeui
loramac get appkey
loramac get class
loramac get adr
loramac get dr
loramac get pub

loramac set deveui cafebabe12345678
loramac set appeui cafebabeffffffff
loramac set appkey cafebabe12345678cafebabe12345678
loramac set adr on
loramac save

loramac join otaa
# Blocage du programme !

loramac tx Hello
```

Register the endpoint on a network server (TTN, CampusIoT, Orange LiveObject) with an OTAA device profile


#### ABP
Enter the command lines:

```
loramac set deveui cafebabe12345679
loramac set appeui cafebabeffffffff
loramac set appskey cafebabe12345679cafebabe12345679
loramac set nwkskey cafebabe12345679cafebabe12345679
loramac set devaddr 00001234
loramac save
loramac join abp

loramac tx Hello
# Blocage du programme !

```


Register the endpoint on a network server (TTN, CampusIoT, Orange LiveObject) with an ABP device profile

#### LoRaWAN simple program

Plugin the Nucleo LRWAN1 kit : Nucleo L073RZ + [SX1272MB2xAS)](https://os.mbed.com/components/SX1272MB2xAS/) with the USB cable.

Set the DevEUI, AppEUI and AppKey into `~/github/RIOT-OS/riot-course/exercises/riot-lorawan/simple/.solution/main.c`
```
/* Device and application informations required for OTAA activation */
static const uint8_t deveui[LORAMAC_DEVEUI_LEN] = { 0xca, 0xfe, 0xba, 0xbe, 0x12, 0x72, 0x00, 0x01 };
static const uint8_t appeui[LORAMAC_APPEUI_LEN] = { 0xca, 0xfe, 0xba, 0xbe, 0x12, 0xff, 0xff, 0xff };
static const uint8_t appkey[LORAMAC_APPKEY_LEN] = { 0xca, 0xfe, 0xba, 0xbe, 0x12, 0x72, 0x00, 0x01, 0xca, 0xfe, 0xba, 0xbe, 0x12, 0x72, 0x00, 0x01 };
```

Build and flash
```bash
make BOARD=nucleo-l073rz DRIVER=sx1272 -C ~/github/RIOT-OS/riot-course/exercises/riot-lorawan/simple/.solution flash
```
Open serial terminal (115200 8N1 No Hardware Flow Control, No Software Flow Control)
```bash
ls -al /dev/tty.*
minicom -s
```

#### LoRaWAN simple program

Plugin the second kit : Nucleo F411RE + [SX1276MB1xAS](https://os.mbed.com/components/SX1276MB1xAS/)
 with the USB cable.


Set the DevEUI, AppEUI and AppKey into `~/github/RIOT-OS/riot-course/exercises/riot-lorawan/simple/.solution/main.c`
```
/* Device and application informations required for OTAA activation */
static const uint8_t deveui[LORAMAC_DEVEUI_LEN] = { 0xca, 0xfe, 0xba, 0xbe, 0x12, 0x76, 0x00, 0x01 };
static const uint8_t appeui[LORAMAC_APPEUI_LEN] = { 0xca, 0xfe, 0xba, 0xbe, 0x12, 0xff, 0xff, 0xff };
static const uint8_t appkey[LORAMAC_APPKEY_LEN] = { 0xca, 0xfe, 0xba, 0xbe, 0x12, 0x76, 0x00, 0x01, 0xca, 0xfe, 0xba, 0xbe, 0x12, 0x76, 0x00, 0x01 };
```

Build and flash
```bash
make BOARD=nucleo-f411re DRIVER=sx1276 -C ~/github/RIOT-OS/riot-course/exercises/riot-lorawan/simple/.solution flash
```

Open serial terminal (115200 8N1 No Hardware Flow Control, No Software Flow Control)
```bash
ls -al /dev/tty.*
minicom -s
```


# References
* https://github.com/RIOT-OS/RIOT/tree/master/examples/lorawan
* https://github.com/aabadie/riot-course
* https://wireless-solutions.de/products/radiomodules/im880b-l
* https://github.com/fjmolinas/RIOT/tree/im880b_loramac



