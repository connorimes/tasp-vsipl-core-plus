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
/* $Id: real_f.h,v 2.0 2003/02/22 15:23:18 judd Exp $ */
static void real_f(){
   printf("********\nTEST real_f\n");
   {
       vsip_cscalar_f s = vsip_cmplx_f(3,4);
       vsip_scalar_f  a = 3;
       vsip_scalar_f  b = vsip_real_f(s);
       printf("%5.4f = vsip_real_f(%3.2f + %3.2fi)\n",b,s.r,s.i);
       (fabs(a-b) > .0001) ? printf("error\n") :
                             printf("correct\n");
       fflush(stdout);
   }
   return;
}
/* done */
