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
/* $Id: rcfftopEx.c,v 2.0 2003/02/22 15:46:38 judd Exp $ */

#include<vsip.h>

#define VU_PI 3.141592653589793
#define F  .15
#define L  24

int main (){vsip_init((void*)0);
{
  int i;
  vsip_cvview_d* vectorOut = vsip_cvcreate_d(L/2 + 1,0);
  vsip_vview_d* vectorIn = vsip_vcreate_d(L,0);
  vsip_vview_d* ivectorOut = vsip_vcreate_d(L,0);
  vsip_fft_d* fftplan  = vsip_rcfftop_create_d(L,1.0/L,0,0);
  vsip_fft_d* ifftplan = vsip_crfftop_create_d(L,(double)(1.0),0,0);
  char printbuffer[L/2][40];

  vsip_vramp_d(0, 2 * VU_PI * F, vectorIn);
  vsip_vcos_d(vectorIn,vectorIn);

  /* print vectorIn */
  for(i=0; i<L/2; i++)
       sprintf(printbuffer[i],"%2d, %2d input-> %7.3f, %7.3f",i, i+L/2, vsip_vget_d(vectorIn,i), vsip_vget_d(vectorIn,i+L/2));

  /*find the fft*/
  vsip_rcfftop_d(fftplan,vectorIn,vectorOut);
  /*find the inverse fft*/
  vsip_crfftop_d(ifftplan,vectorOut,ivectorOut);
  /*print it */
  for(i=0; i<L/2; i++)
     printf("%s   fft -> (%9.4f, %9.4f) ifft-> %7.3f, %7.3f\n" ,
           printbuffer[i],
           vsip_real_d(vsip_cvget_d(vectorOut,i)),
           vsip_imag_d(vsip_cvget_d(vectorOut,i)),
           vsip_vget_d(ivectorOut,i), 
           vsip_vget_d(ivectorOut,i+L/2));
  printf("                                  fft -> (%9.4f, %9.4f)\n",
           vsip_real_d(vsip_cvget_d(vectorOut,i)),
           vsip_imag_d(vsip_cvget_d(vectorOut,i)));
  {
     vsip_cvalldestroy_d(vectorOut);
     vsip_valldestroy_d(vectorIn);
     vsip_fft_destroy_d(fftplan);
  }
  }vsip_finalize((void*)0);return 0;
}
