## RJudd
## SPAWARSYSCEN San Diego
## $Id: Makefile,v 2.0 2003/02/22 15:40:23 judd Exp $

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

OBJECTS = gempEx gempTNEx gempNTEx gempTTEx

all:$(OBJECTS)

gempEx:	gempEx.c
	$(CC) -o gempEx gempEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

gempTNEx:gempTNEx.c
	$(CC) -o gempTNEx gempTNEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

gempTTEx:gempTTEx.c
	$(CC) -o gempTTEx gempTTEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

gempNTEx:gempNTEx.c
	$(CC) -o gempNTEx gempNTEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

clean:
	rm -f $(OBJECTS) *.exe
