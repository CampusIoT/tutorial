# CampusIoT :: Riot OS :: Tutoriel

## Installation de RIOT OS
TODO



## Cartes SODAQ Explorer
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




# References
* https://github.com/RIOT-OS/RIOT/tree/master/examples/lorawan
* https://github.com/aabadie/riot-course
* https://wireless-solutions.de/products/radiomodules/im880b-l
* https://github.com/fjmolinas/RIOT/tree/im880b_loramac



