SRC=ttftest.c
BIN=ttftest

$(BIN): $(SRC)
	gcc -Wall -g -std=c99 $(SRC) `sdl-config --cflags --libs` -L$(HOME)/Espace-de-depot/methodo/SDL2_ttf-2.0.14 -l SDL_ttf -o $(BIN)

clean:
	rm -f $(BIN)
 
