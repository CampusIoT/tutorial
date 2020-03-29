# P-NUCLEO-LRWAN Starter Packs

ST Microelectronics propose 2 Starter Packs de prototypage de la technologie LoRa. Chaque pack contient une gateway LoRaWAN basée sur une carte Nucleo NUCLEO-F746ZG et un concentrateur LRWAN_GS_HF1 SX1301 de RisingHF (433 MHz et 868 MHz), et un endpoint LoRaWAN basé sur une carte Nucleo NUCLEO-L073RZ et une carte fille comportant un module LoRa (USI pour le 868 MHz et RisingHF pour le 433 MHz).

La gateway LoRaWAN peut être (re)configurée via des commandes AT pour changer:
* le plan de fréquence du SX1301 (ie les 8 channels),
* l'adresse du network server (TTN, Loriot ou CampusIoT) du packet forwarder,
* ...

## Démarrage de la gateway

Lisez le [manuel de démarrage](https://www.st.com/content/ccc/resource/technical/document/user_manual/group1/01/0e/9a/df/16/73/42/51/DM00620948/files/DM00620948.pdf/jcr:content/translations/en.DM00620948.pdf).

### Branchements

Branchez l'antenne sur la carte fille LRWAN_GS_HF1. 

Branchez le connecteur micro USB (CN1) de la carte fille LRWAN_GS_HF1 sur un adaptateur 5V.

Branchez le connecteur micro USB (CN1) de la carte Nucleo sur le port USB de votre machine et repérez son port `/dev/tty.*`. Attention: ce port NE SERT PAS à l'alimentation de l'ensemble.

Lancez `minicom -s` sur ce port avec la configuration suivante : `115200 8N1`.


### Enregistrement de la gateway

Entrez les commandes suivantes dans le terminal série pour connaitre l'identifiant du packet forwarder de la gateway :
```
AT+SYS
```

Enregistrez la gateway dans votre organisation.

### Configuration du Network Server

Entrez les commandes suivantes dans le terminal série pour reconfigurer l'adresse du network server:
```
AT+PKTFWD
AT+PKTFWD=lora.campusiot.imag.fr,1700,1700
AT+RESET
```

Vérifiez que la configuration est effective. 
```
+RESET: OK                                                                      
Restarting...                                                                   
                                                                                
    _/_/_/    _/_/_/    _/_/_/  _/_/_/  _/      _/    _/_/_/  _/    _/  _/_/_/  
   _/    _/    _/    _/          _/    _/_/    _/  _/        _/    _/  _/       
  _/_/_/      _/      _/_/      _/    _/  _/  _/  _/  _/_/  _/_/_/_/  _/_/_/    
 _/    _/    _/          _/    _/    _/    _/_/  _/    _/  _/    _/  _/         
_/    _/  _/_/_/  _/_/_/    _/_/_/  _/      _/    _/_/_/  _/    _/  _/          
                                                                                
Powered by RisingHF & STMicroelectronics                                        
------------------------------------------------------------------------------- 
           VERSION: 2.1.7, Nov  6 2018                                          
               LOG: OFF                                                         
           AT ECHO: ON                                                          
          BAUDRATE: 115200bps                                                   
           MACADDR: 00:80:E1:01:52:AF                                           
          ETHERNET: DHCP                                                        
              DNS1: 114.114.114.114                                             
              DNS2: 8.8.8.8                                                     
        NTP SERVER: 1.ubuntu.pool.ntp.org                                       
       EUI PADDING: {3, FF}, {4, FF}                                            
        GATEWAY ID: 0080E1FFFF0152AF                                            
           LORAWAN: Public                                                      
    LORAWAN SERVER: lora.campusiot.imag.fr                                      
   UPLINK UDP PORT: 1700                                                        
 DOWNLINK UDP PORT: 1700                                                        
          CHANNEL0: 867100000, A, SF7/SF12, BW125KHz    (LORA_MULTI_SF)         
          CHANNEL1: 867300000, A, SF7/SF12, BW125KHz    (LORA_MULTI_SF)         
          CHANNEL2: 867500000, A, SF7/SF12, BW125KHz    (LORA_MULTI_SF)         
          CHANNEL3: 867700000, A, SF7/SF12, BW125KHz    (LORA_MULTI_SF)         
          CHANNEL4: 867900000, A, SF7/SF12, BW125KHz    (LORA_MULTI_SF)         
          CHANNEL5: 868100000, B, SF7/SF12, BW125KHz    (LORA_MULTI_SF)         
          CHANNEL6: 868300000, B, SF7/SF12, BW125KHz    (LORA_MULTI_SF)         
          CHANNEL7: 868500000, B, SF7/SF12, BW125KHz    (LORA_MULTI_SF)         
          CHANNEL8: 868300000, B, SF7, BW250KHz         (LORA_STANDARD)         
          CHANNEL9: 868800000, B, 50Kbps                (FSK)                   
------------------------------------------------------------------------------- 
Concentrator starting...                                                        
Concentrator Radio A type SX1257                                                
Concentrator Radio B type SX1257                                                
Concentrator started (2926ms)                                                   
ST LoRa GW V2                                                                   
Ethernet starting...                                                            
Ethernet started                                                                
DHCP IP: 10.0.1.3                                                               
Downlink UDP Connected                                                          
Uplink UDP Connected                                                            
```

La gateway envoie alors les messages LoRa reçus par le concentrateur RisingHF au network server.

### Configuration du serveur NTP

L'adresse du serveur NTP est pas défaut `1.ubuntu.pool.ntp.org`

La configuration du NTP server peut être requis (c'est le cas à l'Université Grenoble Alpes).

```
AT+NTP                                                                          
+NTP: "1.ubuntu.pool.ntp.org"                                                   
AT+NTP=0.europe.pool.ntp.org                                                    
+NTP: "0.EUROPE.POOL.NTP.ORG"                                                   
AT+SYS
```

Pour l'Université Grenoble Alpes:
```
AT+NTP=195.83.24.250                                                    
AT+SYS
```
### Branchement du GPS



### Liste des commandes AT

        AT Returns +OK.
        AT+HELP Prints help information.
        AT+FDEFAULT Resets to factory default settings.
        AT+RESET Software-reset gateway.
        AT+SYS Checks all configurations.
        AT+VER Gets version.
        AT+LOG Turns on/off packet forwarder log.
        AT+ECHO AT command echo on/off.
        AT+MAC Sets/gets the gateway MAC address.
        AT+IP DHCP/static IP control.
        AT+DNS Sets/gets the DNS address.
        AT+NTP Sets/gets the NTP server address.
        AT+EUI MAC Address (EUI48) to Gateway ID (EUI64) padding. LORAWAN LoRaWAN® network selection (public/private).
        AT+PKTFWD Packet forwarder server address and port settings.
        AT+CH Packet forwarder channels.
        AT+Baudrate AT command and logging UART interface baud rate.

## Démarrage de la carte Nucleo avec le I-Nucleo

TODO


## Documentation
* [P-NUCLEO-LRWAN2](https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/stm32-nucleo-expansion-boards/p-nucleo-lrwan2.html)  STM32 Nucleo pack LoRa™ HF band sensor and gateway
* [P-NUCLEO-LRWAN3](https://www.st.com/en/evaluation-tools/p-nucleo-lrwan3.html) STM32 Nucleo pack LoRa™ LF band sensor and gateway
* https://www.st.com/content/ccc/resource/technical/document/user_manual/group1/01/0e/9a/df/16/73/42/51/DM00620948/files/DM00620948.pdf/jcr:content/translations/en.DM00620948.pdf
