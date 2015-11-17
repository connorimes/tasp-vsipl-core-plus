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
/* $Id: cvmprodEx.c,v 2.0 2003/02/22 15:38:22 judd Exp $ */

#include <stdio.h>
#include<vsip.h>

#define M  3
#define N  4
#define P  5

int main(){vsip_init((void*)0);
{
/*   vsip_cmview_f *B = vsip_cmcreate_f(P,N,VSIP_ROW,0);*/
   vsip_scalar_f Re[20], Im[20];
   vsip_cblock_f *Bblock = vsip_cblockbind_f(Re,Im,20,0);
   vsip_cmview_f *B = vsip_cmbind_f(Bblock,0,4,5,1,4);
   vsip_cvview_f *a = vsip_cvcreate_f(P,0),
                 *r = vsip_cvcreate_f(N,0);
   int i, j;
   for(i=0;i<P;i++) 
        vsip_cvput_f(a,i,vsip_cmplx_f(i,1 + sqrt(i)));
   
   for(i=0;i<P;i++) for(j=0;j<N;j++)
        vsip_cmput_f(B,i,j,vsip_cmplx_f(1 , i * j));
   
   vsip_cvmprod_f(a,B,r);
   printf("\n vector input \n v=[");

   for(i=0;i<P;i++)
          printf("(%5.2f %+5.2fi) ",
          vsip_real_f(vsip_cvget_f(a,i)),
          vsip_imag_f(vsip_cvget_f(a,i)));
   printf("]\n");
   
   printf("\n B input \n B =[\n");
   {for(i=0;i<P;i++) {for(j=0;j<N;j++){
           printf(" (%5.2f %+5.2fi) ",
             vsip_real_f(vsip_cmget_f(B,i,j)),
             vsip_imag_f(vsip_cmget_f(B,i,j)));
           }
           printf(";\n");
       }
       printf("]\n");
   }
   printf("\n vector output \n");
   for(i=0;i<N;i++)
           printf("(%5.2f, %5.2f) ",
             vsip_real_f(vsip_cvget_f(r,i)),
             vsip_imag_f(vsip_cvget_f(r,i)));
   printf("\n");
   vsip_cvalldestroy_f(a);
   vsip_cmalldestroy_f(B);
   vsip_cvalldestroy_f(r);
   } vsip_finalize((void*)0); return 0;
}
