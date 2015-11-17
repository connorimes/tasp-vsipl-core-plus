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
/* $Id: test_fft.c,v 2.0 2003/02/22 15:23:09 judd Exp $ */
#include"test_fft.h"
#include"ccfftip_f.h"
#include"iccfftip_f.h"
#include"ccfftop_f.h"
#include"ccfftop_sc_f.h"
#include"iccfftop_f.h"
#include"rcfftop_f.h"
#include"crfftop_f.h"
#include"ccfftip_d.h"
#include"iccfftip_d.h"
#include"ccfftop_d.h"
#include"ccfftop_sc_d.h"
#include"iccfftop_d.h"
#include"rcfftop_d.h"
#include"crfftop_d.h"
int main(int argc, char* argv[]){
  int init = 666;
  init = vsip_init((void*)0);
  {
/*     ccfftip_f();
     iccfftip_f();
     ccfftop_f();
     ccfftop_sc_f();
     iccfftop_f();
     rcfftop_f();
     crfftop_f();
     ccfftip_d();
     iccfftip_d();
     ccfftop_d();
     ccfftop_sc_d();
     iccfftop_d();
     rcfftop_d(); */
     crfftop_d();
  }    
  vsip_finalize((void*)0);
  return 0;
}
