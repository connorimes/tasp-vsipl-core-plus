/* Created RJudd */
/* SPAWARSYSCEN D881 */
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
/* $Id: toeplitzEx.c,v 2.0 2003/02/22 15:46:42 judd Exp $ */

#include<vsip.h>
#include<VU.h>

int main(){vsip_init((void*)0);
{
    vsip_vview_f *t = vsip_vcreate_f(4,VSIP_MEM_NONE),
                 *x = vsip_vcreate_f(4,VSIP_MEM_NONE),
                 *w = vsip_vcreate_f(4,VSIP_MEM_NONE),
                 *y = vsip_vcreate_f(4,VSIP_MEM_NONE);
    vsip_vput_f(t,(vsip_index)0,(vsip_scalar_f)5.0);
    vsip_vput_f(t,(vsip_index)1,(vsip_scalar_f)0.5);
    vsip_vput_f(t,(vsip_index)2,(vsip_scalar_f)0.2);
    vsip_vput_f(t,(vsip_index)3,(vsip_scalar_f)0.1);
    vsip_vput_f(y,(vsip_index)0,(vsip_scalar_f)4.0);
    vsip_vput_f(y,(vsip_index)1,(vsip_scalar_f)-1.0);
    vsip_vput_f(y,(vsip_index)2,(vsip_scalar_f)3.0);
    vsip_vput_f(y,(vsip_index)3,(vsip_scalar_f)-2.0);
    printf("t=");VU_vprintm_f("6.4",t);
    printf("y=");VU_vprintm_f("6.4",y);
    vsip_toepsol_f(t,y,w,x);
    printf("t=\n");VU_vprintm_f("6.4",t);
    printf("y=\n");VU_vprintm_f("6.4",y);
    printf("w=\n");VU_vprintm_f("6.4",w);
    printf("x=\n");VU_vprintm_f("6.4",x);
    vsip_valldestroy_f(t);
    vsip_valldestroy_f(x);
    vsip_valldestroy_f(w);
    vsip_valldestroy_f(y);
    }vsip_finalize((void*)0);return 0;
}
