#include<stdio.h>
#include<vsip.h>
#include<VU.h>

int
main()
{
   vsip_index z_i,y_i,x_i;
   vsip_scalar_i data[]  = {0, 1, 2, 3, \
                            1, 11, 12, 13, \
                            2, 21, 22, 23, \
                            10, 101, 102, 103, \
                            11, 111, 112, 113, \
                            12, 121, 122, 123, \
                            20, 201, 202, 203, \
                            21, 211, 212, 213, \
                            22, 221, 222, 223, \
                            30, 301, 302, 303, \
                            31, 311, 312, 313, \
                            32, 321, 322, 323};
    vsip_block_i *block  = vsip_blockbind_i(data,48,0);
    vsip_tview_i *tview  = vsip_tbind_i(block,0,12,4,4,3,1,4);

    vsip_tview_i *tview_a = vsip_tcreate_i(12,9,12,VSIP_LEADING,VSIP_MEM_NONE);
    vsip_block_i *block_a = vsip_tgetblock_i(tview_a);

    vsip_tview_i *tview_b = vsip_tsubview_i(tview_a,1,2,3,4,3,4);

    vsip_stride z_a_st = vsip_tgetzstride_i(tview_a);
    vsip_stride y_a_st = vsip_tgetystride_i(tview_a);
    vsip_stride x_a_st = vsip_tgetxstride_i(tview_a);

    vsip_offset b_o_calc = z_a_st + 2 * y_a_st + 3 * x_a_st;
    vsip_offset b_o_get  = vsip_tgetoffset_i(tview_b);

    vsip_tview_i *tview_c = vsip_tbind_i(block_a,b_o_calc,
                                            z_a_st,4,
                                            y_a_st,3,
                                            x_a_st,4);

    vsip_mview_i *mviewz_0 = vsip_tmatrixview_i(tview,VSIP_TMYX,0);
    vsip_mview_i *mviewz_1 = vsip_tmatrixview_i(tview,VSIP_TMYX,1);
    vsip_mview_i *mviewz_2 = vsip_tmatrixview_i(tview,VSIP_TMYX,2);
    vsip_mview_i *mviewz_3 = vsip_tmatrixview_i(tview,VSIP_TMYX,3);
    vsip_mview_i *mviewx_0 = vsip_tmatrixview_i(tview,VSIP_TMZY,0);
    vsip_mview_i *mviewx_1 = vsip_tmatrixview_i(tview,VSIP_TMZY,1);
    vsip_mview_i *mviewx_2 = vsip_tmatrixview_i(tview,VSIP_TMZY,2);
    vsip_mview_i *mviewx_3 = vsip_tmatrixview_i(tview,VSIP_TMZY,3);
    vsip_mview_i *mviewy_0 = vsip_tmatrixview_i(tview,VSIP_TMZX,0);
    vsip_mview_i *mviewy_1 = vsip_tmatrixview_i(tview,VSIP_TMZX,1);
    vsip_mview_i *mviewy_2 = vsip_tmatrixview_i(tview,VSIP_TMZX,2);
    vsip_vview_i *vview_x_1_0 = vsip_tvectview_i(tview,VSIP_TVX,1,0);
    vsip_vview_i *vview_y_2_1 = vsip_tvectview_i(tview,VSIP_TVY,2,1);
    vsip_vview_i *vview_z_1_2 = vsip_tvectview_i(tview,VSIP_TVZ,1,2);
    vsip_tview_i *ttview_YX = vsip_ttransview_i(tview,VSIP_TTRANS_YX);
    vsip_blockadmit_i(block,VSIP_TRUE);
    printf("z_a_st %d; y_a_st %d; x_a_st %d\n",z_a_st,y_a_st,x_a_st); fflush(stdout);
    printf("b_o_calc %ul; b_o_get %ul\n",b_o_calc,b_o_get); fflush(stdout);
    for(z_i = 0; z_i < vsip_tgetzlength_i(tview);z_i++)
       for(y_i = 0; y_i < vsip_tgetylength_i(tview);y_i++)
          for(x_i = 0; x_i < vsip_tgetxlength_i(tview);x_i++)
             vsip_tput_i(tview_b,z_i,y_i,x_i,vsip_tget_i(tview,z_i,y_i,x_i)); 
    printf("TMZY 0\n"); VU_mprintm_i("5",mviewx_0); 
    printf("TMZY 1\n"); VU_mprintm_i("5",mviewx_1); 
    printf("TMZY 2\n"); VU_mprintm_i("5",mviewx_2); 
    printf("TMZY 3\n"); VU_mprintm_i("5",mviewx_3); 
    printf("TMYX_0\n"); VU_mprintm_i("5",mviewz_0); 
    printf("TMYX_1\n"); VU_mprintm_i("5",mviewz_1); 
    printf("TMYX_2\n"); VU_mprintm_i("5",mviewz_2); 
    printf("TMYX_3\n"); VU_mprintm_i("5",mviewz_3); 
    printf("TMZX_0\n"); VU_mprintm_i("5",mviewy_0); 
    printf("TMZX_1\n"); VU_mprintm_i("5",mviewy_1); 
    printf("TMZX_2\n"); VU_mprintm_i("5",mviewy_2); 
    printf("tensor\n"); VU_tprintm_i("5",tview);
    printf("tensor_a\n"); VU_tprintm_i("5",tview_a);
    printf("tensor_b\n"); VU_tprintm_i("5",tview_b);
    printf("tensor_c\n"); VU_tprintm_i("5",tview_c);
    printf("vector vview_x_1_0\n"); VU_vprintm_i("5",vview_x_1_0);
    printf("vector vview_y_2_1\n"); VU_vprintm_i("5",vview_y_2_1);
    printf("vector vview_z_1_2\n"); VU_vprintm_i("5",vview_z_1_2);
    printf("tensor ttview_YX\n"); VU_tprintm_i("5",ttview_YX);
    vsip_mdestroy_i(mviewx_0);
    vsip_mdestroy_i(mviewx_1);
    vsip_mdestroy_i(mviewx_2);
    vsip_mdestroy_i(mviewx_3);
    vsip_mdestroy_i(mviewz_0);
    vsip_mdestroy_i(mviewz_1);
    vsip_mdestroy_i(mviewz_2);
    vsip_mdestroy_i(mviewz_3);
    vsip_mdestroy_i(mviewy_0);
    vsip_mdestroy_i(mviewy_1);
    vsip_mdestroy_i(mviewy_2);
    vsip_vdestroy_i(vview_x_1_0);
    vsip_vdestroy_i(vview_y_2_1);
    vsip_vdestroy_i(vview_z_1_2);
    vsip_talldestroy_i(tview);
    vsip_tdestroy_i(tview_c);
    vsip_tdestroy_i(tview_b);
    vsip_talldestroy_i(tview_a);
    return 0;
}


