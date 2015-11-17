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
/* $Id: cvget_put_d.h,v 2.0 2003/02/22 15:23:33 judd Exp $ */
static void cvget_put_d(){
   printf("********\nTEST cvget_put_d\n");
   {
     vsip_scalar_d datar_a[]   = { 0,  1,  1, 0,   1, 0};
     vsip_scalar_d datai_a[]   = { 1, -1, -1, 1,  -1, 1};
                                 
     vsip_scalar_d ansr[]      = { 0,  1,  1, 0,   1, 0};
     vsip_scalar_d ansi[]      = { 1, -1, -1, 1,  -1, 1};
     vsip_cblock_d *block_a    = vsip_cblockbind_d(datar_a,datai_a,6,VSIP_MEM_NONE);
     vsip_cvview_d *a          = vsip_cvbind_d(block_a,0,1,6);

     vsip_cblock_d *block_b    = vsip_cblockcreate_d(50,VSIP_MEM_NONE);
     vsip_cvview_d *b          = vsip_cvbind_d(block_b, 35,-2,6);
     vsip_index i;

     vsip_cblockadmit_d(block_a,VSIP_TRUE);

     /* copy <a> into <b> */
     for(i=0; i<6; i++) vsip_cvput_d(b,i,vsip_cvget_d(a,i));
     /* check <a> against ans */
     printf("check unit stride compact view\n");
     for(i=0; i<6; i++){
        vsip_cscalar_d chk = vsip_cvget_d(a,i);
        chk.r = chk.r - ansr[i]; chk.i = chk.i - ansi[i];
        chk.r = chk.r * chk.r + chk.i * chk.i;
        (chk.r < 0.0001) ? printf("correct\n") : printf("error\n");
        fflush(stdout);
     }
     printf("check general stride view\n");
     for(i=0; i<6; i++){
        vsip_cscalar_d chk = vsip_cvget_d(b,i);
        chk.r = chk.r - ansr[i]; chk.i = chk.i - ansi[i];
        chk.r = chk.r * chk.r + chk.i * chk.i;
        (chk.r < 0.0001) ? printf("correct\n") : printf("error\n");
        fflush(stdout);
     }
     vsip_cvalldestroy_d(a);
     vsip_cvalldestroy_d(b);
   }
   return;
}
