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
/* $Id: csmmul_d.h,v 2.0 2003/02/22 15:23:22 judd Exp $ */
static void csmmul_d(){
    printf("\n******\nTEST csmmul_d\n");
    {
        vsip_cscalar_d data1 = vsip_cmplx_d(5.5,-1.5);
        vsip_scalar_d data2_r[]= {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
        vsip_scalar_d data2_i[]= {-1.1, 2.2, -3.3, 4.4, -5.5, 6.6, -7.7, 8.8, -9.9};
        vsip_scalar_d ans_r[] =  {4.40, 30.80, 30.80, 15.40, 22.00, 61.60, 13.20, 46.20, 39.60};
        vsip_scalar_d ans_i[] =  {-7.70, 17.60, -53.90, 8.80, -38.50, 35.20, -23.10, 26.40, -69.30};

        vsip_cmview_d *m2 = vsip_cmbind_d(
                  vsip_cblockbind_d(data2_r,data2_i,9,VSIP_MEM_NONE),0,1,3,3,3);
        vsip_cmview_d *ma = vsip_cmbind_d(
                  vsip_cblockbind_d(ans_r,ans_i,9,VSIP_MEM_NONE),0,3,3,1,3);
        vsip_cmview_d *m3 = vsip_cmcreate_d(3,3,VSIP_ROW,VSIP_MEM_NONE);
        vsip_cmview_d *chk = vsip_cmcreate_d(3,3,VSIP_ROW,VSIP_MEM_NONE);
        vsip_mview_d  *chk_r = vsip_mrealview_d(chk);
        vsip_cblockadmit_d(vsip_cmgetblock_d(m2),VSIP_TRUE);
        vsip_cblockadmit_d(vsip_cmgetblock_d(ma),VSIP_TRUE);
        printf("call vsip_csmmul_d(alpha,b,c)\n");
        printf("alpha = %f %+fi\n",vsip_real_d(data1),vsip_imag_d(data1));
        printf("b =\n");VU_cmprintm_d("8.6",m2);
        vsip_csmmul_d(data1,m2,m3);
        printf("c =\n");VU_cmprintm_d("8.6",m3);
        printf("\nright answer =\n"); VU_cmprintm_d("6.4",ma);
        vsip_cmsub_d(ma,m3,chk); vsip_cmmag_d(chk,chk_r); vsip_mclip_d(chk_r,0,2 * .0001,0,1,chk_r);
        if(fabs(vsip_msumval_d(chk_r)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        vsip_cmcopy_d_d(m2,m3);
        printf(" b,c inplace\n");
        vsip_csmmul_d(data1,m3,m3);
        vsip_cmsub_d(ma,m3,chk); vsip_cmmag_d(chk,chk_r); vsip_mclip_d(chk_r,0,2 * .0001,0,1,chk_r);
        if(fabs(vsip_msumval_d(chk_r)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        vsip_cmalldestroy_d(m2);
        vsip_cmalldestroy_d(m3); vsip_cmalldestroy_d(ma);
        vsip_mdestroy_d(chk_r);    vsip_cmalldestroy_d(chk);
    }                                                       
      
    return;
}
