CC=gcc
CFLAGS=-Iinclude -ansi -Werror -Wall -pedantic
SDIR=src
TDIR=test
BDIR=build

hbconv: $(SDIR)/hbconv/*.c
	$(CC) $(CFLAGS) -o $(BDIR)/$@ $^