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
/* $Id: cvkron_d.h,v 2.0 2003/02/22 15:23:23 judd Exp $ */
static void cvkron_d(){
   printf("********\nTEST cvkron_d\n");
   {
     vsip_cscalar_d alpha = vsip_cmplx_d(-3,2);
     vsip_scalar_d data_a_r[] = { 1,  1};
     vsip_scalar_d data_a_i[] = { 1, -1};
     vsip_scalar_d data_b_r[] = {3, 5, 2};
     vsip_scalar_d data_b_i[] = {1, 1, 2};
     vsip_scalar_d ans_r[] = { -14.0,  -8.0,
                               -24.0, -10.0,
                                -8.0, -12.0};
     vsip_scalar_d ans_i[] = { -8.0,  14.0,
                              -10.0,  24.0,
                              -12.0,   8.0};


     vsip_cblock_d  *block_a = vsip_cblockbind_d(data_a_r,data_a_i,2,VSIP_MEM_NONE);
     vsip_cblock_d  *block_b = vsip_cblockbind_d(data_b_r,data_b_i,3,VSIP_MEM_NONE);
     vsip_cblock_d  *block_c = vsip_cblockcreate_d(100,VSIP_MEM_NONE);
     vsip_cblock_d  *ans_block = vsip_cblockbind_d(ans_r,ans_i,6,VSIP_MEM_NONE);

     vsip_cvview_d  *a = vsip_cvbind_d(block_a,0,1,2);
     vsip_cvview_d  *b = vsip_cvbind_d(block_b,0,1,3);
     vsip_cmview_d  *c = vsip_cmbind_d(block_c,99,-1,3,-4,2);

     vsip_cmview_d  *ansm = vsip_cmbind_d(ans_block,0,2,3,1,2);
     vsip_cmview_d  *chk = vsip_cmcreate_d(3,2,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_d  *chk_r = vsip_mrealview_d(chk);

     vsip_cblockadmit_d(block_a,VSIP_TRUE);
     vsip_cblockadmit_d(block_b,VSIP_TRUE);
     vsip_cblockadmit_d(ans_block,VSIP_TRUE);

     printf("vsip_cvkron_d(alpha,a,b,c)\n");
     vsip_cvkron_d(alpha,a,b,c);
     printf("alpha = %f %+fi\n",alpha);
     printf("vector a\n");VU_cvprintm_d("8.6",a);
     printf("vector b\n");VU_cvprintm_d("8.6",b);
     printf("matrix c\n");VU_cmprintm_d("8.6",c);
     printf("right answer\n");VU_cmprintm_d("8.4",ansm);

     vsip_cmsub_d(c,ansm,chk); vsip_cmmag_d(chk,chk_r); vsip_mclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_msumval_d(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     vsip_cvalldestroy_d(a);
     vsip_cvalldestroy_d(b);
     vsip_cmalldestroy_d(c);
     vsip_mdestroy_d(chk_r);
     vsip_cmalldestroy_d(chk);
     vsip_cmalldestroy_d(ansm);
   }
   return;
}
