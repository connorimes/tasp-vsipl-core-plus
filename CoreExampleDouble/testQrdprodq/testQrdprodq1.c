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
/* $Id: testQrdprodq1.c,v 2.0 2003/02/22 15:47:05 judd Exp $ */

#include<vsip.h>
#include<VU.h>

void VU_mfillz_d(vsip_mview_d* Z)
{
     vsip_length m = vsip_mgetcollength_d(Z);
     vsip_length n = vsip_mgetrowlength_d(Z);
     vsip_stride i,j;
     for(i=0; i<m; i++)
        for(j=0; j<n; j++)
          vsip_mput_d(Z,i,j,(vsip_scalar_d)0.0);
     return;
}
vsip_mview_d* VU_I_d(vsip_length M)
{
  vsip_mview_d *I = vsip_mcreate_d(M,M,VSIP_ROW,VSIP_MEM_NONE);
  if(I != NULL){
      vsip_vview_d *row = vsip_mrowview_d(I,0);
      if(row != NULL){
          vsip_vputlength_d(row,(vsip_length)(M * M));
          vsip_vfill_d((vsip_scalar_d)0.0,row);
          vsip_vputlength_d(row,M);
          vsip_vputstride_d(row,(vsip_stride) (M + 1));
          vsip_vfill_d((vsip_scalar_d)1.0,row);
          vsip_vdestroy_d(row);
      } else {
          vsip_mdestroy_d(I);
          return (vsip_mview_d*) NULL;
      }
   } else {
      return (vsip_mview_d*) NULL;
   }
   return I;
}

int main(int argc, char *argv[]){vsip_init((void*)0);
{  if(argc < 3){
      printf("usage\nqrdex M N FileName\n");
   } else {
   /* matrix size */
   vsip_length M    = (vsip_length)atoi(argv[1]),
               N    = (vsip_length)atoi(argv[2]);
   /* Create some space to hold the matrix */
   vsip_mview_d *A  = vsip_mcreate_d(M,N,VSIP_COL,VSIP_MEM_NONE),
                *A0 = vsip_mcreate_d(M,N,VSIP_COL,VSIP_MEM_NONE);
   /* get data */
   FILE *fptr = fopen(argv[3],"r");
   VU_mreadf_d(fptr,A);
   fclose(fptr);
   vsip_mcopy_d_d(A,A0); /* will use A, original data in A0 */
   { /* test prodq for Q1 */
     /* create a QRD object */
     vsip_qr_d *qrd   = vsip_qrd_create_d(M,N,VSIP_QRD_SAVEQ1);
     /* create a matrix to hold Q */
     vsip_mview_d *I = VU_I_d(M);
     vsip_mview_d *Q = vsip_msubview_d(I,0,0,M,N);
     vsip_mview_d *Qt = vsip_mtransview_d(Q);
     /* create a matrix to hold R */
     vsip_mview_d *A1 = vsip_mcreate_d(M,N,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_d *R1 = vsip_msubview_d(A1,0,0,N,N);
     vsip_mview_d *R  = vsip_mcreate_d(N,N,VSIP_ROW,VSIP_MEM_NONE);
     /* create a matrix to hold Q Q^t */
     vsip_mview_d *I1 = vsip_mcreate_d(M,M,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_d *I_1NN = vsip_msubview_d(I1,0,0,N,N);
     vsip_mview_d *I_1MN = vsip_msubview_d(I1,0,0,M,N);
     vsip_mview_d *I_1NM = vsip_msubview_d(I1,0,0,N,M);
     /* create a matrix to hold Q^t Q */
     vsip_mview_d *I2 = vsip_mcreate_d(M,M,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_d *I_2NN = vsip_msubview_d(I2,0,0,N,N);
     vsip_mview_d *I_2MN = vsip_msubview_d(I2,0,0,M,N);
     vsip_mview_d *I_2NM = vsip_msubview_d(I2,0,0,N,M);
     /* do decomposition */
     vsip_qrd_d(qrd,A);
     /* find Q */
     vsip_qrdprodq_d(qrd,VSIP_MAT_NTRANS,VSIP_MAT_RSIDE,I);
     printf("A = \n"); VU_mprintm_d("6.4",A0);
     printf("Q = \n"); VU_mprintm_d("6.4",Q);
     /* find R */
     vsip_mcopy_d_d(A0,A1);
     vsip_mprod_d(Qt,A1,R);
     printf("From mprod R = \n"); VU_mprintm_d("6.4",R);
     vsip_qrdprodq_d(qrd,VSIP_MAT_TRANS,VSIP_MAT_LSIDE,A1);
     printf("From qrdprod R = \n"); VU_mprintm_d("6.4",R1);

     /* find A from Q and R */
     vsip_mprod_d(Q,R,A1);
     printf("Q R = \n");VU_mprintm_d("6.4",A1);

     /* find Q^t Q using mprod */
     VU_mfillz_d(I1); VU_mfillz_d(I2);
     vsip_mcopy_d_d(Qt,I_1NM);
     vsip_mprod_d(I_1NM,Q,I_2NN);
     printf("directly using mprod Q^t Q = \n"); VU_mprintm_d("6.4",I_2NN);

     /* find Q^t Q using matprod on Rside */
     VU_mfillz_d(I1);
     vsip_mcopy_d_d(Qt,I_1NM);
     vsip_qrdprodq_d(qrd,VSIP_MAT_NTRANS,VSIP_MAT_RSIDE,I_1NM);
     printf("using qrdprodq Q^t Q Rside = \n"); VU_mprintm_d("6.4",I_1NN);

     /* find Q^t Q using matprod on Lside */
     VU_mfillz_d(I2);
     vsip_mcopy_d_d(Q,I_2MN);
     vsip_qrdprodq_d(qrd,VSIP_MAT_TRANS,VSIP_MAT_LSIDE,I2);
     printf("using qrdprodq Q^t Q Lside = \n"); VU_mprintm_d("6.4",I_2NN);
    
     /* find Q Q^t using Mprod */
     VU_mfillz_d(I1); VU_mfillz_d(I2);
     vsip_mcopy_d_d(Qt,I_1NM);
     vsip_mprod_d(Q,I_1NM,I2);
     printf("directly using mprod Q Q^t = \n"); VU_mprintm_d("6.4",I2);
      
     /* find Q Q^t using matprod on Rside */
     VU_mfillz_d(I1);
     vsip_mcopy_d_d(Q,I_1MN);
     vsip_qrdprodq_d(qrd,VSIP_MAT_TRANS,VSIP_MAT_RSIDE,I1);
     printf("using qrdprodq Q Q^t Rside = \n"); VU_mprintm_d("6.4",I1);

     /* find Q Q^t using matprod on Lside */
     VU_mfillz_d(I2);
     vsip_mcopy_d_d(Qt,I_2NM);
     vsip_qrdprodq_d(qrd,VSIP_MAT_NTRANS,VSIP_MAT_LSIDE,I2);
     printf("using qrdprodq Q Q^t Lside = \n"); VU_mprintm_d("6.4",I2);
    }
  }
  }vsip_finalize((void*)0);return 0;
}

