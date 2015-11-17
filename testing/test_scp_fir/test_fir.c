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
/* $Id: test_fir.c,v 2.0 2003/02/22 15:23:12 judd Exp $ */
#include"test_fir.h"
#include"fir_N201_D1_f.h"
#include"fir_N200_D1_f.h"
#include"fir_N201_D2_f.h"
#include"fir_N201_D3_f.h"
#include"cfir_N201_D3_f.h"
#include"cfir_N201_D2_f.h"
#include"fir_N201_D1_NS_f.h"
#include"fir_N201_D2_NS_f.h"
#include"fir_N201_D3_NS_f.h"
#include"fir_N201_D1_NS_sc_f.h"
#include"fir_N201_D2_NS_sc_f.h"
#include"fir_N201_D3_sc_f.h"
#include"fir_n3_N67_D1_f.h"
#include"fir_n3_N67_D2_f.h"
#include"firE_n3_N67_D2_f.h"
#include"firO_n3_N67_D3_f.h"
#include"fir_n3_N67_D3_f.h"
#include"fir_n3_N67_D3_NS_f.h"
#include"fir_N201_D1_d.h"
#include"fir_N200_D1_d.h"
#include"fir_N201_D2_d.h"
#include"fir_N201_D3_d.h"
#include"cfir_N201_D3_d.h"
#include"cfir_N201_D2_d.h"
#include"fir_N201_D1_NS_d.h"
#include"fir_N201_D2_NS_d.h"
#include"fir_N201_D3_NS_d.h"
#include"fir_N201_D1_NS_sc_d.h"
#include"fir_N201_D2_NS_sc_d.h"
#include"fir_N201_D3_sc_d.h"
#include"fir_n3_N67_D1_d.h"
#include"fir_n3_N67_D2_d.h"
#include"firE_n3_N67_D2_d.h"
#include"firO_n3_N67_D3_d.h"
#include"fir_n3_N67_D3_d.h"
#include"fir_n3_N67_D3_NS_d.h"
int main(int argc, char* argv[]){
  int init = 666;
  init = vsip_init((void*)0);
  {
     fir_N201_D1_f();
     fir_N200_D1_f();
     fir_N201_D2_f();
     fir_N201_D3_f();
     cfir_N201_D3_f(); 
     cfir_N201_D2_f();
     fir_N201_D1_NS_f();
     fir_N201_D2_NS_f();
     fir_N201_D3_NS_f();
     fir_N201_D1_NS_sc_f();
     fir_N201_D2_NS_sc_f();
     fir_N201_D3_sc_f(); 
     fir_n3_N67_D1_f();
     fir_n3_N67_D2_f();
     firE_n3_N67_D2_f();
     firO_n3_N67_D3_f();
     fir_n3_N67_D3_f();
     fir_n3_N67_D3_NS_f();
     fir_N201_D1_d();
     fir_N200_D1_d();
     fir_N201_D2_d();
     fir_N201_D3_d();
     cfir_N201_D3_d(); 
     cfir_N201_D2_d();
     fir_N201_D1_NS_d();
     fir_N201_D2_NS_d();
     fir_N201_D3_NS_d();
     fir_N201_D1_NS_sc_d();
     fir_N201_D2_NS_sc_d();
     fir_N201_D3_sc_d(); 
     fir_n3_N67_D1_d();
     fir_n3_N67_D2_d();
     firE_n3_N67_D2_d();
     firO_n3_N67_D3_d();
     fir_n3_N67_D3_d();
     fir_n3_N67_D3_NS_d();
  }    
  vsip_finalize((void*)0);
  return 0;
}
