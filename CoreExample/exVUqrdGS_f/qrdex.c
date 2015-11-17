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
/* $Id: qrdex.c,v 2.0 2003/02/22 15:34:53 judd Exp $ */

#include<stdio.h>
#include<vsip.h>
#include<VU.h>

int main(int argc, char *argv[]){vsip_init((void*)0);
{  if(argc < 3){
      printf("usage\nqrdex M N FileName\n");
      exit(1);
   }
   {
     int VU_qrd_f(vsip_mview_f*,vsip_mview_f*);
     vsip_length M = (vsip_length)atoi(argv[1]),
                 N = (vsip_length)atoi(argv[2]);
     vsip_mview_f *A = vsip_mcreate_f(M,N,VSIP_COL,0),
                  *Q = vsip_mcreate_f(M,N,VSIP_COL,0),
                  *R = vsip_mcreate_f(N,N,VSIP_ROW,0);
     FILE *fptr = fopen(argv[3],"r");
     VU_mreadf_f(fptr,A);
     fclose(fptr);
     vsip_mcopy_f_f(A,Q);
     printf("A =");VU_mprintm_f("9.6",A);
     VU_qrd_f(Q,R);
     printf("Q =");VU_mprintm_f("9.6",Q); 
     printf("R =");VU_mprintm_f("9.6",R);
     vsip_mprod_f(Q,R,A);
     printf("QR =");VU_mprintm_f("9.6",A);
     vsip_malldestroy_f(A);
     vsip_malldestroy_f(Q);
     vsip_malldestroy_f(R);
     } vsip_finalize((void*)0); return 0;
   }
}
int VU_qrd_f(
      vsip_mview_f *A,
      vsip_mview_f *R){
  vsip_length N = vsip_mgetrowlength_f(A);
  vsip_scalar_f r;
  vsip_stride cvst = vsip_mgetrowstride_f(A);
  vsip_offset a0o = vsip_mgetoffset_f(A);
  vsip_offset ao = a0o;
  vsip_length i,j;
  vsip_vview_f *a = vsip_mcolview_f(A,0);
  vsip_vview_f *q = vsip_mcolview_f(A,0);
  if((a == NULL) || (q == NULL)){  /* failure to create vector view */
      vsip_vdestroy_f(a);  /* destroy in case one create worked */
      vsip_vdestroy_f(q);
      return 1; /* zero implies success */
  }
  for(i=0; i<N; i++){
    vsip_vputoffset_f(a,a0o);
    vsip_vputoffset_f(q,a0o);
    vsip_mput_f(R,i,i,(r = sqrt(vsip_vdot_f(q,q))));
    if(r == 0){ /* no devide by zero */
        vsip_vdestroy_f(a);  /* clean up any creates */
        vsip_vdestroy_f(q);
        return 2; /* zero implies success */
    }
    vsip_svmul_f((1./r),q,q);
    a0o += cvst;
    for(j=i+1; j<N; j++){
       ao += cvst;
       vsip_vputoffset_f(a,ao);
       vsip_mput_f(R,i,j,(r = vsip_vdot_f(q,a)));
       vsip_mput_f(R,j,i,0); /* make sure lower diagonal is initialized to zero */
       vsip_vsma_f(q,-r,a,a);
    }
    ao = a0o;
  }
  vsip_vdestroy_f(a);  /* clean up any creates */
  vsip_vdestroy_f(q);
  return 0; /* zero implies success */
}
