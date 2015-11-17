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
/* $Id: cvmmulEx.c,v 2.0 2003/02/22 15:46:50 judd Exp $ */

#include<stdio.h>
#include<vsip.h>
#include<VU.h>

int main(){vsip_init((void*)0);
{
   FILE *vfptr = fopen("cvector.data","r");
   FILE *mfptr = fopen("cmatrix.data","r");
   vsip_cmview_d *B = vsip_cmcreate_d(3,5,VSIP_ROW,0);
   vsip_cmview_d *R = vsip_cmcreate_d(3,5,VSIP_ROW,0);
   vsip_cvview_d *a = vsip_cvcreate_d(5,0);
   VU_cvreadf_d(vfptr,a);
   VU_cmreadf_d(mfptr,B);
   fclose(vfptr); fclose(mfptr);
   vsip_cvmmul_d(a,B,VSIP_ROW,R);
   printf("a = "); VU_cvprintm_d("6.2",a);
   printf("B = "); VU_cmprintm_d("6.2",B);
   printf("R = "); VU_cmprintm_d("6.2",R);
   { /* test for VSIP_COL */
     vsip_cmview_d *BT = vsip_cmtransview_d(B);
     vsip_cmview_d *RT = vsip_cmtransview_d(R);
     vsip_cvmmul_d(a,BT,VSIP_COL,RT);
     printf("a = "); VU_cvprintm_d("6.2",a);
     printf("BT = "); VU_cmprintm_d("6.2",BT);
     printf("RT = "); VU_cmprintm_d("6.2",RT);
     vsip_cmdestroy_d(BT);
     vsip_cmdestroy_d(RT);
   }
   vsip_cvalldestroy_d(a);
   vsip_cmalldestroy_d(B);
   vsip_cmalldestroy_d(R);
   }vsip_finalize((void*)0);return 0;
}

