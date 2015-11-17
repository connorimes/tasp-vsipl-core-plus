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
/* $Id: VUX_mgramopen_f.c,v 2.0 2003/02/22 15:20:00 judd Exp $ */
#include<stdio.h>
#include<string.h>
#include<vsip.h>
#include<VUX.h>

void VUX_mgramopen_f(
         VUX_gram_f* gram)
{
     int i;
     unsigned long int white,black;
     gram->disp = XOpenDisplay(gram->displayname);
     gram->screen = DefaultScreen(gram->disp);
     black = BlackPixel(gram->disp,gram->screen);
     white = WhitePixel(gram->disp,gram->screen);
     gram->win = XCreateSimpleWindow(
                 gram->disp,DefaultRootWindow(gram->disp),
                 gram->xwinpos, gram->ywinpos,
                 gram->xpixels,gram->ypixels,5,
                 black,white);
     gram->gc = XCreateGC(gram->disp,gram->win,0,0);
     XSetBackground(gram->disp,gram->gc,white);
     XSetForeground(gram->disp,gram->gc,black);
     for(i=0; i<258; i++) gram->gc_color[i] = XCreateGC(gram->disp,gram->win,0,0);
     XMapRaised(gram->disp,gram->win);
     XFlush(gram->disp);
     return;
}
