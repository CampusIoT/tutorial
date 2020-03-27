## Environnement de développement sous OSX pour iM880a

Il faut tout d'abord installer les outils de compilation (cmake, arm-none-eabi-gcc) 
et de flashage (openocd ou stlink). 

Plus de détails à <https://github.com/Lora-net/LoRaMac-node/wiki/Development-environment#prerequisites> et <https://github.com/texane/stlink>

    brew install cmake # génère les Makefile
    brew tap ARMmbed/homebrew-formulae && brew install arm-none-eabi-gcc #cross-compile
    brew install openocd
    brew install stlink

Le flashage peut se faire : 

- soit via `openocd` (<https://github.com/Lora-net/LoRaMac-node/wiki/Development-environment#debugging>) 
- soit les utilitaires liés à `stlink` (<https://github.com/texane/stlink/blob/master/doc/tutorial.md#building-and-flashing-a-program>). 
