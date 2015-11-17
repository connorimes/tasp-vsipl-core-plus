/* Created R Judd */
/* Copyright (c) 2006 Randall Judd */
/* MIT style license, see Copyright notice in top level directory */
/* $Id: atest.c,v 1.2 2006/05/16 16:45:18 judd Exp $ */

#include <stdio.h>
#include<vsip.h>
#include<VU.h>

#include"covsol_f.h"
#include"covsol_d.h"
#include"ccovsol_f.h"
#include"ccovsol_d.h"
#include"llsqsol_f.h"
#include"llsqsol_d.h"
#include"cllsqsol_f.h"
#include"cllsqsol_d.h"
#include"toeplitz_f.h"
#include"toeplitz_d.h"
#include"ctoeplitz_f.h"
#include"ctoeplitz_d.h"

int main (int argc, const char * argv[]) {
   int init=vsip_init((void*)0);
    if(init) {
      printf("vsip initialize failed");
      return 1;
   }
   covsol_f();
   covsol_d();
   ccovsol_f();
   ccovsol_d();
   llsqsol_f();
   llsqsol_d();
   cllsqsol_f();
   cllsqsol_d();
   toeplitz_f();
   toeplitz_d();
   ctoeplitz_f();
   ctoeplitz_d();
   vsip_finalize((void*)0);
   return 0;
}
