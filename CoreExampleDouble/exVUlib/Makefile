## RJudd
## SPAWARSYSCEN San Diego
## $Id: Makefile,v 2.0 2003/02/22 15:46:43 judd Exp $

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

all:tv tm tcv tcm

tv:tv.c
	$(CC) -o tv tv.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

tm:tm.c
	$(CC) -o tm tm.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

tcv:tcv.c
	$(CC) -o tcv tcv.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

tcm:tcm.c
	$(CC) -o tcm tcm.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

clean:
	rm -f tv tm tcv tcm tv.exe tm.exe tcv.exe tcm.exe
