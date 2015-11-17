/* Created RJudd May 20, 1999 */
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
/* $Id: VUX_mgraminit_f.c,v 2.0 2003/02/22 15:20:00 judd Exp $ */
#include<stdio.h>
#include<string.h>
#include<vsip.h>
#include<VUX.h>

void VUX_mgraminit_f(
         VUX_gram_f* gram,
         int xsize,
         int ysize,
         int xpixels,
         int ypixels,
         int xwinpos,
         int ywinpos)
{
     gram->xsize  = xsize;
     gram->ysize  = ysize;
     gram->xpixels = xpixels;
     gram->ypixels = ypixels;
     gram->xwinpos = xwinpos;
     gram->ywinpos = ywinpos;              
     gram->xformat = NULL;
     gram->yformat = NULL;
     gram->xtitle = NULL;
     gram->ytitle = NULL;
     gram->title = NULL;
     gram->displayname = 0;
     gram->xmax = 0;
     gram->xmin = 0;
     gram->ymax = 0;
     gram->ymin = 0;
     gram->xoff = 0;
     gram->yoff = 0;
     gram->axis_yn = VSIP_FALSE;
     gram->xtitle_yn = VSIP_FALSE;
     gram->ytitle_yn = VSIP_FALSE;
     gram->title_yn = VSIP_FALSE;
     gram->num_color = 2;
     return;
}
