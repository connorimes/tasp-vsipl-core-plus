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
/* $Id: cvlogEx.c,v 2.0 2003/02/22 15:49:12 judd Exp $ */
#include<stdio.h>
#include<vsip.h>
#include<VU.h>

int main(){
vsip_init((void*)0);{
    vsip_cvview_f *A = vsip_cvcreate_f(16,0);
    vsip_cvview_f *a = vsip_cvsubview_f(A,0,4);
    vsip_cvview_f *B = vsip_cvcreate_f(16,0);
    vsip_cvview_f *b = vsip_cvsubview_f(B,0,4);
    vsip_scalar_f user_data_r[16],*udr;
    vsip_scalar_f user_data_i[16],*udi;
    vsip_cblock_f *cblock = vsip_cblockbind_f(
             user_data_r,user_data_i,16,0);
    vsip_cvview_f *c = vsip_cvbind_f(cblock,1,2,4);

    /* unit stride data_even out of place */
    FILE *fptr = fopen("data_even","r");
    vsip_cblockadmit_f(cblock,VSIP_FALSE);
    printf("test cvlog\n");
    printf("unit stride data even out of place");
    VU_cvreadf_f(fptr,a);
    fclose(fptr);
    printf("input vector\n"); VU_cvprintm_f("6.4",a);
    vsip_cvlog_f(a,b);
    printf("input vector after operation\n");VU_cvprintm_f("6.4",a);
    printf("output vector\n"); VU_cvprintm_f("6.4",b);
    /* inplace */
    vsip_cvlog_f(a,a);
    printf("output of inplace\n"); VU_cvprintm_f("6.4",a);

    /* unit stride data_odd out of place */
    printf("unit stride data odd out of place\n");
    vsip_cvputlength_f(a,5);
    vsip_cvputlength_f(b,5);
    fptr = fopen("data_odd","r");
    VU_cvreadf_f(fptr,a);
    fclose(fptr);
    printf("input vector\n"); VU_cvprintm_f("6.4",a);
    vsip_cvlog_f(a,b);
    printf("input vector after operation\n");VU_cvprintm_f("6.4",a);
    printf("output vector\n"); VU_cvprintm_f("6.4",b);

    /* input stride 1 output stride 2 */
    printf("input stride 1 output stride 2\n");
    vsip_cvputstride_f(b,2);
    fptr = fopen("data_odd","r"); VU_cvreadf_f(fptr,a); fclose(fptr);
    vsip_cvlog_f(a,b);
    printf("output vector\n"); VU_cvprintm_f("6.4",b);

    /* input stride 2 output stride 3 */
    printf("input stride 2 output stride 3\n");
    vsip_cvputstride_f(a,2);
    vsip_cvputstride_f(b,3);
    fptr = fopen("data_odd","r"); VU_cvreadf_f(fptr,a); fclose(fptr);
    vsip_cvlog_f(a,b);
    printf("output vector\n"); VU_cvprintm_f("6.4",b);

    /* input stride 2 output stride 1 */
    printf("input stride 2 output stride 1\n");
    vsip_cvputstride_f(a,2);
    vsip_cvputstride_f(b,1);
    fptr = fopen("data_odd","r"); VU_cvreadf_f(fptr,a); fclose(fptr);
    vsip_cvlog_f(a,b);
    printf("output vector\n"); VU_cvprintm_f("6.4",b);

    /* in place stride 2 */
    printf("in place stride 2\n");
    fptr = fopen("data_odd","r"); VU_cvreadf_f(fptr,a); fclose(fptr);
    vsip_cvlog_f(a,a);
    printf("output vector\n"); VU_cvprintm_f("6.4",a);

    /* out of place from user block to VSIPL block */
    printf("out of place from user block to VSIPL block\n");
    printf("User block associated with split complex data array\n");
    printf("user view offset 1, stride 2\n");
    printf("vsipl view offset 0, stride 2\n");
    fptr = fopen("data_odd","r"); VU_cvreadf_f(fptr,c); fclose(fptr);
    vsip_cvlog_f(c,a);
    printf("output vector\n"); VU_cvprintm_f("6.4",a);

    /* clean up */
    vsip_cblockrelease_f(cblock,VSIP_FALSE,&udr,&udi);
    vsip_cvalldestroy_f(c);
    vsip_cvdestroy_f(a);
    vsip_cvdestroy_f(b);
    vsip_cvalldestroy_f(A);
    vsip_cvalldestroy_f(B);
    }vsip_finalize((void*)0);return 0;
}
