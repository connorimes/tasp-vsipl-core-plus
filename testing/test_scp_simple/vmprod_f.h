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
/* $Id: vmprod_f.h,v 2.0 2003/02/22 15:23:29 judd Exp $ */
static void vmprod_f(){
   printf("********\nTEST vmprod_f\n");
   {
     vsip_scalar_f datav[] = {1,2,3,4,5};
     vsip_scalar_f datam[] = { .1, .2, .3, .4,    
                              1.0, 1.1, 1.2, 1.3,
                              2.1, 2.2, 2.3, 2.4,
                              -1.1, -1.2, -1.3, -1.4,
                              2.1, 2.2, 2.3, 3.4};
     vsip_scalar_f ans_data[] = { 14.5,15.2,15.9,21.6};
     vsip_block_f *blockv = vsip_blockbind_f(datav,5,VSIP_MEM_NONE);
     vsip_block_f *blockm = vsip_blockbind_f(datam,20,VSIP_MEM_NONE);
     vsip_block_f *block_ans = vsip_blockbind_f(ans_data,4,VSIP_MEM_NONE);
     vsip_block_f *block  = vsip_blockcreate_f(70,VSIP_MEM_NONE);
     vsip_vview_f *v = vsip_vbind_f(blockv,0,1,5);
     vsip_mview_f *m = vsip_mbind_f(blockm,0,4,5,1,4);
     vsip_vview_f *ans = vsip_vbind_f(block_ans,0,1,4);
     vsip_vview_f *a = vsip_vbind_f(block,5,-1,5);
     vsip_mview_f *b = vsip_mbind_f(block,50,-2,5,-10,4);
     vsip_vview_f *c = vsip_vbind_f(block,49,-2,4);
     vsip_vview_f *chk = vsip_vcreate_f(4,VSIP_MEM_NONE);
     vsip_blockadmit_f(blockv,VSIP_TRUE);
     vsip_blockadmit_f(blockm,VSIP_TRUE);
     vsip_blockadmit_f(block_ans,VSIP_TRUE);
     vsip_vcopy_f_f(v,a);
     vsip_mcopy_f_f(m,b);
     vsip_vmprod_f(a,b,c);
     printf("vsip_vmprod_f(a,b,c)\n");    
     printf("a\n"); VU_vprintm_f("6.4",a);
     printf("b\n"); VU_mprintm_f("6.4",b);
     printf("c\n"); VU_vprintm_f("6.4",c);
     printf("right answer\n"); VU_vprintm_f("6.4",ans);
     vsip_vsub_f(c,ans,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_f(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");
     vsip_valldestroy_f(v);
     vsip_malldestroy_f(m);
     vsip_valldestroy_f(ans);
     vsip_vdestroy_f(a);
     vsip_mdestroy_f(b);
     vsip_valldestroy_f(c);
     vsip_valldestroy_f(chk);
   }
   return;
}
