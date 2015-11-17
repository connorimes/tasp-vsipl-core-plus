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
/* $Id: ccorr1dEx.c,v 2.0 2003/02/22 15:46:19 judd Exp $ */

/* to do a feel good test on complex correlate function */

#include<vsip.h>
#include<VU.h>

#define f0 25
#define fs 128
#define Nval 75
#define Mval 50

int main(){vsip_init((void*)0);
{
   vsip_cvview_d *x = vsip_cvcreate_d(Nval,0);
   vsip_cvview_d *h = vsip_cvcreate_d(Mval,0);
   vsip_cvview_d *y = vsip_cvcreate_d(Nval+Mval-1,0); 
   vsip_ccorr1d_d *cor = vsip_ccorr1d_create_d(Mval,Nval,VSIP_SUPPORT_FULL,0,0);
   vsip_vview_d *xr = vsip_vrealview_d(x); vsip_vview_d *xi = vsip_vimagview_d(x);
   vsip_vview_d *hr = vsip_vrealview_d(h); vsip_vview_d *hi = vsip_vimagview_d(h);
   vsip_vramp_d(0,(2 * M_PI * f0)/ fs,xr);
   vsip_veuler_d(xr,x); /* in-place operation allowed by specification */
   vsip_vputlength_d(xr,Mval); /* Mval >= Nval , required by specification */
   vsip_vputlength_d(xi,Mval);
   vsip_vadd_d(xi,xr,hr);
   vsip_vmul_d(xr,xi,hi);
   vsip_vdestroy_d(xr); vsip_vdestroy_d(xi);
   vsip_vdestroy_d(hr); vsip_vdestroy_d(hi);

   printf("h = ");VU_cvprintm_d("6.4",h);
   printf("x = ");VU_cvprintm_d("6.4",x);

   vsip_ccorrelate1d_d(cor,VSIP_BIASED,h,x,y);
   { vsip_corr1d_attr attr;
     vsip_ccorr1d_getattr_d(cor,&attr);
     printf("hLength = %ld\n",attr.ref_len);
     printf("xLength = %ld\n",attr.data_len);
     printf("support = %d\n",attr.support);
     printf("outLength = %ld\n",attr.lag_len);
   }
   printf("yFull = ");VU_cvprintm_d("6.4",y);
   vsip_ccorr1d_destroy_d(cor);

   cor = vsip_ccorr1d_create_d(Mval,Nval,VSIP_SUPPORT_FULL,0,0);
   vsip_ccorrelate1d_d(cor,VSIP_UNBIASED,h,x,y);
   printf("yFullU = ");VU_cvprintm_d("6.4",y);
   vsip_ccorr1d_destroy_d(cor);

   cor = vsip_ccorr1d_create_d(Mval,Nval,VSIP_SUPPORT_SAME,0,0);
   vsip_cvputlength_d(y,Nval);
   vsip_ccorrelate1d_d(cor,VSIP_BIASED,h,x,y);
   printf("ySame = ");VU_cvprintm_d("6.4",y);
   vsip_ccorr1d_destroy_d(cor);

   cor = vsip_ccorr1d_create_d(Mval,Nval,VSIP_SUPPORT_SAME,0,0);
   vsip_cvputlength_d(y,Nval);
   vsip_ccorrelate1d_d(cor,VSIP_UNBIASED,h,x,y);
   printf("ySameU = ");VU_cvprintm_d("6.4",y);
   vsip_ccorr1d_destroy_d(cor);

   cor = vsip_ccorr1d_create_d(Mval,Nval,VSIP_SUPPORT_MIN,0,0);
   vsip_cvputlength_d(y,Nval-Mval+1);
   vsip_ccorrelate1d_d(cor,VSIP_BIASED,h,x,y);
   printf("yMin= ");VU_cvprintm_d("6.4",y);
   vsip_ccorr1d_destroy_d(cor);

   cor = vsip_ccorr1d_create_d(Mval,Nval,VSIP_SUPPORT_MIN,0,0);
   vsip_cvputlength_d(y,Nval-Mval+1);
   vsip_ccorrelate1d_d(cor,VSIP_UNBIASED,h,x,y);
   printf("yMinU= ");VU_cvprintm_d("6.4",y);
   vsip_ccorr1d_destroy_d(cor);

   vsip_cvalldestroy_d(x);
   vsip_cvalldestroy_d(h);
   vsip_cvalldestroy_d(y);
   }vsip_finalize((void*)0);return 0;
}
