#ifndef PHYSIQUE_H
#define PHYSIQUE_H 
  
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h> 
#include <math.h>
#include <time.h> 
   
 

/* Size of the window */
#define SCREEN_WIDTH    1024
#define SCREEN_HEIGHT   761

/*Parametre fin du jeu*/
#define DECOMPTE_FIN 2000
/*Parametre Menu:*/
#define MENU_JOUER_SIZE 425  //425*252
#define PLACEMENT_MENU_JOUER_X 420
#define PLACEMENT_MENU_JOUER_Y 550
#define NB_MENU_JOUER_SPRITE 1
#define NB_MAX_MENU_JOUER 1

#define MENU_QUITTER_SIZE 425 //425*252 aussi ?
#define PLACEMENT_MENU_QUITTER_X 420
#define PLACEMENT_MENU_QUITTER_Y 300
#define NB_MENU_QUITTER_SPRITE 1
#define NB_MAX_MENU_QUITTER  1

#define MENU_GAME_OVER_SIZE 425
#define NB_MENU_GAME_OVER_SPRITE 1
#define NB_MAX_MENU_GAME_OVER 1

#define MENU_RETURN_SIZE 960
#define NB_MENU_RETURN_SPRITE 1
#define NB_MAX_MENU_RETURN 1

/* Points added to the score */
#define BIG_AST_POINT   250   
#define NORM_AST_POINT  500
#define SMALL_AST_POINT 1225
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
#define MAX_LIFE_SHIP        2  

/* Size and number of asteroids */
#define BIG_AST_SIZE    64
#define NB_MAX_BIG_AST      15
#define VIT_BIG_AST     0.04     //0.02
#define BIG_AST_LIFE    4
/*Norm ast:*/
#define NORM_AST_SIZE   32
#define NB_MAX_NORM_AST     25    //15
#define VIT_NORM_AST    0.08     //0.05
#define NORM_AST_LIFE   2        //2
/*Small ast:*/
#define SMALL_AST_SIZE  16   
#define NB_MAX_SMALL_AST    45   //30
#define VIT_SMALL_AST   0.2      //0.1
#define SMALL_AST_LIFE  1        //1

/*Number of type of asteroid => big, norm, small at this moment*/
#define NB_TYPE_AST 3
/*in the ast we have 32 pictures*/
#define NB_AST_SPRITE 32
 
//////////
/*EXPLOSION:*/
#define EXPLOSION_SIZE     64
#define ANIM_EXPLOSION_NUM 12
#define NB_MAX_EXPL   100

/*Projectiles*/
#define NB_MAX_PIOU 10
#define PIOU_SIZE 8
#define VIT_NORM_PIOU 2   //2
#define PORTEE_PIOU 150   //150


/*BONUS:*/
/*Atomic_bomb*/
#define ATOMIC_BOMB_SIZE 32
#define NB_ATOMIC_BOMB_SPRITE 1
#define NB_MAX_ATOMIC_BOMB 1
#define CHANCE_D_APPARITION_ATOMIC_BOMBE 50000      //1 chance sur "donne le nombre ici" par tour de boucle

/*Vrac:*/
#define DUREE_INV_APP_DEGATS 10000
#define FROTTEMENT   0.0009


/*ATOMIC_BOMB_SIZE, 
		NB_ATOMIC_BOMB_SPRITE, NB_MAX_ATOMIC_BOMB*/




SDL_Surface *screen, *temp, *spaceship, *big_comet, *norm_comet, *small_comet, *background, *bullet, *spaceship2;
SDL_Surface *explosion_picture; //stocke l'image de l'explosion
SDL_Surface *vie; //NBRE DE VIE
SDL_Surface *menu_jouer_selec, *menu_jouer, *menu_quitter, *menu_quitter_selec; //menu
SDL_Surface *menu_game_over, *menu_return;
SDL_Surface *atomic_bomb_picture;
int nbBigAst, nbNormAst, nbSmallAst, nbtirs, nbExplosion, nbAtomicBomb;
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
void various_information(sprite_t *space_ship, sprite_t *big_ast, sprite_t *norm_ast,
			 sprite_t *small_ast, int *score);

void SetUpPosition(sprite_t *sprite); //, SDL_Surface *surface
void Random_Position_Partout(sprite_t *sprite);
void Random_Position (sprite_t *sprite);
void Random_Direction(sprite_t *sprite, float vitesse);

void init_all_sprite(sprite_t *space_ship, sprite_t *big_ast, sprite_t *norm_ast,
		     sprite_t *small_ast, sprite_t *tirs, sprite_t *explosion,
		     sprite_t *game_over, sprite_t *return_menu,
		     sprite_t *jouer, sprite_t *quitter);

void sprite_init(sprite_t *sprite, int type, SDL_Surface * sprite_picture,
		 int sprite_size, int anim_sprite_num, int nombre_max_sprite);

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

bool collide_test(sprite_t sprite1, sprite_t sprite2,
		  SDL_PixelFormat* format, int * cu, int * cv);



/*in com_bust.c*/
void CreateExplosion(sprite_t *explosion, sprite_t *sprite, int numero);
bool compare_position_param(int x1, int y1, int a1, int x2, int y2, int a2);
bool compare_position(sprite_t *sprite1, sprite_t *sprite2);
void kill_ast(sprite_t *ast, int numero);
void SetUpAtPosition(sprite_t *sprite1, sprite_t *sprite2);
void draw_all_sprite(SDL_Surface *picture,sprite_t *sprite);
void move_all_sprite(sprite_t *sprite);

void collide_ship_param(sprite_t *sprite1,  sprite_t *sprite2,
			bool *cogne, int *decompte);

void collide_tab_param(sprite_t *sprite1,  sprite_t *sprite2);

void collide(sprite_t *space_ship, sprite_t *tirs, sprite_t *big_ast,
	     sprite_t *norm_ast, sprite_t *small_ast, int *gameover,
	     bool *cogne, int *decompte, sprite_t *bonus_atomic_bomb,
	     bool *bomb_triggered);

void DivideAst(sprite_t *ast, int numero, sprite_t *big_ast,
	       sprite_t *norm_ast, sprite_t *small_ast);
int gimmeIsNb(sprite_t *sprite);


#endif
 
