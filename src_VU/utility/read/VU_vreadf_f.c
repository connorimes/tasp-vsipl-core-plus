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
/* $Id: VU_vreadf_f.c,v 2.0 2003/02/22 15:20:06 judd Exp $ */
#include<stdio.h>
#include<vsip.h>
#include<VU.h>

void VU_vreadf_f(
     FILE* fptr,
     vsip_vview_f* m)
{
    vsip_index i;
    int n;
    vsip_scalar_f x;
    while((n = fscanf(fptr,"%lu %f",&i,&x)) != EOF){
         vsip_vput_f(m,i,x);
    }
    return;
}
