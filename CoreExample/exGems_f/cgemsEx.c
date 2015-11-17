/* Created by RJudd January 31, 1999*/
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
/* $Id: cgemsEx.c,v 2.0 2003/02/22 15:39:22 judd Exp $ */

#include <stdio.h>
#include<vsip.h>

#define M  3
#define N  4
#define L  3
#define alpha_r 2.0
#define alpha_i 1.0
#define beta_r  3.5
#define beta_i  0.5

int main(){vsip_init((void*)0);
{
   vsip_cscalar_f alpha = vsip_cmplx_f(alpha_r,alpha_i);
   vsip_cscalar_f beta = vsip_cmplx_f(beta_r,beta_i);
   void VU_cmprint_f(vsip_cmview_f*);
   void VU_cmfill_f(vsip_cmview_f*, vsip_cscalar_f);
   vsip_cmview_f *A = vsip_cmcreate_f(N,M,VSIP_ROW,0),
                 *C = vsip_cmcreate_f(N,M,VSIP_ROW,0);
   int row, col,i;
   for(row=0;row<N;row++) for(col=0;col<M;col++)
        vsip_cmput_f(A,row,col,vsip_cmplx_f(row,col + sqrt(col*row)));
   
   printf("\n A input \n");
   VU_cmprint_f(A);
   VU_cmfill_f(C,vsip_cmplx_f(0,0));
   printf("\n C input \n");
   VU_cmprint_f(C);
   printf("alpha= %f %+fi, beta= %f %+fi,\n",
               alpha_r,alpha_i,
               beta_r,beta_i);
   {
      vsip_mat_op OpA = VSIP_MAT_NTRANS;
      printf("OpA %i\n",OpA);
      for(i=0; i<L; i++){
         vsip_cgems_f(alpha,A,OpA,beta,C);
         printf("C number %i\n",i); VU_cmprint_f(C); 
      }
   }
   vsip_cmalldestroy_f(A);
   vsip_cmalldestroy_f(C);
   } vsip_finalize((void*)0); return 0;
}
     
void VU_cmprint_f(vsip_cmview_f *X)
{
    vsip_length RL = vsip_cmgetrowlength_f(X);
    vsip_length CL = vsip_cmgetcollength_f(X);
    vsip_length row,col;
    vsip_cscalar_f x;
    printf("[\n");
    for(row=0; row<CL; row++){
      for(col=0; col<RL; col++){
        x=vsip_cmget_f(X,row,col);
        printf("(%6.4f %+6.4fi%s ",vsip_real_f(x),vsip_imag_f(x),((col==(RL-1))
? ");" : ")"));
      }  
      printf("\n");
    }
    printf("];\n");
    return;
}

void VU_cmfill_f(vsip_cmview_f *X, vsip_cscalar_f a)
{
    vsip_length RL = vsip_cmgetrowlength_f(X);
    vsip_length CL = vsip_cmgetcollength_f(X);
    vsip_length row,col;
    for(row=0; row<CL; row++)
      for(col=0; col<RL; col++)
        vsip_cmput_f(X,row,col,a);
    return;
}
/* expected output */
