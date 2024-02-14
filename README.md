# Tetris

## Participants

* Augusto MIRANDA DE PAULA
* Nuno BARBOSA

## Case Analysis

* Implanter complètement les règles du Jeu TETRIS simple utilisateur;
* Plusieurs joueurs peuvent jouer ensemble;
* Un utilisateur peut inviter l'autre à travers du logiciel;
* Il est possible d’avoir l’ordinateur qui simule un joueur.

## Le jeu

### Le plateau de jeu

Le plateau de jeu est souvent appelé « puit » ou « matrice ». Il s'agit de l'espace dans lequel tombent les pièces. Il dispose toujours d'une grille en arrière-plan, visible ou non, dont les cases sont de la même grandeur que les carrés des pièces, et que celles-ci suivent dans leur chute. Il est également entouré par une armature appelée « tétrion », infranchissable, qui pose les limites du champ de jeu.

D'après le Tetris Guidline, la taille du champ de jeu en norme est de dix cases de largeur et de vingtdeux cases de hauteur. Cependant, quelques jeux font exceptions, comme Tetrinet (douze cases de largeur) ou Tetris Jr. (huit cases de largeur).

### Les pièces

Les pièces dans se jeux sont des assemblages de quatre carrés. Il existe en tout 7 pièces

Les sept pièces sont les suivantes :
* **I**: aussi appelée « bâton », « ordinaire », « barre » ou « long ». Elle est constituée de quatre carrés formant une ligne.
* **O**: aussi appelée « carré » ou « bloc ». Elle est constituée de quatre carrés formant un méta-carré de 2x2.
* **T**: Elle est constituée de trois carrés en ligne et d'un quatrième carré sous le centre.
* **L**: Elle est constituée de trois carrés en ligne et d'un quatrième carré sous le côté gauche.
* **J**: aussi appelée « L inversé » ou « gamma ». Elle est constituée de trois carrés en ligne et d'un quatrième carré sous le côté droit.
* **Z**: aussi appelée « biais ». Elle est constituée de quatre carrés formant un méta-carré de 2x2, dont la rangée supérieure est glissée d'un pas vers la gauche.
* **S**: aussi appelée « biais inversé ». Elle est constituée de quatre carrés formant un métacarré de 2x2, dont la rangée supérieure est glissée d'un pas vers la droite.

Chacune des sept pièces dispose d'une couleur qui lui est propre. Il n’y a aucune couleurprédéterminée pour chacune des pièces.

### Les mouvements latéraux
Le joueur peut à l’aide de certaines touches déplacer latéralement les pièces, c'est-à-dire vers la droite ou vers la gauche. Cependant si la pièce touche les bords du jeu, le déplacement ne sera pas possible.

### Les rotations

Le joueur peut faire tourner plusieurs fois à gauche et/ou à droite selon la version, de 90° n'importe
quel bloc pour le poser de la façon désirée pendant que le bloc descend.

### La chute des pièces

La vitesse de la chute des pièces est déterminée par le niveau auquel le joueur se trouve. Plus le niveau est élevé, plus les pièces tombent vite ! 

Au niveau 0 on peut faire 5-6 déplacements latéraux avant que la pièce tombe d'un rang, au niveau 9 on ne peut plus faire que 1-2 mouvements latéraux. Le niveau 15 équivaut au niveau de la vitesse à tout le temps appuyer sur la flèche du bas, il n'y a plus de déplacements latéraux possibles directement.

### Le cas particulier des rotations

Tant qu’une action sur une pièce est en cours, une pièce n'est définitivement posée sur l'écran de jeu.

Le joueur peut même si aucun déplacement latéral n’est possible procéder à des rotations de la pièce et peut ainsi soit déplacer latéralement la pièce soit poser la pièce sur une autre pièce par exemple.

### La suppression de lignes
Quand une ligne est pleine, c'est-à-dire aucune case de cette ligne n’est vide, cette ligne est supprimée.

### Le but du jeu

Le jouer doit essayer de jouer le plus longtemps possible avant que le plateau de jeu ne soit rempli. Ke
score est calculé comme suit en fonction du nombre de lignes supprimées en une passe :

* une ligne qui disparaît rapporte 40 points,
* 2 lignes qui sont supprimées rapportent 100 points
* 3 lignes qui sont supprimées rapportent 300 points
* 4 lignes (on ne peut pas plus) rapportent 1200 points.

Pour compliquer un peu les formules le nombre de points dépend en fait du niveau. La formule pour
calculer le nombre de points obtenus par la suppression d’un ou plusieurs lignes pour un niveau donné
est :
$$f(p,n)=p(n+1)$$
où p est le nombre de points au niveau 0 et n le niveau actuel.

## Classes

* Classe Game
* Classe Utilisateur
* Classe père pour les blocs 
    * Classe fils = types de blocs (7)
    * Classe neto = chaque bloc
* Classe grid
* Classe Interface Utilisateur
* Classe Controleur
* Classe Serveur
* Classe gerent des pièces

## Diagramme

## Approche

1. Créer un noyau du programme (prototype simple : nombre restreint de pièces, mouvement limités)
2. ensuite d’ajouter les éléments supplémentaires (pièces supplémentaires, calcul du score, gestion des joueurs)