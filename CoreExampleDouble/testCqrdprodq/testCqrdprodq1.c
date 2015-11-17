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
/* $Id: testCqrdprodq1.c,v 2.0 2003/02/22 15:47:03 judd Exp $ */

#include<vsip.h>
#include<VU.h>

void VU_cmconjIP_d(vsip_cmview_d *A)
{
      vsip_length m = vsip_cmgetcollength_d(A);
      vsip_length n = vsip_cmgetrowlength_d(A);
      vsip_stride i,j;
      for(i=0; i<m; i++)
         for(j=0; j<n; j++)
            vsip_cmput_d(A,i,j,vsip_conj_d(vsip_cmget_d(A,i,j)));
}

void VU_cmfillz_d(vsip_cmview_d* Z)
{
     vsip_length m = vsip_cmgetcollength_d(Z);
     vsip_length n = vsip_cmgetrowlength_d(Z);
     vsip_stride i,j;
     for(i=0; i<m; i++)
        for(j=0; j<n; j++)
          vsip_cmput_d(Z,i,j,vsip_cmplx_d(0.0,0.0));
     return;
}
vsip_cmview_d* VU_cI_d(vsip_length M)
{
  vsip_cmview_d *I = vsip_cmcreate_d(M,M,VSIP_ROW,VSIP_MEM_NONE);
  if(I != NULL){
      vsip_cvview_d *row = vsip_cmrowview_d(I,0);
      if(row != NULL){
          vsip_cvputlength_d(row,(vsip_length)(M * M));
          vsip_cvfill_d(vsip_cmplx_d(0.0,0.0),row);
          vsip_cvputlength_d(row,M);
          vsip_cvputstride_d(row,(vsip_stride) (M + 1));
          vsip_cvfill_d(vsip_cmplx_d(1.0,0.0),row);
          vsip_cvdestroy_d(row);
      } else {
          vsip_cmdestroy_d(I);
          return (vsip_cmview_d*) NULL;
      }
   } else {
      return (vsip_cmview_d*) NULL;
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
   vsip_cmview_d *A  = vsip_cmcreate_d(M,N,VSIP_COL,VSIP_MEM_NONE),
                *A0 = vsip_cmcreate_d(M,N,VSIP_COL,VSIP_MEM_NONE);
   /* get data */
   FILE *fptr = fopen(argv[3],"r");
   VU_cmreadf_d(fptr,A);
   fclose(fptr);
   vsip_cmcopy_d_d(A,A0); /* will use A, original data in A0 */
   { /* test prodq for Q1 */
     /* create a QRD object */
     vsip_cqr_d *qrd   = vsip_cqrd_create_d(M,N,VSIP_QRD_SAVEQ1);
     /* create a matrix to hold Q */
     vsip_cmview_d *I = VU_cI_d(M);
     vsip_cmview_d *Q = vsip_cmsubview_d(I,0,0,M,N);
     vsip_cmview_d *Qt = vsip_cmtransview_d(Q);
     /* create a matrix to hold R */
     vsip_cmview_d *A1 = vsip_cmcreate_d(M,N,VSIP_ROW,VSIP_MEM_NONE);
     vsip_cmview_d *R1 = vsip_cmsubview_d(A1,0,0,N,N);
     vsip_cmview_d *R  = vsip_cmcreate_d(N,N,VSIP_ROW,VSIP_MEM_NONE);
     /* create a matrix to hold Q Q^h */
     vsip_cmview_d *I1 = vsip_cmcreate_d(M,M,VSIP_ROW,VSIP_MEM_NONE);
     vsip_cmview_d *I_1NN = vsip_cmsubview_d(I1,0,0,N,N);
     vsip_cmview_d *I_1MN = vsip_cmsubview_d(I1,0,0,M,N);
     vsip_cmview_d *I_1NM = vsip_cmsubview_d(I1,0,0,N,M);
     /* create a matrix to hold Q^h Q */
     vsip_cmview_d *I2 = vsip_cmcreate_d(M,M,VSIP_ROW,VSIP_MEM_NONE);
     vsip_cmview_d *I_2NN = vsip_cmsubview_d(I2,0,0,N,N);
     vsip_cmview_d *I_2MN = vsip_cmsubview_d(I2,0,0,M,N);
     vsip_cmview_d *I_2NM = vsip_cmsubview_d(I2,0,0,N,M);
     /* do decomposition */
     vsip_cqrd_d(qrd,A);
     /* find Q */
     vsip_cqrdprodq_d(qrd,VSIP_MAT_NTRANS,VSIP_MAT_RSIDE,I);
     printf("A = "); VU_cmprintm_d("6.4",A0);
     printf("Q = "); VU_cmprintm_d("6.4",Q);
     /* find R */
     vsip_cmcopy_d_d(A0,A1);
     VU_cmconjIP_d(Qt);
     vsip_cmprod_d(Qt,A1,R);
     VU_cmconjIP_d(Qt);
     printf("From mprod R = "); VU_cmprintm_d("6.4",R);
     vsip_cqrdprodq_d(qrd,VSIP_MAT_HERM,VSIP_MAT_LSIDE,A1);
     printf("From qrdprod R = "); VU_cmprintm_d("6.4",R1);

     /* find A from Q and R */
     vsip_cmprod_d(Q,R,A1);
     printf("Q R = ");VU_cmprintm_d("6.4",A1);

     /* find Q^h Q using mprod */
     VU_cmfillz_d(I1); VU_cmfillz_d(I2);
     vsip_cmherm_d(Q,I_1NM);
     vsip_cmprod_d(I_1NM,Q,I_2NN);
     printf("directly using mprod Q^h Q = "); VU_cmprintm_d("6.4",I_2NN);

     /* find Q^h Q using matprod on Rside */
     VU_cmfillz_d(I1);
     vsip_cmherm_d(Q,I_1NM);
     vsip_cqrdprodq_d(qrd,VSIP_MAT_NTRANS,VSIP_MAT_RSIDE,I_1NM);
     printf("using qrdprodq Q^h Q Rside = "); VU_cmprintm_d("6.4",I_1NN);

     /* find Q^h Q using matprod on Lside */
     VU_cmfillz_d(I2);
     vsip_cmcopy_d_d(Q,I_2MN);
     vsip_cqrdprodq_d(qrd,VSIP_MAT_HERM,VSIP_MAT_LSIDE,I2);
     printf("using qrdprodq Q^h Q Lside = "); VU_cmprintm_d("6.4",I_2NN);
    
     /* find Q Q^h using Mprod */
     VU_cmfillz_d(I1); VU_cmfillz_d(I2);
     vsip_cmherm_d(Q,I_1NM);
     vsip_cmprod_d(Q,I_1NM,I2);
     printf("directly using mprod Q Q^h = "); VU_cmprintm_d("6.4",I2);
      
     /* find Q Q^h using matprod on Rside */
     VU_cmfillz_d(I1);
     vsip_cmcopy_d_d(Q,I_1MN);
     vsip_cqrdprodq_d(qrd,VSIP_MAT_HERM,VSIP_MAT_RSIDE,I1);
     printf("using qrdprodq Q Q^h Rside = "); VU_cmprintm_d("6.4",I1);

     /* find Q Q^h using matprod on Lside */
     VU_cmfillz_d(I2);
     vsip_cmherm_d(Q,I_2NM);
     vsip_cqrdprodq_d(qrd,VSIP_MAT_NTRANS,VSIP_MAT_LSIDE,I2);
     printf("using qrdprodq Q Q^h Lside = "); VU_cmprintm_d("6.4",I2);
    }
  }
  }vsip_finalize((void*)0);return 0;
}

