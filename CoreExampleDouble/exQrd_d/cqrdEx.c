/* Created by RJudd April 21, 1998 */
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
/* $Id: cqrdEx.c,v 2.0 2003/02/22 15:46:35 judd Exp $ */

/* A "feel good" test for lud */
/*
 *  vsip/CORE/CoreExample/exQrd/cqrdEx.c
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
 *  created:          sept-8-98 (AP) (in line with qrdEx.c)
 *
 *                    october-1-98 (AP)
 *                    made necessary changes to work in development mode
 *
 *                    july-23-99 (AP)
 *                    added options to cover all combinations of SAVEQ, 
 *                    SAVEQ1, and NOSAVEQ options with both Least-Squares
 *                    and Modified Gram-Schmidt systems, where ever feasible.
 *
 * -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  
 */

#include<vsip.h>

#define M 6
#define N 6
#define NN 6
#define NB 6
#define QOPT 2 /* 0 = NOSAVEQ, 1 = SAVEQ, 2 = SAVEQ1 */
#define QPROB  1 /* 0 = COV, 1 = LLSQ */

int main(){vsip_init((void*)0);
{
    int i,j, solretval=0;
    vsip_cmview_d *A  = vsip_cmcreate_d(M,N,VSIP_COL,0);
    vsip_cmview_d *X  = vsip_cmcreate_d(M,NB,VSIP_ROW,0);

    /* Nullify the data-space */
    for (i=0; i <  vsip_cmgetcollength_d(A); i++)
      for(j=0; j < vsip_cmgetrowlength_d(A); j++)
        vsip_cmput_d(A,i,j,vsip_cmplx_d(0,0));

    for (i=0; i <  vsip_cmgetcollength_d(X); i++)
      for(j=0; j <  vsip_cmgetrowlength_d(X); j++)
        vsip_cmput_d(X,i,j,vsip_cmplx_d(0,0));

    /* Initialise matrix A */
    for (i=0; i<M; i++)
      for (j = 0; j < N; j++)
	if(i == j) 
          vsip_cmput_d(A,i,j,vsip_cmplx_d(M+1, 0));
        else if(i > j)
          vsip_cmput_d(A,i,j, vsip_cmplx_d(1,1));
        else if(i < j)
          vsip_cmput_d(A,i,j,vsip_cmplx_d(1,-1));


    {int i,j; 
    printf("A matrix\nA = [\n");
    for(i=0; i<M; i++)
      {
	for(j=0; j< N; j++) 
	  printf("%6.2f+%6.2fi%s",
                     vsip_real_d(vsip_cmget_d(A,i,j)),
                     vsip_imag_d(vsip_cmget_d(A,i,j)),(j == N-1) ? "":",");
                   (i == M - 1) ? printf("]\n") : printf(";\n");
      }
    }
    { int j, k; 
    vsip_cvview_d *y = NULL;
    vsip_cvview_d *x;
    vsip_vview_d *yr = NULL, *yi = NULL;

    vsip_length L    = NB;
    vsip_length p    = M;
    for(k=0; k<L; k++)
      {
        x  = vsip_cmcolview_d(X,k);
	for (j=0; j<p; j++)
	  {
	    y  = vsip_cmrowview_d(A,j);
            yr = vsip_vrealview_d(y);
            yi = vsip_vimagview_d(y);
	    vsip_cvput_d(x,j, vsip_cmplx_d((double)(k+1)*(vsip_vsumval_d(yr)),
                             (double) (k+1)*(vsip_vsumval_d(yi))));
	    /* vsip_vput_d(x,j,(vsip_vsumval_d(y)));*/
	   vsip_cvdestroy_d(y);
           vsip_vdestroy_d(yr);
           vsip_vdestroy_d(yi);
	  }
        vsip_cvdestroy_d(x);
      }
    }
    {int i,j; 
    printf("rhs matrix\nB = [\n");
    for(i=0; i<NN; i++)
      {
	for(j=0; j<NB; j++) 
	  printf("%7.2f+%7.2fi%s",
                     vsip_real_d(vsip_cmget_d(X,i,j)),
                     vsip_imag_d(vsip_cmget_d(X,i,j)),(j == NB-1) ? "":",");
                   (i == NN - 1) ? printf("]\n") : printf(";\n");
      }
    }
    {vsip_cqr_d* qrAop = vsip_cqrd_create_d(M,N, QOPT);
    if(qrAop == NULL) exit(1);

    {int i,j;
    printf("matrix A after factorisation\n R/Q -- \n");
    if(QOPT == VSIP_QRD_SAVEQ1)
    {
      printf("qrd returns %i\n",vsip_cqrd_d(qrAop,A));      
      printf("matrix A after factorisation: skinny Q explicitly\n Q1 = [\n");
      for(i= 0; i< M ; i++)
        {
          for(j=0; j< N; j++)
            printf("%8.4f+%8.4fi%s",
                     vsip_real_d(vsip_cmget_d(A,i,j)),
                     vsip_imag_d(vsip_cmget_d(A,i,j)),(j == N-1) ? "":",");
                   (i == M - 1) ? printf("]\n") : printf(";\n");
        }

    } else if(QOPT == VSIP_QRD_SAVEQ || QOPT == VSIP_QRD_NOSAVEQ)
    {
      printf("qrd returns %i\n",vsip_cqrd_d(qrAop,A));
      printf("matrix A after fact.: R and ");
	(QOPT == VSIP_QRD_SAVEQ) ?  printf("full Q implicitly\n Q/R = [\n") :
			printf("Q not saved -- ignore LT portion. \n R = [\n");
      for(i= 0; i<M ; i++)
	{
	  for(j=0; j< N; j++)
	    printf("%9.5f+%9.5fi%s",
                     vsip_real_d(vsip_cmget_d(A,i,j)),
                     vsip_imag_d(vsip_cmget_d(A,i,j)),(j == N-1) ? "":",");
                   (i == M - 1) ? printf("]\n") : printf(";\n"); 
	}
    }
    }
    if( QPROB == VSIP_LLS)
    {
       if (QOPT == VSIP_QRD_SAVEQ1 || QOPT == VSIP_QRD_SAVEQ)
       {
	  if((solretval=vsip_cqrsol_d(qrAop, QPROB, X)))
	  {
	    printf("WARNING -- Least Squares soln returns %i-- CHECK\n", 
		   solretval);	    
	    printf("Upper triang. mat. R, possibly singular\n");
	  }
	  else
	    printf("Least Squares soln returns %i\n", solretval);
       }
       else
	 {
	 printf("Least Squares systems cannot be solved by the NOSAVEQ option -- exiting\n");
	 exit(1);
	 }
       }
    else
      {
      if((solretval=vsip_cqrsol_d(qrAop,QPROB, X)))
      {
	printf("Covariance soln returns %i\n",solretval);
	printf("Upper triang. mat. R, possibly singular\n");
      }
      else
      printf("Covariance soln returns %i\n",solretval);
    }
    vsip_cqrd_destroy_d(qrAop);
    }

    {int i,j;
    printf("Soln Matrix\nX = [\n");
      for(i=0; i<N; i++)
	{
	  for(j=0; j<NB; j++) 
	    printf("%9.5f+%9.5fi%s",
                     vsip_real_d(vsip_cmget_d(X,i,j)),
                     vsip_imag_d(vsip_cmget_d(X,i,j)),(j == NB-1) ? "":",");
                   (i == N - 1) ? printf("]\n") : printf(";\n");
	}
    }

    vsip_cmalldestroy_d(X);
    vsip_cmalldestroy_d(A);
    }vsip_finalize((void*)0);return 1;
}
