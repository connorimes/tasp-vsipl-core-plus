
/* Created by RJudd April 21, 1998 */
/* SPAWARSYSCEN D881 */
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
/* $Id: clud2Ex.c,v 2.0 2003/02/22 15:46:30 judd Exp $ */
/* A "feel good" test for lud */

#include<vsip.h>
#define N 4

int main(){vsip_init((void*)0);
{
    vsip_cmview_d *A  = vsip_cmcreate_d(N,N,VSIP_COL,0);
    vsip_cvview_d *x0 = vsip_cvcreate_d(N,0);
    vsip_cvview_d *b  = vsip_cvcreate_d(N,0);
    vsip_cmview_d *X  = vsip_cmcreate_d(N,3,VSIP_ROW,0);
    vsip_cmview_d *XT  = vsip_cmcreate_d(N,3,VSIP_COL,0);
    vsip_cmview_d *XH  = vsip_cmcreate_d(N,3,VSIP_COL,0);
    vsip_cmview_d *XC  = vsip_cmcreate_d(N,3,VSIP_COL,0);
    {  /* make up an x vector to start with */
       vsip_vview_d *Re = vsip_vrealview_d(x0);
       vsip_vview_d *Im = vsip_vimagview_d(x0);
       vsip_vramp_d(1,1,Re); vsip_vmul_d(Re,Re,Re);
       vsip_vfill_d(0.0,Im);
       vsip_vdestroy_d(Re); vsip_vdestroy_d(Im);
    }
    /* enter some data in the A matrix */
    vsip_cmput_d(A,0,0,vsip_cmplx_d(-3,2)); vsip_cmput_d(A,0,1,vsip_cmplx_d(7,2)); vsip_cmput_d(A,0,2,vsip_cmplx_d(10,2)); vsip_cmput_d(A,0,3,vsip_cmplx_d(12,2));
    vsip_cmput_d(A,1,0,vsip_cmplx_d(0,3)); vsip_cmput_d(A,1,1,vsip_cmplx_d(13,3)); vsip_cmput_d(A,1,2,vsip_cmplx_d(18,3)); vsip_cmput_d(A,1,3,vsip_cmplx_d(6,3));
    vsip_cmput_d(A,2,0,vsip_cmplx_d(2,2)); vsip_cmput_d(A,2,1,vsip_cmplx_d(-9,2)); vsip_cmput_d(A,2,2,vsip_cmplx_d(6,2)); vsip_cmput_d(A,2,3,vsip_cmplx_d(3,2));
    vsip_cmput_d(A,3,0,vsip_cmplx_d(1,1)); vsip_cmput_d(A,3,1,vsip_cmplx_d(2,1)); vsip_cmput_d(A,3,2,vsip_cmplx_d(3,1)); vsip_cmput_d(A,3,3,vsip_cmplx_d(4,1));
   {/* Print out the A Matrix so it is easy to cut and past into Matlab */
      int i,j; printf("A matrix \nA = [");for(i=0; i<N; i++){
                  for(j=0; j<N; j++) printf("%9.2f + %9.2fi%s",
                     vsip_real_d(vsip_cmget_d(A,i,j)),
                     vsip_imag_d(vsip_cmget_d(A,i,j)),(j == N-1) ? "":",");
                 (i == N - 1) ? printf("]\n") : printf(";\n");
       }
   }
   { /* Make up the B matrix so A * X = B */
     int k; 
     vsip_cvview_d *x;
     vsip_length L  = vsip_cmgetrowlength_d(X);
     for(k=0; k<L; k++){
       x  = vsip_cmcolview_d(X,k);
       vsip_cmvprod_d(A,x0,b); /* b(k) = A * x0(k) */
       vsip_cvcopy_d_d(b,x);
       vsip_csvmul_d(vsip_cmplx_d(2.0,0.0),x0,x0); /* x0(k) = 2 * x0(k-1) */
       vsip_cvdestroy_d(x);
     }
   }
   {/* Now print out B = [b1,b2,b3], note done in place so X denotes B before solving */ 
       int i,j; 
       printf("X Matrix\nX = [\n");
       for(i=0; i<N; i++){
         for(j=0; j<3; j++) printf("%9.2f + %9.2fi%s",
                 vsip_real_d(vsip_cmget_d(X,i,j)),
                 vsip_imag_d(vsip_cmget_d(X,i,j)),(j == 2) ? "":",");
               (i == N - 1) ? printf("]\n") : printf(";\n");
       }
   }
   {/* create lu object, make up input data for each case, solve */
      vsip_clu_d* luAop = vsip_clud_create_d(N);
      vsip_cmcopy_d_d(X,XT);
      vsip_cmcopy_d_d(X,XH);
      vsip_cmcopy_d_d(X,XC);
      if(luAop == NULL) exit(1);
      printf("lud returns %i\n",vsip_clud_d(luAop,A));
      vsip_clusol_d(luAop,VSIP_MAT_NTRANS,X);
      vsip_clusol_d(luAop,VSIP_MAT_TRANS,XT);
      vsip_clusol_d(luAop,VSIP_MAT_HERM,XH);
      vsip_clusol_d(luAop,VSIP_MAT_CONJ,XC);
      vsip_clud_destroy_d(luAop);
   }
   {int i,j; printf("X matrix Answer=> A\\X \n");for(i=0; i<N; i++){
                 for(j=0; j<3; j++) printf("(%9.2f, %9.2f)%s",
                     vsip_real_d(vsip_cmget_d(X,i,j)),
                     vsip_imag_d(vsip_cmget_d(X,i,j)),(j == 2) ? "":",");
                 printf(";\n");
             }
   }
   {int i,j; printf("X matrix Answer for transpose=> A.'\\X\n");for(i=0; i<N; i++){
                for(j=0; j<3; j++) printf("(%9.2f, %9.2f)%s",
                    vsip_real_d(vsip_cmget_d(XT,i,j)),
                    vsip_imag_d(vsip_cmget_d(XT,i,j)),(j == 2) ? "":",");
                printf(";\n");
           }
   }
   {int i,j; printf("X matrix Answer for hermition=> A'\\X\n");for(i=0; i<N; i++){
                 for(j=0; j<3; j++) printf("(%9.2f, %9.2f)%s",
                     vsip_real_d(vsip_cmget_d(XH,i,j)),
                     vsip_imag_d(vsip_cmget_d(XH,i,j)),(j == 2) ? "":",");
                 printf(";\n");
             }
   }
   {int i,j; printf("X matrix Answer for conjugate=> conj(A)\\X\n");for(i=0; i<N; i++){
                 for(j=0; j<3; j++) printf("(%9.2f, %9.2f)%s",
                     vsip_real_d(vsip_cmget_d(XC,i,j)),
                     vsip_imag_d(vsip_cmget_d(XC,i,j)),(j == 2) ? "":",");
                 printf(";\n");
             }
   }
   {
     vsip_cmalldestroy_d(A);
     vsip_cvalldestroy_d(x0);
     vsip_cvalldestroy_d(b);
     vsip_cmalldestroy_d(X);
     vsip_cmalldestroy_d(XT);
     vsip_cmalldestroy_d(XH);
     vsip_cmalldestroy_d(XC);
   }
   }vsip_finalize((void*)0);return 1;
}
