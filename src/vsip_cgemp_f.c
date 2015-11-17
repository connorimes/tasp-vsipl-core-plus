/* Created RJudd January 27, 1999 */
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
/* $Id: vsip_cgemp_f.c,v 2.1 2003/03/08 14:43:33 judd Exp $ */
/* vsip_gemp_f */
#include<vsip_cmviewattributes_f.h>
#include<vsip_cvviewattributes_f.h>
#include<vsip.h>
#include"VI_cmcolview_f.h"
#include"VI_cmrowview_f.h"

static
vsip_cscalar_f 
VI_cvjjdot_f(const vsip_cvview_f *a,const vsip_cvview_f *b)
{
    /* register */ vsip_length n = a->length;
    vsip_stride cast = a->block->cstride;
    vsip_stride cbst = b->block->cstride;
    vsip_scalar_f *apr = (vsip_scalar_f*) ((a->block->R->array) + cast * a->offset),
                  *bpr = (vsip_scalar_f*) ((b->block->R->array) + cbst * b->offset);
    vsip_scalar_f *api = (vsip_scalar_f*) ((a->block->I->array) + cast * a->offset),
                  *bpi = (vsip_scalar_f*) ((b->block->I->array) + cbst * b->offset);
    /* register */ vsip_stride ast = (cast * a->stride),
                               bst = (cbst * b->stride);
  vsip_cscalar_f r;
  r.r = 0; r.i = 0;
  while(n-- > 0){
      r.r += (*apr * *bpr - *api * *bpi);
      r.i -= (*api * *bpr + *apr * *bpi);
      apr += ast; api += ast;
      bpr += bst; bpi += bst;
  }
  return r;
}

void (vsip_cgemp_f)(vsip_cscalar_f alpha,
                   const vsip_cmview_f *AA,
                   vsip_mat_op OpA,
                   const vsip_cmview_f *BB,
                   vsip_mat_op OpB,
                   vsip_cscalar_f beta,
                   const vsip_cmview_f *C){
  vsip_cmview_f At = *AA,
                Bt = *BB;
  vsip_cmview_f *A = &At,
                *B = &Bt;
  vsip_cscalar_f (*dot)(const vsip_cvview_f*,const vsip_cvview_f*) = vsip_cvdot_f;
  if((OpA == 1) || (OpA == 2)){
       A->row_length = AA->col_length;
       A->col_length = AA->row_length;
       A->row_stride = AA->col_stride;
       A->col_stride = AA->row_stride;
  }
  if((OpB == 1) || (OpB == 2)){
       B->row_length = BB->col_length;
       B->col_length = BB->row_length;
       B->row_stride = BB->col_stride;
       B->col_stride = BB->row_stride;
  }
  {
      vsip_length M = A->col_length,
                  N = B->row_length;
      vsip_length i,j;
      vsip_cvview_f aa,bb,cc,*a,*b,*c,*af,*bs;
      vsip_offset Boffset = B->offset;
      vsip_stride Brow_stride = B->row_stride,
                  Acol_stride = A->col_stride;
                  a = VI_cmrowview_f(A,0,&aa);
                  b = VI_cmcolview_f(B,0,&bb);
                  af = a; bs = b;
      if( ((OpA == 2) || (OpA == 3)) && ((OpB !=2) || (OpB !=3))){
                  dot = vsip_cvjdot_f;
                  af = b;
                  bs = a;
      }
      if( ((OpA != 2) || (OpA != 3)) && ((OpB ==2) || (OpB ==3))){
                 dot = vsip_cvjdot_f;
      } 
      if( ((OpA == 2) || (OpA == 3)) && ((OpB ==2) || (OpB ==3))){
                  dot = VI_cvjjdot_f;
      }
      c = VI_cmrowview_f(C,0,&cc);
      {
        vsip_cscalar_f temp;
        vsip_scalar_f  temp_r;
        vsip_stride str  = c->stride * c->block->cstride;
        vsip_stride str1 = C->col_stride * C->block->cstride;
        vsip_scalar_f  *c_pr_r =(vsip_scalar_f*) (c->block->R->array + c->offset * c->block->cstride),
                       *c_pr1_r = c_pr_r;
        vsip_scalar_f  *c_pr_i =(vsip_scalar_f*) (c->block->I->array + c->offset * c->block->cstride),
                       *c_pr1_i = c_pr_i;
        for(i = 0; i < M; i++){
          c_pr_r = c_pr1_r;
          c_pr_i = c_pr1_i;
          b->offset = Boffset;
          for(j =0; j < N; j++){
               temp_r = beta.r * *c_pr_r - beta.i * *c_pr_i;
              *c_pr_i = beta.i * *c_pr_r + beta.r * *c_pr_i;
              *c_pr_r = temp_r;
               temp = dot(af,bs);
              *c_pr_r += (alpha.r * temp.r - alpha.i * temp.i);
              *c_pr_i += (alpha.i * temp.r + alpha.r * temp.i);
               c_pr_r += str;
               c_pr_i += str;
               b->offset += Brow_stride;
          }  
          a->offset += Acol_stride;
          c_pr1_r += str1;
          c_pr1_i += str1;
        }
      }
   }  
}
