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
/* $Id: VU_cmreadf_d.c,v 2.0 2003/02/22 15:20:06 judd Exp $ */
#include<stdio.h>
#include<vsip.h>
#include<VU.h>

void VU_cmreadf_d(
     FILE* fptr,
     vsip_cmview_d* M)
{
    vsip_index i,j;
    int n;
    vsip_scalar_d x,y;
    while((n = fscanf(fptr,"%lu %lu %lf %lf",&i,&j,&x,&y)) != EOF){
         vsip_cmput_d(M,i,j,vsip_cmplx_d(x,y));
    }
    return;
}
