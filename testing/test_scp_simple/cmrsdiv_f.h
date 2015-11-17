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
/* $Id: cmrsdiv_f.h,v 2.0 2003/02/22 15:23:21 judd Exp $ */
static void cmrsdiv_f(){
    printf("\n******\nTEST cmrsdiv_f\n");
    {
        vsip_scalar_f data1 = 5.5;
        vsip_scalar_f data2_r[]= {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
        vsip_scalar_f data2_i[]= {-1.1, 2.2, -3.3, 4.4, -5.5, 6.6, -7.7, 8.8, -9.9};
        vsip_scalar_f ans_r[] =  {0.2000, 0.8000, 1.4000, 0.4000, 1.0000, 1.6000, 0.6000, 1.2000, 1.8000 };
        vsip_scalar_f ans_i[] =  { -0.2000, 0.8000,-1.4000, 0.4000,-1.0000, 1.6000, -0.6000, 1.2000,-1.8000 };
        vsip_cmview_f *m2 = vsip_cmbind_f(
                  vsip_cblockbind_f(data2_r,data2_i,9,VSIP_MEM_NONE),0,1,3,3,3);
        vsip_cmview_f *ma = vsip_cmbind_f(
                  vsip_cblockbind_f(ans_r,ans_i,9,VSIP_MEM_NONE),0,3,3,1,3);
        vsip_cmview_f *m3 = vsip_cmcreate_f(3,3,VSIP_ROW,VSIP_MEM_NONE);
        vsip_cmview_f *chk = vsip_cmcreate_f(3,3,VSIP_ROW,VSIP_MEM_NONE);
        vsip_mview_f  *chk_r = vsip_mrealview_f(chk);
        vsip_cblockadmit_f(vsip_cmgetblock_f(m2),VSIP_TRUE);
        vsip_cblockadmit_f(vsip_cmgetblock_f(ma),VSIP_TRUE);
        printf("call vsip_cmrsdiv_f(a,beta,c)\n");
        printf("a =\n");VU_cmprintm_f("8.6",m2);
        printf("beta = %f\n",data1);
        vsip_cmrsdiv_f(m2,data1,m3);
        printf("c =\n");VU_cmprintm_f("8.6",m3);
        printf("\nright answer =\n"); VU_cmprintm_f("6.4",ma);
        vsip_cmsub_f(ma,m3,chk); vsip_cmmag_f(chk,chk_r); vsip_mclip_f(chk_r,0,2 * .0001,0,1,chk_r);
        if(fabs(vsip_msumval_f(chk_r)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        vsip_cmcopy_f_f(m2,m3);
        printf("a,c inplace\n");
        vsip_cmrsdiv_f(m3,data1,m3);
        vsip_cmsub_f(ma,m3,chk); vsip_cmmag_f(chk,chk_r); vsip_mclip_f(chk_r,0,2 * .0001,0,1,chk_r);
        if(fabs(vsip_msumval_f(chk_r)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        vsip_cmalldestroy_f(m2);
        vsip_cmalldestroy_f(m3); vsip_cmalldestroy_f(ma);
        vsip_mdestroy_f(chk_r);    vsip_cmalldestroy_f(chk);
    }                                                       
      
    return;
}
