# Ecole [MPLS](https://alpes-dauphine.maisons-pour-la-science.org/) 2025 :: Atelier GNSS (La Mure)

Auteur: Didier DONSEZ, GINP-UGA.

> Ce support est sous licence [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/). Les exemples de croquis fournis ne sont pas couverts par cette licence. Veuillez vous référer à la licence de chacun.

**[Sommaire](README.md)**

## Glossaire

| Terme/Acronyme | Explication |
| -------------- |------------ |
| Constellation | Ensemble de satellites réalisant une même service |
| Constellation GNSS | Ensemble de satellites embarquant des horloges atomiques et diffusant des messages permettant le calcul du temps précis et de la position par des récepteurs GNSS. La constellation américaine GPS est constituée de 24 satellites placés sur 6 plans orbitaux en orbite moyenne (MEO) à environ 20000 Kms |
| GNSS | [Géolocalisation et Navigation par un Système de Satellites ou ***Global Navigation Satellite System***](https://fr.wikipedia.org/wiki/Syst%C3%A8me_de_positionnement_par_satellites)|
| DGNSS | [GNSS différentiel](https://fr.wikipedia.org/wiki/GPS_diff%C3%A9rentiel) |
| [AGPS](https://fr.wikipedia.org/wiki/Assisted_GPS) | Le GPS assisté accélère de démarrage à froid en communiquant au récepteur GNSS les éphémérides téléchargées depuis Internet (3G, 4G ...) |
| RTK | [Cinématique temps réel ou Real Time Kinematic](https://fr.wikipedia.org/wiki/Cin%C3%A9matique_temps_r%C3%A9el)|
| [Centrale inertielle](https://fr.wikipedia.org/wiki/Centrale_%C3%A0_inertie) | instrument de navigation capable d'intégrer les mouvements d'un mobile (accélération et vitesse angulaire) pour estimer son orientation (angles de roulis, de tangage et de cap), sa vitesse linéaire et sa position. Certains modules GNSS sont dotés d'une centrale inertielle afin de continuer à fournir une position malgré la perte (passage dans un tunnel) ou le leurrage des signaux GNSS.|
| IMU | Inertial Measurement Unit ou Centrale inertielle |
| [MEMS](https://en.wikipedia.org/wiki/MEMS) | micro-electromechanical systems |
| Paramêtres orbitaux | |
| Ephémérides | Tables astronomiques par lesquelles on détermine, pour chaque jour, la valeur d'une grandeur caractéristique d'un objet céleste, comme un satellite artificiel de positionnement. Dans le cas des systèmes GNSS, ces tables sont diffusées périodiquement vers les récepteurs GNSS par les satellites eux-même. |
| TLE | [Two-line elements](https://fr.wikipedia.org/wiki/Param%C3%A8tres_orbitaux_%C3%A0_deux_lignes) |
| NMEA 0813 | Format de données textuel utilisé par des systèmes de navigation (GNSS, centrale inertielle ...) |
| GNSS Raw Data| |
| [RTKLib](https://www.rtklib.com/) | logiciel libre pour un positionnement GNSS standard et précis |
| DOP ou GDOP | [***Geometric dilution of precision*** (GDOP) ou Dilution of precision (DOP)](https://fr.wikipedia.org/wiki/Geometric_dilution_of_precision) |
| HDOP | ***Horizontal Dilution of precision*** |
| VDOP | ***Vertical Dilution of precision*** |
| TDOP | ***Time Dilution of precision*** |
| Démarrage à froid | A la mise sous tension, le module GNSS ne dispose pas d'éphérémides récentes. Il doit attendre la diffusion périodique de celles-ci pour pouvoir calculer la position de son mobile porteur. |
| Démarrage à chaud | A la mise sous tension, le module GNSS dispose d'éphérémides récentes. Celles-ci sont sauvegardées dans une mémoire sauvegardée par une petite pile. |
| Fixe | Après la mise sous tension, le module est en mesure de calculer et de fournir la position du mobile porteur. Cela se traduit parfois par le clignotement de la LED PPS (bleue sur les modules Sparkfun XA1110). |
| Brouillage GPS | effets d'une énergie électromagnétique due à des émissions, rayonnements ou inductions qui dégrade, entrave ou interrompt le fonctionnement des récepteurs GPS. Exemple: Aéroport de Nantes-Atlantique (7,2 millions de passagers par an) le 21 avril 2017 |
| Leurrage GPS | technique consistant à émettre de signaux GPS synthétiques pour fausser le calcul de temps et de la position par des récepteurs GPS. C'est un des risques cyber pour les entreprises et gouvernements |
| Dispositif anti-leurrage | Système de détection du leurrage GNSS. Certains modules GNSS sont dotés de tels systèmes. |
| [SAASM](https://en.wikipedia.org/wiki/Selective_availability_anti-spoofing_module) | |
| dBm | [decibel-milliwatts](https://en.wikipedia.org/wiki/DBm)|
| dBi | [dB(isotropic)](https://en.wikipedia.org/wiki/Decibel#Antenna_measurements)|
| RSSI | [Received signal strength indicator](https://en.wikipedia.org/wiki/Received_signal_strength_indicator)|
| SNR | [Signal-to-Noise Ratio](https://en.wikipedia.org/wiki/Signal-to-noise_ratio) |
| ANRF | [Agence Nationale des fréquences](https://www.anfr.fr). [Elle est en charge de lutter contre le brouillage et le leurrage](https://www.anfr.fr/controler/traitement-des-brouillages/les-enquetes-de-lanfr) |
| NTRIP | ***Network and Transport of RTCM via Internet Protocol***;  protocole de transmission des corrections RTCM via IP à des rovers RTK |
| RTCM | format des données specifié par ***Radio Technical Commission for Maritime Services*** pour décrire les corrections différentielles des constellations GNSS |
| Rover | Equipement mobile consommant des messages RTCM afin d'améliorer la précision de la position calculée par le module GNSS RTK |
| Base | Equipement fixe et dont la position est connue, produisant des messages RTCM consommés par des rovers|
| Caster | Service diffusant vers des rovers les messages RTCM produits par une ou plusieurs bases |
| Centipede | Service contributif et public de diffusion de messages RTCM |
| UART | Interface série d'un microcontrôleur. Universelle. Les micro-contrôleurs ne disposent que peu d'interfaces UART (1 à 3). |
| SPI | Bus de communication entre un microcontrôleur et des périphériques. Certains modules GNSS disposent d'une interface SPI. |
| I2C | Bus de communication entre un microcontrôleur et des périphériques. Certains modules GNSS disposent d'une interface SPI. |
| PPS | ***Pulse-per-second***; implusion générée à chaque seconde du temps GNSS par le module GNSS. Cette impulse peut être utilisée par le micro-contrôleur pour synchroniser finement son horloge interne et pour dater finement des événements (arrivée d'un message ...) |
| PPM | mesure de performance en stabilité d'un [oscillateur](https://fr.wikipedia.org/wiki/Oscillateur_(%C3%A9lectronique)). Elle est définie par la variation de la fréquence sur une durée et dans des conditions environnementales spécifiées |
| UTC | Temps universel coordonné ou ***Universal Time Coordinated*** |
| GMT | temps moyen de Greenwich ou ***Greenwich Mean Time*** |
| 1/1/1970 00:00:00 UTC | [Date de début](https://fr.wikipedia.org/wiki/Epoch) du temps POSIX / UNIX. Aussi appelé ***epoch Unix***|
| 6/1/1980 00:00:00 UTC| [Date de début](https://fr.wikipedia.org/wiki/Epoch) du temps GPS. Aussi appelé ***epoch GPS*** |
| IoT | Internet des Objets ou ***Internet of Things*** |
| FSK |  Modulation radio pour des communications radio longue distance (***long range***) |
| LoRa | Modulation radio pour des communications radio longue distance (***long range***) basse consommation d'énergie (***low power***) pour l'IoT |
| LoRaWAN | Spécification d'un protocole de communication dans le réseau (***long range***) d'équipements (***low power***) IoT. Il s'appuie sur plusieurs modulations : FSK, LoRa, LR-FHSS |
| Meshtastic | protocole de communication basé sur la modulation LoRa pour des réseaux maillés (***mesh***) d'équipements IoT |
| ESP-Now | [Protocole de communication directe par Wifi entre des ESP32](https://www.espressif.com/en/solutions/low-power-solutions/esp-now) |
| NB-IoT | |
| LTE-M | |
| RTLS | Real Time Locating System |
| Ranging | télémétrie pour mesurer une distance entre 2 ou plusieurs objets fixes ou mobiles |
| ToF | Time of Flight ou temps de vol|
| TWR | Two-Way Ranging. télémétrie avec temps de vol |
| TDOA | [Time difference of arrival](https://en.wikipedia.org/wiki/Time_of_arrival) |
| AoA | Angle of Arrival |
| Direction Finding | |
| UWB | ultra-wideband. |
| Beacon | petit boîtier physique qui utilise la connexion Bluetooth Low Energy (BLE). Il émet à intervalle régulier des signaux qui sont lus directement par un smartphone ou une tablette quand celui-ci arrive à proximité des balises. |
| SDR | Software Defined Radio ou Radio Logicielle |
| GNSS offloading | |
| ***GIS*** ou [SIG](https://fr.wikipedia.org/wiki/Syst%C3%A8me_d%27information_g%C3%A9ographique)  | Système d'information géographique: système d'information conçu pour recueillir, stocker, traiter, analyser, gérer et présenter tous les types de données spatiales et géographiques. Les applications sont par exemple, les cadastres, les réseaux d'eau, de gaz, d'électricité, les systèmes de gestion des batiments (BMS) ... |
| [QGIS](https://fr.wikipedia.org/wiki/QGIS)| logiciel SIG (système d'information géographique) libre multiplate-forme|
| [Geofencing](https://fr.wikipedia.org/wiki/G%C3%A9orep%C3%A9rage) | Le géorepérage ou gardiennage virtuel (en anglais, geofence ou geofencing) est une fonction d'un logiciel de géolocalisation qui permet de surveiller à distance la position et le déplacement d'un objet et de prendre des mesures si la position ou le déplacement s'écarte de certaines valeurs fixées d'avance. |
| [GPX](https://fr.wikipedia.org/wiki/GPX_(format_de_fichier)) | format de fichier permettant l'échange de coordonnées géographiques provenant d'un récepteur GNSS. Il est utilisé par les applications et les réseaux sociaux sportifs |
| [GeoJSON](https://fr.wikipedia.org/wiki/GeoJSON) | format ouvert d'encodage d'ensemble de données géospatiales simples utilisant la norme JSON  |
| POI | Point of Interest ou Point d'intéret |
| ZOI | Zone of Interest ou Zone d'intéret |
| [EXIF](https://fr.wikipedia.org/wiki/Exchangeable_image_file_format) | Exchangeable image file format est une spécification de format de fichier pour les images. Il permet de décrire entre autre les coordonnées géographiques au sein du fichier image. Ces coordonnées peuvent être exploitées par des personnes malveillantes (vie privée, informations stratégiques ...) quand les images sont rendues publiques (réseaux sociaux ...). |
| [ExifTool](https://exiftool.org/)| Outil en ligne de commande permettant la manipulation des données EXIF dans les fichiers image |
| [GeoCode](https://fr.wikipedia.org/wiki/Code_g%C3%A9ographique) | |
| [GeoHash](https://fr.wikipedia.org/wiki/Geohash) | fonction de hachage qui subdivise la surface terrestre selon une grille hiérarchique. |
| [HexGrid](https://www.redblobgames.com/grids/hexagons/implementation.html) | fonction de hachage multi-niveau de coordonnées géographiques. La sphére terrestre est représentée comme une grille d'hexagones. A chaque niveau, chaque hexagone couvre une aire terrestre identique. |
| [OpenStreetMap](https://fr.wikipedia.org/wiki/OpenStreetMap) | base de données géographique contributive et gratuite |

## Comparison of satellite navigation orbits

Source: Wikimedia

![Comparison of satellite navigation orbits](https://upload.wikimedia.org/wikipedia/commons/b/b4/Comparison_satellite_navigation_orbits.svg)
