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
/* $Id: ccfftipEx.c,v 2.0 2003/02/22 15:15:37 judd Exp $ */

#include<vsip.h>

#define VU_PI 3.141592653589793
#define F  .15
#define L  38

int main () {vsip_init((void*)0);
{
  int i;
  vsip_cvview_f* vector = vsip_cvcreate_f(L,0);
  vsip_vview_f* realIn = vsip_vrealview_f(vector);
  vsip_vview_f* imagIn = vsip_vimagview_f(vector);
  vsip_fft_f* fftplan = vsip_ccfftip_create_f(L,1,-1,0,0);
  vsip_fft_f* fftplanI = vsip_ccfftip_create_f(L,(double)1/L,1,0,0);
  char printDataOne[L][20],
       printDataTwo[L][30];

  /* put some data in realIn*/
  vsip_vramp_f(0, 2 * VU_PI * F, realIn);
  vsip_vcos_f(realIn,realIn);
  /* print realIn */
  for(i=0; i<L; i++){ 
       sprintf(printDataOne[i],"%2d input -> %7.4f",i, vsip_vget_f(realIn,i));
  }
  /*make sure imagIn is full of zeros*/
  vsip_vfill_f(0,imagIn);

  /*find the fft*/
  vsip_ccfftip_f(fftplan,vector);
  for(i=0; i<L; i++){
     sprintf(printDataTwo[i]," fft -> (%7.3f, %7.3f)",
           vsip_real_f(vsip_cvget_f(vector,i)),
           vsip_imag_f(vsip_cvget_f(vector,i)));
  }
  /*invert the fft*/
  vsip_ccfftip_f(fftplanI,vector);
  /*print it */
  for(i=0; i<L; i++){
     printf("%s %s  ifft -> (%7.3f, %7.3f)\n",
           printDataOne[i],
           printDataTwo[i],
           vsip_real_f(vsip_cvget_f(vector,i)),
           vsip_imag_f(vsip_cvget_f(vector,i)));
  }
  {/* test vsip_fft_getattr_f */
      vsip_fft_attr_f attr;
      vsip_fft_getattr_f(fftplan, &attr);
      printf("%lu %lu %d %f %d\n",attr.input,attr.output,attr.place,attr.scale,attr.dir);
      vsip_fft_getattr_f(fftplanI, &attr);
      printf("%lu %lu %d %f %d\n",attr.input,attr.output,attr.place,attr.scale,attr.dir);
  }
  {
     vsip_vdestroy_f((void*)imagIn);
     vsip_vdestroy_f((void*)realIn);
     vsip_cblockdestroy_f(vsip_cvdestroy_f((void*)vector));
     vsip_fft_destroy_f((void*)fftplan);
     vsip_fft_destroy_f((void*)fftplanI);
  }
  } vsip_finalize((void*)0); return 0;
}
