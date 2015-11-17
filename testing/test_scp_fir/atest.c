/* Created by RJudd */
/* SPAWARSYSCEN D857 */
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
/* $Id: atest.c,v 2.0 2003/02/22 15:23:11 judd Exp $ */
#include"test_fir.h"
#include"cfir_N201_D3_d.h"
#include"cfir_N201_D2_d.h"
/* #include"cfir_N201_D2_f.h"
#include"cfir_N201_D3_f.h" */
int main(int argc, char* argv[]){
  int init = 666;
  init = vsip_init((void*)0);
  {
     cfir_N201_D3_d(); 

     cfir_N201_D2_d();
/*     cfir_N201_D2_f();
     cfir_N201_D3_f(); */
  }    
  vsip_finalize((void*)0);
  return 0;
}
