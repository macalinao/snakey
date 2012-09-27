.DEFAULT_GOAL: all
.PHONY: all
all: clean build

.PHONY: build
build:
	@echo Recreating folders...
	@mkdir -p build/
	@mkdir -p dist/

	@echo Compiling...
	@for f in src/*.c; do \
		gcc -Wall -c $${f} -o build/$$(basename -s .c $${f}).o; \
	done

	@echo Linking and creating executable...
	@gcc build/*.o -o dist/snakey -lncurses -lportaudio bloopsaphone/libbloopsaphone.a

	@echo Done.

.PHONY: clean
clean:
	@echo Cleaning...
	@rm -rf build/
	@rm -rf dist/

.PHONY: deps
deps:
	@echo Compiling dependencies...
	@git submodule update --init
	@cd bloopsaphone; make

.PHONY: exec
exec:
	@./dist/snakey
