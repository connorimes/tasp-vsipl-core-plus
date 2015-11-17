/* Created RJudd */
/* SPAWARSYSCEN */
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
/* $Id: atest.c,v 2.0 2003/02/22 15:23:07 judd Exp $ */
#include<stdio.h>
#include<string.h>
#include<vsip.h>
#include<VU.h>
#define NDPTR_f ((vsip_scalar_f*)NULL)
#define NDPTR_d ((vsip_scalar_d*)NULL)

#include"chol_f.h"
#include"cchol_f.h"
#include"chol_d.h"
#include"cchol_d.h"

int main(){
   vsip_init((void*)0);
   chol_f();
   cchol_f();
   chol_d();
   cchol_d();
   vsip_finalize((void*)0);
   return 0;
}
