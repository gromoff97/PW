CC=gcc
C_DEPS=src/autopic.c src/argcheck.c
H_DEPS=include/*
BUILD_DIR=build
CFLAGS=-I include -std=c11 -ftrapv -fverbose-asm -pedantic -Wall -Werror

main: $(C_DEPS) $(H_DEPS)
	$(CC) -o $(BUILD_DIR)/$@ $(CFLAGS) $(C_DEPS)
