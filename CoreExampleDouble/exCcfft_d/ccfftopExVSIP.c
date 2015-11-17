/* Created by RJudd August 27, 1998*/
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
/* $Id: ccfftopExVSIP.c,v 2.0 2003/02/22 15:46:13 judd Exp $ */

#include<vsip.h>
#include<VU.h>

#define VU_PI 3.141592653589793
#define F  .15
#define LL 24
#define LP 32
#define delta .0000000001

int main (int argc,char *argv[]){ vsip_init((void*)0);
{
vsip_length L = LL;
vsip_length Lp;
if(argc != 1) L = (vsip_length) atoi(argv[1]);
Lp = (LP > L) ? L : LP;
{
  int i;
  vsip_cvview_d* vector = vsip_cvcreate_d(L,0);
  vsip_cvview_d* vectorOUT = vsip_cvcreate_d(L,0);
  vsip_vview_d* realIn = vsip_vrealview_d(vector);
  vsip_vview_d* imagIn = vsip_vimagview_d(vector);
  vsip_fft_d* fftplan = vsip_ccfftop_create_d(L,1,-1,0,0);
  vsip_fft_d* fftplanI = vsip_ccfftop_create_d(L,(double)1/L,1,0,0);
  char printDataOne[LP][20],
       printDataTwo[LP][30];

  { int k; for(k=0; k<1; k++){
  /* put some data in realIn*/
  vsip_vramp_d(0, 2 * VU_PI * F, realIn);
  vsip_vcos_d(realIn,realIn);
  /* print realIn */
  for(i=0; i<Lp; i++){ 
       sprintf(printDataOne[i],"%2d input -> %7.4f",i, vsip_vget_d(realIn,i)+delta);
  }
  /*make sure imagIn is full of zeros*/
  vsip_vfill_d(0,imagIn);
  /*find the fft*/
  {
    double atime = VU_ansi_c_clock();
    vsip_ccfftop_d(fftplan,vector,vectorOUT);
    atime = VU_ansi_c_clock() - atime;
    printf("%6.2f sec\n",atime);
  }
  for(i=0; i<Lp; i++){
     sprintf(printDataTwo[i]," fft -> (%7.3f, %7.3f)",
           vsip_real_d(vsip_cvget_d(vectorOUT,i))+delta,
           vsip_imag_d(vsip_cvget_d(vectorOUT,i))+delta);
  }
  /*invert the fft*/
  vsip_ccfftop_d(fftplanI,vectorOUT,vector); 
  /*print it */
  for(i=0; i<Lp; i++){
     printf("%s %s  ifft -> (%7.3f, %7.3f)\n",
           printDataOne[i],
           printDataTwo[i],
           vsip_real_d(vsip_cvget_d(vector,i))+delta,
           vsip_imag_d(vsip_cvget_d(vector,i))+delta);
  }
  }} 
  {
     vsip_vdestroy_d((void*)imagIn);
     vsip_vdestroy_d((void*)realIn);
     vsip_cblockdestroy_d(vsip_cvdestroy_d((void*)vector));
     vsip_fft_destroy_d((void*)fftplan); 
     vsip_fft_destroy_d((void*)fftplanI);
  }
  } vsip_finalize((void*)0); return 0;
}
}
