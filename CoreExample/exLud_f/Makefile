## RJudd
## SPAWARSYSCEN San Diego
## $Id: Makefile,v 2.0 2003/02/22 15:39:15 judd Exp $

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

all: lud3Ex ludEx lud2Ex clud2Ex clud3Ex

ludEx:	ludEx.c
	$(CC) -o ludEx ludEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

lud2Ex:	lud2Ex.c
	$(CC) -o lud2Ex lud2Ex.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

lud3Ex:	lud3Ex.c
	$(CC) -o lud3Ex lud3Ex.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

clud2Ex: clud2Ex.c
	$(CC) -o clud2Ex clud2Ex.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

clud3Ex: clud3Ex.c
	$(CC) -o clud3Ex clud3Ex.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

clean:
	rm -f lud3Ex clud3Ex ludEx lud2Ex clud2Ex \
        lud3Ex.exe clud3Ex.exe ludEx.exe lud2Ex.exe clud2Ex.exe
