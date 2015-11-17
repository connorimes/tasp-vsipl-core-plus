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
/* $Id: cmaddEx.c,v 2.0 2003/02/22 15:49:06 judd Exp $ */
#include<vsip.h>
#include<VU.h>

int main(){
vsip_init((void*)0);{
    vsip_cmview_f *A = vsip_cmcreate_f(3,4,VSIP_COL,0);
    vsip_cmview_f *B = vsip_cmcreate_f(3,4,VSIP_ROW,0);
    vsip_cmview_f *CB = vsip_cmcreate_f(8,9,VSIP_ROW,0);
    vsip_cmview_f *C = vsip_cmsubview_f(CB,2,3,3,4);
    vsip_cvview_f *a = vsip_cmcolview_f(A,0);
    vsip_cvputlength_f(a,12);
    { vsip_vview_f *a_r = vsip_vrealview_f(a);
      vsip_vview_f *a_i = vsip_vimagview_f(a);
      vsip_vramp_f(1,.05,a_r);
      vsip_vramp_f(2,.11, a_i);
      vsip_vdestroy_f(a_r); vsip_vdestroy_f(a_i);
    }
    printf("A = ");VU_cmprintm_f("6.3",A);
    vsip_rscmadd_f(2,A,B);
    printf("2+A -> B =");VU_cmprintm_f("6.3",B);
    vsip_cmadd_f(A,B,C);
    printf("A+B -> C =");VU_cmprintm_f("6.3",C);
    vsip_cmneg_f(A,A);
    printf("Neg A -> A =");VU_cmprintm_f("6.3",A);
    vsip_csmadd_f(vsip_cmplx_f(1,2),C,C);
    printf("(1+2i) + C -> C =");VU_cmprintm_f("6.3",C);
    vsip_cmsqrt_f(C,A);
    printf(" sqrt(C) -> A =");VU_cmprintm_f("6.3",A);
    vsip_cmsqrt_f(C,C);
    printf(" sqrt(C) -> C =");VU_cmprintm_f("6.3",C);
    { vsip_mview_f *A_r = vsip_mrealview_f(A);
      vsip_rcmadd_f(A_r,B,B);
      printf("Real A + B -> B =");VU_cmprintm_f("6.3",B);
      vsip_rcmadd_f(A_r,A,A);
      printf("Real A + A -> A =");VU_cmprintm_f("6.3",A);
      vsip_mdestroy_f(A_r);
    }
    vsip_cmconj_f(A,C);
    printf("conj(A) -> C =");VU_cmprintm_f("6.3",C);
    vsip_cmadd_f(A,C,C);
    printf("A + C -> C =");VU_cmprintm_f("6.3",C);
    vsip_cmsqrt_f(C,A);
    printf(" sqrt(C) -> A =");VU_cmprintm_f("6.3",A);
    vsip_cmsqrt_f(C,C);
    printf(" sqrt(C) -> C =");VU_cmprintm_f("6.3",C);
    } vsip_finalize((void*)0);return 0;
}
