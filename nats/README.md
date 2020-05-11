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

## Etape 2: Installation de NodeRED
Installez NodeRED et la contribution NATS
```bash
...
npm i node-red-contrib-natsio
```

TBC

