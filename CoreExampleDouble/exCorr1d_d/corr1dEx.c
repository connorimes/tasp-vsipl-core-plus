/* Created RJudd March 17, 1999 */
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
/* $Id: corr1dEx.c,v 2.0 2003/02/22 15:46:19 judd Exp $ */

/* to do a feel good test on correlate function */

#include<vsip.h>
#include<VU.h>

#define f0 25
#define fs 128
#define Nval 75
#define Mval 50

int main(){vsip_init((void*)0);
{
   vsip_vview_d *x = vsip_vcreate_d(Nval,0);
/*   vsip_vview_d *h = vsip_vcreate_hanning_d(Mval,0); */
   vsip_vview_d *h = vsip_vcreate_d(Mval,0);
   vsip_vview_d *y = vsip_vcreate_d(Nval+Mval-1,0); 
   vsip_corr1d_d *cor = vsip_corr1d_create_d(Mval,Nval,VSIP_SUPPORT_FULL,0,0);
   vsip_vramp_d(0,(2 * M_PI * f0)/ fs,x);
   vsip_vputlength_d(x,Mval);
   vsip_vsin_d(x,h);
   vsip_vputlength_d(x,Nval);
   vsip_vsin_d(x,x);

   printf("h = ");VU_vprintm_d("6.4",h);
   printf("x = ");VU_vprintm_d("6.4",x);

   vsip_correlate1d_d(cor,VSIP_BIASED,h,x,y);
   { vsip_corr1d_attr attr;
     vsip_corr1d_getattr_d(cor,&attr);
     printf("hLength = %ld\n",attr.ref_len);
     printf("xLength = %ld\n",attr.data_len);
     printf("support = %d\n",attr.support);
     printf("outLength = %ld\n",attr.lag_len);
   }
   printf("yFull = ");VU_vprintm_d("6.4",y);
   vsip_corr1d_destroy_d(cor);

   cor = vsip_corr1d_create_d(Mval,Nval,VSIP_SUPPORT_FULL,0,0);
   vsip_correlate1d_d(cor,VSIP_UNBIASED,h,x,y);
   printf("yFullU = ");VU_vprintm_d("6.4",y);
   vsip_corr1d_destroy_d(cor);

   cor = vsip_corr1d_create_d(Mval,Nval,VSIP_SUPPORT_SAME,0,0);
   vsip_vputlength_d(y,Nval);
   vsip_correlate1d_d(cor,VSIP_BIASED,h,x,y);
   printf("ySame = ");VU_vprintm_d("6.4",y);
   vsip_corr1d_destroy_d(cor);

   cor = vsip_corr1d_create_d(Mval,Nval,VSIP_SUPPORT_SAME,0,0);
   vsip_vputlength_d(y,Nval);
   vsip_correlate1d_d(cor,VSIP_UNBIASED,h,x,y);
   printf("ySameU = ");VU_vprintm_d("6.4",y);
   vsip_corr1d_destroy_d(cor);

   cor = vsip_corr1d_create_d(Mval,Nval,VSIP_SUPPORT_MIN,0,0);
   vsip_vputlength_d(y,Nval-Mval+1);
   vsip_correlate1d_d(cor,VSIP_BIASED,h,x,y);
   printf("yMin= ");VU_vprintm_d("6.4",y);
   vsip_corr1d_destroy_d(cor);

   cor = vsip_corr1d_create_d(Mval,Nval,VSIP_SUPPORT_MIN,0,0);
   vsip_vputlength_d(y,Nval-Mval+1);
   vsip_correlate1d_d(cor,VSIP_UNBIASED,h,x,y);
   printf("yMinU= ");VU_vprintm_d("6.4",y);
   vsip_corr1d_destroy_d(cor);

   vsip_valldestroy_d(x);
   vsip_valldestroy_d(h);
   vsip_valldestroy_d(y);
   }vsip_finalize((void*)0);return 0;
}
