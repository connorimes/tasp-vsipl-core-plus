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
      exit(1);
   }
   {
     vsip_length M = (vsip_length)atoi(argv[1]),
                 N = (vsip_length)atoi(argv[2]);
     vsip_mview_f *A = vsip_mcreate_f(M,N,VSIP_COL,0),
                  *Q = vsip_mcreate_f(M,N,VSIP_COL,0),
                  *R = vsip_mcreate_f(N,N,VSIP_ROW,0);
     vsip_mview_f *Id = vsip_mcreate_f(M,M,VSIP_ROW,0);
     vsip_mview_f *Idt = vsip_mtransview_f(Id);
     vsip_qr_f  *qrd = vsip_qrd_create_f(M,N,VSIP_QRD_SAVEQ);
     FILE *fptr = fopen(argv[3],"r");
     VU_mreadf_f(fptr,A);
     fclose(fptr);
     vsip_mcopy_f_f(A,Q);
     vsip_qrd_f(qrd,Q);
     printf("A =");VU_mprintm_f("9.6",A);
     {
       vsip_vview_f *Idrow = vsip_mrowview_f(Id,0);
       vsip_vputlength_f(Idrow,M * M);
       vsip_vfill_f(0,Idrow);
       vsip_vputlength_f(Idrow,M);
       vsip_vputstride_f(Idrow,M + 1);
       vsip_vfill_f(1,Idrow);
       vsip_vdestroy_f(Idrow);
       printf("I =");VU_mprintm_f("9.6",Id);
       vsip_qrdprodq_f(qrd,VSIP_MAT_NTRANS,VSIP_MAT_LSIDE,Id);
       printf("Q =");VU_mprintm_f("9.6",Id);
     }
     vsip_mprod_f(Idt,A,R);
     printf("R =");VU_mprintm_f("9.6",R);
     vsip_mprod_f(Id,R,A);
     printf("A =");VU_mprintm_f("9.6",A);
     vsip_malldestroy_f(Id);
     vsip_malldestroy_f(A);
     vsip_malldestroy_f(Q);
     vsip_qrd_destroy_f(qrd);
     } vsip_finalize((void*)0); return 0;
   }
}
