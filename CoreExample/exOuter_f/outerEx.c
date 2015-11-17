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
/* $Id: outerEx.c,v 2.0 2003/02/22 15:37:49 judd Exp $ */

/* Example of outer */
 
#include<stdio.h>
#include<vsip.h>

#define M 4                   /*length*/
#define N 3                   /*length*/

int main(){vsip_init((void*)0);
{

    int i,j;
    vsip_vview_f* a  = vsip_vcreate_f(M,0);
    vsip_vview_f* b  = vsip_vcreate_f(N,0);
    vsip_mview_f* r = vsip_mcreate_f(
                      vsip_vgetlength_f(a),
                      vsip_vgetlength_f(b),
                      VSIP_ROW,0);
    vsip_vramp_f(1.0, 1.0 , b);
    vsip_vramp_f(1.0, -2.0/(double)(N-1), a);

    vsip_vouter_f(1,a, b, r);
    printf("a = [\n");
    for(i=0; i<vsip_vgetlength_f(a); i++)
        printf("%6.3f%s\n", vsip_vget_f(a,i),
        (i == vsip_vgetlength_f(a) -1) ? "":";");
    printf("]\n");
    printf("b = [\n");
    for(i=0; i<vsip_vgetlength_f(b); i++)
        printf("%6.3f%s\n", vsip_vget_f(b,i),
        (i == vsip_vgetlength_f(a) -1) ? "":";");
        printf("]\n");
    printf("\na * b' = \n");
    for(i=0; i<vsip_vgetlength_f(a); i++){
       for(j=0; j<vsip_vgetlength_f(b); j++) 
          printf("%6.3f  ",vsip_mget_f(r,i,j));
       printf("\n");
    }
    printf("]\n");

    /*destroy the vector views and any associated blocks*/
    vsip_valldestroy_f(b);
    vsip_valldestroy_f(a);
    vsip_malldestroy_f(r);
    } vsip_finalize((void*)0); return 0;
}
