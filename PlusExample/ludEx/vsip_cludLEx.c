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
/* $Id: vsip_cludLEx.c,v 2.0 2003/02/22 15:49:14 judd Exp $ */
#include<vsip.h>
#include<VU.h>
#include<sys/times.h>

#define NN 600

int main() {  
vsip_init((void*)0);
   vsip_cmview_f *A = vsip_cmcreate_f(NN,NN,VSIP_ROW,VSIP_MEM_NONE);
   vsip_cmview_f *B = vsip_cmcreate_f(NN,2,VSIP_COL,VSIP_MEM_NONE);
   struct tms t_buf;
   clock_t tclicks;
   vsip_clu_f *lud = vsip_clud_create_f(NN);
   printf("data fill in times 1 %lu\n",times(&t_buf));
   { int i;
      vsip_cvview_f *r = vsip_cmrowview_f(A,0);
      vsip_vview_f *r_r = vsip_vrealview_f(r);
      vsip_vview_f *r_i = vsip_vimagview_f(r);
      vsip_offset o = vsip_cvgetoffset_f(r);
      for(i=0; i<NN; i++){
          vsip_vputoffset_f(r_r,o);
          vsip_vputoffset_f(r_i,o);
          vsip_vramp_f(i,1,r_r);
          vsip_vramp_f(i,-1,r_i);
          o += 1;
      }
      vsip_vdestroy_f(r_r); vsip_vdestroy_f(r_i);
      vsip_cvdestroy_f(r);
   }
   { vsip_cvview_f *r = vsip_cmdiagview_f(A,0);
      vsip_vview_f *r_r = vsip_vrealview_f(r);
      vsip_vview_f *r_i = vsip_vimagview_f(r);
      vsip_vfill_f(0,r_r);
      vsip_vfill_f(0,r_i);
      vsip_vdestroy_f(r_r); vsip_vdestroy_f(r_i);
      vsip_cvdestroy_f(r);
   }
   {  
      vsip_cvview_f *r = vsip_cmcolview_f(B,0);
      vsip_vview_f *r_r = vsip_vrealview_f(r);
      vsip_vview_f *r_i = vsip_vimagview_f(r);
      vsip_vramp_f(1,.01,r_r);
      vsip_vfill_f(0,r_i);
      vsip_cvdestroy_f(r); r = vsip_cmcolview_f(B,1);
      vsip_vdestroy_f(r_r); vsip_vdestroy_f(r_i);
      r_r = vsip_vrealview_f(r); r_i = vsip_vimagview_f(r);
      vsip_vramp_f(2,.01,r_r);
      vsip_vfill_f(0,r_i);
      vsip_vdestroy_f(r_r); vsip_vdestroy_f(r_i);
      vsip_cvdestroy_f(r);
   }
   /* printf("A = "); VU_cmprintm_f("7.4",A); */
   /* printf("B = "); VU_cmprintm_f("7.4",B); */
   printf("lud in times 2 %lu\n",(tclicks = times(&t_buf)));
   vsip_clud_f(lud,A);
   printf("lud out times 3 %lu\n",times(&t_buf) - tclicks);
   /* printf("Adec = "); VU_cmprintm_f("7.4",A); */ 
   printf("lusol in times 4 %lu\n",(tclicks = times(&t_buf)));
   vsip_clusol_f(lud,VSIP_MAT_NTRANS,B);
   printf("lusol out times 5 %lu\n",times(&t_buf) - tclicks);
   /* printf("B = "); VU_cmprintm_f("7.4",B); */
   } vsip_finalize((void*)0);return 0;
}
