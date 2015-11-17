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
/* $Id: ludEx.c,v 2.0 2003/02/22 15:39:15 judd Exp $ */

/* A "feel good" test for lud */

#include<vsip.h>

#define NN 7

int main(){vsip_init((void*)0);
{
    vsip_mview_f *A  = vsip_mcreate_f(NN,NN,VSIP_ROW,0);
    vsip_vview_f *x0 = vsip_vcreate_f(NN,0);
    vsip_vview_f *b  = vsip_vcreate_f(NN,0);
    vsip_mview_f *X  = vsip_mcreate_f(NN,3,VSIP_ROW,0);
    vsip_mview_f *XT  = vsip_mcreate_f(NN,3,VSIP_ROW,0);
    vsip_vramp_f(1,1,x0); vsip_vmul_f(x0,x0,x0);
    { int i;
      vsip_vview_f *r = vsip_mrowview_f(A,0);
      vsip_offset o = vsip_vgetoffset_f(r);
      for(i=0; i<NN; i++){
          vsip_vputoffset_f(r,o);
          vsip_vramp_f(i,1,r);
          o +=NN;
      }
      vsip_vdestroy_f(r);
    }
    { vsip_vview_f *r = vsip_mdiagview_f(A,0);
      vsip_vfill_f(0,r);
      vsip_vdestroy_f(r);
    }
    {int i,j; printf("A = [\n"); for(i=0; i<NN; i++){
                  for(j=0; j<NN; j++) printf("%9.2f%s",vsip_mget_f(A,i,j),(j == NN-1) ? "":",");
                  printf(";\n");
              }
              printf("]\n");
    }
    { int k; 
      vsip_vview_f *x;
      vsip_length L    = vsip_mgetrowlength_f(X);
      for(k=0; k<L; k++){
        x  = vsip_mcolview_f(X,k);
        vsip_mvprod_f(A,x0,b);
        vsip_vcopy_f_f(b,x);
        vsip_svmul_f(2.0,x0,x0);
        vsip_vdestroy_f(x);
      }
    {int i,j; printf("X = [\n"); for(i=0; i<NN; i++){
                  for(j=0; j<3; j++) printf("%9.2f%s",vsip_mget_f(X,i,j),(j == 2) ? "":",");
                  printf(";\n");
              }
              printf("]\n");
    }
      {vsip_lu_f* luAop = vsip_lud_create_f(NN);
      vsip_mcopy_f_f(X,XT);
      if(luAop == NULL) exit(1);
      vsip_lud_f(luAop,A);
      {  vsip_lu_attr_f attr;
         vsip_lud_getattr_f(luAop,&attr);
         printf("lud size %lu\n",attr.n);
      }  
      vsip_lusol_f(luAop,0,X);
      vsip_lusol_f(luAop,1,XT);
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
       vsip_valldestroy_f(b);
       vsip_valldestroy_f(x0);
       vsip_malldestroy_f(X);
       vsip_malldestroy_f(A);
    }
    } vsip_finalize((void*)0); return 1;
}
