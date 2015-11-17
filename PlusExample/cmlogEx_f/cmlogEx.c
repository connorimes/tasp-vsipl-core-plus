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
/* $Id: cmlogEx.c,v 2.0 2003/02/22 15:49:10 judd Exp $ */
#include<stdio.h>
#include<vsip.h>
#include<VU.h>

int main(){
vsip_init((void*)0);{
    vsip_cmview_f *A = vsip_cmcreate_f(16,16,VSIP_ROW,0);
    vsip_cmview_f *a = vsip_cmsubview_f(A,0,0,4,4);
    vsip_cmview_f *B = vsip_cmcreate_f(16,16,VSIP_ROW,0);
    vsip_cmview_f *b = vsip_cmsubview_f(B,0,0,4,4);
    /* Compact 4x4 matrix data_even_even out of place */
    FILE *fptr = fopen("data_even_even","r");
    printf("test cmlog\n");
    printf("Compact, row major, row even, col even out of place\n");
    VU_cmreadf_f(fptr,a); fclose(fptr);
    printf("input matrix\n"); VU_cmprintm_f("6.4",a);
    vsip_cmlog_f(a,b);
    printf("input matrix after operation\n");VU_cmprintm_f("6.4",a);
    printf("output matrix\n"); VU_cmprintm_f("6.4",b);
    /* inplace */
    printf("Compact, row major, row even, col even in place\n");
    vsip_cmlog_f(a,a);
    printf("output of inplace\n"); VU_cmprintm_f("6.4",a);

    /* unit stride data_odd out of place */
/*    printf("unit stride data odd out of place\n");
    vsip_cvputlength_f(a,5);
    vsip_cvputlength_f(b,5);
    fptr = fopen("data_odd","r");
    VU_cvreadf_f(fptr,a);
    fclose(fptr);
    printf("input vector\n"); VU_cvprintm_f("6.4",a);
    vsip_cvlog_f(a,b);
    printf("input vector after operation\n");VU_cvprintm_f("6.4",a);
    printf("output vector\n"); VU_cvprintm_f("6.4",b); */

    /* input stride 1 output stride 2 */
/*    printf("input stride 1 output stride 2\n");
    vsip_cvputstride_f(b,2);
    fptr = fopen("data_odd","r"); VU_cvreadf_f(fptr,a); fclose(fptr);
    vsip_cvlog_f(a,b);
    printf("output vector\n"); VU_cvprintm_f("6.4",b); */

    /* input stride 2 output stride 3 */
/*    printf("input stride 2 output stride 3\n");
    vsip_cvputstride_f(a,2);
    vsip_cvputstride_f(b,3);
    fptr = fopen("data_odd","r"); VU_cvreadf_f(fptr,a); fclose(fptr);
    vsip_cvlog_f(a,b);
    printf("output vector\n"); VU_cvprintm_f("6.4",b); */

    /* input stride 2 output stride 1 */
/*    printf("input stride 2 output stride 1\n");
    vsip_cvputstride_f(a,2);
    vsip_cvputstride_f(b,1);
    fptr = fopen("data_odd","r"); VU_cvreadf_f(fptr,a); fclose(fptr);
    vsip_cvlog_f(a,b);
    printf("output vector\n"); VU_cvprintm_f("6.4",b);*/

    /* in place stride 2 */
/*    printf("in place stride 2\n");
    fptr = fopen("data_odd","r"); VU_cvreadf_f(fptr,a); fclose(fptr);
    vsip_cvlog_f(a,a);
    printf("output vector\n"); VU_cvprintm_f("6.4",a); */

    /* clean up */
    vsip_cmdestroy_f(a);
    vsip_cmdestroy_f(b);
    vsip_cmalldestroy_f(A);
    vsip_cmalldestroy_f(B);
    }vsip_finalize((void*)0);return 0;
}
