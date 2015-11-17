/* Created RJudd January 5, 1998 */
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
/* $Id: vsip_cvswap_f.c,v 2.0 2003/02/22 15:18:52 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Removed Development Mode RJudd Sept 00 */

#include<vsip.h>
#include<vsip_cvviewattributes_f.h>

void (vsip_cvswap_f)(
const vsip_cvview_f* a,
const vsip_cvview_f* b) {		/* swap(a_j, b_j)	*/
    {
      /* register */ vsip_length n = a->length;
      vsip_stride cast = a->block->cstride,
                  cbst = b->block->cstride;
      vsip_scalar_f *apr = (vsip_scalar_f *)((a->block->R->array) + cast * a->offset),
                    *bpr = (vsip_scalar_f *)((b->block->R->array) + cbst * b->offset);
      vsip_scalar_f *api = (vsip_scalar_f *)((a->block->I->array) + cast * a->offset),
                    *bpi = (vsip_scalar_f *)((b->block->I->array) + cbst * b->offset);
      vsip_scalar_f  temp;
      /* register */ vsip_stride ast = (cast * a->stride),
                                 bst = (cbst * b->stride);
      while(n-- > 0){
          temp = *apr; *apr = *bpr; *bpr = temp;
          temp = *api; *api = *bpi; *bpi = temp;
          apr += ast; api += ast;
          bpr += bst; bpi += bst;
      }
    }
}
