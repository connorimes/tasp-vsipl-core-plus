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
/* $Id: ccfftipEx.c,v 2.0 2003/02/22 15:46:13 judd Exp $ */

#include<vsip.h>

#define VU_PI 3.141592653589793
#define F  .15
#define L  38

int main (){vsip_init((void*)0);
{
  int i;
  vsip_cvview_d* vector = vsip_cvcreate_d(L,0);
  vsip_vview_d* realIn = vsip_vrealview_d(vector);
  vsip_vview_d* imagIn = vsip_vimagview_d(vector);
  vsip_fft_d* fftplan = vsip_ccfftip_create_d(L,1,-1,0,0);
  vsip_fft_d* fftplanI = vsip_ccfftip_create_d(L,(double)1/L,1,0,0);
  char printDataOne[L][20],
       printDataTwo[L][30];

  /* put some data in realIn*/
  vsip_vramp_d(0, 2 * VU_PI * F, realIn);
  vsip_vcos_d(realIn,realIn);
  /* print realIn */
  for(i=0; i<L; i++){ 
       sprintf(printDataOne[i],"%2d input -> %7.4f",i, vsip_vget_d(realIn,i));
  }
  /*make sure imagIn is full of zeros*/
  vsip_vfill_d(0,imagIn);

  /*find the fft*/
  vsip_ccfftip_d(fftplan,vector);
  for(i=0; i<L; i++){
     sprintf(printDataTwo[i]," fft -> (%7.3f, %7.3f)",
           vsip_real_d(vsip_cvget_d(vector,i)),
           vsip_imag_d(vsip_cvget_d(vector,i)));
  }
  /*invert the fft*/
  vsip_ccfftip_d(fftplanI,vector);
  /*print it */
  for(i=0; i<L; i++){
     printf("%s %s  ifft -> (%7.3f, %7.3f)\n",
           printDataOne[i],
           printDataTwo[i],
           vsip_real_d(vsip_cvget_d(vector,i)),
           vsip_imag_d(vsip_cvget_d(vector,i)));
  }
 
  {
     vsip_vdestroy_d((void*)imagIn);
     vsip_vdestroy_d((void*)realIn);
     vsip_cblockdestroy_d(vsip_cvdestroy_d((void*)vector));
     vsip_fft_destroy_d((void*)fftplan);
     vsip_fft_destroy_d((void*)fftplanI);
  }
  } vsip_finalize((void*)0);return 0;
}
