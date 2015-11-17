/* Created RJudd */
/* SPAWARSYSCEN D881 */
#ifndef _vsip_VUX_h
#define _vsip_VUX_h
#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<vsip.h>

typedef struct {
    Display *disp;
    Window  win;
    int screen;
    GC gc;
    char *xtitle,
         *ytitle,
         *title;
    int xtitle_xloc,
        xtitle_yloc,
        ytitle_xloc,
        ytitle_yloc,
        title_xloc,
        title_yloc;
    vsip_scalar_bl xtitle_yn,
                   ytitle_yn,
                   title_yn;
    int  num_xticks,
         num_yticks;
    char *xformat,
         *yformat;
    vsip_scalar_bl axis_yn;
    vsip_scalar_f xmax,
                  xmin,
                  ymax,
                  ymin;
    int xsize,
        ysize;
    int xpixels,
        ypixels;
    int xoff,
        yoff;
    int xwinpos,
        ywinpos;
    int xcross,
        ycross;
    char *displayname;
    } VUX_graph_f;

typedef struct {
    Display *disp;
    Window  win;
    int screen;
    GC gc;
   char *xtitle,
        *ytitle,
        *title;
   int xtitle_xloc,
       xtitle_yloc,
       ytitle_xloc,
       ytitle_yloc,
        title_xloc,
        title_yloc;
   vsip_scalar_bl xtitle_yn,
                  ytitle_yn,
                   title_yn;
   int num_xticks,
       num_yticks;
   char *xformat,
        *yformat;
   vsip_scalar_bl axis_yn;
   vsip_scalar_f xmax,
                 xmin,
                 ymax,
                 ymin;
   int xsize,
       ysize;
   int xpixels,
       ypixels;
   int xoff,
       yoff;
   int xwinpos,
       ywinpos;
   char *displayname;
   int num_color;
   XColor color[258];
   GC gc_color[258];
   } VUX_gram_f;

/* x, y ploting routines */

void VUX_vxyplotinit_f(
                VUX_graph_f*);
void VUX_vxyplotmaxmin_f(
                VUX_graph_f*,
                vsip_scalar_f,  /*xmin*/ 
                vsip_scalar_f,  /*xmax*/
                vsip_scalar_f,  /*ymin*/
                vsip_scalar_f); /*ymax*/
void VUX_vxyplottitle_f(
                VUX_graph_f*,
                float, /* x % or x pixels */
                float, /* y % or y pixels */
                char*);
void VUX_vxyplotxtitle_f(
                VUX_graph_f*,
                float x, /* x % or x pixels */
                float y, /* y % or y pixels */
                char*);
void VUX_vxyplotytitle_f(
                VUX_graph_f*,
                float x, /* x % or x pixels */
                float y, /* y % or y pixels */
                char*);
void VUX_vxyplotaxis_f(
                VUX_graph_f*,
                int, /* num x ticks */
                int, /* num y ticks */
                char*,       /* format for xmin, xmax */
                char*);      /* format for ymin, ymax */
void VUX_vxyplotsize_f(
                VUX_graph_f*,
                int,  /* window length */
                int,  /* window height */
                int,  /* plot x length <= window length */
                int,  /* plot y length <= window height */
                int,  /* window location from left edge of screen */
                int); /* window location from top edge of screen */
void VUX_vxyplotopen_f(
                VUX_graph_f*);
void VUX_vxyplot_f(VUX_graph_f*,
     vsip_vview_f*, /* x values */
     vsip_vview_f*, /* values */
     vsip_scalar_bl /* auto update graph object? */);
void VUX_vxyplotclose_f(
                VUX_graph_f*);

/* Gram Functions */
void VUX_mgraminit_f(
     VUX_gram_f*,
     int,  /* matrix columns */
     int,  /* matrix rows */
     int,  /* window x size */
     int,  /* window ysize */
     int,  /* window x position */
     int); /* window y position */

void VUX_mgramopen_f(
     VUX_gram_f*);

void VUX_mgram_f(
     VUX_gram_f*,  /* gram must be initialized and opened first */
     vsip_mview_f*);   /* Matrix to plot */

void VUX_mgramupdate_f(
     VUX_gram_f*,  /* gram must be initialized and opened first */
     vsip_mview_f*);   /* Matrix to plot */

void VUX_mgramtitle_f(
                VUX_gram_f*,
                float, /* x % or x pixels */
                float, /* y % or y pixels */
                char*);                  

void VUX_mgramxtitle_f(
                VUX_gram_f*,
                float x, /* x % or x pixels */
                float y, /* y % or y pixels */
                char*);
void VUX_mgramytitle_f(
                VUX_gram_f*,
                float x, /* x % or x pixels */
                float y, /* y % or y pixels */
                char*);
void VUX_mgramaxis_f(
                VUX_gram_f*,
                int, /* num x ticks */
                int, /* num y ticks */
                char*,       /* format for xmin, xmax */
                char*);      /* format for ymin, ymax */          
void VUX_mgram_colorarray_f(
                VUX_gram_f*,
                int);
void VUX_mgram_gsarray_f(
                VUX_gram_f*,
                int);
void VUX_Drawgram_point(
                VUX_gram_f*,
                int,
                int,
                XColor);

#endif /*_vsip_VUX_h */
