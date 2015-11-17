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
/* $Id: mvprodEx.c,v 2.0 2003/02/22 15:38:22 judd Exp $ */

#include <stdio.h>
#include<vsip.h>

#define N  4
#define P  5

int main(){vsip_init((void*)0);
{
   vsip_vview_f *a = vsip_vcreate_f(N,0),
                *r = vsip_vcreate_f(P,0);
   vsip_mview_f *B = vsip_mcreate_f(P,N,VSIP_ROW,0);
   int i, j;
   vsip_vramp_f(1.0,1.0,a);
   for(i=0;i<P;i++) for(j=0;j<N;j++)
        vsip_mput_f(B,i,j,1 + i * j);
   
   printf("\n  vector input \n");
   vsip_mvprod_f(B,a,r);
   for(j=0;j<N;j++){
        printf(" %6.2f  ",vsip_vget_f(a,j));
   }
   printf("\n");
   printf("\n matrix input \n");
   {for(i=0; i<P; i++) {for(j=0;j<N;j++){
           printf(" %6.2f  ",vsip_mget_f(B,i,j));
           }
       printf(";\n");
       }
   }
   printf("\n vector output \n");
   for(j=0;j<P;j++){
           printf("%6.2f ",vsip_vget_f(r,j));
   }
   printf("\n");
   vsip_valldestroy_f(a);
   vsip_valldestroy_f(r);
   vsip_malldestroy_f(B);
   } vsip_finalize((void*)0); return 0;
}
