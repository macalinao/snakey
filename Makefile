all: clean build

build:
	mkdir -p build/
	mkdir -p dist/
	gcc -Wall -c src/snakey.c -o build/snakey.o
	gcc build/snakey.o -o dist/snakey -lncurses -lportaudio bloopsaphone/libbloopsaphone.a

clean:
	rm -rf build/
	rm -rf dist/
