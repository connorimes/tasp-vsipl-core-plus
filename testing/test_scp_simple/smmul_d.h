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
/* $Id: smmul_d.h,v 2.0 2003/02/22 15:23:27 judd Exp $ */
static void smmul_d(){
    printf("\n******\nTEST smmul_d\n");
    {
        vsip_scalar_d alpha = 1.2345;
        vsip_scalar_d data2[]= {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
        vsip_scalar_d ans[] = {1.3579, 5.4318, 9.5056,
                                 2.7159, 6.7897, 10.8636,
                                 4.0738, 8.1477, 12.2216};
        vsip_mview_d *m2 = vsip_mbind_d(
                  vsip_blockbind_d(data2,9,VSIP_MEM_NONE),0,1,3,3,3);
        vsip_mview_d *ma = vsip_mbind_d(
                  vsip_blockbind_d(ans,9,VSIP_MEM_NONE),0,3,3,1,3);
        vsip_mview_d *m3 = vsip_mcreate_d(3,3,VSIP_ROW,VSIP_MEM_NONE);
        vsip_mview_d *chk = vsip_mcreate_d(3,3,VSIP_ROW,VSIP_MEM_NONE);
        vsip_blockadmit_d(vsip_mgetblock_d(m2),VSIP_TRUE);
        vsip_blockadmit_d(vsip_mgetblock_d(ma),VSIP_TRUE);
        printf("call vsip_smmul_d(alpha,b,c)\n");
        printf("alpha = %f\n",alpha);
        printf("b =\n");VU_mprintm_d("8.6",m2);
        vsip_smmul_d(alpha,m2,m3);
        printf("c =\n");VU_mprintm_d("8.6",m3);
        printf("\nright answer =\n"); VU_mprintm_d("6.4",ma);
        vsip_msub_d(ma,m3,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,0,.0001,0,1,chk);
        if(fabs(vsip_msumval_d(chk)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        vsip_mcopy_d_d(m2,m3);
        printf(" b,c inplace\n");
        vsip_smmul_d(alpha,m3,m3);
        vsip_msub_d(ma,m3,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,0,.0001,0,1,chk);
        if(fabs(vsip_msumval_d(chk)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        vsip_malldestroy_d(m2);
        vsip_malldestroy_d(m3); vsip_malldestroy_d(ma);
        vsip_malldestroy_d(chk);
    }                                                       
      
    return;
}
