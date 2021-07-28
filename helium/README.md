# Helium :: Tutoriel

[Helium](https://en.wikipedia.org/wiki/Helium_Systems) est un opérateur d'un réseau public LoRaWAN _crowdsourcé_. Les propriétaires de _hotspots_ LoRa (ie stations) sont récompensés avec de la [crypto-monnaie HNT](https://coinmarketcap.com/currencies/helium/).

## Création d'un compte Helium

![Sign Up](signup.png)

## Connection à la console

https://console.helium.com

![Login](login.png)

## Lister les équipements terminaux (device)

![Devices](devices.png)

## Ajouter un équipement (device)

![Détail d'un Device](devices-detail.png)

## Détail d'un équipement (device)

![Ajout d'un Device](devices-add.png)

## Lister les labels

Les labels sont utilisés pour l'intégration.

![Labels](labels.png)

## Détail d'un label

![Détail d'un Label](labels-detail.png)

## Lister les fonctions

![Fonctions](functions.png)

> Une bibliothèque de fonctions de décodage est disponible [ici](https://github.com/helium/console-decoders). Les fonctions de décodage ont la même définition que les décodeurs TTNv2.

## Détail d'une fonction de décodage de la charge utile d'un message

![Détail d'une fonction de décodage de la charge utile d'un message](functions-detail.png)

## Lister les intégrations

![Intégrations](integrations.png)

## Détail d'une intégration MQTT

Helium peut publier les messages relatives aux équipements vers un broker MQTT externe.

La charge utile est décodée dans la propriété `decoded` du message JSON.

Ce message LoRa n'a été reçu que par un seul hotspot Helium (ie station Helium)

```json
{
  "app_eui": "37363132FFFFFFFF",
  "decoded": {
    "payload": {
      "dataRate": 1,
      "gain": 16,
      "size": 16,
      "temperature": 43,
      "txpower": 14
    },
    "status": "success"
  },
  "dev_eui": "373631320078747B",
  "devaddr": "9D000048",
  "fcnt": 2,
  "hotspots": [
    {
      "channel": 6,
      "frequency": 867.7000122070312,
      "hold_time": 475,
      "id": "112sVdDJ4ajY8ziyvu1QxUw44skHeuSzzk5x6gAFeCEfufZ7Weao",
      "lat": 45.15376191524278,
      "long": 5.728159689661103,
      "name": "narrow-candy-gazelle",
      "reported_at": 1627050089668,
      "rssi": -116,
      "snr": -21.5,
      "spreading": "SF11BW125",
      "status": "success"
    }
  ],
  "id": "ec66d94c-36ac-4425-ba1a-406910bec89e",
  "metadata": {
    "adr_allowed": false,
    "cf_list_enabled": false,
    "labels": [
      {
        "id": "699edce5-55ea-4ab9-ae34-9946ade65e64",
        "name": "balloon",
        "organization_id": "cf997e03-a2b9-4f59-9339-059bb3a85fe7"
      }
    ],
    "multi_buy": 1,
    "organization_id": "cf997e03-a2b9-4f59-9339-059bb3a85fe7"
  },
  "name": "IMST_747B",
  "payload": "DgEQzAAAAAAAAAAAAAAAAA==",
  "payload_size": 16,
  "port": 2,
  "reported_at": 1627050089668,
  "uuid": "76b51b8a-09a8-45f4-b889-4368c30882a4"
}
```

![Détail d'une intégration MQTT](integrations-mqtt.png)

## Lister les flots

![Flots](flows.png)

## Lister les organisations

![Organizations](organizations.png)

## Lister les utilisateurs

![Users](users.png)

## Lister les crédits HNT

Le crédit initial en [HNT](https://coinmarketcap.com/currencies/helium/) est décrémenté à chaque réception de messages d'un des équipements.

![Data credits](datacredits.png)

## Ajouter un Hotspot (aka Miner)

https://www.helium.com/mine#hotspots