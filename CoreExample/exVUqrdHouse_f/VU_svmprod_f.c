/* Created RJudd July 9, 1999 */
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
/* $Id: VU_svmprod_f.c,v 2.0 2003/02/22 15:34:27 judd Exp $ */

/*          -T ->              */
/* w = beta A  v               */

#include<vsip.h>

void VU_svmprod_f(
     vsip_scalar_f beta,
     vsip_vview_f *v,
     vsip_mview_f *A,
     vsip_vview_f *w)
{
     vsip_vmprod_f(v,A,w);
     vsip_svmul_f(beta,w,w);
     return;
}
     
     
