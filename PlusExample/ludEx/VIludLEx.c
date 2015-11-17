/* Created RJudd */
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
/* $Id: VIludLEx.c,v 2.0 2003/02/22 15:49:14 judd Exp $ */
#include<vsip.h>
#include<vsip_mviewattributes_f.h>
#include<VU.h>
#include"VI_lud.h"
#include"VI_ludattributes_f.h"
#include<sys/times.h>

#define NN 600

int main(){  
vsip_init((void*)0);{
   vsip_mview_f *A = vsip_mcreate_f(NN,NN,VSIP_COL,VSIP_MEM_NONE);
   vsip_mview_f *B = vsip_mcreate_f(NN,2,VSIP_COL,VSIP_MEM_NONE);
   clock_t tclicks;
   struct tms t_buf;
   VI_lu_f *lud = VI_lud_create_f(NN);
   printf("data fill in times 1 %lu\n",times(&t_buf));
   { int i;
      vsip_vview_f *r = vsip_mrowview_f(A,0);
      vsip_offset o = vsip_vgetoffset_f(r);
      for(i=0; i<NN; i++){
          vsip_vputoffset_f(r,o);
          vsip_vramp_f(i,1,r);
          o += 1;
      }
      vsip_vdestroy_f(r);
   }
   { vsip_vview_f *r = vsip_mdiagview_f(A,0);
      vsip_vfill_f(0,r);
      vsip_vdestroy_f(r);
   }
   {  
      vsip_vview_f *r = vsip_mcolview_f(B,0);
      vsip_vramp_f(1,.01,r);
      vsip_vdestroy_f(r); r = vsip_mcolview_f(B,1);
      vsip_vramp_f(2,.01,r); vsip_vdestroy_f(r); 
   }
   /*printf("A = "); VU_mprintm_f("7.4",A);*/
   /*printf("B = "); VU_mprintm_f("7.4",B);*/
   printf("lud in times 2 %lu\n",(tclicks = times(&t_buf)));
   VI_lud_f(lud,A);
   printf("lud out times 3 %lu\n",times(&t_buf) - tclicks);
   /*printf("Adec = "); VU_mprintm_f("7.4",A);*/
   printf("lusol in times 4 %lu\n",(tclicks = times(&t_buf)));
   VI_lusol_f(lud,B);
   printf("lusol out times 5 %lu\n", times(&t_buf) - tclicks);
   /*printf("B = "); VU_mprintm_f("7.4",B); */
   }vsip_finalize((void*)0);return 0;
}
