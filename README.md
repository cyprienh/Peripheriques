# BE Périphériques
#### Maïlis Dy, Emily Holmes, Cyprien Heusse
Ce repository contient le code du projet de périphériques pour implémenter la commande d'un voilier.
Les différentes fonctions réalisées sont :
- F1 - Bordage automatique (Cyprien Heusse)
- F2 - Orientation du voilier (Emily Holmes)
- F3 - Système anti-chavirement (Maïlis Dy)
- F4 - Communication avec la télécommande (Emily Holmes)
- F5 - Real Time Clock (Cyprien Heusse)

Ce projet a été créé sur Keil μVision pour STM32F103.

## Mapping
L'architecture du projet est la suivante :
![Mapping-1](https://user-images.githubusercontent.com/46382251/203351447-dd459ae1-9e70-4edb-9482-e1c2d52973bf.jpg)

## Utiliser ce projet
Le projet final se situe dans le dossier "Voilier".
Il s'agit d'un projet Bare Metal, les drivers pour les différents périphériques ont été programmés par nous. Vous pouvez trouver des tests des différents pérophériques dans les dossier "TPx_...".
