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
/* $Id: testcqrd.c,v 2.0 2003/02/22 15:30:37 judd Exp $ */

#include<vsip.h>
#include<VU.h>

int main(int argc, char *argv[]){vsip_init((void*)0);
{  if(argc < 3){
      printf("usage\ntestcqrd M N FileName\n");
   } else {
      /* matrix size */
      vsip_length M    = (vsip_length)atoi(argv[1]),
                  N    = (vsip_length)atoi(argv[2]);
      /* Create some space to hold the matrix */
      vsip_cmview_f *A  = vsip_cmcreate_f(M,N,VSIP_COL,VSIP_MEM_NONE);
      vsip_cqr_f *qr = vsip_cqrd_create_f(M,N,VSIP_QRD_SAVEQ);
      /* get data */
      FILE *fptr = fopen(argv[3],"r");
      VU_cmreadf_f(fptr,A);
      fclose(fptr);
      vsip_cqrd_f(qr,A);
      VU_cmprintm_f("9.6",A);
      vsip_cmalldestroy_f(A);
      vsip_cqrd_destroy_f(qr);
   }
   } vsip_finalize((void*)0); return 0;
} 
