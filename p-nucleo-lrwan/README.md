# P-NUCLEO-LRWAN Starter Packs

ST Microelectronics propose 2 Starter Packs de prototypage de la technologie LoRa : [P-NUCLEO-LRWAN2](https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/stm32-nucleo-expansion-boards/p-nucleo-lrwan2.html) et  [P-NUCLEO-LRWAN3](https://www.st.com/en/evaluation-tools/p-nucleo-lrwan3.html). Chaque pack contient une gateway LoRaWAN basée sur une carte Nucleo NUCLEO-F746ZG et un concentrateur LRWAN_GS_HF1 SX1301 de RisingHF (433 MHz et 868 MHz), et un endpoint LoRaWAN basé sur une carte Nucleo NUCLEO-L073RZ et une carte fille comportant un module LoRa (USI pour le 868 MHz et RisingHF pour le 433 MHz).

La gateway LoRaWAN peut être (re)configurée via des commandes AT pour changer:
* le plan de fréquence du SX1301 (ie les 8 channels),
* l'adresse du network server (TTN, Loriot ou CampusIoT) du packet forwarder,
* ...

![P-NUCLEO-LRWAN Starter Packs](./images/p-nucleo-lrwan.jpg)


## Démarrage de la gateway LRWAN2 (868 MHz)

Lisez le [manuel de démarrage](https://www.st.com/content/ccc/resource/technical/document/user_manual/group1/01/0e/9a/df/16/73/42/51/DM00620948/files/DM00620948.pdf/jcr:content/translations/en.DM00620948.pdf).

### Branchements

Branchez l'antenne sur la carte fille LRWAN_GS_HF1. 

Branchez le connecteur micro USB (CN1) de la carte fille LRWAN_GS_HF1 sur un adaptateur 5V.

Branchez le connecteur micro USB (CN1) de la carte Nucleo sur le port USB de votre machine et repérez son port `/dev/tty.*` ou `/dev/ttyACM0`. Attention: ce port NE SERT PAS à l'alimentation de l'ensemble.

Lancez `minicom -s` sur ce port avec la configuration suivante : `115200 8N1`.

![P-NUCLEO-LRWAN Branchement](./images/lrwan2-cables.png)


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
AT+PKTFWD=lns.campusiot.imag.fr,1700,1700
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
    LORAWAN SERVER: lns.campusiot.imag.fr                                      
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

Positionnez le mode de journalisation de la gateway.
```
AT+LOG                                                                      
AT+LOG=ON
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
TODO


### Liste des commandes AT

```
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
```


### Trace de réception des messages
* `RX` affiche la trame LoRa recue.
* `JUL` affiche le contenu du datagramme envoyé au network serveur.
* `JDL` affiche le contenu du datagramme recu de network serveur.
* `LTX` affiche la trame LoRa envoyée à un endpoint.
* `LTS` affiche le ???.
 

```
RX: 407BAD00FC800000088F8CC34CD1A913D9574AD997EC732B902412A00B77
JUL: {"rxpk":[{"tmst":47323908,"chan":0,"rfch":0,"freq":433.175000,"stat":1,"modu":"LORA","datr":"SF9BW125","codr":"4/5","lsnr":11.5,"rssi":-28,"size":30,"data":"QHutAPyAAAAIj4zDTNGpE9lXStmX7HMrkCQSoA"}]}
JDL: {"txpk":{"imme":false,"rfch":0,"powe":14,"ant":0,"brd":0,"tmst":48323908,"freq":433.175,"modu":"LORA","datr":"SF9BW125","codr":"4/5","ipol":true,"size":18,"data":"YHutAPyGAAADUv8AAQb6/Vlm"}}
LTX: 607BAD00FC8600000352FF000106FAFD5966
LTS: 47686199 48323908 637709
...
LRX: 407BAD00FC802F0008577306DBC51D660B627B4F8F0FD1F738979A452C5E
JUL: {"rxpk":[{"tmst":925204115,"chan":1,"rfch":0,"freq":433.375000,"stat":1,"modu":"LORA","datr":"SF7BW125","codr":"4/5","lsnr":11.3,"rssi":-33,"size":30,"data":"QHutAPyALwAIV3MG28UdZgtie0+PD9H3OJeaRSxe"}]}
LRX: 407BAD00FC80300008F0AE14EBB9E18174A2AD5807D8F7A0E8D93185D870
JUL: {"rxpk":[{"tmst":944028803,"chan":0,"rfch":0,"freq":433.175000,"stat":1,"modu":"LORA","datr":"SF7BW125","codr":"4/5","lsnr":9.5,"rssi":-34,"size":30,"data":"QHutAPyAMAAI8K4U67nhgXSirVgH2Peg6Nkxhdhw"}]}
LRX: 407BAD00FC8031000841FE2E9D0BF57386EA6514A6FFEA3C083110CF4F33
JUL: {"rxpk":[{"tmst":962853363,"chan":0,"rfch":0,"freq":433.175000,"stat":1,"modu":"LORA","datr":"SF7BW125","codr":"4/5","lsnr":9.3,"rssi":-35,"size":30,"data":"QHutAPyAMQAIQf4unQv1c4bqZRSm/+o8CDEQz08z"}]}
LRX: 407BAD00FC8032000892FF1918D8F185EED04A2442C055A3328D83639893
JUL: {"rxpk":[{"tmst":981675995,"chan":0,"rfch":0,"freq":433.175000,"stat":1,"modu":"LORA","datr":"SF7BW125","codr":"4/5","lsnr":9.5,"rssi":-30,"size":30,"data":"QHutAPyAMgAIkv8ZGNjxhe7QSiRCwFWjMo2DY5iT"}]}
```

### Perte ou mise à jour du firmware par défaut

Afin d'éviter une perte du firmware, vous pouvez _dumper_ celui de votre carte avant son usage.

Vous pouvez aussi réinstaller celui-ci mis à disposition par [TTN](https://www.thethingsnetwork.org/docs/gateways/st/).

> Attention: il faudra configurer la gateway avec les commandes AT et notamment la MacAddress avec celui qui est sur l'étiquette présente sous la carte (`AT+MAC=mac_address`).

## Démarrage du kit I-NUCLEO-LRWAN1 (868 MHz)

Le kit [I-NUCLEO-LRWAN1](https://www.st.com/en/evaluation-tools/i-nucleo-lrwan1.html) (carte Nucleo L073RZ et [modem USI LoRa](https://raw.githubusercontent.com/USIWP1Module/USI_I-NUCLEO-LRWAN1/master/WM-SG-SM-42%20AT%20Command%20Reference%20Manual%20rev.2.6_20200225.pdf) avec SX1272) est livré avec un firmware par défaut.

DevEUI, AppEUI et AppKey sont inscrits sur une étiquette sur la face dessous de la carte Nucleo.

Si ce n'est pas ou plus le cas, pour récupérer DevEUI, AppEUI et AppKey, vous pouvez :
* soit observer les frames LoRa de type JoinRequest reçues par votre gateway. Sur le LoRaServer, le joinEUI correspond à l'AppEUI,
* soit brancher un adapteur USBSerial sur les broches de la carte USI retirée de la carte Nucleo.
* soit lire le DevEUI et l'AppEui dans la mémoire Flash de la carte Nucleo

Pour le deuxième cas, le brochage est le suivant:
* +3V3 (CN6 pin 4)
* GND (CN6 pin 6)
* LPUART1_Rx (CN8 pin 2)
* LPUART1_Tx (CN8 pin 1)
et le réglage du port série est : 115200 8N1

Les commandes AT sont les suivantes:
```
AT+EUI
AT+APPEUI
AT+AK
```

Pour le troisième cas, les commandes à lancer sont:
* Pour le DevEUI: `ST-LINK_CLI.exe -c swd ur -r8 0x08080000 0x08`
* Pour l'AppEUI: `ST-LINK_CLI.exe -c swd ur -r8 0x08080008 0x08`

Si vous utilisez STM32CubeIDE, vous pouvez utiliser `gdb`:
```
(gdb) set endian big
The target is assumed to be big endian

(gdb) x/g 0x08080000
0x8080000:      0x....

(gdb) x/g 0x08080008
0x8080008:      0x....
```

Dans le firmware par défaut, l'AppKey est la concatenation du DevEUI et l'AppEUI.

Vous pouvez alors enregistrer le kit sur votre network server.

Une fois enregistré, le kit effectue l'activation en mode OTAA et envoie périodiquement des frames dont le payload est encodé au [format LPP Cayenne](https://community.mydevices.com/t/cayenne-lpp-2-0/7510). Configurez le décodeur de frames selon le mode LPP Cayenne pour décoder le payload. Le résultat ressemblera à cet objet JSON: 
```
{
  "digitalInput": {
    "3": 0
  },
  "digitalOutput": {
    "4": 0
  },
  "temperatureSensor": {
    "1": 23
  },
  "humiditySensor": {
    "2": 41.5
  },
  "barometer": {
    "0": 990.7
  }
}
```
## Modification du programme du kit I-NUCLEO-LRWAN1 (868 MHz)

Pour recontruire le firmware avec l'environnement gratuit [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html), il faut : 
- télécharger le code de la dernière version de l'[extension LoRaWAN du STM3Cube](https://www.st.com/en/embedded-software/i-cube-lrwan.html) soit la version 1.3.1 dans ce tutoriel.
- importer le projet `STM32CubeExpansion_LRWAN_V1.3.1/Projects/STM32L073RZ-Nucleo/Applications/LoRa/AT_Master/SW4STM32/LRWAN_NS1` de l'environnement [SW4STM32](https://www.st.com/en/development-tools/sw4stm32.html) avec `File > Import` puis `General > Projects from Folder or Archive` dans STM32CubeIDE: [guide de migration](https://www.st.com/resource/en/user_manual/dm00613836-migration-guide-from-system-workbench-to-stm32cubeide-stmicroelectronics.pdf)
- modifier le code source de l'application AT_Master `STM32CubeExpansion_LRWAN_V1.3.1/Projects/STM32L073RZ-Nucleo/Applications/LoRa/AT_Master/LoRaWAN/App/src/main.c` comme indiqué dans la page 24 (section 4.3) de la [documentation](https://www.st.com/resource/en/user_manual/dm00620948-getting-started-with-the-pnucleolrwan2-and-pnucleolrwan3-starter-packs-stmicroelectronics.pdf#page=24)
- compiler le projet et flasher le firmware sur le noeud (menu `Run>Run`).  Plus de détails sur https://www.st.com/en/development-tools/stm32cubeide.html#resource

Vous pouvez ajouter d'autres shields Nucleo et Arduino (3.3V) pour prototyper des applications IoT avancées.

## Démarrage de la gateway LRWAN3 (433 MHz)

Le démarrage de la gateway LRWAN3 est presque identique au démarrage de la gateway LRWAN2.
Elle est par défaut configurée sur la bande ISM chinoise (cn470). Il convient de reconfigurer ces canaux pour être conforme à la réglementation européene (ETSI eu433).

```
AT+SYS
AT+SYS                                                                       
+SYS: OK                                                                     
-------------------------------------------------------------------------------
           VERSION: 2.1.7, Nov  6 2018  
               LOG: OFF                 
           AT ECHO: ON                  
          BAUDRATE: 115200bps           
           MACADDR: 00:80:E1:01:12:34   
          ETHERNET: DHCP
              DNS1: 114.114.114.114
              DNS2: 8.8.8.8
        NTP SERVER: 1.ubuntu.pool.ntp.org                                       
       EUI PADDING: {3, FF}, {4, FF}                                            
        GATEWAY ID: 0080E1FFFF011234                                            
           LORAWAN: Public                                                      
    LORAWAN SERVER: cn1.loriot.io                                               
   UPLINK UDP PORT: 1780                                                        
 DOWNLINK UDP PORT: 1780                                                        
          CHANNEL0: 471500000, A, SF7/SF12, BW125KHz    (LORA_MULTI_SF)         
          CHANNEL1: 471700000, A, SF7/SF12, BW125KHz    (LORA_MULTI_SF)         
          CHANNEL2: 471900000, A, SF7/SF12, BW125KHz    (LORA_MULTI_SF)         
          CHANNEL3: 472100000, A, SF7/SF12, BW125KHz    (LORA_MULTI_SF)         
          CHANNEL4: 472300000, B, SF7/SF12, BW125KHz    (LORA_MULTI_SF)         
          CHANNEL5: 472500000, B, SF7/SF12, BW125KHz    (LORA_MULTI_SF)         
          CHANNEL6: 472700000, B, SF7/SF12, BW125KHz    (LORA_MULTI_SF)         
          CHANNEL7: 472900000, B, SF7/SF12, BW125KHz    (LORA_MULTI_SF)         
          CHANNEL8: OFF                                 (LORA_STANDARD)         
          CHANNEL9: OFF                                 (FSK)                   
------------------------------------------------------------------------------- 
```

```
AT+PKTFWD=lns.campusiot.imag.fr,1700,1700
AT+LOG=ON                                                                    
AT+CH
AT+CH=eu433                                                                    
AT+RESET
```

La gateway écoute et réponds désormais sur les canaux suivants.
```
+CH: 0, 433175000, A, SF7/SF12, BW125KHz (LORA_MULTI_SF)                        
+CH: 1, 433375000, A, SF7/SF12, BW125KHz (LORA_MULTI_SF)                        
+CH: 2, 433575000, A, SF7/SF12, BW125KHz (LORA_MULTI_SF)                        
+CH: 3, 433775000, A, SF7/SF12, BW125KHz (LORA_MULTI_SF)                        
+CH: 4, 433975000, B, SF7/SF12, BW125KHz (LORA_MULTI_SF)                        
+CH: 5, 434175000, B, SF7/SF12, BW125KHz (LORA_MULTI_SF)                        
+CH: 6, 434375000, B, SF7/SF12, BW125KHz (LORA_MULTI_SF)                        
+CH: 7, 434575000, B, SF7/SF12, BW125KHz (LORA_MULTI_SF)                        
+CH: 8, OFF                              (LORA_STANDARD)                        
+CH: 9, OFF                              (FSK)                                  
```

La gateway peut être enregistrée sur un network server configuré par la bande eu433.

## Démarrage du kit LRWAN_NS1 (433 MHz)

Le kit ST Nucleo LoRa Sensor LRWAN_NS1 est basé sur la carte Nucleo-L073 et la carte fille ST Nucleo LoRa Sensor basé sur le module [RHF0M003](http://www.risinghf.com/#/product-details?product_id=4&lang=en) de RisingHF.

Par défaut, ce kit est par défaut configuré sur la bande ISM chinoise (cn470). Il convient de reconfigurer ses canaux pour être conforme à la réglementation européene (ETSI eu433) conformément à la [documentation](https://www.st.com/resource/en/user_manual/dm00620948-getting-started-with-the-pnucleolrwan2-and-pnucleolrwan3-starter-packs-stmicroelectronics.pdf#page=28):
- soit en reconstruisant le firmware 
- soit en le reconfigurant via les commandes AT

Pour recontruire le firmware avec l'environnement gratuit [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html), il faut : 
- télécharger le code de l'[extension LoRaWAN du STM3Cube](https://www.st.com/en/embedded-software/i-cube-lrwan.html)
- importer le projet `STM32CubeExpansion_LRWAN_V1.3.1/Projects/STM32L073RZ-Nucleo/Applications/LoRa/AT_Master/SW4STM32/LRWAN_NS1` de l'environnement [SW4STM32](https://www.st.com/en/development-tools/sw4stm32.html) dans STM32CubeIDE: [guide de migration](https://www.st.com/resource/en/user_manual/dm00613836-migration-guide-from-system-workbench-to-stm32cubeide-stmicroelectronics.pdf)
- modifier le code source de l'application AT_Master `STM32CubeExpansion_LRWAN_V1.3.1/Projects/STM32L073RZ-Nucleo/Applications/LoRa/AT_Master/LoRaWAN/App/src/main.c` comme indiqué dans la page 28 (section 5.3) de la [documentation](https://www.st.com/resource/en/user_manual/dm00620948-getting-started-with-the-pnucleolrwan2-and-pnucleolrwan3-starter-packs-stmicroelectronics.pdf#page=28)
```
#main.c

#ifdef USE_LRWAN_NS1
#define FREQ_BAND                  /*EU868*/ CN470PREQUEL <-- à modifier pour EU433
#endif
```
- compiler le projet et flasher le firmware sur le noeud (menu `Run>Run`).  Plus de détails sur https://www.st.com/en/development-tools/stm32cubeide.html#resource

Une fois enregistré, le kit effectue l'activation en mode OTAA et envoie périodiquement des frames dont le payload est encodé au [format LPP Cayenne](https://community.mydevices.com/t/cayenne-lpp-2-0/7510). Configurez le décodeur de frames selon le mode LPP Cayenne pour décoder le payload. Le résultat ressemblera à cet objet JSON: 
```
{
  "digitalInput": {
    "3": 0
  },
  "digitalOutput": {
    "4": 0
  },
  "temperatureSensor": {
    "1": 23
  },
  "humiditySensor": {
    "2": 41.5
  },
  "barometer": {
    "0": 990.7
  }
}
```


### Trace et Debug
Vous pouvez tracer les commandes AT du modem LoRaWAN en vous connecter pour port USBSerial de la carte Nucleo (`9600 8N1`).

```
AT
????+AT: OK
AT+ID=DevEui
????+ID: DevEui, 8C:F9:57:20:00:00:12:34
AT+ID=APPEUI
????+ID: AppEui, A1:79:AA:AA:AD:20:4A:72
AT+FDEFAULT
+FDEFAULT: OK
AT+LOWPOWER=AUTOON
????+LOWPOWER: AUTOON
AT+DR=EU433
????+DR: EU433
AT+ID=DevAddr
????+ID: DevAddr, 00:00:FC:6F
AT+MODE=LWOTAA
????+MODE: LWOTAA
AT+WDT=OFF
????+WDT: OFF
AT+ADR=OFF
????+ADR: OFF
AT+DR=3
AT+JOIN
????+JOIN: Start
????+JOIN: NORMAL
????+JOIN: Network joined
????+JOIN: NetID C0002B DevAddr FC:00:AF:88
????+JOIN: Done
AT+VDD
????+VDD: 3.31V
AT+MSGHEX=007326a601670105026860030064040100
????+MSGHEX: Start
????+MSGHEX: FPENDING
????+MSGHEX: RXWIN1, RSSI -22, SNR 7.5
????+MSGHEX: Done
AT+VDD
????+VDD: 3.31V
AT+MSGHEX=007326a601670105026860030064040100
????+MSGHEX: Start
????+MSGHEX: Done
AT+VDD
????+VDD: 3.31V
```


Remarque: il est possible que le programme plante après la commande `AT+ADR=OFF` présente dans la trace : il faut ajouter l'instruction suivante dans la fonction `Lora_SetDataRate` du fichier `lora_driver.c`.

```c
ATEerror_t Lora_SetDataRate(uint8_t DataRate)
{
  ATEerror_t Status;
  int32_t var = DataRate; // Instruction à ajouter
  Status = Modem_AT_Cmd(AT_SET, AT_DR, &var);

  return (Status);
}
```

Remarque: Pour activer l'ADR, vous pouvez modifier la fonction `Lora_fsm` du fichier `lora_driver.c`.
```C
        /*to adapt the data rate during transmission*/
        LoraCmdRetCode = Lora_SetAdaptiveDataRate(ADAPT_DATA_RATE_ENABLE);
        //LoraCmdRetCode = Lora_SetAdaptiveDataRate(ADAPT_DATA_RATE_DISABLE);
```

## Documentation
* [P-NUCLEO-LRWAN2](https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/stm32-nucleo-expansion-boards/p-nucleo-lrwan2.html)  STM32 Nucleo pack LoRa™ HF band sensor and gateway
* [P-NUCLEO-LRWAN3](https://www.st.com/en/evaluation-tools/p-nucleo-lrwan3.html) STM32 Nucleo pack LoRa™ LF band sensor and gateway
* [manuel de démarrage](https://www.st.com/content/ccc/resource/technical/document/user_manual/group1/01/0e/9a/df/16/73/42/51/DM00620948/files/DM00620948.pdf/jcr:content/translations/en.DM00620948.pdf)
