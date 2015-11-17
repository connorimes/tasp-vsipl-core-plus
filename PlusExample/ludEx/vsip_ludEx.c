/* Created RJudd */
/* SPAWARSYSCEN D857 */
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
/* $Id: vsip_ludEx.c,v 2.0 2003/02/22 15:49:14 judd Exp $ */
#include<vsip.h>
#include<VU.h>

int main() {  
vsip_init((void*)0);{
   vsip_mview_f *A = vsip_mcreate_f(3,3,VSIP_ROW,VSIP_MEM_NONE);
   vsip_mview_f *B = vsip_mcreate_f(3,2,VSIP_ROW,VSIP_MEM_NONE);
   vsip_lu_f *lud = vsip_lud_create_f(3);
   vsip_mput_f(A,0,0,3); vsip_mput_f(A,0,1,17); vsip_mput_f(A,0,2, 10);
   vsip_mput_f(A,1,0,2); vsip_mput_f(A,1,1, 4); vsip_mput_f(A,1,2, -2);
   vsip_mput_f(A,2,0,6); vsip_mput_f(A,2,1,18); vsip_mput_f(A,2,2,-12);
   vsip_mput_f(B,0,0,1); vsip_mput_f(B,0,1,2);
   vsip_mput_f(B,1,0,3); vsip_mput_f(B,1,1,-1);
   vsip_mput_f(B,2,0,5); vsip_mput_f(B,2,1,-2);
   printf("A = "); VU_mprintm_f("7.4",A);
   printf("B = "); VU_mprintm_f("7.4",B);
   vsip_lud_f(lud,A);
   printf("Adec = "); VU_mprintm_f("7.4",A);
   vsip_lusol_f(lud,VSIP_MAT_TRANS,B);
   printf("B = "); VU_mprintm_f("7.4",B);
   } vsip_finalize((void*)0);return 0;
}
