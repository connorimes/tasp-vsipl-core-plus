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
/* $Id: VU_tprintm_i.c,v 2.0 2003/02/22 15:20:03 judd Exp $ */
#include<stdio.h>
#include<string.h>
#include<vsip.h>
#include<VU.h>

void VU_tprintm_i(char s[],
    vsip_tview_i *X)
{
    char format[50];
    vsip_length ZL = vsip_tgetzlength_i(X);
    vsip_length YL = vsip_tgetylength_i(X);
    vsip_length XL = vsip_tgetxlength_i(X);
    vsip_length x,y,z;
    vsip_scalar_i a;
    strcpy(format,"%");
    strcat(format,s);
    strcat(format,"d %s");
    printf("[\n");	
    for(z=0; z<ZL; z++){
      for(y=0; y<YL; y++){
         for(x=0; x<XL; x++){
             a=vsip_tget_i(X,z,y,x);
             printf(format,a,((x==(XL-1)) ? ";" : " "));
         }
      printf("\n");
      }  
      printf("\n");
    }
    printf("];\n");
    return;
}

