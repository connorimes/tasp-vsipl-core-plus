/* Created by RJudd */
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
/* $Id: cmvprodEx.c,v 2.0 2003/02/22 15:46:32 judd Exp $ */

#include <stdio.h>
#include<vsip.h>

#define M  3
#define N  4
#define P  5

int main(){vsip_init((void*)0);
{
   vsip_cmview_d *A = vsip_cmcreate_d(P,N,VSIP_ROW,0);
   vsip_cvview_d *b = vsip_cvcreate_d(N,0),
                 *r = vsip_cvcreate_d(P,0);
   int i, j;
   for(i=0;i<N;i++) 
        vsip_cvput_d(b,i,vsip_cmplx_d(i,1 + sqrt(i)));
   
   for(i=0;i<P;i++) for(j=0;j<N;j++)
        vsip_cmput_d(A,i,j,vsip_cmplx_d(1 , i * j));
   
   vsip_cmvprod_d(A,b,r);
   printf("\n vector input \n");

   for(i=0;i<N;i++)
          printf("(%5.2f, %5.2f) ",
          vsip_real_d(vsip_cvget_d(b,i)),
          vsip_imag_d(vsip_cvget_d(b,i)));
   printf("\n");
   
   printf("\n B input \n");
   {for(i=0;i<P;i++) {for(j=0;j<N;j++){
           printf(": (%5.2f, %5.2f) ",
             vsip_real_d(vsip_cmget_d(A,i,j)),
             vsip_imag_d(vsip_cmget_d(A,i,j)));
           }
       printf(":\n");
       }
   }
   printf("\n vector output \n");
   for(i=0;i<P;i++)
           printf("(%5.2f, %5.2f) ",
             vsip_real_d(vsip_cvget_d(r,i)),
             vsip_imag_d(vsip_cvget_d(r,i)));
   printf("\n");
   vsip_cvalldestroy_d(b);
   vsip_cmalldestroy_d(A);
   vsip_cvalldestroy_d(r);
   }vsip_finalize((void*)0);return 0;
}
