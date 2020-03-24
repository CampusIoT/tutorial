# LoRaCloud Location Solver :: Tutoriel

LoRaCloud est un service en ligne proposé par l'entreprise Semtech qui est le fondeur des composants LoRa.

LoRaCloud propose un service de géolocalisation d'équipements à partir d'informations dérivées du réseau (RSSI, TDOA).

Ce service est décrit ici https://www.loracloud.com/portal/geolocation

Il propose une API REST dont l'interface est décrite https://www.loracloud.com/documentation/geolocation?url=index.html

## Démarrage

Créez un compte utilisateur sur LoRaCloud https://www.loracloud.com/

Créez un Token pour l'utilisation de l'API https://www.loracloud.com/portal/geolocation/token_management

Testez les scripts suivants en utilisant le Token créé.

```bash
./singleframe.sh > singleframe.result.json
cat singleframe.result.json
```

```json
{
	"result": {
		"numUsedGateways": 7,
		"HDOP": 0.82,
		"locationEst": {
			"latitude": 51.498998,
			"longitude": -0.146996,
			"toleranceHoriz": 185
		},
		"algorithmType": "Tdoa"
	},
	"warnings": []
}
```

```bash
./multiframes.sh > multiframes.result.json
cat multiframes.result.json
```

```json
{
	"result": [{
		"numUsedGateways": 5,
		"HDOP": 1.0,
		"locationEst": {
			"latitude": 46.987555,
			"longitude": 6.9027,
			"toleranceHoriz": 75
		},
		"algorithmType": "Tdoa"
	}, {
		"numUsedGateways": 5,
		"HDOP": 1.0,
		"locationEst": {
			"latitude": 46.987555,
			"longitude": 6.9027,
			"toleranceHoriz": 75
		},
		"algorithmType": "Tdoa"
	}],
	"warnings": []
}
```


## Visualisation du résultat en GeoJSON

```bash
node res2geojson.js multiframes.json multiframes.result.json > multiframes.geojson
```

Ouvrez le fichier [multiframes.geojson](./multiframes.geojson) avec http://geojson.io
