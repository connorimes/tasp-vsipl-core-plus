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
/* $Id: ccfftopEx.c,v 2.0 2003/02/22 15:46:13 judd Exp $ */

#include<vsip.h>

#define PI 3.141592653589793
#define F  .15
#define L  38

int main (){ vsip_init((void*)0); 
{
  int i;
  vsip_cblock_d* blockOut = vsip_cblockcreate_d(2 * L, 0);
  vsip_cvview_d* vectorOut = vsip_cvbind_d(blockOut,0,2,L);
  vsip_cvview_d* vectorIn = vsip_cvcreate_d(L,0);
  vsip_vview_d* realIn = vsip_vrealview_d(vectorIn);
  vsip_vview_d* imagIn = vsip_vimagview_d(vectorIn);
  vsip_fft_d* fftplan = vsip_ccfftop_create_d(L,1,-1,0,0);
  vsip_fft_d* fftplanI = vsip_ccfftop_create_d(L,(double)1/L,1,0,0);
  char inputdata[L][20];

  /* put some data in realIn*/
  vsip_vramp_d(0, 2 * PI * F, realIn);
  vsip_vcos_d(realIn,realIn);
  /* print realIn */
  for(i=0; i<L; i++)
       sprintf(inputdata[i],"%2d input-> %7.3f",i, vsip_vget_d(realIn,i));
  /*make sure imagIn is full of zeros*/
  vsip_vfill_d(0,imagIn);

  /*find the fft*/
  vsip_ccfftop_d(fftplan,vectorIn,vectorOut);
  /*invert the fft*/
  vsip_ccfftop_d(fftplanI,vectorOut,vectorIn);
  /*print it */
  for(i=0; i<L; i++)
     printf("%s   fft -> (%7.3f, %7.3f)   ifft -> (%7.3f, %7.3f)\n",
           inputdata[i],
           vsip_real_d(vsip_cvget_d(vectorOut,i)),
           vsip_imag_d(vsip_cvget_d(vectorOut,i)),
           vsip_real_d(vsip_cvget_d(vectorIn,i)),
           vsip_imag_d(vsip_cvget_d(vectorIn,i)));
  {
     vsip_vdestroy_d(imagIn);
     vsip_vdestroy_d(realIn);
     vsip_cblockdestroy_d(vsip_cvdestroy_d(vectorIn));
     vsip_cblockdestroy_d(vsip_cvdestroy_d(vectorOut));
     vsip_fft_destroy_d(fftplan);
     vsip_fft_destroy_d(fftplanI);
  }
  } vsip_finalize((void*)0);return 0;
}
