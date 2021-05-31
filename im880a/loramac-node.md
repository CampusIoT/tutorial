# LoRaMac-node sur LoRaMote

![LoRaMote+st-linkv2](./figs/LoRaMote+st-linkv2.png)  
**Fig. 1: LoRaMote + st-linkv2**

Pour commencer la LoRaMote est plus simple car

- elle a longtemps été la plateforme par défaut du [dépot LoRaMac](https://github.com/Lora-net/LoRaMac-node) utilisée pour la certification des noeuds par semtech
- on peut directement connecter le jtag pour la flasher
- les paquets sont directement visibles dans TTN pour tester
- par contre, comment accéder au lien série ? 

### Compilation 

Il faut ensuite rapatrier le code source pour la LoRaMote, basculer sur la [branche master](https://github.com/Lora-net/LoRaMac-node/wiki/LoRaMAC-node-Wiki) où se trouve la plateforme LoRaMote et compiler

    git clone https://github.com/Lora-net/LoRaMac-node #Attention branche develop par défaut
    cd LoRaMac-node
    git checkout master #basculer sur la branche master
    mkdir build && cd build
    cmake -DCMAKE_TOOLCHAIN_FILE="cmake/toolchain-arm-none-eabi.cmake" ..
    make

Par défaut, le Makefile généré par `cmake` est pour la plateforme *LoRaMote*, l'application *LoRaMAC*, en classe A, la région *EU868*, ...

Pour modifier ces options, plus de détails au <https://github.com/Lora-net/LoRaMac-node/wiki/Development-environment#available-configuration-options-for-cmake>

### Flashage avec le STLinkV2

Les étapes sont : 

- alimenter la carte par USB (cf. figure 1)
- positionner l'interrupteur sur la position ON (vers le bas)
- pour un st-link v2
	- Connectez le JTAG
	- `st-flash --format ihex write LoRaMote-LoRaMac-classA.hex` ([LoRaMote-LoRaMac-classA.hex](./firmware/LoRaMote-LoRaMac-classA.hex)) 

Si tout fonctionne bien, vous devriez voir les 3 leds clignoter une fois le noeud flashé et à chaque envoi de paquet. 
Vous pouvez également voir les paquets dans TTN (<https://console.thethingsnetwork.org/>) si une GW à proximité les reçoit (cf figure 2).  
  
![le paquet envoyé par la loRaMote](./figs/LoRaMoteTTN.png)  
**Fig. 2: Visualisation des paquets de la LoRaMote dans l'interface de TTN**


### Les problèmes éventuels

Si le flashage ne marche pas, mieux vaut utiliser openocd pour débugger car il est plus bavard que les utilitaires st-link. Les différents problèmes possibles sont : 

- votre OS ne voit par le stlink v2 : `st-info --probe` indiquera *Found 0 stlink programmers*. Vérifiez votre JTAG
- une carte mal alimentée : `openocd -f interface/stlink-v2.cfg -f target/stm32l1.cfg` vous indiquera *Error: target voltage may be too low for reliable debugging*. 
- `openocd` indique `Error: init mode failed (unable to connect to the target)`. `st-info --probe` devrait remettre la carte dans un état accessible par `openocd`

