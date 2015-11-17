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
/* $Id: komegaEx.c,v 2.1 2004/05/16 05:00:57 judd Exp $ */

#include <stdio.h>
#include <vsip.h>
#include <VUX.h>
#define D 1.5    /* hydrophone spacing meters */
#define Fs 1000  /* sample rate Hz */
#define F0 450   /* some frequencys for a target */
#define F1 300
#define F2 150
#define F3 10
#define Ns 512    /* samples in a time series */
#define Nn 1024   /* sample in a noise series */
#define Mp 128    /* hydrophones in linear arary */
#define c 1500    /* sound speed */
#define Nnoise 64
#define kaiser 9
#define Nfilter 20

int main(){vsip_init((void*)0);
{
   int k,i,j;
   vsip_vview_f *windowt = vsip_vcreate_hanning_f(Ns,0);
   vsip_vview_f *windowp = vsip_vcreate_hanning_f(Mp,0);
   vsip_vview_f *kernel = vsip_vcreate_kaiser_f(Nfilter,kaiser,0);
   vsip_fir_f *fir = vsip_fir_create_f(kernel,VSIP_NONSYM,2 * Nn,2,
                        VSIP_STATE_SAVE,0,0);
   vsip_vview_f *t = vsip_vcreate_f(Ns,0); /* time vector */
   vsip_vview_f *noise[Nnoise];
   vsip_vview_f *nv = vsip_vcreate_f(2 * Nn,0);
   vsip_vview_f *tt = vsip_vcreate_f(Ns,0); /* scratch vector */
   vsip_mview_f *data = vsip_mcreate_f(Mp,Ns,VSIP_ROW,0),
                *rmview;
   vsip_vview_f *data_v,
                *gram_v;
   vsip_cvview_f *gram_data_v;
   vsip_cmview_f *gram_data = vsip_cmcreate_f(Mp,Ns/2 + 1,VSIP_COL,0);
   vsip_mview_f *gram = vsip_mcreate_f(Mp,Ns/2 + 1,VSIP_ROW,0);
   vsip_mview_f *Xim = vsip_mcreate_f(Mp,Mp+1,VSIP_ROW,0);
   vsip_vview_f *m = vsip_vcreate_f(Mp,0);
   vsip_vview_f *Xi = vsip_vcreate_f(Mp + 1,0);
   vsip_randstate *state = vsip_randcreate(15,1,1,VSIP_PRNG);
   vsip_scalar_f w0 = 2 * M_PI * F0/Fs;
   vsip_scalar_f w1 = 2 * M_PI * F1/Fs;
   vsip_scalar_f w2 = 2 * M_PI * F2/Fs;
   vsip_scalar_f w3 = 2 * M_PI * F3/Fs;
   vsip_scalar_f cnst1 = M_PI/Nnoise;  /* Nnoise angle steps */
   vsip_scalar_f cnst2 = D * Fs / c; /* delta t between phones at endfire */
   vsip_offset offset0 = (vsip_offset)(cnst2 * Mp + 1);
   VUX_gram_f gram_obj;
   vsip_fftm_f *rcfftmop_obj = vsip_rcfftmop_create_f(Mp,Ns,1,VSIP_ROW,0,0);
   vsip_fftm_f *ccfftmip_obj = vsip_ccfftmip_create_f(Mp,Ns/2 + 1,VSIP_FFT_FWD,1,VSIP_COL,0,0);

   for(j=0; j<Nnoise; j++) noise[j] = vsip_vcreate_f(Nn,0);

   vsip_vramp_f(0,1,m);
   vsip_vramp_f(0,M_PI/Mp,Xi);
   vsip_vcos_f(Xi,Xi);
   vsip_vouter_f(cnst2,m,Xi,Xim);

   VUX_mgraminit_f(&gram_obj,
              Ns/2 + 1,Mp,
              Ns/2 + 101,Mp + 100,
              50,50);
   VUX_mgramaxis_f(
           &gram_obj,
           8,10,
           NULL,
           NULL); 
   
   VUX_mgramtitle_f(&gram_obj,.40,.10,"Frequency Wavenumber Plot");
   VUX_mgramxtitle_f(&gram_obj,.35,.90,"Frequency 0 - 500 Hz");
   VUX_mgramytitle_f(&gram_obj,.01,.15,"K cos(theta)");
   VUX_mgramopen_f(
           &gram_obj);
   { vsip_vview_f *gram_v = vsip_mrowview_f(gram,0);
     vsip_vputlength_f(gram_v,Mp*(Ns/2 + 1));
     vsip_vfill_f(0,gram_v);
     vsip_vdestroy_f(gram_v);
   }
   VUX_mgram_gsarray_f(&gram_obj,256);
   VUX_mgram_f(&gram_obj,gram);
   for(j=0; j<Nnoise; j++){ /* make some noise for Nnoise directions */
      vsip_vputoffset_f(noise[j],0); 
      vsip_vputlength_f(noise[j],Nn);
      vsip_vrandn_f(state,nv);
      vsip_firflt_f(fir,nv,noise[j]);
      vsip_vputlength_f(noise[j],Ns);
      vsip_svmul_f(1.0/(10 * Nnoise),noise[j],noise[j]);
   }
   for(k=0; k<=Mp; k+=4){ /* iterate through all the directions */
     vsip_scalar_f kn = k * Ns,
                   Xim_val;
     vsip_vramp_f(kn,1.0,t);
     for(i=0; i<Mp; i++){ /* fill each data vector for each phone */
         Xim_val = vsip_mget_f(Xim,i,k);
         data_v = vsip_mrowview_f(data,i);
         vsip_vsmsa_f(t,w0,-w0 * Xim_val,tt);
         vsip_vcos_f(tt,data_v);
         vsip_vsmsa_f(t,w1,-w1 * Xim_val,tt);
         vsip_vcos_f(tt,tt);
         vsip_vadd_f(tt,data_v,data_v);
         vsip_vsmsa_f(t,w2,-w2 * Xim_val,tt);
         vsip_vcos_f(tt,tt);
         vsip_vadd_f(tt,data_v,data_v);
         vsip_vsmsa_f(t,w3,-w3 * Xim_val,tt);
         vsip_vcos_f(tt,tt);
         vsip_svmul_f(2.0,tt,tt);
         vsip_vadd_f(tt,data_v,data_v);
         vsip_svmul_f(2,data_v,data_v);
         for(j=0; j<Nnoise; j++){ /* simple time delay beam forming for noise */
            vsip_vputoffset_f(noise[j],offset0 + (int)( i * cnst2 * cos(j * cnst1)));
            vsip_vadd_f(noise[j],data_v,data_v); 
         } 
         vsip_vdestroy_f(data_v);
     }
     { /* window the data and the array to reduce sidelobes */
       vsip_vmmul_f(windowt,data,VSIP_ROW,data);
       vsip_vmmul_f(windowp,data,VSIP_COL,data);
     }

     /* do ffts */
     vsip_rcfftmop_f(rcfftmop_obj,data,gram_data);
     vsip_ccfftmip_f(ccfftmip_obj,gram_data);

     { /* scale gram to db, min 0 max 255 */
        vsip_index ind;
        gram_v = vsip_mrowview_f(gram,0);
        gram_data_v = vsip_cmcolview_f(gram_data,0);
        rmview = vsip_mrealview_f(gram_data);
        vsip_vputlength_f(gram_v,Mp*(Ns/2 + 1)); /* vector viewing all of gram*/
        vsip_cvputlength_f(gram_data_v,Mp*(Ns/2 + 1)); /* vector viewing all of gram*/
        data_v = vsip_vrealview_f(gram_data_v);
        vsip_vcmagsq_f(gram_data_v,data_v);
        vsip_mcopy_f_f(rmview,gram);
        vsip_vdestroy_f(data_v);
        vsip_svadd_f(1.0 - vsip_vminval_f(gram_v,&ind),gram_v,gram_v); /* scale so min is 1 */
        vsip_vlog10_f(gram_v,gram_v); /* log10, min is now zero */
        vsip_svmul_f( 256.0 / vsip_vmaxval_f(gram_v,&ind), gram_v,gram_v);/* scale */
        /* reorganize the data to place zero in the center for direction space */
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
     VUX_mgramupdate_f(&gram_obj,gram);
     printf("beam %3d\n",k);
   }
   } vsip_finalize((void*)0); return 0;        
}
