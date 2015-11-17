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
/* $Id: VUX_vxyplot_f.c,v 2.0 2003/02/22 15:20:00 judd Exp $ */
#include<stdio.h>
#include<string.h>
#include<vsip.h>
#include<VUX.h>

void VUX_vxyplot_f(
         VUX_graph_f* graph,
         vsip_vview_f* x,
         vsip_vview_f* y,
         vsip_scalar_bl bool)
{
     vsip_length N = vsip_vgetlength_f(x),
                 i;
     vsip_scalar_f xval,yval,xdelta,ydelta;
     int xpix,ypix;
     vsip_index index;
     if(bool || (graph->xmax == graph->xmin)){
         graph->xmin = vsip_vminval_f(x,&index);
         graph->xmax = vsip_vmaxval_f(x,&index);
         graph->ymin = vsip_vminval_f(y,&index);
         graph->ymax = vsip_vmaxval_f(y,&index);
     }
     graph->xoff = (graph->xpixels - graph->xsize)/2 + (graph->xpixels - graph->xsize)%2;
     graph->yoff = (graph->ypixels - graph->ysize)/2 + (graph->ypixels - graph->ysize)%2;
     xdelta =graph->xmax - graph->xmin;
     ydelta =graph->ymax - graph->ymin;
     if(graph->axis_yn){
        { /* draw x axis */
           char str[20];
           XDrawLine(graph->disp,graph->win,graph->gc,
                                      graph->xoff , graph->yoff + graph->ysize,
                                      graph->xoff + graph->xsize, graph->yoff + graph->ysize);
           for(i=0; i<=graph->num_xticks; i++)
              XDrawLine(graph->disp,graph->win,graph->gc,
                                      graph->xoff + i * graph->xsize/graph->num_xticks, 
                                      graph->yoff + graph->ysize,
                                      graph->xoff + i * graph->xsize/graph->num_xticks, 
                                      graph->yoff + graph->ysize -5); 
           sprintf(str,graph->xformat,graph->xmin);
           XDrawString(graph->disp,graph->win,graph->gc,
                          graph->xoff,graph->yoff + graph->ysize + graph->yoff/2,str,(int)strlen(str));
           sprintf(str,graph->xformat,graph->xmax);
           XDrawString(graph->disp,graph->win, graph->gc,
                          graph->xoff + graph->xsize - 20,
                           graph->yoff + graph->ysize + graph->yoff/2,str,(int)strlen(str));
        }
        { /* draw y axis */
           char str[20];
           XDrawLine(graph->disp,graph->win,graph->gc,
                                      graph->xoff,
                                      graph->yoff, 
                                      graph->xoff,
                                      graph->yoff + graph->ysize);
           for(i=0; i<=graph->num_yticks; i++)
                    XDrawLine(graph->disp,graph->win,graph->gc,
                                      graph->xoff,
                                      graph->yoff + i * graph->ysize/graph->num_yticks,
                                      graph->xoff +5,
                                      graph->yoff + i * graph->ysize/graph->num_yticks); 
           sprintf(str,graph->yformat,graph->ymin);
           XDrawString(graph->disp,graph->win,graph->gc,0,
                           graph->yoff + graph->ysize,str,(int)strlen(str));
           sprintf(str,graph->yformat,graph->ymax);
           XDrawString(graph->disp,graph->win,graph->gc,0,
                           graph->yoff,str,(int)strlen(str));
        }
     }
     if(graph->title_yn ){
          XDrawString(graph->disp,graph->win,graph->gc,
                      graph->title_xloc,graph->title_yloc,graph->title,(int)strlen(graph->title));
     }
     if(graph->xtitle_yn ){
          XDrawString(graph->disp,graph->win,graph->gc,
                      graph->xtitle_xloc,graph->xtitle_yloc,graph->xtitle,(int)strlen(graph->xtitle));
     }
     if(graph->ytitle_yn ){
          XDrawString(graph->disp,graph->win,graph->gc,
                      graph->ytitle_xloc,graph->ytitle_yloc,graph->ytitle,(int)strlen(graph->ytitle));
     }
     for(i=0; i<N; i++){
        xval = vsip_vget_f(x,i); yval = vsip_vget_f(y,i);
        if((xval < graph->xmin) || (xval > graph->xmax))break;
        if((yval < graph->ymin) || (yval > graph->ymax))break;
        xpix = graph->xoff + (int)((vsip_scalar_f)graph->xsize * (xval - graph->xmin)/xdelta);
        ypix = graph->yoff + graph->ysize - (int)((vsip_scalar_f)graph->ysize * (yval - graph->ymin)/ydelta);
        XDrawPoint(graph->disp,graph->win,graph->gc,xpix,ypix);
     }
     XFlush(graph->disp);
     return;
}
