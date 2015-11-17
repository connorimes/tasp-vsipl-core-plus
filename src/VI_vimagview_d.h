/* Created RJudd October 6, 2000 */
/* SPAWARSYSCEN D857             */
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
/* $Id: VI_vimagview_d.h,v 2.0 2003/02/22 15:18:34 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_cvviewattributes_f.h>

#ifndef VI_VIMAGVIEW_D_H
#define VI_VIMAGVIEW_D_H

static
vsip_vview_d* 
VI_vimagview_d(
  const vsip_cvview_d* v, 
  vsip_vview_d*  a){ 
    a->block = v->block->I; 
    a->offset = v->offset; 
    a->stride = v->stride; 
    a->length = v->length; 
    a->markings = VSIP_VALID_STRUCTURE_OBJECT; 
    return a;
} 
#endif
