/* Created By RJudd Janary 8, 1999 */
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
/* $Id: VI_ccfftip_create_d_def.h,v 2.2 2003/04/22 02:19:56 judd Exp $ */
/* calculate number of factors of 2,3,4 in N */
/* calculate N = 2^n2 * 4^n4 * 8^n8 * 3^n3 * 5^n5 *7^n7 * n */
#include"VI_fft_building_blocks_d.h"
#include"VI_nuV.h"
#include"VI_jofk.h"
#include"VI_vrealview_d.h"
#include"VI_vimagview_d.h"
#include"vsip_scalars.h"


vsip_fft_d* vsip_ccfftip_create_d(vsip_length N,
                       vsip_scalar_d scale,
                       vsip_fft_dir dir,
                       unsigned int ntimes,
                       vsip_alg_hint hint)
{
    vsip_length i;
    vsip_vview_d wt1,wt2;
    vsip_fft_d *fft = (vsip_fft_d*) malloc(sizeof(vsip_fft_d));
    if(fft == NULL) return (vsip_fft_d*) NULL;
    fft->N = N;
    fft->scale = scale;
    fft->d = dir;
    fft->pn = (vsip_scalar_vi*)malloc(6 * sizeof(vsip_scalar_vi));
    fft->p0 = (vsip_scalar_vi*)malloc(6 * sizeof(vsip_scalar_vi));
    fft->pF = (vsip_scalar_vi*)malloc(6 * sizeof(vsip_scalar_vi));
    fft->temp = vsip_cvcreate_d(N,VSIP_MEM_NONE); /* create a space to copy too when unsorting */
    fft->wt = vsip_cvcreate_d(N,VSIP_MEM_NONE);
    fft->index = (vsip_scalar_vi*) malloc(N * sizeof(vsip_scalar_vi));
    if((fft->pn == NULL) || (fft->p0 == NULL) || 
       (fft->pF == NULL) || (fft->wt == NULL) ||
       (fft->temp == NULL) || (fft->index == NULL)){
         vsip_fft_destroy_d(fft);
         return (vsip_fft_d*) NULL;
    }
    fft->length = VI_nuV(N,
         fft->pn,
         fft->p0,
         fft->pF);
    fft->hint = hint;
    fft->ntimes = ntimes; 
    fft->type = VSIP_CCFFTIP; 

    /* create twiddle table */
    { 
        vsip_vview_d *wtR = VI_vrealview_d(fft->wt,&wt1); 
        vsip_vview_d *wtI = VI_vimagview_d(fft->wt,&wt2); 
        if(dir == -1){ 
          vsip_vramp_d((vsip_scalar_d)0.,- (vsip_scalar_d)VI_ft_d_2PI/N,wtR);  
        }else{ 
          vsip_vramp_d((vsip_scalar_d)0., (vsip_scalar_d)VI_ft_d_2PI/N,wtR); 
        }   
        vsip_vsin_d(wtR,wtI);
        vsip_vcos_d(wtR,wtR);
    }

    if((fft->p0[0] == 1) && (fft->pF[0] == N)){
        fft->dft = 1; /* implies no supported factor exists */
    } else {
        fft->dft = 0; /* implies at least one of the supported factors exist */
    }
    /* calculate unsorting vector */
    {
        vsip_scalar_vi pF = fft->pF[fft->length - 1];
        for(i = 0; i< N; i++) fft->index[i] = VI_jofk(i,fft->pn,fft->p0,pF,fft->length);
    }
    return fft;
}
