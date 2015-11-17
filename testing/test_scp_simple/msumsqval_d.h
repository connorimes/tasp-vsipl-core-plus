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
/* $Id: msumsqval_d.h,v 2.0 2003/02/22 15:23:26 judd Exp $ */
static void msumsqval_d(){
   printf("\n*******\nTEST msumsqval_d\n");
   {
       vsip_scalar_d data[] = {1.0, 1.1, 1.2, 1.3, 1.4, 1.4, 1.3, 1.2, 1.1, 1.0};
       vsip_mview_d *m1 = vsip_mbind_d(
                 vsip_blockbind_d(data,10,VSIP_MEM_NONE),0,5,2,1,5);       
       vsip_block_d  *block = vsip_blockcreate_d(1024,VSIP_MEM_NONE);
       vsip_mview_d *m = vsip_mbind_d(block,4,20,2,2,5);
       vsip_blockadmit_d(vsip_mgetblock_d(m1),VSIP_TRUE);
       vsip_mcopy_d_d(m1,m);
       printf("matrix m1, user matrix, compact, row major\n");
       VU_mprintm_d("6.4",m1);
       printf("matrix m1, VSIPL matrix, irregular, row major\n");
       printf("col stride 20, row stride 2\n");
       printf("copy m1 to m. Matrix m equals\n");
       VU_mprintm_d("6.4",m);
       printf("msumsqval_d(m1) = %f\n",vsip_msumsqval_d(m1));
       printf("msumsqval_d(m) = %f\n",vsip_msumsqval_d(m));
       printf("ans should be 14.6 \n");
       if((fabs(14.6000-vsip_msumsqval_d(m) > .0001)) ||
          (fabs(14.6000-vsip_msumsqval_d(m1) > .0001))) {
          printf("error\n");
       }else{
           printf("correct\n");
       }
       vsip_malldestroy_d(m); vsip_malldestroy_d(m1);
    }
    return;
}
