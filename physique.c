#include "physique.h"

/*Give various information, press v in game to know what.*/
void various_information(sprite_t *space_ship, sprite_t *big_ast, sprite_t *norm_ast, sprite_t *small_ast, int *score)
{
  int i;
  printf("space_ship->life : %d\n", space_ship->life);
  
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
  printf("score: %d \n", *score);
}

/*Set Position of all Sprites*/
void SetUpPosition(sprite_t *sprite){  //, SDL_Surface *surface) avant
  
  /* set sprite position in the middle of the window */
  switch(sprite->type) {
  case 0:
    sprite->x = (SCREEN_WIDTH - SPACE_SHIP_SIZE) / 2;
    sprite->y = (SCREEN_HEIGHT - SPACE_SHIP_SIZE) / 2;
    sprite->vx = 0;
    sprite->vy = 0;
    break;
  case 1:
  case 2:
  case 3:
    // printf("in SUPos: sprite type : %d \n",sprite->type);
    Random_Position(sprite);
    break;
  case 10:
    sprite->x =(SCREEN_WIDTH - PLACEMENT_MENU_JOUER_X)/2;
    sprite->y = (SCREEN_HEIGHT - PLACEMENT_MENU_JOUER_Y);
    sprite->col = sprite->x;
    sprite->lig = sprite->y;
    sprite->position.x = sprite->col;
    sprite->position.y = sprite->lig;
    break;
  case 11:
    sprite->x = (SCREEN_WIDTH - PLACEMENT_MENU_QUITTER_X)/2;
    sprite->y = (SCREEN_HEIGHT - PLACEMENT_MENU_QUITTER_Y);
    sprite->col = sprite->x;
    sprite->lig = sprite->y;
    sprite->position.x = sprite->col;
    sprite->position.y = sprite->lig;
    break;
  case 12:
    sprite->x = (SCREEN_WIDTH - MENU_GAME_OVER_SIZE)/2;
    sprite->y = 0;
    sprite->col = sprite->x;
    sprite->lig = sprite->y;
    sprite->position.x = sprite->col;
    sprite->position.y = sprite->lig;
    break;
  case 13:
    sprite->x = (SCREEN_WIDTH - MENU_RETURN_SIZE)/2;
    sprite->y = (SCREEN_HEIGHT - 400);
    sprite->col = sprite->x;
    sprite->lig = sprite->y;
    sprite->position.x = sprite->col;
    sprite->position.y = sprite->lig;
    break;
  case 21:
  case 22:
    Random_Position_Partout(sprite);
    sprite->col = sprite->x;
    sprite->lig = sprite->y;
    sprite->position.x = sprite->col;
    sprite->position.y = sprite->lig;
    break;
  default:
    break;
  }
}

void Set_up_PV(sprite_t *PV)

 {
  int i;
  for(i = 0; i<MAX_LIFE_SHIP ; i++)
    {
      PV[i].x = 0 +i*PV_SIZE;
      PV[i].y = PV_SIZE;
      PV[i].col = PV[i].x;
      PV[i].lig = PV[i].y;
      PV[i].position.x = PV[i].col;
      PV[i].position.y = PV[i].lig;
    }
 }

void Random_Position_Partout(sprite_t *sprite)
{
    sprite->x = rand()%(SCREEN_WIDTH);
    sprite->y = rand()%(SCREEN_HEIGHT);
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
void init_all_sprite(sprite_t *space_ship, sprite_t *big_ast, sprite_t *norm_ast,
		     sprite_t *small_ast, sprite_t *tirs, sprite_t *explosion
		    , sprite_t *game_over, sprite_t *return_menu
		     , sprite_t *jouer, sprite_t *quitter, sprite_t *PV)
{
  int i;
  /*init menu*/
  sprite_init(jouer, 10, menu_jouer_selec, MENU_JOUER_SIZE, NB_MENU_JOUER_SPRITE, NB_MAX_MENU_JOUER);
  sprite_init(quitter, 11, menu_quitter, MENU_QUITTER_SIZE, NB_MENU_QUITTER_SPRITE, NB_MAX_MENU_QUITTER);
  sprite_init(game_over, 12, menu_game_over, MENU_GAME_OVER_SIZE, NB_MENU_GAME_OVER_SPRITE, NB_MAX_MENU_GAME_OVER);
  sprite_init(return_menu, 13, menu_return, MENU_RETURN_SIZE, NB_MENU_RETURN_SPRITE, NB_MAX_MENU_RETURN);
   
  
  for(i=0; i<MAX_LIFE_SHIP ; i++){
    sprite_init(PV, 20, vie, PV_SIZE, NB_PV_SPRITE,
		MAX_LIFE_SHIP);
  }

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
  for(i=0 ; i<NB_MAX_EXPL ; i++){
    sprite_init(&explosion[i],  5, explosion_picture, EXPLOSION_SIZE, ANIM_EXPLOSION_NUM, NB_MAX_EXPL);
  }
					    
}

/*Main fonction to create new sprite*/
void sprite_init(sprite_t *sprite, int type, SDL_Surface *sprite_picture,
		 int sprite_size, int anim_sprite_num, int nombre_max_sprite)
{
  sprite->type = type;
  sprite->current = 0;
  sprite->size = sprite_size;
  sprite->nb_sprite = anim_sprite_num;
  sprite->decompte = 0;
  sprite->vx = 0;
  sprite->vy = 0;
  sprite->col = 0;      //AJOUT
  sprite->lig = 0;      //AJOUT
  sprite->position.x = sprite->col;
  sprite->position.y = sprite->lig;
  sprite->nombre_max = nombre_max_sprite;
  sprite->sprite_picture = sprite_picture;
  sprite->life = BASE_LIFE;
  /*ship*/
  if(type == 0){
    sprite->current = INIT_DIR;
    sprite->life = MAX_LIFE_SHIP;
    SetUpPosition(sprite); //,sprite_picture
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
  if(type == 10 || type == 11 ||type == 12 || type == 21 || type == 22){
    SetUpPosition(sprite);
  }
  if(type == 20){
    Set_up_PV(sprite);
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
    sprite->current = sprite->nb_sprite*2 - 1;
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
  
  if (sprite->type == 0)
    {
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
    sprite->vx += accel * cos(sprite->current * 5 * M_PI / 180) - FROTTEMENT * sprite->vx;
    sprite->vy += accel * (-sin(sprite->current * 5 * M_PI / 180)) - FROTTEMENT * sprite->vy;
    if(abs(sprite->vx) >= abs(VIT_MAX * cos(sprite->current * 5 * M_PI / 180)) && accel > 0)
      sprite->vx -= accel * cos(sprite->current * 5 * M_PI / 180);
    if(abs(sprite->vy) >= abs(VIT_MAX * sin(sprite->current * 5 * M_PI / 180)))
      sprite->vy -= accel * (-sin(sprite->current * 5 * M_PI / 180));
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
  vie = download_sprite_("PackDeSoin.bmp");
  menu_jouer = download_sprite_("Bouton_play.bmp");
  menu_jouer_selec = download_sprite_("Bouton_play_selec.bmp");
  menu_quitter = download_sprite_("Bouton_quit.bmp");
  menu_quitter_selec = download_sprite_("Bouton_quit_selec.bmp");
  menu_game_over = download_sprite_("Game_Over_redim.bmp");
  menu_return = download_sprite_("Back_to_menu.bmp");
  atomic_bomb_picture = download_sprite_("BombeAtomique.bmp");
  bonus_mitraille = download_sprite_("Mitraille.bmp");
  /*Set all colorkey*/
  set_colorkey_(spaceship, 255, 0, 255, screen);
  set_colorkey_(spaceship2, 255, 0, 255, screen);
  set_colorkey_(big_comet, 0, 255, 255, screen);
  set_colorkey_(norm_comet, 0, 255, 255, screen);
  set_colorkey_(small_comet, 0, 255, 255, screen);
  set_colorkey_(explosion_picture, 0, 255, 255, screen);
  set_colorkey_(bullet, 255, 125, 0, screen);
  set_colorkey_(vie, 0, 0, 0, screen);
  //menu
  set_colorkey_(menu_jouer, 255, 255, 255, screen);
  set_colorkey_(menu_jouer_selec, 255, 255, 255, screen);
  set_colorkey_(menu_quitter_selec, 255, 255, 255, screen);
  set_colorkey_(menu_quitter, 255, 255, 255, screen);
  set_colorkey_(menu_game_over, 255, 255, 255, screen);
  set_colorkey_(menu_return, 255, 255, 255, screen);

  //Bonus:
  set_colorkey_(atomic_bomb_picture, 255, 0, 255, screen);
  set_colorkey_(bonus_mitraille, 136, 136, 136, screen);
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

///////////////////////////////////////////////////////////////////////////

bool collide_test(sprite_t sprite1, sprite_t sprite2, SDL_PixelFormat* format, int * cu, int * cv) 
{
  /* rough test using the bounding boxes (bb) only */
  bool test = !(sprite2.x > sprite1.x + sprite1.size ||
		sprite2.x + sprite2.size < sprite1.x ||
		sprite2.y > sprite1.y + sprite1.sprite_picture->h ||
		sprite2.y + sprite2.sprite_picture->h < sprite1.y);

  /* if the rough test succeeded, a fine test is performed using the colorkeys (transparency colors) of the sprites (may be optimized!) */
  if (test) {
    Uint32 *bmp1 = (Uint32*)malloc(sizeof(Uint32) * sprite1.size * sprite1.sprite_picture->h), *sprite_it, *bmp_it;
    Uint32 *bmp2 = (Uint32*)malloc(sizeof(Uint32) * sprite2.size * sprite2.sprite_picture->h);
    int u, v, v1 = 0; 

    /* lock the video memory and copy the sprite bitmaps into cpu memory */
    // printf("SDL_MUSTLOCK(sprite1->sprite) : %d\n", SDL_MUSTLOCK(sprite1->sprite));
    SDL_LockSurface(sprite1.sprite_picture);
    SDL_LockSurface(sprite2.sprite_picture);
    bmp_it = bmp1;
    sprite_it = (Uint32*)(sprite1.sprite_picture->pixels) +  sprite1.current/2 * sprite1.size;
    for (v = 0; v < sprite1.sprite_picture->h; v++) {
      for (u = 0; u < sprite1.size; u++) {
	*bmp_it++ = *sprite_it++;
      }
      sprite_it += (sprite1.sprite_picture->w - sprite1.size);
    }
    bmp_it = bmp2;
    sprite_it = (Uint32*)(sprite2.sprite_picture->pixels) +  sprite2.current/2 * sprite2.size;
    for (v = 0; v < sprite2.sprite_picture->h; v++) {
      for (u = 0; u < sprite2.size; u++) {
	*bmp_it++ = *sprite_it++;
      }
      sprite_it += (sprite2.sprite_picture->w - sprite2.size);
    }
    SDL_UnlockSurface(sprite1.sprite_picture);
    SDL_UnlockSurface(sprite2.sprite_picture);

    bmp_it = bmp1;
    test = false;

    /* for each pixel p1 in bmp1, until test = true... */
    while (!test && v1 < sprite1.sprite_picture->h) {
      int u1 = 0;
      while (!test && u1 < sprite1.size) {
	/* get the screen coordinates of pixel p1 */
	int screen_u = u1 + sprite1.x;
	int screen_v = v1 + sprite1.y;

	/* if the screen coordinates of p1 are inside the bb of sprite2... */
	if (screen_u >= sprite2.x &&
	    screen_u < sprite2.x + sprite2.size &&
	    screen_v >= sprite2.y &&
	    screen_v < sprite2.y + sprite2.sprite_picture->h) {
	  Uint32 pixel1 = *bmp_it;
	  unsigned int col1;
	  Uint8 r, g, b;
	  
	  /* get the color col1 of p1*/
	  SDL_GetRGB(pixel1, format, &r, &g, &b);
	  col1 = SDL_MapRGB(format, r, g, b);

	  /* if col1 is a NON transparent color... */
	  if (col1 != sprite1.sprite_picture->format->colorkey) {
	    Uint32 pixel2;
	    unsigned int col2;
	    Uint8 r, g, b;
	    int u2, v2;

	    /* get the local coordinates of pixel p2 in sprite2 corresponding to the screen coordinates of p1 */
	    u2 = screen_u - sprite2.x;
	    v2 = screen_v - sprite2.y;
	    
	    /* get the color col2 of p2 */
	    pixel2 = *(bmp2 + u2 + v2 * sprite2.size);
	    SDL_GetRGB(pixel2, format, &r, &g, &b);
	    col2 = SDL_MapRGB(format, r, g, b);
	    
	    /* if col2 is also a non transparent color, a collision occurs  */
	    if (col2 != sprite2.sprite_picture->format->colorkey) {
	      test = true;
	      *cu = screen_u; 
	      *cv = screen_v;
	    }
	  }
	}
	u1++;
	bmp_it++;
      }
      v1++;
    }
    free(bmp1);
    free(bmp2);
  }
  
  return test;
}
