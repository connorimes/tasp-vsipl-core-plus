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
/* $Id: VU_rscmvprod_f.c,v 2.0 2003/02/22 15:35:58 judd Exp $ */

/*          - ->              */
/* w = beta A v               */
/* Modified Aug 2i, 1999 to rscmvprod */

#include<vsip.h>

void VU_rscmvprod_f(
     vsip_scalar_f beta,
     vsip_cmview_f *A,
     vsip_cvview_f *v,
     vsip_cvview_f *w)
{
     vsip_cmvprod_f(A,v,w);
     vsip_rscvmul_f(beta,w,w);
     return;
}
     
     
