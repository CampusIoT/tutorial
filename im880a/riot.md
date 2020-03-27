# Cartes iM880 avec RIOT OS

## RIOT OS
RIOT OS est un système d'exploitation pour les systèmes embarqués et les objets connectés. Il supporte de nombreux architectures, CPU, boards, composants (capteurs, actionneurs).


On s'intéresse à RIOT-OS car il offre: 

- plus de souplesse en terme de programmation (un OS, pile IP, support d'autres technologies wireless, timer, serial, ...)
- le support de nombreuses plateformes
- beaucoup d'applicatifs
- ...

Il supporte notamment le module IMST [iM880b](https://doc.riot-os.org/group__boards__im880b.html).

Le module iM880a n'étant pas supporté par défaut dans le dépôt officiel: on se base sur la [plateforme iM880b](https://wireless-solutions.de/products/starterkits/sk-im880b.html) qui est quasi similaire.  

*(Merci de vous référer aux paramètres de configuration de la section précédente pour l'adaptateur USB notamment.)*

## Installation de RIOT OS


```bash
mkdir -p github/RIOT-OS
cd github/RIOT-OS
git clone git://github.com/RIOT-OS/RIOT.git
cd RIOT
RIOT_BASE=$(pwd)
```

Sur MacOS, récupérez une version récente de `make`
```
brew install make
PATH="/usr/local/opt/make/libexec/gnubin:$PATH"
```

### 2 applications : 1 LoRa et 1 LoRaWAN

Les 2 applications existantes pour LoRa dans RIOT sont : 

- [```${RIOT_BASE}/tests/driver_sx127x```](https://github.com/fjmolinas/RIOT/blob/im880b_loramac/tests/driver_sx127x) qui permet de tester le driver radio lora 127x
- [```${RIOT_BASE}/tests/pkg_semtech-loramac```](https://github.com/fjmolinas/RIOT/blob/im880b_loramac/tests/pkg_semtech-loramac/README.md) qui permet de tester le réseau LoRaWAN


Pour compiler et flasher, on suit les étapes suivantes :  

Pour le test LoRa de base

```bash
make BOARD=im880b DRIVER=sx1272 -C tests/driver_sx127x # pour l'exemple LoRa de base
arm-none-eabi-objcopy -O binary ${RIOT_BASE}/tests/driver_sx127x/bin/im880b/tests_driver_sx127x.elf tests_driver_sx127x.bin # conversion format .elf au format .bin
st-flash write tests_driver_sx127x.bin 0x8000000 
```

Pour le test LoRaWAN
   
```bash
make BOARD=im880b LORA_DRIVER=sx1272 -C tests/pkg_semtech-loramac # pour l'exemple LoRaWAN
arm-none-eabi-objcopy -O binary ${RIOT_BASE}/tests/pkg_semtech-loramac/bin/im880b/tests_pkg_semtech-loramac.elf tests_pkg_semtech-loramac.bin # conversion format .elf au format .bin
st-flash write tests_pkg_semtech-loramac.bin 0x8000000
```

Pour un accès direct aux firmwares : ([```tests_driver_sx127x.bin```](firmware/tests_driver_sx127x.bin)), ([```pkg_semtech-loramac.bin```](firmware/tests_pkg_semtech-loramac.bin))

Pour vérifier le bon fonctionnement, connectons nous sur le lien série afin d'accéder au shell RIOT.  
Sous OSX, plusieurs [solutions](https://pbxbook.com/other/mac-tty.html) sont possibles. On a retenu la suivante :   

- on installe minicom : `brew install minicom`
- on configure minicom
	 - `minicom -s` (Pour accéder à l'aide, il faut utiliser Esc-Z à la place de Meta-Z)
	 - menu "Serial port setup" et on modifie les paramètres par défaut comme suit  
	 `A - Serial Device			 : /dev/tty.wchusbserial1410
	 E - Bps/Par/Bits			: 115200 8N1
	 F - Hardware Flow Control 	: No
	 G - Software Flow Control 	: No `
	 - on sauvegarde via le menu "Save setup as dfl" 
	 - on quitte minicom
- on règle les problèmes de retour à la ligne en ajoutant à $HOME/.minirc.dfl la ligne suivante  
`pu addcarreturn    Yes`

`minicom` nous donne accès au lien série et au shell de RIOT.  

Pour expérimenter, il ne reste plus qu'à suivre les instructions de l'exemple LoRa ([```readme driver_sx127x```](https://github.com/fjmolinas/RIOT/blob/im880b_loramac/tests/driver_sx127x)) ou LoRaWAN ([```readme pkg_semtech-loramac```](https://github.com/fjmolinas/RIOT/blob/im880b_loramac/tests/driver_sx127x)).  
Nous testons la procédure OTAA sur TTN dans la section suivante. 

### RIOT + LoRaWAN (OTAA on TTN)

Les notes ci-dessous viennent compléter les instructions du [```readme pkg_semtech-loramac```](https://github.com/fjmolinas/RIOT/blob/im880b_loramac/tests/driver_sx127x)

Pour permettre à un noeud de se connecter à TTN selon la procédure OTAA, il faut suivre les étapes suivantes : 

1. Enregistrer le noeud sur TTN :  <https://www.thethingsnetwork.org/docs/devices/registration.html> 
2. Programmer Device EUI, App Key et App EUI sur le noeud : <https://github.com/RIOT-OS/RIOT/tree/master/tests/pkg_semtech-loramac#using-the-shell>
3. Observer les messages de join dans l'interface de TTN accessible via le menu `Applications > Application\_Name > Devices > Device\_Name > Data`
4. Générer des messages coté noeud
	- `riot$ loramac set dr 0` (cf. [tableau datarate Europe](https://lora-alliance.org/sites/default/files/2018-04/lorawantm_regional_parameters_v1.1rb_-_final.pdf#page=16)) pour toucher les GW les plus éloignées
	- `riot$ loramac tx hello`
5. Voir les messages coté interface TTN
	- TIP: In the Payload formats > Payload format of your application console, select the Custom payload format and in the Decoder text edit, add the following decoding javascript function:

```javascript
function Decoder(bytes, port) {
  var message = "";

  for  (var i=0; i < bytes.length; i++) {
    message += String.fromCharCode(bytes[i]);
  }
  var decoded = {};
  decoded.message = message;
  return decoded;
}
```

Pour aller plus loin, un tutoriel parfait : <https://github.com/riot-os/riot-course#content-of-the-course> avec des [slides plus spécifique sur LoRa](https://riot-os.github.io/riot-course/slides/05-lorawan-with-riot/#1). 

Mettons en oeuvre un firmware se connectant en OTAA avec des EUI en dur et envoyant ensuite un message toutes les 20s : <https://github.com/RIOT-OS/riot-course/tree/master/exercises/riot-lorawan/simple>  

1. compiler et flasher le firmware  

    `cd ~/github/RIOT-OS`  
    `git clone --recursive https://github.com/riot-os/riot-course`  
    `cd riot-course/exercises/riot-lorawan/simple/.solution`  
    `git apply add-deveui-appeui-appkey.patch #to fix the DEVEUI, APPEUI and APPKEY` ([add-deveui-appeui-appkey.patch](./firmware/add-deveui-appeui-appkey.patch))  
    `make BOARD=im880b DRIVER=sx1272                                               `  
    `st-flash --format ihex write bin/im880b/lorawan.hex                           `  ([lorawan.hex](./firmware/lorawan.hex))  
  
2. alimentons la carte à l'aide des piles (ne pas oublier le jumper pour activer l'alimentation par les piles)
3. observons les paquets émis dans la console applicative de TTN <https://console.thethingsnetwork.org/applications/application_name/devices/device_name/data>
4. le bouton reset permet de rebooter le noeud

<!-- <http://doc.riot-os.org/group__pkg__semtech-loramac.html> -->

D'autres scénarios sont envisageables : 

- lui ajouter des périphériques (GPS, ...)
- se balader avec le noeud, tester son autonomie, le mettre dans un ballon stratosphérique, la localisation,  ... <https://air.imag.fr/index.php?search=lora&title=Special%3ASearch&go=Go>
- Low power : <https://github.com/aabadie/riot-course-exercises/tree/master/riot-lorawan/pm>

## TODO

- [ ] instructions LoraServer
- [ ] ajout du support du st-linkv2-1 : https://gitlab.ensimag.fr/lorawan-bm/riot-im880b + googledocs
