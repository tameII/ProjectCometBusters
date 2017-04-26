#ifndef PHYSIQUE_H
#define PHYSIQUE_H

#define FROTEMENT   0.001

#include <SDL.h>
#include <math.h>
#include <time.h>

#define INIT_DIR 9
#define INIT_ROTATION 1
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define VIT_MAX 5
#define BIG_AST_SIZE    64

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


void Random_Position (SDL_Rect *Position);
void Random_Direction(sprite_t *sprite, float vitesse);

void sprite_init(sprite_t *sprite, int type, SDL_Surface * sprite_picture, int sprite_size, int anim_sprite_num);
void sprite_turn_left(sprite_t *sprite);
void sprite_turn_right(sprite_t *sprite);
void sprite_move(sprite_t *sprite); 
void sprite_boost(sprite_t *sprite, float accel);



#endif
