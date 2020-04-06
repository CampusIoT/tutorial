# CampusIoT :: Tutoriel sur openSenseMap

openSenseMap est une plateforme ouverte de partage de mesures de données de capteurs environnementaux (température, humidité, PM2.5, PM10)  https://opensensemap.org

L'API REST de openSenseMap permet d'ajouter de nouvelles mesures. https://github.com/sensebox/openSenseMap-API

L'objectif de ce tutoriel est d'utiliser cette API pour ajouter des données produites par des endpoints enregistrés sur le réseau LoRaWAN de CampusIoT.

## Enregistrement d'un senseBox

Après avoir créer un compte sur https://opensensemap.org, créez un senseBox en utilisant la configuration manuelle du hardware. Ajoutez les mesures qui sont produites par votre endpoint LoRaWAN qui est enregistré sur CampusIoT.

## Test de l'API

Notez les identifiants de votre senseBox (`SENSEBOX_ID`) et de ses différents capteurs (`SENSOR_ID`).

Testez l'API avec le script suivant:
```bash
# Content-Type
ACCEPT_JSON="Accept: application/json"
ACCEPT_CSV="Accept: text/csv"
CONTENT_JSON="Content-Type: application/json"
CONTENT_CSV="Content-Type: text/csv"

# Operations
CURL="curl -s --insecure"
GET="${CURL} -X GET --header \""$ACCEPT_JSON"\""
POST="${CURL} -X POST --header \""$ACCEPT_JSON"\""

# SenseBox ID
SENSEBOX_ID="5e8a411a6feb9700XXXXXXXX"

# Sensor IDs
# temperature
SENSOR1_ID="5e8a411a6feb9700XXXXXXXX"

URL="https://api.opensensemap.org/boxes/${SENSEBOX_ID}/data"
${POST}  --data '{"'${SENSOR1_ID}'":10.0}' --header "$CONTENT_JSON" "${URL}"
```

## Redirection du traffic vers opensensemap

Démarrez un conteneur NodeRed avec le flot suivant:

```bash
TODO
```

```
TODO
```

Ouvrez la console de NodeRED http://localhost:1880

Entrez les credentials de votre organisation dans le noeud `MQTT CampusIoT`.

Renseignez le `DevEUI` du endpoint dans le topic du noeud `MQTT CampusIoT`.

Renseignez les indentifants `SENSEBOX_ID` et `SENSORx_IDv dans les variables du noeud `Convert to opensensemap data`.

Déployez le flot modifié.

Visualisez les données produites par votre endpoint `DevEUI`.