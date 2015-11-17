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
/* $Id: mcmagsq_f.h,v 2.0 2003/02/22 15:23:24 judd Exp $ */
static void mcmagsq_f(){
   printf("\n*******\nTEST mcmagsq_f\n\n");
   { vsip_scalar_f data_r[] = {M_PI/8.0,  M_PI/4.0,  M_PI/3.0,  M_PI/1.5,  1.25 * M_PI,  1.75 * M_PI};
     vsip_scalar_f data_i[] = { 1,        2,         -3,        -4,         5,           6};
     vsip_scalar_f ans[] = {1.1542, 4.6169, 10.0966, 20.3865, 40.4213, 66.2257};
     vsip_cblock_f  *block = vsip_cblockbind_f(data_r,data_i,6,VSIP_MEM_NONE);
     vsip_block_f  *ans_block = vsip_blockbind_f(ans,6,VSIP_MEM_NONE);
     vsip_cmview_f  *a = vsip_cmbind_f(block,0,2,3,1,2);
     vsip_mview_f  *ansm = vsip_mbind_f(ans_block,0,2,3,1,2);
     vsip_mview_f  *b = vsip_mcreate_f(3,2,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_f  *chk = vsip_mcreate_f(3,2,VSIP_COL,VSIP_MEM_NONE);
     vsip_cblockadmit_f(block,VSIP_TRUE);
     vsip_blockadmit_f(ans_block,VSIP_TRUE);
     printf("test out of place, compact, user \"a\", vsipl \"b\"\n");
     vsip_mcmagsq_f(a,b);
     printf("vsip_mcmagsq_f(a,b)\n matrix a\n");VU_cmprintm_f("8.6",a);
     printf("matrix b\n");VU_mprintm_f("8.6",b);
     printf("answer\n");VU_mprintm_f("8.4",ansm);

     vsip_msub_f(b,ansm,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_f(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     vsip_cmalldestroy_f(a);
     vsip_malldestroy_f(b);
     vsip_malldestroy_f(chk);
     vsip_malldestroy_f(ansm);
   }
   return;
}
