/* Created RJudd February 28, 2000*/
/* SPAWARSYSCEN D857 */
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
/* $Id: vsip_mcopy_d_d.c,v 2.0 2003/02/22 15:18:55 judd Exp $ */

#include<vsip.h>
#include<vsip_mviewattributes_d.h>

void (vsip_mcopy_d_d)(
  const vsip_mview_d *a,
  const vsip_mview_d *r) {

  { 
    vsip_length n_mj, /* major length */
                n_mn; /* minor length */
    vsip_stride ast_mj, ast_mn,
                rst_mj, rst_mn;
    vsip_scalar_d *rp = (r->block->array) + r->offset * r->block->rstride;
    vsip_scalar_d *ap = (a->block->array) + a->offset * a->block->rstride;
    vsip_scalar_d *rp0 = rp;
    vsip_scalar_d  *ap0 = ap;
    /* pick direction dependent on output */
    if(r->row_stride < r->col_stride){
           n_mj   = r->row_length; n_mn = r->col_length;
           rst_mj = r->row_stride; rst_mn = r->col_stride;
           ast_mj = a->row_stride; ast_mn = a->col_stride;
           rst_mj *= r->block->rstride; rst_mn *= r->block->rstride;
           ast_mj *= a->block->rstride; ast_mn *= a->block->rstride;
    } else {
           n_mn = r->row_length; n_mj = r->col_length;
           rst_mn = r->row_stride; rst_mj = r->col_stride;
           ast_mn = a->row_stride; ast_mj = a->col_stride;
           rst_mn *= r->block->rstride; rst_mj *= r->block->rstride;
           ast_mn *= a->block->rstride; ast_mj *= a->block->rstride;
    }
    /*end define*/
    while(n_mn-- > 0){
       int n = n_mj;
       while(n-- >0){
         *rp = (vsip_scalar_d)(*ap);
         ap += ast_mj;  rp += rst_mj;
       }
       ap0 += ast_mn; rp0 += rst_mn;
       ap = ap0; rp = rp0;
    }
  }
  return;
}
