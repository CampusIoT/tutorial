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

Communiquez les informations `LoRaNode EUI` et `MQTT_USERNAME` retournées par le script `getinfo.sh` au sysadmin du serveur CampusIoT (Didier DONSEZ pour le moment).

Récupérez les `MQTT_USERNAME` et `MQTT_PASSWORD` de la gateway auprès du sysadmin du serveur CampusIoT (Didier DONSEZ pour le moment) en lui communiquant le `LoRaNote EUI`.

Loggez-vous (admin) sur la gateway et exécuter les commandes suivantes:
```
cd /tmp
REPO=https://raw.githubusercontent.com/CampusIoT/gateway-config/master
DIST=multitech-mtcap
wget $REPO/$DIST/install.sh -O install.sh
chmod +x install.sh
./install.sh
./install.sh __MQTT_USERNAME__ __MQTT_PASSWORD__
```

> Il peut être nécessaire de rebooter la passerelle pour que le forwarder fonctionne.

> Remarque : Les scripts d'installation sont dans le dépôt https://github.com/CampusIoT/gateway-config/tree/master/multitech-mtcap

### Installation sur Multitech Conduit USB
Votre gateway [Multitech Conduit](https://www.multitech.com/brands/multiconnect-conduit) doit avoir le firmware mLinux et non pas AEP. [Plus de détails](http://www.multitech.net/developer/software/mlinux/using-mlinux/flashing-mlinux-firmware-for-conduit/)

Loggez-vous (admin) sur la gateway et exécuter les commandes suivantes:
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
Communiquez les informations `LoRaNode EUI` et `MQTT_USERNAME` retournées par le script `getinfo.sh` au sysadmin du serveur CampusIoT (Didier DONSEZ pour le moment).

Récupérez les `MQTT_USERNAME` et `MQTT_PASSWORD` de la gateway auprès du sysadmin du serveur CampusIoT (Didier DONSEZ pour le moment).

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
> Remarque : Les scripts d'installation sont dans le dépôt https://github.com/CampusIoT/gateway-config/tree/master/multitech-mtcdt-usb

### Installation sur Multitech Conduit IP67
Votre gateway [Multitech Conduit IP67](https://www.multitech.com/brands/multiconnect-conduit-ip67) doit avoir le firmware mLinux et non pas AEP. [Plus de détails](http://www.multitech.net/developer/software/mlinux/using-mlinux/flashing-mlinux-firmware-for-conduit/)
TODO

### Installation sur RPI3 + iC880a

IMPORTANT: Il faut préalablement activer le SPI via l'option `"5 Interface Options"` avec `sudo /usr/bin/raspi-config`. Il faut ensuite redémarrer la carte pour que le changement soit pris en compte avec `sudo reboot`.

Loggez-vous (PI) sur la gateway et exécuter les commandes suivantes:
```
cd /tmp
REPO=https://raw.githubusercontent.com/CampusIoT/gateway-config/master
DIST=rpi3-ic880a
wget $REPO/$DIST/getinfo.sh -O getinfo.sh
chmod +x getinfo.sh
./getinfo.sh
```

Communiquez les informations `LoRaNode EUI` et `MQTT_USERNAME` retournées par le script `getinfo.sh` au sysadmin du serveur CampusIoT (Didier DONSEZ pour le moment).

Récupérez les `MQTT_USERNAME` et `MQTT_PASSWORD` de la gateway auprès du sysadmin du serveur CampusIoT (Didier DONSEZ pour le moment).

Loggez-vous (admin) sur la gateway et exécuter les commandes suivantes:
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

> Remarque : Les scripts d'installation sont dans le dépôt https://github.com/CampusIoT/gateway-config/tree/master/rpi3-ic880a

### Installation sur RPI3 + Picocell

Loggez-vous (PI) sur la gateway et exécuter les commandes suivantes:
```
cd /tmp
REPO=https://raw.githubusercontent.com/CampusIoT/gateway-config/master
DIST=rpi3-picocell
wget $REPO/$DIST/getinfo.sh -O getinfo.sh
chmod +x getinfo.sh
./getinfo.sh
```

Communiquez les informations `LoRaNode EUI` et `MQTT_USERNAME` retournées par le script `getinfo.sh` au sysadmin du serveur CampusIoT (Didier DONSEZ pour le moment).

Récupérez les `MQTT_USERNAME` et `MQTT_PASSWORD` de la gateway auprès du sysadmin du serveur CampusIoT (Didier DONSEZ pour le moment).

Loggez-vous (admin) sur la gateway et exécuter les commandes suivantes:
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

Remarque : Les scripts d'installation sont dans le dépôt https://github.com/CampusIoT/gateway-config/tree/master/rpi3-picocell

### Installation sur Kerlink Wirgrid
TODO

> Remarque: le gain de l'antenne livrée par défaut est 4.5 dBi.

### Installation sur Kerlink Femtocell
TODO

> Remarque: le gain de l'antenne livrée par défaut est 2-3dBi

> Remarque : Les scripts d'installation sont dans le dépôt https://github.com/CampusIoT/gateway-config/tree/master/kerlink-ifemtocell

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

Modifiez les propriétés `WIFI_SSID` et `WIFI_PASS` dans le fichier `config.py` du répertoire `lopy-nano-gateway`.

Chargez les fichiers du répertoire `lopy-nano-gateway` sur la carte (via le plugin Pycom d'Atom).

## Enregistrement d’une gateway

Créez une gateway depuis une application créée (`Menu > Gateways`) en utilisant le `GWID` (64 bits soit 16 caractères hexadécimaux) fourni. Le `GWID` est calculé soit à partir de l’adresse MAC de la carte ethernet (`eth0`) de la gateway ou à partir de l’identifiant du composant concentrateur SX130x de la gateway (ie le `LoRaNote EUI`). (A noter: une gateway comme la Kerlink iBTS peut avoir plusieurs concentrateurs donc plusieurs `LoRaNote EUI`s).

![Gateway Add](images/gateway-add.png)

> Remarque: le gain de l’antenne ne peut pas être spécifié via le frontend Web.

## Enregistrement et configuration d’une gateway TDOA.
TODO

## Affichage live des frames recus par une gateway

Une fois la gateway enregistrée, les frames reçues par la gateway sont visualisables en temps réel depuis l’onglet “`Live LoRaWAN Frame`”.

![Gateway Live Frame](images/gateway-live.png)

### Récupération du flot MQTT des messages par la gateway
MQTT est le moyen par défaut pour récupérer les messages recus par les gateways.

Le flot de messages envoyés par les devices des applications peut être récupérer via des clients MQTT comme mosquitto_sub (en ligne de commande), [mqtt-spy](https://kamilfb.github.io/mqtt-spy/), , HiveMQ Websocket Client, MQTTBox ([configuration](images/mqttbox-brokerconfig.png), [souscription](images/mqttbox-subscribe.png)) [myMQTT](https://play.google.com/store/apps/details?id=at.tripwire.mqtt.client) pour Android ... Remarque: Des clients (comme [mqtt-lens](https://chrome.google.com/webstore/detail/mqttlens/hemojaaeigabkbcookmlgmdigohjobjm) pour Chrome) ne supportent pas MQTT/TLS.

Installez le client MQTT `mosquitto_sub` avec
```
sudo apt-get install -y mosquitto-clients
```
> Remarque: Une alternative à mosquitto-clients est la commande `mqtt` qui s'installe avec `sudo npm install mqtt -g; mqtt help subscribe; mqtt help publish`.

Il faut installer dans le répertoire courant le certificat `ca.crt` dec l’autorité de certification du broker MQTT avec la commande suivante:
```
wget https://raw.githubusercontent.com/CampusIoT/campusiot-certs/master/mqtt/ca.crt
```
> Remarque: l'option `--insecure` des commandes `mqtt` et `mosquitto_sub` permet de se passer du certificat du broker MQTT.

Actuellement, les commandes à utiliser sont:

```
ORGID=1 # l'id de votre ORGANISATION (ce n’est pas le username de votre compte utilisateur)
BROKER=lora.campusiot.imag.fr
MQTTUSER=org-$ORGID # le username de votre ORGANISATION (ce n’est pas le username de votre compte utilisateur)
MQTTPASSWORD=__SUPER_SECRET_TO_CHANGE__ # le mot de passe de votre ORGANISATION (ce n’est pas le username de votre compte utilisateur)
TLS="--cafile ca.crt -p 8883"

GWEUI=__LE_LoRaNode_EUI_de_la_Gateway__
# Receive Gateway rx
mosquitto_sub -h $BROKER -t "gateway/$GWEUI/rx" -u $MQTTUSER -P $MQTTPASSWORD -v  $TLS
```

[Plus de détails](https://www.loraserver.io/lora-app-server/integrate/data/)

### A voir
* [Introduction à LoRaServer](./README.md)
* [Ajouter une application et des équipements](./README-app.md)
* [Administrer une organisation](./README-org.md)
* [Administrer du service](./README-admin.md)
