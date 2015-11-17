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
/* $Id: qrdsolrEx.c,v 2.0 2003/02/22 15:36:52 judd Exp $ */


#include<stdio.h>
#include<vsip.h>
#include<VU.h>

#define M 4

int main(){vsip_init((void*)0);
{
   vsip_mview_f *A   = vsip_mcreate_f(M,M,VSIP_ROW,0);
   vsip_mview_f *ATA = vsip_mcreate_f(M,M,VSIP_ROW,0);
   vsip_mview_f *ATB = vsip_mcreate_f(M,1,VSIP_COL,0);
   { /* store data ; upper trianglar so answers are obvious */
     vsip_mput_f(A,0,0,1); vsip_mput_f(A,0,1,2); vsip_mput_f(A,0,2,1);vsip_mput_f(A,0,3,1);
     vsip_mput_f(A,1,0,0); vsip_mput_f(A,1,1,-1); vsip_mput_f(A,1,2,0);vsip_mput_f(A,1,3,1);
     vsip_mput_f(A,2,0,0); vsip_mput_f(A,2,1,0); vsip_mput_f(A,2,2,-1);vsip_mput_f(A,2,3,1);
     vsip_mput_f(A,3,0,0); vsip_mput_f(A,3,1,0); vsip_mput_f(A,3,2,0);vsip_mput_f(A,3,3,1);
     vsip_mput_f(ATB,0,0,1); vsip_mput_f(ATB,1,0,2); vsip_mput_f(ATB,2,0,2); vsip_mput_f(ATB,3,0,1);
   }
   printf("b = \n");VU_mprintm_f("6.4",ATB);
   printf("use upper triangular so Q is I and R is A\n");
   printf("A = \n");VU_mprintm_f("6.4",A);
   vsip_mcopy_f_f(A,ATA);
   { /* solve using LUD */
      vsip_lu_f* luAop = vsip_lud_create_f(M);
      vsip_lud_f(luAop,ATA);
      vsip_lusol_f(luAop,VSIP_MAT_NTRANS,ATB);
      printf("solve A x = b\n");
      printf("x from LUD = \n"); VU_mprintm_f("6.4",ATB);
      vsip_lud_destroy_f(luAop);
   } 
   vsip_mcopy_f_f(A,ATA);
   { /* solve using qrdsolr */
     vsip_qr_f *qrd;
     vsip_mview_f *B = vsip_mcreate_f(4,1,VSIP_COL,0);
     qrd = vsip_qrd_create_f(4,4,VSIP_QRD_NOSAVEQ);
     vsip_qrd_f(qrd,ATA);
     vsip_mput_f(B,0,0,1); vsip_mput_f(B,1,0,2); vsip_mput_f(B,2,0,2); vsip_mput_f(B,3,0,1);
     vsip_qrdsolr_f(qrd,VSIP_MAT_NTRANS,1,B);
     printf("X from qrdsolr NOSAVEQ =\n");VU_mprintm_f("6.4",B);
     vsip_qrd_destroy_f(qrd);
    }
   vsip_mcopy_f_f(A,ATA);
   { /* solve using qrdsolr */
     vsip_qr_f *qrd;
     vsip_mview_f *B = vsip_mcreate_f(4,1,VSIP_COL,0);
     qrd = vsip_qrd_create_f(4,4,VSIP_QRD_SAVEQ1);
     vsip_qrd_f(qrd,ATA);
     vsip_mput_f(B,0,0,1); vsip_mput_f(B,1,0,2); vsip_mput_f(B,2,0,2); vsip_mput_f(B,3,0,1);
     vsip_qrdsolr_f(qrd,VSIP_MAT_NTRANS,1,B);
     printf("X from qrdsolr SAVEQ1 =\n");VU_mprintm_f("6.4",B);
     vsip_qrd_destroy_f(qrd);
    }
   vsip_mdestroy_f(A);
   vsip_mdestroy_f(ATA);
   vsip_mdestroy_f(ATB);
   } vsip_finalize((void*)0); return 0;
}

