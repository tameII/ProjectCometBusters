#include "physique.h"
   
 
///////////////////////////////////////////////////////////////////////////////
/******************************FIN HEADER*************************************/
//////////////////////////////////////////////////////////////////////////////
/****************************************************************************/
/*FONCTION ANNEXE MUSIQUE*/
/* Les données du fichier son chargé */
Uint8 * sounddata;
/* La taille du fichier son chargé, en octets */
Uint32 soundlength;
/* Position courante de lecture dans le fichier son */
Uint32 soundpos;

/* Fonction de rappel qui copie les données sonores dans le tampon audio */
void mixaudio(void * userdata, Uint8 * stream, int len)
{
  /* Attention à ne pas déborder lors de la copie */
  Uint32 tocopy = soundlength - soundpos > len ? len : soundlength - soundpos; 

  /* Copie des données sonores dans le tampon audio... */
  memcpy(stream, sounddata + soundpos, tocopy); 

  /* Mise à jour de la position de lecture */
  soundpos += tocopy;
}

 
void pause_and_close_audio()
{
  /* On cesse d'appeler la fonction de rappel */
  SDL_PauseAudio(1);

  /* Fermer le périphérique audio */
  SDL_CloseAudio();
  
}


/*Parametres généraux a mettre en place.*/
int musique_param(SDL_AudioSpec *soundfile, SDL_AudioSpec *obtained,
		  SDL_AudioCVT *cvt )
{

  /* Conversion vers le format du tampon audio */
  if (SDL_BuildAudioCVT(cvt, soundfile->format, soundfile->channels,
			soundfile->freq, obtained->format, obtained->channels,
			obtained->freq) < 0) {
    printf("Impossible de construire le convertisseur audio!\n");
    return 1;
  }
  /* Création du tampon utilisé pour la conversion */
  cvt->buf = malloc(soundlength * cvt->len_mult);
  cvt->len = soundlength;
  memcpy(cvt->buf, sounddata, soundlength);

  /* Conversion... */
  if (SDL_ConvertAudio(cvt) != 0) {
    printf("Erreur lors de la conversion du fichier audio: %s\n",
	   SDL_GetError());
    return 1;
  } 

  /* Libération de l'ancien tampon, création du nouveau,
     copie des données converties, effacement du tampon de conversion */
  SDL_FreeWAV(sounddata);
  sounddata = malloc(cvt->len_cvt);
  memcpy(sounddata, cvt->buf, cvt->len_cvt);
  free(cvt->buf);

  soundlength = cvt->len_cvt;
  /*printf("Taille du son converti: %d octets\n", soundlength);*/
  soundpos = 0;


  return 0;
      
}

/*Fonction mettant en place la musique*/
int musique(char *titre, SDL_AudioSpec *desired, SDL_AudioSpec *obtained,
	    SDL_AudioSpec *soundfile, SDL_AudioCVT *cvt )
{
  int bug;

  if (SDL_OpenAudio(desired, obtained) != 0) {
    printf("Erreur lors de l'ouverture du périphérique audio: %s\n",
	   SDL_GetError());
    return 1;
  }
  /* Chargement du fichier .wav */
  if (SDL_LoadWAV(titre, soundfile, &sounddata, &soundlength) == NULL) {
    printf("Erreur lors du chargement du fichier son: %s\n",
	   SDL_GetError());
    return 1;
  }
  bug = musique_param(soundfile, obtained, cvt);

  /* La fonction de rappel commence à être appelée à partir de maintenant. */
  /* printf("Démarrage de la lecture...\n");*/
  SDL_PauseAudio(0);

  return bug;
  
}

/*Init musique, met a jour les caractèristiques de la musique.*/
void init_musique(SDL_AudioSpec *desired, int freq, char *format, int channel,
		  int sample)
{
  // printf("%s \n", format);
  
  if(strstr(format, "AUDIO_U16SYS")){
    /*Initialisation de tout ce qui a trait a la musique
      C'est marrant parce que une freq de 11025 fonctionne quand même*/
    /* Son 16 bits stéréo à 44100 Hz *///AUDIO_U16SYS
    desired->freq = freq;
    desired->format = AUDIO_U16SYS;
    desired->channels = channel;
    /* Le tampon audio contiendra 512 ou 1024 échantillons*/ 
    desired->samples = sample;

    /*Mise en place de la fonction de rappel et des données utilisateur*/
    desired->callback = &mixaudio;
    desired->userdata = NULL;
  }

  
  if(strstr(format, "AUDIO_S8")){  
    /* Son 8 bits stéréo à 11025 Hz */
    desired->freq = freq;
    desired->format = AUDIO_S8;
    desired->channels = channel;
    /* Le tampon audio contiendra 512 ou 1024 échantillons*/ 
    desired->samples = sample;

    /*Mise en place de la fonction de rappel et des données utilisateur*/
    desired->callback = &mixaudio;
    desired->userdata = NULL;
  }

  

}


/**************************************************************************/
/*FONCTION OF CREATION :*/
/*Create two portal, be aware to set the NB_MAX to a pair number,*
 *even if i set a security*/
void CreatePortal(sprite_t *portal)
{
  if(nbPortal < NB_MAX_PORTAL-1){  
    if(nbPortal < NB_MAX_PORTAL){
      sprite_init(&portal[nbPortal], 23, portal_picture, PORTAL_SIZE,
		  NB_PORTAL_SPRITE, NB_MAX_PORTAL);
      nbPortal +=1;
    }
    if(nbPortal < NB_MAX_PORTAL){
      sprite_init(&portal[nbPortal], 23, portal_picture, PORTAL_SIZE,
		  NB_PORTAL_SPRITE, NB_MAX_PORTAL);
      nbPortal +=1;
    }
  }
}


/*Create bombe atomique qui fait apparaitre a un endroit aleatoire*
 * une BOMBE ATOMIQUE OUH YEAH                                    */
void CreateAtomicBomb(sprite_t *bonus_atomic_bomb){
  if(nbAtomicBomb < 1){
    sprite_init(bonus_atomic_bomb, 21, atomic_bomb_picture, ATOMIC_BOMB_SIZE, 
		NB_ATOMIC_BOMB_SPRITE, NB_MAX_ATOMIC_BOMB);
	      
    nbAtomicBomb += 1;
  }
}

/*Create a device who fire harder better faster stronger*/
void CreateMitraille(sprite_t *mitraille)
{
  if(nbMitraille < 1)
    {
      sprite_init(mitraille,  22, bonus_mitraille, BONUS_MITRAILLE_SIZE,
		  NB_BONUS_MITRAILLE_SPRITE, NB_MAX_BONUS_MITRAILLE);
      nbMitraille += 1;
    }
}

/*Create explosion size 64*64*/
void CreateExplosion(sprite_t *explosion, sprite_t *sprite, int numero)
{
  if (nbExplosion < NB_MAX_EXPL){
    sprite_init(&explosion[nbExplosion], 5, explosion_picture, EXPLOSION_SIZE,
		ANIM_EXPLOSION_NUM, NB_MAX_EXPL);
    SetUpAtPosition(&explosion[nbExplosion], &sprite[numero] );
    nbExplosion += 1;
  }

}

/*Create Small Ast, appel de sprite_init avec les carac' du small_ast,*/
/* puis donne une vitesse aléatoire avec sprite_boost                 */
void CreateSmallAst(sprite_t *small_ast)
{
  if(nbSmallAst < NB_MAX_SMALL_AST){
    sprite_init(&small_ast[nbSmallAst], 3, small_comet, SMALL_AST_SIZE,
		NB_AST_SPRITE, NB_MAX_SMALL_AST);
    sprite_boost(&small_ast[nbSmallAst], VIT_SMALL_AST);
    nbSmallAst += 1; 
  }
  
}

/*Create Norm Ast*/
void CreateNormAst(sprite_t *norm_ast)
{
  if (nbNormAst < NB_MAX_NORM_AST){
    sprite_init(&norm_ast[nbNormAst], 2, norm_comet, NORM_AST_SIZE,
		NB_AST_SPRITE, NB_MAX_NORM_AST);
    sprite_boost(&norm_ast[nbNormAst], VIT_NORM_AST);
    nbNormAst += 1;
  }
  
} 

/*Create comet size 64*64,*/
void CreateBigAst(sprite_t *big_ast)
{
 
  if (nbBigAst < NB_MAX_BIG_AST){
    sprite_init(&big_ast[nbBigAst], 1, big_comet, BIG_AST_SIZE,
		NB_AST_SPRITE, NB_MAX_BIG_AST);
    sprite_boost(&big_ast[nbBigAst], VIT_BIG_AST);
    nbBigAst += 1;
  }
  
}

/*Create an ast*/
void CreateAst(sprite_t *ast){
  if (ast->type == 1){
    CreateBigAst(ast);
  }
  if (ast->type == 2){
    CreateNormAst(ast);
  }
  if (ast->type == 3){
    CreateSmallAst(ast);
  }
    
}



/*Create projectile*/
void create_piou (sprite_t* tirs, sprite_t* space_ship)
{
  if (nbtirs<NB_MAX_PIOU){
    sprite_init(&tirs[nbtirs], 4, bullet, PIOU_SIZE, 1, NB_MAX_PIOU);
    tirs[nbtirs].current = space_ship->current/2;
    sprite_boost(&tirs[nbtirs], VIT_NORM_PIOU);
    SetUpAtMiddle(&tirs[nbtirs], space_ship);
    //printf("Piou !\n");
    nbtirs += 1;
  }
}


/*********************************************************************/


/*Remet a zero la vie de tout les sprtie du tableau donné*/
void kill_all_sprite_param(sprite_t *sprite, int nb_max)
{
  int i;
  for(i=0; i<nb_max;i++){
    sprite[i].life = 0;
  }
}
/*Fonction qui fait exploser TOUT les sprites sur l'ecran  *
 *Servira pour la bombe atomique et pour la fin du jeu     *
 *En fait ça met a zero toute les vie de chaque sprite     *
 *si le space_ship->life = 0                               */
void kill_all_sprite(sprite_t *space_ship,sprite_t *big_ast, sprite_t *norm_ast,
		     sprite_t *small_ast, sprite_t *tirs, int *gameover,
		     int *animationFinale, bool *bomb_triggered)
{

  if(space_ship->life <= 0){
    *animationFinale += 1;
    kill_all_sprite_param(big_ast, NB_MAX_BIG_AST);
    kill_all_sprite_param(norm_ast, NB_MAX_NORM_AST);
    kill_all_sprite_param(small_ast, NB_MAX_SMALL_AST);
    kill_all_sprite_param(tirs, NB_MAX_PIOU);
    SetUpPosition(space_ship);
    cogne = false;
    if( *animationFinale >= DECOMPTE_FIN){
      *gameover = 1;                // GAME OVER ICI !!!
      *animationFinale = 0;
    } 
  }
  if(*bomb_triggered == true){
    kill_all_sprite_param(big_ast, NB_MAX_BIG_AST);
    kill_all_sprite_param(norm_ast, NB_MAX_NORM_AST);
    kill_all_sprite_param(small_ast, NB_MAX_SMALL_AST);
    *bomb_triggered = false;
  }
}

/*Fonction qui fait disparaitre tout les sprites de l'ecran*/
void kill_all_number()
{
  nbBigAst = 0;
  nbNormAst = 0;
  nbSmallAst = 0;
  nbtirs = 0;
  nbExplosion = 0;
  nbAtomicBomb = 0;
  nbMitraille = 0;
  nbPortal = 0;
}

void ajout_score(int *score, int point)
{
  *score += point;
}
void score(int *score, int type)
{
  if(type == 1){
    ajout_score(score, BIG_AST_POINT);
  }
  if(type == 2){
    ajout_score(score, NORM_AST_POINT);
  }
  if(type == 3){
    ajout_score(score, SMALL_AST_POINT);
  }
} 


/*Test si le ship est mort. Pourrait theoriquement fonctionner pour un sprite *
 *si on modifie la condition droit de scorer                                  */
void dead_ship_param(sprite_t *sprite, int  *gameover, int *score_total,
		     bool *droitDeScorer)
{
  bool dead = false;
 
  if(sprite->life <= 0){
    dead = true;
  } 
  if(dead){
    *droitDeScorer = false;
  }
}
/*Teste si chaque element du tableau est mort.fonctionne pour tout tableau.*/
void dead_tab_param(sprite_t *sprite, sprite_t *big_ast, sprite_t *norm_ast,
		    sprite_t *small_ast, sprite_t *explosion, int *score_total,
		    bool *droitDeScorer)
{
  int i;
  int type = sprite->type;
  int nb = *gimmeIsNb(sprite);
  bool dead = false;
  for(i=0;i<nb;i++){
    if(sprite[i].life <= 0){
      dead = true;    
      if(dead){
	if (type == 1 || type == 2 || type == 3){
	  CreateExplosion(explosion, sprite, i);
	  if(*droitDeScorer){
	    score(score_total, type);
	  }
	}
	DivideAst(sprite, i, big_ast, norm_ast, small_ast);
	kill_sprite(sprite, i);
      }
    }
  }
}
/*Appelle les fonctions permettant de savoir si un sprite est mort, *
 * et de le faire disparaitre si c'est le cas.                      */
void dead(sprite_t *space_ship, sprite_t *big_ast, sprite_t *norm_ast,
	  sprite_t *small_ast, sprite_t *tirs, sprite_t *explosion,
	  int *gameover, int *score_total, bool *droitDeScorer)
{
  dead_ship_param(space_ship, gameover, score_total, droitDeScorer);
  
  dead_tab_param(big_ast, big_ast, norm_ast, small_ast, explosion, score_total,
		 droitDeScorer);
  dead_tab_param(norm_ast, big_ast, norm_ast, small_ast, explosion, score_total,
		 droitDeScorer);
  dead_tab_param(small_ast, big_ast, norm_ast, small_ast, explosion,
		 score_total, droitDeScorer);
  dead_tab_param(tirs, big_ast, norm_ast, small_ast, explosion, score_total,
		 droitDeScorer);
  dead_tab_param(explosion, big_ast, norm_ast, small_ast, explosion,
		 score_total, droitDeScorer);
}


/*Fonction qui teleporte UN sprite si CE sprite rencontre un portal*/
void teleportation(sprite_t *sprite1, sprite_t *portal)
{
  int j;
  for(j=0; j<nbPortal; j++){
    if(compare_position(sprite1, &portal[j])){
      if(j%2 == 0){
	SetUpAtMiddle(sprite1, &portal[j+1]);
	kill_sprite(portal, j+1);
	kill_sprite(portal, j);
      }
      else if(j%2 == 1){
	SetUpAtMiddle(sprite1, &portal[j-1]);
	kill_sprite(portal, j);
	kill_sprite(portal, j-1);
      }
    }
  }
}

void collide_ship_bonus_param(sprite_t *sprite1,  sprite_t *sprite2,
			      bool *bomb_triggered, bool *have_mitraille)
{
  if(sprite2->type == 21){
    if(nbAtomicBomb > 0){
      if(compare_position(sprite1, sprite2)){
	*bomb_triggered = true;
	kill_sprite_number(&nbAtomicBomb);
      }
    }
  }
  if(sprite2->type == 22){
    if(nbMitraille > 0){
      if(compare_position(sprite1, sprite2)){
	Get_Mitraille();
	kill_sprite_number(&nbMitraille);
      }
    }
  }
}

/*Collide pour le ship,  ne pas utiliser de tableau dans sprite 1 !!! *
 * c'est le space_ship en sprite1                                     */
void collide_ship_param(sprite_t *sprite1,  sprite_t *sprite2, bool *cogne,
			int *decompte)
{
  int j;
  int nb2 = *gimmeIsNb(sprite2);
  for(j=0; j<nb2; j++){
    if(compare_position(sprite1, &sprite2[j])){
      sprite1->life -= 1;
      sprite2[j].life -= 1;
      *cogne = true;
      *decompte = DUREE_INV_APP_DEGATS;
      //printf("Ship collide with sprite type : %d \n",sprite2[j].type);
    }
  }
}

/*Tableau en sprite 1 et en sprite2, donnez*/
void collide_tab_param(sprite_t *sprite1,  sprite_t *sprite2)
{
  int i, j;
  int nb1 = *gimmeIsNb(sprite1);
  int nb2 = *gimmeIsNb(sprite2);
  if(nb1>0 && nb2>0){
    for(i=0; i<nb1; i++){  
      for(j=0; j<nb2; j++){
	if(compare_position(&sprite1[i], &sprite2[j])){
	  sprite1[i].life -= 1;
	  sprite2[j].life -= 1;
	}
      }
    }
  }
}



/*Verifie si le tirs ou space_ship est en contact avec big/norm/small_ast*
 *Faites appel a collide_tab_param dans le cas de deux tableau,          *
 *et collide_ship_param dans le cas d'un sprite un tableau               */
void collide(sprite_t *space_ship, sprite_t *tirs, sprite_t *big_ast,
	     sprite_t *norm_ast, sprite_t *small_ast, int *gameover,
	     bool *cogne, int *decompte, sprite_t *bonus_atomic_bomb,
	     bool *bomb_triggered, bool *have_mitraille, sprite_t *mitraille,
	     sprite_t *portal)
{
  collide_tab_param(tirs, big_ast);
  collide_tab_param(tirs, norm_ast);
  collide_tab_param(tirs, small_ast);
   
  collide_ship_param(space_ship, big_ast, cogne, decompte);
  collide_ship_param(space_ship, norm_ast, cogne, decompte);
  collide_ship_param(space_ship, small_ast, cogne, decompte);
  teleportation(space_ship, portal);

  collide_ship_bonus_param(space_ship, bonus_atomic_bomb, bomb_triggered,
			   have_mitraille);
  collide_ship_bonus_param(space_ship, mitraille, bomb_triggered,
			   have_mitraille);
  
}



/*Fonction qui fait apparaitre deux plus petit astéroide *
 * seulement si le type est 1 ou 2                       */
void DivideAst(sprite_t *ast, int numero, sprite_t *big_ast,
	       sprite_t *norm_ast, sprite_t *small_ast)
{
  int type = ast->type;
  int nb_Big_Ast = nbBigAst;
  int nb_Norm_Ast = nbNormAst;
  int nb_Small_Ast = nbSmallAst;
  //printf("Divide Ast: ast type %d \t | nb_Big_ast: %d \t|", type, nb_Big_Ast);
  //printf("nb_Norm_Ast: %d \n nb_Small_Ast %d \n", nb_Norm_Ast, nb_Small_Ast);
  
  
  if(type == 1 && nb_Big_Ast > 0){  
    CreateAst(norm_ast);                                                 
    SetUpAtPosition(&norm_ast[nb_Norm_Ast], &ast[numero]);                        
    if (nb_Norm_Ast+1 < NB_MAX_NORM_AST){                                
      CreateAst(norm_ast);                                              
      SetUpAtPosition(&norm_ast[nb_Norm_Ast+1], &ast[numero]);                   
      InvertDirection(&norm_ast[nb_Norm_Ast], &norm_ast[nb_Norm_Ast+1]);
    }
  }
  if(type == 2 && nb_Norm_Ast > 0){                                 
    CreateAst(small_ast);
    SetUpAtPosition(&small_ast[nb_Small_Ast], &ast[numero]);
    if (nb_Small_Ast+1 < NB_MAX_SMALL_AST){
      CreateAst(small_ast);
      SetUpAtPosition(&small_ast[nb_Small_Ast+1], &ast[numero]);
      InvertDirection(&small_ast[nb_Small_Ast], &small_ast[nb_Small_Ast+1]);
    }
  }
  
}


/*Créé un astéroide par rapport a temps actuel qui compte le *
 * nombre de tours de boucle écoulé depuis  le début du jeu  */
void CreateAstWithTime(sprite_t *big_ast, sprite_t *norm_ast,
		       sprite_t *small_ast)
{
  if (temps_actuel%CHANCE_D_APPARITION_BIG_AST == 0){  
    CreateBigAst(big_ast);                          
  }
  if (temps_actuel%CHANCE_D_APPARITION_NORM_AST == 0){  
    CreateNormAst(norm_ast);                          
  }
  if(temps_actuel%CHANCE_D_APPARITION_SMALL_AST == 0){        
    CreateSmallAst(small_ast);                        
  }

}


/*Fait apparaitre un bonus a l'aide de Rand.*/
void CreateBonusWithTime(sprite_t *bonus_atomic_bomb, sprite_t *mitraille,
			 sprite_t *portal)
{
  int i;
  int j;
  j = rand()%(CHANCE_D_APPARITION_MITRAILLE);
  i = rand()%(CHANCE_D_APPARITION_ATOMIC_BOMBE);
  if(i == 0){
    CreateAtomicBomb(bonus_atomic_bomb);
  }
  if(j == 0){
    CreateMitraille(mitraille);
  }
  i = rand()%(CHANCE_D_APPARITION_PORTAL);
  if(i == 0){
    CreatePortal(portal);
  }
   
}

void change_sprite_ship (sprite_t *ship, SDL_Surface * spaceship,
			 SDL_Surface * spaceship2)
{
  if(ship->sprite_picture == spaceship)
    {
      ship->sprite_picture = spaceship2;
    }
  else
    {
      ship->sprite_picture = spaceship;
    }
}

void Get_Mitraille()
{
  have_mitraille = true;
  bonus_compt = 5000;
}
void Effect_mitraille()
{
  if (bonus_compt > 0)
    {
      can_piou = true;
      bonus_compt--;
    }
}


/////////////////////////////////////////////////////////////////
/* Handle events coming from the user:
   - quit the game?
   - return to agree
   - use left/right to change the orientation of the ship
   - use up/down to move on the ship to the right direction
   - or up/down to move in the menu
   - Space to shoot
   - o to create a new big asteroide
   - i to create a new norm ast
   - u to create a new small ast
   - p : all thing disapeared
   - k to kill a random ast
   - l to divide an ast.
   - t to create projectiles
   - v for various information. 
   - b for nuclear bomb
   - y for ARMAGGEDON
   - e for a tiny explosion
   - n to make a sprite -1 life (choose wich)
   - c to believe you are invincible...but no.
   -sometimes there's an SDL_Delay
   -it because we want thing to go less fast.
*/

  

void HandleEvent(SDL_Event event, int *quit, sprite_t *space_ship, double *accel,
		 sprite_t *big_ast, sprite_t *norm_ast, sprite_t *small_ast,
		 sprite_t *tirs, sprite_t *explosion, bool *play,
		 int *score_total, bool *bomb_triggered)
{
  int i,j;
  switch (event.type) {
    /* close button clicked */
  case SDL_QUIT:
    *quit = 1;
    break;
    
    /* handle the keyboard*/
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_ESCAPE:
    case SDLK_q:
      *quit = 1;
      break;
    case SDLK_k:  //KIll a random ast
      printf("touch k pressed \n");
      i = rand()%(3);
      if (i == 0){
	j = rand()%(NB_MAX_BIG_AST-1);
	kill_sprite(big_ast, j);
      }
      if (i == 1){
	j = rand()%(NB_MAX_NORM_AST);
	kill_sprite(norm_ast, j);
      }
      if (i == 2){
	j = rand()%(NB_MAX_SMALL_AST);
	kill_sprite(small_ast, j);
      }
      // printf("i : %d, j : %d \n",i,j);
      SDL_Delay(100);
      break;
    case SDLK_u:
      //printf("touch u pressed \n");
      CreateAst(small_ast);
      SDL_Delay(100);
      break;
    case SDLK_i:
      // printf("Touch i pressed \n");
      CreateAst(norm_ast);
      SDL_Delay(100);
      break;
    case SDLK_o:
      //printf("Touch o pressed\n");
      CreateAst(big_ast);
      SDL_Delay(100); 
      break;
    case SDLK_p: 
      // printf("Touch p pressed \n");
      kill_sprite_number(&nbBigAst);
      kill_sprite_number(&nbNormAst);
      kill_sprite_number(&nbSmallAst);
      kill_sprite_number(&nbtirs); 
      break;
    case SDLK_e:   //BOOOM
      printf("touch e pressed \n");
      CreateExplosion(explosion, big_ast, 0);
      SDL_Delay(100);
      break;
    case SDLK_y:   
      CreateAst(big_ast);
      CreateAst(norm_ast);
      CreateAst(small_ast);
      break;
    case SDLK_w:  
      printf("touch l pressed \n");
      DivideAst(big_ast, 1, big_ast, norm_ast, small_ast );  
      SDL_Delay(100);
      break;
    case SDLK_x:    
      printf("touch l pressed \n");
      DivideAst(norm_ast, 1, big_ast, norm_ast, small_ast);
      SDL_Delay(100);
      break;
    case SDLK_n:    
      printf("touch n pressed \n");
      i = 0; //numero ast demandé
      j = 1; //nombre de vie retirée
      if(small_ast[i].life > 0){
	small_ast[i].life -= j ;
      }
      SDL_Delay(100);
      break;
    case SDLK_v :
      various_information(space_ship, big_ast, norm_ast, small_ast,
			  score_total);
      SDL_Delay(100);
      break;
    case SDLK_c :
      change_sprite_ship(space_ship, spaceship, spaceship2);
      break;
    case SDLK_b : //BOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOM
      *bomb_triggered = true;
      break;
    default:
      break;
    }
    break;
  }

}
/*Multitouche:     */
void HandleEvent2(SDL_Event event, sprite_t *space_ship, double *accel,
		  int *quit, int Table_move[5], sprite_t *tirs, bool *can_piou)
{
  /* Handle events coming from the user: multitouch: */
  switch(event.type){
  case SDL_QUIT:
    *quit = 1;
    break;
    /* activation des action en appuyant sur les touches*/
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym)
      {
	/* case SLDK_ESCAPE: */
	/* 	*quit = 1; */
	/* 	break; */
      case SDLK_UP:
	Table_move[0] = 1;
	break;
      case SDLK_DOWN:
	Table_move[1] = 1;
	break;
      case SDLK_LEFT:
	Table_move[2] = 1;
	break;
      case SDLK_RIGHT:
	Table_move[3] = 1;
	break;
      case SDLK_SPACE:
	Table_move[4] = 1;
	break;
      default:
	break;
      }
    break;
    /*déactivation des actions en arretant d'appuyer*/
  case SDL_KEYUP:
    switch (event.key.keysym.sym)
      {
      case SDLK_UP:
	Table_move[0] = 0;
	break;
      case SDLK_DOWN:
	Table_move[1] = 0;
	break;
      case SDLK_LEFT:
	Table_move[2] = 0;
	break;
      case SDLK_RIGHT:
	Table_move[3] = 0;
	break;
      case SDLK_SPACE:
	Table_move[4] = 0;
	*can_piou = true;
	break;
      default:
	break;
      }
    break;
  }
  if(Table_move[0] == 1){
    *accel = CONS_ACCEL;
  }
  if(Table_move[1] == 1){
    *accel = -CONS_ACCEL;
  }
  if(Table_move[2] == 1){
    ship_turn_left(space_ship);
  }
  if(Table_move[3] == 1){
    ship_turn_right(space_ship);
  }
  if(Table_move[4] ==1 && *can_piou == true){
    create_piou(tirs, space_ship);
    *can_piou = false;
  }
}

/*Prend en charge la touche entrée*/
void HandleMenuReturn(sprite_t *jouer, sprite_t *quitter, bool *play,
		      int *gameover, int *ending, int *finmenu)
{
  if(jouer->sprite_picture == menu_jouer_selec){
    *play = true;
    *gameover = 0;
    *ending = 1;
  }
  else if(quitter->sprite_picture == menu_quitter_selec){
    *ending = 1;
    *gameover = 1;
    *finmenu = 1;
  }
  else{
    /*Autres options*/
  }
}

/*Gestion du clavier au niveau des menus*/
void HandleEventMenu(SDL_Event event, int *gameover, bool *play, int *ending,
		     int *finmenu, sprite_t *jouer, sprite_t *quitter)
{
  switch (event.type) {
    /* close button clicked */
  case SDL_QUIT:
    *gameover = 1;
    *ending = 1;
    *finmenu = 1;
    break;
  case SDL_KEYUP:
    switch (event.key.keysym.sym)
      {
      case SDLK_ESCAPE:
      case SDLK_q:
	*gameover = 1;
	*ending = 1;
	*finmenu = 1;
	break;
      case SDLK_UP:
      case SDLK_DOWN:
	change_sprite_ship (jouer, menu_jouer, menu_jouer_selec );
	change_sprite_ship (quitter, menu_quitter, menu_quitter_selec );
	break;
      case SDLK_RETURN:
	HandleMenuReturn(jouer, quitter, play, gameover, ending, finmenu);
	break;
      default:
	break;
      }
  default:
    break;
  }
}


///////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
  /*Tout les SDL_Surfaces sont définis en variable globale*/
  /*Definition des différents sprites*/
  sprite_t jouer;      //type 10
  sprite_t quitter;    //type 11
  sprite_t game_over;  //type 12
  sprite_t return_menu; //type 13
  //sprite_t credit; //type 14 ?

  //les highscore avec SDL ttf ?
  sprite_t space_ship;
  sprite_t big_ast[NB_MAX_BIG_AST];
  sprite_t norm_ast[NB_MAX_NORM_AST];
  sprite_t small_ast[NB_MAX_SMALL_AST]; 
  sprite_t tirs[NB_MAX_PIOU];
  sprite_t explosion[NB_MAX_EXPL];

  /*bonus et affichage:*/
  sprite_t PV[MAX_LIFE_SHIP]; //type 20
  sprite_t bonus_atomic_bomb; //type 21
  sprite_t mitraille;  //type 22
  sprite_t portal[NB_MAX_PORTAL]; //type 23 TOUJOURS METTRE NB MAX PAIR


  /*Initialize rand :*/
  srand(time(NULL)); 

  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  TTF_Init();
  
  /*Initialisation de tout ce qui a trait a la musique*/

  /*Definition des variables musicales :*/
  SDL_AudioSpec desired, obtained, soundfile;
  SDL_AudioCVT cvt; 

  /*C'est marrant parce que une freq de 11025 fonctionne quand même*/
  /*Deux format supporté ici : AUDIO_U16SYS et AUDIO_S8 */
  char format[20] = "AUDIO_U16SYS";
  init_musique(&desired, 44100, format, 2, 1024);
  if (musique("KDE_Startup_new.wav",&desired, &obtained, &soundfile,
	      &cvt ) == 1){
    return 1;
  }
  bool son_deces_du_vaisseau_lance;
  bool son_apres_game_over_lance;
  /*****************************************************/

  /* Load the font. */
  TTF_Font *font = TTF_OpenFont("04B_30__.TTF", 32);

  /* set the title bar */
  SDL_WM_SetCaption("Comet Buster", "Comet Buster");
  
  /* create window */
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  
  /* set keyboard repeat */
  SDL_EnableKeyRepeat(10, 10);

  /*Download pictures of all sprites*/
  downloadsprite();
 
  /*Initialise all sprite*/
  init_all_sprite(&space_ship, big_ast, norm_ast, small_ast,
		  tirs, explosion, &game_over, &return_menu,
		  &jouer, &quitter, PV, portal);
  
  int gameover = 0;
  int ending = 0;
  int finmenu = 0;
  bool play = false;
  bool droitDeScorer = true;
  int animationFinale = 0;
  int Table_move[5]={0,0,0,0,0};
  can_piou = true;
  bool bomb_triggered = false;

  cogne = false;
  have_mitraille = false;
  bonus_compt = 0;
  
  /*Les variables utilisée avec SDL_TTF  */
  int ScoreTotal;
  int *score_total;
  score_total = &ScoreTotal;
  *score_total = 0;  //score_total = 0;
  char affichage_score[25] = "Comet Buster !!!"; /* Tableau de char suffisamment grand */
  SDL_Color color = { 255, 255, 255 };
  SDL_Surface *textSurface = TTF_RenderUTF8_Solid(font, affichage_score,
						  color);


  /*Menu :*/
  while (!finmenu){

    /*MENU :*/
    if(!play){
      SDL_Event event2;
      if (SDL_PollEvent(&event2)) {
	HandleEventMenu(event2, &gameover, &play, &ending, &finmenu, &jouer, &quitter);
	
	SDL_BlitSurface(background, NULL, screen, NULL);
	SDL_BlitSurface(jouer.sprite_picture, NULL, screen, &jouer.position);
	SDL_BlitSurface(quitter.sprite_picture, NULL, screen, &quitter.position);
	SDL_BlitSurface(textSurface, NULL, screen, NULL);
	
	SDL_UpdateRect(screen, 0, 0, 0, 0);
      }
    }
    
    /*JEU:*/
    if(play){

      pause_and_close_audio();
      sprintf(format, "AUDIO_S8"); 
      init_musique(&desired, 11025, format, 2, 1024);
      if( musique("Castlevania_Soundtrack_modifie.wav",&desired, &obtained,
		  &soundfile, &cvt ) == 1){
	return 1;
      }

      /* main loop: check events and re-draw the window until the end */
      while (!gameover)
	{	  
	  int i;
	  double accel = 0.0;
	  SDL_Event event;
	  temps_actuel +=1;

	  
	  /* look for an event; possibly update the position and the shape
	   * of the ship. */
	  if (SDL_PollEvent(&event)) {
	    HandleEvent(event, &gameover, &space_ship, &accel, big_ast,
			norm_ast,small_ast, tirs, explosion, &play,
			score_total, &bomb_triggered);
	    HandleEvent2(event, &space_ship, &accel, &gameover, Table_move,
			 tirs, &can_piou);
	  }

	  /*Call new ast and bonus */
	  CreateAstWithTime(big_ast, norm_ast, small_ast);
	  CreateBonusWithTime(&bonus_atomic_bomb, &mitraille, portal);
 
	  /*Look if some sprite need to be boomed*/
	  kill_all_sprite(&space_ship, big_ast, norm_ast,
			  small_ast, tirs, &gameover, &animationFinale, 
			  &bomb_triggered);


	  /* draw the background */
	  SDL_BlitSurface(background, NULL, screen, NULL);
      
	  {
	    /*position, mouvement et acceleration des sprites*/
	    /*draw portal*/
	    move_all_sprite(portal);
	    draw_all_sprite(portal);

	    /*Space_ship*/
	    sprite_boost(&space_ship, accel);
	    sprite_move(&space_ship);

	    SDL_BlitSurface(space_ship.sprite_picture, &space_ship.image,
			    screen, &space_ship.position);
	  
	  
	  /*Affichage des bonus:*/
	  /*Atomic_bomb*/
	  if(*gimmeIsNb(&bonus_atomic_bomb) > 0){
	    SDL_BlitSurface(bonus_atomic_bomb.sprite_picture,
			    NULL, screen, &bonus_atomic_bomb.position);
	  }
	  
	  /*Mitraille*/
	  if(nbMitraille > 0)
	    {
	      SDL_BlitSurface(mitraille.sprite_picture, NULL, screen,
			      &mitraille.position);
	    }
	  
	  /*draw Big Asteroid*/
	  move_all_sprite(big_ast);
	  draw_all_sprite(big_ast);	  

	  /*draw norm asteroid*/
	  move_all_sprite(norm_ast);
	  draw_all_sprite(norm_ast);

	  /*draw small asteroid*/
	  move_all_sprite(small_ast);
	  draw_all_sprite(small_ast);	  

	  /*Draw EXPLOSION*/ 
	  move_all_sprite(explosion);
	  draw_all_sprite(explosion);
	  decompte_and_destroy_sprite(explosion, DECOMPTE_MORT_EXPLOSION);
      
	  /*Draw projectile (piou)*/
	  move_all_sprite(tirs);
	  draw_all_sprite_one_image(tirs);
	  decompte_and_destroy_sprite(tirs, PORTEE_PIOU);

	  
	  /*Draw PV*/
	  for (i = 0; i<space_ship.life ; i++)
	    {
	      SDL_BlitSurface(PV->sprite_picture, NULL, screen, &PV[i].position);
	    }

	  }
	  
	  /*Collision*/
	  if (cogne == false){ 
	    collide(&space_ship, tirs, big_ast, norm_ast, small_ast, &gameover,
		    &cogne, &decompte, &bonus_atomic_bomb, &bomb_triggered,
		    &have_mitraille, &mitraille, portal);
	    dead(&space_ship, big_ast, norm_ast, small_ast, tirs, explosion,
		 &gameover, score_total, &droitDeScorer);
	  }
	  else {
	    decompte--;
	    change_sprite_ship(&space_ship, spaceship, spaceship2);
	    can_piou = false;
	    bonus_compt = 0;
	    if (decompte <1)
	      {
		cogne = false;
	      }
	    dead(&space_ship, big_ast, norm_ast, small_ast, tirs, explosion,
		 &gameover, score_total, &droitDeScorer);
	  }
	  
	  Effect_mitraille();

	  /*Update the score:*/
	  sprintf(affichage_score, "Score : %d", *score_total);
	  SDL_Surface *textSurface = TTF_RenderUTF8_Solid(font, affichage_score,
							  color);
	  SDL_BlitSurface(textSurface, NULL, screen, NULL);
	  SDL_FreeSurface(textSurface);
	  
	  /* update the screen */
	  SDL_UpdateRect(screen, 0, 0, 0, 0);

	  /*Gameover music*/
	  if(space_ship.life == 0){
	    if(!son_deces_du_vaisseau_lance){
	      
	      pause_and_close_audio();
	      sprintf(format, "AUDIO_S8"); 
	      init_musique(&desired, 44100, format, 1, 1024);
	      if(musique("8-Bit-SFX_Explosion_10.wav",&desired, &obtained, &soundfile, &cvt ) == 1){
		return 1;
	      }
	      son_deces_du_vaisseau_lance = true;
	    }
	  }
	  
	  /*End of while of the game*/
	}
       
      ending = 0;
      
      /*End of if(play)*/
    }
    if(gameover){
      
      /*Ending music*/ 
      pause_and_close_audio();
      sprintf(format, "AUDIO_S8"); 
      init_musique(&desired, 11025, format, 2, 1024);
      if(musique("game_over_coupe.wav",&desired, &obtained, &soundfile, &cvt ) == 1){
	return 1;
      }

      /*Refresh the whole game except the score_total*/
      play = false;
      space_ship.life = MAX_LIFE_SHIP;
      SetUpPosition(&space_ship);
      kill_all_number();
      temps_actuel = 0;
      printf("Commandant ! voici votre score : %d \n", *score_total);
      droitDeScorer = true;

      while(!ending){
	
	/*Insert function of menu here (blitsurface...)*/
	
	SDL_Event event3;
	if (SDL_PollEvent(&event3)) {
	  HandleEventMenu(event3, &gameover, &play, &ending, &finmenu, &jouer, &quitter);
	}
	SDL_BlitSurface(background, NULL, screen, NULL);
	SDL_BlitSurface(jouer.sprite_picture, NULL, screen, &jouer.position);
	SDL_BlitSurface(quitter.sprite_picture, NULL, screen, &quitter.position);
	SDL_BlitSurface(game_over.sprite_picture, NULL, screen, &game_over.position);
	
	/*Affichage score*/
	sprintf(affichage_score, "Score : %d", *score_total);
	SDL_Surface *textSurface = TTF_RenderUTF8_Solid(font, affichage_score,
							color);
	SDL_BlitSurface(textSurface, NULL, screen, NULL);
	SDL_FreeSurface(textSurface);
	
	SDL_UpdateRect(screen, 0, 0, 0, 0);

	
	if (soundpos >= soundlength){
	  if(!son_apres_game_over_lance){
	    pause_and_close_audio();
	    if( musique("apres_game_over.wav",&desired, &obtained,
			&soundfile, &cvt ) == 1){
	      return 1;
	    }
	    son_apres_game_over_lance = true;
	  }
	}
	
      }
      
      /*Refresh the score and refresh bool son_lance*/
      *score_total = 0;
      son_deces_du_vaisseau_lance = false;
      son_apres_game_over_lance = false;
    }
    /*End of while menu*/
  }
  
  pause_and_close_audio();
   
  /* clean up */
  SDL_FreeSurface(portal_picture);
  SDL_FreeSurface(textSurface);
  SDL_FreeSurface(menu_jouer);
  SDL_FreeSurface(menu_jouer_selec);
  SDL_FreeSurface(menu_quitter);
  SDL_FreeSurface(menu_quitter_selec);
  SDL_FreeSurface(menu_return);
  SDL_FreeSurface(menu_game_over);
  SDL_FreeSurface(vie);
  SDL_FreeSurface(bullet);
  SDL_FreeSurface(small_comet);
  SDL_FreeSurface(norm_comet);
  SDL_FreeSurface(big_comet);
  SDL_FreeSurface(spaceship);
  SDL_FreeSurface(spaceship2);
  SDL_FreeSurface(background);
  SDL_FreeSurface(screen);

  /* Free the font. */
  TTF_CloseFont(font);

  /* Cleanup SDL and SDL_ttf. */
  SDL_Quit();
  TTF_Quit();

  return 0;
  
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
  portal_picture = download_sprite_("portail.bmp");
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
