all: install

install:
	gcc -std=gnu99 -o game_of_life game_of_life.c -lm
test:
	./game_of_life
clean:
	rm game_of_life

