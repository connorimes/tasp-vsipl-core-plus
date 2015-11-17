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
/* $Id: meuler_f.h,v 2.0 2003/02/22 15:23:24 judd Exp $ */
static void meuler_f(){
   printf("\n*******\nTEST meuler_f\n\n");
   { vsip_scalar_f data[] = {M_PI/8.0, M_PI/4.0, M_PI/3.0, M_PI/1.5, 1.25 * M_PI, 1.75 * M_PI};
     vsip_scalar_f ans_r[] = {0.9239, 0.7071, 0.5000, -0.5000, -0.7071, 0.7071};
     vsip_scalar_f ans_i[] = {0.3827, 0.7071, 0.8660, 0.8660, -0.7071, -0.7071};
     vsip_block_f  *block = vsip_blockbind_f(data,6,VSIP_MEM_NONE);
     vsip_cblock_f  *ans_block = vsip_cblockbind_f(ans_r,ans_i,6,VSIP_MEM_NONE);
     vsip_mview_f  *a = vsip_mbind_f(block,0,2,3,1,2);
     vsip_cmview_f  *ansm = vsip_cmbind_f(ans_block,0,2,3,1,2);
     vsip_cmview_f  *b = vsip_cmcreate_f(3,2,VSIP_ROW,VSIP_MEM_NONE);
     vsip_cmview_f  *chk = vsip_cmcreate_f(3,2,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_f  *chk_r = vsip_mrealview_f(chk);
     vsip_blockadmit_f(block,VSIP_TRUE);
     vsip_cblockadmit_f(ans_block,VSIP_TRUE);
     printf("test out of place, compact, user \"a\", vsipl \"b\"\n");
     vsip_meuler_f(a,b);
     printf("meuler_f(a,b)\n matrix a\n");VU_mprintm_f("8.6",a);
     printf("matrix b\n");VU_cmprintm_f("8.6",b);
     printf("answer\n");VU_cmprintm_f("8.4",ansm);

     vsip_cmsub_f(b,ansm,chk); vsip_cmmag_f(chk,chk_r); vsip_mclip_f(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_msumval_f(chk_r) > .5)
         printf("error\n");
     else
         printf("correct\n");

     printf("check meuler_f in place, <a> realview of <b>.\n");
     { vsip_mview_f *d = vsip_mrealview_f(b);
       vsip_mcopy_f_f(a,d);
       vsip_meuler_f(d,b);
       vsip_cmsub_f(b,ansm,chk); vsip_cmmag_f(chk,chk_r); vsip_mclip_f(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_msumval_f(chk_r) > .5)
         printf("error\n");
     else
         printf("correct\n");
       vsip_mdestroy_f(d);
     }

     vsip_malldestroy_f(a);
     vsip_cmalldestroy_f(b);
     vsip_mdestroy_f(chk_r);
     vsip_cmalldestroy_f(chk);
     vsip_cmalldestroy_f(ansm);
   }
   return;
}
