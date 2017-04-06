Pour l'astéroide on à :

SDL_Surface *big_comet;
sprite_t big_ast;
SDL_Rect bigCometPosition

void SetUpPosition(sprite_t *sprite, SDL_Surface *surface, 
SDL_Rect *rectPosition);

void CreateBigComet(sprite_t *big_ast, SDL_Surface *big_comet, 
SDL_Rect *bigCometPosition)
{
SetUpPosition(big_ast, big_comet, bigCometPosition);
sprite_init(big_ast, 1, big_comet, BIG_AST_SIZE, NB_BIG_AST_SPRITE);
sprite_boost(big_ast, VIT_BIG_AST);
}

début 
|
|L'image de météore est stockée dans big_comet (SDL_Surface)
|colorkey de big_comet est effacée (255, 0, 255)
|
|
|
|big_comet->clip_rect.x = NULL;
|big_comet->clip_rect.y = NULL;
|
|
|
|
||||||||||MOTEUR
|(-on rentre dans la boucle )
||-si event clavier o :
|||	thereisacomet = true
|||	createBigComet( big_ast, big_comet, bigCometPosition);
||-fin si
||
||sprite_move(&big_ast);
||bigCometPosition.x = big_ast.col;
||bigCometPosition.y = big_ast.lig;
||
||Si thereisacomet = true alors
||SDL_BlitSurface(big_comet, NULL, screen, &bigCometPosition);
||
|(-Fin de la boucle)
||||||||||FIN MOTEUR
| 
|
|
|
|SDL_FreeSurface(big_comet);
|
|fin.

