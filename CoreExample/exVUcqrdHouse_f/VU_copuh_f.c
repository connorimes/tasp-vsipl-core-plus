/* Created RJudd July 9, 1999 */
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
/* $Id: VU_copuh_f.c,v 2.0 2003/02/22 15:35:58 judd Exp $ */

/* Outer Product Update       */
/*            T               */
/* A = A + x y                */
/* Golub and Van Loan, Third Edition, 1.1.9 */
/* Modified Aug 26, 1999 from opu real to complex */

#include<vsip.h>

void VU_copuh_f(
    vsip_cmview_f *A,
    vsip_cvview_f *x,
    vsip_cvview_f *y)
{
     vsip_length m = vsip_cmgetcollength_f(A);
     vsip_length n = vsip_cmgetrowlength_f(A);
     vsip_length i,j;
     vsip_cscalar_f temp;
     for(i=0; i<m; i++)
         for(j=0; j<n; j++){
             temp = vsip_cjmul_f(vsip_cvget_f(x,i),vsip_cvget_f(y,j));
             vsip_cmput_f(A,i,j,vsip_cadd_f(vsip_cmget_f(A,i,j),temp));
         }
     return;
}
