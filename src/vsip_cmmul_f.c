/* Created RJudd September 24, 1999*/
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
/* $Id: vsip_cmmul_f.c,v 2.0 2003/02/22 15:18:43 judd Exp $ */

#include<vsip.h>
#include<vsip_mviewattributes_f.h>
#include<vsip_cmviewattributes_f.h>

void (vsip_cmmul_f)(
  const vsip_cmview_f *a,
  const vsip_cmview_f *b,
  const vsip_cmview_f *r) {

  { 
    vsip_length n_mj, /* major length */
                n_mn; /* minor length */
    vsip_stride ast_mj, ast_mn,
                bst_mj, bst_mn,
                rst_mj, rst_mn;
    vsip_scalar_f *ap_r = (a->block->R->array) + a->offset * a->block->cstride,
                  *bp_r = (b->block->R->array) + b->offset * b->block->cstride,
                  *rp_r = (r->block->R->array) + r->offset * r->block->cstride;
    vsip_scalar_f *ap_i = (a->block->I->array) + a->offset * a->block->cstride,
                  *bp_i = (b->block->I->array) + b->offset * b->block->cstride,
                  *rp_i = (r->block->I->array) + r->offset * r->block->cstride;
    vsip_scalar_f *ap0_r = ap_r,
                  *bp0_r = bp_r,
                  *rp0_r = rp_r;
    vsip_scalar_f *ap0_i = ap_i,
                  *bp0_i = bp_i,
                  *rp0_i = rp_i;
    vsip_scalar_f temp;
    /* pick direction dependent on output */
    if(r->row_stride < r->col_stride){
           n_mj = r->row_length; n_mn = r->col_length;
           rst_mj = r->row_stride; rst_mn = r->col_stride;
           ast_mj = a->row_stride; ast_mn = a->col_stride;
           bst_mj = b->row_stride; bst_mn = b->col_stride;
           rst_mj *= r->block->cstride; rst_mn *= r->block->cstride;
           ast_mj *= a->block->cstride; ast_mn *= a->block->cstride;
           bst_mj *= b->block->cstride; bst_mn *= b->block->cstride;
    } else {
           n_mn = r->row_length; n_mj = r->col_length;
           rst_mn = r->row_stride; rst_mj = r->col_stride;
           ast_mn = a->row_stride; ast_mj = a->col_stride;
           bst_mn = b->row_stride; bst_mj = b->col_stride;
           rst_mn *= r->block->cstride; rst_mj *= r->block->cstride;
           ast_mn *= a->block->cstride; ast_mj *= a->block->cstride;
           bst_mn *= b->block->cstride; bst_mj *= b->block->cstride;
    }
    /* end define */
    while(n_mn-- > 0){
       int n = n_mj;
       while(n-- >0){
          temp =  *ap_r * *bp_r - *bp_i * *ap_i;
          *rp_i = *ap_r * *bp_i + *ap_i * *bp_r;
          *rp_r = temp;
         ap_r += ast_mj; bp_r += bst_mj; rp_r += rst_mj;
         ap_i += ast_mj; bp_i += bst_mj; rp_i += rst_mj;
       }
       ap0_r += ast_mn; bp0_r += bst_mn; rp0_r += rst_mn;
       ap_r = ap0_r; bp_r = bp0_r; rp_r = rp0_r;
       ap0_i += ast_mn; bp0_i += bst_mn; rp0_i += rst_mn;
       ap_i = ap0_i; bp_i = bp0_i; rp_i = rp0_i;
    }
  }
  return;
}
