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

void VU_cmconjIP_f(vsip_cmview_f*);
void VU_chouse_f(vsip_cvview_f*,vsip_cvview_f*, vsip_scalar_f*);
void VU_chouseqr_f(vsip_cmview_f*,vsip_scalar_f*);
void VU_cqprodm_f(vsip_cmview_f*,vsip_cmview_f*,vsip_scalar_f*);
void VU_cmprodq_f(vsip_cmview_f*,vsip_cmview_f*,vsip_scalar_f*);
void VU_cqhprodm_f(vsip_cmview_f*,vsip_cmview_f*,vsip_scalar_f*);
void VU_cmprodqh_f(vsip_cmview_f*,vsip_cmview_f*,vsip_scalar_f*);
int VU_cqrd_f(vsip_cmview_f*,vsip_cmview_f*);
int main(int argc, char *argv[]){vsip_init((void*)0);
{  if(argc < 3){
      printf("usage\nqrdex M N FileName\n");
      exit(1);
   }
   { /* get some data */
     vsip_length M = (vsip_length)atoi(argv[1]),
                 N = (vsip_length)atoi(argv[2]);
     vsip_cmview_f *A = vsip_cmcreate_f(M,N,VSIP_COL,0),
                  *Q = vsip_cmcreate_f(M,N,VSIP_ROW,0);
     vsip_scalar_f *beta = (vsip_scalar_f*)malloc(N * sizeof(vsip_scalar_f));
     
     FILE *fptr = fopen(argv[3],"r");
     VU_cmreadf_f(fptr,A);
     fclose(fptr);
     vsip_cmcopy_f_f(A,Q);
     printf("input matrix A \n");
     printf("A =");VU_cmprintm_f("6.4",A);
     VU_chouseqr_f(Q,beta); /* make a QR matrix, keep the betas */
     printf("Decomposed A with R in upper, \n");
     printf("and householder vector in lower \n");
     printf("householder value on diagonal is 1\n");
     printf("v(2:m)\\R =");VU_cmprintm_f("6.4",Q); 
     { /* Multiply Q times R to see if we get A */
       vsip_length i,j;
       vsip_cmview_f *R = vsip_cmcreate_f(M,N,VSIP_ROW,0);
       vsip_cvview_f *r = vsip_cmrowview_f(R,0);
       vsip_cvputlength_f(r,N * M);
       vsip_cvfill_f(vsip_cmplx_f(0,0),r);
       for(i=0; i<N; i++) /* extract R */
          for(j = i; j<N; j++)
              vsip_cmput_f(R,i,j,vsip_cmget_f(Q,i,j));
       VU_cqprodm_f(R,Q,beta); /* Q * R */
       printf("Multiply Q times R and see if we get A\n");
       printf("QR = \n"); VU_cmprintm_f("6.4",R);
       vsip_cvdestroy_f(r);
       vsip_cmalldestroy_f(R);
     }
     { /* Multiply I * Q to get Q */
       vsip_cmview_f *I = vsip_cmcreate_f(M,M,VSIP_ROW,0);
       vsip_cvview_f *I_rv = vsip_cmrowview_f(I,0);
       vsip_cvputlength_f(I_rv,M * M);
       vsip_cvfill_f(vsip_cmplx_f(0.0,0.0),I_rv);
       vsip_cvputlength_f(I_rv,M);
       vsip_cvputstride_f(I_rv,M+1);
       vsip_cvfill_f(vsip_cmplx_f(1.0,0.0),I_rv);
       printf("Using an Identity matrix extract Q using Householdoer update\n");
       printf("I = \n"); VU_cmprintm_f("6.4",I);
       VU_cqprodm_f(I,Q,beta);
       printf("Q = \n"); VU_cmprintm_f("6.4",I);
       { /* Multiply Q hermitian * A to get R */
         vsip_cmview_f *AC = vsip_cmcreate_f(M,N,VSIP_COL,0);
         vsip_cmview_f *QT = vsip_cmtransview_f(I);
         vsip_cmview_f *R  = vsip_cmcreate_f(M,N,VSIP_ROW,0);
         vsip_cmprodj_f(QT,A,R);
         VU_cmconjIP_f(R);
         printf("Using Q from above mutiply Hermitian(Q) times A to get R\n");
         printf("QT * A = R = \n"); VU_cmprintm_f("6.4",R);
         vsip_cmcopy_f_f(A,AC);
         printf("Using Householder update multiply Transpose(Q) times A to get R\n");
         VU_cqhprodm_f(AC,Q,beta);
         printf("QT * AC = R = \n"); VU_cmprintm_f("6.4",AC);
         { vsip_cmview_f *QTQ = vsip_cmcreate_f(M,M,VSIP_ROW,0);
           vsip_cmprodj_f(QT,I,QTQ);
           printf("QT * Q = I = \n"); VU_cmprintm_f("6.4",QTQ);
           vsip_cmalldestroy_f(QTQ);
         }
         vsip_cmdestroy_f(QT);
         vsip_cmalldestroy_f(R); 
       } 
       {
          /* general Multiply  */
         vsip_cmview_f *J = vsip_cmcreate_f(M,2 * M,VSIP_ROW,0);
         vsip_cmview_f *K = vsip_cmcreate_f(M,2 * M,VSIP_ROW,0);
         vsip_cvview_f *J_rv = vsip_cmrowview_f(J,0);
         vsip_cvputlength_f(J_rv,2 * M * M);
         vsip_cvfill_f(vsip_cmplx_f(2.0,-1.0),J_rv);
         vsip_cvputlength_f(J_rv,M);
         vsip_cvputstride_f(J_rv,2 * M+1);
         vsip_cvfill_f(vsip_cmplx_f(1.0,1.0),J_rv);
         vsip_cvputoffset_f(J_rv,M);
         vsip_cvfill_f(vsip_cmplx_f(3.0,0.0),J_rv);
         printf("Make a big matrix J to test with \n");
         printf("J = \n"); VU_cmprintm_f("6.4",J);

         vsip_cmprod_f(I,J,K);
         VU_cqprodm_f(J,Q,beta);
         printf("Multiply Q * J using Householder update \n");
         printf("J = \n"); VU_cmprintm_f("6.4",J);
         printf("Multiply Q * J using Q extracted above \n");
         printf("K = \n"); VU_cmprintm_f("6.4",K);
         printf("\n");

         {  vsip_cmview_f *JT = vsip_cmtransview_f(J);
            vsip_cmview_f *KT = vsip_cmtransview_f(K);
            VU_cmconjIP_f(JT);
            printf("Conjugate Transpose the current J (overwritten by the above operation\n");
            printf("JT = \n"); VU_cmprintm_f("6.4",JT);
            vsip_cmprod_f(JT,I,KT);
            VU_cmprodq_f(JT,Q,beta);

            printf("Multiply hermitian(J) * Q using Householder update \n");
            printf("JT = \n"); VU_cmprintm_f("6.4",JT);
            printf("Multiply hermitian(J) * Q using Q extracted above \n");
            printf("KT = \n"); VU_cmprintm_f("6.4",KT);
            vsip_cmdestroy_f(JT);
            vsip_cmdestroy_f(KT);
         }
         {  vsip_cmview_f *QT = vsip_cmtransview_f(I);
            VU_cmconjIP_f(QT);
            vsip_cmprod_f(QT,J,K);
            VU_cqhprodm_f(J,Q,beta);
            printf("Transpose JT to J, multiply transpose(Q) * J using Householder\n");
            printf("J = \n"); VU_cmprintm_f("6.4",J);
            printf("Transpose JT to J, multiply transpose(Q) * J using Q extracted above\n");
            printf("K = \n"); VU_cmprintm_f("6.4",K);
            {
               vsip_cmview_f* JT = vsip_cmtransview_f(J);
               vsip_cmview_f* KT = vsip_cmtransview_f(K);
               VU_cmconjIP_f(JT);
               vsip_cmprod_f(JT,QT,KT);
               VU_cmconjIP_f(QT);
               printf("Transpose J, Multiply J * transpose(Q) using Q extracted above\n");
               printf("K = \n"); VU_cmprintm_f("6.4",KT);
               VU_cmprodqh_f(JT,Q,beta);
               VU_cmconjIP_f(JT);
               printf("Transpose J, Multiply J * transpose(Q) using Householder\n");
               printf("J = \n"); VU_cmprintm_f("6.4",JT);
               vsip_cmdestroy_f(JT);
               vsip_cmdestroy_f(KT);
            }
            vsip_cmdestroy_f(QT);
         }
         { vsip_cmview_f *I2 = vsip_cmcreate_f(M,M,VSIP_ROW,0);
           vsip_cmview_f *I2t = vsip_cmtransview_f(I2);
           vsip_cmcopy_f_f(I,I2);                  VU_cmprodqh_f(I2,Q,beta);
           printf("test mprodqh QQh =\n"); VU_cmprintm_f("6.4",I2);
           vsip_cmcopy_f_f(I,I2);VU_cmconjIP_f(I2);VU_cqprodm_f(I2t,Q,beta);
           printf("test qprodm QQh =\n"); VU_cmprintm_f("6.4",I2);
           vsip_cmcopy_f_f(I,I2);                  VU_cqhprodm_f(I2,Q,beta);
           printf("test qhprodm QhQ =\n"); VU_cmprintm_f("6.4",I2);
           vsip_cmcopy_f_f(I,I2);VU_cmconjIP_f(I2);VU_cmprodq_f(I2t,Q,beta);
           printf("test mprodq QhQ =\n"); VU_cmprintm_f("6.4",I2);
           vsip_cmdestroy_f(I2t);
           vsip_cmalldestroy_f(I2);
         }
           
       }
       vsip_cvdestroy_f(I_rv);
       vsip_cmalldestroy_f(I);
     }
     vsip_cmalldestroy_f(A);
     vsip_cmalldestroy_f(Q);
     free(beta);
     } vsip_finalize((void*)0); return 0;
   }
}
void VU_cmconjIP_f(vsip_cmview_f *R)
{
    vsip_cvview_f *R_row = vsip_cmrowview_f(R,0);
    vsip_length MR       = vsip_cmgetcollength_f(R);
    vsip_stride Rcs      = vsip_cmgetcolstride_f(R);
    vsip_offset offset   = vsip_cmgetoffset_f(R);
    while(MR-- > 1){
         vsip_cvconj_f(R_row,R_row);
         offset += Rcs;
         vsip_cvputoffset_f(R_row,offset);
   }vsip_cvconj_f(R_row,R_row);
   vsip_cvdestroy_f(R_row);
}         
