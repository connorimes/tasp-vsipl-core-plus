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
/* $Id: cmmeansqval_d.h,v 2.0 2003/02/22 15:23:21 judd Exp $ */
static void cmmeansqval_d(){
   printf("\n*******\nTEST cmmeansqval_d\n\n");
   { vsip_scalar_d data_r[] = {M_PI/8.0,  M_PI/4.0,  M_PI/3.0,  M_PI/1.5,  1.25 * M_PI,  1.75 * M_PI};
     vsip_scalar_d data_i[] = { 1,        2,         -3,        -4,         5,           6};
     vsip_scalar_d ans = 23.8168;
     vsip_scalar_d val;
     vsip_cblock_d  *block = vsip_cblockbind_d(data_r,data_i,6,VSIP_MEM_NONE);
     vsip_cmview_d  *a = vsip_cmbind_d(block,0,2,3,1,2);
     vsip_cblockadmit_d(block,VSIP_TRUE);
     val = vsip_cmmeansqval_d(a);
     printf("val = vsip_cmmeansqval_d(a)\n matrix a\n");VU_cmprintm_d("8.6",a);
     printf("val =  %+f\n",val);
     printf("right answer = %+f\n",ans);
     if(fabs(val-ans) > .0001)
        printf("error\n");
     else
        printf("correct\n");
     vsip_cmalldestroy_d(a);
   }
   return;
}
