#include "physique.h"

/*Give various information, press b in game to know what.*/
void various_information(sprite_t *big_ast, sprite_t *norm_ast, sprite_t *small_ast)
{
  int i;
  for(i=0;i<gimmeIsNb(big_ast);i++){
    printf("big_ast[%d].life = %d \n", i, big_ast[i].life);
  }
  printf("\n");
  for(i=0;i<gimmeIsNb(norm_ast);i++){
    printf("norm_ast[%d].life = %d \n", i, norm_ast[i].life);
  }
  printf("\n");
  for(i=0;i<gimmeIsNb(small_ast);i++){
    printf("small_ast[%d].life = %d \n", i, small_ast[i].life);
  }
  printf("\n");
  printf("nbBigAst: %d |nbNormAst: %d |nbSmallAst: %d |", nbBigAst, nbNormAst, nbSmallAst);
  printf("nbtirs: %d |temps_actuel: %d |\n", nbtirs, temps_actuel);
}

/*Set Position of all Sprites*/
void SetUpPosition(sprite_t *sprite){  //, SDL_Surface *surface) avant
  
  /* set sprite position in the middle of the window */
  switch(sprite->type) {
  case 0:
    sprite->x = (SCREEN_WIDTH - SPACE_SHIP_SIZE) / 2;
    sprite->y = (SCREEN_HEIGHT - SPACE_SHIP_SIZE) / 2;
    break;
  case 1:
  case 2:
  case 3:
    // printf("in SUPos: sprite type : %d \n",sprite->type);
    Random_Position(sprite);
    break;
  default:
    break;
  }
}
 
/*Set a random position on the edge of the grid*/
void Random_Position (sprite_t *sprite)
{
  int i;
  i = rand()%(4);

  if (i == 0){
    sprite->x = rand()%(SCREEN_WIDTH);
    sprite->y = 0;
  }
  if (i == 1){
    sprite->x = 0;
    sprite->y = rand()%(SCREEN_HEIGHT);
  }
  
  if (i == 2){
    sprite->x = rand()%(SCREEN_WIDTH);
    sprite->y = SCREEN_HEIGHT - sprite->size;
  }  

  if (i == 3){
    sprite->x = SCREEN_WIDTH - sprite->size;
    sprite->y = rand()%(SCREEN_HEIGHT);
  }
  
}
/*Set a random direction at a constant speed */
void Random_Direction(sprite_t *sprite, float vitesse)
{
  sprite->current = rand()%(36);
  sprite->vx += vitesse * cos(sprite->current  * 10 * M_PI / 180);
  sprite->vy += vitesse * (-sin(sprite->current  * 10 * M_PI / 180));  
}

////////////////////////////////////////////////////////////////////////////////
/*Need to init all sprite at begun*/
void init_all_sprite(sprite_t *space_ship, sprite_t *big_ast, sprite_t *norm_ast, sprite_t *small_ast, sprite_t *tirs)
{
  int i;
  /*init ship*/
  sprite_init(space_ship, 0, spaceship, SPACE_SHIP_SIZE, NB_SPACE_SHIP_SPRITE, NB_MAX_SHIP);
  
  /*Init all ast at begun (big_small_norm)*/
  for(i=0 ; i<NB_MAX_BIG_AST ; i++){
  sprite_init(&big_ast[i], 1, big_comet, BIG_AST_SIZE, NB_AST_SPRITE, NB_MAX_BIG_AST);
  }
  for(i=0 ; i<NB_MAX_NORM_AST ; i++){
    sprite_init(&norm_ast[i], 2, norm_comet, NORM_AST_SIZE, NB_AST_SPRITE, NB_MAX_NORM_AST);
  }
  for(i=0 ; i<NB_MAX_SMALL_AST ; i++){
  sprite_init(&small_ast[i], 3, small_comet, SMALL_AST_SIZE, NB_AST_SPRITE, NB_MAX_SMALL_AST);
  }
  for(i=0 ; i<NB_MAX_PIOU ; i++){
  sprite_init(&tirs[i], 4, bullet, PIOU_SIZE, 1, NB_MAX_PIOU);
  }

					    
}

/*Main fonction to create new sprite*/
void sprite_init(sprite_t *sprite, int type, SDL_Surface *sprite_picture, int sprite_size, int anim_sprite_num, int nombre_max_sprite)
{
  sprite->type = type;
  //sprite->col = sprite_picture->clip_rect.x;
  //sprite->lig = sprite_picture->clip_rect.y;
  //sprite->x = sprite_picture->clip_rect.x;
  //sprite->y = sprite_picture->clip_rect.y;
  sprite->current = 0;
  sprite->size = sprite_size;
  sprite->nb_sprite = anim_sprite_num;
  sprite->decompte = 0;
  sprite->vx = 0;
  sprite->vy = 0;
  sprite->position.x = sprite->col;
  sprite->position.y = sprite->lig;
  sprite->nombre_max = nombre_max_sprite;
  sprite->sprite_picture = sprite_picture;
  sprite->life = BASE_LIFE;
  /*ship*/
  if(type == 0){
    sprite->current = INIT_DIR;
    sprite->life = MAX_LIFE_SHIP;
    SetUpPosition(sprite); //, sprite_picture
}
  /*Big, Normal, Small Ast*/
  if(type == 1 ){
    sprite->numero_object = nbBigAst;
    SetUpPosition(sprite); 
    sprite->life = BIG_AST_LIFE;
  }
  if(type == 2){
    sprite->numero_object = nbNormAst;
    sprite->life = NORM_AST_LIFE;
    SetUpPosition(sprite); 
  }
  if(type == 3){
    sprite->numero_object = nbSmallAst;
    sprite->life = SMALL_AST_LIFE;
    SetUpPosition(sprite);
  }
  if(type == 4){
    sprite->numero_object = nbtirs;
  }
  if(type == 5){
    /*NOTHING printf("EXPLOSION MUAHAHAHHAHAHAHAH \n");*/
  }
}
/*the animation of the sprite turn */
void sprite_turn_left(sprite_t *sprite)
{
  sprite->current += 1;
  if(sprite->current >= sprite->nb_sprite)
    sprite->current = 0;
}

/*the animation of the sprite turn */
void sprite_turn_right(sprite_t *sprite)
{
  sprite->current -= 1;
  if(sprite->current < 0)
    sprite->current = sprite->nb_sprite - 1;
}

void ship_turn_left(sprite_t *sprite)
{
  sprite->current += 1;
  if(sprite->current >= sprite->nb_sprite*2)
    sprite->current = 0;
}

void ship_turn_right(sprite_t *sprite)
{
  sprite->current -= 1;
  if(sprite->current < 0)
    sprite->current = sprite->nb_sprite*5 - 1;
}

void ship_image(sprite_t *sprite)
{
  /* Define the source rectangle for the BlitSurface */
  sprite->image.y = 0;
  sprite->image.w = sprite->size;
  sprite->image.h = sprite->size;
  /* choose image according to direction and animation flip: */
  sprite->image.x = sprite->size * (sprite->current / 2);
}

void sprite_image(sprite_t *sprite)
{
  /* Define the source rectangle for the BlitSurface */
  sprite->image.y = 0;
  sprite->image.w = sprite->size;
  sprite->image.h = sprite->size;
  /* choose image according to direction and animation flip: */
  sprite->image.x = sprite->size * sprite->current;
}

/*Move of the sprite (+ hyperespace)*/
void sprite_move(sprite_t *sprite)
{
  sprite->x += sprite->vx;
  sprite->y += sprite->vy;
  
  hyperespace(sprite);
  
  sprite->col = sprite->x;
  sprite->lig = sprite->y;
  sprite->position.x = sprite->col;
  sprite->position.y = sprite->lig;
  if (sprite->type == 0){
    ship_image(sprite);
  }
  else
    {
      sprite_image(sprite);
    }
  sprite->decompte += 1;
  
  if (sprite->type == 1 || sprite->type == 2 || sprite->type == 3){ 
    if (sprite->decompte > 80){          //Un decompte qui permet de faire tourner le sprite
      sprite_turn_left(sprite);
      sprite->decompte = 0;   
    }
  }
  if (sprite->type == 5){
    if (sprite->decompte %100 == 0){  /*Permet d'animer l'explosion (utilisation du modulo car sinon plus complexe d'arreter la fameuse explosion)*/
      sprite_turn_left(sprite);   
    }
  }  
}
/*Acceleration of the sprite (it can be a const)*/
void sprite_boost(sprite_t *sprite, float accel)
{
  if (sprite->type == 0){
    sprite->vx += accel * cos(sprite->current *5* M_PI / 180) - FROTTEMENT * sprite->vx;
    sprite->vy += accel * (-sin(sprite->current *5* M_PI / 180)) - FROTTEMENT * sprite->vy;
    if(abs(sprite->vx) >= abs(VIT_MAX * cos(sprite->current *5* M_PI / 180)) && accel > 0)
      sprite->vx -= accel * cos(sprite->current *5* M_PI / 180);
    if(abs(sprite->vy) >= abs(VIT_MAX * sin(sprite->current *5* M_PI / 180)))
      sprite->vy -= accel * (-sin(sprite->current *5* M_PI / 180));
  }
  if (sprite->type ==4){
    sprite->vx += accel * cos(sprite->current  * 10 * M_PI / 180);
    sprite->vy += accel * (-sin(sprite->current  * 10 * M_PI / 180));  
  }
  if (sprite->type == 1 || sprite->type == 2 || sprite->type == 3){
    Random_Direction(sprite, accel);
  }
}

void hyperespace(sprite_t *sprite)
{
  if(sprite->x < 0)
    sprite->x = sprite->x + SCREEN_WIDTH - sprite->size;
  else if(sprite->x > SCREEN_WIDTH - sprite->size)
    sprite->x =sprite->x - SCREEN_WIDTH + sprite->size;
  if(sprite->y < 0)
    sprite->y = sprite->y + SCREEN_HEIGHT - sprite->size;
  else if(sprite->y > SCREEN_HEIGHT - sprite->size)
    sprite->y =sprite->y - SCREEN_HEIGHT + sprite->size;
  
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*auxiliary function : set colorkey*/
void set_colorkey_(SDL_Surface *sprite_picture, int R, int G, int B, SDL_Surface *screen)
{
  int colorkey;
  colorkey = SDL_MapRGB(screen->format, R, G, B);
  SDL_SetColorKey(sprite_picture, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
}

/*auxiliary fonction to downloadsprite*/
SDL_Surface* download_sprite_(char *nomSprite)
{
 
  SDL_Surface *temp, *nom;
  temp = SDL_LoadBMP(nomSprite);
  nom = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  
  return nom;
}
/*init SDL-Surface with picture, set up colorkey for each.*/
void downloadsprite()
{
  /*Load all sprite_picture*/
  explosion_picture = download_sprite_("explosion_model_12_64x64.bmp");
  small_comet = download_sprite_("asteroid-model1-32_16x16.bmp");
  norm_comet = download_sprite_("asteroid-model1-32_32x32.bmp");
  big_comet = download_sprite_("asteroid-model1-32_64x64.bmp");
  spaceship = download_sprite_("sprite(new)v2.bmp");
  spaceship2 = download_sprite_("sprite(new).bmp");
  background = download_sprite_("espace.bmp");
  bullet = download_sprite_("bullet02.bmp");

  /*Set all colorkey*/
  set_colorkey_(spaceship, 255, 0, 255, screen);
  set_colorkey_(spaceship2, 255, 0, 255, screen);
  set_colorkey_(big_comet, 0, 255, 255, screen);
  set_colorkey_(norm_comet, 0, 255, 255, screen);
  set_colorkey_(small_comet, 0, 255, 255, screen);
  set_colorkey_(explosion_picture, 0, 255, 255, screen);
  set_colorkey_(bullet, 255, 125, 0, screen);
}

///////////////////////////////////////////////////////////////////
/*test if kill ast is possible*/
bool kill_ast_param(int nombre_max, int numero, int type)
{
  bool killed = false;
  /*No need of more object than 100 on screen*/
  if (nombre_max > 100){
    printf("kill_ast : nombre_max is overrated : %d \n",nombre_max);
    killed = true;
  }
  if (numero < 0){
    printf("kill_ast : aaaw man, seriously ?  (numero < 0)\n");
    killed = true;
  }
  if (numero > (nombre_max)){
    printf("kill_ast : Numero asked is overated, max is: %d \n",nombre_max);
    printf("kill_ast : You asked numero :%d \t|type : %d \n",numero, type);
    killed = true;
  }
  
  return killed;
  
}
///////////////////////////////////////////////////////////////////////
int max(int a, int b)
{
  if(a>=b){
    return a;
  }
  if(b>a){
    return b;
  }
  printf("max : ERREUR");
  return 0;
}

int min(int a, int b)
{
  if(a<=b){
    return a;
  }
  if(b<a){
    return b;
  }
  printf("min : ERREUR");
  return 0;
}

