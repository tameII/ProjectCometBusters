# ProjectCometBusters
This is a project from two L1 informatique from fac des sciences et technologie of Nancy.

CHANGELOG:

la v.0.5 sera quand les astéroides seront bien implémentés
Update v.0.420:


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
