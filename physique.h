#ifndef PHYSIQUE_H
#define PHYSIQUE_H

#define FROTTEMENT   0.001
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <math.h>
#include <time.h>

#define INIT_DIR 9
#define INIT_ROTATION 1

#define VIT_MAX 4.7

/* Size of the window */
#define SCREEN_WIDTH    640
#define SCREEN_HEIGHT   480

/* In the sprite, we have 36 images of a 32x32 picture */
#define NB_SPRITE       36

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

/* Size of ship: */
#define SPRITE_SIZE     32
/* Size of projectiles */
#define PROJECT_SIZE    8

/* Size and number of asteroids, je sais que c'est beaucoup pour l'instant :p */
#define BIG_AST_SIZE    64
#define NB_MAX_BIG_AST      5
#define VIT_BIG_AST     0.02

#define NORM_AST_SIZE   32
#define NB_MAX_NORM_AST     10
#define VIT_NORM_AST    0.05

#define SMALL_AST_SIZE  16
#define NB_MAX_SMALL_AST    20
#define VIT_SMALL_AST   0.1
/*in the ast, for now we have just 1 picture of 64*64*/
#define NB_BIG_AST_SPRITE 1



struct Sprite_t{
  int type;
  int col;
  int lig;
  double x;
  double y;
  int current;
  int size;
  int nb_sprite;
  double vx;
  double vy;
};

typedef struct Sprite_t sprite_t;

void SetUpPosition(sprite_t *sprite, SDL_Surface *surface);
void Random_Position (sprite_t *sprite, int size);
void Random_Direction(sprite_t *sprite, float vitesse);

void sprite_init(sprite_t *sprite, int type, SDL_Surface * sprite_picture, int sprite_size, int anim_sprite_num);
void sprite_turn_left(sprite_t *sprite);
void sprite_turn_right(sprite_t *sprite);
void sprite_move(sprite_t *sprite); 
void sprite_boost(sprite_t *sprite, float accel);



#endif
