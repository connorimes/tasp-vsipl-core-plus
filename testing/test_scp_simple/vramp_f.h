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
/* $Id: vramp_f.h,v 2.0 2003/02/22 15:23:30 judd Exp $ */
static void vramp_f(){
   printf("********\nTEST vramp_f\n");
   {
     vsip_scalar_f ans[] = { 1.1, 1.2, 1.3, 1.4, 1.5, 1.6};
     vsip_scalar_f start = 1.1;
     vsip_scalar_f inc   = 0.1;

     vsip_block_f  *block_c = vsip_blockcreate_f(30,VSIP_MEM_NONE);
     vsip_block_f  *ans_block = vsip_blockbind_f(ans,6,VSIP_MEM_NONE);

     vsip_vview_f  *c = vsip_vbind_f(block_c,18,-2,6);
     vsip_vview_f  *ansv = vsip_vbind_f(ans_block,0,1,6);
     vsip_vview_f  *chk = vsip_vcreate_f(6,VSIP_MEM_NONE);

     vsip_blockadmit_f(ans_block,VSIP_TRUE);

     printf("vsip_vramp_f(start,inc,c)\n");
     vsip_vramp_f(start,inc,c);
     printf("start = %3.1f\ninc = %3.1f \nVector <c> of length 6\n");
     printf("vector c\n");VU_vprintm_f("8.6",c);
     printf("right answer\n");VU_vprintm_f("8.4",ansv);

     vsip_vsub_f(c,ansv,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_f(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     vsip_valldestroy_f(c);
     vsip_valldestroy_f(chk);
     vsip_valldestroy_f(ansv);
   }
   return;
}
