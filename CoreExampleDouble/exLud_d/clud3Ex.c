
/* Created by RJudd April 21, 1998 */
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
/* $Id: clud3Ex.c,v 2.0 2003/02/22 15:46:30 judd Exp $ */
/* A "feel good" test for lud */

#include<vsip.h>
#include<VU.h>

#define NN 7

int main(){vsip_init((void*)0);
{
    vsip_cmview_d *Adummy  = vsip_cmcreate_d(5*NN,5*NN,VSIP_COL,0);
    vsip_cmview_d *A = vsip_cmsubview_d(Adummy,3,2,NN,NN);
/*    vsip_cmview_d *A= vsip_cmcreate_d(NN,NN,VSIP_COL,0); */
    vsip_cvview_d *x0 = vsip_cvcreate_d(NN,0);
    vsip_vview_d *x0_r = vsip_vrealview_d(x0);
    vsip_vview_d *x0_i = vsip_vimagview_d(x0);
    vsip_cmview_d *X  = vsip_cmcreate_d(NN,3,VSIP_ROW,0);
    vsip_cmview_d *XT  = vsip_cmcreate_d(NN,3,VSIP_COL,0);
    vsip_cmputrowstride_d(A,2*vsip_cmgetrowstride_d(A));
    vsip_cmputcolstride_d(A,3*vsip_cmgetcolstride_d(A)); 

    /* matrix data */
    vsip_cmput_d(A,0,0,vsip_cmplx_d(0.5,0.1)); vsip_cmput_d(A,0,1,vsip_cmplx_d(7,0.1)); 
    vsip_cmput_d(A,0,2,vsip_cmplx_d(10,0.1)); vsip_cmput_d(A,0,3,vsip_cmplx_d(12,0.1));
    vsip_cmput_d(A,0,4,vsip_cmplx_d(-3,0.1)); vsip_cmput_d(A,0,5,vsip_cmplx_d(0,0.1)); vsip_cmput_d(A,0,6,vsip_cmplx_d(.05,0.1));

    vsip_cmput_d(A,1,0,vsip_cmplx_d(2,0.1)); vsip_cmput_d(A,1,1,vsip_cmplx_d(13,0.1)); 
    vsip_cmput_d(A,1,2,vsip_cmplx_d(18,0.1)); vsip_cmput_d(A,1,3,vsip_cmplx_d(6,0.1));
    vsip_cmput_d(A,1,4,vsip_cmplx_d(0,0.1)); vsip_cmput_d(A,1,5,vsip_cmplx_d(130,0.1)); vsip_cmput_d(A,1,6,vsip_cmplx_d(8,0.1));

    vsip_cmput_d(A,2,0,vsip_cmplx_d(3,0.1)); vsip_cmput_d(A,2,1,vsip_cmplx_d(-9,0.1)); 
    vsip_cmput_d(A,2,2,vsip_cmplx_d(2,0.1)); vsip_cmput_d(A,2,3,vsip_cmplx_d(3,0.2));
    vsip_cmput_d(A,2,4,vsip_cmplx_d(2,0.2)); vsip_cmput_d(A,2,5,vsip_cmplx_d(-9,0.2)); vsip_cmput_d(A,2,6,vsip_cmplx_d(6,0.2));

    vsip_cmput_d(A,3,0,vsip_cmplx_d(4,0.2)); vsip_cmput_d(A,3,1,vsip_cmplx_d(2,0.2)); 
    vsip_cmput_d(A,3,2,vsip_cmplx_d(2,0.2)); vsip_cmput_d(A,3,3,vsip_cmplx_d(4,0.2));
    vsip_cmput_d(A,3,4,vsip_cmplx_d(1,0.2)); vsip_cmput_d(A,3,5,vsip_cmplx_d(2,0.2)); vsip_cmput_d(A,3,6,vsip_cmplx_d(3,0.2));

    vsip_cmput_d(A,4,0,vsip_cmplx_d(.2,0.3)); vsip_cmput_d(A,4,1,vsip_cmplx_d(2,0.3)); 
    vsip_cmput_d(A,4,2,vsip_cmplx_d(9,0.3)); vsip_cmput_d(A,4,3,vsip_cmplx_d(4,0.3));
    vsip_cmput_d(A,4,4,vsip_cmplx_d(1,0.3)); vsip_cmput_d(A,4,5,vsip_cmplx_d(2,0.3)); 
    vsip_cmput_d(A,4,6,vsip_cmplx_d(3,0.3));

    vsip_cmput_d(A,5,0,vsip_cmplx_d(.1,0.4)); vsip_cmput_d(A,5,1,vsip_cmplx_d(2,0.4)); 
    vsip_cmput_d(A,5,2,vsip_cmplx_d(.3,0.4)); vsip_cmput_d(A,5,3,vsip_cmplx_d(4,0.4));
    vsip_cmput_d(A,5,4,vsip_cmplx_d(1,0.4)); vsip_cmput_d(A,5,5,vsip_cmplx_d(2,0.4)); vsip_cmput_d(A,5,6,vsip_cmplx_d(3,0.4));

    vsip_cmput_d(A,6,0,vsip_cmplx_d(.01,0.4)); vsip_cmput_d(A,6,1,vsip_cmplx_d(.2,0.4)); 
    vsip_cmput_d(A,6,2,vsip_cmplx_d(3,0.4)); vsip_cmput_d(A,6,3,vsip_cmplx_d(4,0.4));
    vsip_cmput_d(A,6,4,vsip_cmplx_d(1,0.4)); vsip_cmput_d(A,6,5,vsip_cmplx_d(2,0.4)); vsip_cmput_d(A,6,6,vsip_cmplx_d(3,0.4));

    { /* were solving for NTRANS Ax = B */
      /* use a known X, calculate B using Ax */
      int k; 
      vsip_cvview_d *x;
      vsip_cmview_d *AT = vsip_cmcreate_d(NN,NN,VSIP_ROW,VSIP_MEM_NONE);
      vsip_length L     = vsip_cmgetrowlength_d(X);
      vsip_cmherm_d(A,AT);
      printf("A = "); VU_cmprintm_d("7.4",A);
      printf("AT = "); VU_cmprintm_d("7.4",AT);
      vsip_vramp_d(1,1,x0_r);
      vsip_vramp_d(1,-1,x0_i);
      for(k=0; k<L; k++){
        x  = vsip_cmcolview_d(X,k);
        vsip_cmvprod_d(A,x0,x);
        vsip_rscvmul_d(2.0,x0,x0);
        vsip_cvdestroy_d(x);
      }
      vsip_vramp_d(1,1,x0_r);
      vsip_vramp_d(1,-1,x0_i);
      for(k=0; k<L; k++){
        x  = vsip_cmcolview_d(XT,k);
        vsip_cmvprod_d(AT,x0,x);
        VU_cvprintm_d("7.4",x0);
        vsip_rscvmul_d(2.0,x0,x0);
        vsip_cvdestroy_d(x);
      }
      vsip_cmalldestroy_d(AT);
      printf("B = "); VU_cmprintm_d("7.4",X);
      printf("BT = "); VU_cmprintm_d("7.4",XT);
      {
        /* then solve to see if we get X back */
        vsip_clu_d* luAop = vsip_clud_create_d(NN);
        if(luAop == NULL) exit(1);
        vsip_clud_d(luAop,A);
        {  vsip_clu_attr_d attr;
           vsip_clud_getattr_d(luAop,&attr);
           printf("lud size %lu\n",attr.n);
        }  
        vsip_clusol_d(luAop,VSIP_MAT_NTRANS,X);
        vsip_clusol_d(luAop,VSIP_MAT_HERM,XT);
        vsip_clud_destroy_d(luAop);
      }
    }
    printf("A\\X = "); VU_cmprintm_d("9.6",X);
    printf("A'\\X = "); VU_cmprintm_d("9.6",XT);
    {
       vsip_vdestroy_d(x0_r);vsip_vdestroy_d(x0_i);
       vsip_cvalldestroy_d(x0);
       vsip_cmalldestroy_d(X);
       vsip_cmalldestroy_d(A);
    }
    }vsip_finalize((void*)0);return 1;
}
