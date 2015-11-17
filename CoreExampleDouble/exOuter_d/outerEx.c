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
/* $Id: outerEx.c,v 2.0 2003/02/22 15:46:33 judd Exp $ */

/* Example of outer */
 
#include<stdio.h>
#include<vsip.h>

#define M 4                   /*length*/
#define N 3                   /*length*/

int main(){vsip_init((void*)0);
{

    int i,j;
    vsip_vview_d* a  = vsip_vcreate_d(M,0);
    vsip_vview_d* b  = vsip_vcreate_d(N,0);
    vsip_mview_d* r = vsip_mcreate_d(
                      vsip_vgetlength_d(a),
                      vsip_vgetlength_d(b),
                      VSIP_ROW,0);
    vsip_vramp_d(1.0, 1.0 , b);
    vsip_vramp_d(1.0, -2.0/(double)(N-1), a);

    vsip_vouter_d(1,a, b, r);
    printf("a = [\n");
    for(i=0; i<vsip_vgetlength_d(a); i++)
        printf("%6.3f%s\n", vsip_vget_d(a,i),
        (i == vsip_vgetlength_d(a) -1) ? "":";");
    printf("]\n");
    printf("b = [\n");
    for(i=0; i<vsip_vgetlength_d(b); i++)
        printf("%6.3f%s\n", vsip_vget_d(b,i),
        (i == vsip_vgetlength_d(a) -1) ? "":";");
        printf("]\n");
    printf("\na * b' = \n");
    for(i=0; i<vsip_vgetlength_d(a); i++){
       for(j=0; j<vsip_vgetlength_d(b); j++) 
          printf("%6.3f  ",vsip_mget_d(r,i,j));
       printf("\n");
    }
    printf("]\n");

    /*destroy the vector views and any associated blocks*/
    vsip_valldestroy_d(b);
    vsip_valldestroy_d(a);
    vsip_malldestroy_d(r);
    }vsip_finalize((void*)0);return 0;
}
