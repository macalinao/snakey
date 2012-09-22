build:
	gcc -Wall -c snakey.c -o snakey.o
	gcc snakey.o -o snakey -lncurses -lportaudio bloopsaphone/libbloopsaphone.a
	rm snakey.o
