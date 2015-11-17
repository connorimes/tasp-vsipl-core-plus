#include<stdio.h>
#include<string.h>
#include<vsip.h>
#include<VU.h>
#define NDPTR_f ((vsip_scalar_f*)NULL)
#define NDPTR_d ((vsip_scalar_d*)NULL)

#include"cblock_admit_release_d.h"

int main(){
  vsip_init((void*)0);
  cblock_admit_release_d();
  vsip_finalize((void*)0);
  return 0;
}
