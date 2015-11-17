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
/* $Id: rcfftmEx.c,v 2.0 2003/02/22 15:46:22 judd Exp $ */

#include<stdio.h>
#include<vsip.h>

#define L      54
#define beta    3.5
#define ripple 60.0

int main(){vsip_init((void*)0);
{
    void VU_cmprint_d(vsip_cmview_d*);
    void VU_mprint_d(vsip_mview_d*);
    vsip_mview_d *w = vsip_mcreate_d(4,L,VSIP_ROW,0);
    vsip_cmview_d *W = vsip_cmcreate_d(4,L/2 + 1,VSIP_ROW,0);
    vsip_vview_d *blackman = vsip_vcreate_blackman_d(L,0),
                 *hanning  = vsip_vcreate_hanning_d(L,0),
                 *kaiser   = vsip_vcreate_kaiser_d(L,beta,0),
                 *cheby    = vsip_vcreate_cheby_d(L,ripple,0);
    vsip_fftm_d *fft = vsip_rcfftmop_create_d(4,L,1,VSIP_ROW,0,0);
    vsip_fftm_d *ifft = vsip_crfftmop_create_d(4,L,1.0/L,VSIP_ROW,0,0);
    /*printf("  blackman ");
    printf("     hanning      kaiser       chebyshev\n");
    for(i=0; i < L; i++)
       printf("%11.8f; %11.8f; %11.8f; %11.8f\n", 
              vsip_vget_d(blackman,i),
              vsip_vget_d(hanning,i),
              vsip_vget_d(kaiser,i),
              vsip_vget_d(cheby,i)); */
    {
       vsip_vview_d *v  = vsip_mrowview_d(w,0);
       vsip_offset o = (vsip_offset)vsip_mgetcolstride_d(w);
       vsip_vcopy_d_d(blackman,v);
       vsip_vputoffset_d(v,vsip_vgetoffset_d(v) + o);
       vsip_vcopy_d_d(hanning,v);
       vsip_vputoffset_d(v,vsip_vgetoffset_d(v) + o);
       vsip_vcopy_d_d(kaiser,v);
       vsip_vputoffset_d(v,vsip_vgetoffset_d(v) + o);
       vsip_vcopy_d_d(cheby,v);
       vsip_vdestroy_d(v);
    }
    printf(" w = ");VU_mprint_d(w);
    vsip_rcfftmop_d(fft,w,W);
    printf(" W = ");VU_cmprint_d(W);
    vsip_crfftmop_d(ifft,W,w);
    printf(" inverse W = ");VU_mprint_d(w);
    vsip_fftm_destroy_d(fft); 
    vsip_fftm_destroy_d(ifft); 
    vsip_valldestroy_d(blackman);
    vsip_valldestroy_d(hanning); 
    vsip_valldestroy_d(kaiser); 
    vsip_valldestroy_d(cheby);  
    vsip_malldestroy_d(w); 
    vsip_cmalldestroy_d(W); 
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
void VU_mprint_d(vsip_mview_d *X)
{
    vsip_length RL = vsip_mgetrowlength_d(X);  
    vsip_length CL = vsip_mgetcollength_d(X);  
    vsip_length i,j;
    vsip_scalar_d x;
    printf("[\n");
    for(j=0; j<RL; j++){
      for(i=0; i<CL; i++){
        x=vsip_mget_d(X,i,j);
        printf("%6.4f %s", x, ((i==(CL-1)) ? ";" : " "));
      }
      printf("\n");
    }
    printf("];\n");
    return;
}
