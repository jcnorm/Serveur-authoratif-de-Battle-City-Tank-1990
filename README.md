# Serveur authoratif de Battle City / Tank 1990:
Projet de session de système en temps réel sur Battle City / Tank 1990. On cherche à implémenter un serveur authoratif de validation d'état de jeu. L’implémentation (en C++11 avec la libraire graphique SDL2) du jeu fut réalisé par l’utilisateur Krystian Kaluzny et est disponible sur Github à cette adresse :
https://github.com/krystiankaluzny/Tanks

Le but de ce projet se divise en deux. Tout d’abord, ajouter des fonctions de triches pour briser le fonctionnement normal du jeu pendant son exécution. Puis, bâtir un serveur authoratif pour recevoir l’état de jeu et le renvoyer au client dans un état valide au besoin pour pouvoir rétablir le fonctionnement normal du jeu. Le tout doit se faire sans considérablement affecter les FPS ou tout autre métrique de performances du jeu. La partie serveur ne fonctionne qu’en Linux, ce qui contraint le jeu à ce système contrairement au projet original.

## Fonction de triches
Touche F5 : Incrémente la vitesse de déplacement du Tank joueur.
Touche F6 : Incrémente la quantité de balles pouvant exister pour le Tank joueur.
Touche F7 : Abrège le délai de tir avant de pouvoir tirer la prochaine balle.
Touche F8 : Instable! Peut causer des segfaults si il y a tirs en succession. Augmente la vitesse des balles tirées.


## Build

### Requis 
 - make
 - libsdl2-dev
 - libsdl2-ttf-dev
 - libsdl2-image-dev
 
 `sudo apt install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev`

### Compilation et exécution

Avec un terminal ouvert sur le dossier Tanks-master, où se trouve le Makefile, exécuté:

`make clean all`

Ensuite, ouvrir un deuxième terminal et à partir de Tanks-master exécuter pour démarrer le serveur authoratif:

`cd build/remote_server && ./Server`

Finalement, on démarre le jeu dans le premier terminal avec la ligne suivante:

`cd build/bin && ./Tanks -valid`

L'argument -valid est nécessaire pour activer la communication avec le serveur.
Il faut l'enlever si on veut constater l'effet de la triche sur le jeu.

On peut les arrêter tout les deux avec un signal SIGINT (Ctrl-C)



