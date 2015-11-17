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
/* $Id: cqrdsolrEx.c,v 2.0 2003/02/22 15:33:23 judd Exp $ */


#include<stdio.h>
#include<vsip.h>
#include<VU.h>

#define M 4

int main(){vsip_init((void*)0);
{
   vsip_cmview_f *A   = vsip_cmcreate_f(M,M,VSIP_ROW,0);
   vsip_cmview_f *ATA = vsip_cmcreate_f(M,M,VSIP_ROW,0);
   vsip_cmview_f *ATB = vsip_cmcreate_f(M,1,VSIP_COL,0);
   { /* store data ; upper trianglar so answers are obvious */
     vsip_cmput_f(A,0,0,vsip_cmplx_f(1,0)); vsip_cmput_f(A,0,1,vsip_cmplx_f(2,1)); 
          vsip_cmput_f(A,0,2,vsip_cmplx_f(1,2));vsip_cmput_f(A,0,3,vsip_cmplx_f(1,3));
     vsip_cmput_f(A,1,0,vsip_cmplx_f(0,0)); vsip_cmput_f(A,1,1,vsip_cmplx_f(3,0)); 
          vsip_cmput_f(A,1,2,vsip_cmplx_f(0,0));vsip_cmput_f(A,1,3,vsip_cmplx_f(0,1));
     vsip_cmput_f(A,2,0,vsip_cmplx_f(0,0)); vsip_cmput_f(A,2,1,vsip_cmplx_f(0,0)); 
          vsip_cmput_f(A,2,2,vsip_cmplx_f(2,0));vsip_cmput_f(A,2,3,vsip_cmplx_f(3,1));
     vsip_cmput_f(A,3,0,vsip_cmplx_f(0,0)); vsip_cmput_f(A,3,1,vsip_cmplx_f(0,0)); 
          vsip_cmput_f(A,3,2,vsip_cmplx_f(0,0));vsip_cmput_f(A,3,3,vsip_cmplx_f(1,0));
  
     vsip_cmput_f(ATB,0,0,vsip_cmplx_f(1,0)); vsip_cmput_f(ATB,1,0,vsip_cmplx_f(2,1)); 
          vsip_cmput_f(ATB,2,0,vsip_cmplx_f(1,0)); vsip_cmput_f(ATB,3,0,vsip_cmplx_f(3,1));
   }
   printf("b = ");VU_cmprintm_f("6.4",ATB); 
   printf("use upper triangular so Q is I and R is A\n");
   printf("A = ");VU_cmprintm_f("6.4",A); 
   vsip_cmcopy_f_f(A,ATA);
   { /* solve using LUD */
      vsip_clu_f* luAop = vsip_clud_create_f(M);
      vsip_clud_f(luAop,ATA);
      vsip_clusol_f(luAop,VSIP_MAT_HERM,ATB);
      printf("solve A x = b\n");
      printf("x from LUD = "); VU_cmprintm_f("6.4",ATB); 
      vsip_clud_destroy_f(luAop);
   } 
   vsip_cmcopy_f_f(A,ATA);
   { /* solve using qrdsolr */
     vsip_cqr_f *qrd;
     vsip_cmview_f *B = vsip_cmcreate_f(4,1,VSIP_COL,0);
     qrd = vsip_cqrd_create_f(4,4,VSIP_QRD_NOSAVEQ);
     vsip_cqrd_f(qrd,ATA);
     vsip_cmput_f(B,0,0,vsip_cmplx_f(1,0)); vsip_cmput_f(B,1,0,vsip_cmplx_f(2,1)); 
          vsip_cmput_f(B,2,0,vsip_cmplx_f(1,0)); vsip_cmput_f(B,3,0,vsip_cmplx_f(3,1));
     vsip_cqrdsolr_f(qrd,VSIP_MAT_HERM,vsip_cmplx_f(1,0),B);
     printf("X from qrdsolr NOSAVEQ =");VU_cmprintm_f("6.4",B); 
     vsip_cqrd_destroy_f(qrd);
    }
   vsip_cmcopy_f_f(A,ATA);
   { /* solve using qrdsolr */
     vsip_cqr_f *qrd;
     vsip_cmview_f *B = vsip_cmcreate_f(4,1,VSIP_COL,0);
     qrd = vsip_cqrd_create_f(4,4,VSIP_QRD_SAVEQ);
     vsip_cqrd_f(qrd,ATA);
     vsip_cmput_f(B,0,0,vsip_cmplx_f(1,0)); vsip_cmput_f(B,1,0,vsip_cmplx_f(2,1)); 
          vsip_cmput_f(B,2,0,vsip_cmplx_f(1,0)); vsip_cmput_f(B,3,0,vsip_cmplx_f(3,1));
     vsip_cqrdsolr_f(qrd,VSIP_MAT_HERM,vsip_cmplx_f(1,0),B);
     printf("X from qrdsolr SAVEQ1 =");VU_cmprintm_f("6.4",B); 
     vsip_cqrd_destroy_f(qrd);
    }
   vsip_cmdestroy_f(A);
   vsip_cmdestroy_f(ATA);
   vsip_cmdestroy_f(ATB);
   } vsip_finalize((void*)0); return 0;
}

