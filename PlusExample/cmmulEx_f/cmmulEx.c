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
/* $Id: cmmulEx.c,v 2.0 2003/02/22 15:49:11 judd Exp $ */
#include<vsip.h>
#include<VU.h>

int main(){
vsip_init((void*)0);{
    vsip_cmview_f *A  = vsip_cmcreate_f(3,4,VSIP_ROW,0);
    vsip_cmview_f *B  = vsip_cmcreate_f(3,4,VSIP_COL,0);
    vsip_cmview_f *CB = vsip_cmcreate_f(8,9,VSIP_ROW,0);
    vsip_cmview_f *C  = vsip_cmsubview_f(CB,2,3,3,4);
    vsip_cvview_f *a  = vsip_cmrowview_f(A,0);
    vsip_cvputlength_f(a,12);
    { vsip_vview_f *a_r = vsip_vrealview_f(a);
      vsip_vview_f *a_i = vsip_vimagview_f(a);
      vsip_vramp_f(1,.05,a_r);
      vsip_vramp_f(2,.11, a_i);
      vsip_vdestroy_f(a_r); vsip_vdestroy_f(a_i);
    }
    printf("A = ");VU_cmprintm_f("6.3",A);
    vsip_rscmmul_f(2,A,B);
    printf("2 * A -> B =");VU_cmprintm_f("6.3",B);
    vsip_csmmul_f(vsip_cmplx_f(1,2),B,B);
    printf("(1+2i) * B -> B = "); VU_cmprintm_f("6.3",B);
    vsip_cmrecip_f(A,C);
    printf("Recip(A) -> C =");VU_cmprintm_f("6.3",C);
    vsip_cmmul_f(C,A,C);
    printf("C * A -> C ="); VU_cmprintm_f("6.3",C);
    vsip_cmconj_f(A,C);
    vsip_cmmul_f(A,C,C);
    printf("conj(A) -> C; A * C -> C ="); VU_cmprintm_f("6.3",C);
    vsip_cmmul_f(A,A,A);
    printf(" A * A -> A ="); VU_cmprintm_f("6.3",A);
    }vsip_finalize((void*)0);return 0;
}
