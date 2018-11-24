CC=gcc
CFLAGS=-Iinclude -ansi -Werror -Wall -pedantic
SDIR=src
TDIR=test
BDIR=build

all: hbconv hbconv_tt

hbconv: $(SDIR)/hbconv/*.c
	$(CC) $(CFLAGS) -o $(BDIR)/$@ $^

hbconv_tt: $(SDIR)/$(TDIR)/*.c
	$(CC) $(CFLAGS) -o $(BDIR)/$(TDIR)/$@ $^