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

## Installation de lora-packet dans NodeRED
TODO
