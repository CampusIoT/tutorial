# CampusIoT :: LoRaServer > Partie 1 :: Tutoriel :fr:

Si ce tutoriel vous est utile, pensez à donner une étoile :star: en haut à droit.

## Architecture et composants du LoRaServer
[Loraserver.io](https://www.loraserver.io/) est un network server LoRaWAN open-source.
Il est déployé sur une machine de l’IMAG lora.campusiot.imag.fr avec la composition Docker disponible sur https://github.com/CampusIoT/loraserver-docker.

Les principaux composants sont décrits dans la figure ci-dessous.
![Architecture](https://www.loraserver.io/img/architecture.png)

Dans le déploiement sur lora.campusiot.imag.fr, le service Mosquitto est sécurisé avec TLS (port 8883) et une authentification par username / password des organisations et des gateways. Les ACL par gateway et par organisation seront mises en place ASAP. Le port 1700 UDP vers le lora-gateway-bridge sera prochainement filtré par des raisons de sécurité.

Des containers supplémentaires ont été déployés pour le rendre opérationnel (dump des bases de données, log des messages MQTT, démo NodeRed, console Grafana …).

## NetID de CampusIoT
Le NetID officiel de l'Université Grenoble Alpes auprès de la LoRa Alliance pour CampusIoT est `0xC0002B` (NetID de Ttype 6).

## Rubriques
* [Ajouter une application et des équipements](./README-app.md)
* [Installer une nouvelle gateway](./README-gateway.md)
* [Administrer une organisation](./README-org.md)
* [Administrer du service](./README-admin.md)
