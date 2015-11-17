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
/* $Id: maddEx.c,v 2.0 2003/02/22 15:49:16 judd Exp $ */
#include<vsip.h>
#include<VU.h>

int main(){
vsip_init((void*)0);{
    vsip_mview_f *A = vsip_mcreate_f(3,4,VSIP_COL,0);
    vsip_mview_f *B = vsip_mcreate_f(3,4,VSIP_ROW,0);
    vsip_mview_f *CB = vsip_mcreate_f(8,9,VSIP_ROW,0);
    vsip_mview_f *C = vsip_msubview_f(CB,2,3,3,4);
    vsip_vview_f *a = vsip_mcolview_f(A,0);
    vsip_vputlength_f(a,12);
    vsip_vramp_f(1,.05,a);
    printf("A = ");VU_mprintm_f("5.2",A);
    vsip_smadd_f(2,A,B);
    printf("B = 2+A =");VU_mprintm_f("5.2",B);
    vsip_madd_f(A,B,C);
    printf("A+B =");VU_mprintm_f("5.2",C);
    vsip_mneg_f(A,A);
    printf("Neg A -> A =");VU_mprintm_f("5.2",A);
    printf("C = ");VU_mprintm_f("5.2",C);
    vsip_madd_f(A,C,C);
    printf("A + C -> C =");VU_mprintm_f("5.2",C);
    vsip_mrecip_f(A,A);
    printf("A recip ->A ="); VU_mprintm_f("5.2",A);
    vsip_madd_f(A,C,C);
    printf("A + C -> C =");VU_mprintm_f("5.3",C);
    }vsip_finalize((void*)0);return 0;
}
