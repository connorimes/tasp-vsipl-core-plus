/* Created RJudd */
/* SPAWARSYSCEN D857 */
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
/* $Id: vsip_tcloneview_i.c,v 2.0 2003/02/22 15:19:05 judd Exp $ */

#define VI_TVIEW_I_
#include"VI_support_priv_i.h"

vsip_tview_i *vsip_tcloneview_i(
    const vsip_tview_i *tview_in)
{
   vsip_tview_i *tview = VI_tview_i();
   if(tview != NULL) *tview = *tview_in;
   return tview;
}
     

