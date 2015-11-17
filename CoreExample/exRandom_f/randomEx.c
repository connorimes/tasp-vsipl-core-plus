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
/* $Id: randomEx.c,v 2.0 2003/02/22 15:38:21 judd Exp $ */

#include<stdio.h>
#include<vsip.h>

#define L 40                   /*length*/
#define NS 8
#define TYPE VSIP_PRNG

int main(){vsip_init((void*)0);
{

    int i;
    vsip_vview_f* data      = vsip_vcreate_f(L,0);
    vsip_vview_f* dataOne   = vsip_vcreate_f(L,0);
    vsip_vview_f* dataTwo   = vsip_vcreate_f(L,0);
    vsip_vview_f* dataThree = vsip_vcreate_f(L,0);
    vsip_vview_f* dataFour = vsip_vcreate_f(L,0);
    vsip_vview_f* dataFive = vsip_vcreate_f(L,0);
    vsip_vview_f* dataSix = vsip_vcreate_f(L,0);
    vsip_vview_f* dataSeven = vsip_vcreate_f(L,0);
    vsip_vview_f* dataEight = vsip_vcreate_f(L,0);
    vsip_randstate *state = vsip_randcreate(7,1,1,TYPE);
    vsip_randstate *stateOne  = vsip_randcreate(7,NS,1,TYPE);
    vsip_randstate *stateTwo  = vsip_randcreate(7,NS,2,TYPE);
    vsip_randstate *stateThree = vsip_randcreate(7,NS,3,TYPE);
    vsip_randstate *stateFour = vsip_randcreate(7,NS,4,TYPE);
    vsip_randstate *stateFive = vsip_randcreate(7,NS,5,TYPE);
    vsip_randstate *stateSix = vsip_randcreate(7,NS,6,TYPE);
    vsip_randstate *stateSeven = vsip_randcreate(7,NS,7,TYPE);
    vsip_randstate *stateEight = vsip_randcreate(7,NS,8,TYPE);
    vsip_vrandu_f(state,data);
    vsip_vrandu_f(stateOne,dataOne);
    vsip_vrandu_f(stateTwo,dataTwo);
    vsip_vrandu_f(stateThree,dataThree);
    vsip_vrandu_f(stateFour,dataFour);
    vsip_vrandu_f(stateFive,dataFive);
    vsip_vrandu_f(stateSix,dataSix);
    vsip_vrandu_f(stateSeven,dataSeven);
    vsip_vrandu_f(stateEight,dataEight);
    for(i=0; i<L; i++)
        printf("%6.4f %6.4f %6.4f %6.4f %6.4f %6.4f %6.4f %6.4f %6.4f\n",
             vsip_vget_f(data,i),
             vsip_vget_f(dataOne,i),
             vsip_vget_f(dataTwo,i),
             vsip_vget_f(dataThree,i),
             vsip_vget_f(dataFour,i),
             vsip_vget_f(dataFive,i),
             vsip_vget_f(dataSix,i),
             vsip_vget_f(dataSeven,i),
             vsip_vget_f(dataEight,i));
    vsip_vrandu_f(state,data);/* calculate some random numbers to catch up with the other states */
    vsip_vrandu_f(state,data);
    vsip_vrandu_f(state,data);
    vsip_vrandu_f(state,data);
    vsip_vrandu_f(state,data);
    vsip_vrandu_f(state,data);
    vsip_vrandu_f(state,data);
    vsip_vrandu_f(state,data);/* this set of randoms should overlap with the next random */
    { vsip_scalar_f x[8];
      x[0] = vsip_randu_f(stateOne);
      x[1] = vsip_randu_f(stateTwo);
      x[2] = vsip_randu_f(stateThree);
      x[3] = vsip_randu_f(stateFour);
      x[4] = vsip_randu_f(stateFive);
      x[5] = vsip_randu_f(stateSix);
      x[6] = vsip_randu_f(stateSeven);
      x[7] = vsip_randu_f(stateEight);
      /* add seven to make up for the starting point of the series */
      /* should print out equal numbers */
      for(i=0; i<8; i++)
         printf("%6.4f %6.4f\n",vsip_vget_f(data,i + 7), x[i]);
     }

    /*destroy the vector views and any associated blocks*/
    vsip_valldestroy_f(data);
    vsip_valldestroy_f(dataOne);
    vsip_valldestroy_f(dataTwo);
    vsip_valldestroy_f(dataThree);
    vsip_valldestroy_f(dataFour);
    vsip_valldestroy_f(dataFive);
    vsip_valldestroy_f(dataSix);
    vsip_valldestroy_f(dataSeven);
    vsip_valldestroy_f(dataEight);
    vsip_randdestroy(state);
    vsip_randdestroy(stateOne);
    vsip_randdestroy(stateTwo);
    vsip_randdestroy(stateThree);
    vsip_randdestroy(stateFour);
    vsip_randdestroy(stateFive);
    vsip_randdestroy(stateSix);
    vsip_randdestroy(stateSeven);
    vsip_randdestroy(stateEight); 
    } vsip_finalize((void*)0); return 1;
}
