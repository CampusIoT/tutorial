# CampusIoT :: LoRaServer > Partie 2: Installer une nouvelle gateway :: Tutoriel :fr:

Si ce tutoriel vous est utile, pensez à donner une étoile :star: en haut à droit.

## Création d’un gateway-profile
Cette opération est pour l’administrateur d’une organisation

Créer au moins un gateway-profile `DEFAULT` pour l’organisation.

![Gateway Profile](images/gateway-profile-add.png)

[Plus de détails](https://www.loraserver.io/lora-app-server/use/gateways/)

## Installation et enregistrement d’une gateway
Deux composants doivent être installés sur une nouvelle gateway.
* Semtech lora-pkt-fwd
* lora-gateway-bridge

Une fois ces 2 composants installés, la gateway peut être enregistrée via Menu > Gateways
Prérequis


### Installation sur Multitech
Votre gateway Multitech Conduit doit avoir le firmware mLinux et non pas AEP. [Plus de détails](http://www.multitech.net/developer/software/mlinux/using-mlinux/flashing-mlinux-firmware-for-conduit/)

Se logger (admin) sur la gateway et exécuter les commandes suivantes:
```
cd /tmp
REPO=https://raw.githubusercontent.com/CampusIoT/gateway-config/master
DIST=multitech-mtcap
wget $REPO/$DIST/getinfo.sh -O getinfo.sh
chmod +x getinfo.sh
./getinfo.sh
wget $REPO/$DIST/packages.sh -O packages.sh
chmod +x packages.sh
./packages.sh
```

Récupérer les MQTT_USERNAME et MQTT_PASSWORD de la gateway auprès du sysadmin du serveur CampusIoT (Didier DONSEZ pour le moment).

Se logger (admin) sur la gateway et exécuter les commandes suivantes:
```
cd /tmp
REPO=https://raw.githubusercontent.com/CampusIoT/gateway-config/master
DIST=multitech-mtcap
wget $REPO/$DIST/install.sh -O install.sh
chmod +x install.sh
./install.sh
./install.sh __MQTT_USERNAME__ __MQTT_PASSWORD__
```

### Installation sur Multitech Conduit USB
Votre gateway Multitech Conduit doit avoir le firmware mLinux et non pas AEP. [Plus de détails](http://www.multitech.net/developer/software/mlinux/using-mlinux/flashing-mlinux-firmware-for-conduit/)

Se logger (admin) sur la gateway et exécuter les commandes suivantes:
```
cd /tmp
REPO=https://raw.githubusercontent.com/CampusIoT/gateway-config/master
DIST=multitech-mtcdt-usb
wget $REPO/$DIST/getinfo.sh -O getinfo.sh
chmod +x getinfo.sh
./getinfo.sh
wget $REPO/$DIST/packages.sh -O packages.sh
chmod +x packages.sh
./packages.sh
```
Récupérer les MQTT_USERNAME et MQTT_PASSWORD de la gateway auprès du sysadmin du serveur CampusIoT (Didier DONSEZ pour le moment).

Se logger (admin) sur la gateway et exécuter les commandes suivantes:
```
cd /tmp
REPO=https://raw.githubusercontent.com/CampusIoT/gateway-config/master
DIST=multitech-mtcdt-usb
wget $REPO/$DIST/install.sh -O install.sh
chmod +x install.sh
./install.sh
./install.sh __MQTT_USERNAME__ __MQTT_PASSWORD__
```

### Installation sur RPI3 + iC880a
TODO
### Installation sur RPI3 + Picocell
TODO
### Installation sur Kerlink Wirgrid
TODO
Récupérer l’adresse MAC de la carte Ethernet de la gateway.
### Installation sur Kerlink Femtocell
TODO

## Enregistrement d’une gateway
https://lora.campusiot.imag.fr/#/organizations/1/gateways/create

Créer une gateway depuis une application créée (`Menu > Gateways`) en utilisant le `GWID` (64 bits soit 16 caractères hexadécimaux) fourni. Le GWID est calculé soit à partir de l’adresse MAC de la carte ethernet (`eth0`) de la gateway ou à partir de l’identifiant du composant concentrateur SX130x de la gateway. (A noter: une gateway peut avoir plusieurs concentrateurs).

![Gateway Add](images/gateway-add.png)

> Remarque: le gain de l’antenne ne peut pas être spécifié via le frontend Web.

## Enregistrement et configuration d’une gateway TDOA.
TODO

## Affichage live des frames recus par une gateway

https://lora.campusiot.imag.fr/#/organizations/1/gateways/008000000000ba6a/frames

Une fois enregistrée, les frames reçus par la gateway sont visualisables en temps réel  depuis l’onglet “`Live LoRaWAN Frame`”.

![Gateway Live Frame](images/gateway-live.png)

### La suite
* [Partie 1 : Débuter](./README.md)
* [Partie 3 : Administrer du service](./README-admin.md)
