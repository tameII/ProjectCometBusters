#ifndef PHYSIQUE_H
#define PHYSIQUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <math.h>
#include <time.h>


#define FROTTEMENT   0.0009

/* Size of the window */
#define SCREEN_WIDTH    640
#define SCREEN_HEIGHT   480

/* In the sprite, we have 36 images of a 32x32 picture */
#define NB_SPACE_SHIP_SPRITE       36

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
#define VIT_MAX 4.7

/* Size of ship: */
#define SPACE_SHIP_SIZE     32
#define NB_MAX_SHIP         1
/* Size of projectiles */
#define PROJECT_SIZE    8

/* Size and number of asteroids */
//#define BIG_AST_TYPE    1
#define BIG_AST_SIZE    64
#define NB_MAX_BIG_AST      5
#define VIT_BIG_AST     0.02
/*Norm ast:*/
#define NORM_AST_SIZE   32
#define NB_MAX_NORM_AST     7
#define VIT_NORM_AST    0.05
/*Small ast:*/
#define SMALL_AST_SIZE  16
#define NB_MAX_SMALL_AST    10
#define VIT_SMALL_AST   0.1
/*Number of type of asteroid => big, norm, small at this moment*/
#define NB_TYPE_AST 3
/*in the ast we have 32 pictures*/
#define NB_AST_SPRITE 32

SDL_Surface *screen, *temp, *spaceship, *big_comet, *norm_comet, *small_comet, *background;
int *nbBigAst, *nbNormAst, *nbSmallAst;
bool *Random_Position_activated; //the function is activated?
int *temps_actuel; 

struct Sprite_t{
  int type;
  int col;
  int lig;
  double x;
  double y;
  int current;
  int size;
  int nb_sprite;
  int decompte;
  int numero_object; //number of the present object
  int nombre_max;
  double vx;
  double vy;
  SDL_Rect position;
  SDL_Rect image;
};

typedef struct Sprite_t sprite_t;



void SetUpPosition(sprite_t *sprite, SDL_Surface *surface);
void Random_Position (sprite_t *sprite);
void Random_Direction(sprite_t *sprite, float vitesse);

void sprite_init(sprite_t *sprite, int type, SDL_Surface * sprite_picture, int sprite_size, int anim_sprite_num, int nombre_max_sprite);
void sprite_turn_left(sprite_t *sprite);
void sprite_turn_right(sprite_t *sprite);
void sprite_move(sprite_t *sprite); 
void sprite_boost(sprite_t *sprite, float accel);
void hyperespace(sprite_t *sprite);

SDL_Surface* download_sprite_(char *nomSprite);
void downloadsprite(int *colorkey);

#endif
