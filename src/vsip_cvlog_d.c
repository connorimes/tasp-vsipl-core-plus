/* Created RJudd January 30, 2000 */
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
/* $Id: vsip_cvlog_d.c,v 2.0 2003/02/22 15:18:50 judd Exp $ */
#include<vsip.h>
#include<vsip_cvviewattributes_d.h>

void (vsip_cvlog_d)(
  const vsip_cvview_d *a,
  const vsip_cvview_d *r) {
  {
     /* register */ unsigned int n = (unsigned int) r->length;
     int cast = a->block->cstride;
     int crst = r->block->cstride;
     vsip_scalar_d *apr = (vsip_scalar_d*) ((a->block->R->array) + cast * a->offset),
                   *rpr = (vsip_scalar_d*) ((r->block->R->array) + crst * r->offset);
     vsip_scalar_d *api = (vsip_scalar_d*) ((a->block->I->array) + cast * a->offset),
                   *rpi = (vsip_scalar_d*) ((r->block->I->array) + crst * r->offset);
     /* register */ int ast = (int)(cast * a->stride),
                        rst = (int)(crst * r->stride);
     vsip_scalar_d mag  = 0,
                   s = 0,
                   ss=0;
     if(a == r){ /* in place */
        while(n-- > 0){
           s = ((*rpr > 0) ? *rpr: -*rpr) + ((*rpi >0) ? *rpi: -*rpi);
           ss = s * s;
           if(s == 0){ 
               mag = -VSIP_MAX_SCALAR_F; /* error */
           } else {
               mag = (vsip_scalar_d)log(s * sqrt((*rpr * *rpr)/ss + (*rpi * *rpi)/ss));
           }
           *rpi = (vsip_scalar_d)atan2(*rpi,*rpr); 
           *rpr = mag;
           rpr += rst; rpi += rst;
       }
     } else { /* out of place */
        while(n-- > 0){
           s = ((*apr > 0) ? *apr: -*apr) + ((*api >0) ? *api: -*api);
           ss = s * s;
           if(s == 0){ 
              *rpr = -VSIP_MAX_SCALAR_F; /* error */
            } else {
               *rpr = (vsip_scalar_d)log(s * sqrt((*apr * *apr)/ss + (*api * *api)/ss));
            }
            *rpi  = (vsip_scalar_d)atan2(*api,*apr);
            apr += ast; api += ast; 
            rpr += rst; rpi += rst;
        }
     }
  }
  return;
}
