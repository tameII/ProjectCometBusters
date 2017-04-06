#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>

#include "physique.h"

/* Size of the window */
#define SCREEN_WIDTH    640
#define SCREEN_HEIGHT   480

/* In the sprite, we have 36 images of a 32x32 picture */
#define NB_SPRITE       36

/* Size of ship: */
#define SPRITE_SIZE     32
/* Size of projectiles */
#define PROJECT_SIZE    8
/* Size and number of asteroids, je sais que c'est beaucoup pour l'instant :p */
#define BIG_AST_SIZE    64
#define NB_BIG_AST      5
#define VIT_BIG_AST     0.02

#define NORM_AST_SIZE   32
#define NB_NORM_AST     10
#define VIT_NORM_AST    0.05

#define SMALL_AST_SIZE  16
#define NB_SMALL_AST    20
#define VIT_SMALL_AST   0.1
/*in the ast, for now we have just 1 picture of 64*64*/
#define NB_BIG_AST_SPRITE 1

/* Nb of life at the start */
#define MAX_LIFE        5
/* Points added to the score */
#define BIG_AST_POINT   20
#define NORM_AST_POINT  50
#define SMALL_AST_POINT 100

/* Order of the different directions in the picture: */
#define INIT_DIR        9
#define ANGLE_DIR       10

/* Speed of ship */
#define CONS_ACCEL      0.01

/*Set Position of all Sprites*/
void SetUpPosition(sprite_t *sprite, SDL_Surface *surface, SDL_Rect *rectPosition){
  
  /* set sprite position in the middle of the window */
  switch(sprite->type) {
  case 1:
    Random_Position(rectPosition);
    surface->clip_rect.x = rectPosition->x;
    surface->clip_rect.y = rectPosition->y;
  default:
    rectPosition->x = (SCREEN_WIDTH - SPRITE_SIZE) / 2;
    surface->clip_rect.x = rectPosition->x;
    rectPosition->y = (SCREEN_HEIGHT - SPRITE_SIZE) / 2;
    surface->clip_rect.y = rectPosition->y;
    break;
  }
}

/*Create comet size 64*64*/
void CreateBigComet(sprite_t *big_ast,SDL_Surface *big_comet, SDL_Rect *bigCometPosition )
{
  SetUpPosition(big_ast, big_comet, bigCometPosition);
  sprite_init(big_ast, 1, big_comet, BIG_AST_SIZE, NB_BIG_AST_SPRITE);
  sprite_boost(big_ast, VIT_BIG_AST);
  
}

/////////////////////////////////////////////////////////////////
/* Handle events coming from the user:
   - quit the game?
   - use left/right to change the orientation of the ship
   - use up to move on the ship to the right direction
*/
void HandleEvent(SDL_Event event,
		 int *quit, sprite_t *sprite, double *accel, sprite_t *big_ast, SDL_Surface *big_comet, SDL_Rect *bigCometPosition, bool *thereisacomet)
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
      *thereisacomet = true;
      CreateBigComet(big_ast,big_comet, bigCometPosition);
      break;
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
  sprite_t space_ship;
  sprite_t big_ast;
  /* Information about the current situation of the ship: */
  
  /* Rectangle to store the position of the sprite in the window.
   * Only the x and y coordinates are used. */
  SDL_Rect spritePosition;
  SDL_Rect bigCometPosition;
  
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
  SetUpPosition(&space_ship, sprite, &spritePosition);
  sprite_init(&space_ship,0,sprite,SPRITE_SIZE,NB_SPRITE);

  /*no comet at begun*/
  bool thereisacomet = false;

  int gameover = 0;
  /* Define the float position of the ship */
  
  /* main loop: check events and re-draw the window until the end */
  while (!gameover)
    {
      double accel=0.0;
      SDL_Event event;
      
      /* look for an event; possibly update the position and the shape
       * of the sprite. */
      if (SDL_PollEvent(&event)) {
	HandleEvent(event, &gameover, &space_ship, &accel, &big_ast, big_comet, &bigCometPosition, &thereisacomet);
      }
      /*position, mouvement et acceleration des sprites*/
      sprite_boost(&space_ship, accel);
      sprite_move(&space_ship);

      spritePosition.x = space_ship.col;
      spritePosition.y = space_ship.lig;
  

      sprite_move(&big_ast);
      bigCometPosition.x = big_ast.col;
      bigCometPosition.y = big_ast.lig;
      
      /* draw the background */
      SDL_BlitSurface(background, NULL, screen, NULL);
      
      
      
      /* Draw the selected image of the sprite at the right position */
      {
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
      if (thereisacomet){
      SDL_BlitSurface(big_comet, NULL, screen, &bigCometPosition);
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
