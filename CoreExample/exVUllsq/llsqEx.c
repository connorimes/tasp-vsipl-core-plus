/* Created RJudd February 7, 1999 */
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
/* $Id: llsqEx.c,v 2.0 2003/02/22 15:36:52 judd Exp $ */


#include<stdio.h>
#include<vsip.h>
#include<VU.h>

#define M 4
#define N 3

int main(){vsip_init((void*)0);
{
   void VU_mprint_f(vsip_mview_f*);
   void VU_mfill_f(vsip_mview_f*, vsip_scalar_f);
   void VU_vprint_f(vsip_vview_f*);
   vsip_mview_f *A   = vsip_mcreate_f(M,N,VSIP_ROW,0);
   vsip_mview_f *ATA = vsip_mcreate_f(N,N,VSIP_ROW,0);
   vsip_vview_f *b   = vsip_vcreate_f(M,0);
   vsip_mview_f *ATB = vsip_mcreate_f(N,1,VSIP_COL,0);
   vsip_vview_f *ATb = vsip_mcolview_f(ATB,0);
   { /* store data */
     vsip_mput_f(A,0,0,1); vsip_mput_f(A,0,1,2); vsip_mput_f(A,0,2,1);
     vsip_mput_f(A,1,0,3); vsip_mput_f(A,1,1,-1); vsip_mput_f(A,1,2,0);
     vsip_mput_f(A,2,0,2); vsip_mput_f(A,2,1,1); vsip_mput_f(A,2,2,-1);
     vsip_mput_f(A,3,0,1); vsip_mput_f(A,3,1,2); vsip_mput_f(A,3,2,2);
     vsip_vput_f(b,0,1); vsip_vput_f(b,1,2); vsip_vput_f(b,2,2); vsip_vput_f(b,3,1);
   }
   printf("b = \n");VU_vprint_f(b);
   printf("A = \n");VU_mprint_f(A);
   VU_mfill_f(ATA,0);
   vsip_gemp_f(1,A,VSIP_MAT_TRANS,A,VSIP_MAT_NTRANS,1,ATA);
   printf("ATA = \n");VU_mprint_f(ATA);
   vsip_vmprod_f(b,A,ATb);
   printf("ATb = \n"); VU_vprint_f(ATb);
   {
      vsip_lu_f* luAop = vsip_lud_create_f(N);
      vsip_lud_f(luAop,ATA);
      vsip_lusol_f(luAop,VSIP_MAT_NTRANS,ATB);
      printf("solve ATA x = ATb\n");
      printf("x = \n"); VU_mprint_f(ATB);
      vsip_lud_destroy_f(luAop);
   }
   { vsip_qr_f *qrd = vsip_qrd_create_f(4,3,VSIP_QRD_SAVEQ1);
     vsip_mview_f *B = vsip_mcreate_f(4,1,VSIP_COL,0);
     vsip_qrd_f(qrd,A);
     vsip_mput_f(B,0,0,1); vsip_mput_f(B,1,0,2); vsip_mput_f(B,2,0,2); vsip_mput_f(B,3,0,1);
     vsip_qrsol_f(qrd,1,B);
     printf("B=\n");VU_mprintm_f("6.4",B);
    }
   vsip_valldestroy_f(b);
   vsip_vdestroy_f(ATb);
   vsip_mdestroy_f(A);
   vsip_mdestroy_f(ATA);
   vsip_mdestroy_f(ATB);
   } vsip_finalize((void*)0); return 0;
}
void VU_vprint_f(vsip_vview_f *x)
{
   vsip_length i,L = vsip_vgetlength_f(x);
   printf("[\n");
   for(i=0; i<L; i++)
      printf("%6.4f%s\n",vsip_vget_f(x,i),((i == (L-1)) ? ";" : "]"));
   return;
}
   

void VU_mprint_f(vsip_mview_f *X)
{
    vsip_length RL = vsip_mgetrowlength_f(X);
    vsip_length CL = vsip_mgetcollength_f(X);
    vsip_length row,col;
    vsip_scalar_f x;
    printf("[\n");
    for(row=0; row<CL; row++){
      for(col=0; col<RL; col++){
        x=vsip_mget_f(X,row,col);
        printf("%6.4f %s",x,((col==(RL-1)) ? ";" : " "));
      }  
      printf("\n");
    }
    printf("];\n");
    return;
}

void VU_mfill_f(vsip_mview_f *X, vsip_scalar_f a)
{
    vsip_length RL = vsip_mgetrowlength_f(X);
    vsip_length CL = vsip_mgetcollength_f(X);
    vsip_length row,col;
    for(row=0; row<CL; row++)
      for(col=0; col<RL; col++)
        vsip_mput_f(X,row,col,a);
    return;
}

