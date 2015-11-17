## RJudd
## SPAWARSYSCEN San Diego
## $Id: Makefile,v 2.0 2003/02/22 15:46:14 judd Exp $

## Top Level of library distribution
## Underneath Root Directory (RDIR) we expect a "lib" which includes
## libvsip.a (or whatever it is named) and the VSIP User functions
## included with the distribution in libVU.a (or whatever it is named).
## Also under RDIR should be a "include" directory with vsip.h and VU.h
## in it. This assumes you do things the way I do. There are other ways
## for people who know more than I; feel free.
## RDIR=$(HOME)/local
RDIR=../..
## C compiler
CC=cc
INCLUDEDIR=-I$(RDIR)/include
LIBDIR=-L$(RDIR)/lib
LIBS=-lVU -lvsip -lm
OPTIONS=-O2

OBJECTS = cgempEx cgempNTEx cgempTNEx cgempTTEx cgempNHEx cgempHNEx \
cgempHHEx cgempCHEx cgempHCEx cgempCCEx

all:$(OBJECTS)

cgempEx:cgempEx.c
	$(CC) -o cgempEx cgempEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

cgempNTEx:cgempNTEx.c
	$(CC) -o cgempNTEx cgempNTEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

cgempTNEx:cgempTNEx.c
	$(CC) -o cgempTNEx cgempTNEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

cgempTTEx:cgempTTEx.c
	$(CC) -o cgempTTEx cgempTTEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

cgempNHEx:cgempNHEx.c
	$(CC) -o cgempNHEx cgempNHEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

cgempHNEx:cgempHNEx.c
	$(CC) -o cgempHNEx cgempHNEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

cgempHHEx:cgempHHEx.c
	$(CC) -o cgempHHEx cgempHHEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

cgempCHEx:cgempCHEx.c
	$(CC) -o cgempCHEx cgempCHEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

cgempHCEx:cgempHCEx.c
	$(CC) -o cgempHCEx cgempHCEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

cgempCCEx:cgempCCEx.c
	$(CC) -o cgempCCEx cgempCCEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

clean:
	rm -f $(OBJECTS) *.exe
