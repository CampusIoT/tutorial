# CampusIoT :: Collos :: Tutoriel :fr:

## Collos
[Collos (Collaborative Location Service)](http://preview.collos.org/Home/About) est un service de géolocalisation d'équipements basés sur l'analyse d'émission de messages des équipements.

Les technologies radio considérées par Collos sont :
* LoRa,
* Wifi,
* Bluetooth.

Les données utilisées pour la résolution de la position sont :
* la position (latitude, longitude) des passerelles réceptrices
* le qualité du signal recu (RSSI et SNR pour LoRa).
* l'estampille temporelle de l'arrivée du message à la passerelle

Collos propose plusieurs algorithmes de résolution de géolocalisation via des APIs REST décrites avec le standard OpenAPI.

Les APIs Collos sont accessibles au moyen d'une clé.

Plusieurs network server LoRaWAN (ttn, loraserver.io) peuvent utiliser Collos moyennement leur configuration avec la clé fournie.

## Démarrage

TBC


## Références
* [Richard Lansdowne - LoRa Geolocation](https://www.youtube.com/watch?v=WEqLESKW6N8)
* [TDoA-Based Outdoor Positioning with Tracking Algorithm in a Public LoRa Network](https://www.hindawi.com/journals/wcmc/2018/1864209/)
* [A. R. Kulaib, R. M. Shubair, M. A. Al-Qutayri, and J. W. P. Ng, “An overview of localization techniques for wireless sensor networks,” in Proceedings of the 2011 International Conference on Innovations in Information Technology, IIT 2011, pp. 167–172, are, April 2011](https://ieeexplore.ieee.org/document/5893810)
* [Luo, Mingzhi & Chen, Xiang & Cao, Shuai & Zhang, Xu. (2018). Two New Shrinking-Circle Methods for Source Localization Based on TDoA Measurements. Sensors (Basel, Switzerland). 18. 10.3390/s18041274.](https://www.researchgate.net/publication/324679575_Two_New_Shrinking-Circle_Methods_for_Source_Localization_Based_on_TDoA_Measurements)
