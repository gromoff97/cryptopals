CC=gcc
CFLAGS=-Iinclude -ansi -Werror -Wall -pedantic -g
SDIR=src
TDIR=test
BDIR=build

all: hbconv hbconv_tt

hbconv: $(SDIR)/hbconv/core.c $(SDIR)/hbconv/hbconv.c
	$(CC) $(CFLAGS) -o $(BDIR)/$@ $^

hbconv_tt: $(SDIR)/hbconv/core.c $(SDIR)/$(TDIR)/hbconv_tt.c
	$(CC) $(CFLAGS) -o $(BDIR)/$(TDIR)/$@ $^