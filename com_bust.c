
#include "physique.h"


/*Create comet size 64*64*/
void CreateBigComet(sprite_t *big_ast,SDL_Surface *big_comet, int *nbBigAst )
{
  int numeroAst = *nbBigAst;
  if (*nbBigAst < NB_MAX_BIG_AST){
    sprite_init(&big_ast[numeroAst], 1, big_comet, BIG_AST_SIZE, NB_BIG_AST_SPRITE);
    SetUpPosition(&big_ast[numeroAst], big_comet);
    sprite_boost(&big_ast[numeroAst], VIT_BIG_AST);
    *nbBigAst += 1;
  }
}

/*Kil asteroid
void kill(int *nb)
{
  if (*nb>=0){
    *nb -= 1;
    }
}*/
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
      CreateBigComet(big_ast, big_comet, nbBigAst);
      break;
    case SDLK_p:
      kill(nbBigAst);
    default:
      break;
    }
    break;
  }
}

int main(int argc, char* argv[])
{
  SDL_Surface *screen, *temp, *sprite, *big_comet, *background;
  int colorkey;
  int nbBigAst = 0;
  sprite_t space_ship;
  sprite_t big_ast[NB_MAX_BIG_AST];
  /* Information about the current situation of the ship: */
  
  /* Rectangle to store the position of all the sprite in the window.
   * Only the x and y coordinates are used. (temp variable) */
  SDL_Rect spritePosition;

  
  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);
  
  /* set the title bar */
  SDL_WM_SetCaption("Comet Buster", "Comet Buster");
  
  /* create window */
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  
  /* set keyboard repeat */
  SDL_EnableKeyRepeat(10, 10);


  /*load Big Comet*/
  temp   = SDL_LoadBMP("meteore_64.bmp");
  big_comet  = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  /* setup comet colorkey and turn on RLE */
  colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
  SDL_SetColorKey(big_comet, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

   /* load sprite */
  temp   = SDL_LoadBMP("greenship-v1.bmp");
  sprite = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  /* setup sprite colorkey and turn on RLE */
  colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
  SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  
  /* load background */
  temp  = SDL_LoadBMP("backgroundlvl1.bmp");
  background = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
   
  /*set up position of ship*/
  sprite_init(&space_ship,0,sprite,SPRITE_SIZE,NB_SPRITE);
  SetUpPosition(&space_ship, sprite);
  

  int gameover = 0;
  /* Define the float position of the ship */
  
  /* main loop: check events and re-draw the window until the end */
  while (!gameover)
    {
      double accel=0.0;
      int i;
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
	spritePosition.x = space_ship.col;
	spritePosition.y = space_ship.lig;
 
	/* Define the source rectangle for the BlitSurface */
	SDL_Rect spriteImage;
	spriteImage.y = 0;
	spriteImage.w = space_ship.size;
	spriteImage.h = space_ship.size;
	/* choose image according to direction and animation flip: */
	spriteImage.x = space_ship.size * space_ship.current;
	
	SDL_BlitSurface(sprite, &spriteImage, screen, &spritePosition);
      }

      /*draw Asteroid*/
      

      for (i=0; i<nbBigAst; i++){
	if (nbBigAst>0){
	  sprite_move(&big_ast[i]);
	  spritePosition.x = big_ast[i].col;
	  spritePosition.y = big_ast[i].lig;
	  SDL_BlitSurface(big_comet, NULL, screen, &spritePosition);
	}
      }
      /* update the screen */
      SDL_UpdateRect(screen, 0, 0, 0, 0); 
    }
  
  /* clean up */
  SDL_FreeSurface(big_comet);
  SDL_FreeSurface(sprite);
  SDL_FreeSurface(background);
  SDL_Quit();
  
  return 0;
}
