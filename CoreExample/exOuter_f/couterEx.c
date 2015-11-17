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
/* $Id: couterEx.c,v 2.0 2003/02/22 15:37:49 judd Exp $ */

/* Example of outer */
 
#include<stdio.h>
#include<vsip.h>

#define M 4                   /*length*/
#define N 3                   /*length*/

int main(){vsip_init((void*)0);
{

    int i,j;
    vsip_cvview_f* a  = vsip_cvcreate_f(M,0);
    vsip_cvview_f* b  = vsip_cvcreate_f(N,0);
    vsip_cmview_f* r = vsip_cmcreate_f(
                   vsip_cvgetlength_f(a),
                   vsip_cvgetlength_f(b),
                   VSIP_ROW,0);
    vsip_vview_f* tmpR = vsip_vrealview_f(a);
    vsip_vview_f* tmpI = vsip_vimagview_f(a);

    vsip_vramp_f(1.0, -2.0/(double)(N-1), tmpR);
    vsip_vramp_f(.5,.5,tmpI);
    vsip_vdestroy_f(tmpR); vsip_vdestroy_f(tmpI);
    tmpR = vsip_vrealview_f(b); tmpI = vsip_vimagview_f(b);
    vsip_vramp_f(1.0, 1.0 , tmpR);
    vsip_vramp_f(1.1,.1,tmpI);
    vsip_vdestroy_f(tmpR); vsip_vdestroy_f(tmpI);

    vsip_cvouter_f(vsip_cmplx_f(1,0),a, b, r);

    printf("a = [\n");
    for(i=0; i<vsip_cvgetlength_f(a); i++)
        printf("%6.3f + %6.3fi%s \n", 
            vsip_real_f(vsip_cvget_f(a,i)),
            vsip_imag_f(vsip_cvget_f(a,i)),
            (i == vsip_cvgetlength_f(a) -1) ? "":";");
        printf("]\n");
    printf("b = [\n");
    for(i=0; i<vsip_cvgetlength_f(b); i++)
        printf("%6.3f + %6.3fi%s\n ", 
            vsip_real_f(vsip_cvget_f(b,i)),
            vsip_imag_f(vsip_cvget_f(b,i)),
            (i == vsip_cvgetlength_f(b) -1) ? "":";");
        printf("]\n");
        printf("\n");
    
    printf("a * b' = \n");
    for(i=0; i<vsip_cvgetlength_f(a); i++){
       for(j=0; j<vsip_cvgetlength_f(b); j++) 
        printf("%6.3f + %6.3fi   ", 
            vsip_real_f(vsip_cmget_f(r,i,j)),
            vsip_imag_f(vsip_cmget_f(r,i,j)));
       printf("\n");
    }

    /*destroy the vector views and any associated blocks*/
    vsip_cvalldestroy_f(b);
    vsip_cvalldestroy_f(a);
    vsip_cmalldestroy_f(r);
    } vsip_finalize((void*)0); return 0;
}
