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
/* $Id: conv1dEx.c,v 2.0 2003/02/22 15:46:18 judd Exp $ */

#include<vsip.h>
#include<VU.h>

#define f0 2
#define fs 2000
#define Ds 2
#define Nl 2000
#define Ml 601

int main(){vsip_init((void*)0);
{
   vsip_length Yl = Nl + Ml -1;
   vsip_vview_d *h = vsip_vcreate_hanning_d(Ml,0)/*vsip_vcreate_d(1024,0)*/,
                *x = vsip_vcreate_d(Nl,0),
                *y = vsip_vcreate_d(Yl,0);
/*   FILE *hfile = fopen("hfile.data","r");*/
/*   FILE *xfile = fopen("xfile.data","r");*/
/*   VU_vreadf_d(hfile,h); */
/*   VU_vreadf_d(xfile,x); */
/*   vsip_vputlength_d(h,13); */
/*   vsip_vputlength_d(y,37); */
   vsip_vramp_d(0,2 * M_PI * f0/fs,x);
   vsip_vsin_d(x,x);
   printf("h =");VU_vprintm_d("9.6",h);
   printf("x =");VU_vprintm_d("9.6",x);  
   {
      vsip_conv1d_d *conv = vsip_conv1d_create_d(h,VSIP_NONSYM,Nl,Ds,VSIP_SUPPORT_FULL,0,0);
      { vsip_length length = (Nl + Ml -2)/Ds + 1;
        vsip_vputlength_d(y,length);
      }
      vsip_convolve1d_d(conv,x,y);
      { vsip_conv1d_attr attr;
        vsip_conv1d_getattr_d(conv,&attr);
        printf("kernel_len = %ld; \n symm = %d; \n data_len = %ld; \n support = %d;  \n out_len = %ld;  \n decimation = %d; \n",
                attr.kernel_len,
                attr.symm,
                attr.data_len,
                attr.support,
                attr.out_len,
                attr.decimation);
      }
      vsip_conv1d_destroy_d(conv); 
   }
   printf("yFull =");VU_vprintm_d("9.6",y);
   {
      vsip_conv1d_d *conv = vsip_conv1d_create_d(h,VSIP_NONSYM,Nl,Ds,VSIP_SUPPORT_SAME,0,0);
      { vsip_length length = (Nl - 1)/Ds + 1;
        vsip_vputlength_d(y,length);
      }
      vsip_convolve1d_d(conv,x,y);
      vsip_conv1d_destroy_d(conv);
   }
   printf("ySame =");VU_vprintm_d("9.6",y);
   {
      vsip_conv1d_d *conv = vsip_conv1d_create_d(h,VSIP_NONSYM,Nl,Ds,VSIP_SUPPORT_MIN,0,0);
      { vsip_length length = (Nl - 1)/Ds - (Ml -1)/Ds + 1;
        vsip_vputlength_d(y,length);
      }
      vsip_convolve1d_d(conv,x,y);
      vsip_conv1d_destroy_d(conv);
   }
   printf("yMin =");VU_vprintm_d("9.6",y);
   vsip_valldestroy_d(h); vsip_valldestroy_d(x); vsip_valldestroy_d(y);
   }vsip_finalize((void*)0);return 0;
}
