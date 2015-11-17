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
/* $Id: example19.c,v 2.0 2003/02/22 15:27:36 judd Exp $ */

#include<vsip.h>
#define f0 5      /* Frequency */
#define fs 128    /* Sample rate */
#define Nval 75   /* Input Data Length */
#define Mval 51   /* Reference Data Length */
 
void VU_vfprintxyg_f(
       char*,vsip_vview_f*,vsip_vview_f*,char*);
int main(){vsip_init((void*)0);
{
   vsip_length max_l = Nval + Mval - 1;
   vsip_vview_f *x = vsip_vcreate_f(Nval,0);
   vsip_vview_f *h = vsip_vcreate_f(Mval,0);
   vsip_vview_f *y = vsip_vcreate_f(max_l,0);
   vsip_vview_f *z_y = vsip_vcreate_f(max_l,0);
   vsip_vview_f *z_xh = vsip_vcreate_f(Nval,0);
   vsip_corr1d_f *cor = vsip_corr1d_create_f(
              Mval,Nval,VSIP_SUPPORT_FULL,0,0);
   vsip_vramp_f(0,(2 * M_PI * f0)/ fs,x);
   vsip_vramp_f(-((vsip_scalar_f)max_l)/(2.0 * fs),
              1.0/(fs),z_y);
   vsip_vramp_f(0.0,1.0/(fs),z_xh);
   vsip_vputlength_f(x,Mval);
   vsip_vsin_f(x,h);
   vsip_vputlength_f(x,Nval);
   vsip_vsin_f(x,x);
   vsip_vputlength_f(z_xh,Mval /*h length*/);
   VU_vfprintxyg_f("%8.6f %8.6f\n",z_xh,h,"h_data");
   vsip_vputlength_f(z_xh,Nval /*x length*/);
   VU_vfprintxyg_f("%8.6f %8.6f\n",z_xh,x,"x_data");

   vsip_correlate1d_f(cor,VSIP_BIASED,h,x,y);
   vsip_vputoffset_f(z_y,0);
   vsip_vputlength_f(z_y,vsip_vgetlength_f(y));
   VU_vfprintxyg_f("%8.6f %8.6f\n",z_y,y,"y_full");

   vsip_correlate1d_f(cor,VSIP_UNBIASED,h,x,y);
   VU_vfprintxyg_f(
              "%8.6f %8.6f\n",z_y,y,"y_full_unbiased");
   vsip_corr1d_destroy_f(cor);

cor = vsip_corr1d_create_f(
                 Mval,Nval,VSIP_SUPPORT_SAME,0,0);
   vsip_vputlength_f(y,Nval);
   vsip_vputlength_f(z_y,Nval);
   vsip_vputoffset_f(z_y,(vsip_offset)(Mval/2));
   vsip_correlate1d_f(cor,VSIP_BIASED,h,x,y);
   VU_vfprintxyg_f("%8.6f %8.6f\n",z_y,y,"y_same");
   vsip_corr1d_destroy_f(cor);

   cor = vsip_corr1d_create_f(
                 Mval,Nval,VSIP_SUPPORT_MIN,0,0);
   vsip_vputlength_f(y,Nval-Mval+1);
   vsip_vputoffset_f(z_y,(vsip_offset)(Mval - 1));
   vsip_vputlength_f(z_y,Nval-Mval+1);
   vsip_correlate1d_f(cor,VSIP_BIASED,h,x,y);
   VU_vfprintxyg_f("%8.6f %8.6f\n",z_y,y,"y_min");
   vsip_corr1d_destroy_f(cor);

   vsip_valldestroy_f(x);
   vsip_valldestroy_f(h);
   vsip_valldestroy_f(y);
   } vsip_finalize((void*)0); return 0;
}

void VU_vfprintxyg_f(char* format,
                     vsip_vview_f* x,
                     vsip_vview_f* y,
                     char* fname){
    vsip_length N = vsip_vgetlength_f(y);
    vsip_length i;
    FILE *of = fopen(fname,"w");
    for(i=0; i<N; i++)
      fprintf(of,format,
                vsip_vget_f(x,i), vsip_vget_f(y,i));
    fclose(of);
    return;
}
