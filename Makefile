CC=gcc
CFLAGS=-ansi -Werror -Wall -pedantic

hbconv: src/hbconv.c
	$(CC) -o build/hbconv src/hbconv.c $(CFLAGS)