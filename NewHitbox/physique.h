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
#define SCREEN_WIDTH    1024
#define SCREEN_HEIGHT   761

/* Points added to the score */
#define BIG_AST_POINT   20
#define NORM_AST_POINT  50
#define SMALL_AST_POINT 100
/*Base life for all sprite*/
#define BASE_LIFE       1
/* Order of the different directions in the picture: */
#define INIT_DIR        9
#define ANGLE_DIR       10

/* Speed of ship */
#define CONS_ACCEL      0.01
#define VIT_MAX 4.7

/* In the sprite, we have 36 images of a 32x32 picture */
#define NB_SPACE_SHIP_SPRITE       36
/* Size of ship: */
#define SPACE_SHIP_SIZE     32
#define NB_MAX_SHIP         1
/* Nb of life at the start */
#define MAX_LIFE_SHIP        15  //150 lol

/* Size and number of asteroids */
#define BIG_AST_SIZE    64
#define NB_MAX_BIG_AST      5
#define VIT_BIG_AST     0.02     //0.02
#define BIG_AST_LIFE    4
/*Norm ast:*/
#define NORM_AST_SIZE   32
#define NB_MAX_NORM_AST     15    //15
#define VIT_NORM_AST    0.05     //0.05
#define NORM_AST_LIFE   2        //2
/*Small ast:*/
#define SMALL_AST_SIZE  16   
#define NB_MAX_SMALL_AST    30   //30
#define VIT_SMALL_AST   0.1      //0.1
#define SMALL_AST_LIFE  1        //1

/*Number of type of asteroid => big, norm, small at this moment*/
#define NB_TYPE_AST 3
/*in the ast we have 32 pictures*/
#define NB_AST_SPRITE 32
 
//////////
/*EXPLOSION:*/
#define EXPLOSION_SIZE     64
#define ANIM_EXPLOSION_NUM 12
#define NB_MAX_EXPLOSION   1

/*Projectiles*/
#define NB_MAX_PIOU 10
#define PIOU_SIZE 8
#define VIT_NORM_PIOU 2   //2
#define PORTEE_PIOU 150   //150

#define DUREE_INV_APP_DEGATS 1000


SDL_Surface *screen, *temp, *spaceship, *big_comet, *norm_comet, *small_comet, *background, *bullet, *spaceship2;
SDL_Surface *explosion_picture; //stocke l'image de l'explosion 
int nbBigAst, nbNormAst, nbSmallAst, nbtirs;
bool Random_Position_activated; //the function is activated?
bool cogne;
int temps_actuel; 
int decompte;

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
  int life;
  double vx;
  double vy;
  SDL_Rect position;
  SDL_Rect image;
  SDL_Surface *sprite_picture;
};

typedef struct Sprite_t sprite_t;


/*in physique.c*/
void various_information(sprite_t *big_ast, sprite_t *norm_ast, sprite_t *small_ast);

void SetUpPosition(sprite_t *sprite); //, SDL_Surface *surface
void Random_Position (sprite_t *sprite);
void Random_Direction(sprite_t *sprite, float vitesse);

void init_all_sprite(sprite_t *space_ship, sprite_t *big_ast, sprite_t *norm_ast, sprite_t *small_ast, sprite_t *tirs);
void sprite_init(sprite_t *sprite, int type, SDL_Surface * sprite_picture, int sprite_size, int anim_sprite_num, int nombre_max_sprite);
void sprite_turn_left(sprite_t *sprite);
void sprite_turn_right(sprite_t *sprite);
void sprite_move(sprite_t *sprite); 
void sprite_boost(sprite_t *sprite, float accel);
void hyperespace(sprite_t *sprite);
void ship_turn_left(sprite_t *sprite);
void ship_turn_right(sprite_t *sprite);
void ship_image(sprite_t *sprite);

SDL_Surface* download_sprite_(char *nomSprite);
void downloadsprite();

bool kill_ast_param(int nombre_max, int numero, int type);

int max(int a, int b);
int min(int a, int b);

/*in com_bust.c*/
bool CreateExplosion(sprite_t *explosion, sprite_t *sprite);
bool compare_position_param(int x1, int y1, int a1, int x2, int y2, int a2);
bool compare_position(sprite_t *sprite1, sprite_t *sprite2);
void kill_ast(sprite_t *ast, int numero);
void draw_all_sprite(SDL_Surface *picture,sprite_t *sprite);
void move_all_sprite(sprite_t *sprite);
void collide_ship_param(sprite_t *sprite1,  sprite_t *sprite2, bool *cogne, int *decompte);
void collide_tab_param(sprite_t *sprite1,  sprite_t *sprite2);
void collide(sprite_t *ship, sprite_t *tirs, sprite_t *big_ast, sprite_t *norm_ast, sprite_t *small_ast, int *gameover, bool *cogne, int *decompte);
void DivideAst(sprite_t *ast, int numero, sprite_t *big_ast, sprite_t *norm_ast, sprite_t *small_ast);
int gimmeIsNb(sprite_t *sprite);

bool collide_test(sprite_t sprite1, sprite_t sprite2, SDL_PixelFormat* format, int * cu, int * cv);
#endif