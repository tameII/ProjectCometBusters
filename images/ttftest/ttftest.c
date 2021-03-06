#include <SDL.h>
#include <SDL_ttf.h>

int main( int argc, char* argv[] )
{
  const char *text = "Hello, world!";

  /* Initialize SDL and SDL_ttf. */
  SDL_Init(SDL_INIT_VIDEO); 
  TTF_Init();

  /* Load the font. */
  TTF_Font *font = TTF_OpenFont("A Love of Thunder.ttf", 64);

  /* Compute the size of the rendered text. */
  int w, h;
  TTF_SizeUTF8(font, text, &w, &h);

  /* Set the title bar. */
  SDL_WM_SetCaption("SDL_ttf test", "SDL_ttf test");

  /* Create the window. */
  SDL_Surface *screen = SDL_SetVideoMode(w, h, 0, 0);

  SDL_Event event;
  int quit = 0;

  /* Main loop: check events and re-draw the window until the end. */
  while (!quit)
  {
    /* Look for an event. */
    if (SDL_PollEvent(&event)) {
      /* An event was found. */
      switch (event.type) {
        /* Close button clicked. */
        case SDL_QUIT:
          quit = 1;
          break;

        /* Handle the keyboard */
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
            case SDLK_q:
              quit = 1;
              break;
            /* Do nothing for other keys. */
            default:
              break;
          }
          break;
      }
    }

    /* Fill the screen with black. */
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

    /* Render the text into a surface. */
    SDL_Color color = { 255, 255, 255 };
    SDL_Surface *textSurface = TTF_RenderUTF8_Solid(font, text, color);

    /* Copy the rendered text to the screen. */
    SDL_BlitSurface(textSurface, NULL, screen, NULL);

    /* Free the rendered text surface. */
    SDL_FreeSurface(textSurface);

    /* Update the screen. */
    SDL_UpdateRect(screen, 0, 0, 0, 0);
  }

  /* Free the font. */
  TTF_CloseFont(font);

  /* Cleanup SDL and SDL_ttf. */
  SDL_Quit();
  TTF_Quit();

  return 0;
}
