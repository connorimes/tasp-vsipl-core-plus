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
## $Id: Makefile,v 2.0 2003/02/22 15:49:23 judd Exp $
CC=cc 

all:tt_si tt_i tt tt_d ctt ctt_d

tt_si:tt_si.c
	$(CC) -o tt_si tt_si.c -L../../lib -I../../include -lVU_c -lvsip_c -lm

tt_i:tt_i.c
	$(CC) -o tt_i tt_i.c -L../../lib -I../../include -lVU_c -lvsip_c -lm

tt:tt.c
	$(CC) -o tt tt.c -L../../lib -I../../include -lVU_c -lvsip_c -lm

tt_d:tt_d.c
	$(CC) -o tt_d tt_d.c -L../../lib -I../../include -lVU_c -lvsip_c -lm

ctt:ctt.c
	$(CC) -o ctt ctt.c -L../../lib -I../../include -lVU_c -lvsip_c -lm

ctt_d:ctt_d.c
	$(CC) -o ctt_d ctt_d.c -L../../lib -I../../include -lVU_c -lvsip_c -lm

clean:
	rm -f ctt ctt_d tt tt_d tt_i tt_si
