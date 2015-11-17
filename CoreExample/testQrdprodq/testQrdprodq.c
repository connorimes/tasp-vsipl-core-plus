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
/* $Id: testQrdprodq.c,v 2.0 2003/02/22 15:31:15 judd Exp $ */

#include<vsip.h>
#include<VU.h>

void VU_mfillz_f(vsip_mview_f* Z)
{
     vsip_length m = vsip_mgetcollength_f(Z);
     vsip_length n = vsip_mgetrowlength_f(Z);
     vsip_stride i,j;
     for(i=0; i<m; i++)
        for(j=0; j<n; j++)
          vsip_mput_f(Z,i,j,(vsip_scalar_f)0.0);
     return;
}
vsip_mview_f* VU_I_f(vsip_length M)
{
  vsip_mview_f *I = vsip_mcreate_f(M,M,VSIP_ROW,VSIP_MEM_NONE);
  if(I != NULL){
      vsip_vview_f *row = vsip_mrowview_f(I,0);
      if(row != NULL){
          vsip_vputlength_f(row,(vsip_length)(M * M));
          vsip_vfill_f((vsip_scalar_f)0.0,row);
          vsip_vputlength_f(row,M);
          vsip_vputstride_f(row,(vsip_stride) (M + 1));
          vsip_vfill_f((vsip_scalar_f)1.0,row);
          vsip_vdestroy_f(row);
      } else {
          vsip_mdestroy_f(I);
          return (vsip_mview_f*) NULL;
      }
   } else {
      return (vsip_mview_f*) NULL;
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
   vsip_mview_f *A  = vsip_mcreate_f(M,N,VSIP_COL,VSIP_MEM_NONE),
                *A0 = vsip_mcreate_f(M,N,VSIP_COL,VSIP_MEM_NONE);
   /* get data */
   FILE *fptr = fopen(argv[3],"r");
   VU_mreadf_f(fptr,A);
   fclose(fptr);
   vsip_mcopy_f_f(A,A0); /* will use A, original data in A0 */
   { /* test prodq for Q1 */
     /* create a QRD object */
     vsip_qr_f *qrd   = vsip_qrd_create_f(M,N,VSIP_QRD_SAVEQ);
     /* create a matrix to hold Q */
     vsip_mview_f *I = VU_I_f(M);
     vsip_mview_f *Q = vsip_msubview_f(I,0,0,M,M);
     vsip_mview_f *Qt = vsip_mtransview_f(Q);
     /* create a matrix to hold R */
     vsip_mview_f *A1 = vsip_mcreate_f(M,N,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_f *R1 = vsip_msubview_f(A1,0,0,M,N);
     vsip_mview_f *R  = vsip_mcreate_f(M,N,VSIP_ROW,VSIP_MEM_NONE);
     /* create a matrix to hold Q Q^t */
     vsip_mview_f *I1 = vsip_mcreate_f(M,M,VSIP_ROW,VSIP_MEM_NONE);
     /* create a matrix to hold Q^t Q */
     vsip_mview_f *I2 = vsip_mcreate_f(M,M,VSIP_ROW,VSIP_MEM_NONE);
     /* do decomposition */
     vsip_qrd_f(qrd,A);
     printf("A decomposed = "); VU_mprintm_f("6.4",A);
     /* find Q */
     vsip_qrdprodq_f(qrd,VSIP_MAT_NTRANS,VSIP_MAT_RSIDE,I);
     printf("A = \n"); VU_mprintm_f("6.4",A0);
     printf("Q = \n"); VU_mprintm_f("6.4",Q);
     /* find R */
     vsip_mcopy_f_f(A0,A1);
     vsip_mprod_f(Qt,A1,R);
     printf("From mprod R = \n"); VU_mprintm_f("6.4",R);
     vsip_qrdprodq_f(qrd,VSIP_MAT_TRANS,VSIP_MAT_LSIDE,A1);
     printf("From qrdprod R = \n"); VU_mprintm_f("6.4",R1);

     /* find A from Q and R */
     vsip_mprod_f(Q,R,A1);
     printf("Q R = \n");VU_mprintm_f("6.4",A1);

     /* find Q^t Q using mprod */
     VU_mfillz_f(I1); VU_mfillz_f(I2);
     vsip_mcopy_f_f(Qt,I1);
     vsip_mprod_f(I1,Q,I2);
     printf("directly using mprod Q^t Q = \n"); VU_mprintm_f("6.4",I2);

     /* find Q^t Q using matprod on Rside */
     VU_mfillz_f(I1);
     vsip_mcopy_f_f(Qt,I1);
     vsip_qrdprodq_f(qrd,VSIP_MAT_NTRANS,VSIP_MAT_RSIDE,I1);
     printf("using qrdprodq Q^t Q Rside = \n"); VU_mprintm_f("6.4",I1);

     /* find Q^t Q using matprod on Lside */
     VU_mfillz_f(I2);
     vsip_mcopy_f_f(Q,I2);
     vsip_qrdprodq_f(qrd,VSIP_MAT_TRANS,VSIP_MAT_LSIDE,I2);
     printf("using qrdprodq Q^t Q Lside = \n"); VU_mprintm_f("6.4",I2);
    
     /* find Q Q^t using Mprod */
     VU_mfillz_f(I1); VU_mfillz_f(I2);
     vsip_mcopy_f_f(Qt,I1);
     vsip_mprod_f(Q,I1,I2);
     printf("directly using mprod Q Q^t = \n"); VU_mprintm_f("6.4",I2);
      
     /* find Q Q^t using matprod on Rside */
     VU_mfillz_f(I1);
     vsip_mcopy_f_f(Q,I1);
     vsip_qrdprodq_f(qrd,VSIP_MAT_TRANS,VSIP_MAT_RSIDE,I1);
     printf("using qrdprodq Q Q^t Rside = \n"); VU_mprintm_f("6.4",I1);

     /* find Q Q^t using matprod on Lside */
     VU_mfillz_f(I2);
     vsip_mcopy_f_f(Qt,I2);
     vsip_qrdprodq_f(qrd,VSIP_MAT_NTRANS,VSIP_MAT_LSIDE,I2);
     printf("using qrdprodq Q Q^t Lside = \n"); VU_mprintm_f("6.4",I2);
    }
  }
  }vsip_finalize((void*)0);return 0;
}

