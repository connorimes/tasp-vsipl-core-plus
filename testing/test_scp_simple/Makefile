## Created RJudd */
## SPAWARSYSCEN */
##*********************************************************************
## For TASP VSIPL Documentation and Code neither the United States    /
## Government, the United States Navy, nor any of their employees,    /
## makes any warranty, express or implied, including the warranties   /
## of merchantability and fitness for a particular purpose, or        /
## assumes any legal liability or responsibility for the accuracy,    /
## completeness, or usefulness of any information, apparatus,         /
## product, or process disclosed, or represents that its use would    /
## not infringe privately owned rights                                /
##********************************************************************/
## $Id: Makefile,v 2.0 2003/02/22 15:23:20 judd Exp $
CC=cc
RDIR=../..
INCLUDE=-I$(RDIR)/include
LIB=-L$(RDIR)/lib
VSIPLIB=-lvsip
VULIB=-lVU
FFTWLIB=

test_all: test_all.c *.h
	$(CC) -o test_all test_all.c $(LIB) $(INCLUDE) $(VULIB) $(VSIPLIB) -lm

test_scp: test_scp.c *.h
	$(CC) -o test_scp test_scp.c $(LIB) $(INCLUDE) $(VULIB) $(VSIPLIB) -lm

atest: atest.c *.h
	$(CC) -o atest atest.c $(LIB) $(INCLUDE) $(VULIB) $(VSIPLIB) -lm

clean:
	rm -f atest test_all test_scp
