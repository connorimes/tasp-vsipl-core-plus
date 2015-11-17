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
/* $Id: ccholdEx.c,v 2.0 2003/02/22 15:46:16 judd Exp $ */

/*  vsip/CORE/CoreExample/exChold/ccholdEx.c
 *  Vsip Library Tester component
 *
 *  Avijit Purkayastha 
 *  High Performance Computing Laboratory
 *  Department of Computer Science and NSF Engineering Research Center
 *  Mississippi State University, Mississippi State, MS 39762
 *                             and
 *  Department of Mathematics
 *  University of Puerto Rico, Mayaguez, PR 00681.
 *  
 *  Contact Information:
 *  Phone: (601) 325-2565; Fax: (601) 325-7692
 *  avijit@erc.msstate.edu; avijit@cs.upr.clu.edu
 *
 * -  -   -   -   -   -   -  -  -  -  -  -  -  -  -  -  -  -  -               
 *
 * Copyright (C) Mississippi State University, 1998.
 *
 * Permission is hereby granted for using this software to all persons to
 * copy, modify, distribute and produce derivative works for any purpose
 * and without any restrictions, provided that this copyright notice and the
 * following disclaimer appear on all copies. This computer code also does
 * not make any warranty, express or implied, or assumes any legal liability
 * or  responsibility for  the accuracy, completeness or usefulness of any
 * of any information, apparatus, product or  process  disclosed, or
 * represents that its  use would not infringe privately owned rights.
 *
 * Work supported under contract from DARPA (TASP) through the US Air Force
 * Rome Laboratory, under contracts F30602-95-1-0036 and F30602-96-1-0329.
 * Any opinions, findings and conclusions or recommendations expressed
 * in this material are those of the author(s) and do not necessarily
 * reflect the views of U.S. Department of Energy or Mississippi State
 * University or University of Puerto Rico.
 *
 * -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -               
 *
 *  Author: A. Purkayastha
 *
 *  created:          august-28-98 (AP) (originally from AP's choldEx.c)
 *
 *
 * -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  
 */

#include<vsip.h>

#define N 20
#define M 6
#define UPP_LOW 0

int main(){vsip_init((void*)0);
{
    int i,j, solretval;
    vsip_cmview_d *A  = vsip_cmcreate_d(N,N,VSIP_COL,0);
    vsip_cmview_d *X  = vsip_cmcreate_d(N+1,M,VSIP_ROW,0);

    /* Nullify the data-space */
    for (i=0; i <  vsip_cmgetcollength_d(A); i++)
      for(j=0; j < vsip_cmgetrowlength_d(A); j++)
        vsip_cmput_d(A,i,j,vsip_cmplx_d(0,0));

    for (i=0; i <  vsip_cmgetcollength_d(X); i++)
      for(j=0; j <  vsip_cmgetrowlength_d(X); j++)
        vsip_cmput_d(X,i,j,vsip_cmplx_d(0,0));

    /* Initialise matrix A */
    for (i=0; i<N; i++)
      for (j = 0; j < N; j++)
	if(i == j) 
/*	  vsip_cmput_d(A,i,j, vsip_cmplx_d(N+1,N+1));
	else
	  vsip_cmput_d(A,i,j,vsip_cmplx_d(1,1));*/
        vsip_cmput_d(A,i,j, vsip_cmplx_d(N+1,0)); 
      else if (i > j) 
        vsip_cmput_d(A,i,j,vsip_cmplx_d(1,1));
      else if (i < j) 
        vsip_cmput_d(A,i,j,vsip_cmplx_d(1,-1)); 

    /* print  A */
    {int i,j; 
    printf("A matrix\nA = [\n");
    for(i=0; i<N; i++)
      {
	for(j=0; j< N; j++) 
	  printf("%6.2f+%6.2fi%s",
                     vsip_real_d(vsip_cmget_d(A,i,j)),
                     vsip_imag_d(vsip_cmget_d(A,i,j)),(j == N-1) ? "":",");
                   (i == N - 1) ? printf("]\n") : printf(";\n");
      }
    }
    /* initialise rhs */
    { int j, k; 
    vsip_cvview_d *y = NULL;
    vsip_cvview_d *x;
    vsip_vview_d *yr=NULL, *yi = NULL;

    vsip_length L    = vsip_cmgetrowlength_d(X);
    vsip_length m    = vsip_cmgetcollength_d(A);
    for(k=0; k<L; k++)
      {
        x  = vsip_cmcolview_d(X,k);
	for (j=0; j<m; j++)
	  {
	    y  = vsip_cmrowview_d(A,j);
            yr = vsip_vrealview_d(y);
            yi = vsip_vimagview_d(y);
	    vsip_cvput_d(x,j,vsip_cmplx_d((double)(k+1)*(vsip_vsumval_d(yr)),
                             (double) (k+1)*(vsip_vsumval_d(yi))));
	   vsip_cvdestroy_d(y);
           vsip_vdestroy_d(yr);
           vsip_vdestroy_d(yi);
	  }
        vsip_cvdestroy_d(x);
      }
    }
    /* print rhs */
    {int i,j; 
    printf("rhs matrix\nX = [\n");
    for(i=0; i<N; i++)
      {
	for(j=0; j<M; j++) 
	  printf("%7.2f+%7.2fi%s",
                     vsip_real_d(vsip_cmget_d(X,i,j)),
                     vsip_imag_d(vsip_cmget_d(X,i,j)),(j == M-1) ? "":",");
                   (i == N - 1) ? printf("]\n") : printf(";\n");
      }
    }
    /* main computational loop */
    {vsip_cchol_d* cholAop = vsip_cchold_create_d(UPP_LOW,N);
    if(cholAop == NULL) exit(1);
    printf("cchold returns %i\n",vsip_cchold_d(cholAop,A));
    {int i,j;
    printf("matrix A after factorisation\nA = [\n");
    for(i=0; i<N; i++)
      {
	for(j=0; j< N; j++)
	  printf("%7.2f+%7.2fi%s",
                     vsip_real_d(vsip_cmget_d(A,i,j)),
                     vsip_imag_d(vsip_cmget_d(A,i,j)),(j == N-1) ? "":",");
                   (i == N - 1) ? printf("]\n") : printf(";\n");
      }
    }
    if((solretval=vsip_ccholsol_d(cholAop,X)))
    {
      printf("Cholesky sol function returns %i\n",solretval);
      printf("Upper triang. mat R, is possibly singular\n");
    }
    else
    {
      printf("Cholesky sol function returns %i\n",solretval);
    }

    vsip_cchold_destroy_d(cholAop);
    }

    {int i,j;
    printf("Soln Matrix\nX = [\n"); 
    for(i=0; i<N; i++)
      {
	for(j=0; j<M; j++) 
	  printf("%9.2f + %9.2fi%s",
                     vsip_real_d(vsip_cmget_d(X,i,j)),
                     vsip_imag_d(vsip_cmget_d(X,i,j)),(j == M-1) ? "":",");
                   (i == N - 1) ? printf("]\n") : printf(";\n");
      }
    }

    vsip_cmalldestroy_d(X);
    vsip_cmalldestroy_d(A);
    }vsip_finalize((void*)0);return 1;
}
