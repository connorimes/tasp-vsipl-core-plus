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
/* $Id: VUX_mgramupdate_f.c,v 2.0 2003/02/22 15:20:00 judd Exp $ */
#include<stdio.h>
#include<string.h>
#include<vsip.h>
#include<VUX.h>

void VUX_mgramupdate_f(
         VUX_gram_f* gram,
         vsip_mview_f* X)
         
{
     vsip_length RL = vsip_mgetrowlength_f(X),
                 CL = vsip_mgetcollength_f(X),
                 row,col;
     int mval;
     gram->xoff = (gram->xpixels - gram->xsize)/2 + (gram->xpixels - gram->xsize)%2;
     gram->yoff = (gram->ypixels - gram->ysize)/2 + (gram->ypixels - gram->ysize)%2;
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
