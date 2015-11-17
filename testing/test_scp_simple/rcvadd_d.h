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
/* $Id: rcvadd_d.h,v 2.0 2003/02/22 15:23:27 judd Exp $ */
static void rcvadd_d(){
   printf("********\nTEST rcvadd_d\n");
   {
     vsip_scalar_d data_a[]   = { 1.1,  1.2,    2.1,  2.2,  -3.1, -3.3};
     vsip_scalar_d data_b_r[] = { 8.1, 10.2,  -12.1, 10.2, -11.1, -2.3};
     vsip_scalar_d data_b_i[] = {10.1, 11.2,   22.1, 12.2, -13.1, -0.3};
     vsip_scalar_d ans_r[]    = {9.20, 11.4,  -10.0, 12.4, -14.2, -5.6};
     vsip_scalar_d ans_i[]    = {10.1, 11.2,   22.1, 12.2, -13.1, -0.3};

     vsip_block_d   *block_a = vsip_blockbind_d(data_a,6,VSIP_MEM_NONE);
     vsip_cblock_d  *block_b = vsip_cblockbind_d(data_b_r,data_b_i,6,VSIP_MEM_NONE);
     vsip_cblock_d  *block_c = vsip_cblockcreate_d(30,VSIP_MEM_NONE);
     vsip_cblock_d  *block_d = vsip_cblockcreate_d(30,VSIP_MEM_NONE);
     vsip_cblock_d  *ans_block = vsip_cblockbind_d(ans_r,ans_i,6,VSIP_MEM_NONE);

     vsip_vview_d  *a = vsip_vbind_d(block_a,0,1,6);
     vsip_cvview_d  *b = vsip_cvbind_d(block_b,0,1,6);
     vsip_cvview_d  *c = vsip_cvbind_d(block_c,18,-2,6);
     vsip_cvview_d  *d = vsip_cvbind_d(block_d,2,3,6);

     vsip_cvview_d  *ansv = vsip_cvbind_d(ans_block,0,1,6);
     vsip_cvview_d  *chk = vsip_cvcreate_d(6,VSIP_MEM_NONE);
     vsip_vview_d   *chk_r = vsip_vrealview_d(chk);

     vsip_blockadmit_d(block_a,VSIP_TRUE);
     vsip_cblockadmit_d(block_b,VSIP_TRUE);
     vsip_cblockadmit_d(ans_block,VSIP_TRUE);

     printf("vsip_rcvadd_d(a,b,c)\n");
     vsip_rcvadd_d(a,b,c);
     printf("vector a\n");VU_vprintm_d("8.6",a);
     printf("vector b\n");VU_cvprintm_d("8.6",b);
     printf("vector c\n");VU_cvprintm_d("8.6",c);
     printf("right answer\n");VU_cvprintm_d("8.4",ansv);

     vsip_cvsub_d(c,ansv,chk); vsip_cvmag_d(chk,chk_r); vsip_vclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_d(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\na,c in place, <a> real view of <c>\n");
     { vsip_vview_d *a_r = vsip_vrealview_d(d);
       vsip_vcopy_d_d(a,a_r);
       vsip_rcvadd_d(a_r,b,d);
       vsip_vdestroy_d(a_r);
     }
     vsip_cvsub_d(d,ansv,chk); vsip_cvmag_d(chk,chk_r); vsip_vclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_d(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     vsip_valldestroy_d(a);
     vsip_cvalldestroy_d(b);
     vsip_cvalldestroy_d(c);
     vsip_cvalldestroy_d(d);
     vsip_vdestroy_d(chk_r);
     vsip_cvalldestroy_d(chk);
     vsip_cvalldestroy_d(ansv);
   }
   return;
}
