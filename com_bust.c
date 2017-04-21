#include "physique.h"


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


/*Kill, The cursor on the tab recule*/
void kill(int *nb)
{
  if (*nb>0){
    *nb -= 1;
    }
  
}
/*Kill the ast[numero], need to Init the bool at false at begun.*/
void kill_ast(sprite_t *ast, int numero, bool killed)
{

  /*No need of more object than 100 on screen*/
  if (ast->nombre_max > 100){
    printf("kill_ast :nombre_max is overrated");
    killed = true;
  }
  if (numero < 0){
    printf("kill_ast : aaaw man, seriously ?  \n");
    killed = true;
  }
  if (numero > (ast->nombre_max-1)){
    printf("Number asked is overated, max is: %d",ast->nombre_max-1);
    killed = true;
  }
  if (numero == (ast->nombre_max-1) || numero == 0){
    switch (ast->type){
    case 1:
      kill(nbBigAst);
      break;
    case 2:
      kill(nbNormAst);
      break;
    case 3:
      kill(nbSmallAst);
      break;
    }
    killed = true;
  }
  if (killed == false){
    ast[numero] = ast[(numero+1)];
    kill_ast(ast, (numero+1), false);
  }
}

void CreateAst(sprite_t *big_ast, sprite_t *norm_ast, sprite_t *small_ast)
{
      if (*temps_actuel%11000 == 0){
	//printf("temps actuel = %d \n",*temps_actuel);
	//printf("CreateAst : Create new big ast \n");
	CreateBigAst(big_ast);
      }
      if (*temps_actuel%7000 == 0){
	//printf("temps actuel = %d \n",*temps_actuel);
	//printf("CreateAst : Create new norm ast \n");
	CreateNormAst(norm_ast);
      }
      if(*temps_actuel%4000 == 0){
	//printf("temps actuel = %d \n",*temps_actuel);
	//printf("CreateAst : Create new small ast \n");
	CreateSmallAst(small_ast);
      }

}

/////////////////////////////////////////////////////////////////
/* Handle events coming from the user:
   - quit the game?
   - use left/right to change the orientation of the ship
   - use up to move on the ship to the right direction
   - down is not defined right now
   -o o to create a new big asteroide
*/
void HandleEvent(SDL_Event event,
		 int *quit, sprite_t *space_ship, double *accel, sprite_t *big_ast, sprite_t *norm_ast, sprite_t *small_ast)
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
    case SDLK_k:
      printf("touch k pressed \n");
      srand(time(NULL));
      i = rand()%(3);
      if (i == 0){
	j = rand()%(NB_MAX_BIG_AST-1);
	kill_ast(big_ast, j, false);
      }
      if (i == 1){
	j = rand()%(NB_MAX_NORM_AST);
	kill_ast(norm_ast, j, false);
      }
      if (i == 2){
	j = rand()%(NB_MAX_SMALL_AST);
	kill_ast(small_ast, j, false);
      }
      printf("i : %d, j : %d \n",i,j);
      SDL_Delay(100);
      break;
    case SDLK_u:
      printf("touch u pressed \n");
      CreateSmallAst(small_ast);
      SDL_Delay(100);
      break;
    case SDLK_i:
      printf("Touch i pressed \n");
      CreateNormAst(norm_ast);
      SDL_Delay(100);
      break;
    case SDLK_o:
      printf("Touch o pressed\n");
      CreateBigAst(big_ast);
      SDL_Delay(100); //delai de 100 ms pour pas faire ooooooooooo
      break;
    case SDLK_p:
      printf("Touch p pressed \n");
      kill(nbBigAst);
      kill(nbNormAst);
      kill(nbSmallAst);
      SDL_Delay(100);
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
  /*timer du temps passé depuis l'activation de sdl avec SDL_GetTicks()*/
  int tempsActuel = 0;
  temps_actuel = &tempsActuel;
  
  /*permet de ne pas poper les astéroide au meme endroit a peu près quand on appuie longtemps*/
  bool Random_PositionActivated;
  Random_Position_activated = &Random_PositionActivated;
  int colorkey;
  int nombreBigAst = 0, nombreNormAst = 0, nombreSmallAst = 0;
  nbBigAst = &nombreBigAst; /*pointeur général*/
  nbNormAst = &nombreNormAst;
  nbSmallAst = &nombreSmallAst;
  /*Definition des différents sprites*/
  sprite_t space_ship;
  sprite_t big_ast[NB_MAX_BIG_AST];
  sprite_t norm_ast[NB_MAX_NORM_AST];
  sprite_t small_ast[NB_MAX_SMALL_AST]; 


  
  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);
  
  /* set the title bar */
  SDL_WM_SetCaption("Comet Buster", "Comet Buster");
  
  /* create window */
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  
  /* set keyboard repeat */
  SDL_EnableKeyRepeat(10, 10);

  /*Download pictures of all sprites*/
  downloadsprite(&colorkey);
 
  /*set up position of ship*/
  sprite_init(&space_ship, 0, spaceship, SPACE_SHIP_SIZE, NB_SPACE_SHIP_SPRITE, NB_MAX_SHIP);
  
  /*Init all ast at begun*/
  sprite_init(&big_ast[*nbBigAst], 1, big_comet, BIG_AST_SIZE, NB_AST_SPRITE, NB_MAX_BIG_AST);
  sprite_init(&small_ast[*nbSmallAst], 3, small_comet, SMALL_AST_SIZE, NB_AST_SPRITE, NB_MAX_SMALL_AST);
  sprite_init(&norm_ast[*nbNormAst], 2, norm_comet, NORM_AST_SIZE, NB_AST_SPRITE, NB_MAX_NORM_AST);

  
  int gameover = 0;
  
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
	HandleEvent(event, &gameover, &space_ship, &accel, big_ast, norm_ast, small_ast);
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
      CreateAst(big_ast, norm_ast, small_ast);

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
