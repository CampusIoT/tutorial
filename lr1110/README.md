# CampusIoT :: Tutoriel sur le Semtech LR1110

Le composant LR1110 de Semtech est un transmetteur LoRa (rx tx) qui a également la capacité de "sniffer" les réseaux WiFi environnants et les signaux des constellations GNSS (GPS/ BeiDou).

Il offre la possibilité des réaliser des endpoints dédiés à la géolocalisation avec une faible consommation énergétique.

## LR1110 LoRa Edge 

Ultra-low power platform that integrates a long range LoRa® transceiver, multi-constellation scanner and passive Wi-Fi AP MAC address scanner targeting asset management applications.

Low-Power High-Sensitivity LoRa/(G)FSK Half-Duplex RF Transceiver

    Worldwide ISM frequency bands support in the range 150 - 960MHz
    Low Noise Figure RX front-end for enhanced LoRa/ (G) FSK sensitivity
    High power PA path +22 dBm
    High efficiency PA path +15 dBm
    Integrated PA regulator supply selector to simplify dual power +15/+22dBm with one board implementation
    Able to support world-wide multi-region BOM, the circuit adapts to matching network to satisfy regulatory limits
    Fully compatible with the SX1261/2/8 family and the LoRaWAN® standard, defined by the LoRa Alliance®

Multi-Purpose Radio Front-End targeting geo-positioning purposes

    GNSS (GPS/ BeiDou) low-power scanning
    802.11b/g/n Wi-Fi ultra-low-power passive scanning
    150 - 2700 MHz continuous frequency synthesizer range
    High bandwidth RX ADC (up to 24 MHz DSB)
    Digital baseband processing


References:
* https://www.semtech.com/products/wireless-rf/lora-transceivers/LR1110#download-resources


## LR1110 Software

* https://github.com/Lora-net/lr1110_driver

## Flot NodeRED avec les services de LoRaCloud


Lancez le container NodeRED
```bash
mkdir -p data/nodered
mkdir -p data/log
docker run -d \
    -p 1880:1880 \
    -v $PWD/data/nodered:/data \
    -v $PWD/data/log:/log \
    --name nodered-lr1110 nodered/node-red
open http://127.0.0.1:8080
```

Ajoutez le flot [flows.json](./flows.json) via la console Web.

> Il reste à configurer les credentials des brokers MQTT des réseaux sur lesquels sont enregistrés les LR1110.

## Press Release

https://iotbusinessnews.com/2020/02/24/50343-semtech-releases-a-new-portfolio-of-solutions-lora-edge-to-simplify-and-accelerate-iot-applications/

### LA SOLUTION DE GÉOLOCALISATION LORA EDGE DE SEMTECH INTÈGRE GNSS ET WI-FI
https://vipress.net/la-solution-de-geolocalisation-lora-edge-de-semtech-integre-gnss-et-wi-fi/

25 Fév 2020

Semtech, fournisseur de semiconducteurs analogiques et à signaux mixtes et d’algorithmes complexes, annonce le lancement de LoRa Edge, une nouvelle plateforme basée sur la technologie LoRa utilisant un logiciel faible consommation et polyvalent, qui doit permettre un large portefeuille d’applications pour la gestion d’actifs en intérieur comme en extérieur, ciblant les marchés de l’industrie, du bâtiment et la domotique, de l’agriculture, des transports et de la logistique.
Le premier produit de ce portefeuille est une solution de géolocalisation qui vise le développement des objets connectés pour les applications de gestion d’actifs, intégrant des capacités de détection utilisant les technologies faible consommation Wi-Fi et GNSS (Global Navigation Satellite System) associées à des services Lora Cloud de géolocalisation et de gestion des produits connectés, permettant de réduire significativement les coûts et la complexité de la localisation et de la gestion des dispositifs connectés sur un réseau IoT.
« Semtech offre continuellement des solutions IoT qui simplifient et accélèrent le développement des applications LPWAN. Les services LoRa Edge et de géolocalisation LoRa Cloud permettent aux clients de développer des applications à très faible consommation pour un grand nombre de marchés, ce qui va favoriser l’adoption massive de la technologie LoRa dans le monde des objets connectés », explique Pedro Pachuca, directeur au sein de la division IoT sans fil (IoT Wireless) au du groupe ‘Wireless and Sensing Products’ de Semtech.
D’ici 10 ans, on estime que 500 milliards d’appareils seront connectés à Internet, car les entreprises continueront de mettre en œuvre des stratégies de développement centrées sur les réseaux d’objets connectés ; la majorité de ces objets connectés exigent une certaine forme de capacité de localisation que ce soit au moment de leur installation ou au cours de leur cycle de vie. La plateforme de géolocalisation LoRa Edge permettra aux fournisseurs de solutions de bénéficier des capacités uniques de géolocalisation de la technologie LoRa ainsi que des capacités de détection de la technologie GNSS (utilisée par les GPS) et du Wi-Fi, le tout dans une solution mono-puce, permettant aux clients de choisir le meilleur outil de localisation pour l’application à mettre en œuvre.


En faisant l’économie de composants externes GNSS et Wi-Fi, la solution LoRa Edge réduit les coûts matériels pour les dispositifs et limite significativement la complexité du système et de l’approvisionnement en composants. En ajoutant les services de géolocalisation LoRa Cloud, qui permettent les calculs — simples à utiliser et économiques — de la localisation via des techniques basées sur la triangulation TDOA, la technologie GNSS et le Wi-Fi, afin de réduire largement les exigences de puissance des dispositifs et améliorer la gestion des actifs, la solution LoRa Edge permet aux clients de mieux gérer le coût total de possession de leur réseau IoT, en ne payant que lorsqu’un objet a besoin d’être localisé. Un service inégalé de chargement des clés de sécurité, directement réalisé sur le site de fabrication, et un service de ‘Join Server’ sécurisé achèvent de simplifier le développement des solutions IoT, répondant ainsi aux attentes précises des clients en matière de sécurité.


Caractéristiques principales du produit :


Système radio frontal multi-usage
* Plage du synthétiseur de fréquence continue : 150-2700 MHz
* Analyse GPS/BeiDou
* Analyse Wi-Fi passive

Émetteur-récepteur RF LoRa/(G)FSK faible consommation
* Compatible avec les bandes de fréquence internationales dans la plage 150-960 MHz
* PA haute puissance +22 dBm
* PA haute efficacité +15 dBm
* Totalement compatible avec le standard LoRaWAN®

Moteur de cryptographie
* Compatibilité matérielle pour les algorithmes de chiffrement/déchiffrement AES-128
* Prise en charge des paramètres des dispositifs tels que DevEUI et JoinEUI
* Protège les données sensibles telles que les clés de chiffrement
* Stocke les clés NwkKey, AppKey, tel que défini dans le standard LoRaWAN

Le tout premier chipset LoRa Edge intégrant la géolocalisation (LR1110) est déjà disponible ; d’autres produits vont compléter l’offre de ce portefeuille au cours du premier semestre 2020.