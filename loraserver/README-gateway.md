# CampusIoT :: LoRaServer > Partie 2: Installer une nouvelle gateway :: Tutoriel :fr:

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

Récupérer l’adresse MAC de la carte Ethernet de la gateway.

La communiquer à xxxx@imag.fr

Il fournira l’id (gweui), le username et le password de la gateway qui servira à la configuration de 2 composants.
## Installation du Semtech lora-pkt-fwd
### Sur Kerlink Wirgrid
TODO

### Sur Multitech Conduit USB
Votre gateway Multitech Conduit doit avoir le firmware mLinux et non pas AEP. [Plus de détails](http://www.multitech.net/developer/software/mlinux/using-mlinux/flashing-mlinux-firmware-for-conduit/)
TODO
### Sur Multitech
Votre gateway Multitech Conduit doit avoir le firmware mLinux et non pas AEP. [Plus de détails](http://www.multitech.net/developer/software/mlinux/using-mlinux/flashing-mlinux-firmware-for-conduit/)
TODO
### Sur RPI3 + iC880a
TODO
### Sur RPI3 + Picocell
TODO
### Sur Kerlink Femtocell
TODO

## Installation du lora-gateway-bridge
### Sur Kerlink Wirgrid
TODO

#### Sur Multitech
Votre gateway Multitech Conduit doit avoir le firmware mLinux et non pas AEP. [Plus de détails](http://www.multitech.net/developer/software/mlinux/using-mlinux/flashing-mlinux-firmware-for-conduit/)
TODO

### Sur RPI3 + iC880a
TODO

### Sur Kerlink Femtocell
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
