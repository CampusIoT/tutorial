# ODB-II ::Tutoriel

## Montage

* [Keyestudio CAN-BUS Shield MCP2515](https://fr.aliexpress.com/item/32998255055.html) [wiki](https://wiki.keyestudio.com/KS0411_keyestudio_CAN-BUS_Shield)

![Keyestudio CAN-BUS Shield MCP2515](images/Keyestudio-CAN-BUS-Shield-MCP2515.jpg)

# Carte de pilote de Bus CAN MCP2515 + TJA1050 récepteur SPI 

* [Carte de pilote de Bus CAN MCP2515 TJA1050 récepteur SPI](https://fr.aliexpress.com/item/32223930366.html)


# Carte de pilote de Bus CAN MCP2515 

* [Carte de pilote de Bus CAN MCP2515 TJA1050 récepteur SPI](https://fr.aliexpress.com/item/32223930366.html)

# Carte CAN VP230

* [Carte CAN VP230](https://fr.aliexpress.com/item/1005002843325046.html)


# KS0411 keyestudio CAN-BUS Shield

Ce shield contient à la fois un driver MCP2515 et un lecteur de cartes Micro-SD : il faut s'en servir pour l'emulateur d'OBC.

https://wiki.keyestudio.com/KS0411_keyestudio_CAN-BUS_Shield

Celle-ci semble être un clone de la carte [Sparkfun CAN BUS](https://github.com/sparkfun/CAN-Bus_Shield)

La broche CS du lecteur de carte Micro-SD est Arduino D9.

Code de test sur Arduino (MCU AVR)
* https://www.dropbox.com/sh/hd1feflnh5gkw8l/AACFr87wOB2fKy98NXHXgZZya/Resource?dl=0&subfolder_nav_tracking=1
* [Sparkfun CAN BUS](https://github.com/sparkfun/CAN-Bus_Shield)


L9616 seems compatible with the [NXP TJA1042](https://www.nxp.com/docs/en/data-sheet/TJA1042.pdf) CAN driver.

The TJA1042 driver for RIOT should be added as a module.

## Wiring with 2 Nucleo F446RE + 2 L9616


The pinout of the L9616 is belong:
![l9616](images/l9616-pin.png)


The pinout of the L9616 (SOC8) adapter is: 

		        VREF			RXD	--> D15 (Grey)
		        CANL (Yellow)	VDD --> 5V	(Red)
		        CANH (Green)	VSS	--> GND	(Black)		
		GND <-- RS				TXD --> D14	(Purple)
		     			ARIES	
	 

[see pinout Nucleo F443RE](https://os.mbed.com/platforms/ST-Nucleo-F446RE/).

The Nucleo F446RE had 2 CAN ports:
* CAN1 (CAN1_RD is on D15, CAN1_TD is on D14) --> can0 on "can list"
* CAN2 (CAN2_RD is on D4, CAN2_TD is on D10)  --> can1 on "can list"
