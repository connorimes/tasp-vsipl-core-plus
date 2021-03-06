/**********************************************************************
// For TASP VSIPL Documentation and Code neither the United States    /
// Government, the United States Navy, nor any of their employees,    /
// makes any warranty, express or implied, including the warranties   /
// of merchantability and fitness for a particular purpose, or        /
// assumes any legal liability or responsibility for the accuracy,    /
// completeness, or usefulness of any information, apparatus,         /
// product, or process disclosed, or represents that its use would    /
// not infringe privately owned rights                                /
**********************************************************************/
/* $Id: tv.c,v 2.0 2003/02/22 15:46:43 judd Exp $ */

#include<stdio.h>
#include<vsip.h>
#include<VU.h>
int main(){vsip_init((void*)0);
{
   FILE *fptr = fopen("tv.data","r");
   vsip_vview_d *M = vsip_vcreate_d(6,0);
   VU_vreadf_d(fptr,M);
   VU_vprintm_d("6.4",M);
   }vsip_finalize((void*)0);return 0;
}
