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

void VU_house_f(vsip_vview_f*,vsip_vview_f*, vsip_scalar_f*);
void VU_houseqr_f(vsip_mview_f*,vsip_scalar_f*);
void VU_qprodm_f(vsip_mview_f*,vsip_mview_f*,vsip_scalar_f*);
void VU_mprodq_f(vsip_mview_f*,vsip_mview_f*,vsip_scalar_f*);
void VU_qtprodm_f(vsip_mview_f*,vsip_mview_f*,vsip_scalar_f*);
void VU_mprodqt_f(vsip_mview_f*,vsip_mview_f*,vsip_scalar_f*);

int main(int argc, char *argv[]){vsip_init((void*)0);
{  if(argc < 3){
      printf("usage\nqrdex M N FileName\n");
      exit(1);
   }
   { /* get some data */
     int VU_qrd_f(vsip_mview_f*,vsip_mview_f*);
     vsip_length M = (vsip_length)atoi(argv[1]),
                 N = (vsip_length)atoi(argv[2]);
     vsip_mview_f *A = vsip_mcreate_f(M,N,VSIP_COL,0),
                  *Q = vsip_mcreate_f(M,N,VSIP_ROW,0);
     vsip_scalar_f *beta = (vsip_scalar_f*)malloc(N * sizeof(vsip_scalar_f));
     
     FILE *fptr = fopen(argv[3],"r");
     VU_mreadf_f(fptr,A);
     fclose(fptr);
     vsip_mcopy_f_f(A,Q);
     printf("input matrix A \n");
     printf("A =");VU_mprintm_f("9.6",A);
     VU_houseqr_f(Q,beta); /* make a QR matrix, keep the betas */
     printf("Decomposed A with R in upper, \n");
     printf("and householder vector in lower \n");
     printf("householder value on diagonal is 1\n");
     printf("v(2:m)\\R =");VU_mprintm_f("9.6",Q); 
     { /* Multiply Q times R to see if we get A */
       vsip_length i,j;
       vsip_mview_f *R = vsip_mcreate_f(M,N,VSIP_ROW,0);
       vsip_vview_f *r = vsip_mrowview_f(R,0);
       vsip_vputlength_f(r,N * M);
       vsip_vfill_f(0,r);
       for(i=0; i<N; i++) /* extract R */
          for(j = i; j<N; j++)
              vsip_mput_f(R,i,j,vsip_mget_f(Q,i,j));
       VU_qprodm_f(R,Q,beta); /* Q * R */
       printf("Multiply Q times R and see if we get A\n");
       printf("QR = \n"); VU_mprintm_f("9.6",R);
       vsip_vdestroy_f(r);
       vsip_malldestroy_f(R);
     }
     { /* Multiply I * Q to get Q */
       vsip_mview_f *I = vsip_mcreate_f(M,M,VSIP_ROW,0);
       vsip_vview_f *I_rv = vsip_mrowview_f(I,0);
       vsip_vputlength_f(I_rv,M * M);
       vsip_vfill_f(0.0,I_rv);
       vsip_vputlength_f(I_rv,M);
       vsip_vputstride_f(I_rv,M+1);
       vsip_vfill_f(1.0,I_rv);
       printf("Using an Identity matrix extract Q using Householdoer update\n");
       printf("I = \n"); VU_mprintm_f("9.6",I);
       VU_qprodm_f(I,Q,beta);
       printf("Q = \n"); VU_mprintm_f("9.6",I);
       { /* Multiply Q transpose * A to get R */
         vsip_mview_f *AC = vsip_mcreate_f(M,N,VSIP_COL,0);
         vsip_mview_f *QT = vsip_mtransview_f(I);
         vsip_mview_f *R  = vsip_mcreate_f(M,N,VSIP_ROW,0);
         vsip_mprod_f(QT,A,R);
         printf("Using Q from above mutiply Transpose(Q) times A to get R\n");
         printf("QT * A = R = \n"); VU_mprintm_f("9.6",R);
         vsip_mcopy_f_f(A,AC);
         printf("Using Householder update multiply Transpose(Q) times A to get R\n");
         VU_qtprodm_f(AC,Q,beta);
         printf("QT * AC = R = \n"); VU_mprintm_f("9.6",AC);
         { vsip_mview_f *QTQ = vsip_mcreate_f(M,M,VSIP_ROW,0);
           vsip_mprod_f(QT,I,QTQ);
           printf("QT * Q = I = \n"); VU_mprintm_f("9.6",QTQ);
           vsip_malldestroy_f(QTQ);
         }
         vsip_mdestroy_f(QT);
         vsip_malldestroy_f(R); 
       } 
       {
          /* general Multiply  */
         vsip_mview_f *J = vsip_mcreate_f(M,2 * M,VSIP_ROW,0);
         vsip_mview_f *K = vsip_mcreate_f(M,2 * M,VSIP_ROW,0);
         vsip_vview_f *J_rv = vsip_mrowview_f(J,0);
         vsip_vputlength_f(J_rv,2 * M * M);
         vsip_vfill_f(2.0,J_rv);
         vsip_vputlength_f(J_rv,M);
         vsip_vputstride_f(J_rv,2 * M+1);
         vsip_vfill_f(1.0,J_rv);
         vsip_vputoffset_f(J_rv,M);
         vsip_vfill_f(3.0,J_rv);
         printf("Make a big matrix J to test with \n");
         printf("J = \n"); VU_mprintm_f("9.6",J);
         vsip_mprod_f(I,J,K); 
         VU_qprodm_f(J,Q,beta);
         printf("Multiply Q * J using Householder update \n");
         printf("J = \n"); VU_mprintm_f("9.6",J);
         printf("Multiply Q * J using Q extracted above \n");
         printf("K = \n"); VU_mprintm_f("9.6",K);
         {  vsip_mview_f *JT = vsip_mtransview_f(J);
            vsip_mview_f *KT = vsip_mtransview_f(K);
            printf("Transpose the current J (overwritten by the above operation\n");
            printf("JT = \n"); VU_mprintm_f("9.6",JT);
            vsip_mprod_f(JT,I,KT);
            VU_mprodq_f(JT,Q,beta);
            printf("Multiply transpose(J) * Q using Householder update \n");
            printf("JT = \n"); VU_mprintm_f("9.6",JT);
            printf("Multiply transpose(J) * Q using Q extracted above \n");
            printf("KT = \n"); VU_mprintm_f("9.6",KT);
            vsip_mdestroy_f(JT);            
            vsip_mdestroy_f(KT);            
         }
         {  vsip_mview_f *QT = vsip_mtransview_f(I);
            vsip_mprod_f(QT,J,K);
            VU_qtprodm_f(J,Q,beta);
            printf("Transpose JT to J, multiply transpose(Q) * J using Householder\n");
            printf("J = \n"); VU_mprintm_f("9.6",J);
            printf("Transpose JT to J, multiply transpose(Q) * J using Q extracted above\n");
            printf("K = \n"); VU_mprintm_f("9.6",K);
            {
               vsip_mview_f* JT = vsip_mtransview_f(J);
               vsip_mview_f* KT = vsip_mtransview_f(K);
               vsip_mprod_f(JT,QT,KT);
               printf("Transpose J, Multiply J * transpose(Q) using Q extracted above\n");
               printf("K = \n"); VU_mprintm_f("9.6",KT);
               VU_mprodqt_f(JT,Q,beta);
               printf("Transpose J, Multiply J * transpose(Q) using Householder\n");
               printf("J = \n"); VU_mprintm_f("9.6",JT);
               vsip_mdestroy_f(JT);
               vsip_mdestroy_f(KT);
            }
            vsip_mdestroy_f(QT);            
         }
         vsip_vdestroy_f(J_rv);
         vsip_malldestroy_f(J);
         vsip_malldestroy_f(K);
       }                              
       vsip_vdestroy_f(I_rv);
       vsip_malldestroy_f(I);
     }
     vsip_malldestroy_f(A);
     vsip_malldestroy_f(Q);
     free(beta);
     } vsip_finalize((void*)0); return 0;
   }
}
