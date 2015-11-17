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
/* $Id: tget_put_f.h,v 2.0 2003/02/22 15:23:35 judd Exp $ */
static void tget_put_f(){
   printf("********\nTEST tget_put_f\n");
   {
     vsip_scalar_f data_a[]     = { 0, 1, 1, 0, 1, 0,
                                    1, 0, 0, 1, 0, 1,
                                   2, 1, 1, 2, 1, 2};
                                 
     vsip_scalar_f ans[2][3][3] = { 0, 1, 1, 0,  1, 0,
                                    1, 0, 0, 1, 0, 1,
                                   2, 1, 1, 2, 1, 2};
     vsip_block_f *block_a    = vsip_blockbind_f(data_a,18,VSIP_MEM_NONE);
     vsip_tview_f *a          = vsip_tbind_f(block_a,0,9,2,3,3,1,3);

     vsip_block_f *block_b    = vsip_blockcreate_f(50,VSIP_MEM_NONE);
     vsip_tview_f *b          = vsip_tbind_f(block_b,2,22,2,7,3,2,3);
     vsip_index h,i,j;

     vsip_blockadmit_f(block_a,VSIP_TRUE);

     /* copy <a> into <b> */
     for(h=0; h<2; h++)
       for(i=0; i<3; i++) 
         for(j=0; j<3; j++)
           vsip_tput_f(b,h,i,j,vsip_tget_f(a,h,i,j));
     /* check <a> against ans */
     printf("check unit stride compact view\n");
     for(h=0; h<2; h++)
       for(i=0; i<3; i++)
         for(j=0; j<3; j++) {
           vsip_scalar_f chk = fabs(ans[h][i][j] - vsip_tget_f(a,h,i,j));
           (chk < 0.0001) ? printf("correct\n") : printf("error\n");
           fflush(stdout);
     }
     printf("check general stride view\n");
     for(h=0; h<2; h++)
       for(i=0; i<3; i++)
         for(j=0; j<3; j++) {
           vsip_scalar_f chk = fabs(ans[h][i][j] - vsip_tget_f(b,h,i,j));
           (chk < 0.0001) ? printf("correct\n") : printf("error\n");
           fflush(stdout);
     }
     vsip_talldestroy_f(a);
     vsip_talldestroy_f(b);
   }
   return;
}
