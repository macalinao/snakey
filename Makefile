all: clean build

build:
	mkdir -p build/
	mkdir -p dist/

	# Build files the hard way
	gcc -Wall -c src/keyboard.c -o build/keyboard.o
	gcc -Wall -c src/screen.c -o build/screen.o
	gcc -Wall -c src/snakey.c -o build/snakey.o
	gcc -Wall -c src/sound.c -o build/sound.o
	gcc -Wall -c src/state_title.c -o build/state_title.o

	# Final build
	gcc build/*.o -o dist/snakey -lncurses -lportaudio bloopsaphone/libbloopsaphone.a

clean:
	rm -rf build/
	rm -rf dist/
