#include "physique.h"
/*Set a random position on the grid*/
void Random_Position (SDL_Rect *Position)
{

  srand(time(NULL));
  Position->x = rand()%(SCREEN_WIDTH-BIG_AST_SIZE);
  Position->y = rand()%(SCREEN_HEIGHT-BIG_AST_SIZE);
  
}

/*Set a random direction at a constant speed */
void Random_Direction(sprite_t *sprite, float vitesse)
{
  srand(time(NULL));
  sprite->current = rand()%(36);
  sprite->vx += vitesse * cos(sprite->current * 10 * M_PI / 180);
  sprite->vy += vitesse * (-sin(sprite->current * 10 * M_PI / 180));  
}

void sprite_init(sprite_t *sprite, int type, SDL_Surface * sprite_picture, int sprite_size, int anim_sprite_num)
{
  sprite->type = type;
  sprite->col = sprite_picture->clip_rect.x;
  sprite->lig = sprite_picture->clip_rect.y;
  sprite->x = sprite_picture->clip_rect.x;
  sprite->y = sprite_picture->clip_rect.y;
  sprite->size = sprite_size;
  sprite->nb_sprite = anim_sprite_num;
  sprite->vx = 0;
  sprite->vy = 0;
  //ship
  if(type == 0){
    sprite->current = INIT_DIR;
}
  //big_ast
  if(type == 1){
    sprite->current = INIT_ROTATION;
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
  if(sprite->x < 0)
    sprite->x = sprite->x + SCREEN_WIDTH - sprite->size;
  else if(sprite->x > SCREEN_WIDTH - sprite->size)
    sprite->x =sprite->x - SCREEN_WIDTH + sprite->size;
  sprite->y += sprite->vy;
  if(sprite->y < 0)
    sprite->y = sprite->y + SCREEN_HEIGHT - sprite->size;
  else if(sprite->y > SCREEN_HEIGHT - sprite->size)
    sprite->y =sprite->y - SCREEN_HEIGHT + sprite->size;
  sprite->col = sprite->x;
  sprite->lig = sprite->y;


}

/*Acceleration of the sprite (it can be a const)*/
void sprite_boost(sprite_t *sprite, float accel)
{
  if (sprite->type == 0){
    sprite->vx += accel * cos(sprite->current * 10 * M_PI / 180) - FROTEMENT * sprite->vx;
    sprite->vy += accel * (-sin(sprite->current * 10 * M_PI / 180)) - FROTEMENT * sprite->vy;
    if(abs(sprite->vx) >= abs(VIT_MAX * cos(sprite->current * 10 * M_PI / 180)) && accel > 0)
      sprite->vx -= accel * cos(sprite->current * 10 * M_PI / 180);
    if(abs(sprite->vy) >= abs(VIT_MAX * sin(sprite->current * 10 * M_PI / 180)))
      sprite->vy -= accel * (-sin(sprite->current * 10 * M_PI / 180));
  }
  if (sprite->type == 1){
    Random_Direction(sprite, accel);
  }
}
