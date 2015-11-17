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
/* $Id: fftmipEx.c,v 2.0 2003/02/22 15:41:03 judd Exp $ */

#include<stdio.h>
#include<vsip.h>

#define L      24
#define beta    3.5
#define ripple 60.0

int main(){vsip_init((void*)0);
{
    void VU_cmprint_f(vsip_cmview_f*);
 /*   int i;*/
    vsip_cmview_f *w = vsip_cmcreate_f(4,L,VSIP_ROW,0);
    vsip_cmview_f *W = vsip_cmcreate_f(4,L,VSIP_ROW,0);
    vsip_cmview_f *IW = vsip_cmcreate_f(4,L,VSIP_ROW,0);
    vsip_vview_f *blackman = vsip_vcreate_blackman_f(L,0),
                 *hanning  = vsip_vcreate_hanning_f(L,0),
                 *kaiser   = vsip_vcreate_kaiser_f(L,beta,0),
                 *cheby    = vsip_vcreate_cheby_f(L,ripple,0);
    vsip_fftm_f *fft = vsip_ccfftmip_create_f(4,L,1,VSIP_FFT_FWD,VSIP_ROW,0,0);
    vsip_fftm_f *ifft = vsip_ccfftmip_create_f(4, L, 1.0/L, VSIP_FFT_INV, VSIP_ROW,0,0);
    /*printf("  blackman ");
    printf("     hanning      kaiser       chebyshev\n");
    for(i=0; i < L; i++)
       printf("%11.8f; %11.8f; %11.8f; %11.8f\n", 
              vsip_vget_f(blackman,i),
              vsip_vget_f(hanning,i),
              vsip_vget_f(kaiser,i),
              vsip_vget_f(cheby,i)); */
    {
       vsip_mview_f *wR = vsip_mrealview_f(w);
       vsip_mview_f *wI = vsip_mimagview_f(w);
       vsip_vview_f *v  = vsip_mrowview_f(wR,0);
       vsip_vview_f *vi  = vsip_mrowview_f(wI,0);
       vsip_offset o = (vsip_offset)vsip_mgetcolstride_f(wR);
       vsip_offset oi = (vsip_offset)vsip_mgetcolstride_f(wI);
       vsip_vcopy_f_f(blackman,v);
       vsip_vfill_f(0,vi);
       vsip_vputoffset_f(v,vsip_vgetoffset_f(v) + o);
       vsip_vputoffset_f(vi,vsip_vgetoffset_f(vi) + oi);
       vsip_vcopy_f_f(hanning,v);
       vsip_vfill_f(0,vi);
       vsip_vputoffset_f(v,vsip_vgetoffset_f(v) + o);
       vsip_vputoffset_f(vi,vsip_vgetoffset_f(vi) + oi);
       vsip_vcopy_f_f(kaiser,v);
       vsip_vfill_f(0,vi);
       vsip_vputoffset_f(v,vsip_vgetoffset_f(v) + o);
       vsip_vputoffset_f(vi,vsip_vgetoffset_f(vi) + oi);
       vsip_vcopy_f_f(cheby,v);
       vsip_vfill_f(0,vi);
       vsip_mdestroy_f(wR);
       vsip_vdestroy_f(v);
       vsip_mdestroy_f(wI);
       vsip_vdestroy_f(vi);
    }
    vsip_cmcopy_f_f(w,W);
    vsip_ccfftmip_f(fft,W);
    vsip_cmcopy_f_f(W,IW);
    vsip_ccfftmip_f(ifft,IW);
    printf(" w = ");VU_cmprint_f(w);
    printf(" W = ");VU_cmprint_f(W);
    printf("IW = ");VU_cmprint_f(IW);
    {/* test vsip_fftm_getattr_f */
        vsip_fftm_attr_f attr;
        vsip_fftm_getattr_f(fft, &attr);
        printf("%lu %lu %lu %lu %d %f %d %d\n",
        vsip_rowindex(attr.input),
        vsip_colindex(attr.input),
        vsip_rowindex(attr.output),
        vsip_colindex(attr.output),
        attr.place,attr.scale,attr.dir,attr.major);
        vsip_fftm_getattr_f(ifft, &attr);
        printf("%lu %lu %lu %lu %d %f %d %d\n",
        vsip_rowindex(attr.input),
        vsip_colindex(attr.input),
        vsip_rowindex(attr.output),
        vsip_colindex(attr.output),
        attr.place,attr.scale,attr.dir,attr.major);
    }
    vsip_fftm_destroy_f(fft); 
    vsip_fftm_destroy_f(ifft); 
    vsip_valldestroy_f(blackman);
    vsip_valldestroy_f(hanning); 
    vsip_valldestroy_f(kaiser); 
    vsip_valldestroy_f(cheby);  
    vsip_cmalldestroy_f(w); 
    vsip_cmalldestroy_f(W); 
    vsip_cmalldestroy_f(IW); 
    } vsip_finalize((void*)0); return 0;
}
void VU_cmprint_f(vsip_cmview_f *X)
{
    vsip_length RL = vsip_cmgetrowlength_f(X);  
    vsip_length CL = vsip_cmgetcollength_f(X);  
    vsip_length i,j;
    vsip_cscalar_f x;
    printf("[\n");
    for(j=0; j<RL; j++){
      for(i=0; i<CL; i++){
        x=vsip_cmget_f(X,i,j);
        printf("(%6.4f%+6.4fi%s",vsip_real_f(x),vsip_imag_f(x),((i==(CL-1)) ? ");" : ")"));
      }
      printf("\n");
    }
    printf("];\n");
    return;
}
