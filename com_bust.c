#include "physique.h"
 
bool CreateExplosion(sprite_t *explosion, sprite_t *sprite);
bool compare_position_param(int x1, int y1, int a1, int x2, int y2, int a2);
bool compare_position(sprite_t *sprite1, sprite_t *sprite2);
void kill_ast(sprite_t *ast, int numero);
void draw_sprite(SDL_Surface *picture,sprite_t *sprite, int nb_sprite);
void move_all_sprite(sprite_t *sprite, int nb_sprite);
//void collide_param(sprite_t *sprite1, int nbSprite1,  sprite_t *sprite2, int nbSprite2);
void collide(sprite_t *tirs, sprite_t *big_ast, sprite_t *norm_ast, sprite_t *small_ast);
void DivideAst(sprite_t *ast, sprite_t *big_ast, sprite_t *norm_ast, sprite_t *small_ast);
////////////////////////////////////////////////////////////////////////////////////////////////
/******************************FIN HEADER******************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////
/*void explosion()
{
  sprite_t explosion;
  sprite_init(&explosion,  5, explosion_picture, EXPLOSION_SIZE, ANIM_EXPLOSION_NUM, NB_MAX_EXPLOSION);
  sprite_move(&explosion);
  draw_sprite(explosion_picture, &explosion, 1);
  if (explosion.decompte >= 100*12+1){
    //explosionNeeded = false;
    explosion.decompte = 0;
  }
}*/
void collide_param(sprite_t *sprite1, int nbSprite1,  sprite_t *sprite2, int nbSprite2, sprite_t *tirs, sprite_t *big_ast, sprite_t *norm_ast, sprite_t *small_ast)
{
  int i, j;
  
  if(nbSprite1>0 && nbSprite2>0){
    for(i=0; i<nbSprite1; i++){  
      for(j=0; j<nbSprite2; j++){
	if(compare_position(&sprite1[i], &sprite2[j])){
	   DivideAst(sprite1, big_ast, norm_ast, small_ast);
	   DivideAst(sprite2, big_ast, norm_ast, small_ast);
	  // kill_ast(sprite1, i);
	  // kill_ast(sprite2, j);
	    }
      }
    }
  }
}
void collide(sprite_t *tirs, sprite_t *big_ast, sprite_t *norm_ast, sprite_t *small_ast)
{
  collide_param(tirs, nbtirs, big_ast, nbBigAst, tirs, big_ast, norm_ast, small_ast);
  collide_param(tirs, nbtirs, norm_ast, nbNormAst, tirs, big_ast, norm_ast, small_ast);
  collide_param(tirs, nbtirs, small_ast, nbSmallAst, tirs, big_ast, norm_ast, small_ast);
}

bool compare_position(sprite_t *sprite1, sprite_t *sprite2)
{
  bool collision = false;
  collision = compare_position_param(sprite1->col, sprite1->lig, sprite1->size, sprite2->col, sprite2->lig, sprite2->size);
  return collision;
}
/*Fonction Collision pour un carré*/
bool compare_position_param(int x1, int y1, int a1, int x2, int y2, int a2)
{
  bool collision = false;
  if(min(x1+a1, x2+a2)>max(x1, x2) && min(y1+a1, y2+a2)>max(y1, y2)){
    //rintf("BOOM \n");
      collision = true;
  }
  return collision;
}


/*Create Small Ast*/
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
int gimmeIsNb(sprite_t *ast)
{
  int type = ast->type;
  
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
  default:
    printf("gimmeIsNB : Error : ask type 0, 1, 2, 3, 4. \n type asked :%d \n",type);
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
  if (nbAst > 0){
  nbAst -= 1;
  }
  killed = kill_ast_param(nombre_max, numero);
 
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

/*Fonction qui divise l'astéroide demandé en deux plus petit. (pour l'instant)*/
void DivideAst(sprite_t *ast, sprite_t *big_ast, sprite_t *norm_ast, sprite_t *small_ast)
{
  int numero = ast->numero_object; 
  int type = ast->type;
  int nb_Big_Ast = nbBigAst;
  int nb_Norm_Ast = nbNormAst;
  int nb_Small_Ast = nbSmallAst;
 
  //printf("Divide Ast : numero = %d \n",numero);

  /*Si on demande gros Ast, et il y en a 1 :  * 
   * Alors on créé un Norm Ast qu'on place    * 
   *à la pos du gros.                         *
   *Si  on demande norm Ast, et il y en a 1 : *
   *Alors on créé un Small Ast qu'on place    *
   *à la pos du normal.                       */
 
  if(type == 1 && nb_Big_Ast > 0){  
    CreateNormAst(norm_ast);                                             //Créé un norm ast
    SetUpAtPosition(&norm_ast[nb_Norm_Ast], ast);                        //Met le premier norm ast a la position du gros ast.
    if (nb_Norm_Ast+1 < NB_MAX_NORM_AST){                                //Si on peut créer un second norm ast.
      CreateNormAst(norm_ast);                                           //Créé un norm ast
      SetUpAtPosition(&norm_ast[nb_Norm_Ast+1], ast);                    //Met le second norm ast a la pos du gros ast.
      InvertDirection(&norm_ast[nb_Norm_Ast], &norm_ast[nb_Norm_Ast+1]); //lance les deux ast dans une direction opposée
    }
    kill_ast(ast, numero); //tue l'"ast".
  }
  if(type == 2 && nb_Norm_Ast > 0){                                      //Pareil mais pour un norm ast.
    //printf("DivideAst : type 2, createsmallAst");
    CreateAst(small_ast);
    SetUpAtPosition(&small_ast[nb_Small_Ast], ast);
    if (nb_Small_Ast+1 < NB_MAX_SMALL_AST){
      CreateAst(small_ast);
      SetUpAtPosition(&small_ast[nb_Small_Ast+1], ast);
      InvertDirection(&small_ast[nb_Small_Ast], &small_ast[nb_Small_Ast+1]);
    }
    kill_ast(ast, numero);
  }
  if (type != 1 && type != 2){                                          //une sécurité (et une tentative pour généraliser cette fonction)
    kill_ast(ast, numero);                                              //Je devrais plutot appeler divide dans kill m'enfin bref
  }
}
/*Créé un astéroide a l'aide de la variable globale temps actuel*/
void CreateAstWithTime(sprite_t *big_ast, sprite_t *norm_ast, sprite_t *small_ast)
{
  if (temps_actuel%11000 == 0){                       //toute les 11000 tours de boucle un Gros Ast apparait
    //printf("temps actuel = %d \n",*temps_actuel);    //des printf pour avoir une idée de tout les cb de temps
    //printf("CreateAst : Create new big ast \n");     //
    CreateBigAst(big_ast);                             //
  }
  if (temps_actuel%7000 == 0){                        //toute les 7000 tours de boucle  un Norm Ast apparait
    //printf("temps actuel = %d \n",*temps_actuel);    //
    //printf("CreateAst : Create new norm ast \n");    //
    CreateNormAst(norm_ast);                           //
  }
  if(temps_actuel%4000 == 0){                         //toute les 4000 tours de boucle un Small Ast apparait
    //printf("temps actuel = %d \n",*temps_actuel);    //
    //printf("CreateAst : Create new small ast \n");   //
    CreateSmallAst(small_ast);                         //
  }

}


bool CreateExplosion(sprite_t *explosion, sprite_t *sprite)
{
  bool BOOOOOOOOOOM = true;
  SetUpAtPosition(explosion, sprite);
  
  return BOOOOOOOOOOM;
}

//creation of projectile
void create_piou (sprite_t* tirs, sprite_t* space_ship)
{
  if (nbtirs<NB_MAX_PIOU){
    sprite_init(&tirs[nbtirs], 4, bullet, PIOU_SIZE, 1, 1);
    tirs[nbtirs].current = space_ship->current;
    sprite_boost(&tirs[nbtirs], VIT_NORM_PIOU);
    SetUpAtPosition(&tirs[nbtirs], space_ship);
    //printf("Piou !\n");
    nbtirs += 1;
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
*/

  

void HandleEvent(SDL_Event event, int *quit, sprite_t *space_ship, double *accel, sprite_t *big_ast, sprite_t *norm_ast, sprite_t *small_ast, sprite_t *explosion, bool *explosionNeeded, sprite_t *tirs)
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
    case SDLK_LEFT:
      sprite_turn_left(space_ship);
      break;
    case SDLK_RIGHT:
      sprite_turn_right(space_ship);
      break;
    case SDLK_UP:
      *accel = CONS_ACCEL;
      break;
    case SDLK_DOWN:
      break;
    case SDLK_l:
      printf("touch l pressed \n");
      //DivideAst(&big_ast[0], big_ast, norm_ast, small_ast );
      DivideAst(&norm_ast[0], big_ast, norm_ast, small_ast);
      SDL_Delay(100);
      break;
    case SDLK_k:
      printf("touch k pressed \n");
      i = rand()%(3);
      /*  if (i == 0){
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
      printf("i : %d, j : %d \n",i,j);
      */
      kill_ast(small_ast, 0);
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
    case SDLK_p:
      // printf("Touch p pressed \n");
      kill(&nbBigAst);
      kill(&nbNormAst);
      kill(&nbSmallAst);
      kill(&nbtirs);
      //SDL_Delay(100);
      break;
    case SDLK_e:
      printf("touch e pressed \n");
      *explosionNeeded = CreateExplosion(explosion, &big_ast[0]);
      SDL_Delay(100);
      break;
    case SDLK_t:
      //printf("touch t pressed \n");
      create_piou(tirs,space_ship);
      SDL_Delay(250);
      break;
    case SDLK_y:
      CreateAst(big_ast);
      CreateAst(norm_ast);
      CreateAst(small_ast);
      break;
    default:
      break;
    }
    break;
  }

}

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
  /*Definition des différents sprites*/
  sprite_t space_ship;
  sprite_t big_ast[NB_MAX_BIG_AST];
  sprite_t norm_ast[NB_MAX_NORM_AST];
  sprite_t small_ast[NB_MAX_SMALL_AST]; 
  sprite_t explosion;
  sprite_t tirs[NB_MAX_PIOU];
  
  /*Initialize rand :*/
   srand(time(NULL)); 

  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);
  
  /* set the title bar */
  SDL_WM_SetCaption("Comet Buster", "Comet Buster");
  
  /* create window */
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  
  /* set keyboard repeat */
  SDL_EnableKeyRepeat(10, 10);

  /*Download pictures of all sprites*/
  downloadsprite();

  /*Initialise all sprite*/
  init_all_sprite(&space_ship, big_ast, norm_ast, small_ast);
  sprite_init(&explosion,  5, explosion_picture, EXPLOSION_SIZE, ANIM_EXPLOSION_NUM, NB_MAX_EXPLOSION);
  sprite_init(&tirs[nbtirs], 4, bullet, PIOU_SIZE, 1, 1);

  int gameover = 0;
  bool explosionNeeded = true;

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
	HandleEvent(event, &gameover, &space_ship, &accel, big_ast, norm_ast, small_ast, &explosion,  &explosionNeeded, tirs);
      }


      /* draw the background */
      SDL_BlitSurface(background, NULL, screen, NULL);
      
      
      {
	/*position, mouvement et acceleration des sprites*/
	sprite_boost(&space_ship, accel);
	sprite_move(&space_ship);

	SDL_BlitSurface(spaceship, &space_ship.image, screen, &space_ship.position);
      }
      
      /*Call new ast with time*/
      //CreateAstWithTime(big_ast, norm_ast, small_ast);

      /*draw Big Asteroid*/
      move_all_sprite(big_ast, nbBigAst);
      draw_sprite(big_comet,big_ast, nbBigAst);	  

      /*draw norm asteroid*/
      move_all_sprite(norm_ast, nbNormAst);
      draw_sprite(norm_comet, norm_ast, nbNormAst);

      /*draw small asteroid*/
      move_all_sprite(small_ast, nbSmallAst);
      draw_sprite(small_comet, small_ast, nbSmallAst);	  

      /*Draw EXPLOSION*/
       if (explosionNeeded == true){
	sprite_move(&explosion);
	draw_sprite(explosion_picture, &explosion, 1);
	if (explosion.decompte >= 100*12+1){
	  explosionNeeded = false;
	  explosion.decompte = 0;
	}
       }
      /*Draw projectile (piou)*/
      for (i=0; i<nbtirs; i++) {
	if (nbtirs>0){
	  sprite_move(&tirs[i]);
	  if (tirs[i].decompte > PORTEE_PIOU){
	    kill_ast(tirs, i);
	  }
	  SDL_BlitSurface(bullet, NULL , screen, &tirs[i].position);
	}
      }

      /*Collision*/
      collide(tirs, big_ast, norm_ast, small_ast);
  
      /* update the screen */
      SDL_UpdateRect(screen, 0, 0, 0, 0); 
    }
  
  /* clean up */
  SDL_FreeSurface(bullet);
  SDL_FreeSurface(small_comet);
  SDL_FreeSurface(norm_comet);
  SDL_FreeSurface(big_comet);
  SDL_FreeSurface(spaceship);
  SDL_FreeSurface(background);
  SDL_FreeSurface(screen);
  SDL_Quit();
  
  return 0;
  
}
/*Appelle sprite move pour chacun des sprites du tableau de sprite envoyé (ne fonctionne que pour des tableau)*/
void move_all_sprite(sprite_t *sprite, int nb_sprite)
{
  int i;
  for (i=0; i<nb_sprite; i++){
    if (nb_sprite>0){
      sprite_move(&sprite[i]);
    }
  }
}
/*Appelle SDL_BlitSurface pour chacun des sprites du tableau de sprite envoyé (ne fonctionne que pour des tableau)*/
void draw_sprite(SDL_Surface *picture, sprite_t *sprite, int nb_sprite)
{
  int i;
  for (i=0; i<nb_sprite; i++){
    if (nb_sprite>0){
      SDL_BlitSurface(picture, &sprite[i].image, screen, &sprite[i].position);
    }
  }
}
