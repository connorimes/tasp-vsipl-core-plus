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
/* $Id: windowsEx.c,v 2.0 2003/02/22 15:31:56 judd Exp $ */

#include<vsip.h>
#include<VU.h>

int main(){vsip_init((void*)0);
{
     vsip_vview_f* Bw = vsip_vcreate_blackman_f(101,0);
     vsip_vview_f* Hw = vsip_vcreate_hanning_f(101,0);
     vsip_vview_f* Kw = vsip_vcreate_kaiser_f(64,10,0);
     vsip_vview_f* Cf = vsip_vcreate_cheby_f(64,100,0);
     vsip_vview_d* Cd = vsip_vcreate_cheby_d(64,100,0);
     printf("BW = "); VU_vprintm_f("6.8",Bw);
     printf("HW = "); VU_vprintm_f("6.8",Hw);
     printf("KW = "); VU_vprintm_f("6.8",Kw);
     printf("CF = "); VU_vprintm_f("6.8",Cf);
     printf("CD = "); VU_vprintm_d("6.8",Cd);
     vsip_valldestroy_f(Bw);
     vsip_valldestroy_f(Hw);
     vsip_valldestroy_f(Kw);
     vsip_valldestroy_f(Cf);
     vsip_valldestroy_d(Cd);
     } vsip_finalize((void*)0); return 0;
}
