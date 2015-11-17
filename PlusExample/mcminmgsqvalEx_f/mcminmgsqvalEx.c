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
/* $Id: mcminmgsqvalEx.c,v 2.0 2003/02/22 15:49:19 judd Exp $ */
#include<stdio.h>
#include<vsip.h>
#include<VU.h>

int main(){
vsip_init((void*)0);{
    vsip_cmview_f *A = vsip_cmcreate_f(16,16,VSIP_ROW,0);
    vsip_cmview_f *a = vsip_cmsubview_f(A,0,0,4,4);
    vsip_cmview_f *B = vsip_cmcreate_f(16,16,VSIP_ROW,0);
    vsip_cmview_f *b = vsip_cmsubview_f(B,0,0,4,4);
    vsip_scalar_mi index;
    vsip_scalar_f ans;
    /* Compact 4x4 matrix data_even_even */
    FILE *fptr = fopen("data_even_even","r");
    printf("test mcminmgsqval\n");
    printf("Compact, row major, row even, col even out of place\n");
    VU_cmreadf_f(fptr,a); fclose(fptr);
    printf("input matrix\n"); VU_cmprintm_f("6.4",a);
    ans = vsip_mcminmgsqval_f(a,&index);
    printf("input matrix after operation\n");VU_cmprintm_f("6.4",a);
    printf("ans = %6.4f; index = (row) %ld (col) %ld\n",ans,index.r,index.c);


    /* clean up */
    vsip_cmdestroy_f(a);
    vsip_cmdestroy_f(b);
    vsip_cmalldestroy_f(A);
    vsip_cmalldestroy_f(B);
    }vsip_finalize((void*)0);return 0;
}
