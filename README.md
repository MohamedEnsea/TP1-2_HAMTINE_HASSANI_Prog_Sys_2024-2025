# ENSEASH
Dans le cadre de notre TP de synthèse, l'objectif est de réaliser un micro shell, affichant les codes de sortie et les temps d’exécution des programmes lancés.

## Organisation
Ce TP a été réalisé par Mohamed HAMTINE et Wilal HASSANI (2G2/TD1/TP1) et s'étend sur deux séances de 8 heures chacune. Nous avons structuré le projet de manière à ce que chaque fichier corresponde à une question différente.

## Fonctionnement
Avant d'exécuter le code, il est important de s'assurer que le chemin est bien défini pour vérifier que l'on se trouve dans le bon répertoire de travail pour exécuter nos codes. Pour cela, on peut utiliser la commande "pwd". Si on n'est pas dans le bon répertoire, il faut utiliser la commande suivante : cd /workspaces/codespaces-blank/enseash.

Pour vérifier que l'on est dans le bon répertoire, on peut utiliser la commande "ls" qui permet de lister le contenu du répertoire courant, y compris les fichiers et les sous-répertoires.

Ensuite, pour exécuter le code de chaque fichier (chaque question), il suffit d'écrire dans le terminal :
- make (pour tout compiler)
- gcc -o enseash question1.c (exemple pour le fichier question1.c)
- ./enseash

## Pour la question 2
Lors de la réalisation des tests, nous avons utilisé des commandes comme "date", "cal" ou "clear". Attention, la commande "fortune" ne fonctionne pas sur cet IDE.
