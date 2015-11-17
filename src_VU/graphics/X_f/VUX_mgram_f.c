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
/* $Id: VUX_mgram_f.c,v 2.0 2003/02/22 15:20:00 judd Exp $ */
#include<stdio.h>
#include<string.h>
#include<vsip.h>
#include<VUX.h>

void VUX_mgram_f(
         VUX_gram_f* gram,
         vsip_mview_f* X)
         
{
     vsip_length RL = vsip_mgetrowlength_f(X),
                 CL = vsip_mgetcollength_f(X),
                 row,col,i;
     int mval;
     gram->xoff = (gram->xpixels - gram->xsize)/2 + (gram->xpixels - gram->xsize)%2;
     gram->yoff = (gram->ypixels - gram->ysize)/2 + (gram->ypixels - gram->ysize)%2;
     if(gram->axis_yn){
        { /* draw x axis  */
           char str[20];
           XDrawLine(gram->disp,gram->win,gram->gc,
                      gram->xoff, gram->yoff + gram->ysize + 5,
                                      gram->xoff + gram->xsize, gram->yoff + gram->ysize + 5);
           for(i=0; i<=gram->num_xticks; i++)
              XDrawLine(gram->disp,gram->win,gram->gc,
                                      gram->xoff + i * gram->xsize/gram->num_xticks, 
                                      gram->yoff + gram->ysize +5,
                                      gram->xoff + i * gram->xsize/gram->num_xticks, 
                                      gram->yoff + gram->ysize +10); 
           if(gram->xformat != NULL){
              sprintf(str,gram->xformat,gram->xmin);
              XDrawString(gram->disp,gram->win,gram->gc,
                       gram->xoff, gram->yoff + gram->ysize + gram->yoff/2,str,(int)strlen(str));
              sprintf(str,gram->xformat,gram->xmax);
              XDrawString(gram->disp,gram->win,gram->gc,
                           gram->xoff + gram->xsize - 20,
                           gram->yoff + gram->ysize + gram->yoff/2,str,(int)strlen(str));
            }
        }
        { /* draw y axis */
           char str[20];
           XDrawLine(gram->disp,gram->win, gram->gc,
                                      gram->xoff-5,
                                      gram->yoff, 
                                      gram->xoff-5,
                                      gram->yoff + gram->ysize);
           for(i=0; i<=gram->num_yticks; i++)
               XDrawLine(gram->disp,gram->win,gram->gc,
                                      gram->xoff -5,
                                      gram->yoff + i * gram->ysize/gram->num_yticks,
                                      gram->xoff -10,
                                      gram->yoff + i * gram->ysize/gram->num_yticks); 
           if(gram->yformat != NULL){
              sprintf(str,gram->yformat,gram->ymin);
              XDrawString(gram->disp,gram->win,gram->gc,
                    0, gram->yoff + gram->ysize,str,(int)strlen(str));
              sprintf(str,gram->yformat,gram->ymax);
              XDrawString(gram->disp,gram->win,gram->gc,
                    0, gram->yoff,str,(int)strlen(str));
           }
        }
     }
     if(gram->title_yn ){
          XDrawString(gram->disp,gram->win,gram->gc,
                      gram->title_xloc,gram->title_yloc,gram->title,(int)strlen(gram->title));
     }
     if(gram->xtitle_yn ){
          XDrawString(gram->disp,gram->win,gram->gc,
                      gram->xtitle_xloc,gram->xtitle_yloc,gram->xtitle,(int)strlen(gram->xtitle));
     }
     if(gram->ytitle_yn ){
          XDrawString(gram->disp,gram->win,gram->gc,
                      gram->ytitle_xloc,gram->ytitle_yloc,gram->ytitle,(int)strlen(gram->ytitle));
     } 
     for(row=0; row<CL; row++){
        for(col=0; col<RL; col++){
           mval = (int)vsip_mget_f(X,row,col);
           if((mval < gram->num_color) && (mval >= 0)){
                     VUX_Drawgram_point(gram,
                                    col + gram->xoff, 
                                    gram->yoff + gram->ysize - row,
                                    gram->color[mval]); 
           }else{
               (mval >= gram->num_color) ? 
                     VUX_Drawgram_point(gram,
                                    col + gram->xoff, 
                                    gram->yoff + gram->ysize - row,
                                    gram->color[gram->num_color - 1]):
                     VUX_Drawgram_point(gram,
                                    col + gram->xoff, 
                                    gram->yoff + gram->ysize - row,
                                    gram->color[0]);
          }
        }
     }
     XFlush(gram->disp);
     return;
}

void VUX_Drawgram_point(VUX_gram_f *gram, int x, int y, XColor color)
{
    XSetForeground(gram->disp,gram->gc,color.pixel);
    XDrawPoint(gram->disp,gram->win,gram->gc,x,y);  
    return;
}
