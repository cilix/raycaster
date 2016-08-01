CC=gcc
HEADERS=/usr/local/include
LIB=/usr/local/lib
WARNS=-Wall -ansi -pedantic -std=c89

main:
	$(CC) -I $(HEADERS) -L $(LIB) -lSDL2 src/*.c $(WARNS) -O3 -o game

run:
	make && ./game

clean:
	rm game
