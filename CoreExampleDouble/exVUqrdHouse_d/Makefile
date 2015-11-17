## RJudd
## SPAWARSYSCEN San Diego
## $Id: Makefile,v 2.0 2003/02/22 15:46:48 judd Exp $

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

CFILES=VU_houseqr_d.c VU_house_d.c VU_opu_d.c VU_svmprod_d.c VU_qprodm_d.c \
VU_mprodq_d.c VU_qtprodm_d.c VU_mprodqt_d.c VU_smvprod_d.c

all:qrdex qrdprodex

qrdprodex:qrdprodex.c
	$(CC) -o qrdprodex qrdprodex.c $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)


qrdex: qrdex.c $(CFILES)
	$(CC) -o qrdex qrdex.c $(CFILES) $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

clean:
	rm -f qrdex qrdprodex
