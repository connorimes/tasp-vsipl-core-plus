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
/* $Id: nrandomEx.c,v 2.0 2003/02/22 15:38:21 judd Exp $ */

#include<vsip.h>
#include<VU.h>
#define N 30000

int main(){vsip_init((void*)0);
{
     vsip_vview_f *n = vsip_vcreate_f(N,0);
     vsip_vview_f *u = vsip_vcreate_f(N,0);
     vsip_randstate *state = vsip_randcreate(52,1,1,VSIP_PRNG);
     vsip_vrandu_f(state,u);
     vsip_vrandn_f(state,n);
     vsip_randdestroy(state);
     printf("up =");VU_vprintm_f("8.6",u);
     printf("np =");VU_vprintm_f("8.6",n);
     state = vsip_randcreate(52,1,1,VSIP_NPRNG);
     vsip_vrandu_f(state,u);
     vsip_vrandn_f(state,n);
     vsip_randdestroy(state);
     printf("un =");VU_vprintm_f("8.6",u);
     printf("nn =");VU_vprintm_f("8.6",n);
     vsip_valldestroy_f(u);
     vsip_valldestroy_f(n);
     } vsip_finalize((void*)0); return 0;
}
