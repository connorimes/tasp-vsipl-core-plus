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
/* $Id: mmulEx.c,v 2.0 2003/02/22 15:49:20 judd Exp $ */
#include<vsip.h>
#include<VU.h>

int main(){
vsip_init((void*)0);{
    vsip_mview_f *A = vsip_mcreate_f(3,4,VSIP_ROW,0);
    vsip_mview_f *B = vsip_mcreate_f(3,4,VSIP_COL,0);
    vsip_mview_f *CB = vsip_mcreate_f(8,9,VSIP_ROW,0);
    vsip_mview_f *C = vsip_msubview_f(CB,2,3,3,4);
    vsip_vview_f *a = vsip_mrowview_f(A,0);
    vsip_vputlength_f(a,12);
    vsip_vramp_f(1,.05,a);
    printf("A = ");VU_mprintm_f("5.2",A);
    vsip_mrecip_f(A,B);
    printf("A recip ->B =");VU_mprintm_f("5.2",B);
    vsip_mmul_f(A,B,C);
    printf("A * B -> C =");VU_mprintm_f("5.2",C);
    vsip_smmul_f(2,C,C);
    printf("2 * C -> C =");VU_mprintm_f("5.2",C);
    }vsip_finalize((void*)0);return 0;
}
