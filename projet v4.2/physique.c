#include "physique.h"

/*Invert direction of sprite 2 */
void InvertDirection(sprite_t *sprite1, sprite_t *sprite2)
{
  sprite2->vx = -sprite1->vx;
  sprite2->vy = -sprite1->vy;
}

/*Set Up sprite 1 at position sprite 2 */
void SetUpAtPosition(sprite_t *sprite1, sprite_t *sprite2)
{
  sprite1->x = sprite2->x;
  sprite1->y = sprite2->y; 
}

/*Set Position of all Sprites*/
void SetUpPosition(sprite_t *sprite, SDL_Surface *surface){
  
  /* set sprite position in the middle of the window */
  switch(sprite->type) {
  case 0:
    sprite->x = (SCREEN_WIDTH - SPACE_SHIP_SIZE) / 2;
    surface->clip_rect.x = sprite->x;
    sprite->y = (SCREEN_HEIGHT - SPACE_SHIP_SIZE) / 2;
    surface->clip_rect.y = sprite->y;
    break;
  case 1:
    //printf("in SUPos: sprite type : %d \n",sprite->type);
    Random_Position(sprite);
    surface->clip_rect.x = sprite->x;
    surface->clip_rect.y = sprite->y;
    break;
  case 2:
    //printf("in SUPos: sprite type : %d \n",sprite->type);
    Random_Position(sprite);
    surface->clip_rect.x = sprite->x;
    surface->clip_rect.y = sprite->y;
    break;
  case 3:
    //printf("in SUPos : sprite type : %d \n",sprite->type);
    Random_Position(sprite);
    surface->clip_rect.x = sprite->x;
    surface->clip_rect.y = sprite->y;
    break;
  default:
    break;
  }
}
 
/*Set a random position on the edge of the grid*/
void Random_Position (sprite_t *sprite)
{
  int i;
  int repositionnement = 0;
  /*if an ast is called, the second after it's not at the same position*/
  if (*Random_Position_activated == true){
    repositionnement = *temps_actuel+18749;
      *Random_Position_activated = false;
  }
  
  srand(time(NULL));
  i = (rand()+repositionnement)%(4);
  
  if (i == 0){
    sprite->x = (rand()+repositionnement)%(SCREEN_WIDTH);
  sprite->y = 0;
  }
  if (i == 1){
    sprite->x = (rand()+repositionnement)%(SCREEN_WIDTH);
    sprite->y = SCREEN_HEIGHT;
  }
  if (i == 2){
    sprite->x = 0;
    sprite->y = (rand()+repositionnement)%(SCREEN_HEIGHT);
  }
  if (i == 3){
    sprite->x = SCREEN_WIDTH;
    sprite->y = (rand()+repositionnement)%(SCREEN_HEIGHT);
  }
  if (repositionnement == 0){
    *Random_Position_activated = true;
  }
  
}
/*Set a random direction at a constant speed */
void Random_Direction(sprite_t *sprite, float vitesse)
{
  srand(time(NULL));
  sprite->current = rand()%(36);
  sprite->vx += vitesse * cos(sprite->current  * 10 * M_PI / 180);
  sprite->vy += vitesse * (-sin(sprite->current  * 10 * M_PI / 180));  
}

////////////////////////////////////////////////////////////////////////////////
/*Need to init all sprite at begun*/
void init_all_sprite(sprite_t *space_ship, sprite_t *big_ast, sprite_t *norm_ast, sprite_t *small_ast){
  int i,j,k;
  /*init ship*/
  sprite_init(space_ship, 0, spaceship, SPACE_SHIP_SIZE, NB_SPACE_SHIP_SPRITE, NB_MAX_SHIP);
  
  /*Init all ast at begun (big_small_norm)*/
  for(i=0 ; i<NB_MAX_BIG_AST-1 ; i++){
  sprite_init(&big_ast[i], 1, big_comet, BIG_AST_SIZE, NB_AST_SPRITE, NB_MAX_BIG_AST);
  }
  for(j=0 ; j<NB_MAX_NORM_AST-1 ; j++){
    sprite_init(&norm_ast[j], 2, norm_comet, NORM_AST_SIZE, NB_AST_SPRITE, NB_MAX_NORM_AST);
  }
  for(k=0 ; k<NB_MAX_SMALL_AST-1 ; k++){
  sprite_init(&small_ast[k], 3, small_comet, SMALL_AST_SIZE, NB_AST_SPRITE, NB_MAX_SMALL_AST);
  }

  
}

/*Main fonction to create new sprite*/
void sprite_init(sprite_t *sprite, int type, SDL_Surface * sprite_picture, int sprite_size, int anim_sprite_num, int nombre_max_sprite)
{
  sprite->type = type;
  sprite->col = sprite_picture->clip_rect.x;
  sprite->lig = sprite_picture->clip_rect.y;
  sprite->x = sprite_picture->clip_rect.x;
  sprite->y = sprite_picture->clip_rect.y;
  sprite->current = 0;
  sprite->size = sprite_size;
  sprite->nb_sprite = anim_sprite_num;
  sprite->decompte = 0;
  sprite->vx = 0;
  sprite->vy = 0;
  sprite->position.x = sprite->col;
  sprite->position.y = sprite->lig;
  sprite->nombre_max = nombre_max_sprite;


  /*ship*/
  if(type == 0){
    sprite->current = INIT_DIR;
    SetUpPosition(sprite, sprite_picture);
}
  /*Big, Normal, Small Ast*/
  if(type == 1 ){
    sprite->numero_object = *nbBigAst;
    SetUpPosition(sprite, sprite_picture);
    //  printf("nbBigAst : %d \n",*nbBigAst);
    // printf("sprite.numero_object = %d \n", sprite->numero_object);
  }
  if(type == 2){
    sprite->numero_object = *nbNormAst;
    SetUpPosition(sprite, sprite_picture);
  }
  if(type == 3){
    sprite->numero_object = *nbSmallAst;
    SetUpPosition(sprite, sprite_picture);
  }
  if(type == 5){
    /*NOTHING*/printf("EXPLOSION MUAHAHAHHAHAHAHAH \n");
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

/*Move of the sprite (+ hyperespace)*/
void sprite_move(sprite_t *sprite)
{
  sprite->x += sprite->vx;
  //sprite->y += sprite->vy;

  hyperespace(sprite);
  
  sprite->col = sprite->x;
  sprite->lig = sprite->y;
  sprite->position.x = sprite->col;
  sprite->position.y = sprite->lig;

  if (sprite->type == 0){
  /* Define the source rectangle for the BlitSurface */
  sprite->image.y = 0;
  sprite->image.w = sprite->size;
  sprite->image.h = sprite->size;
  /* choose image according to direction and animation flip: */
  sprite->image.x = sprite->size * sprite->current;
  }

  if (sprite->type == 1 || sprite->type == 2 || sprite->type == 3){
    sprite->image.y = 0;
    sprite->image.w = sprite->size;
    sprite->image.h = sprite->size;
    sprite->image.x = sprite->size * sprite->current;
    sprite->decompte += 1;
    if (sprite->decompte > 80){
      sprite_turn_left(sprite);
      sprite->decompte = 0;   
    }
  }
  
  if (sprite->type == 4){
    sprite->decompte += 1;

}
  
  if (sprite->type == 5){
    sprite->image.y = 0;
    sprite->image.w = sprite->size;
    sprite->image.h = sprite->size;
    sprite->image.x = sprite->size * sprite->current;
    sprite->decompte += 1;
    if (sprite->decompte %100 == 0){
      sprite_turn_left(sprite);   
    }
  }
}

/*Acceleration of the sprite (it can be a const)*/
void sprite_boost(sprite_t *sprite, float accel)
{
  if (sprite->type == 0){
    sprite->vx += accel * cos(sprite->current * 10 * M_PI / 180) - FROTTEMENT * sprite->vx;
    sprite->vy += accel * (-sin(sprite->current * 10 * M_PI / 180)) - FROTTEMENT * sprite->vy;
    if(abs(sprite->vx) >= abs(VIT_MAX * cos(sprite->current * 10 * M_PI / 180)) && accel > 0)
      sprite->vx -= accel * cos(sprite->current * 10 * M_PI / 180);
    if(abs(sprite->vy) >= abs(VIT_MAX * sin(sprite->current * 10 * M_PI / 180)))
      sprite->vy -= accel * (-sin(sprite->current * 10 * M_PI / 180));
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
  sprite->y += sprite->vy;
  if(sprite->y < 0)
    sprite->y = sprite->y + SCREEN_HEIGHT - sprite->size;
  else if(sprite->y > SCREEN_HEIGHT - sprite->size)
    sprite->y =sprite->y - SCREEN_HEIGHT + sprite->size;
  
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
  int colorkey;
  explosion_picture = download_sprite_("explosion_model_12_64x64.bmp");
  small_comet = download_sprite_("asteroid-model1-32_16x16.bmp");
  norm_comet = download_sprite_("asteroid-model1-32_32x32.bmp");
  big_comet = download_sprite_("asteroid-model1-32_64x64.bmp");
  spaceship = download_sprite_("greenship-v1.bmp");
  background = download_sprite_("backgroundlvl1.bmp");
  bullet = download_sprite_("bullet02.bmp");

  colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
  SDL_SetColorKey(spaceship, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  colorkey = SDL_MapRGB(screen->format, 0, 255, 255);
    SDL_SetColorKey(big_comet, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(norm_comet, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(small_comet, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(explosion_picture, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  colorkey = SDL_MapRGB(screen->format, 255, 125, 125);
    SDL_SetColorKey(bullet, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
}

///////////////////////////////////////////////////////////////////
/*test if kill ast is possible*/
bool kill_sprite_param(int nombre_max, int numero)
{
  bool killed = false;
  /*No need of more object than 100 on screen*/
  if (nombre_max > 100){
    printf("kill_ast : nombre_max is overrated : %d \n",nombre_max);
    killed = true;
  }
  if (numero < 0){
    printf("kill_ast : aaaw man, seriously ?  \n");
    killed = true;
  }
  if (numero > (nombre_max)){
    printf("kill_ast : Numero asked is overated, max is: %d \n",nombre_max);
    printf("kill_ast : You asked numero :%d \n",numero);
    killed = true;
  }
  
  return killed;
  
}