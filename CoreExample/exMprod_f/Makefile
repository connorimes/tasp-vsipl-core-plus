## RJudd
## SPAWARSYSCEN San Diego
## $Id: Makefile,v 2.0 2003/02/22 15:38:22 judd Exp $

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

all: mvprodEx vmprodEx cmprodhEx cmprodtEx mprodtEx cmprodjEx cmprodEx mprodEx \
     cvmprodEx cmvprodEx
	
cmvprodEx:cmvprodEx.c
	$(CC) -o cmvprodEx cmvprodEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

cvmprodEx:cvmprodEx.c
	$(CC) -o cvmprodEx cvmprodEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

vmprodEx:vmprodEx.c
	$(CC) -o vmprodEx vmprodEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

mvprodEx:mvprodEx.c
	$(CC) -o mvprodEx mvprodEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

mprodEx:mprodEx.c
	$(CC) -o mprodEx mprodEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

cmprodEx:cmprodEx.c
	$(CC) -o cmprodEx cmprodEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

cmprodtEx:cmprodtEx.c
	$(CC) -o cmprodtEx cmprodtEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

cmprodjEx:cmprodjEx.c
	$(CC) -o cmprodjEx cmprodjEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

cmprodhEx:cmprodhEx.c
	$(CC) -o cmprodhEx cmprodhEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

mprodtEx:mprodtEx.c
	$(CC) -o mprodtEx mprodtEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

clean:
	rm -f cmprodhEx  mprodtEx cmprodtEx  cmprodjEx cmprodEx mprodEx \
              mvprodEx vmprodEx cvmprodEx cmvprodEx *.exe
