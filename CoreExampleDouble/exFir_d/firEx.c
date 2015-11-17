
/* Created RJudd October 1998 */
/* SPAWARSYSCEN D881 */
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
/* $Id: firEx.c,v 2.0 2003/02/22 15:46:24 judd Exp $ */
#include<stdio.h>
#include<vsip.h>
#include"firEx.h"
#define STATE VSIP_STATE_SAVE

int main(int argc, char *argv[]){vsip_init((void*)0);
{ if(argc < 4){
    printf("usage\nfirEx length decimation filterFile <indataFile >outputFile\n");
    exit(0);
   }
   {
       vsip_length N = (vsip_length)atoi(argv[1]);
       int D = atoi(argv[2]);
       vsip_scalar_vi n = 0,k = 0;
       vsip_scalar_d hv;
       FILE *fh;
       vsip_fir_d *fir;
       vsip_vview_d *x = vsip_vcreate_d(N,0),
                    *h,*y;
       fh = fopen(argv[3],"r");
       while(fscanf(fh,"%lf",&hv) == 1) n++;
       rewind(fh);
       y = vsip_vcreate_d(N/D + 1,0);
       h = vsip_vcreate_d(n,0);
       n=0;
       while(fscanf(fh,"%lf",&hv) == 1){
           vsip_vput_d(h,n,hv);
        n++;
       }
          fclose(fh);
       fir = vsip_fir_create_d(h,VSIP_NONSYM,N,D,STATE,0,0);
       n = VU_scanstdin_d(x);
       while(n == N){
            k = vsip_firflt_d(fir,x,y);
            VU_printstdout_d(y,0,k);
            n = VU_scanstdin_d(x);
       }
       if(n != 0){
            k = vsip_firflt_d(fir,x,y);
            VU_printstdout_d(y,0,k);
       }
       {/* test getattr */
           vsip_fir_attr attr;
           vsip_fir_getattr_d(fir,&attr);
           printf("kernel %lu\n input %lu\n output %lu\ndecimation %d\n",
               attr.kernel_len,attr.in_len,attr.out_len, attr.decimation);
       }
       vsip_valldestroy_d(y);
       vsip_valldestroy_d(x);
       vsip_valldestroy_d(h);
       vsip_fir_destroy_d(fir);
       }vsip_finalize((void*)0);return 1;
   }
}   
