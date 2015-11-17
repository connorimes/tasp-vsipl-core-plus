## Top Makefile for VSIP Core double
## Created by RJudd February 15, 1999
## SPAWARSYSCEN D881
## This work is the work of a government employee as part of his official duties
##
MAKE=make
CC=cc
INCLUDE=-I../include
OPTIONS=-O2 -Wall -ansi -pedantic
AR=ar
AR_OPTIONS=rcvs
ARLIB=libVU_c.a
COMPILE=$(CC) $(OPTIONS)
performance:
	(cd utility/print; $(MAKE) MAKE=$(MAKE) COMPILE='$(COMPILE)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIB)' obj)
	(cd utility/read; $(MAKE) MAKE=$(MAKE) COMPILE='$(COMPILE)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIB)' obj)
	(cd utility/timer; $(MAKE) MAKE=$(MAKE) COMPILE='$(COMPILE)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIB)' obj)
	(cd utility/print; $(MAKE) MAKE=$(MAKE) COMPILE='$(COMPILE)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIB)' arch)
	(cd utility/read; $(MAKE) MAKE=$(MAKE) COMPILE='$(COMPILE)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIB)' arch)
	(cd utility/timer; $(MAKE) MAKE=$(MAKE) COMPILE='$(COMPILE)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIB)' arch)

clean:
	(cd utility/print; $(MAKE) MAKE=$(MAKE) clean) 
	(cd utility/read; $(MAKE) MAKE=$(MAKE) clean) 
	(cd utility/timer; $(MAKE) MAKE=$(MAKE) clean) 
