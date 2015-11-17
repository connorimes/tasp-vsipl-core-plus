/* Created RJudd May 18, 1999 */
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
/* $Id: VUX_vxyplotinit_f.c,v 2.0 2003/02/22 15:20:01 judd Exp $ */
#include<stdio.h>
#include<string.h>
#include<vsip.h>
#include<VUX.h>

void VUX_vxyplotinit_f(
         VUX_graph_f* graph)
{
     graph->xformat = NULL;
     graph->yformat = NULL;
     graph->xtitle = NULL;
     graph->ytitle = NULL;
     graph->title = NULL;
     graph->displayname = 0;
     graph->xmax = 0;
     graph->xmin = 0;
     graph->ymax = 0;
     graph->ymin = 0;
     graph->xsize = 400;
     graph->ysize = 400;
     graph->xpixels = 400;
     graph->ypixels = 400;
     graph->xoff = 0;
     graph->yoff = 0;
     graph->xwinpos = -1;
     graph->ywinpos = -1;
     graph->xcross = 0;
     graph->ycross = 0;
     graph->axis_yn = VSIP_FALSE;
     graph->xtitle_yn = VSIP_FALSE;
     graph->ytitle_yn = VSIP_FALSE;
     graph->title_yn = VSIP_FALSE;
     return;
}
