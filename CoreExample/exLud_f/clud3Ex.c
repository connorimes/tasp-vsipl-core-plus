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
/* $Id: clud3Ex.c,v 2.0 2003/02/22 15:39:15 judd Exp $ */

/* A "feel good" test for lud */

#include<vsip.h>
#include<VU.h>

#define NN 7

int main(){vsip_init((void*)0);
{
    vsip_cmview_f *Adummy  = vsip_cmcreate_f(5*NN,5*NN,VSIP_COL,0);
    vsip_cmview_f *A = vsip_cmsubview_f(Adummy,3,2,NN,NN);
/*    vsip_cmview_f *A= vsip_cmcreate_f(NN,NN,VSIP_COL,0); */
    vsip_cvview_f *x0 = vsip_cvcreate_f(NN,0);
    vsip_vview_f *x0_r = vsip_vrealview_f(x0);
    vsip_vview_f *x0_i = vsip_vimagview_f(x0);
    vsip_cmview_f *X  = vsip_cmcreate_f(NN,3,VSIP_ROW,0);
    vsip_cmview_f *XT  = vsip_cmcreate_f(NN,3,VSIP_COL,0);
    vsip_cmputrowstride_f(A,2*vsip_cmgetrowstride_f(A));
    vsip_cmputcolstride_f(A,3*vsip_cmgetcolstride_f(A)); 

    /* matrix data */
    vsip_cmput_f(A,0,0,vsip_cmplx_f(0.5,0.1)); vsip_cmput_f(A,0,1,vsip_cmplx_f(7,0.1)); 
    vsip_cmput_f(A,0,2,vsip_cmplx_f(10,0.1)); vsip_cmput_f(A,0,3,vsip_cmplx_f(12,0.1));
    vsip_cmput_f(A,0,4,vsip_cmplx_f(-3,0.1)); vsip_cmput_f(A,0,5,vsip_cmplx_f(0,0.1)); vsip_cmput_f(A,0,6,vsip_cmplx_f(.05,0.1));

    vsip_cmput_f(A,1,0,vsip_cmplx_f(2,0.1)); vsip_cmput_f(A,1,1,vsip_cmplx_f(13,0.1)); 
    vsip_cmput_f(A,1,2,vsip_cmplx_f(18,0.1)); vsip_cmput_f(A,1,3,vsip_cmplx_f(6,0.1));
    vsip_cmput_f(A,1,4,vsip_cmplx_f(0,0.1)); vsip_cmput_f(A,1,5,vsip_cmplx_f(130,0.1)); vsip_cmput_f(A,1,6,vsip_cmplx_f(8,0.1));

    vsip_cmput_f(A,2,0,vsip_cmplx_f(3,0.1)); vsip_cmput_f(A,2,1,vsip_cmplx_f(-9,0.1)); 
    vsip_cmput_f(A,2,2,vsip_cmplx_f(2,0.1)); vsip_cmput_f(A,2,3,vsip_cmplx_f(3,0.2));
    vsip_cmput_f(A,2,4,vsip_cmplx_f(2,0.2)); vsip_cmput_f(A,2,5,vsip_cmplx_f(-9,0.2)); vsip_cmput_f(A,2,6,vsip_cmplx_f(6,0.2));

    vsip_cmput_f(A,3,0,vsip_cmplx_f(4,0.2)); vsip_cmput_f(A,3,1,vsip_cmplx_f(2,0.2)); 
    vsip_cmput_f(A,3,2,vsip_cmplx_f(2,0.2)); vsip_cmput_f(A,3,3,vsip_cmplx_f(4,0.2));
    vsip_cmput_f(A,3,4,vsip_cmplx_f(1,0.2)); vsip_cmput_f(A,3,5,vsip_cmplx_f(2,0.2)); vsip_cmput_f(A,3,6,vsip_cmplx_f(3,0.2));

    vsip_cmput_f(A,4,0,vsip_cmplx_f(.2,0.3)); vsip_cmput_f(A,4,1,vsip_cmplx_f(2,0.3)); 
    vsip_cmput_f(A,4,2,vsip_cmplx_f(9,0.3)); vsip_cmput_f(A,4,3,vsip_cmplx_f(4,0.3));
    vsip_cmput_f(A,4,4,vsip_cmplx_f(1,0.3)); vsip_cmput_f(A,4,5,vsip_cmplx_f(2,0.3)); 
    vsip_cmput_f(A,4,6,vsip_cmplx_f(3,0.3));

    vsip_cmput_f(A,5,0,vsip_cmplx_f(.1,0.4)); vsip_cmput_f(A,5,1,vsip_cmplx_f(2,0.4)); 
    vsip_cmput_f(A,5,2,vsip_cmplx_f(.3,0.4)); vsip_cmput_f(A,5,3,vsip_cmplx_f(4,0.4));
    vsip_cmput_f(A,5,4,vsip_cmplx_f(1,0.4)); vsip_cmput_f(A,5,5,vsip_cmplx_f(2,0.4)); vsip_cmput_f(A,5,6,vsip_cmplx_f(3,0.4));

    vsip_cmput_f(A,6,0,vsip_cmplx_f(.01,0.4)); vsip_cmput_f(A,6,1,vsip_cmplx_f(.2,0.4)); 
    vsip_cmput_f(A,6,2,vsip_cmplx_f(3,0.4)); vsip_cmput_f(A,6,3,vsip_cmplx_f(4,0.4));
    vsip_cmput_f(A,6,4,vsip_cmplx_f(1,0.4)); vsip_cmput_f(A,6,5,vsip_cmplx_f(2,0.4)); vsip_cmput_f(A,6,6,vsip_cmplx_f(3,0.4));

    { /* were solving for NTRANS Ax = B */
      /* use a known X, calculate B using Ax */
      int k; 
      vsip_cvview_f *x;
      vsip_cmview_f *AT = vsip_cmcreate_f(NN,NN,VSIP_ROW,VSIP_MEM_NONE);
      vsip_length L     = vsip_cmgetrowlength_f(X);
      vsip_cmherm_f(A,AT);
      printf("A = "); VU_cmprintm_f("7.4",A);
      printf("AT = "); VU_cmprintm_f("7.4",AT);
      vsip_vramp_f(1,1,x0_r);
      vsip_vramp_f(1,-1,x0_i);
      for(k=0; k<L; k++){
        x  = vsip_cmcolview_f(X,k);
        vsip_cmvprod_f(A,x0,x);
        vsip_rscvmul_f(2.0,x0,x0);
        vsip_cvdestroy_f(x);
      }
      vsip_vramp_f(1,1,x0_r);
      vsip_vramp_f(1,-1,x0_i);
      for(k=0; k<L; k++){
        x  = vsip_cmcolview_f(XT,k);
        vsip_cmvprod_f(AT,x0,x);
        VU_cvprintm_f("7.4",x0);
        vsip_rscvmul_f(2.0,x0,x0);
        vsip_cvdestroy_f(x);
      }
      vsip_cmalldestroy_f(AT);
      printf("B = "); VU_cmprintm_f("7.4",X);
      printf("BT = "); VU_cmprintm_f("7.4",XT);
      {
        /* then solve to see if we get X back */
        vsip_clu_f* luAop = vsip_clud_create_f(NN);
        if(luAop == NULL) exit(1);
        vsip_clud_f(luAop,A);
        {  vsip_clu_attr_f attr;
           vsip_clud_getattr_f(luAop,&attr);
           printf("lud size %lu\n",attr.n);
        }  
        vsip_clusol_f(luAop,VSIP_MAT_NTRANS,X);
        vsip_clusol_f(luAop,VSIP_MAT_HERM,XT);
        vsip_clud_destroy_f(luAop);
      }
    }
    printf("A\\X = "); VU_cmprintm_f("9.6",X);
    printf("A'\\X = "); VU_cmprintm_f("9.6",XT);
    {
       vsip_vdestroy_f(x0_r);vsip_vdestroy_f(x0_i);
       vsip_cvalldestroy_f(x0);
       vsip_cmalldestroy_f(X);
       vsip_cmdestroy_f(A);
       vsip_cmalldestroy_f(Adummy);
       vsip_cmalldestroy_f(XT);
    }
    } vsip_finalize((void*)0); return 1;
}
