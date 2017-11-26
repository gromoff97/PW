CC=gcc
C_DEPS=src/C/mainfile.c src/C/argcheck.c src/C/watcher.c
SH_DEPS=src/SH/defpic.sh
H_DEPS=include/argchecker.h include/watcher.h
BUILD_DIR=build
CFLAGS=-I include -std=c11 -ftrapv -fverbose-asm -pedantic -Wall -Werror

main: $(C_DEPS) $(H_DEPS) $(SH_DEPS)
	$(CC) -o $(BUILD_DIR)/$@ $(CFLAGS) $(C_DEPS)
