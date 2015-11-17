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
/* $Id: cmprodh_f.h,v 2.0 2003/02/22 15:23:21 judd Exp $ */
static void cmprodh_f(){
   printf("********\nTEST cmprodh_f\n");
   {
     vsip_scalar_f datal_r[] = {1, 2.0, 3.0,  4,  5.0,
                                5,  .1,  .2, .3,   .4,
                                4, 3.0, 2.0,  0, -1.0};
     vsip_scalar_f datal_i[] = {9, 3.0, 2.0,  4.3,  3.2,
                                5,  .1,  1.2, .3,   1.4,
                                3, 2.0, -2.1,  0.1, 1.0};
     vsip_scalar_f datar_r[] = { .1, .2, .3, .4,    
                              1.0, 1.1, 1.2, 1.3,
                              2.1, 2.2, 2.3, 2.4,
                              -1.1, -1.2, -1.3, -1.4,
                              2.1, 2.2, 2.3, 3.4};
     vsip_scalar_f datar_i[] = { 1.1, 5.2, 3.3, 1.4,    
                              2.1, 1.0, 1.2, 1.2,
                              4.1, 3.0, 2.3, 2.3,
                               1.1, -1.2, -1.3,  1.0,
                              1.0, 2.2, -2.3, 3.4};
     vsip_scalar_f ans_data_r[] = {49.07, 74.82, 43.01, 59.88,
                                      5.59, -4.01, -6.52,  7.19,
                                      5.5,  19.68, 12.14, 12.17};
     vsip_scalar_f ans_data_i[] = {-19.45,-11.98, 15.57,-15.7,
                                       0.71, -8.17, -1.84,  0.97,
                                     -18.02,-27.34,-23.06, -8.38};
     vsip_cblock_f *blockl = vsip_cblockbind_f(datal_r,datal_i,15,VSIP_MEM_NONE);
     vsip_cblock_f *blockr = vsip_cblockbind_f(datar_r,datar_i,20,VSIP_MEM_NONE);
     vsip_cblock_f *block_ans = vsip_cblockbind_f(ans_data_r,ans_data_i,12,VSIP_MEM_NONE);
     vsip_cblock_f *block  = vsip_cblockcreate_f(70,VSIP_MEM_NONE);
     vsip_cmview_f *ml = vsip_cmbind_f(blockl,0,5,3,1,5);
     vsip_cmview_f *mr = vsip_cmbind_f(blockr,0,1,4,4,5);
     vsip_cmview_f *ans = vsip_cmbind_f(block_ans,0,4,3,1,4);
     vsip_cmview_f *a = vsip_cmbind_f(block,15,-1,3,-3,5);
     vsip_cmview_f *b = vsip_cmbind_f(block,50,-2,4,-8,5);
     vsip_cmview_f *c = vsip_cmbind_f(block,49,-2,3,-6,4);
     vsip_cmview_f *chk = vsip_cmcreate_f(3,4,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_f *chk_r = vsip_mrealview_f(chk);
     vsip_cblockadmit_f(blockl,VSIP_TRUE);
     vsip_cblockadmit_f(blockr,VSIP_TRUE);
     vsip_cblockadmit_f(block_ans,VSIP_TRUE);
     vsip_cmcopy_f_f(ml,a);
     vsip_cmcopy_f_f(mr,b);
     vsip_cmprodh_f(a,b,c);
     printf("vsip_cmprodh_f(a,b,c)\n");    
     printf("a\n"); VU_cmprintm_f("6.4",a);
     printf("b\n"); VU_cmprintm_f("6.4",b);
     printf("c\n"); VU_cmprintm_f("6.4",c);
     printf("right answer\n"); VU_cmprintm_f("6.4",ans);
     vsip_cmsub_f(c,ans,chk); vsip_cmmag_f(chk,chk_r); vsip_mclip_f(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_msumval_f(chk_r) > .5)
         printf("error\n");
     else
         printf("correct\n");
     vsip_cmalldestroy_f(ml);
     vsip_cmalldestroy_f(mr);
     vsip_cmdestroy_f(a);
     vsip_cmdestroy_f(b);
     vsip_cmalldestroy_f(c);
     vsip_cmalldestroy_f(ans);
     vsip_mdestroy_f(chk_r);
     vsip_cmalldestroy_f(chk);
   }
   return;
}
