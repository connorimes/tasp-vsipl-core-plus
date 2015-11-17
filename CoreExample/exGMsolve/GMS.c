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
/* $Id: GMS.c,v 2.0 2003/02/22 15:40:27 judd Exp $ */

#include<vsip.h>
#include<VU.h>

int main(){vsip_init((void*)0);
{
    vsip_mview_f *A = vsip_mcreate_f(3,3,VSIP_ROW,VSIP_MEM_NONE);
    vsip_vview_f *t = vsip_vcreate_f(3,VSIP_MEM_NONE),
                 *x = vsip_vcreate_f(3,VSIP_MEM_NONE),
                 *w = vsip_vcreate_f(3,VSIP_MEM_NONE),
                 *y = vsip_vcreate_f(3,VSIP_MEM_NONE);
    vsip_vput_f(t,(vsip_index)0,(vsip_scalar_f)1.0);
    vsip_vput_f(t,(vsip_index)1,(vsip_scalar_f)0.5);
    vsip_vput_f(t,(vsip_index)2,(vsip_scalar_f)0.2);
    vsip_mput_f(A,(vsip_index)0,(vsip_index)0,(vsip_scalar_f)1.0);
    vsip_mput_f(A,(vsip_index)0,(vsip_index)1,(vsip_scalar_f)0.5);
    vsip_mput_f(A,(vsip_index)0,(vsip_index)2,(vsip_scalar_f)0.2);
    vsip_mput_f(A,(vsip_index)1,(vsip_index)1,(vsip_scalar_f)1.0);
    vsip_mput_f(A,(vsip_index)1,(vsip_index)0,(vsip_scalar_f)0.5);
    vsip_mput_f(A,(vsip_index)1,(vsip_index)2,(vsip_scalar_f)0.5);
    vsip_mput_f(A,(vsip_index)2,(vsip_index)2,(vsip_scalar_f)1.0);
    vsip_mput_f(A,(vsip_index)2,(vsip_index)0,(vsip_scalar_f)0.2);
    vsip_mput_f(A,(vsip_index)2,(vsip_index)1,(vsip_scalar_f)0.5);
    vsip_vput_f(y,(vsip_index)0,(vsip_scalar_f)4.0);
    vsip_vput_f(y,(vsip_index)1,(vsip_scalar_f)-1.0);
    vsip_vput_f(y,(vsip_index)2,(vsip_scalar_f)3.0);
    printf("check toeplitz\n");
    { /* check toeplitz */
      vsip_vview_f *tt = vsip_vcreate_f(3,VSIP_MEM_NONE);
      vsip_vview_f *yy = vsip_vcreate_f(3,VSIP_MEM_NONE);
      vsip_vcopy_f_f(t,tt); vsip_vcopy_f_f(y,yy);
      printf("t=\n");VU_vprintm_f("6.4",tt);
      printf("y=\n");VU_vprintm_f("6.4",yy);
      vsip_toepsol_f(tt,yy,w,x);
      printf("x=\n");VU_vprintm_f("6.4",x);
      vsip_valldestroy_f(tt);
      vsip_valldestroy_f(yy);
    } 
    printf("check LUD\n");
    { /* check LUD */
      vsip_mview_f *AA = vsip_mcreate_f(3,3,VSIP_ROW,VSIP_MEM_NONE);
      vsip_mview_f *yy = vsip_mcreate_f(3,1,VSIP_COL,VSIP_MEM_NONE);
      vsip_lu_f *lud = vsip_lud_create_f(3);
      vsip_mcopy_f_f(A,AA);
      { vsip_vview_f *temp = vsip_mcolview_f(yy,0);
        vsip_vcopy_f_f(y,temp);
        vsip_vdestroy_f(temp);
      }
      vsip_lud_f(lud,AA);
      vsip_lusol_f(lud,0,yy);
      printf("A = \n"); VU_mprintm_f("6.4",A);
      printf("y = \n"); VU_vprintm_f("6.4",y);
      printf("x = \n"); VU_mprintm_f("6.4",yy);
      vsip_malldestroy_f(AA);
      vsip_malldestroy_f(yy);
      vsip_lud_destroy_f(lud);
    }
    vsip_malldestroy_f(A);
    vsip_valldestroy_f(t);
    vsip_valldestroy_f(y);
    vsip_valldestroy_f(w);
    vsip_valldestroy_f(x);
    } vsip_finalize((void*)0); return 0;
}
