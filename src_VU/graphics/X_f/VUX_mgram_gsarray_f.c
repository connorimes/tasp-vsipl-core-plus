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
/* $Id: VUX_mgram_gsarray_f.c,v 2.0 2003/02/22 15:20:00 judd Exp $ */
#include<vsip.h>
#include<VUX.h>

void VUX_mgram_gsarray_f(
         VUX_gram_f* gram,
         int num_color)
{
     Colormap cmap = DefaultColormap(gram->disp, gram->screen);
     int i;
     gram->num_color = (num_color > 256) ? 256 : num_color;
      for(i=0; i<gram->num_color; i++){
        (gram->color[i]).red  = (short int)(1 * ((float)i * (65535.0/(256.0 * 1.5))  + 65535/3));
        (gram->color[i]).green = (short int)(1 * ((float)i * (65535.0/(256.0 * 1.5))  + 65535/3));
        (gram->color[i]).blue  = (short int)(1 * ((float)i * (65535.0/(256.0 * 1.5))  + 65535/3));
        XAllocColor(gram->disp,cmap, &(gram->color[i]));
       }                               
     return;
}
