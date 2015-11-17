/*
 *  vsip_vramp_vi.c
 *  Created by Randall Judd on 5/16/06.
 *  Copyright 2006 
 *  See Copyright statement in top level directory
 */
/* $Id: vsip_vramp_vi.c,v 2.3 2006/10/20 16:16:07 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_vi.h>

void (vsip_vramp_vi)(vsip_scalar_vi x,
                     vsip_scalar_vi y, 
                     const vsip_vview_vi* r) {
   vsip_stride rst = r->stride;
   vsip_scalar_vi *rp    = (r->block->array) + r->offset,
                  *rpmax = (r->block->array) + r->offset + (r->length * rst);
   *rp = x;
   if(r->length > 1){
      rp += rst;
      while (rp < rpmax) {
         *rp = *(rp - rst) + y;
         rp += rst;
      }
   }
}

