# CampusIoT :: LoRaServer :: Tutoriel :fr:

## Architecture et composants du LoRaServer
[Loraserver.io](https://www.loraserver.io/) est un network server LoRaWAN open-source.
Il est déployé sur une machine de l’IMAG lora.campusiot.imag.fr avec la composition Docker disponible sur https://github.com/CampusIoT/loraserver-docker.

Les principaux composants sont décrits dans la figure ci-dessous.
![Architecture](https://www.loraserver.io/img/architecture.png)

Dans le déploiement sur lora.campusiot.imag.fr, le service Mosquitto est sécurisé avec TLS (port 8883) et une authentification par username / password des organisations et des gateways. Les ACL par gateway et par organisation seront mises en place ASAP. Le port 1700 UDP vers le lora-gateway-bridge sera prochainement filtré par des raisons de sécurité.

Des containers supplémentaires ont été déployés pour le rendre opérationnel (dump des bases de données, log des messages MQTT, démo NodeRed, console Grafana …).

Remarque: Le NetID est `0x00`. Une demande de NetID est en cours auprès de LoRa Alliance.

## Gestion d’une organisation
Si vous êtes adminstrateur d'une organisation, vous devez au minimum créer un device-profile et un service-profile.

[Plus de détails](https://www.loraserver.io/lora-app-server/use/organizations/)

### Créer un device-profile
Créer (au moins) un device-profile `CLASS_A_OTAA` depuis `Menu > Device-profiles > + Create`

https://lora.campusiot.imag.fr/#/organizations/1/device-profiles

![Device Profile](device-profile.png)

[Plus de détails](https://www.loraserver.io/lora-app-server/use/device-profiles/)

### Créer un service-profile
Créer un service-profile `DEFAULT` depuis `Menu > Service-profiles > + Create`

https://lora.campusiot.imag.fr/#/organizations/1/service-profiles

![Service Profile](service-profile.png)

[Plus de détails](https://www.loraserver.io/lora-app-server/use/service-profiles/)

### Créer une application
Une application est un ensemble de devices envoyant le même format de données et partageant le même service-profile (utiliser `DEFAULT`).

Créer une application depuis `Menu > Applications > + Create`
https://lora.campusiot.imag.fr/#/organizations/1/applications


Les valeurs de “`Payload codec`” sont “`None`”, “`Cayenne LPP`”, “`Custom JavaScript codec functions`”

Le “`Payload codec`” permet de spécifier (ou non) un codec pour décoder le payload des frames montantes et encoder les frames descendantes.

Le “`Payload codec`” peut être mis à jour à tout moment. Une errreur dans le code Javascript ou dans l’encodage LPP produit une erreur dans l’onglet “`Live LoRaWAN Frames`”


Pour plus d’information https://www.loraserver.io/lora-app-server/use/applications/

> Remarques
> L’encodage “Cayenne LPP” est spécifié ici https://mydevices.com/cayenne/docs/lora/#lora-cayenne-low-power-payload
> Les “Custom JavaScript codec functions” ne supportent pas des libraries utiles comme Buffer ...
>Des codec Javascript pour des devices LoRaWAN sont fournis dans https://github.com/CampusIoT/payload-codec/tree/master/src/main/javascript

[Plus de détails](https://www.loraserver.io/lora-app-server/use/applications/)

### Enregistrer un device OTAA
Un device OTAA est un endpoint LoRaWAN envoyant le même format de données et partageant le même service-profile (utiliser `CLASS_A_OTAA` ou un autre plus spécifique que vous aurez créé). Il utilise la procédure par défaut OTAA pour son admission dans le réseau.

Créer un device depuis une application créée (`Menu > Applications`) en utilisant les `DevEUI` (64 bits soit 16 caractères hexadécimaux) inscrit sur l’étiquette collée sur le endpoint LoRaWAN ou sur son emballage d’expédition.
![Add Device](add-device.png)



Ajouter ensuite l’`AppKey` (AES 128bits soit 32 caractères hexadécimaux) fournie avec le endpoint (étiquette amovible, fichier Excel envoyé par le vendeur, …). Penser à valider l’enregistrement de la clé avec le bouton `Set Device-Keys`.
![Set Device Keys](set-device-keys.png)


> A noter : l’`AppKey` par défaut peut être modifié sur la plupart des endpoints via une liaison USB, NFC, BLE via une application mobile (Android, iOS) fournie par le constructeur.

[Plus de détails](https://www.loraserver.io/lora-app-server/use/devices/)

### Enregistrer un device ABP
TODO

[Plus de détails](https://www.loraserver.io/lora-app-server/use/devices/)

### Afficher les messages d’un device
Afficher (en temps réel) les données envoyées par un device depuis l’onglet “Live LoRaWAN Frames” et avec l’onglet “Live Data Device” pour les valeurs du payload décodées avec le codec spécifié pour l’application.

> Remarque: le serveur n’archive pas les données. Il faut utiliser l’onglet “Integrations” de l’application.

### Récupérer les flots MQTT de messages
MQTT est le moyen par défaut pour récupérer les messages envoyés par les devices
https://www.loraserver.io/lora-app-server/integrate/data/

Le flot de messages envoyés par les devices des applications peut récupérer via des clients MQTT comme mosquitto_sub (en ligne de commande), mqtt-spy, mqtt-lens pour Chrome ...

Installer `mosquitto_sub` avec
```
sudo apt-get install -y mosquitto-clients
```

Il faut installer dans le répertoire courant le certificat ca.crt dec l’autorité de certification du broker MQTT avec la commande suivante
```
wget https://raw.githubusercontent.com/CampusIoT/campusiot-certs/master/mqtt/ca.crt
```

Actuellement, les commandes à utiliser sont:

```
BROKER=lora.campusiot.imag.fr
MQTTUSER=org1 # le username de votre ORGANISATION (ce n’est pas le username de votre compte utilisateur)
MQTTPASSWORD=__SUPER_SECRET_TO_CHANGE__
TLS="--cafile ca.crt -p 8883"

# Receive applications messages
mosquitto_sub -h $BROKER -t "application/#" -u $MQTTUSER -P $MQTTPASSWORD -v  $TLS

# Receive Gateways stats
mosquitto_sub -h $BROKER -t "gateway/#" -u $MQTTUSER -P $MQTTPASSWORD -v  $TLS
```

> Remarque: je mettrai en place dès possible des ACL par topic pour les gateways et les organisations.

### Envoyer un downlink à un device
MQTT est le moyen par défaut pour envoyer un message descendant (down) vers un device https://www.loraserver.io/lora-app-server/integrate/data/

Actuellement, les commandes à utiliser sont:

```
BROKER=lora.campusiot.imag.fr
MQTTUSER=org1 # le username de votre ORGANISATION (ce n’est pas le username de votre compte utilisateur)
MQTTPASSWORD=__SUPER_SECRET_TO_CHANGE__
TLS="--cafile ca.crt -p 8883"

applicationID=1
devEUI=1234567890abcdef

# Send Downlink Messages (dn)
mosquitto_pub -h $BROKER -u $MQTTUSER -P $MQTTPASSWORD $TLS  -t "application/$applicationID/device/$devEUI/tx" -m '{"reference": "abcd1234","confirmed": true, "fPort": 10,"data":"SGVsbG8gQ2FtcHVzSW9UICE="}'
```

Le champs data contient le message binaire encodé en base64.
Dans l’exemple, le message est “Hello CampusIoT !”

```
echo `echo SGVsbG8gQ2FtcHVzSW9UICE= | base64 --decode`
echo "Hello CampusIoT !" | base64
```
