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

#include<stdio.h>
#include<vsip.h>
#include<VU.h>

int main(int argc, char *argv[]){vsip_init((void*)0);
{  if(argc < 3){
      printf("usage\nqrdex M N FileName\n");
   } else {
   /* get some data */
   vsip_length M    = (vsip_length)atoi(argv[1]),
               N    = (vsip_length)atoi(argv[2]);
   vsip_mview_d *A  = vsip_mcreate_d(M,N,VSIP_COL,0),
                *A0 = vsip_mcreate_d(M,N,VSIP_COL,0),
                *A1 = vsip_mcreate_d(M,N,VSIP_COL,0);
    vsip_qr_d *qrd  = vsip_qrd_create_d(M,N,VSIP_QRD_SAVEQ);
    vsip_mview_d *Q = vsip_mcreate_d(M,M,VSIP_ROW,0);
    { /* get data */
      FILE *fptr = fopen(argv[3],"r");
      VU_mreadf_d(fptr,A);
      fclose(fptr);
      vsip_mcopy_d_d(A,A0);
      printf("input matrix A \n");
      printf("A =");VU_mprintm_d("9.6",A);
    }
    vsip_qrd_d(qrd,A);
    printf("AD =\n"); VU_mprintm_d("9.6",A);
    { /* Multiply I * Q to get Q */
      vsip_vview_d *Q_rv = vsip_mrowview_d(Q,0);
      vsip_mview_d *Q1   = vsip_msubview_d(Q,0,0,M,N);
      vsip_mview_d *R0   = vsip_mcreate_d(M,N,VSIP_ROW,0);
      vsip_mview_d *R    = vsip_msubview_d(R0,0,0,N,N);
      vsip_vputlength_d(Q_rv,M * M);
      vsip_vfill_d(0.0,Q_rv);
      vsip_vputlength_d(Q_rv,M);
      vsip_vputstride_d(Q_rv,M+1);
      vsip_vfill_d(1.0,Q_rv);
      printf("Using an Identity matrix extract Q \n");
      printf("I = \n"); VU_mprintm_d("9.6",Q);
      vsip_qrdprodq_d(qrd,VSIP_MAT_NTRANS,VSIP_MAT_RSIDE,Q);
      printf("Q1 = \n"); VU_mprintm_d("9.6",Q1);
      printf("Using Q1 and A extract R\n");
      { vsip_mview_d *Q1T = vsip_mtransview_d(Q1);
        vsip_mprod_d(Q1T,A0,R);
        vsip_mdestroy_d(Q1T);
      }
      printf("R = \n"); VU_mprintm_d("9.6",R);
      printf("Q * R =\n");
      vsip_qrdprodq_d(qrd,VSIP_MAT_NTRANS,VSIP_MAT_LSIDE,R0);
      VU_mprintm_d("9.6",R0);
      vsip_qrdprodq_d(qrd,VSIP_MAT_TRANS,VSIP_MAT_LSIDE,A0);
      VU_mprintm_d("9.6",A0);
      vsip_mdestroy_d(R);
      vsip_vdestroy_d(Q_rv);
      vsip_mdestroy_d(Q1);
      vsip_malldestroy_d(R0);
     }
     vsip_qrd_destroy_d(qrd);
     vsip_malldestroy_d(A);
     vsip_malldestroy_d(A0);
     vsip_malldestroy_d(A1);
     vsip_malldestroy_d(Q);
  } 
  }vsip_finalize((void*)0);return 0;
}
