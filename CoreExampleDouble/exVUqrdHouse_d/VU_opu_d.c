
/* Created RJudd July 9, 1998 */
/* SPAWARSYSCEN D881          */
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
/* $Id: VU_opu_d.c,v 2.0 2003/02/22 15:46:48 judd Exp $ */
/* Outer Product Update       */
/*            T               */
/* A = A + x y                */
/* Golub and Van Loan, Third Edition, 1.1.9 */

#include<vsip.h>

void VU_opu_d(
    vsip_mview_d *A,
    vsip_vview_d *x,
    vsip_vview_d *y)
{
     vsip_length m = vsip_mgetcollength_d(A);
     vsip_length n = vsip_mgetrowlength_d(A);
     vsip_length i,j;
     for(i=0; i<m; i++)
         for(j=0; j<n; j++)
             vsip_mput_d(A,i,j,vsip_mget_d(A,i,j) + vsip_vget_d(x,i) * vsip_vget_d(y,j));
     return;
}
