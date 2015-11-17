#include<stdio.h>
#include<vsip.h>
#include<VU.h>

int
main()
{
   vsip_index z_si,y_si,x_si;
   vsip_scalar_si data[]  = {0, 1, 2, 3, \
                            01, 011, 012, 013, \
                            02, 021, 022, 023, \
                            10, 101, 102, 103, \
                            11, 111, 112, 113, \
                            12, 121, 122, 123, \
                            20, 201, 202, 203, \
                            21, 211, 212, 213, \
                            22, 221, 222, 223, \
                            30, 301, 302, 303, \
                            31, 311, 312, 313, \
                            32, 321, 322, 323};
    vsip_block_si *block  = vsip_blockbind_si(data,48,0);
    vsip_tview_si *tview  = vsip_tbind_si(block,0,12,4,4,3,1,4);

    vsip_tview_si *tview_a = vsip_tcreate_si(12,9,12,VSIP_LEADING,VSIP_MEM_NONE);
    vsip_block_si *block_a = vsip_tgetblock_si(tview_a);

    vsip_tview_si *tview_b = vsip_tsubview_si(tview_a,1,2,3,4,3,4);

    vsip_stride z_a_st = vsip_tgetzstride_si(tview_a);
    vsip_stride y_a_st = vsip_tgetystride_si(tview_a);
    vsip_stride x_a_st = vsip_tgetxstride_si(tview_a);

    vsip_offset b_o_calc = z_a_st + 2 * y_a_st + 3 * x_a_st;
    vsip_offset b_o_get  = vsip_tgetoffset_si(tview_b);

    vsip_tview_si *tview_c = vsip_tbind_si(block_a,b_o_calc,
                                            z_a_st,4,
                                            y_a_st,3,
                                            x_a_st,4);

    vsip_mview_si *mviewz_0 = vsip_tmatrixview_si(tview,VSIP_TMYX,0);
    vsip_mview_si *mviewz_1 = vsip_tmatrixview_si(tview,VSIP_TMYX,1);
    vsip_mview_si *mviewz_2 = vsip_tmatrixview_si(tview,VSIP_TMYX,2);
    vsip_mview_si *mviewz_3 = vsip_tmatrixview_si(tview,VSIP_TMYX,3);
    vsip_mview_si *mviewx_0 = vsip_tmatrixview_si(tview,VSIP_TMZY,0);
    vsip_mview_si *mviewx_1 = vsip_tmatrixview_si(tview,VSIP_TMZY,1);
    vsip_mview_si *mviewx_2 = vsip_tmatrixview_si(tview,VSIP_TMZY,2);
    vsip_mview_si *mviewx_3 = vsip_tmatrixview_si(tview,VSIP_TMZY,3);
    vsip_mview_si *mviewy_0 = vsip_tmatrixview_si(tview,VSIP_TMZX,0);
    vsip_mview_si *mviewy_1 = vsip_tmatrixview_si(tview,VSIP_TMZX,1);
    vsip_mview_si *mviewy_2 = vsip_tmatrixview_si(tview,VSIP_TMZX,2);
    vsip_vview_si *vview_x_1_0 = vsip_tvectview_si(tview,VSIP_TVX,1,0);
    vsip_vview_si *vview_y_2_1 = vsip_tvectview_si(tview,VSIP_TVY,2,1);
    vsip_vview_si *vview_z_1_2 = vsip_tvectview_si(tview,VSIP_TVZ,1,2);
    vsip_tview_si *ttview_YX = vsip_ttransview_si(tview,VSIP_TTRANS_YX);
    vsip_blockadmit_si(block,VSIP_TRUE);
    printf("z_a_st %d; y_a_st %d; x_a_st %d\n",z_a_st,y_a_st,x_a_st); fflush(stdout);
    printf("b_o_calc %ul; b_o_get %ul\n",b_o_calc,b_o_get); fflush(stdout);
    for(z_si = 0; z_si < vsip_tgetzlength_si(tview);z_si++)
       for(y_si = 0; y_si < vsip_tgetylength_si(tview);y_si++)
          for(x_si = 0; x_si < vsip_tgetxlength_si(tview);x_si++)
             vsip_tput_si(tview_b,z_si,y_si,x_si,vsip_tget_si(tview,z_si,y_si,x_si)); 
    printf("TMZY 0\n"); VU_mprintm_si("5",mviewx_0); 
    printf("TMZY 1\n"); VU_mprintm_si("5",mviewx_1); 
    printf("TMZY 2\n"); VU_mprintm_si("5",mviewx_2); 
    printf("TMZY 3\n"); VU_mprintm_si("5",mviewx_3); 
    printf("TMYX_0\n"); VU_mprintm_si("5",mviewz_0); 
    printf("TMYX_1\n"); VU_mprintm_si("5",mviewz_1); 
    printf("TMYX_2\n"); VU_mprintm_si("5",mviewz_2); 
    printf("TMYX_3\n"); VU_mprintm_si("5",mviewz_3); 
    printf("TMZX_0\n"); VU_mprintm_si("5",mviewy_0); 
    printf("TMZX_1\n"); VU_mprintm_si("5",mviewy_1); 
    printf("TMZX_2\n"); VU_mprintm_si("5",mviewy_2); 
    printf("tensor\n"); VU_tprintm_si("5",tview);
    printf("tensor_a\n"); VU_tprintm_si("5",tview_a);
    printf("tensor_b\n"); VU_tprintm_si("5",tview_b);
    printf("tensor_c\n"); VU_tprintm_si("5",tview_c);
    printf("vector vview_x_1_0\n"); VU_vprintm_si("5",vview_x_1_0);
    printf("vector vview_y_2_1\n"); VU_vprintm_si("5",vview_y_2_1);
    printf("vector vview_z_1_2\n"); VU_vprintm_si("5",vview_z_1_2);
    printf("tensor ttview_YX\n");   VU_tprintm_si("5",ttview_YX);
    vsip_mdestroy_si(mviewx_0);
    vsip_mdestroy_si(mviewx_1);
    vsip_mdestroy_si(mviewx_2);
    vsip_mdestroy_si(mviewx_3);
    vsip_mdestroy_si(mviewz_0);
    vsip_mdestroy_si(mviewz_1);
    vsip_mdestroy_si(mviewz_2);
    vsip_mdestroy_si(mviewz_3);
    vsip_mdestroy_si(mviewy_0);
    vsip_mdestroy_si(mviewy_1);
    vsip_mdestroy_si(mviewy_2);
    vsip_vdestroy_si(vview_x_1_0);
    vsip_vdestroy_si(vview_y_2_1);
    vsip_vdestroy_si(vview_z_1_2);
    vsip_talldestroy_si(tview); 
    vsip_tdestroy_si(tview_c);
    vsip_tdestroy_si(tview_b); 
    vsip_talldestroy_si(tview_a); 
    return 0;
}


