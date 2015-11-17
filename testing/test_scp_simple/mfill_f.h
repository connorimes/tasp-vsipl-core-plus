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
/* $Id: mfill_f.h,v 2.0 2003/02/22 15:23:24 judd Exp $ */
static void mfill_f(){
    printf("\n******\nTEST mfill_f\n");
    {
        vsip_scalar_f alpha = 1.2345;
        vsip_scalar_f ans[] = {1.2345,1.2345,1.2345,1.2345,1.2345,1.2345,1.2345,1.2345,1.2345};
        vsip_mview_f *ma = vsip_mbind_f(
                  vsip_blockbind_f(ans,9,VSIP_MEM_NONE),0,3,3,1,3);
        vsip_mview_f *chk = vsip_mcreate_f(3,3,VSIP_ROW,VSIP_MEM_NONE);
        vsip_mview_f *B = vsip_mcreate_f(9,9,VSIP_COL,VSIP_MEM_NONE);
        vsip_mview_f *b = vsip_msubview_f(B,2,2,3,3);
        vsip_blockadmit_f(vsip_mgetblock_f(ma),VSIP_TRUE);
        vsip_mputrowstride_f(b,4);
        printf("call vsip_mfill_f(alpha,b)\n");
        printf("alpha = %f\n",alpha);
        vsip_mfill_f(alpha,b);
        printf("b =\n");VU_mprintm_f("8.6",b);
        printf("\nright answer =\n"); VU_mprintm_f("6.4",ma);
        vsip_msub_f(ma,b,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,0,.0001,0,1,chk);
        if(fabs(vsip_msumval_f(chk)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        vsip_mdestroy_f(b);
        vsip_malldestroy_f(B);
        vsip_malldestroy_f(ma);
        vsip_malldestroy_f(chk);
    }                                                       
      
    return;
}
