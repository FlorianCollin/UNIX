# Shared Memory
## Exercice 1

Écrire un programme qui crée une mémoire partagée permettant de stocker un entier non signé, initialisez la valeur à 1 et ajouter un processus fils. Le père et le fils implémenteront une boucle qui lira la valeur de l’entier non signé dans la mémoire partagée, affichera la valeur, incrémentera celle-ci et sauvegardera la valeur dans la mémoire partagée. Qu’observez-vous ? Remédiez-y.

## Exercice 2

Écrire un programme qui permet de trouver la plus petite valeur d’un tableau en parallélisant la recherche avec N processus, N étant un argument donné en entrée du programme. Le tableau sera de taille N^5 et sera généré aléatoirement au début du programme dans une mémoire partagée. Le seul moyen de communication autorisé entre les processus sera la mémoire partagée.
