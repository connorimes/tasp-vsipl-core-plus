## RJudd
## SPAWARSYSCEN San Diego
## $Id: Makefile,v 2.0 2003/02/22 15:39:22 judd Exp $

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

all:cgemsCEx cgemsHEx cgemsTEx cgemsEx gemsEx gemsTEx

cgemsCEx:cgemsCEx.c
	$(CC) -o cgemsCEx cgemsCEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

cgemsHEx:cgemsHEx.c
	$(CC) -o cgemsHEx cgemsHEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

cgemsTEx:cgemsTEx.c
	$(CC) -o cgemsTEx cgemsTEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

cgemsEx:cgemsEx.c
	$(CC) -o cgemsEx cgemsEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

gemsEx:	gemsEx.c
	$(CC) -o gemsEx gemsEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

gemsTEx:gemsTEx.c
	$(CC) -o gemsTEx gemsTEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

clean:
	rm -f cgemsCEx cgemsHEx cgemsTEx cgemsEx gemsEx gemsTEx *.exe
