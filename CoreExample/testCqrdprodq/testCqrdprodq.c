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
/* $Id: testCqrdprodq.c,v 2.0 2003/02/22 15:32:49 judd Exp $ */

#include<vsip.h>
#include<VU.h>

void VU_cmconjIP_f(vsip_cmview_f *A)
{
      vsip_length m = vsip_cmgetcollength_f(A);
      vsip_length n = vsip_cmgetrowlength_f(A);
      vsip_stride i,j;
      for(i=0; i<m; i++)
         for(j=0; j<n; j++)
            vsip_cmput_f(A,i,j,vsip_conj_f(vsip_cmget_f(A,i,j)));
}
void VU_cmfillz_f(vsip_cmview_f* Z)
{
     vsip_length m = vsip_cmgetcollength_f(Z);
     vsip_length n = vsip_cmgetrowlength_f(Z);
     vsip_stride i,j;
     for(i=0; i<m; i++)
        for(j=0; j<n; j++)
          vsip_cmput_f(Z,i,j,vsip_cmplx_f(0.0,0.0));
     return;
}
vsip_cmview_f* VU_cI_f(vsip_length M)
{
  vsip_cmview_f *I = vsip_cmcreate_f(M,M,VSIP_ROW,VSIP_MEM_NONE);
  if(I != NULL){
      vsip_cvview_f *row = vsip_cmrowview_f(I,0);
      if(row != NULL){
          vsip_cvputlength_f(row,(vsip_length)(M * M));
          vsip_cvfill_f(vsip_cmplx_f(0.0,0.0),row);
          vsip_cvputlength_f(row,M);
          vsip_cvputstride_f(row,(vsip_stride) (M + 1));
          vsip_cvfill_f(vsip_cmplx_f(1.0,0.0),row);
          vsip_cvdestroy_f(row);
      } else {
          vsip_cmdestroy_f(I);
          return (vsip_cmview_f*) NULL;
      }
   } else {
      return (vsip_cmview_f*) NULL;
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
   vsip_cmview_f *A  = vsip_cmcreate_f(M,N,VSIP_COL,VSIP_MEM_NONE),
                *A0 = vsip_cmcreate_f(M,N,VSIP_COL,VSIP_MEM_NONE);
   /* get data */
   FILE *fptr = fopen(argv[3],"r");
   VU_cmreadf_f(fptr,A);
   fclose(fptr);
   vsip_cmcopy_f_f(A,A0); /* will use A, original data in A0 */
   { /* test prodq for Q1 */
     /* create a QRD object */
     vsip_cqr_f *qrd   = vsip_cqrd_create_f(M,N,VSIP_QRD_SAVEQ);
     /* create a matrix to hold Q */
     vsip_cmview_f *I = VU_cI_f(M);
     vsip_cmview_f *Q = vsip_cmsubview_f(I,0,0,M,M);
     vsip_cmview_f *Qt = vsip_cmtransview_f(Q);
     /* create a matrix to hold R */
     vsip_cmview_f *A1 = vsip_cmcreate_f(M,N,VSIP_ROW,VSIP_MEM_NONE);
     vsip_cmview_f *R1 = vsip_cmsubview_f(A1,0,0,M,N);
     vsip_cmview_f *R  = vsip_cmcreate_f(M,N,VSIP_ROW,VSIP_MEM_NONE);
     /* create a matrix to hold Q Q^h */
     vsip_cmview_f *I1 = vsip_cmcreate_f(M,M,VSIP_ROW,VSIP_MEM_NONE);
     /* create a matrix to hold Q^h Q */
     vsip_cmview_f *I2 = vsip_cmcreate_f(M,M,VSIP_ROW,VSIP_MEM_NONE);
     /* do decomposition */
     vsip_cqrd_f(qrd,A);
     printf("A decomposed = "); VU_cmprintm_f("6.4",A);
     /* find Q */
     vsip_cqrdprodq_f(qrd,VSIP_MAT_NTRANS,VSIP_MAT_RSIDE,I);
     printf("A = "); VU_cmprintm_f("6.4",A0);
     printf("Q = "); VU_cmprintm_f("6.4",Q);
     /* find R */
     vsip_cmcopy_f_f(A0,A1);
     VU_cmconjIP_f(Qt);
     vsip_cmprod_f(Qt,A1,R);
     VU_cmconjIP_f(Qt);
     printf("From mprod R = "); VU_cmprintm_f("6.4",R);
     vsip_cqrdprodq_f(qrd,VSIP_MAT_HERM,VSIP_MAT_LSIDE,A1);
     printf("From qrdprod R = "); VU_cmprintm_f("6.4",R1);

     /* find A from Q and R */
     vsip_cmprod_f(Q,R,A1);
     printf("Q R = ");VU_cmprintm_f("6.4",A1);

     /* find Q^h Q using mprod */
     VU_cmfillz_f(I1); VU_cmfillz_f(I2);
     vsip_cmherm_f(Q,I1);
     vsip_cmprod_f(I1,Q,I2);
     printf("directly using mprod Q^h Q = "); VU_cmprintm_f("6.4",I2);

     /* find Q^h Q using matprod on Rside */
     VU_cmfillz_f(I1);
     vsip_cmherm_f(Q,I1);
     vsip_cqrdprodq_f(qrd,VSIP_MAT_NTRANS,VSIP_MAT_RSIDE,I1);
     printf("using qrdprodq Q^h Q Rside = "); VU_cmprintm_f("6.4",I1);

     /* find Q^h Q using matprod on Lside */
     VU_cmfillz_f(I2);
     vsip_cmcopy_f_f(Q,I2);
     vsip_cqrdprodq_f(qrd,VSIP_MAT_HERM,VSIP_MAT_LSIDE,I2);
     printf("using qrdprodq Q^h Q Lside = "); VU_cmprintm_f("6.4",I2);
    
     /* find Q Q^h using Mprod */
     VU_cmfillz_f(I1); VU_cmfillz_f(I2);
     vsip_cmherm_f(Q,I1);
     vsip_cmprod_f(Q,I1,I2);
     printf("directly using mprod Q Q^h = "); VU_cmprintm_f("6.4",I2);
      
     /* find Q Q^h using matprod on Rside */
     VU_cmfillz_f(I1);
     vsip_cmcopy_f_f(Q,I1);
     vsip_cqrdprodq_f(qrd,VSIP_MAT_HERM,VSIP_MAT_RSIDE,I1);
     printf("using qrdprodq Q Q^h Rside = "); VU_cmprintm_f("6.4",I1);

     /* find Q Q^h using matprod on Lside */
     VU_cmfillz_f(I2);
     vsip_cmherm_f(Q,I2);
     vsip_cqrdprodq_f(qrd,VSIP_MAT_NTRANS,VSIP_MAT_LSIDE,I2);
     printf("using qrdprodq Q Q^h Lside = "); VU_cmprintm_f("6.4",I2);
    }
  }
  }vsip_finalize((void*)0);return 0;
}

