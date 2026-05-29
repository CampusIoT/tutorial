# CampusIoT :: NATS :: Tutoriel

## Objectif
L'objectif de ce tutoriel est de récupérer les mesures des capteurs gérés par la plateforme CampusIoT afin de les publier vers un broker pubsub NATS.

[NATS](https://docs.nats.io/) est un broker PubSub de messages.

Si ce tutoriel vous est utile, pensez à donner une étoile :star: en haut à droit.

## Etape 0: Prérequis
Installez Docker CE et Docker Compose sur votre machine
* https://docs.docker.com/install/
* https://docs.docker.com/compose/install/

## Etape 1: Installation

Lancez NATS avec Docker (sur votre machine)
```bash
docker pull nats:latest
docker run -p 4222:4222 -ti nats:latest
```

Installez NATS-CLI https://github.com/nats-io/natscli

## Etape 2: Pub-Sub avec NATS-CLI


https://nats.io/blog/nats-cli-pub-sub/


### Terminal Pub
```bash
nats publish --server localhost iot.balloon.1 "12°C;90%RH;700hPA"
```

```
15:16:51 Published 18 bytes to "iot.balloon.1"
```

```bash
nats publish --server localhost iot.balloon.1 "10°C;91%RH;690hPA"
```

```
15:17:08 Published 18 bytes to "iot.balloon.1"
```

```bash
nats publish --server localhost iot.balloon.2 "15°C;80%RH;790hPA"
```

```
15:21:08 Published 18 bytes to "iot.balloon.2"
```

### Terminal Sub
```bash
nats subscribe --server localhost iot.balloon.1
```

```
15:16:48 Subscribing on iot.balloon.1 
[#1] Received on "iot.balloon.1"
12°C;90%RH;700hPA


[#2] Received on "iot.balloon.1"
10°C;91%RH;690hPA
```

```bash
nats subscribe --server localhost iot.balloon.*
```

```
15:20:40 Subscribing on iot.balloon.* 
[#1] Received on "iot.balloon.2"
15°C;80%RH;790hPA
```

## Etape 3: Installation de NodeRED

Installez NodeRED et la contribution NATS https://flows.nodered.org/node/node-red-contrib-nats-suite

```bash
...
npm i node-red-contrib-nats-suite
```

TBC


## Etape 4 : MQTT and NATS

https://docs.nats.io/running-a-nats-service/configuration/mqtt#communication-between-mqtt-and-nats

TBC


## Etape 5 : WebSocket

https://docs.nats.io/running-a-nats-service/configuration/websocket

TBC


## Etape 6: Clustering


### Simple clustering

https://docs.nats.io/running-a-nats-service/configuration/clustering

### Jetstream clustering

https://docs.nats.io/running-a-nats-service/configuration/clustering/jetstream_clustering

TBC

### Running NATS on K8S

https://github.com/nats-io/k8s

TBC

## Etape 6: Superset

https://nats.io/blog/real-time-monitoring-solution-jetstream-risingwave-superset/


## Etape 7: MicroServices

https://nats.io/blog/mongodb-nats-connector/

