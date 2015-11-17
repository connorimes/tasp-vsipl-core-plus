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
/* $Id: VU_cvprintm_d.c,v 2.0 2003/02/22 15:20:03 judd Exp $ */
#include<stdio.h>
#include<string.h>
#include<vsip.h>
#include<VU.h>
void VU_cvprintm_d(char s[],
    vsip_cvview_d *X)
{
    char format[50];
    vsip_length L = vsip_cvgetlength_d(X);
    vsip_index vi;
    vsip_cscalar_d x;
    strcpy(format,"(%");
    strcat(format,s);
    strcat(format,"lf %+");
    strcat(format,s);
    strcat(format,"lfi) %s\n");
    printf("[\n");	
    for(vi=0; vi<L; vi++){
      x=vsip_cvget_d(X,vi);
      printf(format,vsip_real_d(x),
                    vsip_imag_d(x),";");
    }  
    printf("];\n");
    return;
}

