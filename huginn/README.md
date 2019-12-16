# CampusIoT :: Huginn :: Tutorial :us:

## Huginn
Huginn est un système d'exécution d'agents qui effectuent des tâches automatisées telles que lire un site Web, surveiller les événements puis effectuer des actions. C'est une alternative open-source et on premise de IFTTT ou Zapier.

L'objectif du tutoriel est de souscrire au flot MQTT d'une application de CampusIoT pour déclencher l'envoi d'alerte (Mail, SMS).

## Démarrage avec CampusIoT

Pour démarrer Huginn, le plus simple est d'utiliser Docker:

```
docker run -name huginn --hostname huginn -d -p 3000:3000 huginn/huginn
docker logs -f huginn
```

Ouvrez la page http://localhost:3000

Connectez-vous avec l'utilisateur `admin` et le mot de passe `password`

## Création de l'agent MQTT

Ajoutez un nouvel agent MQTT en utilisant le menu `Agents > + New Agent` en selectionnant le type `MQTT Agent` dans la liste des agents disponibles.

Configurez l'agent MQTT avec les paramètres suivants: TBC
