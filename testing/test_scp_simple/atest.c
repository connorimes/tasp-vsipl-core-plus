#include<stdio.h>
#include<string.h>
#include<vsip.h>
#include<VU.h>
#define NDPTR_f ((vsip_scalar_f*)NULL)
#define NDPTR_d ((vsip_scalar_d*)NULL)

#include"mvprod3_f.h"
#include"mvprod3_d.h"

int main(){
   vsip_init((void*)0);
   mvprod3_f();
   mvprod3_d();
   vsip_finalize((void*)0);
   return 0;
}
