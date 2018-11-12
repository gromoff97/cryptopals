CC=gcc
CFLAGS=-ansi -Werror -Wall -pedantic

hbconv: src/hbconv.c
	$(CC) $(CFLAGS) -o build/$@ $<