# CampusIoT :: Tutoriel :: Décoder les trames LoRaWAN :fr:

Si ce tutoriel vous est utile, pensez à donner une étoile :star: en haut à droit.

## Introduction
TODO

## Decodage
TODO

Installer Node.js et npm

Installer la commande de lora-packet-decode https://github.com/anthonykirby/lora-packet

```bash
sudo npm install -g lora-packet
lora-packet-decode --base64 ADFGUkFEshgAdAoAAACyGADXQ5rzpZs=
lora-packet-decode --hex 003146524144B21800740A000000B21800D7439AF3A59B
lora-packet-decode \
        --appkey ec925802ae430ca77fd3dd73cb2cc588 \
        --nwkkey 44024241ed4ce9a68c6a8bc055233fd3 \
        --hex 40F17DBE4900020001954378762B11FF0D  \
```

## Déterminer le fabricant d'un équipement
On peut déterminer le fabricant d'un équipement à partir du DevEUI qui est communiqué dans les trames `JOIN REQUEST`.

```
npm install -g oui

oui 0018b22000000123
>> Adeunis RF
>> 283 rue NEEL
>> Crolles Isere 38920
>> France

oui 0025ca0a00000456
>> LS Research, LLC
>> W66 N220 Commerce Court
>> Cedarburg WI 53012
>> United States

```

## Déterminer le NetId et l'opérateur d'un équipement
On peut déterminer le NetId et l'opérateur d'un équipement à partir du DevAddr qui est communiqué dans les trames `DATA_UP`.

TODO

## Installation de lora-packet dans NodeRED
TODO
