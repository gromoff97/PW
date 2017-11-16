main: src/autopic.c
	gcc -o build/main -std=c11 -ftrapv -fverbose-asm -pedantic -Wall -Werror src/autopic.c
