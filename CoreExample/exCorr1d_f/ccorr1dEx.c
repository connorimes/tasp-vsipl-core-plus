/* Created RJudd March 18, 1999 */
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
/* $Id: ccorr1dEx.c,v 2.0 2003/02/22 15:42:00 judd Exp $ */

/* to do a feel good test on complex correlate function */

#include<vsip.h>
#include<VU.h>

#define f0 25
#define fs 128
#define Nval 75
#define Mval 50

int main(){vsip_init((void*)0);
{
   vsip_cvview_f *x = vsip_cvcreate_f(Nval,0);
   vsip_cvview_f *h = vsip_cvcreate_f(Mval,0);
   vsip_cvview_f *y = vsip_cvcreate_f(Nval+Mval-1,0); 
   vsip_ccorr1d_f *cor = vsip_ccorr1d_create_f(Mval,Nval,VSIP_SUPPORT_FULL,0,0);
   vsip_vview_f *xr = vsip_vrealview_f(x); vsip_vview_f *xi = vsip_vimagview_f(x);
   vsip_vview_f *hr = vsip_vrealview_f(h); vsip_vview_f *hi = vsip_vimagview_f(h);
   vsip_vramp_f(0,(2 * M_PI * f0)/ fs,xr);
   vsip_veuler_f(xr,x); /* in-place operation allowed by specification */
   vsip_vputlength_f(xr,Mval); /* Mval >= Nval , required by specification */
   vsip_vputlength_f(xi,Mval);
   vsip_vadd_f(xi,xr,hr);
   vsip_vmul_f(xr,xi,hi);
   vsip_vdestroy_f(xr); vsip_vdestroy_f(xi);
   vsip_vdestroy_f(hr); vsip_vdestroy_f(hi);

   printf("h = ");VU_cvprintm_f("6.4",h);
   printf("x = ");VU_cvprintm_f("6.4",x);

   vsip_ccorrelate1d_f(cor,VSIP_BIASED,h,x,y);
   printf("yFull = ");VU_cvprintm_f("6.4",y);
   vsip_ccorr1d_destroy_f(cor);

   cor = vsip_ccorr1d_create_f(Mval,Nval,VSIP_SUPPORT_FULL,0,0);
   vsip_ccorrelate1d_f(cor,VSIP_UNBIASED,h,x,y);
   printf("yFullU = ");VU_cvprintm_f("6.4",y);
   vsip_ccorr1d_destroy_f(cor);

   cor = vsip_ccorr1d_create_f(Mval,Nval,VSIP_SUPPORT_SAME,0,0);
   vsip_cvputlength_f(y,Nval);
   vsip_ccorrelate1d_f(cor,VSIP_BIASED,h,x,y);
   printf("ySame = ");VU_cvprintm_f("6.4",y);
   vsip_ccorr1d_destroy_f(cor);

   cor = vsip_ccorr1d_create_f(Mval,Nval,VSIP_SUPPORT_SAME,0,0);
   vsip_cvputlength_f(y,Nval);
   vsip_ccorrelate1d_f(cor,VSIP_UNBIASED,h,x,y);
   printf("ySameU = ");VU_cvprintm_f("6.4",y);
   vsip_ccorr1d_destroy_f(cor);

   cor = vsip_ccorr1d_create_f(Mval,Nval,VSIP_SUPPORT_MIN,0,0);
   vsip_cvputlength_f(y,Nval-Mval+1);
   vsip_ccorrelate1d_f(cor,VSIP_BIASED,h,x,y);
   printf("yMin= ");VU_cvprintm_f("6.4",y);
   vsip_ccorr1d_destroy_f(cor);

   cor = vsip_ccorr1d_create_f(Mval,Nval,VSIP_SUPPORT_MIN,0,0);
   vsip_cvputlength_f(y,Nval-Mval+1);
   vsip_ccorrelate1d_f(cor,VSIP_UNBIASED,h,x,y);
   printf("yMinU= ");VU_cvprintm_f("6.4",y);
   vsip_ccorr1d_destroy_f(cor);

   vsip_cvalldestroy_f(x);
   vsip_cvalldestroy_f(h);
   vsip_cvalldestroy_f(y);
   } vsip_finalize((void*)0); return 0;
}
