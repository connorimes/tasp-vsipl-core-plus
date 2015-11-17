## RJudd
## SPAWARSYSCEN San Diego
## $Id: Makefile,v 2.0 2003/02/22 15:46:19 judd Exp $

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

all:corr1dEx ccorr1dEx

corr1dEx:corr1dEx.c
	$(CC) -o corr1dEx corr1dEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

ccorr1dEx:ccorr1dEx.c
	$(CC) -o ccorr1dEx ccorr1dEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

clean:
	rm -f ccorr1dEx corr1dEx ccorr1dEx.exe corr1dEx.exe
