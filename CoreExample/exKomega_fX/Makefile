## RJudd
## SPAWARSYSCEN San Diego
## $Id: Makefile,v 2.0 2003/02/22 15:39:19 judd Exp $

## Top Level of library distribution
## Underneath Root Directory (RDIR) we expect a "lib" which includes
## libvsip.a (or whatever it is named) and the VSIP User functions
## included with the distribution in libVU.a (or whatever it is named).
## Also under RDIR should be a "include" directory with vsip.h and VU.h
## in it. This assumes you do things the way I do. There are other ways
## for people who know more than I; feel free.

##Directory where X11R6 lives
RXDIR=/usr/X11R6
## Directory where VSIPL lives
RDIR=../..
## C compiler
CC=cc
INCLUDEDIR=-I$(RDIR)/include -I$(RXDIR)/include
LIBDIR=-L$(RDIR)/lib -L$(RXDIR)/lib
## NOTE THAT libVUX.a is not available as default. Read './README/ and build first
LIBS=-lVUX -lVU -lvsip -lX11 -lm
OPTIONS=-O2

CFLAGS  =   $(OPTFLAGS) $(INCLUDE_DIR) 
EXECS =  komegaEx

default: $(EXECS)

komegaEx :komegaEx.c
	$(CC) -o komegaEx komegaEx.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

clean:
	rm -f komegaEx komegaEx.exe
