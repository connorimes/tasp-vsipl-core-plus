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
/* $Id: qrdex.c,v 2.0 2003/02/22 15:36:54 judd Exp $ */

#include<stdio.h>
#include<vsip.h>
#include<VU.h>

int main(int argc, char *argv[]){vsip_init((void*)0);
{  if(argc < 3){
      printf("usage\nqrdex M N FileName\n");
      exit(1);
   }
   {
     int VU_cqrd_f(vsip_cmview_f*,vsip_cmview_f*);
     vsip_length M = (vsip_length)atoi(argv[1]),
                 N = (vsip_length)atoi(argv[2]);
     vsip_cmview_f *A = vsip_cmcreate_f(M,N,VSIP_COL,0),
                  *Q = vsip_cmcreate_f(M,N,VSIP_COL,0),
                  *R = vsip_cmcreate_f(N,N,VSIP_ROW,0);
     FILE *fptr = fopen(argv[3],"r");
     VU_cmreadf_f(fptr,A);
     fclose(fptr);
     vsip_cmcopy_f_f(A,Q);
     printf("A =");VU_cmprintm_f("9.6",A);
     VU_cqrd_f(Q,R);
     printf("Q =");VU_cmprintm_f("9.6",Q); 
     printf("R =");VU_cmprintm_f("9.6",R);
     vsip_cmprod_f(Q,R,A);
     printf("QR =");VU_cmprintm_f("9.6",A);
     vsip_cmalldestroy_f(A);
     vsip_cmalldestroy_f(Q);
     vsip_cmalldestroy_f(R);
     } vsip_finalize((void*)0); return 0;
   }
}
int VU_cqrd_f(
      vsip_cmview_f *A,
      vsip_cmview_f *R){
  vsip_length N = vsip_cmgetrowlength_f(A);
  vsip_cscalar_f r;
  vsip_stride cvst = vsip_cmgetrowstride_f(A);
  vsip_offset a0o = vsip_cmgetoffset_f(A);
  vsip_offset ao = a0o;
  vsip_length i,j;
  vsip_cvview_f *a = vsip_cmcolview_f(A,0);
  vsip_cvview_f *q = vsip_cmcolview_f(A,0);
  if((a == NULL) || (q == NULL)){  /* failure to create vector view */
      vsip_cvdestroy_f(a);  /* destroy in case one create worked */
      vsip_cvdestroy_f(q);
      return 1; /* zero implies success */
  }
  for(i=0; i<N; i++){
    vsip_cvputoffset_f(a,a0o);
    vsip_cvputoffset_f(q,a0o);
    vsip_cmput_f(R,i,i,(r = vsip_csqrt_f(vsip_cvjdot_f(q,q))));
    vsip_csvmul_f(vsip_crecip_f(r),q,q);
    a0o += cvst;
    for(j=i+1; j<N; j++){
       ao += cvst;
       vsip_cvputoffset_f(a,ao);
       vsip_cmput_f(R,i,j,(r = vsip_cvjdot_f(a,q)));
       vsip_cmput_f(R,j,i,vsip_cmplx_f(0,0)); /* make sure lower diagonal is initialized to zero */
       vsip_cvsma_f(q,vsip_cneg_f(r),a,a);
    }
    ao = a0o;
  }
  vsip_cvdestroy_f(a);  /* clean up any creates */
  vsip_cvdestroy_f(q);
  return 0; /* zero implies success */
}
