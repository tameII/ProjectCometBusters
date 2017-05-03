SRC=com_bust.c
BIN=com_bust

$(BIN): $(SRC) physique.o
	gcc -Wall -g -std=c99 $(SRC) `sdl-config  --cflags --libs` -o $(BIN) physique.o -lm
physique.o: physique.c physique.h
	gcc -Wall -Wextra -pedantic -g -std=c99 -c `sdl-config --cflags --libs` -lm -O3 physique.c
clean:
	rm -f $(BIN)
