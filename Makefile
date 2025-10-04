.PHONY: all chip8 run clear

all: chip8

chip8: main.c init/init.c
	@gcc main.c init/init.c -o main
	@./main

run: main
	@./main

clear:
	@rm -f main