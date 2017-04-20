#include "physique.h"


/*Create comet size 64*64,*/
void CreateBigAst(sprite_t *big_ast,SDL_Surface *big_comet, int *nbBigAst )
{
  //int nbBigAst;
  //nbBigAst = big_ast;
  // int nombre_test;
  if (*nbBigAst < NB_MAX_BIG_AST){
    sprite_init(&big_ast[*nbBigAst], 1, big_comet, BIG_AST_SIZE, NB_BIG_AST_SPRITE);
    sprite_boost(&big_ast[*nbBigAst], VIT_BIG_AST);
    *nbBigAst += 1;
    // nombre_test = big_ast[*nbBigAst]->nb_sprite;
  }
}

/*Kill asteroid*/
void kill(int *nb)
{
  if (*nb>0){
    *nb -= 1;
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
		 int *quit, sprite_t *sprite, double *accel, sprite_t *big_ast, SDL_Surface *big_comet, int *nbBigAst)
{
 
  switch (event.type) {
    /* close button clicked */
  case SDL_QUIT:
    *quit = 1;
    break;
    
    /* handle the keyboard + Create_Big_Comet*/
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_ESCAPE:
    case SDLK_q:
      *quit = 1;
      break;
    case SDLK_LEFT:
      sprite_turn_left(sprite);
      break;
    case SDLK_RIGHT:
      sprite_turn_right(sprite);
      break;
    case SDLK_UP:
      *accel = CONS_ACCEL;
      break;
    case SDLK_DOWN:
      break;
    case SDLK_o:
      printf("Touch o pressed\n");
      CreateBigAst(big_ast, big_comet, nbBigAst);
      SDL_Delay(100); //delai de 100 ms pour pas faire ooooooooooo
      break;
    case SDLK_p:
      printf("Touch p pressed \n");
      kill(nbBigAst);
      SDL_Delay(100);
      break;
    default:
      break;
    }
    break;
  }

}

int main(int argc, char* argv[])
{
  
  int colorkey;
  int nbBigAst = 0;
  sprite_t space_ship;
  sprite_t big_ast[NB_MAX_BIG_AST];
  //sprite_t norm_ast[NB_MAX_NORM_AST];
  //sprite_t small_ast[NB_MAX_SMALL_AST]; 


  
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
  sprite_init(&space_ship,0,spaceship,SPRITE_SIZE,NB_SPRITE);


  int gameover = 0;
  /* Define the float position of the ship */
  
  /* main loop: check events and re-draw the window until the end */
  while (!gameover)
    {
      int i;
      double accel=0.0;
      SDL_Event event;
      
      /* look for an event; possibly update the position and the shape
       * of the sprite. */
      if (SDL_PollEvent(&event)) {
	HandleEvent(event, &gameover, &space_ship, &accel, big_ast, big_comet, &nbBigAst);
      }


      /* draw the background */
      SDL_BlitSurface(background, NULL, screen, NULL);
      
      
      
      /* Draw the selected image of the sprite at the right position */
      {
	/*position, mouvement et acceleration des sprites*/
	sprite_boost(&space_ship, accel);
	sprite_move(&space_ship);
	/* Define the source rectangle for the BlitSurface */
	SDL_Rect spriteImage;
	spriteImage.y = 0;
	spriteImage.w = space_ship.size;
	spriteImage.h = space_ship.size;
	/* choose image according to direction and animation flip: */
	spriteImage.x = space_ship.size * space_ship.current;
	
	SDL_BlitSurface(spaceship, &spriteImage, screen, &space_ship.position);
      }

      /*draw Asteroid*/
      for (i=0; i<nbBigAst; i++){
	if (nbBigAst>0){
	  sprite_move(&big_ast[i]);
	  SDL_BlitSurface(big_comet, NULL, screen, &big_ast[i].position);
	  // printf("i = %d \n",i );
	}
	}
      /* update the screen */
      SDL_UpdateRect(screen, 0, 0, 0, 0); 
    }
  
  /* clean up */
  //SDL_FreeSurface(screen);
  SDL_FreeSurface(big_comet);
  SDL_FreeSurface(spaceship);
  SDL_FreeSurface(background);
  SDL_FreeSurface(screen);
  SDL_Quit();
  
  return 0;
}
