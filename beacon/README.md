# CampusIoT :: Beacon :: Tutoriel :fr:

Si ce tutoriel vous est utile, pensez à donner une étoile :star: en haut à droit.

Les [beacons BLE](https://en.wikipedia.org/wiki/Bluetooth_low_energy_beacon) (iBeacons, AltBeacon, EddyStones, Estimote) sont des balises BLE possédant un identifiant unique qui émettent des messages d'avertissement pouvant utiliser pour géolocaliser le terminal récepteur.


## Etape 0: Prérequis
Installer Docker CE et Docker Compose sur votre machine
* https://docs.docker.com/install/
* https://docs.docker.com/compose/install/


## Etape 1 :
Il existe des dizaines d'applications pour scanner des beacons BLE pour Android et iOS.

Cette application [Beacon Scanner](https://play.google.com/store/apps/details?id=com.bridou_n.beaconscanner&rdid=com.bridou_n.beaconscanner) est disponible sur le Play store Android et elle a le mérite d'être en open-source https://github.com/Bridouille/android-beacon-scanner

## Etape 2 : Développement d'un collecteur de beacons géolocalisés avec NodeRED
L'objectif de cette étape est de prototyper un collecteur de beacons géolocalisés au moyen d'un flot NodeRED.

### Côté edge (ie le collecteur)
Il vous faut un Raspberry Pi 3 avec un module GPS 3.3V à brancher sur les broches rx/tx de l'UART via port d'extension du Raspberry Pi 3 ().

Installez NodeRED.

Ajoutez le plugin [node-red-contrib-beacon-scanner](https://www.npmjs.com/package/node-red-contrib-beacon-scanner)

```
cd nodered
sudo apt-get install libbluetooth-dev libudev-dev pi-bluetooth
sudo setcap cap_net_raw+eip $(eval readlink -f `which node`)
npm i noble
npm i node-red-contrib-beacon-scanner
```

Ajoutez le flot flow.collector.json à NodeRED.

### Côté backend

Déployez les containers Mosquitto, NodeRED et MongoDB.

Ajoutez le plugin [node-red-contrib-web-worldmap](https://flows.nodered.org/node/node-red-contrib-web-worldmap)

Ajoutez le flot flow.backend.json à NodeRED.
