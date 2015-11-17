/* Created RJudd */
/* SPAWARSYSCEN D857 */
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
/* $Id: ccfftip_d.h,v 2.1 2007/04/18 17:05:50 judd Exp $ */

static void ccfftip_d()
{  
   printf("******\nTEST ccfftip forward\n");
   {
      vsip_length MAX_POINTS=24;
      vsip_length np[]={8,16,22,24},npm,n2;
      int i;
      vsip_scalar_d enp,t;
      vsip_cvview_d *x = vsip_cvcreate_d(MAX_POINTS,VSIP_MEM_NONE);
      vsip_vview_d  *xr = vsip_vrealview_d(x);
      vsip_vview_d  *xi = vsip_vimagview_d(x);
      vsip_cvview_d  *cramp = vsip_cvcreate_d(MAX_POINTS,VSIP_MEM_NONE);
      vsip_vview_d  *ramp_r = vsip_vrealview_d(cramp);
      vsip_vview_d  *ramp_i = vsip_vimagview_d(cramp);
      vsip_cvview_d  *chk = vsip_cvcreate_d(MAX_POINTS,VSIP_MEM_NONE);
      vsip_vview_d  *chk_r = vsip_vrealview_d(chk);
      vsip_cvview_d *xc = vsip_cvcloneview_d(x);
      vsip_cvview_d *xn = vsip_cvcloneview_d(x);
      vsip_vview_d  *xnr = vsip_vrealview_d(x);
      vsip_vview_d  *xni = vsip_vimagview_d(x);
      vsip_cvputstride_d(xc,-1);
      vsip_vputoffset_d(xnr,1);
      vsip_vputoffset_d(xni,1);
      vsip_cvputoffset_d(xn,1);
      vsip_vramp_d(0,1,ramp_r);
      vsip_vfill_d(0,ramp_i);
      
      for(i=0; i<4; i++){
        printf("vsip_fft_d *fft = vsip_ccfftip_create_d(np,1.0,VSIP_FFT_FWD,0,VSIP_ALG_SPACE)\n");
        printf("np = %4d\n",np[i]);
        enp = np[i]; npm = np[i] / 2 - 1; t = M_PI / enp;
        vsip_cvputlength_d(x,np[i]);
        vsip_cvputlength_d(xc,npm); vsip_cvputoffset_d(xc,np[i]-1);
        vsip_cvputlength_d(xn,npm);
        vsip_vputlength_d(xnr,npm);
        vsip_vputlength_d(xni,npm);
        vsip_cvput_d(x,0,vsip_cmplx_d((enp -1.0)/2.0,0));
        n2 = np[i] / 2; vsip_cvput_d(x,n2,vsip_cmplx_d(-0.5,0));
        vsip_vramp_d(t,t,xni);
        vsip_vcos_d(xni,xnr);
        vsip_vsin_d(xni,xni);
        vsip_vdiv_d(xnr,xni,xni);
        vsip_svmul_d(-0.5,xni,xni);
        vsip_vfill_d(-0.5,xnr);
        vsip_cvconj_d(xn,xc);
        { /* do fft */
          {
          vsip_fft_d *fft = vsip_ccfftip_create_d(np[i],1.0,VSIP_FFT_FWD,0,VSIP_ALG_SPACE);
          printf("x = ");VU_cvprintm_d("8.6",x);
          vsip_ccfftip_d(fft,x);
          printf("vsip_ccfftip_d(fft,x)\n");
          printf("x = ");VU_cvprintm_d("8.6",x);
          vsip_fft_destroy_d(fft); 
          }
        }
        vsip_cvputlength_d(cramp,np[i]); 
        vsip_cvputlength_d(chk,np[i]);vsip_vputlength_d(chk_r,np[i]);
        printf("expected\n");VU_cvprintm_d("7.4",cramp);
        vsip_cvsub_d(x,cramp,chk); vsip_cvmag_d(chk,chk_r);
        vsip_vclip_d(chk_r,.001,.001,0,1,chk_r);
        if(vsip_vsumval_d(chk_r) > .5)
            printf("error\n");
        else
            printf("correct\n");
     }
     vsip_vdestroy_d(xnr);
     vsip_vdestroy_d(xni);
     vsip_cvdestroy_d(xn);
     vsip_cvdestroy_d(xc);
     vsip_vdestroy_d(xr);
     vsip_vdestroy_d(xi);
     vsip_vdestroy_d(chk_r);
     vsip_cvalldestroy_d(chk);
     vsip_vdestroy_d(ramp_r);
     vsip_vdestroy_d(ramp_i);
     vsip_cvalldestroy_d(cramp);
     vsip_cvalldestroy_d(x);
  }
  return;
}
