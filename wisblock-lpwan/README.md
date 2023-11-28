# RAK Wireless WisBlock LPWAN

RAK Wireless WisBlock LPWAN est une plateforme IoT modulaire et empilable conçue pour fournir une connectivité réseau à longue portée et faible consommation d'énergie (LPWAN) pour diverses applications IoT. LPWAN est un type de technologie de réseau sans fil qui permet une communication à longue portée avec une faible consommation d'énergie, ce qui en fait la solution idéale pour les appareils IoT nécessitant une faible consommation d'énergie et une longue durée de vie de la batterie.

La plateforme WisBlock se compose de différents modules qui peuvent être empilés pour construire un appareil IoT personnalisé. Elle utilise un format standardisé, ce qui permet un prototypage et un déploiement faciles et rapides d'applications IoT.

La plateforme WisBlock prend en charge diverses technologies LPWAN telles que LoRaWAN, NB-IoT et LTE-M, la rendant polyvalente et adaptée à divers cas d'utilisation. De plus, elle intègre une unité de microcontrôleur (MCU) puissante et divers capteurs, en faisant un appareil IoT entièrement fonctionnel dès sa sortie de la boîte.

La plateforme RAK Wireless WisBlock LPWAN est conçue pour permettre aux développeurs IoT de créer et déployer rapidement et facilement des solutions IoT à longue portée et faible consommation d'énergie.

## La configuration pour le suiveur de ballons stratosphériques

* [RAK11310 : Raspberry Pi RP2040 Core Module for LoRaWAN with LoRa SX1262 for eu868 band](https://store.rakwireless.com/products/rak11310-wisblock-lpwan-module?variant=40830755471558)
* [RAK19007 : WisBlock Base Board 2nd Gen](https://store.rakwireless.com/products/rak19007-wisblock-base-board-2nd-gen)
* [RAK1910 : GNSS GPS Location Module u-Blox MAX-7Q](https://store.rakwireless.com/products/rak1910-max-7q-gnss-location-sensor)
* [GNSS antenna](https://store.rakwireless.com/products/gps-antenna-27db)
* [Battery Connector Cable](https://store.rakwireless.com/products/battery-connector-cable)
* [Solar Panel Connector Cable](https://store.rakwireless.com/products/solar-panel-connector-cable)

## Getting started

https://docs.rakwireless.com/Product-Categories/WisBlock/RAK11310/Quickstart/#prerequisites


## Montage de la carte WisBlock

Montage du [RAK11310](https://docs.rakwireless.com/Product-Categories/WisBlock/RAK11310/Quickstart/#hardware-setup)

Montage du [RAK1910](https://docs.rakwireless.com/Product-Categories/WisBlock/RAK1910/Quickstart/#hardware-setup)

## Configuration de l'IDE Arduino

https://docs.rakwireless.com/Knowledge-Hub/Learn/Installation-of-Board-Support-Package-in-Arduino-IDE/

Copy this URL https://raw.githubusercontent.com/RAKwireless/RAKwireless-Arduino-BSP-Index/main/package_rakwireless_index.json and paste it on the field as shown in Figure 11. If there are other URLs already there, just add it on the next line. After adding the URL, click OK.

## Communication LoRaWAN

Choisissez le croquis d'exemple  `File > Examples > RAK WisBlock Examples > RAK11300 > Communications > LoRa > LoRaWAN > LoRaWAN_OTAA_ABP`

Cliquez sur le lien et `http://librarymanager/All#SX126x` et choisissez la library https://github.com/beegee-tokyo/SX126x-Arduino/

```console
OTAA join failed!
Check your EUI's and Keys's!
Check if a Gateway is in range!
=====================================
Welcome to RAK11300 LoRaWan!!!
Type: OTAA
Region: EU868
=====================================
OTAA Mode, Network Joined!
Sending frame now...
```

[Le croquis](https://github.com/RAKWireless/WisBlock/blob/master/examples/RAK11300/communications/LoRa/LoRaWAN/LoRaWAN_OTAA_ABP/LoRaWAN_OTAA_ABP.ino)

## Communication LoRaP2P

[Les croquis](https://github.com/RAKWireless/WisBlock/tree/master/examples/RAK11300/communications/LoRa/LoRaP2P)

### LoRaP2P_TX

Choisissez le croquis d'exemple  `File > Examples > RAK WisBlock Examples > RAK11300 > Communications > LoRa > LoRaP2P > LoRaP2P_TX`

[Le croquis]()

### LoRaP2P_RX

Choisissez le croquis d'exemple  `File > Examples > RAK WisBlock Examples > RAK11300 > Communications > LoRa > LoRaP2P > LoRaP2P_RX`

[Le croquis]()

## Communication WiFi AP

Choisissez le croquis d'exemple  `File > Examples > RAK WisBlock Examples > RAK11300 > Communications > WiFi > connect_ap`

[Le croquis]()

## Lecture du niveau de batterie


Ajoutez la bibliothèque https://github.com/olikraus/u8g2 

Choisissez le croquis d'exemple  `File > Examples > RAK WisBlock Examples > RAK11300 > Power > RAK11300 Battery Level Detect`



[Le croquis]()

## Geolocalisation GNSS

Branchez le module [RAK1910 : GNSS GPS Location Module u-Blox MAX-7Q](https://store.rakwireless.com/products/rak1910-max-7q-gnss-location-sensor) Altitude max : 50,000 m

Choisissez le croquis d'exemple  `File > Examples > RAK WisBlock Examples > RAK11300 > Sensors > RAK1910_GPS_UBLOX7`

[Le croquis]()

## RTC

## SD Card

## Exercice

Assemblez les exemples ci-dessus pour transmettre en LoRaWAN ABP la position GNSS et le niveau de batterie.

Faites varier la taille des messages, le DR et le TxPower périodiquement.

Utilisez le [capacité de LNS](https://resources.lora-alliance.org/technical-specifications/lorawan-application-layer-clock-synchronization-specification-v1-0-0) pour synchroniser/régler l'horloge RTC de la MCU.

Si le module SD Card est installé, journalisez la position GNSS et le niveau de batterie dans un fichier de la SD Card.

Inspirez-vous de [Orbimote FTD](https://github.com/CampusIoT/orbimote/tree/master/field_test_device).
