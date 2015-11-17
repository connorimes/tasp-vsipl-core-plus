## RJudd
## SPAWARSYSCEN San Diego
## $Id: Makefile,v 2.0 2003/02/22 15:46:24 judd Exp $

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

SOURCES= VU_printstdout_d.c \
VU_scanstdin_d.c \
VU_cprintstdout_d.c \
VU_cscanstdin_d.c
OBJECTS= VU_printstdout_d.o \
VU_scanstdin_d.o \
VU_cprintstdout_d.o \
VU_cscanstdin_d.o

all:$(OBJECTS) firEx cfirEx 

firEx:firEx.c $(OBJECTS)
	$(CC) -o firEx firEx.c $(OBJECTS) $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

cfirEx:cfirEx.c $(OBJECTS)
	$(CC) -o cfirEx cfirEx.c $(OBJECTS) $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

$(OBJECTS):$(SOURCES)
	$(CC) -c $(OPTIONS) $(SOURCES) $(INCLUDEDIR)

clean:
	rm -f firEx cfirEx $(OBJECTS) *.exe
