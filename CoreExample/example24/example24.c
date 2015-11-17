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
/* $Id: example24.c,v 2.0 2003/02/22 15:27:43 judd Exp $ */

#include<vsip.h>

void VU_mprintm_f(char format[],vsip_mview_f *X)
{ vsip_length RL = vsip_mgetrowlength_f(X),
              CL = vsip_mgetcollength_f(X),
              row,col;
  vsip_scalar_f x;
  printf("[\n");
  for(row=0; row<CL; row++){
    for(col=0; col<RL; col++){
      x=vsip_mget_f(X,row,col);
      printf(format,x,((col==(RL-1)) ? ";" : " "));
    } printf("\n");
  }printf("];\n");
  return;
}

/* A simple Q product example */
int main(){vsip_init((void*)0);
{
  vsip_mview_f 
       *A  = vsip_mcreate_f(3,3,VSIP_ROW,VSIP_MEM_NONE),
       *Q  = vsip_mcreate_f(3,3,VSIP_ROW,VSIP_MEM_NONE),
       *QT = vsip_mtransview_f(Q),
       *A0 = vsip_mcreate_f(3,3,VSIP_COL,VSIP_MEM_NONE),
       *R  = vsip_mcreate_f(3,3,VSIP_COL,VSIP_MEM_NONE);
  vsip_qr_f *qrd=vsip_qrd_create_f(3,3,VSIP_QRD_SAVEQ1);
  vsip_mput_f(A,0,0,1);vsip_mput_f(A,0,1,2);
  vsip_mput_f(A,0,2,3);
  vsip_mput_f(A,1,0,-1);vsip_mput_f(A,1,1,1);
  vsip_mput_f(A,1,2,-2);
  vsip_mput_f(A,2,0,1);vsip_mput_f(A,2,1,1);
  vsip_mput_f(A,2,2,-3);
  vsip_mput_f(Q,0,0,1);vsip_mput_f(Q,0,1,0);
  vsip_mput_f(Q,0,2,0);
  vsip_mput_f(Q,1,0,0);vsip_mput_f(Q,1,1,1);
  vsip_mput_f(Q,0,2,0);
  vsip_mput_f(Q,2,0,0);vsip_mput_f(Q,2,1,0);
  vsip_mput_f(Q,2,2,1); vsip_mcopy_f_f(A,A0);
  printf("A = "); VU_mprintm_f("%4.2f ",A);
  if(0 != vsip_qrd_f(qrd,A)) return 1;
  vsip_qrdprodq_f(qrd,VSIP_MAT_NTRANS,VSIP_MAT_RSIDE,Q);
  printf("Q = I Q =");VU_mprintm_f("%6.3f ",Q);
  vsip_mprod_f(QT,A0,R); 
  printf("R = QT A =");VU_mprintm_f("%6.3f ",R);
  vsip_qrdprodq_f(qrd,VSIP_MAT_NTRANS,VSIP_MAT_LSIDE,R);
  printf("A = QR =");VU_mprintm_f("%6.3f ",R);
  vsip_malldestroy_f(A); vsip_malldestroy_f(A0);
  vsip_malldestroy_f(R);
  vsip_mdestroy_f(QT); vsip_malldestroy_f(Q);
  vsip_qrd_destroy_f(qrd);
  } vsip_finalize((void*)0);return 0;
}
