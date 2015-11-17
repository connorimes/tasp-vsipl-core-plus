#include<stdio.h>
#include<string.h>
#include<vsip.h>
#include<VU.h>
#define NDPTR_f ((vsip_scalar_f*)NULL)
#define NDPTR_d ((vsip_scalar_d*)NULL)

#include"lud_f.h"
#include"lud_d.h"
#include"clud_f.h"
#include"clud_d.h"

int main(){
   vsip_init((void*)0);
   lud_f();
   lud_d();
   clud_f();
   clud_d();
   vsip_finalize((void*)0);
   return 0;
}
