/* Created RJudd May 19, 1999 */
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
/* $Id: VUX_mgramaxis_f.c,v 2.0 2003/02/22 15:20:00 judd Exp $ */
#include<stdio.h>
#include<string.h>
#include<vsip.h>
#include<VUX.h>

void VUX_mgramaxis_f(
         VUX_gram_f* gram,
         int xticks,
         int yticks,
         char *xformat,
         char *yformat)
{
         gram->num_xticks = xticks;
         gram->num_yticks = yticks;
         gram->axis_yn = VSIP_TRUE;
         gram->xformat = xformat;
         gram->yformat = yformat;
         return;
}
