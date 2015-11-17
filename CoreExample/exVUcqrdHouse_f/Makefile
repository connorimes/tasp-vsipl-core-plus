## RJudd
## SPAWARSYSCEN San Diego
## $Id: Makefile,v 2.0 2003/02/22 15:35:57 judd Exp $

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
CFILES= cqrdex.c VU_chouseqr_f.c VU_chouse_f.c VU_cmprodq_f.c VU_cmprodqh_f.c  \
VU_rscvmprod_f.c  VU_copu_f.c VU_chopu_f.c VU_copuh_f.c VU_rscjvmprod_f.c \
VU_cqprodm_f.c VU_rscjmvprod_f.c VU_rscmvprod_f.c VU_cqhprodm_f.c

all:cqrdex

cqrdex:$(CFILES)
	$(CC) -o cqrdex $(CFILES) $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) $(LIBS)

clean:
	rm -f cqrdex cqrdex.exe
