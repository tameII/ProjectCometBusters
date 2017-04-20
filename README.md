# ProjectCometBusters
This is a project from two L1 informatique from fac des sciences et technologie of Nancy.

Ce Changelog sera écrit dans un autre ReadMe lors du rendu de la version finale. (on peut en discuter bien sur ! )
Et dans ce ReadMe il y aura le pseudo-scenario + les controles du jeu.
(et pourquoi pas les explication de pourquoi il y a des frottement, ou pourquoi un escargot spatial géant glisse le long de l'écran).
-
CHANGELOG:
-


la v.0.5 sera quand les astéroides seront bien implémentés

Update v.0.425: (Mathieu Levy)

-Ajout d'une procédure hyperespace:
--Qui prend un sprite_t.
--Si le sprite rencontre un bord de l'écran il est tp.
--Faut-il faire un fonction qui kill les astéroides sortant de l'écran?

-Fixed SetUpPosition:
--L'astéroide apparaissait seulement en 0.
--la RandomDirection fonctionnait correctement.
--Du coup j'avais l'impression que les 4 angles était concernés

-Dans la struct Sprite_t:
--int decompte:
---Sera très utile pour... Hé oui ! decompter des trucs.
--SDL_Rect image:
---Pour la rotation des images des sprites.
---En fait c'est la création du rectangle source pour le blit.
--ceci permet une simplification de la lisibilité du code:

-Dans sprite_move:
--du coup appel de fonction hyperespace.
--Ajout pour type 0(vaisseau) et type 1 (gros asteroide) de:
---utilisation du SDL_Rect image du sprite pour definir la direction
---et l'animation du sprite.
--Pour type 0:
---Truc habituel, je l'ai juste déplacé dans le sprite move.
--Pour type 1:
---Utilisation du decompte pour gerer la vitesse de rotation
---plus tard on pourra ajouter des fonction pour gerer la vitesse dans le cas ou l'ast se fait marave par les tirs.

-Ajout du pointeur global *nbBigAst. (d'autre suivront).
--Le but est de simplifier les appels de fonctions.

-Changement des images d'ast:
--parce que je trouvais ça plus pratique.
--je referais les images d'astéroides a l'occasion.
--cette fonction downloadsprite est vraiment géniale.

Update v.0.420: (Mathieu Levy)


-Ajout d'une procédure SetUpPosition:
--Qui prend un sprite_t et un SDL_Surface.
--Pour chaque type elle definit une position.
--/!\ elle fonctionne bizarre avec le bigast.
(apparait seulement en (0,0), (0,hauteur-max),
(largeur-max,0), (largeur-max,hauteur-max)).


-Ajout d'une procédure Random_Position:
--Qui prend un sprite_t.
--modifie la position x et y
de manière aléatoire (a améliorer)


-Ajout d'une procédure Random_Direction:
--Qui prend un sprite_t et un float vitesse.
--Donne une direction aléatoire a la vitesse donnée.
--elle est appelé dans sprite-boost (pour l'instant)


-Ajout d'une procédure download(et de sa fonction
auxiliaire download):
--permet d'alleger la lecture du main.
--Cette fonction telecharge les image sur le disque dur
pour les garder dans la RAM.


-Amélioration de la struct:
--Ajout d'un SDL_Rect pour chaque "objets"
--Reflexion sur l'utilisation du nb_sprite. (pour alleger
l'appel de la fonction handle-event)
--Utilisation du "size" du sprite(expliqué après).

-Amelioration de sprite-init:
--initialise la size pour chaque type
--type 0: vaisseau, type 1: gros ast, type 2 : norm ast,
type 3: small ast, type 4: tir. (tu es ok pour ça ? )


-Amelioration de sprite-move:
--en fait c'est plutot le début du vrai sprite-move.
--tout ça pour alleger le main bien sur et faire
quelque chose de fonctionnel.

-Création de la procédure CreateBigAst:
--Qui prend un sprite_t, un SDL_Surface et un pointeur
qui mène vers le nb total de bigAst existant.
--Pour l'instant appuie sur o pour créé un ast.

-Création de procédure kill:
--appuie sur p pour supprimer un ast (solution temporaire).
