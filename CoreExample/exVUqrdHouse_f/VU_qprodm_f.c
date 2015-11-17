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
/* $Id: VU_qprodm_f.c,v 2.0 2003/02/22 15:34:27 judd Exp $ */

/* Q * A */

#include <vsip.h>
void VU_svmprod_f(vsip_scalar_f, vsip_vview_f*, vsip_mview_f*, vsip_vview_f*);
void VU_smvprod_f(vsip_scalar_f, vsip_mview_f*, vsip_vview_f*, vsip_vview_f*);
void VU_opu_f(vsip_mview_f*, vsip_vview_f*, vsip_vview_f*);         

void VU_qprodm_f(
     vsip_mview_f *C,
     vsip_mview_f *H,
     vsip_scalar_f *beta)
{
     vsip_mattr_f attr_C,attr_C0;
     vsip_mattr_f attr_H0;
     vsip_vattr_f attr_h,attr_v0;
     vsip_vview_f *h = vsip_mcolview_f(H,0);
     vsip_length m,n;
     vsip_length j;
     vsip_stride k;
     vsip_vview_f *v, *w;
     vsip_mgetattrib_f(C,&attr_C);
     vsip_vgetattrib_f(h,&attr_h);
     vsip_mgetattrib_f(H,&attr_H0);
     attr_C0 = attr_C;
     m = attr_C.col_length;
     n = attr_C.row_length;
     v = vsip_vcreate_f(m,0);
     vsip_vgetattrib_f(v,&attr_v0);
     w = vsip_vcreate_f(n,0);
     vsip_vfill_f(0,v);
     for(k= attr_H0.row_length - 1; k >= 0; k--){
         j = (vsip_length)k;
         attr_h.offset = j * attr_H0.row_stride +
                         j * attr_H0.col_stride + attr_H0.offset;
         attr_h.length = attr_H0.col_length -j;
         vsip_vputlength_f(v,attr_h.length);
         vsip_vputoffset_f(v,m - attr_h.length);
         vsip_vputattrib_f(h,&attr_h);
         vsip_vcopy_f_f(h,v);
         vsip_vput_f(v,0,1);
         vsip_vputattrib_f(v,&attr_v0);
         VU_svmprod_f(-beta[j],v,C,w);
         VU_opu_f(C,v,w);
     }
     vsip_mputattrib_f(C,&attr_C0);
     vsip_vdestroy_f(h);
     vsip_valldestroy_f(v);
     vsip_valldestroy_f(w);
     return;
}

    
