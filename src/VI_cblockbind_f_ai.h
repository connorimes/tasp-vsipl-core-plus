/* Created RJudd May 27, 2002       */
/* SPAWARSYSCEN D857                */
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
/* $Id: VI_cblockbind_f_ai.h,v 2.0 2003/02/22 15:18:28 judd Exp $ */
/* VI_cblockbind_f always interleaved */

if(b != (vsip_cblock_f*)NULL){   
   b->data = (vsip_scalar_f*)malloc(2 * N * sizeof(vsip_scalar_f));   
   b->R = vsip_blockbind_f((vsip_scalar_f*)NULL,N,h);   
   b->I = vsip_blockbind_f((vsip_scalar_f*)NULL,N,h);   
   if(       (b->data == NULL) ||   
             (b->R == (vsip_block_f*)NULL) ||   
             (b->I == (vsip_block_f*)NULL) ) { /* malloc problems, cleanup & exit */   
      if(b->data != NULL) free(b->data);   
      if(b->R != NULL) free(b->R);   
      if(b->I != NULL) free(b->I);   
      free(b); b = (vsip_cblock_f*)NULL;   
   } else {   
      b->size     = N;
      b->kind     = VSIP_USER_BLOCK;   
      b->admit    = VSIP_RELEASED_BLOCK;   
      b->markings = VSIP_VALID_STRUCTURE_OBJECT;   
      b->bindings = 0;   
      b->Rp = Rp;   
      b->Ip = Ip;   
      b->cstride = 2;   
      /* set up derived blocks */   
      b->R->kind = VSIP_DERIVED_BLOCK;   
      b->I->kind = VSIP_DERIVED_BLOCK;   
      b->R->rstride = b->cstride;   
      b->I->rstride = b->cstride;   
      b->R->parent = b;   
      b->I->parent = b;   
   }   
}   

