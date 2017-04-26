#include "physique.h"

bool CreateExplosion(sprite_t *explosion, sprite_t *sprite);


/*Create Small Ast*/
void CreateSmallAst(sprite_t *small_ast)
{
  if(*nbSmallAst < NB_MAX_SMALL_AST){
    sprite_init(&small_ast[*nbSmallAst], 3, small_comet, SMALL_AST_SIZE, NB_AST_SPRITE, NB_MAX_SMALL_AST);
    sprite_boost(&small_ast[*nbSmallAst], VIT_SMALL_AST);
    *nbSmallAst += 1;
  }
  
}

/*Create Norm Ast*/
void CreateNormAst(sprite_t *norm_ast)
{
  if (*nbNormAst < NB_MAX_NORM_AST){
    sprite_init(&norm_ast[*nbNormAst], 2, norm_comet, NORM_AST_SIZE, NB_AST_SPRITE, NB_MAX_NORM_AST);
    sprite_boost(&norm_ast[*nbNormAst], VIT_NORM_AST);
    *nbNormAst += 1;
  }
  
}

/*Create comet size 64*64,*/
void CreateBigAst(sprite_t *big_ast)
{
 
  if (*nbBigAst < NB_MAX_BIG_AST){
    sprite_init(&big_ast[*nbBigAst], 1, big_comet, BIG_AST_SIZE, NB_AST_SPRITE, NB_MAX_BIG_AST);
    sprite_boost(&big_ast[*nbBigAst], VIT_BIG_AST);
    *nbBigAst += 1;
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
int gimmeIsNb(sprite_t *ast)
{
  int type = ast->type;
  
  switch (type){
  case 0:
    return 1;
    break;
  case 1:
    return *nbBigAst;
    break;
  case 2:
    return *nbNormAst;
    break;
  case 3:
    return *nbSmallAst;
    break;
  default:
    printf("gimmeIsNB : Error : ask type 0, 1, 2, 3. \n type asked :%d \n",type);
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
	kill(nbBigAst);
	killed = true;
	break;
      case 2:
	kill(nbNormAst);
	killed = true;
	break;
      case 3:
	kill(nbSmallAst);
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
void InvertDirection(sprite_t *sprite1, sprite_t *sprite2)
{
  sprite2->vx = -sprite1->vx;
  sprite2->vy = -sprite1->vy;
}

/*Set Up sprite 1 at position sprite 2 */
void SetUpAtPosition(sprite_t *sprite1, sprite_t *sprite2)
{
  sprite1->x = sprite2->x;
  sprite1->y = sprite2->y;
}
/*Fonction qui divise l'astéroide demandé en deux plus petit. (pour l'instant)*/
void DivideAst(sprite_t *ast, sprite_t *big_ast, sprite_t *norm_ast, sprite_t *small_ast, sprite_t *explosion, bool *explosionNeeded)
{
  int numero = ast->numero_object; 
  int type = ast->type;
  int nb_Big_Ast = *nbBigAst;
  int nb_Norm_Ast = *nbNormAst;
  int nb_Small_Ast = *nbSmallAst;
 
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
    if (nb_Norm_Ast+1 < NB_MAX_NORM_AST){                                //Si on peut créer un norm ast.
      CreateNormAst(norm_ast);                                           //Créé un norm ast
      SetUpAtPosition(&norm_ast[nb_Norm_Ast+1], ast);                    //Met le second norm ast a la pos du gros ast.
      InvertDirection(&norm_ast[nb_Norm_Ast], &norm_ast[nb_Norm_Ast+1]); //lance les deux ast dans une direction opposée
    }
    *explosionNeeded = CreateExplosion(explosion, ast);                  //Créé une explosion a la position "ast"
    kill_ast(ast, numero);                                               //tue l'"ast".
  }
  if(type == 2 && nb_Norm_Ast > 0){                                      //Pareil mais pour un norm ast.
    printf("DivideAst : type 2, createsmallAst");
    CreateAst(small_ast);
    SetUpAtPosition(&small_ast[nb_Small_Ast], ast);
    if (nb_Small_Ast+1 < NB_MAX_SMALL_AST){
      CreateAst(small_ast);
      SetUpAtPosition(&small_ast[nb_Small_Ast+1], ast);
      InvertDirection(&small_ast[nb_Small_Ast], &small_ast[nb_Small_Ast+1]);
    }
    *explosionNeeded = CreateExplosion(explosion, ast);
    kill_ast(ast, numero);
  }
}
/*Créé un astéroide a l'aide de la variable globale temps actuel*/
void CreateAstWithTime(sprite_t *big_ast, sprite_t *norm_ast, sprite_t *small_ast)
{
  if (*temps_actuel%11000 == 0){                       //toute les 11000 tours de boucle un Gros Ast apparait
    //printf("temps actuel = %d \n",*temps_actuel);    //des printf pour avoir une idée de tout les cb de temps
    //printf("CreateAst : Create new big ast \n");     //
    CreateBigAst(big_ast);                             //
  }
  if (*temps_actuel%7000 == 0){                        //toute les 7000 tours de boucle  un Norm Ast apparait
    //printf("temps actuel = %d \n",*temps_actuel);    //
    //printf("CreateAst : Create new norm ast \n");    //
    CreateNormAst(norm_ast);                           //
  }
  if(*temps_actuel%4000 == 0){                         //toute les 4000 tours de boucle un Small Ast apparait
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
*/
void HandleEvent(SDL_Event event,
		 int *quit, sprite_t *space_ship, double *accel, sprite_t *big_ast, sprite_t *norm_ast, sprite_t *small_ast, sprite_t *explosion, bool *explosionNeeded)
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
      DivideAst(&big_ast[1], big_ast, norm_ast, small_ast, explosion, explosionNeeded);
      DivideAst(&norm_ast[0], big_ast, norm_ast, small_ast, explosion, explosionNeeded);
      SDL_Delay(100);
      break;
    case SDLK_k:
      printf("touch k pressed \n");
      
      srand(time(NULL));
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
      printf("i : %d, j : %d \n",i,j);
      
      //kill_ast(big_ast, 0);
      SDL_Delay(100);
      break;
    case SDLK_u:
      printf("touch u pressed \n");
      CreateAst(small_ast);
      SDL_Delay(100);
      break;
    case SDLK_i:
      printf("Touch i pressed \n");
      CreateAst(norm_ast);
      SDL_Delay(100);
      break;
    case SDLK_o:
      printf("Touch o pressed\n");
      CreateAst(big_ast);
      SDL_Delay(100); //delai de 100 ms pour pas faire ooooooooooo
      break;
    case SDLK_p:
      printf("Touch p pressed \n");
      kill(nbBigAst);
      kill(nbNormAst);
      kill(nbSmallAst);
      SDL_Delay(100);
      break;
    case SDLK_e:
      printf("touch e pressed \n");
      *explosionNeeded = CreateExplosion(explosion, &big_ast[0]);
      SDL_Delay(10);
    default:
      break;
    }
    break;
  }

}

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
  /*timer du temps passé depuis l'activation de sdl avec SDL_GetTicks()*/
  int tempsActuel = 0;
  temps_actuel = &tempsActuel;
  
  /*permet de ne pas poper les astéroide au meme endroit a peu près quand on appuie longtemps*/
  bool Random_PositionActivated;
  Random_Position_activated = &Random_PositionActivated;

  int nombreBigAst = 0, nombreNormAst = 0, nombreSmallAst = 0;
  nbBigAst = &nombreBigAst; /*pointeur général*/
  nbNormAst = &nombreNormAst;
  nbSmallAst = &nombreSmallAst;
  /*Definition des différents sprites*/
  sprite_t space_ship;
  sprite_t big_ast[NB_MAX_BIG_AST];
  sprite_t norm_ast[NB_MAX_NORM_AST];
  sprite_t small_ast[NB_MAX_SMALL_AST]; 
  sprite_t explosion;

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

  int gameover = 0;
  bool explosionNeeded = true;
  /* main loop: check events and re-draw the window until the end */
  while (!gameover)
    {
      int i;
      double accel = 0.0;
      SDL_Event event;
      *temps_actuel +=1;
      /* look for an event; possibly update the position and the shape
       * of the sprite. */
      if (SDL_PollEvent(&event)) {
	HandleEvent(event, &gameover, &space_ship, &accel, big_ast, norm_ast, small_ast, &explosion,  &explosionNeeded);
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
      for (i=0; i<*nbBigAst; i++){
	if (*nbBigAst>0){
	  sprite_move(&big_ast[i]);
	  SDL_BlitSurface(big_comet, &big_ast[i].image, screen, &big_ast[i].position);
	  
	}
      }
      /*draw norm asteroid*/
      for (i=0; i<*nbNormAst; i++){
	if (*nbNormAst>0){
	  sprite_move(&norm_ast[i]);
	  SDL_BlitSurface(norm_comet, &norm_ast[i].image, screen, &norm_ast[i].position);
	}
      }

      /*draw small asteroid*/
      for (i=0; i<*nbSmallAst; i++){
	if (*nbSmallAst>0){
	  sprite_move(&small_ast[i]);
	  SDL_BlitSurface(small_comet, &small_ast[i].image, screen, &small_ast[i].position);	  
	}
      }

      /*Draw EXPLOSION*/
      if (explosionNeeded == true){
	sprite_move(&explosion);
	SDL_BlitSurface(explosion_picture, &explosion.image , screen, &explosion.position);
	if (explosion.decompte >= 100*12+1){
	  explosionNeeded = false;
	  explosion.decompte = 0;
	}
      }
      
      /* update the screen */
      SDL_UpdateRect(screen, 0, 0, 0, 0); 
    }
  
  /* clean up */
  SDL_FreeSurface(small_comet);
  SDL_FreeSurface(norm_comet);
  SDL_FreeSurface(big_comet);
  SDL_FreeSurface(spaceship);
  SDL_FreeSurface(background);
  SDL_FreeSurface(screen);
  SDL_Quit();
  
  return 0;
  
}
