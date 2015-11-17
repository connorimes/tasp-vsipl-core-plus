/* Created RJudd July 21, 1999 */
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
/* $Id: VU_chouse_f.c,v 2.0 2003/02/22 15:35:57 judd Exp $ */

/* Householder Vector calculation */
/* Algorithm 5.1.1 Golub and Van Loan, Third Edition */

#include<vsip.h>
#include<VU.h>

void VU_chouse_f(
   vsip_cvview_f *x,
   vsip_cvview_f *v,
   vsip_scalar_f *beta)
{
   vsip_cscalar_f x_1  = vsip_cvget_f(x,0);
   vsip_scalar_f  x2n  = sqrt(vsip_real_f(vsip_cvjdot_f(x,x)));
   vsip_scalar_f x_1radius  = sqrt(x_1.r * x_1.r + x_1.i * x_1.i);
   x_1.r /= x_1radius; x_1.i /= x_1radius;
   x_1.r *= x2n;  x_1.i *= x2n;
   vsip_cvcopy_f_f(x,v);
   x_1 = vsip_csub_f(vsip_cvget_f(v,0),x_1);
   vsip_csvmul_f(vsip_crecip_f(x_1),v,v);
   vsip_cvput_f(v,0,vsip_cmplx_f(1,0));
   *beta = 2.0 /vsip_real_f(vsip_cvjdot_f(v,v));
   return;
}
