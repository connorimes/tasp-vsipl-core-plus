
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
/* $Id: ludEx.c,v 2.0 2003/02/22 15:46:30 judd Exp $ */
/* A "feel good" test for lud */

#include<vsip.h>

#define N 7

int main(){vsip_init((void*)0);
{
    vsip_mview_d *A  = vsip_mcreate_d(N,N,VSIP_ROW,0);
    vsip_vview_d *x0 = vsip_vcreate_d(N,0);
    vsip_vview_d *b  = vsip_vcreate_d(N,0);
    vsip_mview_d *X  = vsip_mcreate_d(N,3,VSIP_ROW,0);
    vsip_mview_d *XT  = vsip_mcreate_d(N,3,VSIP_ROW,0);
    vsip_vramp_d(1,1,x0); vsip_vmul_d(x0,x0,x0);
    { int i;
      vsip_vview_d *r = vsip_mrowview_d(A,0);
      vsip_offset o = vsip_vgetoffset_d(r);
      for(i=0; i<N; i++){
          vsip_vputoffset_d(r,o);
          vsip_vramp_d(i,1,r);
          o +=N;
      }
      vsip_vdestroy_d(r);
    }
    { vsip_vview_d *r = vsip_mdiagview_d(A,0);
      vsip_vfill_d(0,r);
      vsip_vdestroy_d(r);
    }
    {int i,j; printf("A = [\n"); for(i=0; i<N; i++){
                  for(j=0; j<N; j++) printf("%9.2f%s",vsip_mget_d(A,i,j),(j == N-1) ? "":",");
                  printf(";\n");
              }
              printf("]\n");
    }
    { int k; 
      vsip_vview_d *x;
      vsip_length L    = vsip_mgetrowlength_d(X);
      for(k=0; k<L; k++){
        x  = vsip_mcolview_d(X,k);
        vsip_mvprod_d(A,x0,b);
        vsip_vcopy_d_d(b,x);
        vsip_svmul_d(2.0,x0,x0);
        vsip_vdestroy_d(x);
      }
    {int i,j; printf("X = [\n"); for(i=0; i<N; i++){
                  for(j=0; j<3; j++) printf("%9.2f%s",vsip_mget_d(X,i,j),(j == 2) ? "":",");
                  printf(";\n");
              }
              printf("]\n");
    }
      {vsip_lu_d* luAop = vsip_lud_create_d(N);
      vsip_mcopy_d_d(X,XT);
      if(luAop == NULL) exit(1);
      vsip_lud_d(luAop,A);
      vsip_lusol_d(luAop,0,X);
      vsip_lusol_d(luAop,1,XT);
      vsip_lud_destroy_d(luAop);
      }
    }
    {int i,j; printf("A\\X\n"); for(i=0; i<N; i++){
                  for(j=0; j<3; j++) printf("%9.2f%s",vsip_mget_d(X,i,j),(j == 2) ? "":",");
                  printf(";\n");
              }
    }
    {int i,j; printf("A'\\X\n"); for(i=0; i<N; i++){
                  for(j=0; j<3; j++) printf("%9.2f%s",vsip_mget_d(XT,i,j),(j == 2) ? "":",");
                  printf(";\n");
              }
    }
    {
       vsip_valldestroy_d(b);
       vsip_valldestroy_d(x0);
       vsip_malldestroy_d(X);
       vsip_malldestroy_d(A);
    }
    }vsip_finalize((void*)0);return 1;
}
