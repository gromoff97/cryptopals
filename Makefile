CC=gcc
CFLAGS=-Iinclude -ansi -Werror -Wall -pedantic
SDIR=src
BDIR=build

hbconv: $(SDIR)/hbconv/*.c
	$(CC) $(CFLAGS) -o $(BDIR)/$@ $^