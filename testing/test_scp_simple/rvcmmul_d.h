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
/* $Id: rvcmmul_d.h,v 2.0 2003/02/22 15:23:27 judd Exp $ */
static void rvcmmul_d(){
   printf("********\nTEST rvcmmul_d\n");
   {
     vsip_scalar_d data_a1[] = { 1, 2, 3, 4 };
     vsip_scalar_d data_a2[] = { 6, 5, 4, 3, 2, 1};
     vsip_scalar_d data_b[] = { 1,.1, 1,.1,  1,.1, 1,.1,
                                  1,.1, 1,.1,  1,.1, 1,.1,
                                  1,.1, 1,.1,  1,.1, 1,.1,
                                  1,.1, 1,.1,  1,.1, 1,.1,
                                  1,.1, 1,.1,  1,.1, 1,.1,
                                  1,.1, 1,.1,  1,.1, 1,.1 };
     vsip_scalar_d ans1[] = { 1,.1, 2,.2, 3,.3, 4,.4,
                                1,.1, 2,.2, 3,.3, 4,.4, 
                                1,.1, 2,.2, 3,.3, 4,.4,
                                1,.1, 2,.2, 3,.3, 4,.4,
                                1,.1, 2,.2, 3,.3, 4,.4,
                                1,.1, 2,.2, 3,.3, 4,.4 };
     vsip_scalar_d ans2[] = { 6,.6, 6,.6, 6,.6, 6,.6,
                                5,.5, 5,.5, 5,.5, 5,.5,
                                4,.4, 4,.4, 4,.4, 4,.4,
                                3,.3, 3,.3, 3,.3, 3,.3,
                                2,.2, 2,.2, 2,.2, 2,.2,
                                1,.1, 1,.1, 1,.1, 1,.1 };

     vsip_block_d   *block_a1 = vsip_blockbind_d(data_a1,4,VSIP_MEM_NONE);
     vsip_block_d   *block_a2 = vsip_blockbind_d(data_a2,6,VSIP_MEM_NONE);
     vsip_cblock_d  *block_b = vsip_cblockbind_d(data_b,NDPTR_d,24,VSIP_MEM_NONE);
     vsip_cblock_d  *block_c = vsip_cblockcreate_d(100,VSIP_MEM_NONE);
     vsip_cblock_d  *block_d = vsip_cblockcreate_d(100,VSIP_MEM_NONE);
     vsip_cblock_d  *ans1_block = vsip_cblockbind_d(ans1,NDPTR_d,24,VSIP_MEM_NONE);
     vsip_cblock_d  *ans2_block = vsip_cblockbind_d(ans2,NDPTR_d,24,VSIP_MEM_NONE);

     vsip_vview_d   *a1 = vsip_vbind_d(block_a1,0,1,4);
     vsip_vview_d   *a2 = vsip_vbind_d(block_a2,0,1,6);
     vsip_cmview_d  *b = vsip_cmbind_d(block_b,0,4,6,1,4);
     vsip_cmview_d  *c = vsip_cmbind_d(block_c,95,-1,6,-12,4);
     vsip_cmview_d  *d = vsip_cmbind_d(block_d,0,16,6,2,4);

     vsip_cmview_d  *ansm1 = vsip_cmbind_d(ans1_block,0,4,6,1,4);
     vsip_cmview_d  *ansm2 = vsip_cmbind_d(ans2_block,0,4,6,1,4);
     vsip_cmview_d  *chk = vsip_cmcreate_d(6,4,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_d   *chk_r = vsip_mrealview_d(chk);

     vsip_blockadmit_d(block_a1,VSIP_TRUE);
     vsip_blockadmit_d(block_a2,VSIP_TRUE);
     vsip_cblockadmit_d(block_b,VSIP_TRUE);
     vsip_cblockadmit_d(ans1_block,VSIP_TRUE);
     vsip_cblockadmit_d(ans2_block,VSIP_TRUE);

     printf("vsip_rvcmmul_d(a,b,VSIP_ROW,c); \n");
     vsip_rvcmmul_d(a1,b,VSIP_ROW,c);
     printf("vector a\n");VU_vprintm_d("6.2",a1);
     printf("matrix b\n");VU_cmprintm_d("6.2",b);
     printf("matrix c\n");VU_cmprintm_d("6.2",c);
     printf("right answer\n");VU_cmprintm_d("6.2",ansm1);
     vsip_cmsub_d(c,ansm1,chk); vsip_cmmag_d(chk,chk_r); vsip_mclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_msumval_d(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\nb,c in place\n");
     vsip_cmcopy_d_d(b,d);
     vsip_rvcmmul_d(a1,d,VSIP_ROW,d);
     vsip_cmsub_d(d,ansm1,chk); vsip_cmmag_d(chk,chk_r); vsip_mclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_msumval_d(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("vsip_rvcmmul_d(a,b,VSIP_COL,c); \n");
     vsip_rvcmmul_d(a2,b,VSIP_COL,c);
     printf("vector a\n");VU_vprintm_d("6.2",a2);
     printf("matrix b\n");VU_cmprintm_d("6.2",b);
     printf("matrix c\n");VU_cmprintm_d("6.2",c);
     printf("right answer\n");VU_cmprintm_d("6.2",ansm2);
     vsip_cmsub_d(c,ansm2,chk); vsip_cmmag_d(chk,chk_r); vsip_mclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_msumval_d(chk_r) > .5)
         printf("error\n");
     else 
         printf("correct\n");

     printf("\nb,c in place\n");
     vsip_cmcopy_d_d(b,c);
     vsip_rvcmmul_d(a2,c,VSIP_COL,c);
     vsip_cmsub_d(c,ansm2,chk); vsip_cmmag_d(chk,chk_r); vsip_mclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_msumval_d(chk_r) > .5)
         printf("error\n");
     else
         printf("correct\n");

     vsip_valldestroy_d(a1);
     vsip_valldestroy_d(a2);
     vsip_cmalldestroy_d(b);
     vsip_cmalldestroy_d(c);
     vsip_cmalldestroy_d(d);
     vsip_mdestroy_d(chk_r);
     vsip_cmalldestroy_d(chk);
     vsip_cmalldestroy_d(ansm1);
     vsip_cmalldestroy_d(ansm2);
   }
   return;
}
