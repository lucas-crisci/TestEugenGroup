# TestEugenSystems

## Mode d'emploi
Ce jeu a été réalisé en C++ sous Visual Studio 2019.
Il ne nécessite pas l'installation de logiciel ou de librairies spécifiques.
La fonction main est localisée dans le fichier KnightVsOrc.cpp

## Déroulement
Au lancement du jeu, vous pourrez choisir de limiter le nombre de tour de jeu (5 ou 10 tours).
Si aucun joueur n'est mort pendant ces tours, il n'y a pas de gagnant.
Dans le cas ou le nombre de tours n'est pas limité, le jeu continuera jusqu'à ce qu'un personnage n'ait plus de points de vie.

A chaque tour, chacun des joueurs pourra choisir d'activer son skill s'il n'est pas en rechargement.
Les attaques se lancent ensuite automatiquement sur l'adversaire.

## Structure

Afin de permettre de créer de nouvelles classes plus facilement, une classe principale Fighter.cpp a été créée.
Elle permet de gérer les éléments principaux comme la gestion des points de vie ou l'affichage des données par exemple.
En dessous, on retrouve :
   - Knight.cpp qui permet de créer un combattant ayant un bouclier et possédant la compétence "Charge" et de gérer ces éléments.
   - Orc.cpp permettant l'utilisation du Stun principalement.

Le nombre de joueurs est de 2 comme demandé, mais le code est prévu pour pouvoir augmenter ce nombre.
Si le nombre de joueurs devient plus important, les joueurs pourront sélectionner les cibles de leurs compétences ou de leurs attaques.

## Amélioration
Étant donnée la structure du code, il serait facile de créer un éditeur de parties permettant de selectionner le nombre de joueurs, leurs classes...
