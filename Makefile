CC=gcc
CFLAGS=-Iinclude -ansi -Werror -Wall -pedantic -g
SDIR=src
TDIR=test
BDIR=build

all: hbconv hbconv_tt

hbconv: $(SDIR)/hbconv/core.c $(SDIR)/hbconv/hbconv.c
	[ -d $(BDIR) ] || mkdir $(BDIR)
	$(CC) $(CFLAGS) -o $(BDIR)/$@ $^

hbconv_tt: $(SDIR)/hbconv/core.c $(SDIR)/$(TDIR)/hbconv_tt.c
	[ -d $(BDIR)/$(TDIR) ] || mkdir -p $(BDIR)/$(TDIR)
	$(CC) $(CFLAGS) -o $(BDIR)/$(TDIR)/$@ $^
