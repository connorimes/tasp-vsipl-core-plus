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
/* $Id: fftmipEx.c,v 2.0 2003/02/22 15:46:22 judd Exp $ */

#include<stdio.h>
#include<vsip.h>

#define L      24
#define beta    3.5
#define ripple 60.0

int main(){vsip_init((void*)0);
{
    void VU_cmprint_d(vsip_cmview_d*);
 /*   int i;*/
    vsip_cmview_d *w = vsip_cmcreate_d(4,L,VSIP_ROW,0);
    vsip_cmview_d *W = vsip_cmcreate_d(4,L,VSIP_ROW,0);
    vsip_cmview_d *IW = vsip_cmcreate_d(4,L,VSIP_ROW,0);
    vsip_vview_d *blackman = vsip_vcreate_blackman_d(L,0),
                 *hanning  = vsip_vcreate_hanning_d(L,0),
                 *kaiser   = vsip_vcreate_kaiser_d(L,beta,0),
                 *cheby    = vsip_vcreate_cheby_d(L,ripple,0);
    vsip_fftm_d *fft = vsip_ccfftmip_create_d(4,L,1,VSIP_FFT_FWD,VSIP_ROW,0,0);
    vsip_fftm_d *ifft = vsip_ccfftmip_create_d(4, L, 1.0/L, VSIP_FFT_INV, VSIP_ROW,0,0);
    /*printf("  blackman ");
    printf("     hanning      kaiser       chebyshev\n");
    for(i=0; i < L; i++)
       printf("%11.8f; %11.8f; %11.8f; %11.8f\n", 
              vsip_vget_d(blackman,i),
              vsip_vget_d(hanning,i),
              vsip_vget_d(kaiser,i),
              vsip_vget_d(cheby,i)); */
    {
       vsip_mview_d *wR = vsip_mrealview_d(w);
       vsip_mview_d *wI = vsip_mimagview_d(w);
       vsip_vview_d *v  = vsip_mrowview_d(wR,0);
       vsip_vview_d *vi  = vsip_mrowview_d(wI,0);
       vsip_offset o = (vsip_offset)vsip_mgetcolstride_d(wR);
       vsip_offset oi = (vsip_offset)vsip_mgetcolstride_d(wI);
       vsip_vcopy_d_d(blackman,v);
       vsip_vfill_d(0,vi);
       vsip_vputoffset_d(v,vsip_vgetoffset_d(v) + o);
       vsip_vputoffset_d(vi,vsip_vgetoffset_d(vi) + oi);
       vsip_vcopy_d_d(hanning,v);
       vsip_vfill_d(0,vi);
       vsip_vputoffset_d(v,vsip_vgetoffset_d(v) + o);
       vsip_vputoffset_d(vi,vsip_vgetoffset_d(vi) + oi);
       vsip_vcopy_d_d(kaiser,v);
       vsip_vfill_d(0,vi);
       vsip_vputoffset_d(v,vsip_vgetoffset_d(v) + o);
       vsip_vputoffset_d(vi,vsip_vgetoffset_d(vi) + oi);
       vsip_vcopy_d_d(cheby,v);
       vsip_vfill_d(0,vi);
       vsip_mdestroy_d(wR);
       vsip_vdestroy_d(v);
       vsip_mdestroy_d(wI);
       vsip_vdestroy_d(vi);
    }
    vsip_cmcopy_d_d(w,W);
    vsip_ccfftmip_d(fft,W);
    vsip_cmcopy_d_d(W,IW);
    vsip_ccfftmip_d(ifft,IW);
    printf(" w = ");VU_cmprint_d(w);
    printf(" W = ");VU_cmprint_d(W);
    printf("IW = ");VU_cmprint_d(IW);
    vsip_fftm_destroy_d(fft); 
    vsip_fftm_destroy_d(ifft); 
    vsip_valldestroy_d(blackman);
    vsip_valldestroy_d(hanning); 
    vsip_valldestroy_d(kaiser); 
    vsip_valldestroy_d(cheby);  
    vsip_cmalldestroy_d(w); 
    vsip_cmalldestroy_d(W); 
    vsip_cmalldestroy_d(IW); 
    }vsip_finalize((void*)0);return 0;
}
void VU_cmprint_d(vsip_cmview_d *X)
{
    vsip_length RL = vsip_cmgetrowlength_d(X);  
    vsip_length CL = vsip_cmgetcollength_d(X);  
    vsip_length i,j;
    vsip_cscalar_d x;
    printf("[\n");
    for(j=0; j<RL; j++){
      for(i=0; i<CL; i++){
        x=vsip_cmget_d(X,i,j);
        printf("(%6.4f%+6.4fi%s",vsip_real_d(x),vsip_imag_d(x),((i==(CL-1)) ? ");" : ")"));
      }
      printf("\n");
    }
    printf("];\n");
    return;
}
