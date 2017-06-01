#include "physique.h"
#include <SDL_ttf.h> 


 
void SetUpAtMiddle(sprite_t *sprite1, sprite_t *sprite2);
void kill(int *nb);
///////////////////////////////////////////////////////////////////////////////
/******************************FIN HEADER*************************************/
//////////////////////////////////////////////////////////////////////////////
/*Create two portal, be aware to set the NB_MAX to a pair number, even if i set a security*/
void CreatePortal(sprite_t *portal)
{
  if(nbPortal < NB_MAX_PORTAL-1){  
    if(nbPortal < NB_MAX_PORTAL){
      sprite_init(&portal[nbPortal], 23, portal_picture, PORTAL_SIZE, NB_PORTAL_SPRITE, NB_MAX_PORTAL);
      nbPortal +=1;
    }
    if(nbPortal < NB_MAX_PORTAL){
      sprite_init(&portal[nbPortal], 23, portal_picture, PORTAL_SIZE, NB_PORTAL_SPRITE, NB_MAX_PORTAL);
      nbPortal +=1;
    }
  }
}

/*Create bombe atomique qui fait apparaitre a un endroit aleatoire une BOMBE ATOMIQUE OUH YEAH*/
void CreateAtomicBomb(sprite_t *bonus_atomic_bomb){
  if(nbAtomicBomb < 1){
    sprite_init(bonus_atomic_bomb, 21, atomic_bomb_picture, ATOMIC_BOMB_SIZE, 
		NB_ATOMIC_BOMB_SPRITE, NB_MAX_ATOMIC_BOMB);
	      
    nbAtomicBomb += 1;
  }
}
void CreateMitraille(sprite_t *mitraille)
{
  if(nbMitraille < 1)
    {
      sprite_init(mitraille,  22, bonus_mitraille, BONUS_MITRAILLE_SIZE, NB_BONUS_MITRAILLE_SPRITE, NB_MAX_BONUS_MITRAILLE);
      nbMitraille += 1;
    }
}
//    sprite_init(&big_ast[nbBigAst], 1, big_comet, BIG_AST_SIZE, NB_AST_SPRITE, NB_MAX_BIG_AST);
void kill_all_sprite_param(sprite_t *sprite, int nb_max)
{
  int i;
  for(i=0; i<nb_max;i++){
    sprite[i].life = 0;
  }
}
/*Fonction qui fait exploser TOUT les sprites sur l'ecran*/
/*Servira pour la bombe atomique et pour la fin du jeu
En fait ça met a zero toute les vie de chaque sprite si le space_ship->life = 0*/
void kill_all_sprite(sprite_t *space_ship,sprite_t *big_ast, sprite_t *norm_ast,
		     sprite_t *small_ast, sprite_t *tirs, int *gameover,
		     int *animationFinale, bool *bomb_triggered)
{

  if(space_ship->life <= 0){
    *animationFinale += 1;
    kill_all_sprite_param(big_ast, NB_MAX_BIG_AST);
    kill_all_sprite_param(norm_ast, NB_MAX_NORM_AST);
    kill_all_sprite_param(small_ast, NB_MAX_SMALL_AST);
    kill_all_sprite_param(tirs, NB_MAX_PIOU);
    SetUpPosition(space_ship);
    cogne = false;
    if( *animationFinale >= DECOMPTE_FIN){
      *gameover = 1;                                             // GAME OVER ICI !!!
    } 
  }
  if(*bomb_triggered == true){
    kill_all_sprite_param(big_ast, NB_MAX_BIG_AST);
    kill_all_sprite_param(norm_ast, NB_MAX_NORM_AST);
    kill_all_sprite_param(small_ast, NB_MAX_SMALL_AST);
    *bomb_triggered = false;
    }
}

/*Fonction qui fait disparaitre tout les sprites tableau de l'ecran*/
void kill_all_number()
{
  nbBigAst = 0;
  nbNormAst = 0;
  nbSmallAst = 0;
  nbtirs = 0;
  nbExplosion = 0;
}

void ajout_score(int *score, int point)
{
  *score += point;
}
void score(int *score, int type)
{
    if(type == 1){
      ajout_score(score, BIG_AST_POINT);
    }
    if(type == 2){
      ajout_score(score, NORM_AST_POINT);
    }
    if(type == 3){
      ajout_score(score, SMALL_AST_POINT);
    }
} 
/*Create explosion size 64*64*/
void CreateExplosion(sprite_t *explosion, sprite_t *sprite, int numero)
{
  if (nbExplosion < NB_MAX_EXPL){
    sprite_init(&explosion[nbExplosion], 5, explosion_picture, EXPLOSION_SIZE, ANIM_EXPLOSION_NUM, NB_MAX_EXPL);
    SetUpAtPosition(&explosion[nbExplosion], &sprite[numero] );
    nbExplosion += 1;
  }

}

/*Test si le ship est mort, fonctionne pour tout sprite unique. (bon en vrai que pour le ship pour l'instant, mais peut être update)*/
void dead_ship_param(sprite_t *sprite, int  *gameover, int *score_total, bool *droitDeScorer)
{
  bool dead = false;
 
  if(sprite->life <= 0){
    dead = true;
  } 
  if(dead){
    *droitDeScorer = false;
  }
}
/*Teste si chaque element du tableau est mort.fonctionne pour tout tableau.*/
void dead_tab_param(sprite_t *sprite, sprite_t *big_ast, sprite_t *norm_ast,
		    sprite_t *small_ast, sprite_t *explosion, int *score_total,
		    bool *droitDeScorer)
{
  int i;
  int type = sprite->type;
  int nb = gimmeIsNb(sprite);
  bool dead = false;
  for(i=0;i<nb;i++){
    if(sprite[i].life <= 0){
      dead = true;    
      if(dead){
	if (type == 1 || type == 2 || type == 3){
	  CreateExplosion(explosion, sprite, i);
	  if(*droitDeScorer){
	  score(score_total, type);
	  }
	}
	DivideAst(sprite, i, big_ast, norm_ast, small_ast);
	kill_ast(sprite, i);
      }
    }
  }
}
/*Appelle les fonctions permettant de savoir si u sprite est mort, et de le tuer si c'est le cas (oui oui)*/
void dead(sprite_t *space_ship, sprite_t *big_ast, sprite_t *norm_ast, sprite_t *small_ast, sprite_t *tirs, sprite_t *explosion, int *gameover, int *score_total, bool *droitDeScorer)
{
  dead_ship_param(space_ship, gameover, score_total, droitDeScorer);
  dead_tab_param(big_ast, big_ast, norm_ast, small_ast, explosion, score_total, droitDeScorer);
  dead_tab_param(norm_ast, big_ast, norm_ast, small_ast, explosion, score_total, droitDeScorer);
  dead_tab_param(small_ast, big_ast, norm_ast, small_ast, explosion, score_total, droitDeScorer);
  dead_tab_param(tirs, big_ast, norm_ast, small_ast, explosion, score_total, droitDeScorer);
}


void Get_Mitraille();
void collide_ship_bonus_param(sprite_t *sprite1,  sprite_t *sprite2, bool *bomb_triggered, bool *have_mitraille)
{
  if(sprite2->type == 21){
    if(compare_position(sprite1, sprite2)){
      *bomb_triggered = true;
      kill(&nbAtomicBomb);
    }
  }
  if(sprite2->type == 22){
    if(compare_position(sprite1, sprite2)){
      Get_Mitraille();
      kill(&nbMitraille);
    }
  }
}

/*Collide pour le ship, /!\ ne pas utiliser de tableau dans sprite 1 !!! /!\ c'est le space_ship en sprite1*/
void collide_ship_param(sprite_t *sprite1,  sprite_t *sprite2, bool *cogne, int *decompte)
{
  int j;
  int nb2 = gimmeIsNb(sprite2);
  for(j=0; j<nb2; j++){
    if(compare_position(sprite1, &sprite2[j])){
      sprite1->life -= 1;
      sprite2[j].life -= 1;
      *cogne = true;
      *decompte = DUREE_INV_APP_DEGATS;
      //printf("Ship collide with sprite type : %d \n",sprite2[j].type);
    }
  }
}

/*Tableau en sprite 1 et en sprite2, donnez*/
void collide_tab_param(sprite_t *sprite1,  sprite_t *sprite2)
{
  int i, j;
  int nb1 = gimmeIsNb(sprite1);
  int nb2 = gimmeIsNb(sprite2);
  if(nb1>0 && nb2>0){
    for(i=0; i<nb1; i++){  
      for(j=0; j<nb2; j++){
	if(compare_position(&sprite1[i], &sprite2[j])){
	  sprite1[i].life -= 1;
	  sprite2[j].life -= 1;
	}
      }
    }
  }
}

/*Fonction qui teleporte UN sprite si CE sprite rencontre un portal*/
void teleportation(sprite_t *sprite1, sprite_t *portal)
{
  int j;
  for(j=0; j<nbPortal; j++){
    if(compare_position(sprite1, &portal[j])){
      if(j%2 == 0){
	SetUpAtMiddle(sprite1, &portal[j+1]);
	kill_ast(portal, j+1);
	kill_ast(portal, j);
      }
      else if(j%2 == 1){
	SetUpAtMiddle(sprite1, &portal[j-1]);
	kill_ast(portal, j);
	kill_ast(portal, j-1);
      }
    }
  }
}

/*Verifie si le tirs ou space_ship est en contact avec big/norm/small_ast*/
/*Faites appel a collide_tab_param dans le cas de deux tableau,          */
/*et collide_ship_param dans le cas d'un sprite un tableau               */
void collide(sprite_t *space_ship, sprite_t *tirs, sprite_t *big_ast,
	     sprite_t *norm_ast, sprite_t *small_ast, int *gameover,
	     bool *cogne, int *decompte, sprite_t *bonus_atomic_bomb,
	     bool *bomb_triggered, bool *have_mitraille, sprite_t *mitraille,sprite_t *portal)
{
  collide_tab_param(tirs, big_ast);
  collide_tab_param(tirs, norm_ast);
  collide_tab_param(tirs, small_ast);
   
  collide_ship_param(space_ship, big_ast, cogne, decompte);
  collide_ship_param(space_ship, norm_ast, cogne, decompte);
  collide_ship_param(space_ship, small_ast, cogne, decompte);
  teleportation(space_ship, portal);

  collide_ship_bonus_param(space_ship, bonus_atomic_bomb, bomb_triggered, have_mitraille);
  collide_ship_bonus_param(space_ship, mitraille, bomb_triggered, have_mitraille);
}

/*Prend deux sprites, rend true si les deux sprites sont en contact très grossier*/
bool compare_position(sprite_t *sprite1, sprite_t *sprite2)
{
  int cu = 0;
  int cv = 0;
  return collide_test(*sprite1, *sprite2, sprite1->sprite_picture->format ,&cu, &cv);
}

/*Fonction Collision pour un carré, prend des points x et y et ajoute leurs longueur a    */
/*Puis compare les position des deux carrés et rend un booleen (vrai = carrés se touchent)*//*
bool compare_position_param(int x1, int y1, int a1, int x2, int y2, int a2)
{
  bool collision = false;
  if(min(x1+a1, x2+a2)>max(x1, x2) && min(y1+a1, y2+a2)>max(y1, y2)){
    collision = true;
  }
  return collision;
}
*/

/*Create Small Ast, appel de sprite_init avec les carac' du small_ast,*/
/* puis donne une vitesse aléatoire avec sprite_boost                 */
void CreateSmallAst(sprite_t *small_ast)
{
  if(nbSmallAst < NB_MAX_SMALL_AST){
    sprite_init(&small_ast[nbSmallAst], 3, small_comet, SMALL_AST_SIZE, NB_AST_SPRITE, NB_MAX_SMALL_AST);
    sprite_boost(&small_ast[nbSmallAst], VIT_SMALL_AST);
    nbSmallAst += 1; 
  }
  
}

/*Create Norm Ast*/
void CreateNormAst(sprite_t *norm_ast)
{
  if (nbNormAst < NB_MAX_NORM_AST){
    sprite_init(&norm_ast[nbNormAst], 2, norm_comet, NORM_AST_SIZE, NB_AST_SPRITE, NB_MAX_NORM_AST);
    sprite_boost(&norm_ast[nbNormAst], VIT_NORM_AST);
    nbNormAst += 1;
  }
  
} 

/*Create comet size 64*64,*/
void CreateBigAst(sprite_t *big_ast)
{
 
  if (nbBigAst < NB_MAX_BIG_AST){
    sprite_init(&big_ast[nbBigAst], 1, big_comet, BIG_AST_SIZE, NB_AST_SPRITE, NB_MAX_BIG_AST);
    sprite_boost(&big_ast[nbBigAst], VIT_BIG_AST);
    nbBigAst += 1;
  }
  
}

/*Create an ast*/
void CreateAst(sprite_t *ast){
  if (ast->type == 1){
    CreateBigAst(ast);
  }
  if (ast->type == 2){
    CreateNormAst(ast);
  }
  if (ast->type == 3){
    CreateSmallAst(ast);
  }
    
}


/*Kill, The cursor on the tab recule*/
void kill(int *nb)
{
  if (*nb>0){
    *nb -= 1;
  }
  
}
/*Donne le nombre d'astéroide présent sur l'écran */
int gimmeIsNb(sprite_t *sprite)
{
  int type = sprite->type;
  //printf("sprite->type = %d \n", type);
  switch (type){
  case 0:
    return 1;
    break;
  case 1:
    return nbBigAst;
    break;
  case 2:
    return nbNormAst;
    break;
  case 3:
    return nbSmallAst;
    break;
  case 4:
    return nbtirs;
    break;
  case 5:
    return nbExplosion;
    break;
  case 21:
    return nbAtomicBomb;
    break;
  case 22:
    return nbMitraille;
    break;
  case 23:
    return nbPortal;
    break;
  default:
    printf("gimmeIsNB : Error : ask type 0, 1, 2, 3, 4, 5, 21. \nType asked: %d \n",type);
    return 0;
    break;
  }
}


/*Kill the ast[numero]*/
void kill_ast(sprite_t *ast, int numero)
{
  bool killed = false;
  int type = ast->type;
  int nombre_max = ast->nombre_max;
  nombre_max -= 1;
  int nbAst;
  nbAst = gimmeIsNb(ast);
  if (type != 0){
    if (nbAst > 0){
      nbAst -= 1;
    }
    killed = kill_ast_param(nombre_max, numero, type);
    
    while (killed == false){
      //printf("kill_ast : numero : %d \n",numero);
      //printf("kill ast : nbAst : %d  \n",nbAst);
      //printf("kill ast : nb_max : %d \n",nombre_max);
      if (numero >= nbAst){
	switch (type) {
	case 1:
	  kill(&nbBigAst);
	  killed = true;
	  break;
	case 2:
	  kill(&nbNormAst);
	  killed = true;
	  break;
	case 3:
	  kill(&nbSmallAst);
	  killed = true;
	  break;
	case 4:
	  kill(&nbtirs);
	  killed = true;
	  break;
	case 5:
	  kill(&nbExplosion);
	  killed = true;
	  break;
	case 23:
	  kill(&nbPortal);
	  killed = true;
	  break;
	default:
	  printf("Kill_ast : wrong type. (you asked %d)",ast->type);
	  killed = true;
	  break;
	}   
      }
      if (killed == false){
	ast[numero] = ast[numero+1];
	if (ast[numero].numero_object > 0){
	  ast[numero].numero_object -= 1;
	}
	numero += 1;
      }
    }
  }
}


/*Invert direction of sprite 2 */
void InvertDirection(sprite_t *sprite1, sprite_t *sprite2){

  sprite2->vx = -sprite1->vx;
  sprite2->vy = -sprite1->vy;
}

/*Set Up sprie 1 at position sprite 2 */
void SetUpAtPosition(sprite_t *sprite1, sprite_t *sprite2)
{
  sprite1->x = sprite2->x;
  sprite1->y = sprite2->y;
}
/*Set up sprite1 at middle sprite2 ?*/
void SetUpAtMiddle(sprite_t *sprite1, sprite_t *sprite2)
{
  sprite1->x = sprite2->x + (sprite2->size)/2 - (sprite1->size)/2;
  sprite1->y = sprite2->y + (sprite2->size)/2 - (sprite1->size)/2;
}

/*Fonction qui fait apparaitre deux plus petit astéroide seulement si le type est 1 ou 2*/
void DivideAst(sprite_t *ast, int numero, sprite_t *big_ast, sprite_t *norm_ast, sprite_t *small_ast)
{
  int type = ast->type;
  int nb_Big_Ast = nbBigAst;
  int nb_Norm_Ast = nbNormAst;
  int nb_Small_Ast = nbSmallAst;
  //printf("Divide Ast : ast type %d \t | nb_Big_ast : %d \t| nb_Norm_Ast : %d \n nb_Small_Ast %d \n",type, nb_Big_Ast, nb_Norm_Ast, nb_Small_Ast);
  
  
  if(type == 1 && nb_Big_Ast > 0){  
    CreateAst(norm_ast);                                                 //Créé un norm ast
    SetUpAtPosition(&norm_ast[nb_Norm_Ast], &ast[numero]);                        //Met le premier norm ast a la position du gros ast.
    if (nb_Norm_Ast+1 < NB_MAX_NORM_AST){                                //Si on peut créer un second norm ast.
      CreateAst(norm_ast);                                               //Créé un norm ast
      SetUpAtPosition(&norm_ast[nb_Norm_Ast+1], &ast[numero]);                    //Met le second norm ast a la pos du gros ast.
      InvertDirection(&norm_ast[nb_Norm_Ast], &norm_ast[nb_Norm_Ast+1]); //lance les deux ast dans une direction opposée
    }
  }
  if(type == 2 && nb_Norm_Ast > 0){                                      //Pareil mais pour un norm ast.
    CreateAst(small_ast);
    SetUpAtPosition(&small_ast[nb_Small_Ast], &ast[numero]);
    if (nb_Small_Ast+1 < NB_MAX_SMALL_AST){
      CreateAst(small_ast);
      SetUpAtPosition(&small_ast[nb_Small_Ast+1], &ast[numero]);
      InvertDirection(&small_ast[nb_Small_Ast], &small_ast[nb_Small_Ast+1]);
    }
  }
}


/*Créé un astéroide a l'aide de la variable globale temps actuel*/
void CreateAstWithTime(sprite_t *big_ast, sprite_t *norm_ast, sprite_t *small_ast)
{
  if (temps_actuel%1000 == 0){                       //toute les 1000 tours de boucle un Gros Ast apparait
    CreateBigAst(big_ast);                          
  }
  if (temps_actuel%4000 == 0){                        //toute les 7000 tours de boucle  un Norm Ast apparait
    CreateNormAst(norm_ast);                          
  }
  if(temps_actuel%3000 == 0){                         //toute les 4000 tours de boucle un Small Ast apparait
    CreateSmallAst(small_ast);                        
  }

}
void CreateBonusWithTime(sprite_t *bonus_atomic_bomb, sprite_t *mitraille, sprite_t *portal)
{
  int i;
  int j;
  j = rand()%(CHANCE_D_APPARITION_MITRAILLE);
  i = rand()%(CHANCE_D_APPARITION_ATOMIC_BOMBE);
  if(i == 0){
    CreateAtomicBomb(bonus_atomic_bomb);
  }
  if(j == 0){
    CreateMitraille(mitraille);
  }
  i = rand()%(CHANCE_D_APPARITION_PORTAL);
   if(i == 0){
     CreatePortal(portal);
   }
}


//creation of projectile
void create_piou (sprite_t* tirs, sprite_t* space_ship)
{
  if (nbtirs<NB_MAX_PIOU){
    sprite_init(&tirs[nbtirs], 4, bullet, PIOU_SIZE, 1, NB_MAX_PIOU);
    tirs[nbtirs].current = space_ship->current/2;
    sprite_boost(&tirs[nbtirs], VIT_NORM_PIOU);
    SetUpAtMiddle(&tirs[nbtirs], space_ship);
    //printf("Piou !\n");
    nbtirs += 1;
  }
}

void change_sprite_ship (sprite_t *ship, SDL_Surface * spaceship, SDL_Surface * spaceship2)
{
  if(ship->sprite_picture == spaceship)
    {
      ship->sprite_picture = spaceship2;
    }
  else
    {
      ship->sprite_picture = spaceship;
    }
}

void Get_Mitraille(){
  have_mitraille = true;
  bonus_compt = 5000;
}
void Effect_mitraille()
{
  if (bonus_compt > 0)
    {
      can_piou = true;
      bonus_compt--;
    }
}

void HandleMenuReturn(sprite_t *jouer, sprite_t *quitter, bool *play, int *gameover, int *ending, int *finmenu)
{
  if(jouer->sprite_picture == menu_jouer_selec){
     *play = true;
     *gameover = 0;
     *ending = 1;
  }
  else if(quitter->sprite_picture == menu_quitter_selec){
    *ending = 1;
    *gameover = 1;
    *finmenu = 1;
  }
  else{
    /*Autres options*/
  }
}
/////////////////////////////////////////////////////////////////
/* Handle events coming from the user:
   - quit the game?
   - use left/right to change the orientation of the ship
   - use up to move on the ship to the right direction
   - down is not defined right now
   - o to create a new big asteroide
   - i to create a new norm ast
   - u to create a new small ast
   - p to kill the last small, norm, big ast created
   - k to use kill_ast
   - l to divide an ast.
   - t to create projectiles
   - b for various information. 
*/

  

void HandleEvent(SDL_Event event, int *quit, sprite_t *space_ship, double *accel,
		 sprite_t *big_ast, sprite_t *norm_ast, sprite_t *small_ast,
		 sprite_t *tirs, sprite_t *explosion, bool *play,
		 int *score_total, bool *bomb_triggered)
{
  int i,j;
  switch (event.type) {
    /* close button clicked */
  case SDL_QUIT:
    *quit = 1;
    break;
    
    /* handle the keyboard*/
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_ESCAPE:
    case SDLK_q:
      *quit = 1;
      break;
    case SDLK_k:                                  //KIll a random ast
      printf("touch k pressed \n");
      i = rand()%(3);
      if (i == 0){
	j = rand()%(NB_MAX_BIG_AST-1);
	kill_ast(big_ast, j);
      }
      if (i == 1){
	j = rand()%(NB_MAX_NORM_AST);
	kill_ast(norm_ast, j);
      }
      if (i == 2){
	j = rand()%(NB_MAX_SMALL_AST);
	kill_ast(small_ast, j);
      }
      // printf("i : %d, j : %d \n",i,j);
      
      //kill_ast(small_ast, 0);
      SDL_Delay(100);
      break;
    case SDLK_u:
      //printf("touch u pressed \n");
      CreateAst(small_ast);
      SDL_Delay(100);
      break;
    case SDLK_i:
      // printf("Touch i pressed \n");
      CreateAst(norm_ast);
      SDL_Delay(100);
      break;
    case SDLK_o:
      //printf("Touch o pressed\n");
      CreateAst(big_ast);
      SDL_Delay(100); //delai de 100 ms pour pas faire ooooooooooo
      break;
    case SDLK_p:                                               //it kill everything it touche
      // printf("Touch p pressed \n");
      kill(&nbBigAst);
      kill(&nbNormAst);
      kill(&nbSmallAst);
      kill(&nbtirs);
      //SDL_Delay(100);
      break;
    case SDLK_e:                                                //BOOOM
      printf("touch e pressed \n");
      CreateExplosion(explosion, big_ast, 0);
      SDL_Delay(100);
      break;
    case SDLK_y:                                             //Create ALL type of ast very fast
      CreateAst(big_ast);
      CreateAst(norm_ast);
      CreateAst(small_ast);
      break;
    case SDLK_w:                                              //Divide Ast
      printf("touch l pressed \n");
      DivideAst(big_ast, 1, big_ast, norm_ast, small_ast );  
      SDL_Delay(100);
      break;
    case SDLK_x:                                              //Divide Ast.
      printf("touch l pressed \n");
      DivideAst(norm_ast, 1, big_ast, norm_ast, small_ast);
      SDL_Delay(100);
      break;
    case SDLK_n:                      //ast -1life
      printf("touch n pressed \n");
      i = 0; //numero ast demandé
      j = 1; //nombre de vie retirée
      if(small_ast[i].life > 0){
	small_ast[i].life -= j ;
      }
      SDL_Delay(100);
      break;
    case SDLK_v :
      various_information(space_ship, big_ast, norm_ast, small_ast, score_total);
      SDL_Delay(100);
      break;
    case SDLK_c :
      change_sprite_ship(space_ship, spaceship, spaceship2);
      break;
    case SDLK_b :
      *bomb_triggered = true;
      break;
    default:
      break;
    }
    break;
  }

}

void HandleEvent2(SDL_Event event, sprite_t *space_ship, double *accel, int *quit, int Table_move[5], sprite_t *tirs, bool *can_piou){
  switch(event.type){
  case SDL_QUIT:
    *quit = 1;
    break;
    /* activation des action en appuyant sur les touches*/
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym)
      {
	/* case SLDK_ESCAPE: */
	/* 	*quit = 1; */
	/* 	break; */
      case SDLK_UP:
	Table_move[0] = 1;
	break;
      case SDLK_DOWN:
	Table_move[1] = 1;
	break;
      case SDLK_LEFT:
	Table_move[2] = 1;
	break;
      case SDLK_RIGHT:
	Table_move[3] = 1;
	break;
      case SDLK_SPACE:
	Table_move[4] = 1;
	break;
      default:
	break;
      }
    break;
    /*déactivation des actions en arretant d'appuyer*/
  case SDL_KEYUP:
    switch (event.key.keysym.sym)
      {
      case SDLK_UP:
	Table_move[0] = 0;
	break;
      case SDLK_DOWN:
	Table_move[1] = 0;
	break;
      case SDLK_LEFT:
	Table_move[2] = 0;
	break;
      case SDLK_RIGHT:
	Table_move[3] = 0;
	break;
      case SDLK_SPACE:
	Table_move[4] = 0;
	*can_piou = true;
	break;
      default:
	break;
      }
    break;
  }
  if(Table_move[0] == 1){
    *accel = CONS_ACCEL;
  }
  if(Table_move[1] == 1){
    *accel = -CONS_ACCEL;
  }
  if(Table_move[2] == 1){
    ship_turn_left(space_ship);
  }
  if(Table_move[3] == 1){
    ship_turn_right(space_ship);
  }
  if(Table_move[4] ==1 && *can_piou == true){
    create_piou(tirs, space_ship);
    *can_piou = false;
  }
}

void HandleEventMenu(SDL_Event event, int *gameover, bool *play, int *ending,
		     int *finmenu, sprite_t *jouer, sprite_t *quitter)
{
  switch (event.type) {
    /* close button clicked */
  case SDL_QUIT:
    *gameover = 1;
      *ending = 1;
      *finmenu = 1;
    break;
  case SDL_KEYUP:
    switch (event.key.keysym.sym)
      {
      case SDLK_ESCAPE:
      case SDLK_q:
	*gameover = 1;
	  *ending = 1;
	  *finmenu = 1;
	break;
      case SDLK_UP:
      case SDLK_DOWN:
	change_sprite_ship (jouer, menu_jouer, menu_jouer_selec );
	change_sprite_ship (quitter, menu_quitter, menu_quitter_selec );
	break;
      case SDLK_RETURN:
	HandleMenuReturn(jouer, quitter, play, gameover, ending, finmenu);
	break;
      default:
	break;
      }
  default:
    break;
  }
}
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
  /*Definition des différents sprites*/
  sprite_t jouer;      //type 10
  sprite_t quitter;    //type 11
  sprite_t game_over;  //type 12
  sprite_t return_menu; //type 13
  //sprite_t credit; //type 14 ?

  //les highscore avec SDL ttf ?
  sprite_t space_ship;
  sprite_t big_ast[NB_MAX_BIG_AST];
  sprite_t norm_ast[NB_MAX_NORM_AST];
  sprite_t small_ast[NB_MAX_SMALL_AST]; 
  sprite_t tirs[NB_MAX_PIOU];
  sprite_t explosion[NB_MAX_EXPL];

  /*bonus et affichage:*/
  sprite_t PV[MAX_LIFE_SHIP]; //type 20
  sprite_t bonus_atomic_bomb; //type 21
  sprite_t mitraille;  //type 22
 sprite_t portal[NB_MAX_PORTAL]; //type 23 TOUJOURS METTRE NB MAX PAIR

  int ScoreTotal;
  int *score_total;
  score_total = &ScoreTotal;

  /*Initialize rand :*/
  srand(time(NULL)); 

  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();

  /* Load the font. */
  TTF_Font *font = TTF_OpenFont("04B_30__.TTF", 32);

  /* set the title bar */
  SDL_WM_SetCaption("Comet Buster", "Comet Buster");
  
  /* create window */
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  
  /* set keyboard repeat */
  SDL_EnableKeyRepeat(10, 10);

  /*Download pictures of all sprites*/
  downloadsprite();
 
  /*Initialise all sprite*/
  init_all_sprite(&space_ship, big_ast, norm_ast, small_ast,
		  tirs, explosion, &game_over,
		  &return_menu, &jouer, &quitter, PV, portal);
  int gameover = 0;
  int ending = 0;
  int finmenu = 0;
  bool play = false;
  bool droitDeScorer = true;
  int animationFinale = 0;
  int Table_move[5]={0,0,0,0,0};
  can_piou = true;
  bool bomb_triggered = false;
  *score_total = 0;  //score_total = 0;
  cogne = false;
  have_mitraille = false;
  bonus_compt = 0;
  //CreateAtomicBomb(&bonus_atomic_bomb);
  /*Les variables utilisée avec SDL_TTF       *
   *  (les autres sont plus haut dans le main)*/
  char affichage_score[25] = "Comet Buster !!!"; /* Tableau de char suffisamment grand */
  SDL_Color color = { 255, 255, 255 };
  SDL_Surface *textSurface = TTF_RenderUTF8_Solid(font, affichage_score,
						  color);

  /*Menu :*/
  while (!finmenu){

    /*MENU :*/
    if(!play){
      SDL_Event event2;
      if (SDL_PollEvent(&event2)) {
	HandleEventMenu(event2, &gameover, &play, &ending, &finmenu, &jouer, &quitter);
	
	SDL_BlitSurface(background, NULL, screen, NULL);
	SDL_BlitSurface(jouer.sprite_picture, NULL, screen, &jouer.position);
	SDL_BlitSurface(quitter.sprite_picture, NULL, screen, &quitter.position);
	SDL_BlitSurface(textSurface, NULL, screen, NULL);
	SDL_UpdateRect(screen, 0, 0, 0, 0);
      }
    }
    /*JEU:*/
    if(play){
      /* main loop: check events and re-draw the window until the end */
      while (!gameover)
	{
	  int i;
	  double accel = 0.0;
	  SDL_Event event;
	  temps_actuel +=1;
	  /* look for an event; possibly update the position and the shape
	   * of the sprite. */
	  if (SDL_PollEvent(&event)) {
	    HandleEvent(event, &gameover, &space_ship, &accel, big_ast, norm_ast,
			small_ast, tirs, explosion, &play, score_total,
			&bomb_triggered);
	    HandleEvent2(event, &space_ship, &accel, &gameover, Table_move, tirs, &can_piou);
	  }
      
	  kill_all_sprite(&space_ship, big_ast, norm_ast,
			  small_ast, tirs, &gameover, &animationFinale, 
			  &bomb_triggered);
	  //Si le vaisseau a plus de vie ça tue
	  	  
	  /*Call new ast and bonus */
	  CreateAstWithTime(big_ast, norm_ast, small_ast);
	  CreateBonusWithTime(&bonus_atomic_bomb, &mitraille, portal);
 

	  /* draw the background */
	  SDL_BlitSurface(background, NULL, screen, NULL);
      


	  /*draw portal:*/
	  for (i=0 ; i<nbPortal; i++){
	  sprite_move(&portal[i]);
	  SDL_BlitSurface(portal[i].sprite_picture, &portal[i].image, screen, &portal[i].position);
	  }

	  {
	    /*position, mouvement et acceleration des sprites*/
	    sprite_boost(&space_ship, accel);
	    sprite_move(&space_ship);

	    SDL_BlitSurface(space_ship.sprite_picture, &space_ship.image, screen, &space_ship.position);
	  }
	  /*Affichage des bonus:*/
	  /*Atomic_bomb*/
	  if(gimmeIsNb(&bonus_atomic_bomb) == 1){
	  SDL_BlitSurface(bonus_atomic_bomb.sprite_picture,
			  NULL, screen, &bonus_atomic_bomb.position);
	  }
	  if(nbMitraille > 0)
	    {
	      SDL_BlitSurface(mitraille.sprite_picture, NULL, screen, &mitraille.position);
	      //printf(" position mitraille : x: %d y: %d\n",mitraille.position.x, mitraille.position.y);
	    }
	  /*draw Big Asteroid*/
	  move_all_sprite(big_ast);
	  draw_all_sprite(big_comet,big_ast);	  

	  /*draw norm asteroid*/
	  move_all_sprite(norm_ast);
	  draw_all_sprite(norm_comet, norm_ast);

	  /*draw small asteroid*/
	  move_all_sprite(small_ast);
	  draw_all_sprite(small_comet, small_ast);	  

	  /*Draw EXPLOSION*/ 
	  move_all_sprite(explosion);
	  draw_all_sprite(explosion_picture, explosion);
	  for (i=0; i<nbExplosion; i++){
	    if (nbExplosion>0){
	      if (explosion[i].decompte >= 100*12+1){
		explosion[i].decompte = 0;
		kill_ast(explosion, i);
	      }
	    }
	  }
      
	  /*Draw projectile (piou)*/
	  for (i=0; i<nbtirs; i++) {
	    if (nbtirs>0){
	      sprite_move(&tirs[i]);
	      if (tirs[i].decompte > PORTEE_PIOU){
		tirs[i].life -= 1;
		tirs[i].decompte = 0;
	      }
	      SDL_BlitSurface(bullet, NULL , screen, &tirs[i].position);
	    }
	  }
  /*Draw PV*/
	  for (i = 0; i<space_ship.life ; i++)
	    {
	      SDL_BlitSurface(vie, NULL, screen, &PV[i].position);
	    }
	  /*Collision*/
	  if (cogne == false)
	    {
	      collide(&space_ship, tirs, big_ast, norm_ast, small_ast, &gameover,
		      &cogne, &decompte, &bonus_atomic_bomb, &bomb_triggered, &have_mitraille, &mitraille, portal);
	      dead(&space_ship, big_ast, norm_ast, small_ast, tirs, explosion,
		   &gameover, score_total, &droitDeScorer);
	    }
	  else
	    {
	      decompte--;
	      change_sprite_ship(&space_ship, spaceship, spaceship2);
	      can_piou = false;
	      if (decompte <1)
		{
		  cogne = false;
		}
	    }
	  Effect_mitraille();
	  sprintf(affichage_score, "Score : %d", *score_total);
	  SDL_Surface *textSurface = TTF_RenderUTF8_Solid(font, affichage_score,
						  color);
	  SDL_BlitSurface(textSurface, NULL, screen, NULL);
	  SDL_FreeSurface(textSurface);


	  /* update the screen */
	  SDL_UpdateRect(screen, 0, 0, 0, 0);
	  /*End of while of the game */
	}
       
      ending = 0; //debut d'ecran de gameover
      /*End of if(play)*/
    }
    if(gameover){
      play = false;
      space_ship.life = MAX_LIFE_SHIP;
      SetUpPosition(&space_ship);
      kill_all_number();
      temps_actuel = 0;
      printf("Commandant ! voici votre score : %d \n", *score_total);
      *score_total = 0;
      droitDeScorer = true;

      while(!ending){
	
	      /*Insert function of menu here (blitsurface...)*/
	
	SDL_Event event3;
	if (SDL_PollEvent(&event3)) {
	  HandleEventMenu(event3, &gameover, &play, &ending, &finmenu, &jouer, &quitter);
	}
	SDL_BlitSurface(background, NULL, screen, NULL);
	SDL_BlitSurface(jouer.sprite_picture, NULL, screen, &jouer.position);
	SDL_BlitSurface(quitter.sprite_picture, NULL, screen, &quitter.position);
	SDL_BlitSurface(game_over.sprite_picture, NULL, screen, &game_over.position);
	SDL_UpdateRect(screen, 0, 0, 0, 0);
      }
    }
    /*End of while menu*/
  }
   
  /* clean up */
  SDL_FreeSurface(portal_picture);
  SDL_FreeSurface(textSurface);
  SDL_FreeSurface(menu_jouer);
  SDL_FreeSurface(menu_jouer_selec);
  SDL_FreeSurface(menu_quitter);
  SDL_FreeSurface(menu_quitter_selec);
  SDL_FreeSurface(menu_return);
  SDL_FreeSurface(menu_game_over);
  SDL_FreeSurface(vie);
  SDL_FreeSurface(bullet);
  SDL_FreeSurface(small_comet);
  SDL_FreeSurface(norm_comet);
  SDL_FreeSurface(big_comet);
  SDL_FreeSurface(spaceship);
  SDL_FreeSurface(spaceship2);
  SDL_FreeSurface(background);
  SDL_FreeSurface(screen);

  /* Free the font. */
  TTF_CloseFont(font);

  /* Cleanup SDL and SDL_ttf. */
  SDL_Quit();
  TTF_Quit();

  return 0;
  
}

/*Appelle sprite move pour chacun des sprites du tableau de sprite envoyé (ne fonctionne que pour des tableau)*/
void move_all_sprite(sprite_t *sprite)
{
  int i;
  int nb_sprite = gimmeIsNb(sprite);
  for (i=0; i<nb_sprite; i++){
    if (nb_sprite>0){
      sprite_move(&sprite[i]);
    }
  }
}
/*Appelle SDL_BlitSurface pour chacun des sprites du tableau de sprite envoyé (ne fonctionne que pour des tableau)*/
void draw_all_sprite(SDL_Surface *picture, sprite_t *sprite)
{
  int i;
  int nb_sprite = gimmeIsNb(sprite);
  for (i=0; i<nb_sprite; i++){
    if (nb_sprite>0){
      SDL_BlitSurface(picture, &sprite[i].image, screen, &sprite[i].position);
    }
  }
}