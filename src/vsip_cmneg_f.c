/* Created RJudd September 28, 1999*/
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
/* $Id: vsip_cmneg_f.c,v 2.0 2003/02/22 15:18:43 judd Exp $ */

#include<vsip.h>
#include<vsip_cmviewattributes_f.h>

void (vsip_cmneg_f)(
  const vsip_cmview_f *a,
  const vsip_cmview_f *r) {

  { 
    vsip_length n_mj, /* major length */
                n_mn; /* minor length */
    vsip_stride ast_mj, ast_mn,
                rst_mj, rst_mn;
    vsip_scalar_f *ap_r = (a->block->R->array) + a->offset * a->block->cstride,
                  *rp_r = (r->block->R->array) + r->offset * r->block->cstride;
    vsip_scalar_f *ap_i = (a->block->I->array) + a->offset * a->block->cstride,
                  *rp_i = (r->block->I->array) + r->offset * r->block->cstride;
    vsip_scalar_f *ap0_r = ap_r,
                  *rp0_r = rp_r;
    vsip_scalar_f *ap0_i = ap_i,
                  *rp0_i = rp_i;
    /* pick direction dependent on output */
    if(r->row_stride < r->col_stride){
           n_mj = r->row_length; n_mn = r->col_length;
           rst_mj = r->row_stride; rst_mn = r->col_stride;
           ast_mj = a->row_stride; ast_mn = a->col_stride;
           rst_mj *= r->block->cstride; rst_mn *= r->block->cstride;
           ast_mj *= a->block->cstride; ast_mn *= a->block->cstride;
    } else {
           n_mn = r->row_length; n_mj = r->col_length;
           rst_mn = r->row_stride; rst_mj = r->col_stride;
           ast_mn = a->row_stride; ast_mj = a->col_stride;
           rst_mn *= r->block->cstride; rst_mj *= r->block->cstride;
           ast_mn *= a->block->cstride; ast_mj *= a->block->cstride;
    }
    /*end define*/
    if(ap_i == rp_i){ /* inplace */
       while(n_mn-- > 0){
          int n = n_mj;
          while(n-- >0){
            *rp_r = - *rp_r;
            *rp_i = - *rp_i;
             rp_r += rst_mj;
             rp_i += rst_mj;
          }
          rp0_r += rst_mn;
          rp0_i += rst_mn;
          rp_r = rp0_r;
          rp_i = rp0_i;
       }
    } else {
       while(n_mn-- > 0){
          int n = n_mj;
          while(n-- >0){
            *rp_r = - *ap_r;
            *rp_i = - *ap_i;
            ap_r += ast_mj;  rp_r += rst_mj;
            ap_i += ast_mj;  rp_i += rst_mj;
          }
          ap0_r += ast_mn; rp0_r += rst_mn;
          ap0_i += ast_mn; rp0_i += rst_mn;
          ap_r = ap0_r; rp_r = rp0_r;
          ap_i = ap0_i; rp_i = rp0_i;
    }
   }
  }
  return;
}
