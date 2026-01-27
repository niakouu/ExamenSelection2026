# Défi base de données

Pour ce défi, vous devez avoir [docker](https://docs.docker.com/engine/install/) d'installé afin de pouvoir utiliser la base de données (Postgres) et l'interface web (Adminer)

Après avoir installé `docker`, il suffit de démarrer la base de données et l'interface web avec la commande suivante:

```bash
docker-compose up -d
```

## Utilisation d'Adminer

L'interface web Adminer est accessible à l'adresse suivante: [http://localhost:8080](http://localhost:8080)

Les informations de connexion sont les suivantes:
- Système: PostgreSQL
- Serveur: db
- Utilisateur: root
- Mot de passe: mypassword

## Initialisation de la base de données

Pour initialiser la base de données, vous devez suivre les étapes suivantes:
1. Accéder à l'interface web Adminer: [http://localhost:8080](http://localhost:8080)
2. Se connecter avec les informations de connexion fournies ci-dessus
3. Cliquer sur le bouton `create database` et créer une base de données nommée `challenge`
4. Cliquer sur le bouton à droite `SQL command`
5. Copier le contenu du fichier `init.sql` et le coller dans la zone de texte
6. Cliquer sur le bouton `Execute` 

## Pour exécuter des commandes SQL

1. Cliquer sur le bouton à droite `SQL command`
2. Écrire votre commande SQL dans la zone de texte
3. Cliquer sur le bouton `Execute`  

# Challenge

Lorsque vous avez trouver la requête sql, simplement l'ajouté dans le fichier correpondant dans le dossier `querry/` 

## 1. Trouver seulement le titre et le genre des jeux qui sont plus vieux que 1987

Format de sortie attendu:
| titre           | genre |
|-----------------|--------------|


## 2. Trouver la somme du nombre de jeux faits par Nintendo et PlayStation

Format de sortie attendu:
| nombre_de_jeux |
|------------|

## 3. Trouver le nombre de jeux par année, mais seulement pour les années où il y a plus d'un jeu sorti

Format de sortie attendu:
| annee | nombre_de_jeux |
|-------|----------------|

## 4. Trouver le nom du jeu et des personnages dans ce jeu pour les jeux avec une note supérieure à la moyenne de tous les autres.

Format de sortie attendu:
| titre | nom |
|--------------|-------------------|

## 5. Trouver tous les jeux avec le même genre de jeu que le personnage "Luigi".
En d'autres termes, si Luigi est dans un jeu de plateforme, trouver tous les autres jeux de plateforme.
Retourner seulement le nom des jeux et leur genre en excluant le jeu et le genre du jeu de Luigi.

Assurez-vous de ne pas dupliquer les titres ou les genres.

Format de sortie attendu:
| titre | genre |
|--------------|----------------|

## 6. Trouver le nom des personnages qui apparaissent dans plus d'un jeu.

Format de sortie attendu:
| nom |
|--------------|

## 7. Trouver les noms de tous les personnages qui apparaissent dans des jeux faits par Nintendo après l'année 1984.
Il ne faut pas dupliquer les noms des personnages.

Format de sortie attendu:
| nom |
|--------------|

## 8. Trouver les personnages dans les jeux Capcom après 1984, avec le nombre de jeux dans lesquels ils apparaissent et la note moyenne de ces jeux

En d'autres termes, pour chaque personnage, compter le nombre de jeux Capcom après 1984 dans lesquels ils apparaissent et calculer la note moyenne de ces jeux.

Format de sortie attendu:
| nom | nombre_de_jeux | note_moyenne |
|--------------|----------------|----------------|

## 9. Classer en ordre décroissant de note et de nombre de personnages les consoles qui ont la meilleure note moyenne pour les jeux sortis.

Assurez-vous de ne pas dupliquer les personnages ou les consoles.

Format de sortie attendu:
| console | note_moyenne | nombre_de_personnages |
|--------------|----------------|-------------------|

## 10. Pour chaque pays, trouver le nombre de développeurs de jeux vidéo, le nombre de jeux développés par ces développeurs, la note moyenne de ces jeux, le nombre de personnages créés, le nombre de consoles, la première année de sortie d'un jeu ainsi que la dernière année de sortie d'un jeu.

Assurez-vous de ne pas dupliquer les développeurs, jeux, personnages ou consoles.

Format de sortie attendu:
| pays_developpeur | nombre_developpeurs | nombre_jeux | note_moyenne | nombre_personnages | nombre_consoles_sorties | premiere_sortie | derniere_sortie |
|--------------|----------------|----------------|----------------|-------------------|-------------------|-------------------|-------------------|
