/* Created RJudd March 5, 2002 */
/* SPAWARSYSCEN */
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
/* $Id: vsip_vfirst_f.c,v 2.1 2007/01/30 20:24:04 judd Exp $ */


#include<vsip.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_vviewattributes_bl.h>

vsip_index (vsip_vfirst_f)(
  vsip_index j,
  vsip_bool (*f)(vsip_scalar_f,vsip_scalar_f),
  const vsip_vview_f* a,
  const vsip_vview_f* b) {
    {
      /*define variables*/
      /* register */ unsigned int n = (unsigned int) a->length;
      /* register */ int ast = (int) a->stride * a->block->rstride,
                         bst = (int) b->stride * b->block->rstride;
      vsip_scalar_f  *ap = (a->block->array) + a->offset * a->block->rstride,
                     *bp = (b->block->array) + b->offset * b->block->rstride;
      
      /*end define*/
      
      if(j >= n) return j;
      n -= j;
      ap += j * ast;
      bp += j * bst;
      while(n-- > 0){
           if(f(*ap,*bp)) return (vsip_index)(a->length - n -1);
            ap += ast; bp += bst;
      }
      return (vsip_index)a->length;
    }
}
