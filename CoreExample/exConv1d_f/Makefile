## CREATED RJudd 
## SPAWARSYSCEN
## $Id: Makefile,v 2.0 2003/02/22 15:42:04 judd Exp $

## Top Level of library distribution
## RDIR=$(HOME)/local
RDIR=../..
## C compiler
CC=cc
INCLUDEDIR=-I$(RDIR)/include
LIBDIR=-L$(RDIR)/lib
LIBS=-lVU -lvsip -lm
OPTIONS=-O2

conv1dEx:conv1dEx.c
	$(CC) -o conv1dEx conv1dEx.c $(OPTIONS) $(INCLUDEDIR) $(LIBDIR) $(LIBS)

clean:
	rm -f conv1dEx conv1dEx.exe
