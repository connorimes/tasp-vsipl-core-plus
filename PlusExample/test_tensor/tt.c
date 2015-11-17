#include<stdio.h>
#include<vsip.h>
#include<VU.h>

int
main()
{
   vsip_index z_i,y_i,x_i;
   vsip_scalar_f data[]  = {0.0, 0.01, 0.02, 0.03, \
                            0.1, 0.11, 0.12, 0.13, \
                            0.2, 0.21, 0.22, 0.23, \
                            1.0, 1.01, 1.02, 1.03, \
                            1.1, 1.11, 1.12, 1.13, \
                            1.2, 1.21, 1.22, 1.23, \
                            2.0, 2.01, 2.02, 2.03, \
                            2.1, 2.11, 2.12, 2.13, \
                            2.2, 2.21, 2.22, 2.23, \
                            3.0, 3.01, 3.02, 3.03, \
                            3.1, 3.11, 3.12, 3.13, \
                            3.2, 3.21, 3.22, 3.23};
    vsip_block_f *block  = vsip_blockbind_f(data,48,0);
    vsip_tview_f *tview  = vsip_tbind_f(block,0,12,4,4,3,1,4);

    vsip_tview_f *tview_a = vsip_tcreate_f(12,9,12,VSIP_LEADING,VSIP_MEM_NONE);
    vsip_block_f *block_a = vsip_tgetblock_f(tview_a);

    vsip_tview_f *tview_b = vsip_tsubview_f(tview_a,1,2,3,4,3,4);

    vsip_stride z_a_st = vsip_tgetzstride_f(tview_a);
    vsip_stride y_a_st = vsip_tgetystride_f(tview_a);
    vsip_stride x_a_st = vsip_tgetxstride_f(tview_a);

    vsip_offset b_o_calc = z_a_st + 2 * y_a_st + 3 * x_a_st;
    vsip_offset b_o_get  = vsip_tgetoffset_f(tview_b);

    vsip_tview_f *tview_c = vsip_tbind_f(block_a,b_o_calc,
                                            z_a_st,4,
                                            y_a_st,3,
                                            x_a_st,4);

    vsip_mview_f *mviewz_0 = vsip_tmatrixview_f(tview,VSIP_TMYX,0);
    vsip_mview_f *mviewz_1 = vsip_tmatrixview_f(tview,VSIP_TMYX,1);
    vsip_mview_f *mviewz_2 = vsip_tmatrixview_f(tview,VSIP_TMYX,2);
    vsip_mview_f *mviewz_3 = vsip_tmatrixview_f(tview,VSIP_TMYX,3);
    vsip_mview_f *mviewx_0 = vsip_tmatrixview_f(tview,VSIP_TMZY,0);
    vsip_mview_f *mviewx_1 = vsip_tmatrixview_f(tview,VSIP_TMZY,1);
    vsip_mview_f *mviewx_2 = vsip_tmatrixview_f(tview,VSIP_TMZY,2);
    vsip_mview_f *mviewx_3 = vsip_tmatrixview_f(tview,VSIP_TMZY,3);
    vsip_mview_f *mviewy_0 = vsip_tmatrixview_f(tview,VSIP_TMZX,0);
    vsip_mview_f *mviewy_1 = vsip_tmatrixview_f(tview,VSIP_TMZX,1);
    vsip_mview_f *mviewy_2 = vsip_tmatrixview_f(tview,VSIP_TMZX,2);
    vsip_vview_f *vview_x_1_0 = vsip_tvectview_f(tview,VSIP_TVX,1,0);
    vsip_vview_f *vview_y_2_1 = vsip_tvectview_f(tview,VSIP_TVY,2,1);
    vsip_vview_f *vview_z_1_2 = vsip_tvectview_f(tview,VSIP_TVZ,1,2);
    vsip_tview_f *ttview_YX = vsip_ttransview_f(tview,VSIP_TTRANS_YX);
    vsip_blockadmit_f(block,VSIP_TRUE);
    printf("z_a_st %d; y_a_st %d; x_a_st %d\n",z_a_st,y_a_st,x_a_st); fflush(stdout);
    printf("b_o_calc %ul; b_o_get %ul\n",b_o_calc,b_o_get); fflush(stdout);
    for(z_i = 0; z_i < vsip_tgetzlength_f(tview);z_i++)
       for(y_i = 0; y_i < vsip_tgetylength_f(tview);y_i++)
          for(x_i = 0; x_i < vsip_tgetxlength_f(tview);x_i++)
             vsip_tput_f(tview_b,z_i,y_i,x_i,vsip_tget_f(tview,z_i,y_i,x_i)); 
    printf("TMZY 0\n"); VU_mprintm_f("5.2",mviewx_0); 
    printf("TMZY 1\n"); VU_mprintm_f("5.2",mviewx_1); 
    printf("TMZY 2\n"); VU_mprintm_f("5.2",mviewx_2); 
    printf("TMZY 3\n"); VU_mprintm_f("5.2",mviewx_3); 
    printf("TMYX_0\n"); VU_mprintm_f("5.2",mviewz_0); 
    printf("TMYX_1\n"); VU_mprintm_f("5.2",mviewz_1); 
    printf("TMYX_2\n"); VU_mprintm_f("5.2",mviewz_2); 
    printf("TMYX_3\n"); VU_mprintm_f("5.2",mviewz_3); 
    printf("TMZX_0\n"); VU_mprintm_f("5.2",mviewy_0); 
    printf("TMZX_1\n"); VU_mprintm_f("5.2",mviewy_1); 
    printf("TMZX_2\n"); VU_mprintm_f("5.2",mviewy_2); 
    printf("tensor\n"); VU_tprintm_f("5.2",tview);
    printf("tensor_a\n"); VU_tprintm_f("5.2",tview_a);
    printf("tensor_b\n"); VU_tprintm_f("5.2",tview_b);
    printf("tensor_c\n"); VU_tprintm_f("5.2",tview_c);
    printf("vector vview_x_1_0\n"); VU_vprintm_f("5.2",vview_x_1_0);
    printf("vector vview_y_2_1\n"); VU_vprintm_f("5.2",vview_y_2_1);
    printf("vector vview_z_1_2\n"); VU_vprintm_f("5.2",vview_z_1_2);
    printf("tensor ttview_YX\n"); VU_tprintm_f("5.2",ttview_YX);
    vsip_mdestroy_f(mviewx_0);
    vsip_mdestroy_f(mviewx_1);
    vsip_mdestroy_f(mviewx_2);
    vsip_mdestroy_f(mviewx_3);
    vsip_mdestroy_f(mviewz_0);
    vsip_mdestroy_f(mviewz_1);
    vsip_mdestroy_f(mviewz_2);
    vsip_mdestroy_f(mviewz_3);
    vsip_mdestroy_f(mviewy_0);
    vsip_mdestroy_f(mviewy_1);
    vsip_mdestroy_f(mviewy_2);
    vsip_vdestroy_f(vview_x_1_0);
    vsip_vdestroy_f(vview_y_2_1);
    vsip_vdestroy_f(vview_z_1_2);
    vsip_talldestroy_f(tview);
    vsip_tdestroy_f(tview_c);
    vsip_tdestroy_f(tview_b);
    vsip_talldestroy_f(tview_a);
    return 0;
}


