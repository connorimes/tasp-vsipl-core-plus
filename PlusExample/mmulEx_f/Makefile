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
## $Id: Makefile,v 2.0 2003/02/22 15:49:20 judd Exp $
CC=cc 

mmulEx:mmulEx.c
	$(CC) -o mmulEx mmulEx.c -L../../lib -I../../include -lVU_c -lvsip_c -lm

clean:
	rm -f mmulEx *.exe
