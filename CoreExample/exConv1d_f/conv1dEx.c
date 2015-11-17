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
/* $Id: conv1dEx.c,v 2.0 2003/02/22 15:42:04 judd Exp $ */

#include<vsip.h>
#include<VU.h>

#define f0 2
#define fs 10000
#define Ds 3
#define Nl 10000
#define Ml 500

int main(){vsip_init((void*)0);
{
   vsip_length Yl = Nl + Ml -1;
   vsip_vview_f *h = vsip_vcreate_hanning_f(Ml,0)/*vsip_vcreate_f(1024,0)*/,
                *x = vsip_vcreate_f(Nl,0),
                *y = vsip_vcreate_f(Yl,0);
/*   FILE *hfile = fopen("hfile.data","r");*/
/*   FILE *xfile = fopen("xfile.data","r");*/
/*   VU_vreadf_f(hfile,h); */
/*   VU_vreadf_f(xfile,x); */
   vsip_symmetry sym = VSIP_NONSYM;
 /*  vsip_length hl = Ml;
     if(hl % 2){
        sym = VSIP_SYM_EVEN_LEN_ODD;
        hl = (hl/2 + 1);
     } else {
        sym = VSIP_SYM_EVEN_LEN_EVEN;
        hl = hl/2;
     } 
   vsip_vputlength_f(h,hl);  */
/*   vsip_vputlength_f(y,37); */
   printf("M = %d;D = %d;N = %d;\n",Ml,Ds,Nl);
   vsip_vramp_f(0,2 * M_PI * f0/fs,x);
   vsip_vsin_f(x,x);
   printf("h =");VU_vprintm_f("8.6",h);
   printf("x =");VU_vprintm_f("8.6",x);  
   fflush(stdout);
   {
      vsip_conv1d_f *conv = vsip_conv1d_create_f(h,sym,Nl,Ds,VSIP_SUPPORT_FULL,0,0);
      { vsip_length length = (Nl + Ml -2)/Ds + 1;
        vsip_vputlength_f(y,length);
      }
      vsip_convolve1d_f(conv,x,y);
      vsip_conv1d_destroy_f(conv); 
   }
   printf("yFull =");VU_vprintm_f("8.6",y);
   fflush(stdout);
   {
      vsip_conv1d_f *conv = vsip_conv1d_create_f(h,sym,Nl,Ds,VSIP_SUPPORT_SAME,0,0);
      { vsip_length length = (Nl - 1)/Ds + 1;
        vsip_vputlength_f(y,length);
      }
      vsip_convolve1d_f(conv,x,y);
      vsip_conv1d_destroy_f(conv);
   }
   printf("ySame =");VU_vprintm_f("8.6",y);
   fflush(stdout);
   {
      vsip_conv1d_f *conv = vsip_conv1d_create_f(h,sym,Nl,Ds,VSIP_SUPPORT_MIN,0,0);
      { vsip_length length = (Nl - 1)/Ds - (Ml -1)/Ds + 1;
        vsip_vputlength_f(y,length);
      }
      vsip_convolve1d_f(conv,x,y);
      vsip_conv1d_destroy_f(conv);
   }
   printf("yMin =");VU_vprintm_f("8.6",y);
   fflush(stdout);
   vsip_valldestroy_f(h); vsip_valldestroy_f(x); vsip_valldestroy_f(y);
   } vsip_finalize((void*)0); return 0;
}
