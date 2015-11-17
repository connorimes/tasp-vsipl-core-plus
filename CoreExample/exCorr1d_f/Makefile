## CREATED RJudd 
## SPAWARSYSCEN
## $Id: Makefile,v 2.0 2003/02/22 15:42:00 judd Exp $

## Top Level of library distribution
## RDIR=$(HOME)/local
RDIR=../..
## C compiler
CC=cc
INCLUDEDIR=-I$(RDIR)/include
LIBDIR=-L$(RDIR)/lib
LIBS=-lVU -lvsip -lm
OPTIONS=-O2

all: corr1dEx ccorr1dEx
corr1dEx: corr1dEx.c
	$(CC) -o corr1dEx corr1dEx.c $(OPTIONS) $(INCLUDEDIR) $(LIBDIR) $(LIBS)

ccorr1dEx: ccorr1dEx.c
	$(CC) -o ccorr1dEx ccorr1dEx.c $(OPTIONS) $(INCLUDEDIR) $(LIBDIR) $(LIBS)

clean:
	rm -f corr1dEx ccorr1dEx corr1dEx.exe ccorr1dEx.exe
