/* Created RJudd September 13, 1997*/ 
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
/* $Id: VI_vramp_f.h,v 2.0 2003/02/22 15:18:34 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_f.h>

#ifndef VI_VRAMP_F_H
#define VI_VRAMP_F_H

static
void 
VI_vramp_f(
          vsip_scalar_f x,
          vsip_scalar_f y, 
          const vsip_vview_f* r) {
  { 
      vsip_length N = r->length,
                  i;
    
      /* register */ vsip_stride rst = r->stride * r->block->rstride;
      vsip_scalar_f *rp    = (r->block->array) + r->offset * r->block->rstride;
      *rp = x;
       for(i=1; i<N; i++){
           rp += rst;
          *rp = x + (vsip_scalar_f)i * y;
       }
   }
}
#endif
