/* Created RJudd */
/* SPAWARSYSCEN D857 */
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
/* $Id: clud2Ex.c,v 2.0 2003/02/22 15:49:14 judd Exp $ */

#include<vsip.h>
#define NN 4

int main() {
vsip_init((void*)0);{
    vsip_cmview_f *A  = vsip_cmcreate_f(NN,NN,VSIP_ROW,0);
    vsip_cvview_f *x0 = vsip_cvcreate_f(NN,0);
    vsip_cvview_f *b  = vsip_cvcreate_f(NN,0);
    vsip_cmview_f *X  = vsip_cmcreate_f(NN,3,VSIP_ROW,0);
    vsip_cmview_f *XT  = vsip_cmcreate_f(NN,3,VSIP_COL,0);
    vsip_cmview_f *XH  = vsip_cmcreate_f(NN,3,VSIP_COL,0);
    vsip_cmview_f *XC  = vsip_cmcreate_f(NN,3,VSIP_COL,0);
    {  /* make up an x vector to start with */
       vsip_vview_f *Re = vsip_vrealview_f(x0);
       vsip_vview_f *Im = vsip_vimagview_f(x0);
       vsip_vramp_f(1,1,Re); vsip_vmul_f(Re,Re,Re);
       vsip_vfill_f(0.0,Im);
       vsip_vdestroy_f(Re); vsip_vdestroy_f(Im);
    }
    /* enter some data in the A matrix */
    vsip_cmput_f(A,0,0,vsip_cmplx_f(-3,2)); vsip_cmput_f(A,0,1,vsip_cmplx_f(7,2)); vsip_cmput_f(A,0,2,vsip_cmplx_f(10,2)); vsip_cmput_f(A,0,3,vsip_cmplx_f(12,2));
    vsip_cmput_f(A,1,0,vsip_cmplx_f(0,3)); vsip_cmput_f(A,1,1,vsip_cmplx_f(13,3)); vsip_cmput_f(A,1,2,vsip_cmplx_f(18,3)); vsip_cmput_f(A,1,3,vsip_cmplx_f(6,3));
    vsip_cmput_f(A,2,0,vsip_cmplx_f(2,2)); vsip_cmput_f(A,2,1,vsip_cmplx_f(-9,2)); vsip_cmput_f(A,2,2,vsip_cmplx_f(6,2)); vsip_cmput_f(A,2,3,vsip_cmplx_f(3,2));
    vsip_cmput_f(A,3,0,vsip_cmplx_f(1,1)); vsip_cmput_f(A,3,1,vsip_cmplx_f(2,1)); vsip_cmput_f(A,3,2,vsip_cmplx_f(3,1)); vsip_cmput_f(A,3,3,vsip_cmplx_f(4,1));
   {/* Print out the A Matrix so it is easy to cut and past into Matlab */
      int i,j; printf("A matrix \nA = [");for(i=0; i<NN; i++){
                  for(j=0; j<NN; j++) printf("%9.2f + %9.2fi%s",
                     vsip_real_f(vsip_cmget_f(A,i,j)),
                     vsip_imag_f(vsip_cmget_f(A,i,j)),(j == NN-1) ? "":",");
                 (i == NN - 1) ? printf("]\n") : printf(";\n");
       }
   }
   { /* Make up the B matrix so A * X = B */
     int k; 
     vsip_cvview_f *x;
     vsip_length L  = vsip_cmgetrowlength_f(X);
     for(k=0; k<L; k++){
       x  = vsip_cmcolview_f(X,k);
       vsip_cmvprod_f(A,x0,b); /* b(k) = A * x0(k) */
       vsip_cvcopy_f_f(b,x);
       vsip_csvmul_f(vsip_cmplx_f(2.0,0.0),x0,x0); /* x0(k) = 2 * x0(k-1) */
       vsip_cvdestroy_f(x);
     }
   }
   {/* Now print out B = [b1,b2,b3], note done in place so X denotes B before solving */ 
       int i,j; 
       printf("X Matrix\nX = [\n");
       for(i=0; i<NN; i++){
         for(j=0; j<3; j++) printf("%9.2f + %9.2fi%s",
                 vsip_real_f(vsip_cmget_f(X,i,j)),
                 vsip_imag_f(vsip_cmget_f(X,i,j)),(j == 2) ? "":",");
               (i == NN - 1) ? printf("]\n") : printf(";\n");
       }
   }
   {/* create lu object, make up input data for each case, solve */
      vsip_clu_f* luAop = vsip_clud_create_f(NN);
      vsip_cmcopy_f_f(X,XT);
      vsip_cmcopy_f_f(X,XH);
      vsip_cmcopy_f_f(X,XC);
      if(luAop == NULL) exit(1);
      printf("lud returns %i\n",vsip_clud_f(luAop,A));
      {  vsip_clu_attr_f attr;
         vsip_clud_getattr_f(luAop,&attr);
         printf("lud size %lu\n",attr.n);
      }
      vsip_clusol_f(luAop,VSIP_MAT_NTRANS,X);
      vsip_clusol_f(luAop,VSIP_MAT_TRANS,XT);
      vsip_clusol_f(luAop,VSIP_MAT_HERM,XH);
      vsip_clusol_f(luAop,VSIP_MAT_CONJ,XC);
      vsip_clud_destroy_f(luAop);
   }
   {int i,j; printf("X matrix Answer=> A\\X \n");for(i=0; i<NN; i++){
                 for(j=0; j<3; j++) printf("(%9.2f, %9.2f)%s",
                     vsip_real_f(vsip_cmget_f(X,i,j)),
                     vsip_imag_f(vsip_cmget_f(X,i,j)),(j == 2) ? "":",");
                 printf(";\n");
             }
   }
   {int i,j; printf("X matrix Answer for transpose=> A.'\\X\n");for(i=0; i<NN; i++){
                for(j=0; j<3; j++) printf("(%9.2f, %9.2f)%s",
                    vsip_real_f(vsip_cmget_f(XT,i,j)),
                    vsip_imag_f(vsip_cmget_f(XT,i,j)),(j == 2) ? "":",");
                printf(";\n");
           }
   }
   {int i,j; printf("X matrix Answer for hermition=> A'\\X\n");for(i=0; i<NN; i++){
                 for(j=0; j<3; j++) printf("(%9.2f, %9.2f)%s",
                     vsip_real_f(vsip_cmget_f(XH,i,j)),
                     vsip_imag_f(vsip_cmget_f(XH,i,j)),(j == 2) ? "":",");
                 printf(";\n");
             }
   }
   {int i,j; printf("X matrix Answer for conjugate=> conj(A)\\X\n");for(i=0; i<NN; i++){
                 for(j=0; j<3; j++) printf("(%9.2f, %9.2f)%s",
                     vsip_real_f(vsip_cmget_f(XC,i,j)),
                     vsip_imag_f(vsip_cmget_f(XC,i,j)),(j == 2) ? "":",");
                 printf(";\n");
             }
   }
   {
     vsip_cmalldestroy_f(A);
     vsip_cvalldestroy_f(x0);
     vsip_cvalldestroy_f(b);
     vsip_cmalldestroy_f(X);
     vsip_cmalldestroy_f(XT);
     vsip_cmalldestroy_f(XH);
     vsip_cmalldestroy_f(XC);
   }
   }vsip_finalize((void*)0);return 1;
}
