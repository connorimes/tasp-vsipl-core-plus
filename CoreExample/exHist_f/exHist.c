#include<stdio.h>
#include<vsip.h>
#include<VU.h>

#define MAX 20
#define MIN 1
#define OPTR VSIP_HIST_RESET
#define OPTA VSIP_HIST_ACCUM
#define LENGTH 23
#define HLENGTH 5


int main(){vsip_init((void*)0);{
   vsip_vview_f *a = vsip_vcreate_f(LENGTH,0),
                *r = vsip_vcreate_f(HLENGTH,0);
   vsip_scalar_f min = MIN, max = MAX;
   FILE *fptr;
   fptr = fopen("data","r");
   VU_vreadf_f(fptr,a);
   fclose(fptr);
   vsip_vhisto_f(a,min,max,OPTR,r);
   printf("min = %3.0f, max = %3.0f, data = \n",min,max);VU_vprintm_f("6.3",a);
   printf("Histogram = \n");VU_vprintm_f("3.0",r);
   } vsip_finalize((void*)0); return 0;
}
