/* Created RJudd December 10, 1998 */
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
/* $Id: vsip_CMPLXm_f.c,v 2.0 2003/02/22 15:18:35 judd Exp $ */

#include<vsip.h>

void (vsip_CMPLX_f)(
  vsip_scalar_f a, vsip_scalar_f b,vsip_cscalar_f *r) {
  *r = vsip_cmplx_f(a,b);
}

