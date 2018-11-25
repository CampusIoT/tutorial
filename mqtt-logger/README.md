# CampusIoT :: MQTT Logger :: Tutoriel :fr:
[mqtt-logger](https://github.com/campusiot/mqtt-logger) est un utilitaire qui permet de journaliser simultanément les flux MQTT de plusieurs topics et brokers dans un fichier

## Etape 0: Prérequis
Installer Docker CE et Docker Compose sur votre machine
* https://docs.docker.com/install/
* https://docs.docker.com/compose/install/

## Etape 1: Construire l'image campusiot/mqtt-logger
```bash
git clone https://github.com/campusiot/mqtt-logger.git mqtt-logger
cd mqtt-logger
docker build -f Dockerfile -t campusiot/mqtt-logger:latest .
```

## Etape 2: Configurer
```bash
mkdir -p ~/configuration/mqtt-logger/
mkdir -p ~/data/mqtt-logger/
cp settings.CAMPUSIOT_MQTTS.json ~/configuration/mqtt-logger/settings.json
(cd ~/configuration/mqtt-logger ; wget https://raw.githubusercontent.com/CampusIoT/campusiot-certs/master/mqtt/ca.crt)
touch  ~/data/mqtt-logger/msg.log

# Edit topic, username and password
vi ~/configuration/mqtt-logger/settings.json
```

## Etape 3: Lancer le container
```bash
docker run -d \
  -v ~/configuration/mqtt-logger/settings.json:/usr/src/app/settings.json:ro \
  -v ~/configuration/mqtt-logger/ca.crt:/usr/src/app/ca.crt:ro \
  -v ~/data/mqtt-logger/:/data/ \
  --name mqtt-logger campusiot/mqtt-logger:latest
```

## Etape 4: Surveiller le contenu du journal
```bash
tailf ~/data/mqtt-logger/msg.log
```
