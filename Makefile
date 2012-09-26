,PHONY: all
all: clean build

.PHONY: build
build:
	mkdir -p build/
	mkdir -p dist/

	for f in src/*.c; do \
		gcc -Wall -c $${f} -o build/$$(basename $${f}).o; \
	done

	# Final build
	gcc build/*.o -o dist/snakey -lncurses -lportaudio bloopsaphone/libbloopsaphone.a

.PHONY: clean
clean:
	rm -rf build/
	rm -rf dist/
