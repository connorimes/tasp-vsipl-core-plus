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
/* $Id: firEx.c,v 2.0 2003/02/22 15:40:25 judd Exp $ */

#include<stdio.h>
#include<vsip.h>
#include"VU_scanstdin_f.c"
#include"VU_printstdout_f.c"
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
       vsip_scalar_f hv;
       FILE *fh;
       vsip_fir_f *fir;
       vsip_vview_f *x = vsip_vcreate_f(N,0),
                    *h,*y;
       fh = fopen(argv[3],"r");
       while(fscanf(fh,"%f",&hv) == 1) n++;
       rewind(fh);
       y = vsip_vcreate_f(N/D + 1,0);
       h = vsip_vcreate_f(n,0);
       n=0;
       while(fscanf(fh,"%f",&hv) == 1){
           vsip_vput_f(h,n,hv);
        n++;
       }
          fclose(fh);
       fir = vsip_fir_create_f(h,VSIP_NONSYM,N,D,STATE,0,0);
       n = VU_scanstdin_f(x);
       while(n == N){
            k = vsip_firflt_f(fir,x,y);
            VU_printstdout_f(y,0,k);
            n = VU_scanstdin_f(x);
       }
       if(n != 0){
            k = vsip_firflt_f(fir,x,y);
            VU_printstdout_f(y,0,k);
       }
       {/* test getattr */
           vsip_fir_attr attr;
           vsip_fir_getattr_f(fir,&attr);
           printf("kernel %lu\n input %lu\n output %lu\ndecimation %d\n",
               attr.kernel_len,attr.in_len,attr.out_len, attr.decimation);
       }
       vsip_valldestroy_f(y);
       vsip_valldestroy_f(x);
       vsip_valldestroy_f(h);
       vsip_fir_destroy_f(fir);
       } vsip_finalize((void*)0); return 1;
   }
}   
