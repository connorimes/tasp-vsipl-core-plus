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
/* $Id: ffttest.c,v 2.0 2003/02/22 15:41:04 judd Exp $ */

#include<math.h>
#include<stdio.h>
#include<time.h>
#include<vsip.h>
#include<VU.h>
#define MAX_POINTS 2097152

int main()
{   
   int i = vsip_init((void*)0);
   vsip_length np,np0,npm,n2;
   vsip_index index;
   vsip_scalar_f enp,t,pi,err;
   double time0,time1, time2;
   vsip_cvview_f *x = vsip_cvcreate_f(MAX_POINTS,0);
   vsip_vview_f  *xr = vsip_vrealview_f(x);
   vsip_vview_f  *xi = vsip_vimagview_f(x);
   vsip_vview_f  *ramp = vsip_vcreate_f(MAX_POINTS,0);
   vsip_vview_f  *error = vsip_vcreate_f(MAX_POINTS,0);
   vsip_cvview_f *xc = vsip_cvcloneview_f(x);
   vsip_cvview_f *xn = vsip_cvcloneview_f(x);
   vsip_vview_f  *xnr = vsip_vrealview_f(x);
   vsip_vview_f  *xni = vsip_vimagview_f(x);
   vsip_cvputstride_f(xc,-1);
   vsip_vputoffset_f(xnr,1);
   vsip_vputoffset_f(xni,1);
   vsip_cvputoffset_f(xn,1);
   vsip_vramp_f(0,1,ramp);
   pi = M_PI;
   np = 8;
   np0 = 8;
   while(np <= MAX_POINTS){
     printf("\nnp = %7ld\n",np);
     enp = np; npm = np / 2 - 1; t = pi / enp;
     vsip_cvputlength_f(x,np);
     vsip_cvputlength_f(xc,npm); vsip_cvputoffset_f(xc,np-1);
     vsip_cvputlength_f(xn,npm);
     vsip_vputlength_f(xnr,npm);
     vsip_vputlength_f(xni,npm);
     vsip_cvput_f(x,0,vsip_cmplx_f((enp -1.0)/2.0,0));
     n2 = np / 2; vsip_cvput_f(x,n2,vsip_cmplx_f(-0.5,0));
     vsip_vramp_f(t,t,xni);
     vsip_vcos_f(xni,xnr);
     vsip_vsin_f(xni,xni);
     vsip_vdiv_f(xnr,xni,xni);
     vsip_svmul_f(-0.5,xni,xni);
     vsip_vfill_f(-0.5,xnr);
     vsip_cvconj_f(xn,xc);
     { /* do fft */
       {
         vsip_fft_f *fft = vsip_ccfftip_create_f(np,1.0,VSIP_FFT_FWD,0,VSIP_ALG_SPACE);
         vsip_fft_f *ifft = vsip_ccfftip_create_f(np,1.0/np,VSIP_FFT_INV,0,VSIP_ALG_SPACE);
         time0 = 0; time1 = 0; time2 = 0;
         for(i=0; i<10; i++){
            time0 = VU_ansi_c_clock();
            vsip_ccfftip_f(fft,x);
            time1 += (VU_ansi_c_clock() - time0);
            time0 = VU_ansi_c_clock();
            vsip_ccfftip_f(ifft,x);
            time2 += (VU_ansi_c_clock() - time0);
         }
         vsip_ccfftip_f(fft,x);
         vsip_fft_destroy_f(fft); 
         vsip_fft_destroy_f(ifft); 
       }
     }
     printf("fwd %7.4f sec   inv %7.4f sec\n", time1/(double)10, time2/(double)10);
     vsip_vputlength_f(xr,np); vsip_vputlength_f(xi,np);
     vsip_vputlength_f(ramp,np); vsip_vputlength_f(error,np);
     vsip_vsub_f(xr,ramp,error);
     err = vsip_vmaxmgval_f(error,&index);
     printf("max error = %e, %ld, (%e %+ei)\n",err,index,
             vsip_real_f(vsip_cvget_f(x,index)),
             vsip_imag_f(vsip_cvget_f(x,index)));
     printf("means square error = %e\n",vsip_vmeansqval_f(error));
     printf("means square imag = %e\n",vsip_vmeansqval_f(xi));
     vsip_cvputlength_f(x,np0);VU_cvprintm_f("14.6",x);
     np *= 2;
  }
  vsip_vdestroy_f(xnr);
  vsip_vdestroy_f(xni);
  vsip_cvdestroy_f(xn);
  vsip_cvdestroy_f(xc);
  vsip_vdestroy_f(xr);
  vsip_vdestroy_f(xi);
  vsip_valldestroy_f(error);
  vsip_valldestroy_f(ramp);
  vsip_cvalldestroy_f(x);
  vsip_finalize((void*)0); return 1;
}
