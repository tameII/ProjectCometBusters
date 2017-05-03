# ProjectCometBusters
This is a project from two L1 informatique from fac des sciences et technologie of Nancy.


----
CHANGELOG:
----

Ce Changelog sera écrit dans un autre ReadMe lors du rendu de la version finale. (on peut en discuter bien sur ! )  
Et dans ce ReadMe il y aura le pseudo-scenario + les controles du jeu.  
(et pourquoi pas les explication de pourquoi il y a des frottement, ou pourquoi un escargot spatial géant glisse le long de l'écran).  

la v.0.5 sera quand les astéroides seront bien implémentés.  

--------
Update v.0.440: (Mathieu Levy, 24/04/2017:20h54)  

- Add function CreateExplosion:  
  -- With a new sprite.  
  -- Funny a mettre en place.  
  -- press e to create an explosion youhou  

- Fixed DivideAst:  
  -- Hope no more problem will appear.  
  -- and now you have ONE explosion when you divide ast  
- Fixed KillAst:  
  --Hope the same.  

- Add init_all_sprite :  
 --init all sprite.  

- Add a procedure Divide_ast_param ou un truc comme ça:  
 -- purement esthetique.  
 --permet d'alleger la lecture de divide ast  
 --je l'ai calé dans physique.c pour l'instant, ça me saoulait avec toute les erreur toutes ses conditions annexes qui me brouillaient la vue.  
  


- Il n'y a pas beaucoup d'écrit aujourd'hui mais les erreurs étaient fort nombreuses et je n'ai pas pris le temps de noter chacune.  

Que pensez-vous d'une file pour gérer l'affichage des explosions ?  
ça ferait une bonne expérience.

Update v.0.436: (Mathieu Levy, 21/04/2017:23h55)  

- the global variable *temps_actuel:  
 -- is isn't used with SDL_GetTick for the time being.  

- in kill_ast:  
--Bug fixed:  
---Fixed the capacity of kill when just one ast is init  
---Add a security, so no prob if we forgot to init something (see explication after)  

- in main  
-- Now we init all ast before the while  
-- so if no ast is on screen, the kill_ast dont overrun the memory.  

- in main-while  
-- add procedure CreateAst:  
--- take 3 sprite_t : big, norm and small ast.  

- Utilisation of SDL_GetTick :  
--There is some issue i don't understand:  
--In the while i call CreateAst, in Create Ast, when the SDL_GetTick = 
1000 for exemple i create an ast. But the fonction is called twice in a same milisecond (i think). So i prefer to use a personal variable who count +1 for each turn of while.   

- in HandleEvent :  
-- J'ai fait joujou.  
-- when press "k" : a random ast is chosen and destroyed from all ast.  

- in Random_Position:  
-- some modification was held.  
-- i try to do a good random position,this will get better with time.  


Update v.0.435: (Mathieu Levy, 21/04/2017).

- Dans struct sprite_t :  
-- Ajout de int numero_object:  
--Permet de connaitre le numero de l'objet demandé.  
---est-ce vraiment utile ? comment s'en servir efficacement?  
--Ajout de nombre_max;  
---ça c'est très utile.  
---Donne le nombre max possible de sprite du type demandé.  
---Pour l'instant me sert pour kill_ast (voir ci dessous).  
---Je vais peut être améliorer d'autres fonctions grace à ça.  

- Dans sprite_init :  
--Lors de l'appel de la fonction on doit  
--donner le nombre max de sprite prévu.  
--suite logique de l'ajout de nombre_max.  
--Ajout de le l'initialisation de numero_object.  

- Ajout de la procédure kill_ast:  
--Qui prend un sprite_t, un int et un bool.  
--le int permet de positionner le curseur dans le tableau.  
--le bool doit être initialisé a false au début.  
--Il indique si l'astéroide est détruit ou pas.  
--Utilise la procédure kill créé precedemment.  
--Fonctionne pour gros, normal, petit asteroide.  
--Cette fonction pourrait servir pour d'autre tableaux de sprites.  
--Du coup on la renommera au pire.  
 
- Dans HandleEvent:  
--press k to test kill_ast  
--Remplacez le numero pour tester les différents trucs.  

--
Update v.0.430: (Mathieu Levy)  
Allelujah

-Ajout de la procédure CreateSmallAst:  
--similaire a CreateBigAst  
--press u to pop a small ast  

-Ajout de la procédure CreateNormAst:  
--similaire a CreateBigAst  
--press i to pop a norm ast  

-Ajout des procédures permettant de poper régulièrement des asts:  
--utilisation du SDL_GetTick qui récupère le nb de ms passée depuis début du jeu.  
--ça fonctionne bizarre, deux ast popent d'un coup...  
--Mise en commentaires car besoin d'être améliorée.  

-Amélioration de la procédure Random_Position:  
--notamment par l'utilisation de SDL_GetTick.  
--Mais aussi par l'utilisation d'un booleen.  
--permet de déplacer l'ast pour eviter de le faire poper exactement au meme endroit qu'avant.  
--en effet il faut deux trois secondes pour avoir un nouveau random correct.  
--je pense que c'est dû au fait de faire modulo le temps depuis 1980 ou je sais plus quelle date.  
--en corrigeant a l'aide de SDL_GetTick on obtient un aléatoire plus puissant.  

--
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

--
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
