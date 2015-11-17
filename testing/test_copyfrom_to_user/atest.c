#include<stdio.h>
#include<string.h>
#include<vsip.h>
#include<VU.h>
#define NDPTR_f ((vsip_scalar_f*)NULL)
#define NDPTR_d ((vsip_scalar_d*)NULL)

#include"vcopyfrom_user_d.h"
#include"vcopyfrom_user_f.h"
#include"vcopyto_user_d.h"
#include"vcopyto_user_f.h"
#include"cvcopyfrom_user_d.h"
#include"cvcopyfrom_user_f.h"
#include"cvcopyto_user_d.h"
#include"cvcopyto_user_f.h"
#include"mcopyfrom_user_d.h"
#include"mcopyfrom_user_f.h"
#include"mcopyto_user_d.h"
#include"mcopyto_user_f.h"
#include"cmcopyfrom_user_d.h"
#include"cmcopyfrom_user_f.h"
#include"cmcopyto_user_d.h"
#include"cmcopyto_user_f.h"

int main(){
   vsip_init((void*)0);
   vcopyfrom_user_d();
   vcopyfrom_user_f();
   vcopyto_user_d();
   vcopyto_user_f();
   cvcopyfrom_user_d();
   cvcopyfrom_user_f();
   cvcopyto_user_d();
   cvcopyto_user_f();
   mcopyfrom_user_d();
   mcopyfrom_user_f();
   mcopyto_user_d();
   mcopyto_user_f();
   cmcopyfrom_user_d();
   cmcopyfrom_user_f();
   cmcopyto_user_d();
   cmcopyto_user_f();
   vsip_finalize((void*)0);
   return 0;
}
