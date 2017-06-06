/****************************/
/*      physique.h          */
/*Authors : Albin Parmentier*/
/*        : Mathieu Levy    */
/****************************/

#ifndef PHYSIQUE_H
#define PHYSIQUE_H 
      
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <SDL.h>
#include <SDL_ttf.h> 
#include <math.h>
#include <time.h> 
#include <unistd.h>
#include <string.h>
  
 

/* Size of the window */
#define SCREEN_WIDTH    1024
#define SCREEN_HEIGHT   761
 
/*Parametre fin du jeu*/
#define DECOMPTE_FIN 1200  //Adapté pour salle 310(1700 en normal)
/*Parametre Menu:*/
#define MENU_JOUER_SIZE 256  //256*128
#define PLACEMENT_MENU_JOUER_X 300
#define PLACEMENT_MENU_JOUER_Y 500
#define NB_MENU_JOUER_SPRITE 1
#define NB_MAX_MENU_JOUER 1

#define MENU_QUITTER_SIZE 256 //256*128 
#define PLACEMENT_MENU_QUITTER_X 300
#define PLACEMENT_MENU_QUITTER_Y 300
#define NB_MENU_QUITTER_SPRITE 1
#define NB_MAX_MENU_QUITTER  1

#define MENU_GAME_OVER_SIZE 256
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
#define MAX_LIFE_SHIP        4  

/*life affichage */
#define PV_SIZE 32
#define NB_PV_SPRITE 1

/* Size and number of asteroids */
#define VITESSE_DEFILEMENT_AST   80
#define BIG_AST_SIZE    64
#define NB_MAX_BIG_AST      20   //20
#define VIT_BIG_AST     0.04     //0.04
#define BIG_AST_LIFE    3
#define CHANCE_D_APPARITION_BIG_AST 500 //pour SALLE 310, normal : 800
/*Norm ast:*/
#define NORM_AST_SIZE   32
#define NB_MAX_NORM_AST     35    //35
#define VIT_NORM_AST    0.08     //0.08
#define NORM_AST_LIFE   2        //2
#define CHANCE_D_APPARITION_NORM_AST 2000
/*Small ast:*/
#define SMALL_AST_SIZE  16   
#define NB_MAX_SMALL_AST    50   //50
#define VIT_SMALL_AST   0.25      //0.2
#define SMALL_AST_LIFE  1        //1
#define CHANCE_D_APPARITION_SMALL_AST 1250 

/*Number of type of asteroid => big, norm, small at this moment*/
#define NB_TYPE_AST 3
/*in the ast we have 32 pictures*/
#define NB_AST_SPRITE 32
 
//////////
/*EXPLOSION:*/
#define VITESSE_DEFILEMENT_EXPLOSION  20   //pour SALLE 310, normal 70
#define DECOMPTE_MORT_EXPLOSION 200        //pour Salle 310, normal 850
#define EXPLOSION_SIZE     64
#define ANIM_EXPLOSION_NUM 12
#define NB_MAX_EXPL   120

/*Projectiles*/
#define NB_MAX_PIOU 20
#define PIOU_SIZE 8
#define VIT_NORM_PIOU 2   //2
#define PORTEE_PIOU 150   //150


/*BONUS:*/
/*Atomic_bomb*/
#define ATOMIC_BOMB_SIZE 32
#define NB_ATOMIC_BOMB_SPRITE 1
#define NB_MAX_ATOMIC_BOMB 1
#define CHANCE_D_APPARITION_ATOMIC_BOMBE 30000 

/*Mitraille*/
#define BONUS_MITRAILLE_SIZE 32
#define NB_BONUS_MITRAILLE_SPRITE 1
#define NB_MAX_BONUS_MITRAILLE 1
#define CHANCE_D_APPARITION_MITRAILLE 5000

/*Portal*/
#define VITESSE_DEFILEMENT_PORTAL 50
#define PORTAL_SIZE  64
#define NB_PORTAL_SPRITE  5 
#define NB_MAX_PORTAL     15
#define CHANCE_D_APPARITION_PORTAL 6666

/*Vrac:*/
#define DUREE_INV_APP_DEGATS 1000
#define FROTTEMENT   0.0009



SDL_Surface *screen, *temp;
SDL_Surface *background;
SDL_Surface *spaceship_picture, *spaceship2_picture, *tirs_picture, *PV_picture;
SDL_Surface *big_ast_picture, *norm_ast_picture, *small_ast_picture;
SDL_Surface *explosion_picture; 
SDL_Surface *menu_jouer_selec_picture, *menu_jouer_picture;
SDL_Surface *menu_quitter_picture, *menu_quitter_selec_picture;
SDL_Surface *menu_game_over_picture, *menu_return_picture;
SDL_Surface *atomic_bomb_picture, *bonus_mitraille_picture, *portal_picture;

int error_gimmeIsNb, nbVaisseau, nbBigAst, nbNormAst, nbSmallAst, nbtirs;
int nbExplosion, nbAtomicBomb, nbMitraille, nbPortal ;

bool cogne;
bool can_piou;
bool have_mitraille;

int bonus_compt;
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
  int numero_object; 
  int nombre_max;
  int life;
  double vx;
  double vy;
  SDL_Rect position;
  SDL_Rect image;
  SDL_Surface *sprite_picture;
};

typedef struct Sprite_t sprite_t;


/*physique.c*/
/*1 fonction donnant des info diverse*/
void various_information(sprite_t *space_ship, sprite_t *big_ast,
			 sprite_t *norm_ast, sprite_t *small_ast, 
			 int *score);

/*8 fonction de position et direction*/
void SetUpPosition(sprite_t *sprite);
void InvertDirection(sprite_t *sprite1, sprite_t *sprite2);
void SetUpAtPosition(sprite_t *sprite1, sprite_t *sprite2);
void SetUpAtMiddle(sprite_t *sprite1, sprite_t *sprite2);
void Set_up_PV(sprite_t *PV);
void Random_Position_Partout(sprite_t *sprite);
void Random_Position (sprite_t *sprite);
void Random_Direction(sprite_t *sprite, float vitesse);

/*2 fonctions d'initialisation*/
void init_all_sprite(sprite_t *space_ship, sprite_t *big_ast, sprite_t *norm_ast,
		     sprite_t *small_ast, sprite_t *tirs, sprite_t *explosion,
		     sprite_t *game_over, sprite_t *return_menu,sprite_t *jouer,
		     sprite_t *quitter, sprite_t *PV, sprite_t *portal);
void sprite_init(sprite_t *sprite, int type, SDL_Surface *sprite_picture,
		 int sprite_size, int anim_sprite_num, int nombre_max_sprite);

/*13 fonction de physique, dessin et decompte*/
void sprite_turn_left(sprite_t *sprite);
void sprite_turn_right(sprite_t *sprite);
void ship_turn_left(sprite_t *sprite);
void ship_turn_right(sprite_t *sprite);
void ship_image(sprite_t *sprite);
void sprite_image(sprite_t *sprite);
void sprite_move(sprite_t *sprite);
void decompte_and_destroy_sprite(sprite_t *sprite, int decompte_avant_mort);
void move_all_sprite(sprite_t *sprite);
void draw_all_sprite(sprite_t *sprite);
void draw_all_sprite_one_image(sprite_t *sprite);
void sprite_boost(sprite_t *sprite, float accel);
void hyperespace(sprite_t *sprite);

/*2 fonction permettant de charger un sprite*/
void set_colorkey_(SDL_Surface *sprite_picture, int R, int G, int B,
		   SDL_Surface *screen);
  SDL_Surface* download_sprite_(char *nomSprite);

/*1 fonction donnant le nombre de sprite demandé sur l'ecran*/
int* gimmeIsNb(sprite_t *sprite);

/*3 fonctions de mort de base*/
void kill_sprite_number(int *nb);
bool kill_sprite_param(int nombre_max, int numero, int type);
void kill_sprite(sprite_t *sprite, int numero);

/*4 fonction de calcul de collision*/
int max(int a, int b);
int min(int a, int b);
bool compare_position(sprite_t *sprite1, sprite_t *sprite2);
bool collide_test(sprite_t sprite1, sprite_t sprite2, SDL_PixelFormat* format,
		  int * cu, int * cv);

/***************************************************/


/*in com_bust.c*/
/*5 fonctions de musique.*/
void mixaudio(void * userdata, Uint8 * stream, int len);
void pause_and_close_audio();
int musique_param(SDL_AudioSpec *soundfile, SDL_AudioSpec *obtained,
		  SDL_AudioCVT *cvt );
int musique(char *titre, SDL_AudioSpec *desired, SDL_AudioSpec *obtained,
	    SDL_AudioSpec *soundfile, SDL_AudioCVT *cvt );
void init_musique(SDL_AudioSpec *desired, int freq, char *format, int channel,
		  int sample);

/*8 fonctions de Creations (CreateAst rassemble juste les 3 avant)*/
void CreatePortal(sprite_t *portal);
void CreateAtomicBomb(sprite_t *bonus_atomic_bomb);
void CreateMitraille(sprite_t *mitraille);
void CreateExplosion(sprite_t *explosion, sprite_t *sprite, int numero);
void CreateSmallAst(sprite_t *small_ast);
void CreateNormAst(sprite_t *norm_ast);
void CreateBigAst(sprite_t *big_ast) ;
void CreateAst(sprite_t *ast);
void create_piou (sprite_t* tirs, sprite_t* space_ship);

/*3 fonctions permettant de tout kill*/
void kill_all_sprite_param(sprite_t *sprite, int nb_max);
void kill_all_sprite(sprite_t *space_ship,sprite_t *big_ast, sprite_t *norm_ast,
		     sprite_t *small_ast, sprite_t *tirs, int *gameover,
		     int *animationFinale, bool *bomb_triggered);
void kill_all_number();

/*5 fonctions gérant la mort des sprites*/
void ajout_score(int *score, int point);
void score(int *score, int type);
void dead_ship_param(sprite_t *sprite, int  *gameover, int *score_total,
		     bool *droitDeScorer);
void dead_tab_param(sprite_t *sprite, sprite_t *big_ast, sprite_t *norm_ast,
		    sprite_t *small_ast, sprite_t *explosion, int *score_total,
		    bool *droitDeScorer);
void dead(sprite_t *space_ship, sprite_t *big_ast, sprite_t *norm_ast,
	  sprite_t *small_ast, sprite_t *tirs, sprite_t *explosion,
	  int *gameover, int *score_total, bool *droitDeScorer);

/*5 fonctions de collision (dont la tp)*/
void teleportation(sprite_t *sprite1, sprite_t *portal);
void collide_ship_bonus_param(sprite_t *sprite1,  sprite_t *sprite2,
			      bool *bomb_triggered, bool *have_mitraille);
void collide_ship_param(sprite_t *sprite1,  sprite_t *sprite2, bool *cogne,
			int *decompte);
void collide_tab_param(sprite_t *sprite1,  sprite_t *sprite2);
void collide(sprite_t *space_ship, sprite_t *tirs, sprite_t *big_ast,
	     sprite_t *norm_ast, sprite_t *small_ast, int *gameover,
	     bool *cogne, int *decompte, sprite_t *bonus_atomic_bomb,
	     bool *bomb_triggered, bool *have_mitraille, sprite_t *mitraille,
	     sprite_t *portal);

/*1 fonction de division d'astéroide*/
void DivideAst(sprite_t *ast, int numero, sprite_t *big_ast,
	       sprite_t *norm_ast, sprite_t *small_ast);

/*2 fonctions de création de sprite automatique*/
void CreateAstWithTime(sprite_t *big_ast, sprite_t *norm_ast,
		       sprite_t *small_ast);
void CreateBonusWithTime(sprite_t *bonus_atomic_bomb, sprite_t *mitraille,
			 sprite_t *portal);

/*1 fonction modifiant le sprite du ship*/
void change_sprite_ship (sprite_t *ship, SDL_Surface * spaceship,
			 SDL_Surface * spaceship2);

/*2 fonctions gérant le bonus Mitraille*/
void Get_Mitraille();
void Effect_mitraille();

/*4 Fonctions gérant les touches*/
void HandleEvent(SDL_Event event, int *quit, sprite_t *space_ship, double *accel,
		 sprite_t *big_ast, sprite_t *norm_ast, sprite_t *small_ast,
		 sprite_t *tirs, sprite_t *explosion, bool *play,
		 int *score_total, bool *bomb_triggered);
void HandleEvent2(SDL_Event event, sprite_t *space_ship, double *accel,
		  int *quit, int Table_move[5], sprite_t *tirs, bool *can_piou);
void HandleMenuReturn(sprite_t *jouer, sprite_t *quitter, bool *play,
		      int *gameover, int *ending, int *finmenu);
void HandleEventMenu(SDL_Event event, int *gameover, bool *play, int *ending,
		     int *finmenu, sprite_t *jouer, sprite_t *quitter);
/*1 fonction de chargement de sprite*/
void downloadsprite();


#endif
 
