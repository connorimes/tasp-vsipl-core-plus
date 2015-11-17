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
/* $Id: llsqEx.c,v 2.0 2003/02/22 15:46:45 judd Exp $ */

/* Created RJudd February 7, 1999 */
/* SPAWARSYSCEN D881 */

#include<stdio.h>
#include<vsip.h>

#define M 4
#define N 3

int main(){vsip_init((void*)0);
{
   void VU_mprint_d(vsip_mview_d*);
   void VU_mfill_d(vsip_mview_d*, vsip_scalar_d);
   void VU_vprint_d(vsip_vview_d*);
   vsip_mview_d *A   = vsip_mcreate_d(M,N,VSIP_ROW,0);
   vsip_mview_d *ATA = vsip_mcreate_d(N,N,VSIP_ROW,0);
   vsip_vview_d *b   = vsip_vcreate_d(M,0);
   vsip_mview_d *ATB = vsip_mcreate_d(N,1,VSIP_COL,0);
   vsip_vview_d *ATb = vsip_mcolview_d(ATB,0);
   { /* store data */
     vsip_mput_d(A,0,0,1); vsip_mput_d(A,0,1,2); vsip_mput_d(A,0,2,1);
     vsip_mput_d(A,1,0,3); vsip_mput_d(A,1,1,-1); vsip_mput_d(A,1,2,0);
     vsip_mput_d(A,2,0,2); vsip_mput_d(A,2,1,1); vsip_mput_d(A,2,2,-1);
     vsip_mput_d(A,3,0,1); vsip_mput_d(A,3,1,2); vsip_mput_d(A,3,2,2);
     vsip_vput_d(b,0,1);
     vsip_vput_d(b,1,2);
     vsip_vput_d(b,2,2);
     vsip_vput_d(b,3,1);
   }
   printf("b = \n");VU_vprint_d(b);
   printf("A = \n");VU_mprint_d(A);
   VU_mfill_d(ATA,0);
   vsip_gemp_d(1,A,VSIP_MAT_TRANS,A,VSIP_MAT_NTRANS,1,ATA);
   printf("ATA = \n");VU_mprint_d(ATA);
   vsip_vmprod_d(b,A,ATb);
   printf("ATb = \n"); VU_vprint_d(ATb);
   {
      vsip_lu_d* luAop = vsip_lud_create_d(N);
      vsip_lud_d(luAop,ATA);
      vsip_lusol_d(luAop,VSIP_MAT_NTRANS,ATB);
      printf("solve ATA x = ATb\n");
      printf("x = \n"); VU_mprint_d(ATB);
      vsip_lud_destroy_d(luAop);
   }
   vsip_valldestroy_d(b);
   vsip_vdestroy_d(ATb);
   vsip_mdestroy_d(A);
   vsip_mdestroy_d(ATA);
   vsip_mdestroy_d(ATB);
   }vsip_finalize((void*)0);return 0;
}
void VU_vprint_d(vsip_vview_d *x)
{
   vsip_length i,L = vsip_vgetlength_d(x);
   printf("[\n");
   for(i=0; i<L; i++)
      printf("%6.4f%s\n",vsip_vget_d(x,i),((i == (L-1)) ? ";" : "]"));
   return;
}
   

void VU_mprint_d(vsip_mview_d *X)
{
    vsip_length RL = vsip_mgetrowlength_d(X);
    vsip_length CL = vsip_mgetcollength_d(X);
    vsip_length row,col;
    vsip_scalar_d x;
    printf("[\n");
    for(row=0; row<CL; row++){
      for(col=0; col<RL; col++){
        x=vsip_mget_d(X,row,col);
        printf("%6.4f %s",x,((col==(RL-1)) ? ";" : " "));
      }  
      printf("\n");
    }
    printf("];\n");
    return;
}

void VU_mfill_d(vsip_mview_d *X, vsip_scalar_d a)
{
    vsip_length RL = vsip_mgetrowlength_d(X);
    vsip_length CL = vsip_mgetcollength_d(X);
    vsip_length row,col;
    for(row=0; row<CL; row++)
      for(col=0; col<RL; col++)
        vsip_mput_d(X,row,col,a);
    return;
}

