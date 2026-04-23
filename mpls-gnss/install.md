# Ecole [MPLS](https://alpes-dauphine.maisons-pour-la-science.org/) 2026 :: Atelier GNSS (La Mure)

Auteur: Didier DONSEZ, GINP-UGA.

> Ce support est sous licence [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/). Les exemples de croquis fournis ne sont pas couverts par cette licence. Veuillez vous référer à la licence de chacun.

## Préinstallation

Apportez un parapluie, votre PC/Mac et un adaptateur USB-A <--> USB-C si votre machine n'a que des ports USB-C. Les cartes ESP32 disposent d'un connecteur microUSB.

### Driver CP210x

Téléchargez et installez le [driver CP210x](https://www.silabs.com/developer-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads) (présent sur la carte ESP32) pour votre système d'exploitation.

### IDE Arduino

Installez l'[IDE Arduino](https://www.arduino.cc/en/software) (2.3.4 ou plus) sur votre PC (Windows ou Mac) ou Mac

Ajoutez la définition des cartes ESP32 `https://dl.espressif.com/dl/package_esp32_index.json` dans les préférences `Preferences > URL of Board manager`

Cherchez et installez `exp32` (by Espressif Systems) depuis `Tools > Board > Board manager`, 

Installez la bibliothéque `EspSoftwareSerial` depuis le gestionnaire de bibliothèques `Tools > Manage Libraries ...`.

Installez la bibliothéque `TinyGPSPlusPlus` depuis le gestionnaire de bibliothèques `Tools > Manage Libraries ...`.

Sélectionnez votre carte `ESP32 Dev Module` dans `Tools > Board > esp32`.

Sélectionnez le port auquel est connecté la carte dans `Tools > Port`.

### SW Maps

Installez l'[application SW Maps](https://apps.apple.com/us/app/sw-maps/id6444248083) pour sur votre tablette/smartphone iOS

Installez l'[application SW Maps](https://play.google.com/store/apps/details?id=np.com.softwel.swmaps&hl=fr) pour sur votre tablette/smartphone Android


### Sur Android
Vous devrez activer les emplacements fictifs (mock) dans Android. Il faut obtenir les autorisations de développeur. Sur Android 4.2 et supérieur, vous devez activer les options de développeur, appuyez sur le Numéro de build, version MIUI ou similaire option 7 fois.
* Soit via Paramètres -> À propos du téléphone -> Numéro de build
* Soit via Paramètres -> Système -> À propos du téléphone -> Numéro de build

Vous devez ensuite  
* selectionner 'application fictive de positionnement (mock location app)
* forcer tous les mesures GNSS (full GNSS measurement)
dans les options du développeur supplémentaires

**Chapitre suivant: [GNSS](partie1-gnss.md)**
