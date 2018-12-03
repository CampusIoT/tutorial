# CampusIoT :: Tutoriel :: Enregistrer et utiliser un modem Microchip RN2483 :fr:

Le module RN2483 est un module LoRa/LoRaWAN certifié qui sert de modem de communication à une machine hôte (PC, Mac, Smartphone) via un dongle USB serial (FTDI, ...), ou avec un micro-controleur (cartes Libelium, cartes SODAQ ...).

Le module existe sous la référence RN2483 pour l'Europe avec les bandes ISM 868 MHz et 433 MHz, et sous la référence RN2903 pour les USA, Canada, Australie et New Zealand. Il contient un composant Semtech SX1276.

Les commandes du modem sont documentées ici: http://ww1.microchip.com/downloads/en/DeviceDoc/40001784B.pdf

Il y a 3 types de commandes pour accéder aux différentes fonctions du module:
* Fonctions de configuration et de controle d'un endpoint LoRaWAN Class A (mac)
* Fonctions de configuration de la radio LoRa (radio)
* Fonctions systèmes (sys)

> Remarque: Il existe des breakouts comme celui de [RN2483 breakout de Azzy's Electronics](https://www.tindie.com/products/DrAzzy/rn2483-breakout-bare-board/) à 3 USD pour y souder votre module et votre interface USB serial (FTDI) alimentée en 3.3V DC.

## Installer un client série
Installer Coolterm pour Mac

## Connecter le modem
Configurer la fin de ligne à la valeur `<CR><LF>`.

Connecter le modem avec le débit de 57600 bps, 8 bits, no parity, 1 Stop bit, no flow control.

## Inspecter le modem

Entrer les commandes suivantes dans le terminal série:
```
# lecture des informations du modem
sys get ver
>> RN2483 0.9.5 Mar 24 2015 14:15:33

sys get vdd
>> 2950

sys get hweui
>> 0004A30B001BA7BC
```

## Configurer la clé AppKey et l'AppEUI

```
mac get deveui
>> 0004A30B001BA7BC
mac get appeui
>> 0000000000000000

mac set appeui 0004A30B00123456
>> ok
mac set appkey 0004A30B001BA7BC0004A30B00123456
>> ok
mac set pwridx 1
>> ok

# Sauvegarder les paramêtres de manière persistante dans le module
mac save
>> ok
```

Tenter la procédure OTAA (alors que le device n'est pas enregistré)
```
mac join otaa
>> ok
# Et quelques secondes après
>> denied
```

## Enregistrer le modem dans le serveur

Créer une nouvelle application RN2483_MODEM.

Ajouter un device (device profile CLASS_A_OTAA) avec le DevEUI récupéré et l'AppKey sauvegardée dans le module.

## Envoyer des messages (uplink)

```
mac tx cnf 1 01020304
>> not_joined

# Tenter de nouveau la procédure OTAA
mac join otaa
>> ok
# Et quelques secondes après
>> accepted

# Envoyer un message uplink confirmed (au format hexadécimal) sur le port 1
mac tx cnf 1 01020304
>> ok

# Envoyer un message uplink unconfirmed (au format hexadécimal) sur le port 2
mac tx uncnf 2 05060708
>> ok
```

## Recevoir des messages (downlink)

```
# Envoyer un message uplink confirmed (au format hexadécimal) sur le port 3
mac tx cnf 3 010B0C0D
>> ok
>>
```

## Reconfigurer la couche Mac
```
mac pause

mac reset 868

mac set deveui 0004A30B001BA7BC
mac set appeui 0004A30B00123456
mac set appkey 0004A30B001BA7BC0004A30B00123456
mac set pwridx 1


mac set dr 0
mac set adr on
mac set bat 127
mac set retx 2
mac set linkchk 100
mac set rxdelay1 1000
mac set ar on
mac get rx2 868
mac set rx2 3 869525000


mac get ch freq 0
mac get ch freq 1
mac get ch freq 2
mac get ch dcycle 0
mac get ch dcycle 1
mac get ch dcycle 2

# set DC to 50%
mac set ch dcycle 0 1
mac set ch dcycle 1 1
mac set ch dcycle 2 1

mac save

mac join otaa

mac tx cnf 1 01020304
mac tx uncnf 1 0102034
```
