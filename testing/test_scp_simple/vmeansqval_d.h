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
/* $Id: vmeansqval_d.h,v 2.0 2003/02/22 15:23:29 judd Exp $ */
static void vmeansqval_d(){
   printf("********\nTEST vmeansqval_d\n");
   {
     vsip_scalar_d data[] = {-1,  1, 0,  2, -2 };
     vsip_scalar_d ans = 2.0;
     vsip_scalar_d val=0;
     vsip_block_d  *block = vsip_blockbind_d(data,5,VSIP_MEM_NONE);
     vsip_vview_d  *a = vsip_vbind_d(block,0,1,5);
     vsip_blockadmit_d(block,VSIP_TRUE);
     val = vsip_vmeansqval_d(a);
     printf("val = vsip_vmeansqval_d(a)\n vector a\n");VU_vprintm_d("8.6",a);
     printf("val = %f\n",val);
     printf("right answer %f\n",ans);
     if(val == ans)
          printf("correct\n");
     else
          printf("error\n");
     vsip_valldestroy_d(a);
   }
   return;
}
