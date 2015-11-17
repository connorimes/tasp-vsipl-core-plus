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
/* $Id: VU_houseqr_f.c,v 2.0 2003/02/22 15:34:27 judd Exp $ */

/* In place decompose a matrix with R in the upper diagonal */
/* and v in the lower diagonal */
/* save normalizing beta values */
/* Algorithm 5.2.1 Golub & Van Loan 3rd Ed. */

#include <vsip.h>
#include <VU.h>
void VU_house_f(vsip_vview_f*, vsip_vview_f*,vsip_scalar_f*);
void VU_svmprod_f(vsip_scalar_f, vsip_vview_f*, vsip_mview_f*, vsip_vview_f*);
void VU_opu_f(vsip_mview_f*, vsip_vview_f*, vsip_vview_f*);
void VU_houseqr_f(
   vsip_mview_f *A,
   vsip_scalar_f *beta)
{
   vsip_vview_f *v, *w;
   vsip_vview_f *a = vsip_mcolview_f(A,0);
   vsip_mattr_f attr_A,attr_A0;
   vsip_vattr_f attr_a;
   vsip_length j,m,n;
   vsip_vgetattrib_f(a,&attr_a);
   vsip_mgetattrib_f(A,&attr_A);
   attr_A0 = attr_A;
   m = attr_A.col_length;
   n = attr_A.row_length;
   v = vsip_vcreate_f(m,0);
   w = vsip_vcreate_f(m,0);
   attr_a.stride = attr_A.col_stride;
   for(j=0; j<n; j++){
      attr_a.offset = j * attr_A0.row_stride + 
                       j * attr_A0.col_stride + attr_A0.offset;
      attr_a.length = attr_A0.col_length - j;
      vsip_vputlength_f(v,attr_a.length);
      vsip_vputattrib_f(a,&attr_a);
      VU_house_f(a,v,&beta[j]);
      attr_A.offset = attr_a.offset;
      attr_A.col_length = m - j;
      attr_A.row_length = n - j;
      vsip_mputattrib_f(A,&attr_A);
      vsip_vputlength_f(w,attr_A.row_length);
      VU_svmprod_f(-beta[j],v,A,w);
      VU_opu_f(A,v,w);
      if(j < m - 1 ) {
          vsip_vputlength_f(v,attr_a.length -1);
          vsip_vputoffset_f(v,j+1);
          vsip_vputlength_f(a,attr_a.length -1);
          vsip_vputoffset_f(a,attr_a.offset + attr_a.stride);
          vsip_vcopy_f_f(v,a);
      }
   }
   vsip_mputattrib_f(A,&attr_A0);
   vsip_vdestroy_f(a);
   vsip_valldestroy_f(v);
   vsip_valldestroy_f(w);
   return;
}

       
    
    
