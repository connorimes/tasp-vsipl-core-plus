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
/* $Id: cneg_f.h,v 2.0 2003/02/22 15:23:17 judd Exp $ */
static void cneg_f(){
   printf("********\nTEST cneg_f\n");
   {
       vsip_cscalar_f a = vsip_cmplx_f(+1.5,+2.5);
       vsip_cscalar_f x = vsip_cmplx_f(-1.5,-2.5);
       vsip_cscalar_f b = vsip_cneg_f(x);
       printf("(%5.4f %+5.4fi) = vsip_cneg_f((%5.4f %+5.4fi))\n ",
                             b.r,b.i,x.r,x.i); 
       ((vsip_cmag_f(vsip_csub_f(a,b))) > .0001) ? printf("error\n") :
                             printf("correct\n");
       fflush(stdout);
   }
   return;
}
/* done */
