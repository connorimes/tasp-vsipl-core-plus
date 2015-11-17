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
/* $Id: vmmulEx.c,v 2.0 2003/02/22 15:46:50 judd Exp $ */

#include<stdio.h>
#include<vsip.h>
#include<VU.h>

int main(){vsip_init((void*)0);
{
   FILE *vfptr = fopen("vector.data","r");
   FILE *mfptr = fopen("matrix.data","r");
   vsip_mview_d *B = vsip_mcreate_d(3,5,VSIP_ROW,0);
   vsip_mview_d *R = vsip_mcreate_d(3,5,VSIP_ROW,0);
   vsip_vview_d *a = vsip_vcreate_d(5,0);
   VU_vreadf_d(vfptr,a);
   VU_mreadf_d(mfptr,B);
   fclose(vfptr); fclose(mfptr);
   vsip_vmmul_d(a,B,VSIP_ROW,R);
   printf("a = "); VU_vprintm_d("6.2",a);
   printf("B = "); VU_mprintm_d("6.2",B);
   printf("R = "); VU_mprintm_d("6.2",R);
   { /* test for VSIP_COL */
     vsip_mview_d *BT = vsip_mtransview_d(B);
     vsip_mview_d *RT = vsip_mtransview_d(R);
     vsip_vmmul_d(a,BT,VSIP_COL,RT);
     printf("a = "); VU_vprintm_d("6.2",a);
     printf("BT = "); VU_mprintm_d("6.2",BT);
     printf("RT = "); VU_mprintm_d("6.2",RT);
     vsip_mdestroy_d(BT);
     vsip_mdestroy_d(RT);
   }
   vsip_valldestroy_d(a);
   vsip_malldestroy_d(B);
   vsip_malldestroy_d(R);
   }vsip_finalize((void*)0);return 0;
}

