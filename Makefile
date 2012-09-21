build:
	gcc -c snakey.c -o snakey.o
	gcc snakey.o -o snakey -lncurses
	rm snakey.o
