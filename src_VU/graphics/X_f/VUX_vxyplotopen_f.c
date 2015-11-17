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
/* $Id: VUX_vxyplotopen_f.c,v 2.0 2003/02/22 15:20:01 judd Exp $ */
#include<stdio.h>
#include<string.h>
#include<vsip.h>
#include<VUX.h>

void VUX_vxyplotopen_f(
         VUX_graph_f* graph)
{
     unsigned long int white,black;
     graph->disp = XOpenDisplay(graph->displayname);
     graph->screen = DefaultScreen(graph->disp);
     black = BlackPixel(graph->disp,graph->screen);
     white = WhitePixel(graph->disp,graph->screen);
     graph->win = XCreateSimpleWindow(
                 graph->disp,DefaultRootWindow(graph->disp),
                 graph->xwinpos, graph->ywinpos,
                 graph->xpixels,graph->ypixels,5,
                 black,white);
     graph->gc = XCreateGC(graph->disp,graph->win,0,0);
     XSetBackground(graph->disp,graph->gc,white);
     XSetForeground(graph->disp,graph->gc,black);
     XMapRaised(graph->disp,graph->win);
     XFlush(graph->disp);
     return;
}
