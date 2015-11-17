/* Created RJudd July 9, 1999 */
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
/* $Id: VU_chouseqr_f.c,v 2.0 2003/02/22 15:35:57 judd Exp $ */

/* In place decompose a matrix with R in the upper diagonal */
/* and v in the lower diagonal */
/* save normalizing beta values */
/* Algorithm 5.2.1 Golub & Van Loan 3rd Ed. */
/* Modified to complex Aug 26, 1999 */

#include <vsip.h>
#include <VU.h>
void VU_chouse_f(vsip_cvview_f*, vsip_cvview_f*,vsip_scalar_f*);
void VU_rscjvmprod_f(vsip_scalar_f, vsip_cvview_f*, vsip_cmview_f*, vsip_cvview_f*);
void VU_copu_f(vsip_cmview_f*, vsip_cvview_f*, vsip_cvview_f*);
void VU_chouseqr_f(
   vsip_cmview_f *A,
   vsip_scalar_f *beta)
{
   vsip_cvview_f *v, *w;
   vsip_cvview_f *a = vsip_cmcolview_f(A,0);
   vsip_cmattr_f attr_A,attr_A0;
   vsip_cvattr_f attr_a;
   vsip_length j,m,n;
   vsip_cvgetattrib_f(a,&attr_a);
   vsip_cmgetattrib_f(A,&attr_A);
   attr_A0 = attr_A;
   m = attr_A.col_length;
   n = attr_A.row_length;
   v = vsip_cvcreate_f(m,0);
   w = vsip_cvcreate_f(m,0);
   attr_a.stride = attr_A.col_stride;
   for(j=0; j<n; j++){
      attr_a.offset = j * attr_A0.row_stride + 
                       j * attr_A0.col_stride + attr_A0.offset;
      attr_a.length = attr_A0.col_length - j;
      vsip_cvputlength_f(v,attr_a.length);
      vsip_cvputattrib_f(a,&attr_a);
      VU_chouse_f(a,v,&beta[j]);
      attr_A.offset = attr_a.offset;
      attr_A.col_length = m - j;
      attr_A.row_length = n - j;
      vsip_cmputattrib_f(A,&attr_A);
      vsip_cvputlength_f(w,attr_A.row_length);
      VU_rscjvmprod_f(-beta[j],v,A,w);
      VU_copu_f(A,v,w);
      if(j < m - 1 ) {
          vsip_cvputlength_f(v,attr_a.length -1);
          vsip_cvputoffset_f(v,j+1);
          vsip_cvputlength_f(a,attr_a.length -1);
          vsip_cvputoffset_f(a,attr_a.offset + attr_a.stride);
          vsip_cvcopy_f_f(v,a);
      }
   }
   vsip_cmputattrib_f(A,&attr_A0);
   vsip_cvdestroy_f(a);
   vsip_cvalldestroy_f(v);
   vsip_cvalldestroy_f(w);
   return;
}

       
    
    
