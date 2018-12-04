# CampusIoT :: Tutoriel :: SagemCom Siconia

Mise en oeuvre
En configuration de sortie usine (voir nota 1), le produit est actif, mais en mode dit « Avion » (transmission radio interdite) et de consommation extrêmement réduite. Placé sur un support de communication NFC, il est possible de le réveiller et de lui installer un script applicatif, via un outil adapté.
En mode OTAA (voir les spécifications LoRaWANTM), le produit est équipé de sa clé propre AppKey, et d’un identifiant JoinEUI qui est commun à un lot de fabrication donné. Il n’est pas possible de lire ni modifier la clé AppKey du produit, qui sera transmise à l’utilisateur par un canal indépendant approprié (la clé ne fait pas partie des données d’inventaire publiques).

## Script applicatif par défaut des devices de prod
Le script par défaut provoque un comportement du produit en fonction de la durée d’appui sur le bouton :
En relâchant le bouton avant 3 secondes d’appui,
o Si le mode Avion est désactivé, alors il y a émission d’une trame LORA, et le voyant vert clignote.
La trame émise contient comme information la température relevée par le produit.
o Si le mode Avion est activé, alors rien ne se passe
En relâchant le bouton entre 3 et 6 secondes d’appui, on active/désactive le mode Avion
o Lorsque le mode Avion est activé, le voyant rouge clignote
o Lorsque le mode Avion est désactivé, le voyant vert clignote
Cet état est volatil : en cas de redémarrage du produit, le mode Avion redevient activé par défaut.

13
En relâchant le bouton entre 6 et 9 secondes d’appui,
o Le mode Avion est désactivé (l’émission est donc rendue possible)
o Le produit tente de joindre le réseau LORA (Join Request émis et attente temporisée)
o Le voyant clignote en orange
En cas de non réponse au JOIN, le produit redémarre au bout de 2 minutes.
En relâchant le bouton après 9 secondes d’appui, le produit est redémarré.


## Changement du script

Test de connection (38400 bauds) au Siconia USB.
REPL Javascript fonctionnel
Création d’un repertoire siconia dans endpoint

CR
9600 baud


## Annexe

### Galerie

![Siconia](images/siconia-board-1.jpg)
![Siconia](images/siconia-board-2.jpg)
![Siconia](images/siconia-inside.jpg)
![Siconia on bike saddle](images/siconia-saddle.jpg)
