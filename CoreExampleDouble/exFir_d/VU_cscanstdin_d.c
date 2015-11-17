
/* Created RJudd October 1998 */
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
/* $Id: VU_cscanstdin_d.c,v 2.0 2003/02/22 15:46:24 judd Exp $ */

#include<vsip.h>

vsip_length VU_cscanstdin_d(vsip_cvview_d *x)
{
    vsip_length n = 0;
    vsip_length m = 1;
    vsip_length o = 0;
    vsip_scalar_d xsr;
    vsip_scalar_d xsi;
    vsip_cvattr_d attr;
    vsip_cvgetattrib_d(x,&attr);
    while(n < attr.length){
       ((m = scanf("%lf %lf",&xsr,&xsi)) == 2) ? vsip_cvput_d(x,n++,vsip_cmplx_d(xsr,xsi)) : vsip_cvput_d(x,n++,vsip_cmplx_d(0,0)); 
       if(m == 2) o++;
    }
    return o;
}
