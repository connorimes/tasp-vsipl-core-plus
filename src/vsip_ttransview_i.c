/* Created RJudd October 6, 2000 */
/* SPAWARSYSCEN D857             */
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
/* $Id: vsip_ttransview_i.c,v 2.0 2003/02/22 15:19:08 judd Exp $ */

#define VI_TVIEW_I_
#include"VI_support_priv_i.h"

vsip_tview_i *vsip_ttransview_i(
       const vsip_tview_i *v,
       vsip_ttrans trans)
{
     vsip_tview_i *tranv = (vsip_tview_i*)NULL;
     if(trans == VSIP_TTRANS_NOP){
        tranv = VI_tview_i();
        if(tranv != NULL){
           *tranv = *v;
        }
     } else if(trans == VSIP_TTRANS_YX){
        tranv = VI_tview_i();
        if(tranv != NULL){
           *tranv = *v;
           tranv->y_stride = v->x_stride;
           tranv->x_stride = v->y_stride;
           tranv->y_length = v->x_length;
           tranv->x_length = v->y_length;
         }
     } else if(trans == VSIP_TTRANS_ZY){
        tranv = VI_tview_i();
        if(tranv != NULL){
           *tranv = *v;
           tranv->z_stride = v->y_stride;
           tranv->y_stride = v->z_stride;
           tranv->z_length = v->y_length;
           tranv->y_length = v->z_length;
         }
     } else if(trans == VSIP_TTRANS_ZX){
        tranv = VI_tview_i();
        if(tranv != NULL){
           *tranv = *v;
           tranv->z_stride = v->x_stride;
           tranv->x_stride = v->z_stride;
           tranv->z_length = v->x_length;
           tranv->x_length = v->z_length;
         }
     } else if(trans == VSIP_TTRANS_YXZY){
        tranv = VI_tview_i();
        if(tranv != NULL){
           *tranv = *v;
           tranv->z_stride = v->x_stride;
           tranv->z_length = v->x_length;
           tranv->x_stride = v->y_stride;
           tranv->x_length = v->y_length;
           tranv->y_stride = v->z_stride;
           tranv->y_length = v->z_length;
         }
     } else if(trans == VSIP_TTRANS_YXZX){
        tranv = VI_tview_i();
        if(tranv != NULL){
           *tranv = *v;
           tranv->y_stride = v->x_stride;
           tranv->y_length = v->x_length;
           tranv->z_stride = v->y_stride;
           tranv->z_length = v->y_length;
           tranv->x_stride = v->z_stride;
           tranv->x_length = v->z_length;
        }
     } 
     return tranv;
}
