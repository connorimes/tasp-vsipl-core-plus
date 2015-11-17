/* Created RJudd January 4, 1998 */
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
/* $Id: vsip_cvscatter_f.c,v 2.0 2003/02/22 15:18:52 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */

#include<vsip.h>
#include<vsip_vviewattributes_vi.h>
#include<vsip_cvviewattributes_f.h>

void (vsip_cvscatter_f)(
  const vsip_cvview_f* a,
  const vsip_cvview_f* r,
  const vsip_vview_vi* x) {
  {
    /* register */ vsip_length n = x->length;
    vsip_stride cast = a->block->cstride,
                crst = r->block->cstride;
    vsip_scalar_f *apr = (vsip_scalar_f*) ((a->block->R->array) + cast * a->offset),
                  *rpr = (vsip_scalar_f*) ((r->block->R->array) + crst * r->offset);
    vsip_scalar_f *api = (vsip_scalar_f*) ((a->block->I->array) + cast * a->offset),
                  *rpi = (vsip_scalar_f*) ((r->block->I->array) + crst * r->offset);
    vsip_scalar_vi *xp = (x->block->array) + x->offset;
    /* register */ vsip_stride ast = (cast * a->stride),
                               rst = (crst * r->stride);
    int xinc = 0;
    while(n-- >0){
        xinc = *xp * rst;
       *(rpr + xinc) = *apr;
       *(rpi + xinc) = *api;
        apr += ast; api += ast;
        xp += x->stride;
    }
  }
}
