# Ecole [MPLS](https://alpes-dauphine.maisons-pour-la-science.org/) 2025 :: Atelier GNSS (La Mure)

Auteur: Didier DONSEZ, GINP-UGA.

> Ce support est sous licence [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/). Les exemples de croquis fournis ne sont pas couverts par cette licence. Veuillez vous référer à la licence de chacun.

L'objectif de ce tutoriel est de comprendre les informations retournées par les modules GNSS et GNSS RTK.

## Préinstallation

Apportez un parapluie, votre PC/Mac et un adaptateur USB-A <--> USB-C si votre machine n'a que des ports USB-C. Les cartes ESP32 disposent d'un connecteur microUSB.

Téléchargez et installez le driver CP210x pour la carte ESP32 https://www.silabs.com/developer-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads

Installez l'[IDE Arduino](https://www.arduino.cc/en/software) (2.3.4 ou plus) sur votre PC (Windows ou Mac) ou Mac

Ajoutez la définition des cartes ESP32 `[https://dl.espressif.com/dl/package_esp32_index.json](https://github.com/espressif/arduino-esp32/tree/master/libraries)` dans les préférences `Preferences > URL of Board manager`

Installez la bibliothéque `TinyGPSPlusPlus` depuis le gestionnaire de bibliothèques `Tools > Manage Libraries ...`.

Installez l'[application SW Maps](https://apps.apple.com/us/app/sw-maps/id6444248083) pour sur votre tablette/smartphone iOS

Installez l'[application SW Maps](https://play.google.com/store/apps/details?id=np.com.softwel.swmaps&hl=fr) pour sur votre tablette/smartphone Android


## Sommaire
* [Partie 1: GNSS](partie1-gnss.md)
* [Partie 2: GNSS RTK](partie2-rtk.md)
* [Partie 3: GNSS et Applications](partie3-applications.md)
* [Partie 4: GNSS et risques cyber](partie4-cyberrisk.md)
* [Bonus Track](bonus-track.md)
* [Glossaire](glossaire.md)


![](esp32+xa1110-mikrobus.jpg)
![](gnss-rtk-surveyor-backpack-01.jpg)
