/* Produced By Randall Judd */
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
/* $Id: VU_vprintm_f.c,v 2.0 2003/02/22 15:20:04 judd Exp $ */
#include<stdio.h>
#include<string.h>
#include<vsip.h>
#include<VU.h>
void VU_vprintm_f(char s[],
    vsip_vview_f *X)
{
    char format[50];
    vsip_length L = vsip_vgetlength_f(X);
    vsip_index vi;
    vsip_scalar_f x;
    strcpy(format,"%");
    strcat(format,s);
    strcat(format,"f %s\n");
    printf("[\n");	
    for(vi=0; vi<L; vi++){
      x=vsip_vget_f(X,vi);
      printf(format,x,";");
    }  
    printf("];\n");
    return;
}

