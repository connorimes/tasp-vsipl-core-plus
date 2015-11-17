## CREATED RJudd 
## SPAWARSYSCEN D881 
## $Id: Makefile,v 2.0 2003/02/22 15:42:03 judd Exp $

## Top Level of library distribution
## RDIR=$(HOME)/local
RDIR=../..
## C compiler
CC=cc
INCLUDEDIR=-I$(RDIR)/include
LIBDIR=-L$(RDIR)/lib
LIBS=-lVU -lvsip -lm
OPTIONS=-O2

all: choldEx ccholdEx cludEx

choldEx:choldEx.c
	$(CC) -o choldEx choldEx.c $(OPTIONS) $(INCLUDEDIR) $(LIBDIR) $(LIBS)

ccholdEx:ccholdEx.c
	$(CC) -o ccholdEx ccholdEx.c $(OPTIONS) $(INCLUDEDIR) $(LIBDIR) $(LIBS)

## cludEx is the same as ccholdEx except it uses compulex LUD to solve the problem
cludEx:cludEx.c
	$(CC) -o cludEx cludEx.c $(OPTIONS) $(INCLUDEDIR) $(LIBDIR) $(LIBS)

clean:
	rm -f choldEx ccholdEx cludEx choldEx.exe ccholdEx.exe cludEx.exe
