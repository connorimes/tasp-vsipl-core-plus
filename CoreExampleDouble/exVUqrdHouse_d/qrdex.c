#include<stdio.h>
#include<vsip.h>
#include<VU.h>

void VU_house_d(vsip_vview_d*,vsip_vview_d*, vsip_scalar_d*);
void VU_houseqr_d(vsip_mview_d*,vsip_scalar_d*);
void VU_qprodm_d(vsip_mview_d*,vsip_mview_d*,vsip_scalar_d*);
void VU_mprodq_d(vsip_mview_d*,vsip_mview_d*,vsip_scalar_d*);
void VU_qtprodm_d(vsip_mview_d*,vsip_mview_d*,vsip_scalar_d*);
void VU_mprodqt_d(vsip_mview_d*,vsip_mview_d*,vsip_scalar_d*);
int main(int argc, char *argv[]){vsip_init((void*)0);
{  if(argc < 3){
      printf("usage\nqrdex M N FileName\n");
      exit(1);
   }
   { /* get some data */
     int VU_qrd_d(vsip_mview_d*,vsip_mview_d*);
     vsip_length M = (vsip_length)atoi(argv[1]),
                 N = (vsip_length)atoi(argv[2]);
     vsip_mview_d *A = vsip_mcreate_d(M,N,VSIP_COL,0),
                  *Q = vsip_mcreate_d(M,N,VSIP_ROW,0);
     vsip_scalar_d *beta = (vsip_scalar_d*)malloc(N * sizeof(vsip_scalar_d));
     
     FILE *fptr = fopen(argv[3],"r");
     VU_mreadf_d(fptr,A);
     fclose(fptr);
     vsip_mcopy_d_d(A,Q);
     printf("input matrix A \n");
     printf("A =");VU_mprintm_d("9.6",A);
     VU_houseqr_d(Q,beta); /* make a QR matrix, keep the betas */
     printf("Decomposed A with R in upper, \n");
     printf("and householder vector in lower \n");
     printf("householder value on diagonal is 1\n");
     printf("v(2:m)\\R =");VU_mprintm_d("9.6",Q); 
     { /* Multiply Q times R to see if we get A */
       vsip_length i,j;
       vsip_mview_d *R = vsip_mcreate_d(M,N,VSIP_ROW,0);
       vsip_vview_d *r = vsip_mrowview_d(R,0);
       vsip_vputlength_d(r,N * M);
       vsip_vfill_d(0,r);
       for(i=0; i<N; i++) /* extract R */
          for(j = i; j<N; j++)
              vsip_mput_d(R,i,j,vsip_mget_d(Q,i,j));
       VU_qprodm_d(R,Q,beta); /* Q * R */
       printf("Multiply Q times R and see if we get A\n");
       printf("QR = \n"); VU_mprintm_d("9.6",R);
       vsip_vdestroy_d(r);
       vsip_malldestroy_d(R);
     }
     { /* Multiply I * Q to get Q */
       vsip_mview_d *I = vsip_mcreate_d(M,M,VSIP_ROW,0);
       vsip_vview_d *I_rv = vsip_mrowview_d(I,0);
       vsip_vputlength_d(I_rv,M * M);
       vsip_vfill_d(0.0,I_rv);
       vsip_vputlength_d(I_rv,M);
       vsip_vputstride_d(I_rv,M+1);
       vsip_vfill_d(1.0,I_rv);
       printf("Using an Identity matrix extract Q using Householdoer update\n");
       printf("I = \n"); VU_mprintm_d("9.6",I);
       VU_qprodm_d(I,Q,beta);
       printf("Q = \n"); VU_mprintm_d("9.6",I);
       { /* Multiply Q transpose * A to get R */
         vsip_mview_d *AC = vsip_mcreate_d(M,N,VSIP_COL,0);
         vsip_mview_d *QT = vsip_mtransview_d(I);
         vsip_mview_d *R  = vsip_mcreate_d(M,N,VSIP_ROW,0);
         vsip_mprod_d(QT,A,R);
         printf("Using Q from above mutiply Transpose(Q) times A to get R\n");
         printf("QT * A = R = \n"); VU_mprintm_d("9.6",R);
         vsip_mcopy_d_d(A,AC);
         printf("Using Householder update multiply Transpose(Q) times A to get R\n");
         VU_qtprodm_d(AC,Q,beta);
         printf("QT * AC = R = \n"); VU_mprintm_d("9.6",AC);
         vsip_mdestroy_d(QT);
         vsip_malldestroy_d(R); 
       } 
       {
          /* general Multiply  */
         vsip_mview_d *J = vsip_mcreate_d(M,2 * M,VSIP_ROW,0);
         vsip_mview_d *K = vsip_mcreate_d(M,2 * M,VSIP_ROW,0);
         vsip_vview_d *J_rv = vsip_mrowview_d(J,0);
         vsip_vputlength_d(J_rv,2 * M * M);
         vsip_vfill_d(2.0,J_rv);
         vsip_vputlength_d(J_rv,M);
         vsip_vputstride_d(J_rv,2 * M+1);
         vsip_vfill_d(1.0,J_rv);
         vsip_vputoffset_d(J_rv,M);
         vsip_vfill_d(3.0,J_rv);
         printf("Make a big matrix J to test with \n");
         printf("J = \n"); VU_mprintm_d("9.6",J);
         vsip_mprod_d(I,J,K); 
         VU_qprodm_d(J,Q,beta);
         printf("Multiply Q * J using Householder update \n");
         printf("J = \n"); VU_mprintm_d("9.6",J);
         printf("Multiply Q * J using Q extracted above \n");
         printf("K = \n"); VU_mprintm_d("9.6",K);
         {  vsip_mview_d *JT = vsip_mtransview_d(J);
            vsip_mview_d *KT = vsip_mtransview_d(K);
            printf("Transpose the current J (overwritten by the above operation\n");
            printf("JT = \n"); VU_mprintm_d("9.6",JT);
            vsip_mprod_d(JT,I,KT);
            VU_mprodq_d(JT,Q,beta);
            printf("Multiply transpose(J) * Q using Householder update \n");
            printf("JT = \n"); VU_mprintm_d("9.6",JT);
            printf("Multiply transpose(J) * Q using Q extracted above \n");
            printf("KT = \n"); VU_mprintm_d("9.6",KT);
            vsip_mdestroy_d(JT);            
            vsip_mdestroy_d(KT);            
         }
         {  vsip_mview_d *QT = vsip_mtransview_d(I);
            vsip_mprod_d(QT,J,K);
            VU_qtprodm_d(J,Q,beta);
            printf("Transpose JT to J, multiply transpose(Q) * J using Householder\n");
            printf("J = \n"); VU_mprintm_d("9.6",J);
            printf("Transpose JT to J, multiply transpose(Q) * J using Q extracted above\n");
            printf("K = \n"); VU_mprintm_d("9.6",K);
            {
               vsip_mview_d* JT = vsip_mtransview_d(J);
               vsip_mview_d* KT = vsip_mtransview_d(K);
               vsip_mprod_d(JT,QT,KT);
               printf("Transpose J, Multiply J * transpose(Q) using Q extracted above\n");
               printf("K = \n"); VU_mprintm_d("9.6",KT);
               VU_mprodqt_d(JT,Q,beta);
               printf("Transpose J, Multiply J * transpose(Q) using Householder\n");
               printf("J = \n"); VU_mprintm_d("9.6",JT);
               vsip_mdestroy_d(JT);
               vsip_mdestroy_d(KT);
            }
            vsip_mdestroy_d(QT);            
         }
         vsip_vdestroy_d(J_rv);
         vsip_malldestroy_d(J);
         vsip_malldestroy_d(K);
       }                              
       vsip_vdestroy_d(I_rv);
       vsip_malldestroy_d(I);
     }
     vsip_malldestroy_d(A);
     vsip_malldestroy_d(Q);
     free(beta);
     }vsip_finalize((void*)0);return 0;
   }
}
