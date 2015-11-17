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
/* $Id: VU_smvprod_d.c,v 2.0 2003/02/22 15:46:49 judd Exp $ */

/* Created RJudd July 9, 1999 */
/*          - ->              */
/* w = beta A v               */

#include<vsip.h>

void VU_smvprod_d(
     vsip_scalar_d beta,
     vsip_mview_d *A,
     vsip_vview_d *v,
     vsip_vview_d *w)
{
     vsip_mvprod_d(A,v,w);
     vsip_svmul_d(beta,w,w);
     return;
}
     
     
