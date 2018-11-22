# CampusIoT :: NodeRED :: Tutoriel :fr:

[NodeRED](https://nodered.org/) est un canevas de traitement de flots de données. Il permet la programmation visuelle des chaines de traitement de données. Il est très populaire pour le prototypage d'applications IoT.

## Etape 0: Prérequis
Installer Docker CE et Docker Compose sur votre machine
* https://docs.docker.com/install/
* https://docs.docker.com/compose/install/

## Etape 1: Journaliser le flot MQTT de messages dans un fichier avec NodeRed
Lancer NodeRed avec Docker (sur votre machine)
```bash
docker run -it -p 1880:1880 --name campusiot-nodered nodered/node-red-docker
```

Ouvrir l’interface de NodeRed dans un navigateur Web http://127.0.0.1:1880
```bash
open http://127.0.0.1:1880
```

Créer le “flot” en important le JSON suivant (Menu > Import)
```json
[{"id":"9d6b9737.6ee6a8","type":"mqtt in","z":"b3a2df4.51c83a","name":"campusiot","topic":"#","qos":"2","broker":"61ca344b.cfb484","x":210,"y":180,"wires":[["7fea5047.da2c5","4ece3642.56654"]]},{"id":"7fea5047.da2c5","type":"debug","z":"b3a2df4.51c83a","name":"","active":true,"tosidebar":true,"console":false,"tostatus":false,"complete":"false","x":510,"y":180,"wires":[]},{"id":"4ece3642.56654","type":"file","z":"b3a2df4.51c83a","name":"msg.log","filename":"msg.log","appendNewline":true,"createDir":true,"overwriteFile":"false","x":500,"y":260,"wires":[[]]},{"id":"61ca344b.cfb484","type":"mqtt-broker","z":"","name":"campusiot","broker":"lora.campusiot.imag.fr","port":"8883","tls":"11b0c2f3.c55f2d","clientid":"","usetls":true,"compatmode":true,"keepalive":"60","cleansession":true,"birthTopic":"","birthQos":"0","birthPayload":"","closeTopic":"","closeQos":"0","closePayload":"","willTopic":"","willQos":"0","willPayload":""},{"id":"11b0c2f3.c55f2d","type":"tls-config","z":"","name":"","cert":"","key":"","ca":"","certname":"","keyname":"","caname":"ca.crt","servername":"","verifyservercert":false}]
```

Editer le noeud mqtt-in pour chahger le topic, le ca.crt pour la configuration SSL, le username et password MQTT.
Le certificat se récupère au moyen de 
```bash
wget https://raw.githubusercontent.com/CampusIoT/campusiot-certs/master/mqtt/ca.crt
```

Afficher le journal des messages avec
```bash
docker exec -it campusiot-nodered tailf /usr/src/node-red/msg.log
```

Remarque : Vous pouvez monter un volume local pour rendre persistant le journal dans votre répertoire courant en ajoutant `-v $PWD/msg.log:/usr/src/node-red/msg.log` à la commande docker précédente
```bash
touch $PWD/msg.log
docker run -it -p 1880:1880 -v $PWD/msg.log:/usr/src/node-red/msg.log --name campusiot-nodered nodered/node-red-docker
```
Afficher le flot de messages écrits dans le journal `msg.log`
```bash
tail -f $PWD/msg.log
```
## Etape 2: Journaliser le flot MQTT de messages dans une base time-series InfluxDB avec NodeRed
TODO
* https://github.com/CampusIoT/loraserver-docker/blob/master/nodered.yml
* https://github.com/CampusIoT/loraserver-docker/blob/master/influxdb.yml
* https://github.com/CampusIoT/payload-codec/tree/master/src/main/javascript

## Etape 3: Visualiser les séries temporelles de la base time-series InfluxDB avec Chronograf
TODO

## Etape 4: Visualiser les séries temporelles de la base time-series InfluxDB avec Grafana
TODO
* https://github.com/CampusIoT/loraserver-docker/blob/master/grafana.yml

## Etape 5: Créer une alerte Mail et SMS avec Kapacitor
TODO

## Etape 6: Journaliser le flot MQTT de messages dans une base time-series OpenTSDB avec NodeRed
TODO

## Etape 4: Visualiser les séries temporelles de la base time-series OpenTSDB avec Grafana
TODO
