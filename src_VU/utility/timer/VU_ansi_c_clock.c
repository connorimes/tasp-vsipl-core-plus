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
/* $Id: VU_ansi_c_clock.c,v 2.1 2007/04/18 19:39:09 judd Exp $ */

/*------------------------------------------------------------*
 | ANSI C defined clock                                       |
 | This is a simple timer which uses only functionality       |
 | defined by the ANSI standard. Errors will happen when      |
 | the clock counter rolls over. Big errors will happen if    |
 | the clock is called infrequently.                          |
 | clock returns decimal seconds                              |
 *------------------------------------------------------------*/
#include<stdio.h>
#include<time.h>
double VU_ansi_c_clock() /* JUDD */
{
    static double ansi_time = 0;
    static time_t ansi_time_0 = 0;
    double ansi_clock = 0;
    static double ansi_clock_0 = 0;
    static int ansi_clock_init = 1;
    if(ansi_clock_init){
        time_t t_error = time(&ansi_time_0);
        if(t_error == -1){
             fprintf(stderr,"ansi time error\n"); fflush(stderr);
             return 0;
        }
        ansi_clock_0 = (double)clock();
        ansi_time = (double) ansi_time_0;
        ansi_clock_init = 0;
        return ansi_time;
    }
    ansi_clock = (double)clock();
    if(ansi_clock > ansi_clock_0){
        ansi_time = ansi_time_0 + (ansi_clock - ansi_clock_0)/(double)CLOCKS_PER_SEC;
    } else {
        ansi_clock_0 = (double)clock();
        time(&ansi_time_0);
        if(ansi_time < ansi_time_0) ansi_time = ansi_time_0;
    }
    return ansi_time;
}
