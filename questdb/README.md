# CampusIoT :: QuestDB :: Tutoriel :fr:

## Objectif
QuestDB est une base de données pour le stockage efficace de séries temporelles. https://github.com/questdb/questdb

L'objectif de ce tutoriel est de récupérer les mesures des capteurs gérés par la plateforme CampusIoT afin de les archiver dans une base QuestDB et de les visualiser en temps réel au moyen de Grafana.

Si ce tutoriel vous est utile, pensez à donner une étoile :star: en haut à droit.

## Etape 0: Prérequis
Installez Docker CE et Docker Compose sur votre machine
* https://docs.docker.com/install/
* https://docs.docker.com/compose/install/

## Etape 1: Journaliser le flot MQTT de messages dans une base QuestDD 
Lancez NodeRed avec Docker (sur votre machine)
```bash
docker pull questdb/questdb
docker run -p 9000:9000 -p 8812:8812 questdb/questdb
```
