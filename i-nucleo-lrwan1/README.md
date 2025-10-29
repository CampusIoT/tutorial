# ST I-NUCLEO-LRWAN1 LoRa board



![I Nucleo LRWAN1](./i-nucleo-lrwan1.jpg)

https://www.st.com/en/evaluation-tools/i-nucleo-lrwan1.html

[Schematic](USI LoRa Arduino shield_SCH_20161115-1.pdf)

### On-board sensors

* ST accelerometer and magnetometer sensor (LSM303AGR)
* ST relative humidity and temperature sensor (HTS221)
* ST pressure sensor (LPS22HB)

### Flashage avec un STLinkv2 d'une carte Nucleo

Si vous ne possédez pas de flasheur ST-Link v2, vous pouvez utiliser le flasheur détachable des cartes Nucleo et connecter les 5 premières broches du [connecteur CN4 SWD](https://www.st.com/content/ccc/resource/technical/document/user_manual/98/2e/fa/4b/e0/82/43/b7/DM00105823.pdf/files/DM00105823.pdf/jcr:content/translations/en.DM00105823.pdf) au connecteur J6 SWD de la carte:

	Pin 1: VDD_TARGET (VDD from application), rouge
	Pin 2: SWCLK (clock),  jaune
	Pin 3: GND (ground), noir
	Pin 4: SWDIO (SWD data input/output), bleu
	Pin 5: NRST (RESET of target STM32). vert

## Démarrage avec RIOT OS

https://doc.riot-os.org/group__boards__i-nucleo-lrwan1.html

[STM32-Cube for USI-NUCLEO-LoRaWan](https://gitlab.inria.fr/aduque/STM32-Cube-USI-NUCLEO-LoRaWan]

### Test driver SX127x
```bash
cd ~/github/RIOT-OS/RIOT/tests/drivers/sx127x
gmake BOARD=i-nucleo-lrwan1 DRIVER=sx1272 flash
TBC
```

### Test Semtech LoRaMac
```bash
cd ~/github/RIOT-OS/RIOT/tests/pkg/semtech-loramac
gmake BOARD=i-nucleo-lrwan1 LORA_DRIVER=sx1272 LORA_REGION=EU868 flash
TBC
```
