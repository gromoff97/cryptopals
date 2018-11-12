CC=gcc
CFLAGS=-ansi -Werror -Wall -pedantic
SDIR=src
BDIR=build

hbconv: src/hbconv.c
	$(CC) $(CFLAGS) -o build/$@ $<