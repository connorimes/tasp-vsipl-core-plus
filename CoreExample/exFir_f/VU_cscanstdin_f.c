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
/* $Id: VU_cscanstdin_f.c,v 2.0 2003/02/22 15:40:25 judd Exp $ */

static
vsip_length VU_cscanstdin_f(vsip_cvview_f *x)
{
    vsip_length n = 0;
    vsip_length m = 1;
    vsip_length o = 0;
    vsip_scalar_f xsr;
    vsip_scalar_f xsi;
    vsip_cvattr_f attr;
    vsip_cvgetattrib_f(x,&attr);
    while(n < attr.length){
       ((m = scanf("%f %f",&xsr,&xsi)) == 2) ? vsip_cvput_f(x,n++,vsip_cmplx_f(xsr,xsi)) : vsip_cvput_f(x,n++,vsip_cmplx_f(0,0)); 
       if(m == 2) o++;
    }
    return o;
}
