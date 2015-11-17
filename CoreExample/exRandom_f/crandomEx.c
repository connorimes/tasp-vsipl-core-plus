/* Created by RJudd */
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
/* $Id: crandomEx.c,v 2.0 2003/02/22 15:38:21 judd Exp $ */

#include<stdio.h>
#include<vsip.h>

#define L 40                   /*length*/
#define NS 1
#define TYPE VSIP_PRNG

int main(){vsip_init((void*)0);
{

    int i;
    vsip_cvview_f* data      = vsip_cvcreate_f(L,0);
    vsip_vview_f* datar   = vsip_vcreate_f(2 * L,0);
    vsip_randstate *state  = vsip_randcreate(7,NS,1,TYPE);
    vsip_randstate *stater  = vsip_randcreate(7,NS,1,TYPE);
    vsip_cvrandu_f(state,data);
    vsip_vrandu_f(stater,datar);
    for(i=0; i<2*L; i++)
        printf("%6.4f %6.4f\n",
             vsip_vget_f(datar,i),
             ((i%2) ? 
                vsip_imag_f(vsip_cvget_f(data,(i/2))) : 
                vsip_real_f(vsip_cvget_f(data,(i/2)))));
    /*destroy the vector views and any associated blocks*/
    vsip_cvalldestroy_f(data);
    vsip_valldestroy_f(datar);
    vsip_randdestroy(state);
    vsip_randdestroy(stater);
    } vsip_finalize((void*)0); return 1;
}
