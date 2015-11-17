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
/* $Id: vcos_d.h,v 2.0 2003/02/22 15:23:28 judd Exp $ */
static void vcos_d(){
   printf("********\nTEST vcos_d\n");
   {
     vsip_scalar_d data[] = {0, M_PI/4.0, M_PI/3.0, M_PI, 1.25 * M_PI};
     vsip_scalar_d ans[] = { 1.0, 0.7071, 0.5, -1.0, -0.7071};
     vsip_block_d  *block = vsip_blockbind_d(data,5,VSIP_MEM_NONE);
     vsip_block_d  *ans_block = vsip_blockbind_d(ans,5,VSIP_MEM_NONE);
     vsip_vview_d  *a = vsip_vbind_d(block,0,1,5);
     vsip_vview_d  *ansv = vsip_vbind_d(ans_block,0,1,5);
     vsip_vview_d  *b = vsip_vcreate_d(15,VSIP_MEM_NONE);
     vsip_vview_d  *chk = vsip_vcreate_d(5,VSIP_MEM_NONE);
     vsip_vputlength_d(b,5);
     vsip_blockadmit_d(block,VSIP_TRUE);
     vsip_blockadmit_d(ans_block,VSIP_TRUE);
     printf("test out of place, compact, user \"a\", vsipl \"b\"\n");
     vsip_vcos_d(a,b);
     printf("vcos_d(a,b)\n vector a\n");VU_vprintm_d("8.6",a);
     printf("vector b\n");VU_vprintm_d("8.6",b);
     printf("expected answer to 4 decimal digits\n");VU_vprintm_d("8.4",ansv);

     vsip_vsub_d(b,ansv,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_d(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\na,b in place\n");
     vsip_vputstride_d(b,2);vsip_vcopy_d_d(a,b);
     vsip_vcos_d(a,a);
     vsip_vsub_d(a,ansv,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_d(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\n");
     /* check with a stride 1, b stride 2 */
     printf("vsip_vcos(a,b) with <a> stride 2, <b> stride 1\n");
     vsip_vcos_d(b,a);
     vsip_vsub_d(a,ansv,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_d(chk) > .5) 
         printf(" vcos_d in error for in place\n");
     else {
         printf("correct\n");
     }
     vsip_valldestroy_d(a);
     vsip_valldestroy_d(b);
     vsip_valldestroy_d(chk);
     vsip_valldestroy_d(ansv);
   }
   return;
}
