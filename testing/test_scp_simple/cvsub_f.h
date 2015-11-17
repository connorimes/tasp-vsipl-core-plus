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
/* $Id: cvsub_f.h,v 2.0 2003/02/22 15:23:23 judd Exp $ */
static void cvsub_f(){
   printf("********\nTEST cvsub_f\n");
   {
     vsip_scalar_f data_a_i[] = { 1.1, 1.2, 2.1, 2.2, -3.1, -3.3};
     vsip_scalar_f data_a_r[] = { 2.1, 3.2, -2.1, -2.2, +5.1, +5.3};
     vsip_scalar_f data_b_i[] = {10.1, 11.2, 22.1, 12.2, -13.1, -0.3};
     vsip_scalar_f data_b_r[] = {8.1, 10.2, -12.1, 10.2, -11.1, -2.3};
     vsip_scalar_f ans_r[] = { -6.0000, -7.0000, 10.0000, -12.4000, 16.2000, 7.6000 };
     vsip_scalar_f ans_i[] = { -9, -10, -20, -10, 10, -3 }; 
     vsip_cblock_f  *block_a = vsip_cblockbind_f(data_a_r,data_a_i,6,VSIP_MEM_NONE);
     vsip_cblock_f  *block_b = vsip_cblockbind_f(data_b_r,data_b_i,6,VSIP_MEM_NONE);
     vsip_cblock_f  *block_c = vsip_cblockcreate_f(30,VSIP_MEM_NONE);
     vsip_cblock_f  *block_d = vsip_cblockcreate_f(30,VSIP_MEM_NONE);
     vsip_cblock_f  *ans_block = vsip_cblockbind_f(ans_r,ans_i,6,VSIP_MEM_NONE);

     vsip_cvview_f  *a = vsip_cvbind_f(block_a,0,1,6);
     vsip_cvview_f  *b = vsip_cvbind_f(block_b,0,1,6);
     vsip_cvview_f  *c = vsip_cvbind_f(block_c,18,-2,6);
     vsip_cvview_f  *d = vsip_cvbind_f(block_d,2,3,6);

     vsip_cvview_f  *ansv = vsip_cvbind_f(ans_block,0,1,6);
     vsip_cvview_f  *chk = vsip_cvcreate_f(6,VSIP_MEM_NONE);
     vsip_vview_f  *chk_r = vsip_vrealview_f(chk);

     vsip_cblockadmit_f(block_a,VSIP_TRUE);
     vsip_cblockadmit_f(block_b,VSIP_TRUE);
     vsip_cblockadmit_f(ans_block,VSIP_TRUE);

     printf("vsip_cvsub_f(a,b)\n");
     vsip_cvsub_f(a,b,c);
     printf("cvsub_f(a,b,c)\n vector a\n");VU_cvprintm_f("8.6",a);
     printf("vector b\n");VU_cvprintm_f("8.6",b);
     printf("vector c\n");VU_cvprintm_f("8.6",c);
     printf("right answer\n");VU_cvprintm_f("8.4",ansv);

     vsip_cvsub_f(c,ansv,chk); vsip_cvmag_f(chk,chk_r); vsip_vclip_f(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_f(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\na,c in place\n");
     vsip_cvcopy_f_f(a,d);
     vsip_cvsub_f(d,b,d);
     vsip_cvsub_f(d,ansv,chk); vsip_cvmag_f(chk,chk_r); vsip_vclip_f(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_f(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\nb,c in place\n");
     vsip_cvcopy_f_f(b,c);
     vsip_cvsub_f(a,c,c);
     vsip_cvsub_f(c,ansv,chk); vsip_cvmag_f(chk,chk_r); vsip_vclip_f(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_f(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     vsip_cvalldestroy_f(a);
     vsip_cvalldestroy_f(b);
     vsip_cvalldestroy_f(c);
     vsip_cvalldestroy_f(d);
     vsip_vdestroy_f(chk_r);
     vsip_cvalldestroy_f(chk);
     vsip_cvalldestroy_f(ansv);
   }
   return;
}
