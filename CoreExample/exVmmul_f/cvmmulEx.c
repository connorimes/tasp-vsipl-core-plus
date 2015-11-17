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
/* $Id: cvmmulEx.c,v 2.0 2003/02/22 15:34:00 judd Exp $ */

#include<stdio.h>
#include<vsip.h>
#include<VU.h>

int main(){vsip_init((void*)0);
{
   FILE *vfptr = fopen("cvector.data","r");
   FILE *mfptr = fopen("cmatrix.data","r");
   vsip_cmview_f *B = vsip_cmcreate_f(3,5,VSIP_ROW,0);
   vsip_cmview_f *R = vsip_cmcreate_f(3,5,VSIP_ROW,0);
   vsip_cvview_f *a = vsip_cvcreate_f(5,0);
   VU_cvreadf_f(vfptr,a);
   VU_cmreadf_f(mfptr,B);
   fclose(vfptr); fclose(mfptr);
   vsip_cvmmul_f(a,B,VSIP_ROW,R);
   printf("a = "); VU_cvprintm_f("6.2",a);
   printf("B = "); VU_cmprintm_f("6.2",B);
   printf("R = "); VU_cmprintm_f("6.2",R);
   { /* test for VSIP_COL */
     vsip_cmview_f *BT = vsip_cmtransview_f(B);
     vsip_cmview_f *RT = vsip_cmtransview_f(R);
     vsip_cvmmul_f(a,BT,VSIP_COL,RT);
     printf("a = "); VU_cvprintm_f("6.2",a);
     printf("BT = "); VU_cmprintm_f("6.2",BT);
     printf("RT = "); VU_cmprintm_f("6.2",RT);
     vsip_cmdestroy_f(BT);
     vsip_cmdestroy_f(RT);
   }
   vsip_cvalldestroy_f(a);
   vsip_cmalldestroy_f(B);
   vsip_cmalldestroy_f(R);
   } vsip_finalize((void*)0); return 0;
}

