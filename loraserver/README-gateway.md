# CampusIoT :: LoRaServer > Installer une nouvelle gateway :: Tutoriel :fr:

Si ce tutoriel vous est utile, pensez à donner une étoile :star: en haut à droit.

## Création d’un gateway-profile
Cette opération est pour l’administrateur d’une organisation

Loggez-vous sur https://lora.campusiot.imag.fr

Créez au moins un gateway-profile `DEFAULT` pour l’organisation.

![Gateway Profile](images/gateway-profile-add.png)

[Plus de détails](https://www.loraserver.io/lora-app-server/use/gateways/)

## Installation et enregistrement d’une gateway
Deux composants doivent être installés sur une nouvelle gateway.
* Semtech lora-pkt-fwd qui contrôle le concentrateur SX130X de la gateway,
* lora-gateway-bridge qui réalise un pont entre lora-pkt-fwd et le network server.

Une fois ces 2 composants installés, la gateway peut être enregistrée via `Menu > Gateways` de l'organisation.


### Réglementation ETSI et gain de l'antenne de la gateway

La [réglementation ETSI](https://www.etsi.org/technologies-clusters/technologies/radio) impose que la puissance d'émission d'un équipement ne dépasse pas une limite donnée dans les bandes ISM utilisées : 14 dBm (soit 25 mW) pour les bandes `g` et `g1`, et 27 dBm (soit  500 mW) pour la bande `g3` de la bande ISM `eu868`. La limite de puissance d'émission inclut le gain de l'antenne et la perte du cable et des connecteurs. A titre d'exemple, si la gateway est équipée d'une antenne 12 dBi et que les pertes sont de 0.5 dBm, la puissance en sortie du concentrateur ne peut exéder 2 dBm pour les 2 bandes `g` et `g1`.

Ce travail de limitation est réalisé par le packer forwarder au moyen de la propriété de configuration `SX1301_conf.antenna_gain`.

Afin de respecter la réglementation, il est important que le gain de l'antenne soit déterminé afin qu'il soit configuré (par les scripts d'installation) dans les fichiers `local_conf.json` ou `global_conf.json`. Il faut vous référer à la documentation technique de la gateway ou de l'antenne (on-board or indépendante).

### Installation sur Multitech Conduit AP
Installez la gateway en suivre son [guide](http://www.multitech.net/developer/products/multiconnect-conduit-access-point/).

> Remarque: le gain de l'antenne PCB on-board de la Multitech Conduit AP est 2 dBi.

Votre gateway [Multitech Conduit AP](https://www.multitech.com/brands/multiconnect-conduit-ap) doit avoir le firmware mLinux et non pas AEP. [Plus de détails](http://www.multitech.net/developer/software/mlinux/using-mlinux/flashing-mlinux-firmware-for-conduit/)

Loggez-vous (admin) sur la gateway et exécuter les commandes suivantes pour connaitre le `LoRaNote EUI` de la gateway :
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

Récupérez les MQTT_USERNAME et MQTT_PASSWORD de la gateway auprès du sysadmin du serveur CampusIoT (Didier DONSEZ pour le moment) en lui communiquant le `LoRaNote EUI`.

Logger-vous (admin) sur la gateway et exécuter les commandes suivantes:
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
Votre gateway [Multitech Conduit](https://www.multitech.com/brands/multiconnect-conduit) doit avoir le firmware mLinux et non pas AEP. [Plus de détails](http://www.multitech.net/developer/software/mlinux/using-mlinux/flashing-mlinux-firmware-for-conduit/)

Logger-vous (admin) sur la gateway et exécuter les commandes suivantes:
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
Récupérez les MQTT_USERNAME et MQTT_PASSWORD de la gateway auprès du sysadmin du serveur CampusIoT (Didier DONSEZ pour le moment).

Se logger (admin) sur la gateway et exécuter les commandes suivantes:
```
MQTT_USERNAME=gw-1234567890abcdef
MQTT_PASSWORD=xXxXxXxXxXxXxXxXxXxXxXxXxXxXxX
ANTENNA_GAIN_DBI=3
cd /tmp
REPO=https://raw.githubusercontent.com/CampusIoT/gateway-config/master
DIST=multitech-mtcdt-usb
wget $REPO/$DIST/install.sh -O install.sh
chmod +x install.sh
./install.sh
./install.sh $MQTT_USERNAME $MQTT_PASSWORD $ANTENNA_GAIN_DBI
```

### Installation sur Multitech Conduit IP67
Votre gateway [Multitech Conduit IP67](https://www.multitech.com/brands/multiconnect-conduit-ip67) doit avoir le firmware mLinux et non pas AEP. [Plus de détails](http://www.multitech.net/developer/software/mlinux/using-mlinux/flashing-mlinux-firmware-for-conduit/)
TODO

### Installation sur RPI3 + iC880a

IMPORTANT: Il faut préalablement activer le SPI via l'option `"5 Interface Options"` avec `sudo /usr/bin/raspi-config`. Il faut ensuite redémarrer la carte pour que le changement soit pris en compte avec `sudo reboot`.

Logger-vous (PI) sur la gateway et exécuter les commandes suivantes:
```
cd /tmp
REPO=https://raw.githubusercontent.com/CampusIoT/gateway-config/master
DIST=rpi3-ic880a
wget $REPO/$DIST/getinfo.sh -O getinfo.sh
chmod +x getinfo.sh
./getinfo.sh
```
Récupérez les MQTT_USERNAME et MQTT_PASSWORD de la gateway auprès du sysadmin du serveur CampusIoT (Didier DONSEZ pour le moment).

Se logger (admin) sur la gateway et exécuter les commandes suivantes:
```
MQTT_USERNAME=gw-1234567890abcdef
MQTT_PASSWORD=xXxXxXxXxXxXxXxXxXxXxXxXxXxXxX
ANTENNA_GAIN_DBI=2
cd /tmp
REPO=https://raw.githubusercontent.com/CampusIoT/gateway-config/master
DIST=rpi3-ic880a
wget $REPO/$DIST/install.sh -O install.sh
chmod +x install.sh
./install.sh
./install.sh $MQTT_USERNAME $MQTT_PASSWORD $ANTENNA_GAIN_DBI
```

### Installation sur RPI3 + Picocell
Logger-vous (PI) sur la gateway et exécuter les commandes suivantes:
```
cd /tmp
REPO=https://raw.githubusercontent.com/CampusIoT/gateway-config/master
DIST=rpi3-picocell
wget $REPO/$DIST/getinfo.sh -O getinfo.sh
chmod +x getinfo.sh
./getinfo.sh
```
Récupérez les MQTT_USERNAME et MQTT_PASSWORD de la gateway auprès du sysadmin du serveur CampusIoT (Didier DONSEZ pour le moment).

Se logger (admin) sur la gateway et exécuter les commandes suivantes:
```
MQTT_USERNAME=gw-1234567890abcdef
MQTT_PASSWORD=xXxXxXxXxXxXxXxXxXxXxXxXxXxXxX
ANTENNA_GAIN_DBI=2
cd /tmp
REPO=https://raw.githubusercontent.com/CampusIoT/gateway-config/master
DIST=rpi3-picocell
wget $REPO/$DIST/install.sh -O install.sh
chmod +x install.sh
./install.sh
./install.sh $MQTT_USERNAME $MQTT_PASSWORD $ANTENNA_GAIN_DBI
```

### Installation sur Kerlink Wirgrid
TODO

> Remarque: le gain de l'antenne livrée par défaut est 4.5 dBi.

### Installation sur Kerlink Femtocell
TODO

> Remarque: le gain de l'antenne livrée par défaut est 2-3dBi

### Installation sur Kerlink iBTS Compact
TODO

### Installation sur Kerlink iBTS
TODO

### Installation sur Intel NUC + Picocell
TODO

### Installation sur Intel NUC + NFuse Mini-PCIe
TODO

### Installation d'une nano-gateway Pycom LoPy/FiPy
TODO
Récupérez le programme `lopy-nano-gateway`.
```
git clone https://github.com/CampusIoT/lopy-nano-gateway.git
cd lopy-nano-gateway
```

Mettez à jour le firmware de votre carte Pycom LoPy/FiPy en utilisant l'application [Pycom Firmware Update](https://docs.pycom.io/gettingstarted/installation/firmwaretool.html).

Récupérez les informations de votre carte Pycom LoPy/FiPy via via le plugin Pycom d'Atom.

Modifiez les propriétés WIFI_SSID et WIFI_PASS dans le fichier `config.py` du répertoire `lopy-nano-gateway`.

Chargez les fichiers du répertoire `lopy-nano-gateway` sur la carte (via le plugin Pycom d'Atom).

## Enregistrement d’une gateway

Créez une gateway depuis une application créée (`Menu > Gateways`) en utilisant le `GWID` (64 bits soit 16 caractères hexadécimaux) fourni. Le GWID est calculé soit à partir de l’adresse MAC de la carte ethernet (`eth0`) de la gateway ou à partir de l’identifiant du composant concentrateur SX130x de la gateway (ie le `LoRaNote EUI`). (A noter: une gateway comme la Kerlink iBTS peut avoir plusieurs concentrateurs donc plusieurs `LoRaNote EUI`s).

![Gateway Add](images/gateway-add.png)

> Remarque: le gain de l’antenne ne peut pas être spécifié via le frontend Web.

## Enregistrement et configuration d’une gateway TDOA.
TODO

## Affichage live des frames recus par une gateway

Une fois la gateway enregistrée, les frames reçues par la gateway sont visualisables en temps réel depuis l’onglet “`Live LoRaWAN Frame`”.

![Gateway Live Frame](images/gateway-live.png)

### A voir
* [Introduction à LoRaServer](./README.md)
* [Ajouter une application et des équipements](./README-app.md)
* [Administrer une organisation](./README-org.md)
* [Administrer du service](./README-admin.md)
