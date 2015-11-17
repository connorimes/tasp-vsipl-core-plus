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
/* $Id: windowsEx.c,v 2.0 2003/02/22 15:46:52 judd Exp $ */

#include<vsip.h>
#include<VU.h>

int main(){vsip_init((void*)0);
{
     vsip_vview_d* Bw = vsip_vcreate_blackman_d(101,0);
     vsip_vview_d* Hw = vsip_vcreate_hanning_d(101,0);
     vsip_vview_d* Kw = vsip_vcreate_kaiser_d(64,.5,0);
     printf("BW = "); VU_vprintm_d("6.8",Bw);
     printf("HW = "); VU_vprintm_d("6.8",Hw);
     printf("KW = "); VU_vprintm_d("6.8",Kw);
     vsip_valldestroy_d(Bw);
     vsip_valldestroy_d(Hw);
     vsip_valldestroy_d(Kw);
     }vsip_finalize((void*)0);return 0;
}
