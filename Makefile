CC=gcc
CFLAGS=-ansi -Werror -Wall -pedantic
SDIR=src
BDIR=build

hbconv: $(SDIR)/hbconv/hbconv.c
	$(CC) $(CFLAGS) -o $(BDIR)/$@ $<