# CampusIoT :: Tutoriel :: SagemCom Siconia :fr:

L'équipement Siconia Multi App ATGHMP EndPoint de SagemCom est un endpoint LoRaWAN Class A (OTAA oy ABP). Il est doté de plusieurs capteurs (thermomètre, baromètre, hygromètre, accéléromètre, magnétomètre), ainsi que d'un bouton poussoir et d'une LED (verte, orange et rouge). Il pèse 24 grammes et ses dimensions sont 40x25x23 mm. Le MCU hôte est un [STM32L433CCT6](https://www.st.com/en/microcontrollers-microprocessors/stm32l433cc.html). Il est programmable au moyen d'un script Javascript applicatif en utilisant la bibliothèque Espruino https://www.espruino.com/Reference#software . La documentation en ligne est http://iot.siconia.sagemcom.com:8080/loradevice-doc .


> Remarque: Sa batterie (CR2 CR15H270 3V 850mAh Lithium) étant soudée sur le PCB, il convient d'écrire un script qui limite l'éveil des capteurs et les transmissions uplink.

## Mise en oeuvre
En configuration de sortie usine, l'équipement est actif, mais en mode dit « Avion » (transmission radio interdite) et de consommation extrêmement réduite. Placé sur un [support de communication NFC](https://www.st.com/en/evaluation-tools/m24lr-discovery.html), il est possible de le réveiller et de lui installer un script applicatif, via un application adaptée.

En mode OTAA, l'équipement est livré avec sa clé propre `AppKey`, et d’un identifiant `JoinEUI` qui est commun à un lot de fabrication donné. Il n’est pas possible de lire ni modifier la clé `AppKey` de l'équipement par le script applicatif. La clé `AppKey` est transmise à son propriétaire par le vendeur au moyen d'un canal indépendant approprié.


## Enregistrement de l'équipement
Créez une nouvelle application `SICONIA`.

Ajoutez un device (device profile `CLASS_A_OTAA`) avec le `DevEUI` récupéré (étiquette sur le dos du boitier) et l'`AppKey` communiquée par le vendeur.


## Utilisation du script applicatif par défaut des devices
Le script par défaut provoque un comportement du produit en fonction de la durée d’appui sur le bouton :

En relâchant le bouton avant 3 secondes d’appui,
* Si le mode Avion est désactivé, alors il y a émission d’une trame LoRAWAN, et le voyant vert clignote.

La trame émise contient comme information la température relevée par le produit.
* Si le mode Avion est activé, alors rien ne se passe

En relâchant le bouton entre 3 et 6 secondes d’appui, on active/désactive le mode Avion
* Lorsque le mode Avion est activé, le voyant rouge clignote
* Lorsque le mode Avion est désactivé, le voyant vert clignote

Cet état est volatile : en cas de redémarrage du produit, le mode Avion redevient activé par défaut.


En relâchant le bouton entre 6 et 9 secondes d’appui,
o Le mode Avion est désactivé (l’émission est donc rendue possible)
o Le produit tente de joindre le réseau LORA (Join Request émis et attente temporisée)
o Le voyant clignote en orange

En cas de non réponse à la requête du Join, l'équipement redémarre au bout de 2 minutes.

En relâchant le bouton après 9 secondes d’appui, l'équipement est redémarré.

## Changement du script par USB Serial pour les modèles de développement

Les modèles de développement sont équipés d'une prise micro-USB pour permettre la mise au point itérative du script applicatif.

Il faut utiliser une application de terminal série (comme CoolTerm, Zterm, Putty, ...) pour se connecter à l'invité de commande (ie prompt). Les paramêtres de connection sont : 9600 baud et terminaison de ligne <CR>.

Copiez collez le [script suivant](https://github.com/CampusIoT/endpoints/blob/master/siconia/MotionHumidityTempPressure.js) dans le terminal série.

## Changement du script par NFC pour les modèles de production
Les modèles de production (qui sont étanches) sont dépourvus de prise micro-USB. Le script applicatif que vous avez mis au point précédemment est chargé dans l'équipement par une liaison NFC au moyen d'un [lecteur NFC STM](https://www.st.com/en/evaluation-tools/m24lr-discovery.html) qui est fourni avec le kit de développement Siconia.

Le programme de chargement du script dans les Siconia de production ne peut s'exécuter que sur une machine sous Windows ou bien depuis une machine virtuelle VirtualBox Windows sur MacOS ou Linux. Le programme Java dépend de DLL uniquement disponibles sur Windows.

Les fichiers de configuration pour le chargement d'un équipement ou d'un lot de devices sont les suivants :
* `Endpoints\\config\\config.js` contient les filtres sur le lot de équipements à charger ainsi que la clé `authKey` du propriétaire des équipements. [Exemple](./config.js)
* `Endpoints\\authkeys\\keys.txt` contient les pairs `DEVEUI` `DEV_KEY` des équipements du lot à charger : Attention, la `DEV_KEY` d'un équipement n'est pas ses clés LNS (`APP_KEY`, `APP_SKEY` ou `NWK_SKEY`). Le séparateur `DEVEUI` `DEV_KEY` doit être le caractère virgule `,` en non pas le point virgule `;` [Exemple](./keys.txt)
* `Endpoints\\jsCode\\motion_temp\\script.js` est le programme à charger dans les équipements du lot. Remarque: Le programme Javascript est minifié avant le chargement. [Exemple](./script.js)

Lancez le script `nfc_java.bat` puis placez l'équipement sur l'emplacement de l'antenne du [lecteur NFC STM](https://www.st.com/en/evaluation-tools/m24lr-discovery.html).

La trace suivante est produite par le script :

```
1) Check if a board is connected
A board has been detected UID=E0024DCDBF041234
==> Waiting for device
A board with devEui (4883C7DF30051234) detected
DEV_ADDR = A46B1234
==> A board with devEui (4883C7DF30051234) detected
==> Searching for the board configuration
==> Checking for device compatibility
==> Transferring application code
java -jar compiler.jar -O EMBEDDED   Endpoints/jsCode/motion_temp/script.js
var scriptVersion="1.1",started=!1;function startup(){L.dutycycle(!1);L.airplane
....
******OK
==> Resetting the device
FINAL_DEV_ADDR = A46B1234
==> Creating log information
==> Done. Device personnalized
OK
Took 20282 ms
```

Une fois le chargement accompli, le programme laisse dans le répertoire `Endpoints\\output` une document de diagnostique au format JSON pour chaque équipement chargé.

```
{
  "usedConfigPath": "Endpoints\\config\\4883C7DF30051234.js",
  "DEV_EUI": "4883C7DF30051234",
  "JSCODE": "NA",
  "NFC_UID": "E0024DCDBF041234",
  "TIME": "20282",
  "DEV_ADDR": "A46B1234",
  "AUTH_CHALLENGE": "SUCCESS",
  "JSHASH": "0F1234C7",
  "USING_AUTH_CHALLENGE": "TRUE",
  "HW_VERSION": "0203",
  "FWREV": "0378",
  "DATE": "Tue Jun 11 17:38:42 CEST 2019",
  "STATUS": "DONE",
  "AUTHENTICATION": "SUCCESS",
  "AUTHENTICATOR_TRIED": "FolderCipheredAuthenticator",
  "FINAL_DEV_ADDR": "A46B1234",
  "SW_VERSION": "0111"
}
```

## Bibliothéques de scripts
Plusieurs scripts applicatifs sont disponibles ici : https://github.com/CampusIoT/endpoints/tree/master/siconia

> Remarque: le répertoire `Endpoints\\jsCode\\MultiCasesAPP*` contient une quinzaine de scripts avec un document PDF d'explication. Le script bash suivant permet de minifier un ensemble de scripts à charger : 

```bash
DIR=Endpoints/jsCode/script
FILE=$DIR/app.js
mkdir -p $DIR
rm $FILE
for script in cu1.js cu2.js cu3.js cu4.js cu5.js cu6.js cu7.js cu9.js cu11.js cu13.js calc.js leds.js keepalive.js linkcheck.js lpp.js utils.js resetfactory.js
do
java -jar compiler.jar -O EMBEDDED   Endpoints/jsCode/MultiCasesAPP_1-2-200/$script >> $FILE
done
```


Le script suivant `parking.js` permet de ''parquer'' l'équipement : il n'émet plus de messages jusqu'au prochain chargement pour éviter l'épuisement de la batterie.

```
TODO
```

> Remarque: c'est une bonne pratique de prévoir un état `parking` dans les scripts que vous développez. L'entrée et la sortie de cet état peuvent être déclenché par un appui très long du bouton (par exemple > 10 secondes).

## Recyclage et personnalisation 
La batterie du Siconia est soudée sur le PCB. Il est possible de désouder celle-ci pour la remplacement pour une batterie à l'identique (CR2 CR15H270 3V 850mAh Lithium) ou par un support batterie déporté pour des batteries amovibles de plus grande capacité (Lithium 3V AA) ou moins chères (2 x1.5V Alcaline AA ou AAA). (voir photo ci-dessous)

La carte comporte un emplacement pour un connecteur UFL qui peut être ajouté pour raccorder le Siconia à des antennes de meilleur gain. (voir photo ci-dessous)

![](images/siconia-extbat-01.jpg)
![](images/siconia-extbat-02.jpg)


## Annexe

### Caractéristiques techniques

* Utilisation Extérieure ou Intérieure
* Installation Fixe et/ou Transportable (Le produit n’est pas destiné à être porté continuellement à proximité d’une personne (moins de 2.5 cm de distance de la peau)
* Condition d’utilisation Continue
* Source d’alimentation Pile interne 850mAh, protégée par fusible.
* Plage de température de fonctionnement -20°C à +70 °C
* Plage de température de stockage -20°C à +45 °C
* Altitude maximale d’installation +2000 mètres
* Poids 23 grammes
* Dimensions mécaniques avec fixations (en mm) L 56 x l 25 x H 23.2
* Fixation 2 trous pour vis Ø <3.4mm
* Indice de protection IP65
* Humidité relative Inférieure à 95% d’humidité sans condensation
* Modulation radio LORA WAN ™ - Classe A Bande de fréquence 863 – 870 MHz
* Puissance d’émission radio LORA Jusqu’à 17dBm (au pied de l’antenne)
* Sensibilité LORA -120dBm en SF7 et -133 dBm en SF12
* Mesure de l’accéleration : Echelle configurable :±2/±4/±8/±16 g Résolution : 1mg
* Mesure de température Précision : +/- 1,5 °C Résolution min: 0,0625°C
* Mesure de pression Précision : +/- 2 hPa max. , +/- 1hPa/an Résolution min.: 0.18 Pa
* Mesure d’humidité Précision : +/- 3 %RH +/- 0,5 %RH/an Résolution min.: 0.01%


### Galerie

![Siconia on bike saddle](images/siconia-saddle.jpg)
![Siconia on door](images/siconia-door.jpg)
![Siconia](images/siconia-board-1.jpg)
![Siconia](images/siconia-board-2.jpg)
![Siconia](images/siconia-inside.jpg)
