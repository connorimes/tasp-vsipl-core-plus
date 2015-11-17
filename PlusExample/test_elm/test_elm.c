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
/* $Id: test_elm.c,v 2.0 2003/02/22 15:49:22 judd Exp $ */
#include<vsip.h>
#include<VU.h>

int main(int argc, char *argv[]){
vsip_init((void*)0);
if(argc < 3){printf("usage >test_elm 3 4 A_3_4.data\n"); exit(0);}
{
    vsip_mview_f *A = vsip_mcreate_f(3,4,VSIP_ROW,VSIP_MEM_NONE);
    vsip_mview_f *A0 = vsip_mcreate_f(3,4,VSIP_ROW,VSIP_MEM_NONE);
    vsip_mview_f *B = vsip_mcreate_f(3,4,VSIP_ROW,VSIP_MEM_NONE);
    vsip_mview_f *C = vsip_mcreate_f(3,4,VSIP_ROW,VSIP_MEM_NONE);
    FILE *Afptr = fopen(argv[3],"r");
    VU_mreadf_f(Afptr,A);
    fclose(Afptr);

    vsip_smmul_f(M_PI,A,A);
    vsip_mcopy_f_f(A,A0);
    printf("A = ");VU_mprintm_f("6.4",A);
    vsip_mcos_f(A,A);
    printf("cos(A) = A =");VU_mprintm_f("6.4",A);
    vsip_macos_f(A,C);
    printf("acos(A) = C = ");VU_mprintm_f("6.4",C);
    
    vsip_msin_f(C,C);
    printf("sin(C) = C =");VU_mprintm_f("6.4",C);
    
    vsip_masin_f(C,B);
    printf("asin(C) = B =");VU_mprintm_f("6.4",B);

    vsip_mmul_f(A,A,A); vsip_mmul_f(C,C,C); vsip_madd_f(A,C,C);
    printf("A^2 + C^2 = C");VU_mprintm_f("6.4",C);
    
    vsip_mcopy_f_f(B,A);
    printf("A = ");VU_mprintm_f("6.4",A);
    vsip_mtan_f(A,A);
    printf("tan(A) = A =");VU_mprintm_f("6.4",A);
    vsip_matan_f(A,A);
    printf("atan(A) = A =");VU_mprintm_f("6.4",A);
   
    vsip_smmul_f(2.0,A0,A0);
    printf("A0 = ");VU_mprintm_f("6.4",A0);
    vsip_msin_f(A0,A); vsip_mcos_f(A0,B);
    printf("sin(A0) = A =");VU_mprintm_f("6.4",A);
    printf("cos(A0) = B =");VU_mprintm_f("6.4",B);
    vsip_matan2_f(A,B,C);
    printf("atan2(A,B) = C"); VU_mprintm_f("6.4",C);

    printf("A0 = ");VU_mprintm_f("6.4",A0);
    vsip_mexp_f(A0,A);
    printf("exp(A0) = A");VU_mprintm_f("6.4",A);
    vsip_mlog_f(A,B);
    printf("log(A) = B");VU_mprintm_f("6.4",B);
    vsip_mexp10_f(A0,A);
    printf("exp10(A0) = A");VU_mprintm_f("6.4",A);
    vsip_mlog10_f(A,B);
    printf("log10(A) = B");VU_mprintm_f("6.4",B);

    vsip_msqrt_f(A0,A);
    printf("sqrt(A0) = A =");VU_mprintm_f("6.4",A);

    vsip_mcosh_f(A0,A);
    printf("cosh(A0) = A =");VU_mprintm_f("6.4",A);

    vsip_msinh_f(A0,A);
    printf("sinh(A0) = A =");VU_mprintm_f("6.4",A);

    vsip_mtanh_f(A0,A);
    printf("tanh(A0) = A =");VU_mprintm_f("6.4",A);

    }vsip_finalize((void*)0);return 0;
}
