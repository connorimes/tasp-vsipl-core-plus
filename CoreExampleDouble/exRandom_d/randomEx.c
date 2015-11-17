/* Created by RJudd */
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
/* $Id: randomEx.c,v 2.0 2003/02/22 15:46:37 judd Exp $ */

/* Example of add */
 
#include<stdio.h>
#include<vsip.h>

#define L 40                   /*length*/
#define NS 8
#define TYPE VSIP_NPRNG
int main(){vsip_init((void*)0);
{

    int i;
    vsip_vview_d* data      = vsip_vcreate_d(L,0);
    vsip_vview_d* dataOne   = vsip_vcreate_d(L,0);
    vsip_vview_d* dataTwo   = vsip_vcreate_d(L,0);
    vsip_vview_d* dataThree = vsip_vcreate_d(L,0);
    vsip_vview_d* dataFour = vsip_vcreate_d(L,0);
    vsip_vview_d* dataFive = vsip_vcreate_d(L,0);
    vsip_vview_d* dataSix = vsip_vcreate_d(L,0);
    vsip_vview_d* dataSeven = vsip_vcreate_d(L,0);
    vsip_vview_d* dataEight = vsip_vcreate_d(L,0);
    vsip_randstate *state = vsip_randcreate(7,1,1,TYPE);
    vsip_randstate *stateOne  = vsip_randcreate(7,NS,1,TYPE);
    vsip_randstate *stateTwo  = vsip_randcreate(7,NS,2,TYPE);
    vsip_randstate *stateThree = vsip_randcreate(7,NS,3,TYPE);
    vsip_randstate *stateFour = vsip_randcreate(7,NS,4,TYPE);
    vsip_randstate *stateFive = vsip_randcreate(7,NS,5,TYPE);
    vsip_randstate *stateSix = vsip_randcreate(7,NS,6,TYPE);
    vsip_randstate *stateSeven = vsip_randcreate(7,NS,7,TYPE);
    vsip_randstate *stateEight = vsip_randcreate(7,NS,8,TYPE);
    vsip_vrandu_d(state,data);
    vsip_vrandu_d(stateOne,dataOne);
    vsip_vrandu_d(stateTwo,dataTwo);
    vsip_vrandu_d(stateThree,dataThree);
    vsip_vrandu_d(stateFour,dataFour);
    vsip_vrandu_d(stateFive,dataFive);
    vsip_vrandu_d(stateSix,dataSix);
    vsip_vrandu_d(stateSeven,dataSeven);
    vsip_vrandu_d(stateEight,dataEight);
    for(i=0; i<L; i++)
        printf("%6.4f %6.4f %6.4f %6.4f %6.4f %6.4f %6.4f %6.4f %6.4f\n",
             vsip_vget_d(data,i),
             vsip_vget_d(dataOne,i),
             vsip_vget_d(dataTwo,i),
             vsip_vget_d(dataThree,i),
             vsip_vget_d(dataFour,i),
             vsip_vget_d(dataFive,i),
             vsip_vget_d(dataSix,i),
             vsip_vget_d(dataSeven,i),
             vsip_vget_d(dataEight,i));
    vsip_vrandu_d(state,data);/* calculate some random numbers to catch up with the other states */
    vsip_vrandu_d(state,data);
    vsip_vrandu_d(state,data);
    vsip_vrandu_d(state,data);
    vsip_vrandu_d(state,data);
    vsip_vrandu_d(state,data);
    vsip_vrandu_d(state,data);
    vsip_vrandu_d(state,data);/* this set of randoms should overlap with the next random */
    { vsip_scalar_d x[8];
      x[0] = vsip_randu_d(stateOne);
      x[1] = vsip_randu_d(stateTwo);
      x[2] = vsip_randu_d(stateThree);
      x[3] = vsip_randu_d(stateFour);
      x[4] = vsip_randu_d(stateFive);
      x[5] = vsip_randu_d(stateSix);
      x[6] = vsip_randu_d(stateSeven);
      x[7] = vsip_randu_d(stateEight);
      /* add seven to make up for the starting point of the series */
      /* should print out equal numbers */
      for(i=0; i<8; i++)
         printf("%6.4f %6.4f\n",vsip_vget_d(data,i + 7), x[i]);
     }

    /*destroy the vector views and any associated blocks*/
    vsip_valldestroy_d(data);
    vsip_valldestroy_d(dataOne);
    vsip_valldestroy_d(dataTwo);
    vsip_valldestroy_d(dataThree);
    vsip_valldestroy_d(dataFour);
    vsip_valldestroy_d(dataFive);
    vsip_valldestroy_d(dataSix);
    vsip_valldestroy_d(dataSeven);
    vsip_valldestroy_d(dataEight);
    vsip_randdestroy(state);
    vsip_randdestroy(stateOne);
    vsip_randdestroy(stateTwo);
    vsip_randdestroy(stateThree);
    vsip_randdestroy(stateFour);
    vsip_randdestroy(stateFive);
    vsip_randdestroy(stateSix);
    vsip_randdestroy(stateSeven);
    vsip_randdestroy(stateEight); 
    }vsip_finalize((void*)0);return 1;
}
