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
/* $Id: lud3Ex.c,v 2.0 2003/02/22 15:39:15 judd Exp $ */

/* A "feel good" test for lud */

#include<vsip.h>

#define NN 7

int main(){vsip_init((void*)0);
{
    vsip_mview_f *Adummy  = vsip_mcreate_f(5*NN,5*NN,VSIP_COL,0);
    vsip_mview_f *A = vsip_msubview_f(Adummy,3,2,NN,NN);
    vsip_vview_f *x0 = vsip_vcreate_f(NN,0);
    vsip_mview_f *X  = vsip_mcreate_f(NN,3,VSIP_ROW,0);
    vsip_mview_f *XT  = vsip_mcreate_f(NN,3,VSIP_COL,0);
    vsip_mputrowstride_f(A,2*vsip_mgetrowstride_f(A));
    vsip_mputcolstride_f(A,3*vsip_mgetcolstride_f(A));

    /* matrix data */
    vsip_mput_f(A,0,0,0.5); vsip_mput_f(A,0,1,7); vsip_mput_f(A,0,2,10); vsip_mput_f(A,0,3,12);
    vsip_mput_f(A,0,4,-3); vsip_mput_f(A,0,5,0); vsip_mput_f(A,0,6,.05);

    vsip_mput_f(A,1,0,2); vsip_mput_f(A,1,1,13); vsip_mput_f(A,1,2,18); vsip_mput_f(A,1,3,6);
    vsip_mput_f(A,1,4,0); vsip_mput_f(A,1,5,130); vsip_mput_f(A,1,6,8);

    vsip_mput_f(A,2,0,3); vsip_mput_f(A,2,1,-9); vsip_mput_f(A,2,2,2); vsip_mput_f(A,2,3,3);
    vsip_mput_f(A,2,4,2); vsip_mput_f(A,2,5,-9); vsip_mput_f(A,2,6,6);

    vsip_mput_f(A,3,0,4); vsip_mput_f(A,3,1,2); vsip_mput_f(A,3,2,2); vsip_mput_f(A,3,3,4);
    vsip_mput_f(A,3,4,1); vsip_mput_f(A,3,5,2); vsip_mput_f(A,3,6,3);

    vsip_mput_f(A,4,0,.2); vsip_mput_f(A,4,1,2); vsip_mput_f(A,4,2,9); vsip_mput_f(A,4,3,4);
    vsip_mput_f(A,4,4,1); vsip_mput_f(A,4,5,2); vsip_mput_f(A,4,6,3);

    vsip_mput_f(A,5,0,.1); vsip_mput_f(A,5,1,2); vsip_mput_f(A,5,2,.3); vsip_mput_f(A,5,3,4);
    vsip_mput_f(A,5,4,1); vsip_mput_f(A,5,5,2); vsip_mput_f(A,5,6,3);

    vsip_mput_f(A,6,0,.01); vsip_mput_f(A,6,1,.2); vsip_mput_f(A,6,2,3); vsip_mput_f(A,6,3,4);
    vsip_mput_f(A,6,4,1); vsip_mput_f(A,6,5,2); vsip_mput_f(A,6,6,3);

    {int i,j; printf("A = [\n"); for(i=0; i<NN; i++){
                  for(j=0; j<NN; j++) printf("%9.2f%s",vsip_mget_f(A,i,j),(j == NN-1) ? "":",");
                  printf(";\n");
              }
              printf("]\n");
    }
    { /* were solving for NTRANS Ax = B */
      /* use a known X, calculate B using Ax */
      int k; 
      vsip_vview_f *x;
      vsip_mview_f *AT = vsip_mtransview_f(A);
      vsip_length L    = vsip_mgetrowlength_f(X);
      vsip_vramp_f(1,1,x0);
      for(k=0; k<L; k++){
        x  = vsip_mcolview_f(X,k);
        vsip_mvprod_f(A,x0,x);
        vsip_svmul_f(2.0,x0,x0);
        vsip_vdestroy_f(x);
      }
      vsip_vramp_f(1,1,x0);
      for(k=0; k<L; k++){
        x  = vsip_mcolview_f(XT,k);
        vsip_mvprod_f(AT,x0,x);
        vsip_svmul_f(2.0,x0,x0);
        vsip_vdestroy_f(x);
      }
      vsip_mdestroy_f(AT);
      printf("X = 1  2  4\n    2  4  8\n    3  6 12\n    4  8 16\n    5 10 20\n    6 12 24\n    7 14 28\n");
      { 
         int i,j; printf("B = [\n");for(i=0; i<NN; i++){
                    for(j=0; j<3; j++) printf("%9.2f%s",vsip_mget_f(X,i,j),(j == 2) ? "":",");
                    printf(";\n");
                }
                printf("]\n");
      }
      {
        /* then solve for B to see if we get X back */
        vsip_lu_f* luAop = vsip_lud_create_f(NN);
        if(luAop == NULL) exit(1);
        vsip_lud_f(luAop,A);
        {  vsip_lu_attr_f attr;
           vsip_lud_getattr_f(luAop,&attr);
           printf("lud size %lu\n",attr.n);
        }  
        vsip_lusol_f(luAop,VSIP_MAT_NTRANS,X);
        vsip_lusol_f(luAop,VSIP_MAT_TRANS,XT);
        vsip_lud_destroy_f(luAop);
      }
    }
    {int i,j; printf("A\\X\n"); for(i=0; i<NN; i++){
                  for(j=0; j<3; j++) printf("%9.2f%s",vsip_mget_f(X,i,j),(j == 2) ? "":",");
                  printf(";\n");
              }
    }
    {int i,j; printf("A'\\X\n"); for(i=0; i<NN; i++){
                  for(j=0; j<3; j++) printf("%9.2f%s",vsip_mget_f(XT,i,j),(j == 2) ? "":",");
                  printf(";\n");
              }
    }
    {
       vsip_malldestroy_f(XT);
       vsip_valldestroy_f(x0);
       vsip_malldestroy_f(X);
       vsip_mdestroy_f(A);
       vsip_malldestroy_f(Adummy);
    }
    } vsip_finalize((void*)0); return 1;
}
