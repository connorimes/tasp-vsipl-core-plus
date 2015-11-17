/* Created RJudd July 21, 1999 */
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
/* $Id: VU_house_d.c,v 2.0 2003/02/22 15:46:48 judd Exp $ */

/* Householder Vector calculation */
/* Algorithm 5.1.1 Golub and Van Loan, Third Edition */

#include<vsip.h>

void VU_house_d(
   vsip_vview_d *x,
   vsip_vview_d *v,
   vsip_scalar_d *beta)
{
   vsip_vattr_d attrx,attr2;
   vsip_scalar_d sigma;
   vsip_vgetattrib_d(x,&attrx);
   attr2 = attrx;
   attr2.length -= 1;
   attr2.offset += attrx.stride;
   if(attr2.length > 0){
      vsip_vputattrib_d(x,&attr2);
      sigma = vsip_vdot_d(x,x);
      vsip_vputattrib_d(x,&attrx);
      vsip_vcopy_d_d(x,v);
   } else {
      sigma = 0;
   } 
   vsip_vput_d(v,0,1.0);
   if(sigma == 0){
      *beta = 0;
      if((attr2.length == 0) && (vsip_vget_d(x,0) < 0)) *beta = 2; 
   } else {
       vsip_scalar_d xv0 = vsip_vget_d(x,0),
                     v2 ;
       vsip_scalar_d mu = sqrt(xv0 * xv0 + sigma);
       if(xv0 <= 0){ 
           vsip_vput_d(v,0,xv0 - mu);
      } else {
           vsip_vput_d(v,0,-sigma/(xv0 + mu)); 
       }
       xv0 = vsip_vget_d(v,0);
       v2 = xv0 * xv0;
       *beta = 2 * v2/ (sigma + v2);
       vsip_svmul_d(1.0/xv0,v,v);
   }
   return;
}
