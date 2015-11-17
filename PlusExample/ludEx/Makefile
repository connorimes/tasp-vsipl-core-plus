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
## $Id: Makefile,v 2.0 2003/02/22 15:49:14 judd Exp $

CC=cc 
INCLUDE=-I../../include -I../../include/privateC
DEFINES=
OPTIONS=-O2 -Wall -ansi -pedantic
LIBRARY=-L../../lib
libraries= -lVU_c -lvsip_c -lm

COMPILE=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINES) $(OPTIONS)

all: ludEx lud2Ex clud2Ex vsip_ludEx vsip_ludLEx vsip_cludLEx

vsip_cludLEx:vsip_cludLEx.c
	$(COMPILE) -o vsip_cludLEx vsip_cludLEx.c $(libraries)

vsip_ludLEx:vsip_ludLEx.c
	$(COMPILE) -o vsip_ludLEx vsip_ludLEx.c $(libraries)

vsip_ludEx:vsip_ludEx.c
	$(COMPILE) -o vsip_ludEx vsip_ludEx.c $(libraries)

VIludLEx:VIludLEx.c
	$(COMPILE) -o VIludLEx VIludLEx.c $(libraries)

VIludEx:VIludEx.c
	$(COMPILE) -o VIludEx VIludEx.c $(libraries)

ludEx:ludEx.c
	$(COMPILE) -o ludEx ludEx.c $(libraries)

lud2Ex:lud2Ex.c
	$(COMPILE) -o lud2Ex lud2Ex.c $(libraries)

clud2Ex:clud2Ex.c
	$(COMPILE) -o clud2Ex clud2Ex.c $(libraries)

clean:
	rm -f vsip_ludEx VIludEx ludEx lud2Ex clud2Ex vsip_ludLEx VIludLEx
