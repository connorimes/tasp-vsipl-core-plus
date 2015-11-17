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
/* $Id: ffttest.c,v 2.0 2003/02/22 15:46:21 judd Exp $ */

#include<math.h>
#include<stdio.h>
#include<time.h>
#include<vsip.h>
#include<VU.h>
#define MAX_POINTS 2097152

int main(){vsip_init((void*)0);
{
   vsip_length np,np0,npm,n2;
   vsip_index index;
   vsip_scalar_d enp,t,pi,err;
   double time1, time2;
   vsip_cvview_d *x = vsip_cvcreate_d(MAX_POINTS,0);
   vsip_vview_d  *xr = vsip_vrealview_d(x);
   vsip_vview_d  *xi = vsip_vimagview_d(x);
   vsip_vview_d  *ramp = vsip_vcreate_d(MAX_POINTS,0);
   vsip_vview_d  *error = vsip_vcreate_d(MAX_POINTS,0);
   vsip_cvview_d *xc = vsip_cvcloneview_d(x);
   vsip_cvview_d *xn = vsip_cvcloneview_d(x);
   vsip_vview_d  *xnr = vsip_vrealview_d(x);
   vsip_vview_d  *xni = vsip_vimagview_d(x);
   vsip_cvputstride_d(xc,-1);
   vsip_vputoffset_d(xnr,1);
   vsip_vputoffset_d(xni,1);
   vsip_cvputoffset_d(xn,1);
   vsip_vramp_d(0,1,ramp);
   pi = M_PI;
   np = 8;
   np0 = 8;
   while(np <= MAX_POINTS){
     printf("\nnp = %7ld\n",np);
     enp = np; npm = np / 2 - 1; t = pi / enp;
     vsip_cvputlength_d(x,np);
     vsip_cvputlength_d(xc,npm); vsip_cvputoffset_d(xc,np-1);
     vsip_cvputlength_d(xn,npm);
     vsip_vputlength_d(xnr,npm);
     vsip_vputlength_d(xni,npm);
     vsip_cvput_d(x,0,vsip_cmplx_d((enp -1.0)/2.0,0));
     n2 = np / 2; vsip_cvput_d(x,n2,vsip_cmplx_d(-0.5,0));
     vsip_vramp_d(t,t,xni);
     vsip_vcos_d(xni,xnr);
     vsip_vsin_d(xni,xni);
     vsip_vdiv_d(xnr,xni,xni);
     vsip_svmul_d(-0.5,xni,xni);
     vsip_vfill_d(-0.5,xnr);
     vsip_cvconj_d(xn,xc);
     { /* do fft */
       {
       vsip_fft_d *fft = vsip_ccfftip_create_d(np,1.0,VSIP_FFT_FWD,0,0);
         time1 = VU_ansi_c_clock();
         vsip_ccfftip_d(fft,x);
         time2 = VU_ansi_c_clock();
       vsip_fft_destroy_d(fft); 
       }
     }
     printf("%5.2f sec   \n", (time2 - time1));
     vsip_vputlength_d(xr,np); vsip_vputlength_d(xi,np);
     vsip_vputlength_d(ramp,np); vsip_vputlength_d(error,np);
     vsip_vsub_d(xr,ramp,error);
     err = vsip_vmaxmgval_d(error,&index);
     printf("max error = %e, %ld, (%e %+ei)\n",err,index,
             vsip_real_d(vsip_cvget_d(x,index)),
             vsip_imag_d(vsip_cvget_d(x,index)));
     printf("means square error = %e\n",vsip_vmeansqval_d(error));
     printf("means square imag = %e\n",vsip_vmeansqval_d(xi));
     vsip_cvputlength_d(x,np0);VU_cvprintm_d("14.6",x);
     np *= 2;
  }
  vsip_vdestroy_d(xnr);
  vsip_vdestroy_d(xni);
  vsip_cvdestroy_d(xn);
  vsip_cvdestroy_d(xc);
  vsip_vdestroy_d(xr);
  vsip_vdestroy_d(xi);
  vsip_valldestroy_d(error);
  vsip_valldestroy_d(ramp);
  vsip_cvalldestroy_d(x);
  } vsip_finalize((void*)0); return 1;
}
