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
/* $Id: qrdsolrEx.c,v 2.0 2003/02/22 15:47:07 judd Exp $ */


#include<stdio.h>
#include<vsip.h>
#include<VU.h>

#define M 4

int main(){vsip_init((void*)0);
{
   vsip_mview_d *A   = vsip_mcreate_d(M,M,VSIP_ROW,0);
   vsip_mview_d *ATA = vsip_mcreate_d(M,M,VSIP_ROW,0);
   vsip_mview_d *ATB = vsip_mcreate_d(M,1,VSIP_COL,0);
   { /* store data ; upper trianglar so answers are obvious */
     vsip_mput_d(A,0,0,1); vsip_mput_d(A,0,1,2); vsip_mput_d(A,0,2,1);vsip_mput_d(A,0,3,1);
     vsip_mput_d(A,1,0,0); vsip_mput_d(A,1,1,3); vsip_mput_d(A,1,2,0);vsip_mput_d(A,1,3,1);
     vsip_mput_d(A,2,0,0); vsip_mput_d(A,2,1,0); vsip_mput_d(A,2,2,2);vsip_mput_d(A,2,3,1);
     vsip_mput_d(A,3,0,0); vsip_mput_d(A,3,1,0); vsip_mput_d(A,3,2,0);vsip_mput_d(A,3,3,1);
     vsip_mput_d(ATB,0,0,1); vsip_mput_d(ATB,1,0,2); vsip_mput_d(ATB,2,0,2); vsip_mput_d(ATB,3,0,1);
   }
   printf("b = ");VU_mprintm_d("6.4",ATB);
   printf("use upper triangular so Q is I and R is A\n");
   printf("A = ");VU_mprintm_d("6.4",A);
   vsip_mcopy_d_d(A,ATA);
   { /* solve using LUD */
      vsip_lu_d* luAop = vsip_lud_create_d(M);
      vsip_lud_d(luAop,ATA);
      vsip_lusol_d(luAop,VSIP_MAT_TRANS,ATB);
      printf("solve A x = b\n");
      printf("x from LUD = "); VU_mprintm_d("6.4",ATB);
      vsip_lud_destroy_d(luAop);
   } 
   vsip_mcopy_d_d(A,ATA);
   { /* solve using qrdsolr */
     vsip_qr_d *qrd;
     vsip_mview_d *B = vsip_mcreate_d(4,1,VSIP_COL,0);
     qrd = vsip_qrd_create_d(4,4,VSIP_QRD_NOSAVEQ);
     vsip_qrd_d(qrd,ATA);
     vsip_mput_d(B,0,0,1); vsip_mput_d(B,1,0,2); vsip_mput_d(B,2,0,2); vsip_mput_d(B,3,0,1);
     vsip_qrdsolr_d(qrd,VSIP_MAT_TRANS,1,B);
     printf("X from qrdsolr NOSAVEQ =");VU_mprintm_d("6.4",B);
     vsip_qrd_destroy_d(qrd);
    }
   vsip_mcopy_d_d(A,ATA);
   { /* solve using qrdsolr */
     vsip_qr_d *qrd;
     vsip_mview_d *B = vsip_mcreate_d(4,1,VSIP_COL,0);
     qrd = vsip_qrd_create_d(4,4,VSIP_QRD_SAVEQ);
     vsip_qrd_d(qrd,ATA);
     vsip_mput_d(B,0,0,1); vsip_mput_d(B,1,0,2); vsip_mput_d(B,2,0,2); vsip_mput_d(B,3,0,1);
     vsip_qrdsolr_d(qrd,VSIP_MAT_TRANS,1,B);
     printf("X from qrdsolr SAVEQ1 =");VU_mprintm_d("6.4",B);
     vsip_qrd_destroy_d(qrd);
    }
   vsip_mdestroy_d(A);
   vsip_mdestroy_d(ATA);
   vsip_mdestroy_d(ATB);
   }vsip_finalize((void*)0);return 0;
}

