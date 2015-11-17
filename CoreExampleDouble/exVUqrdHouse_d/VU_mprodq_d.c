/* Created RJudd July 22, 1999 */
/* SPAWARSYCCEN D881 */
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
/* $Id: VU_mprodq_d.c,v 2.0 2003/02/22 15:46:48 judd Exp $ */

/* A * Q */

#include <vsip.h>
void VU_svmprod_d(vsip_scalar_d, vsip_vview_d*, vsip_mview_d*, vsip_vview_d*);
void VU_smvprod_d(vsip_scalar_d, vsip_mview_d*, vsip_vview_d*, vsip_vview_d*);
void VU_opu_d(vsip_mview_d*, vsip_vview_d*, vsip_vview_d*);         

void VU_mprodq_d(
     vsip_mview_d *C,
     vsip_mview_d *H,
     vsip_scalar_d *beta)
{
     vsip_mattr_d attr_C,attr_C0;
     vsip_mattr_d attr_H0;
     vsip_vattr_d attr_h,attr_v0;
     vsip_vview_d *h = vsip_mcolview_d(H,0);
     vsip_length m,n;
     vsip_length j;
     vsip_stride k;
     vsip_vview_d *v, *w;
     vsip_mgetattrib_d(C,&attr_C);
     vsip_vgetattrib_d(h,&attr_h);
     vsip_mgetattrib_d(H,&attr_H0);
     attr_C0 = attr_C;
     m = attr_C.col_length;
     n = attr_C.row_length;
     v = vsip_vcreate_d(n,0);
     vsip_vgetattrib_d(v,&attr_v0);
     w = vsip_vcreate_d(m,0);
     for(k= 0; k < attr_H0.row_length; k++){
         j = (vsip_length)k;
         attr_h.offset = j * attr_H0.row_stride +
                         j * attr_H0.col_stride + attr_H0.offset;
         attr_h.length = attr_H0.col_length - j;
         vsip_vputlength_d(v,attr_h.length);
         vsip_vputoffset_d(v,n - attr_h.length);
         vsip_vputattrib_d(h,&attr_h);
         vsip_vcopy_d_d(h,v);
         vsip_vput_d(v,0,1);
         vsip_vputattrib_d(v,&attr_v0);
         VU_smvprod_d(-beta[j],C,v,w);
         VU_opu_d(C,w,v);
         vsip_vput_d(v,k,0);
     }
     printf("here 1\n");
     vsip_mputattrib_d(C,&attr_C0);
     vsip_vdestroy_d(h);
     vsip_valldestroy_d(v);
     vsip_valldestroy_d(w);
     return;
}
