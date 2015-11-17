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
/* $Id: VU_houseqr_d.c,v 2.0 2003/02/22 15:46:48 judd Exp $ */

/* In place decompose a matrix with R in the upper diagonal */
/* and v in the lower diagonal */
/* save normalizing beta values */
/* Algorithm 5.2.1 Golub & Van Loan 3rd Ed. */

#include <vsip.h>
#include <VU.h>
void VU_house_d(vsip_vview_d*, vsip_vview_d*,vsip_scalar_d*);
void VU_svmprod_d(vsip_scalar_d, vsip_vview_d*, vsip_mview_d*, vsip_vview_d*);
void VU_opu_d(vsip_mview_d*, vsip_vview_d*, vsip_vview_d*);
void VU_houseqr_d(
   vsip_mview_d *A,
   vsip_scalar_d *beta)
{
   vsip_vview_d *v, *w;
   vsip_vview_d *a = vsip_mcolview_d(A,0);
   vsip_mattr_d attr_A,attr_A0;
   vsip_vattr_d attr_a;
   vsip_length j,m,n;
   vsip_vgetattrib_d(a,&attr_a);
   vsip_mgetattrib_d(A,&attr_A);
   attr_A0 = attr_A;
   m = attr_A.col_length;
   n = attr_A.row_length;
   v = vsip_vcreate_d(m,0);
   w = vsip_vcreate_d(m,0);
   attr_a.stride = attr_A.col_stride;
   for(j=0; j<n; j++){
      attr_a.offset = j * attr_A0.row_stride + 
                       j * attr_A0.col_stride + attr_A0.offset;
      attr_a.length = attr_A0.col_length - j;
      vsip_vputlength_d(v,attr_a.length);
      vsip_vputattrib_d(a,&attr_a);
      VU_house_d(a,v,&beta[j]);
      attr_A.offset = attr_a.offset;
      attr_A.col_length = m - j;
      attr_A.row_length = n - j;
      vsip_mputattrib_d(A,&attr_A);
      vsip_vputlength_d(w,attr_A.row_length);
      VU_svmprod_d(-beta[j],v,A,w);
      VU_opu_d(A,v,w);
      if(j < m - 1 ) {
          vsip_vputlength_d(v,attr_a.length -1);
          vsip_vputoffset_d(v,j+1);
          vsip_vputlength_d(a,attr_a.length -1);
          vsip_vputoffset_d(a,attr_a.offset + attr_a.stride);
          vsip_vcopy_d_d(v,a);
      }
   }
   vsip_mputattrib_d(A,&attr_A0);
   vsip_vdestroy_d(a);
   vsip_valldestroy_d(v);
   vsip_valldestroy_d(w);
   return;
}

       
    
    
