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
/* $Id: cmexpEx.c,v 2.0 2003/02/22 15:49:08 judd Exp $ */
#include<stdio.h>
#include<vsip.h>
#include<VU.h>

int main(){
vsip_init((void*)0);{
    vsip_cmview_f *A = vsip_cmcreate_f(16,16,VSIP_ROW,0);
    vsip_cmview_f *a = vsip_cmsubview_f(A,0,0,4,4);
    vsip_cmview_f *B = vsip_cmcreate_f(16,16,VSIP_ROW,0);
    vsip_cmview_f *b = vsip_cmsubview_f(B,0,0,4,4);
    vsip_scalar_f user_data[2*16*16],*ud;
    vsip_cblock_f *cblock = vsip_cblockbind_f(
                 user_data,(vsip_scalar_f*)NULL,2*16*16,0);
    vsip_cmview_f *c = vsip_cmbind_f(cblock,4,10,5,2,4);
    /* Compact 4x4 matrix data_even_even out of place */
    FILE *fptr = fopen("data_even_even","r");
    vsip_cblockadmit_f(cblock,VSIP_FALSE);
    printf("test cmexp\n");
    printf("work matricies are sub views of VSIPL \n");
    printf("row major (unit stride) matricies of size 16x16\n");
    printf("row major, row even, col even out of place\n");
    
    /* unit stride row data even even */
    printf("offset 0,0\n");
    VU_cmreadf_f(fptr,a); fclose(fptr);
    printf("input matrix\n"); VU_cmprintm_f("6.4",a);
    vsip_cmexp_f(a,b);
    printf("input matrix after operation\n");VU_cmprintm_f("6.4",a);
    printf("output matrix\n"); VU_cmprintm_f("6.4",b);
    /* inplace */
    printf("Compact, row major, row even, col even in place\n");
    vsip_cmexp_f(a,a);
    printf("output of inplace\n"); VU_cmprintm_f("6.4",a);

    /* unit stride data_odd_odd out of place */
    printf("row major, row_length odd, col_length odd, out of place\n");
    printf("offset 1,0 for input\n");
    printf("offset 0,5 for output\n");
    vsip_cmdestroy_f(a); vsip_cmdestroy_f(b);
    a=vsip_cmsubview_f(A,1,0,5,5); b = vsip_cmsubview_f(B,0,3,5,5);
    fptr = fopen("data_odd_odd","r"); VU_cmreadf_f(fptr,a); fclose(fptr);
    printf("input matrix\n"); VU_cmprintm_f("6.4",a);
    vsip_cmexp_f(a,b);
    printf("input matrix after operation\n");VU_cmprintm_f("6.4",a);
    printf("output matrix\n"); VU_cmprintm_f("6.4",b);
    vsip_cmexp_f(a,a);
    printf("output of inplace\n"); VU_cmprintm_f("6.4",a);

    /* User data array interleaved for input array */
    printf("row major, row even, col odd, out of place\n");
    printf("input user block \n");
    printf("offset 4,col_stride 10, row_stride 2 for input\n");
    printf("offset 0,5 for output\n");
    vsip_cmdestroy_f(b);
    b = vsip_cmsubview_f(B,0,3,5,4);
    fptr = fopen("data_odd_even","r"); VU_cmreadf_f(fptr,c); fclose(fptr);
    printf("input matrix\n"); VU_cmprintm_f("6.4",c);
    vsip_cmexp_f(c,b);
    printf("input matrix after operation\n");VU_cmprintm_f("6.4",c);
    printf("output matrix\n"); VU_cmprintm_f("6.4",b);
    vsip_cmexp_f(c,c);
    printf("output of inplace (user block)\n"); VU_cmprintm_f("6.4",c);
    /* clean up */
    vsip_cblockrelease_f(cblock,VSIP_FALSE,&ud,&ud);
    vsip_cmdestroy_f(a);
    vsip_cmdestroy_f(b);
    vsip_cmalldestroy_f(A);
    vsip_cmalldestroy_f(B);
    vsip_cmalldestroy_f(c);
    }vsip_finalize((void*)0);return 0;
}
