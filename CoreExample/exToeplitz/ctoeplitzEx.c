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
/* $Id: ctoeplitzEx.c,v 2.0 2003/02/22 15:36:57 judd Exp $ */

#include<vsip.h>
#include<VU.h>

int main(){vsip_init((void*)0);
{
    int retval = 0;
    vsip_cvview_f *t = vsip_cvcreate_f(4,VSIP_MEM_NONE),
                 *x = vsip_cvcreate_f(4,VSIP_MEM_NONE),
                 *w = vsip_cvcreate_f(4,VSIP_MEM_NONE),
                 *y = vsip_cvcreate_f(4,VSIP_MEM_NONE);
/*    vsip_cvput_f(t,(vsip_index)0,vsip_cmplx_f(5.0,0));
    vsip_cvput_f(t,(vsip_index)1,vsip_cmplx_f(0.5,.1));
    vsip_cvput_f(t,(vsip_index)2,vsip_cmplx_f(0.2,.1));
    vsip_cvput_f(t,(vsip_index)3,vsip_cmplx_f(0.1,.15)); */

    vsip_cvput_f(t,(vsip_index)0,vsip_cmplx_f(1.0,0));
    vsip_cvput_f(t,(vsip_index)1,vsip_cmplx_f(0.0,.4));
    vsip_cvput_f(t,(vsip_index)2,vsip_cmplx_f(0.0,.2));
    vsip_cvput_f(t,(vsip_index)3,vsip_cmplx_f(0.0,.15)); 

    vsip_cvput_f(y,(vsip_index)0,vsip_cmplx_f(4.0,1));
    vsip_cvput_f(y,(vsip_index)1,vsip_cmplx_f(-1.0,2));
    vsip_cvput_f(y,(vsip_index)2,vsip_cmplx_f(3.0,3));
    vsip_cvput_f(y,(vsip_index)3,vsip_cmplx_f(-2.0,-4));
    printf("t=\n");VU_cvprintm_f("6.4",t);
    printf("y=\n");VU_cvprintm_f("6.4",y);
    retval = vsip_ctoepsol_f(t,y,w,x);
    printf("%d\n",retval);
    printf("t=\n");VU_cvprintm_f("6.4",t);
    printf("y=\n");VU_cvprintm_f("6.4",y);
    printf("w=\n");VU_cvprintm_f("6.4",w);
    printf("x=\n");VU_cvprintm_f("6.4",x);
    vsip_cvalldestroy_f(t);
    vsip_cvalldestroy_f(x);
    vsip_cvalldestroy_f(w);
    vsip_cvalldestroy_f(y);
    } vsip_finalize((void*)0); return 0;
}
