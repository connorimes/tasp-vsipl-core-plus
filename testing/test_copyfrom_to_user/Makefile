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
## $Id: Makefile,v 1.1 2007/04/18 04:10:03 judd Exp $ */
CC=cc
DIR=../..
INCLUDE=$(DIR)/include
LIB=$(DIR)/lib
VSIPLIB=-lvsip
VULIB=-lVU
FFTWLIB=

atest: atest.c *.h
	$(CC) -o atest atest.c -L$(LIB) -I$(INCLUDE) $(VULIB) $(VSIPLIB) $(FFTWLIB) -lm

clean:
	rm -f atest
