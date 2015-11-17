/* Created RJudd January 26, 2000*/
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
/* $Id: vsip_mminmgval_d.c,v 2.0 2003/02/22 15:18:58 judd Exp $ */

#include<vsip.h>
#include<vsip_mviewattributes_d.h>

vsip_scalar_d (vsip_mminmgval_d)(
  const vsip_mview_d *r,
  vsip_scalar_mi *index)
{ 
    vsip_length n_mj, /* major length */
                n_mn; /* minor length */
    vsip_stride rst_mj, rst_mn;
    vsip_scalar_d *rp = (r->block->array) + r->offset * r->block->rstride;
    vsip_scalar_d *rp0 = rp;
    vsip_scalar_d retval = (*rp < 0) ? (- *rp) : *rp;
    vsip_scalar_d temp = 0;
    vsip_index major_i = 0,
               minor_i = 0;
    vsip_length n0_mn,n0_mj;
    /* pick search direction */
    if(r->row_stride < r->col_stride){
           n_mj = r->row_length; n_mn = r->col_length;
           rst_mj = r->row_stride; rst_mn = r->col_stride;
           rst_mj *= r->block->rstride; rst_mn *= r->block->rstride;
    } else {
           n_mn = r->row_length; n_mj = r->col_length;
           rst_mn = r->row_stride; rst_mj = r->col_stride;
           rst_mn *= r->block->rstride; rst_mj *= r->block->rstride;
    }
    n0_mn = n_mn - 1;
    n0_mj = n_mj - 1;
    /*end define*/
    while(n_mn-- > 0){
          int n = n_mj;
          while(n-- >0){
            if(retval > (temp = (*rp < 0) ? (- *rp) : *rp)){
                   retval = temp;
                   major_i = n0_mj - n;
                   minor_i = n0_mn - n_mn;
            }
            rp += rst_mj;
          }
          rp0 += rst_mn;
          rp = rp0;
    }
    if(index != NULL){
       if(r->row_stride < r->col_stride){
           index->r = minor_i;
           index->c = major_i;
       } else {
           index->r = major_i;
           index->c = minor_i;
       }
    }
    return retval;
}
