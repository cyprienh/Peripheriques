# BE Périphériques
#### Maïlis Dy, Emily Holmes, Cyprien Heusse
Ce repository contient le code du projet de périphériques pour implémenter la commande d'un voilier.
Les différentes fonctions réalisées sont :
- F1 - Bordage automatique (Cyprien Heusse)
  - Mesure l’angle de la girouette afin de border les voiles grâce à une PWM.
- F2 - Orientation du voilier (Emily Holmes)
  - Via PWM et bit de signe, transformer la commande reçue en USART en instruction pour le moteur.
- F3 - Système anti-chavirement (Maïlis Dy)
  - Communication via SPI avec l’accéléromėtre pour lâcher les voiles lorsque le voilier chavire.
- F4 - Envoi d’informations sur le système via la télécommande (Emily Holmes)
  - Communication via le module XBee et USART sur la navigation, le chavirement et l’état de la batterie.
- F5 - Real Time Clock (Cyprien Heusse)
  - Lecture de l’heure en temps réel pour l’envoyer sur la télécommande.

L’ensemble du projet est contrôlé à l’aide de Systick qui appelle les fonctions ci-dessus à chaque tick. La fonction F4 est, elle, appelée tous les 3000 ticks, donc la télécommande reçoit des informations tous les 3000 ticks.

Ce projet a été créé sur Keil μVision pour STM32F103.

## Mapping
L'architecture du projet est la suivante :
![Mapping-1](https://user-images.githubusercontent.com/46382251/203351447-dd459ae1-9e70-4edb-9482-e1c2d52973bf.jpg)

## Utiliser ce projet
Le projet final se situe dans le dossier "Voilier".
Il s'agit d'un projet Bare Metal. Les drivers pour les différents périphériques ont été programmés par nous-mêmes. Vous pouvez trouver les tests des différents périphériques dans les dossiers "TPx_...".
