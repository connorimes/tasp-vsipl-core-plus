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
/* $Id: cmprodt_d.h,v 2.0 2003/02/22 15:23:21 judd Exp $ */
static void cmprodt_d(){
   printf("********\nTEST cmprodt_d\n");
   {
     vsip_scalar_d datal_r[] = {1, 2.0, 3.0,  4,  5.0,
                                5,  .1,  .2, .3,   .4,
                                4, 3.0, 2.0,  0, -1.0};
     vsip_scalar_d datal_i[] = {9, 3.0, 2.0,  4.3,  3.2,
                                5,  .1,  1.2, .3,   1.4,
                                3, 2.0, -2.1,  0.1, 1.0};
     vsip_scalar_d datar_r[] = { .1, .2, .3, .4,    
                              1.0, 1.1, 1.2, 1.3,
                              2.1, 2.2, 2.3, 2.4,
                              -1.1, -1.2, -1.3, -1.4,
                              2.1, 2.2, 2.3, 3.4};
     vsip_scalar_d datar_i[] = { 1.1, 5.2, 3.3, 1.4,    
                              2.1, 1.0, 1.2, 1.2,
                              4.1, 3.0, 2.3, 2.3,
                               1.1, -1.2, -1.3,  1.0,
                              1.0, 2.2, -2.3, 3.4};
     vsip_scalar_d ans_data_r[] = {-36.84, -15.43, -27.98,  18.21,
                                     -12.24,  -4.6,   -0.23, -16.11,
                                      -8.41,   2.11,   7.73,  -1.85};
     vsip_scalar_d ans_data_i[] = {44.52,  70.57,  15.28,  36.27,
                                     10.34,  18.68,  19.31,   7.51,
                                     25.61,  12.38,  32.19,   7.01};
     vsip_cblock_d *blockl = vsip_cblockbind_d(datal_r,datal_i,15,VSIP_MEM_NONE);
     vsip_cblock_d *blockr = vsip_cblockbind_d(datar_r,datar_i,20,VSIP_MEM_NONE);
     vsip_cblock_d *block_ans = vsip_cblockbind_d(ans_data_r,ans_data_i,12,VSIP_MEM_NONE);
     vsip_cblock_d *block  = vsip_cblockcreate_d(120,VSIP_MEM_NONE);
     vsip_cmview_d *ml = vsip_cmbind_d(blockl,0,5,3,1,5);
     vsip_cmview_d *mr = vsip_cmbind_d(blockr,0,5,4,1,5);
     vsip_cmview_d *ans = vsip_cmbind_d(block_ans,0,4,3,1,4);
     vsip_cmview_d *a = vsip_cmbind_d(block,15,-1,3,-3,5);
     vsip_cmview_d *b = vsip_cmbind_d(block,50,1,4,10,5);
     vsip_cmview_d *c = vsip_cmbind_d(block,49,-8,3,-2,4);
     vsip_cmview_d *chk = vsip_cmcreate_d(3,4,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_d *chk_r = vsip_mrealview_d(chk);
     vsip_cblockadmit_d(blockl,VSIP_TRUE);
     vsip_cblockadmit_d(blockr,VSIP_TRUE);
     vsip_cblockadmit_d(block_ans,VSIP_TRUE);
     vsip_cmcopy_d_d(ml,a);
     vsip_cmcopy_d_d(mr,b);
     vsip_cmprodt_d(a,b,c);
     printf("vsip_cmprodt_d(a,b,c)\n");    
     printf("a\n"); VU_cmprintm_d("6.4",a);
     printf("b\n"); VU_cmprintm_d("6.4",b);
     printf("c\n"); VU_cmprintm_d("6.4",c);
     printf("right answer\n"); VU_cmprintm_d("6.4",ans);
     vsip_cmsub_d(c,ans,chk); vsip_cmmag_d(chk,chk_r); vsip_mclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_msumval_d(chk_r) > .5)
         printf("error\n");
     else
         printf("correct\n");
     vsip_cmalldestroy_d(ml);
     vsip_cmalldestroy_d(mr);
     vsip_cmdestroy_d(a);
     vsip_cmdestroy_d(b);
     vsip_cmalldestroy_d(c);
     vsip_cmalldestroy_d(ans);
     vsip_mdestroy_d(chk_r);
     vsip_cmalldestroy_d(chk);
   }
   return;
}
