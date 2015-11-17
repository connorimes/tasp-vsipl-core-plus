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
/* $Id: couterEx.c,v 2.0 2003/02/22 15:46:33 judd Exp $ */

/* Example of outer */
 
#include<stdio.h>
#include<vsip.h>

#define M 4                   /*length*/
#define N 3                   /*length*/

int main(){vsip_init((void*)0);
{

    int i,j;
    vsip_cvview_d* a  = vsip_cvcreate_d(M,0);
    vsip_cvview_d* b  = vsip_cvcreate_d(N,0);
    vsip_cmview_d* r = vsip_cmcreate_d(
                   vsip_cvgetlength_d(a),
                   vsip_cvgetlength_d(b),
                   VSIP_ROW,0);
    vsip_vview_d* tmpR = vsip_vrealview_d(a);
    vsip_vview_d* tmpI = vsip_vimagview_d(a);

    vsip_vramp_d(1.0, -2.0/(double)(N-1), tmpR);
    vsip_vramp_d(.5,.5,tmpI);
    vsip_vdestroy_d(tmpR); vsip_vdestroy_d(tmpI);
    tmpR = vsip_vrealview_d(b); tmpI = vsip_vimagview_d(b);
    vsip_vramp_d(1.0, 1.0 , tmpR);
    vsip_vramp_d(1.1,.1,tmpI);
    vsip_vdestroy_d(tmpR); vsip_vdestroy_d(tmpI);

    vsip_cvouter_d(vsip_cmplx_d(1,0),a, b, r);

    printf("a = [\n");
    for(i=0; i<vsip_cvgetlength_d(a); i++)
        printf("%6.3f + %6.3fi%s \n", 
            vsip_real_d(vsip_cvget_d(a,i)),
            vsip_imag_d(vsip_cvget_d(a,i)),
            (i == vsip_cvgetlength_d(a) -1) ? "":";");
        printf("]\n");
    printf("b = [\n");
    for(i=0; i<vsip_cvgetlength_d(b); i++)
        printf("%6.3f + %6.3fi%s\n ", 
            vsip_real_d(vsip_cvget_d(b,i)),
            vsip_imag_d(vsip_cvget_d(b,i)),
            (i == vsip_cvgetlength_d(b) -1) ? "":";");
        printf("]\n");
        printf("\n");
    
    printf("a * b' = \n");
    for(i=0; i<vsip_cvgetlength_d(a); i++){
       for(j=0; j<vsip_cvgetlength_d(b); j++) 
        printf("%6.3f + %6.3fi   ", 
            vsip_real_d(vsip_cmget_d(r,i,j)),
            vsip_imag_d(vsip_cmget_d(r,i,j)));
       printf("\n");
    }

    /*destroy the vector views and any associated blocks*/
    vsip_cvalldestroy_d(b);
    vsip_cvalldestroy_d(a);
    vsip_cmalldestroy_d(r);
    }vsip_finalize((void*)0);return 0;
}
