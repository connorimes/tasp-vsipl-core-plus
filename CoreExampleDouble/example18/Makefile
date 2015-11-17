## Created RJudd
## SPAWARSYSCEN San Diego
## $Id: Makefile,v 1.1 2003/04/22 02:17:53 judd Exp $

## Top Level of library distribution
## RDIR=$(HOME)/local
RDIR=../..
## C compiler
CC=cc
INCLUDEDIR=-I$(RDIR)/include
LIBDIR=-L$(RDIR)/lib
LIBS=-lVU -lvsip -lm
OPTIONS=-O2

example: example18.c
	$(CC) -o example18 example18.c $(OPTIONS) $(INCLUDEDIR) $(LIBDIR) $(LIBS) 

clean:
	rm -f example18 example18.exe
