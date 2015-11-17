## RJudd
## SPAWARSYSCEN San Diego
## $Id: Makefile,v 2.0 2003/02/22 15:37:47 judd Exp $

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

all: qrdEx qrd2Ex cqrdEx cqrd2Ex

qrdEx:qrdEx.c
	$(CC) -o qrdEx qrdEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

qrd2Ex:qrd2Ex.c
	$(CC) -o qrd2Ex qrd2Ex.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

cqrdEx:cqrdEx.c
	$(CC) -o cqrdEx cqrdEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

cqrd2Ex:cqrd2Ex.c
	$(CC) -o cqrd2Ex cqrd2Ex.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

qrd2_test:qrd2_test.c
	$(CC) -o qrd2_test qrd2_test.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

clean:
	rm -f qrdEx     qrd2Ex     cqrd2Ex     cqrdEx     qrd2_test.exe \
              qrdEx.exe qrd2Ex.exe cqrd2Ex.exe cqrdEx.exe qrd2_test.exe
