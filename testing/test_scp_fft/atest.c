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
/* $Id: atest.c,v 2.1 2006/04/09 19:30:54 judd Exp $ */
#include"test_fft.h"
#include"ccfftop_sc_f.h"
int main(int argc, char* argv[]){
  int init = 666;
  init = vsip_init((void*)0);
  {
     ccfftop_sc_f();
  }    
  vsip_finalize((void*)0);
  return 0;
}
