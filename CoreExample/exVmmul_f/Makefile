## RJudd
## SPAWARSYSCEN San Diego
## $Id: Makefile,v 2.0 2003/02/22 15:34:00 judd Exp $

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

all:vmmulEx rvcmmulEx cvmmulEx
	

vmmulEx:vmmulEx.c
	$(CC) -o vmmulEx vmmulEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

rvcmmulEx:rvcmmulEx.c
	$(CC) -o rvcmmulEx rvcmmulEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

cvmmulEx:cvmmulEx.c
	$(CC) -o cvmmulEx cvmmulEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

clean:
	rm -f vmmulEx rvcmmulEx cvmmulEx  vmmulEx.exe rvcmmulEx.exe cvmmulEx.exe 
