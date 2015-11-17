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
/* $Id: example21.c,v 2.0 2003/02/22 15:27:39 judd Exp $ */

#include <vsip.h>

#define D 1.5      /* sensor spacing meters */
#define Fs 1000    /* sample rate Hz */
#define F0 450     /* some frequencys for a target */
#define F1 300
#define F2 150
#define F3 50
#define Theta_o 40 /* beam number of narrow band tones */
#define Ns 512     /* samples in a time series */
#define Nn 1024    /* sample in a noise series */
#define Mp 128     /* hydrophones in linear arary */
#define c 1500     /* propagation speed */
#define Nnoise 64  /* number of noise directions */
#define kaiser 9 /* window parameter */
#define Nfilter 10 /* kernel length for noise filter */

void VU_mprintgram_f(vsip_mview_f*,char*);

int main(){vsip_init((void*)0);
{  int i,j; /* counters */
   vsip_vview_f *windowt = vsip_vcreate_hanning_f(Ns,0);
   vsip_vview_f *windowp = vsip_vcreate_hanning_f(Mp,0);
   vsip_vview_f *kernel = 
         vsip_vcreate_kaiser_f(Nfilter,kaiser,0);
   vsip_fir_f *fir = vsip_fir_create_f(kernel,
                         VSIP_NONSYM,2 * Nn,2,VSIP_STATE_SAVE,0,0);
   vsip_vview_f *t =vsip_vcreate_f(Ns,0); /*time vector*/
   vsip_vview_f *noise[Nnoise];
   vsip_vview_f *nv = vsip_vcreate_f(2 * Nn,0);
   vsip_vview_f *tt = vsip_vcreate_f(Ns,0); 
   vsip_mview_f *data = vsip_mcreate_f(Mp,Ns,VSIP_ROW,0),
                *rmview;
   vsip_vview_f *data_v, *gram_v;
   vsip_cvview_f *gram_data_v;
   vsip_cmview_f *gram_data = 
        vsip_cmcreate_f(Mp,Ns/2 + 1,VSIP_COL,0);
   vsip_mview_f  *gram = 
         vsip_mcreate_f(Mp,Ns/2 + 1,VSIP_ROW,0);
   vsip_mview_f  *Xim = 
         vsip_mcreate_f(Mp,Mp+1,VSIP_ROW,0);
   vsip_scalar_f alpha = (D * Fs) / c;
vsip_vview_f *m = vsip_vcreate_f(Mp,0);
   vsip_vview_f *Xi = vsip_vcreate_f(Mp + 1,0);
   vsip_randstate *state =
          vsip_randcreate(15,1,1,VSIP_PRNG);
   vsip_scalar_f w0 = 2 * M_PI * F0/Fs;
   vsip_scalar_f w1 = 2 * M_PI * F1/Fs;
   vsip_scalar_f w2 = 2 * M_PI * F2/Fs;
   vsip_scalar_f w3 = 2 * M_PI * F3/Fs;
   vsip_scalar_f cnst1 = M_PI/Nnoise;  
   vsip_offset offset0 = (vsip_offset)(alpha * Mp + 1);
   vsip_fftm_f *rcfftmop_obj = /* time fft */
   vsip_rcfftmop_create_f(Mp,Ns,1,VSIP_ROW,0,0);
   vsip_fftm_f *ccfftmip_obj =
         vsip_ccfftmip_create_f(Mp,Ns/2 +
             1,VSIP_FFT_FWD,1,VSIP_COL,0,0);
   vsip_vramp_f(0,1,m);
   vsip_vramp_f(0,M_PI/Mp,Xi); 
   vsip_vcos_f(Xi,Xi);
   vsip_vouter_f(alpha,m,Xi,Xim);
   { vsip_vview_f *gram_v = vsip_mrowview_f(gram,0);
     vsip_vputlength_f(gram_v,Mp*(Ns/2 + 1));
     vsip_vfill_f(0,gram_v);
     vsip_vdestroy_f(gram_v);
   }
   for(j=0; j<Nnoise; j++){
      noise[j] = vsip_vcreate_f(Nn,0);
      vsip_vrandn_f(state,nv);
      vsip_firflt_f(fir,nv,noise[j]);
      vsip_svmul_f(12.0/(Nnoise),noise[j],noise[j]);
      vsip_vputlength_f(noise[j],Ns);
   }
   vsip_vramp_f(0,1.0,t); /* time vector */
for(i=0; i<Mp; i++){
      vsip_scalar_f Xim_val = vsip_mget_f(Xim,i,Theta_o);
      data_v = vsip_mrowview_f(data,i);
      vsip_vsmsa_f(t,w0,-w0 * Xim_val,tt);
      vsip_vcos_f(tt,data_v); /*F0 time series */
      vsip_vsmsa_f(t,w1,-w1 * Xim_val,tt);
      vsip_vcos_f(tt,tt); /*F1 time series */
      vsip_vadd_f(tt,data_v,data_v);
      vsip_vsmsa_f(t,w2,-w2 * Xim_val,tt);
      vsip_vcos_f(tt,tt); /*F2 time series */
      vsip_vadd_f(tt,data_v,data_v);
      vsip_vsmsa_f(t,w3,-w3 * Xim_val,tt);
      vsip_vcos_f(tt,tt); /*F3 time series */
      vsip_svmul_f(3.0,tt,tt); /* scale by 3.0 */
      vsip_vadd_f(tt,data_v,data_v);
      vsip_svmul_f(3,data_v,data_v);
      for(j=0; j<Nnoise; j++){ 
          /* simple time delay beam forming for noise */
         vsip_vputoffset_f(noise[j],offset0 + 
           (int)( i * alpha * cos(j * cnst1)));
         vsip_vadd_f(noise[j],data_v,data_v); 
      } 
      /* need to destroy before going on to next phone */
      vsip_vdestroy_f(data_v);
   }
   /* window the data and the array to reduce sidelobes */
   vsip_vmmul_f(windowt,data,VSIP_ROW,data);
   vsip_vmmul_f(windowp,data,VSIP_COL,data);

   /* do ffts */
   vsip_rcfftmop_f(rcfftmop_obj,data,gram_data);
   vsip_ccfftmip_f(ccfftmip_obj,gram_data);

   { /* scale gram to db, min 0 max 255 */
      vsip_index ind;
      gram_v = vsip_mrowview_f(gram,0);
      gram_data_v = vsip_cmcolview_f(gram_data,0);
      rmview = vsip_mrealview_f(gram_data);
      vsip_vputlength_f(gram_v,Mp*(Ns/2 + 1)); 
      vsip_cvputlength_f(gram_data_v,Mp*(Ns/2 + 1));
data_v = vsip_vrealview_f(gram_data_v);
      vsip_vcmagsq_f(gram_data_v,data_v);
      vsip_mcopy_f_f(rmview,gram);
      vsip_vdestroy_f(data_v);
      vsip_svadd_f(1.0 -
      vsip_vminval_f(gram_v,&ind),gram_v,gram_v);
      vsip_vlog10_f(gram_v,gram_v); 
      vsip_svmul_f(256.0 / vsip_vmaxval_f(gram_v,&ind),
                    gram_v,gram_v);/* scale */
      /* reorganize the data to place zero in the 
          center for direction space */
      data_v = vsip_vcloneview_f(gram_v);
      vsip_vputlength_f(data_v,(Mp/2) * (Ns/2 + 1));
      vsip_vputoffset_f(data_v,(Mp/2) * (Ns/2 + 1));
      vsip_vputlength_f(gram_v,(Mp/2) * (Ns/2 + 1));
      vsip_vswap_f(data_v,gram_v);
      vsip_vdestroy_f(gram_v);
      vsip_vdestroy_f(data_v);
      vsip_cvdestroy_f(gram_data_v);
      vsip_mdestroy_f(rmview);
   }
   VU_mprintgram_f(gram,"gram_output");
   } vsip_finalize((void*)0); return 0;        
}
void VU_mprintgram_f(vsip_mview_f* M,char* fname)
{   vsip_length RL = vsip_mgetrowlength_f(M);
    vsip_length CL = vsip_mgetcollength_f(M);
    FILE *of = fopen(fname,"w");
    vsip_length row,col;
    for(row = 0; row<CL; row++)
       for(col=0; col<RL; col++)
         fprintf(of,"%ld %ld %3.0f\n",
            row,col,vsip_mget_f(M,row,col));
    fclose(of);
    return;
}
