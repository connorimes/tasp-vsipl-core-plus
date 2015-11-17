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
/* $Id: qrdEx.c,v 2.0 2003/02/22 15:46:35 judd Exp $ */

/*
 *  vsip/CORE/CoreExample/exQrd/qrdEx.c
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
 *  created:          august-25-98 (AP)
 *
 *  last update:      october-1-98 (AP)
 *                    made changes to work in development mode
 *                    as well as documentation
 *
 *                    april-13-99 (AP)
 *                    made changes consistent with API changes for saving
 *                    both "skinny" or full Q i.e. Q1 or Q = [Q1 | Q2]
 *
 * -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  
 */

#include<stdio.h>
#include<vsip.h>

#define M 6
#define N 6
#define NN 6
#define NB 6
#define QOPT 2 /* 0 = NOSAVEQ, 1 = SAVEQ, 2 = SAVEQ1 */
#define QPROB  1 /* 0 = COV, 1 = LLSQ */


int main(){vsip_init((void*)0);
{     
    int solretval=0;
    vsip_scalar_vi i,j;
    vsip_mview_d *A  = vsip_mcreate_d(M, N,VSIP_COL,0); 
    vsip_mview_d *X  = vsip_mcreate_d(M,NB,VSIP_ROW,0);
	    
    /* Nullify the data-space */
    for (i=0; i <  vsip_mgetcollength_d(A); i++)
      for(j=0; j < vsip_mgetrowlength_d(A); j++)
	vsip_mput_d(A,i,j,(double)0);

    for (i=0; i <  vsip_mgetcollength_d(X); i++)
      for(j=0; j <  vsip_mgetrowlength_d(X); j++)
        vsip_mput_d(X,i,j,(double)0);

    /* Initialise matrix A */
     for (i=0; i<M; i++)
      for (j = 0; j < N; j++)
	if(i == j) 
	  vsip_mput_d(A,i,j, (double)(M+1));
	else
	  vsip_mput_d(A,i,j, -1.0); 

    {  /* store data  */

/*      vsip_mput_d(A,0,0,1); vsip_mput_d(A,0,1,2); vsip_mput_d(A,0,2,1); */

/*      vsip_mput_d(A,1,0,3); vsip_mput_d(A,1,1,-1); vsip_mput_d(A,1,2,0); */

/*      vsip_mput_d(A,2,0,2); vsip_mput_d(A,2,1,1); vsip_mput_d(A,2,2,-1); */

/*      vsip_mput_d(A,3,0,1); vsip_mput_d(A,3,1,2); vsip_mput_d(A,3,2,2); */

/*      vsip_mput_d(X,0,0,1); */

/*      vsip_mput_d(X,1,0,2); */

/*      vsip_mput_d(X,2,0,2); */

/*      vsip_mput_d(X,3,0,1); */

    }  
    {int i,j; 
    printf("matrix\n A = [\n");
    for(i=0; i<M; i++)
      {
	for(j=0; j< N; j++) 
	  printf("%9.2f%s",vsip_mget_d(A,i,j),(j == N-1) ? "":",");
        (i==M-1) ? printf(";]\n") : printf(";\n") ; 
      }
    }
  { int j, k; 
    vsip_vview_d *y = NULL;
    vsip_vview_d *x;
    vsip_length L    = NB;
    vsip_length p    = M;
    for(k=0; k<L; k++)
      {
        x  = vsip_mcolview_d(X,k);
	for (j=0; j<p; j++)
	  {
	    y  = vsip_mrowview_d(A,j);
	    vsip_vput_d(x,j,(double)(k+1)*(vsip_vsumval_d(y)));
 	    /* vsip_vput_d(x,j,(vsip_vsumval_d(y)));*/ 
       vsip_vdestroy_d(y);
	  }
        vsip_vdestroy_d(x);
      }
    } 
    {int i,j; 
    printf("rhs matrix\n B = [\n");
    for(i=0; i<NN; i++)
      {
	for(j=0; j<NB; j++) 
	  printf("%9.2f%s",vsip_mget_d(X,i,j),(j == NB-1) ? "":",");
	(i==NN-1) ? printf(";]\n") : printf(";\n") ;
      }
    }
    {vsip_qr_d* qrAop = vsip_qrd_create_d(M,N, QOPT);
    if(qrAop == NULL) exit(1);

    {int i,j;
    if(QOPT == VSIP_QRD_SAVEQ1)
    {
    printf("qrd returns %i\n",vsip_qrd_d(qrAop,A));

      printf("matrix A after factorisation: skinny Q explicitly\n Q1 = [\n");
      for(i= 0; i< M ; i++)
        {
          for(j=0; j< N; j++)
            printf("%8.4f %s",vsip_mget_d(A,i,j),(j == N-1) ? "":",");
                   (i == M - 1) ? printf("]\n") : printf(";\n");
        }
    } else if(QOPT == VSIP_QRD_SAVEQ || QOPT == VSIP_QRD_NOSAVEQ)
    {
      printf("qrd returns %i\n",vsip_qrd_d(qrAop,A));
      printf("matrix A after fact.: R and ");
        (QOPT == VSIP_QRD_SAVEQ) ?  printf("full Q implicitly\n Q/R = [\n") :
                        printf("Q not saved -- ignore LT portion. \n R = [\n");
      for(i= 0; i<M ; i++)
        {
          for(j=0; j< N; j++)
            printf("%9.5f %s",vsip_mget_d(A,i,j),(j == N-1) ? "":",");
                   (i == M - 1) ? printf("]\n") : printf(";\n"); 
        }
    }
    }
    if( QPROB == VSIP_LLS)
    {
       if (QOPT == VSIP_QRD_SAVEQ1 || QOPT == VSIP_QRD_SAVEQ)
       {

	 if((solretval=vsip_qrsol_d(qrAop, QPROB, X)))
	   {
	     printf("Warning -- Least Squares soln returns %i -- Check\n", 
	       solretval);
	     printf("Upper triang. mat. R, possibly singular\n");
	   }
	 else
	   printf("Least Squares soln returns %i\n", solretval);
       }
       else
         {
         printf("Least Squares systems cannot be solved by the NOSAVEQ option --exiting\n");
         exit(1);
         }
       }
    else
      {
      if((solretval=vsip_qrsol_d(qrAop,QPROB, X)))
      {
        printf("Warning -- Covariance soln returns %i -- Check\n",solretval);
        printf("Upper triang. mat. R, possibly singular\n");
      }
      else
      printf("Covariance soln returns %i\n",solretval);

    }
    vsip_qrd_destroy_d(qrAop);
    }

    {int i,j;
    printf("Soln Matrix\n"); 
      for(i=0; i<N; i++)
	{
	  for(j=0; j<NB; j++) 
	    printf("%9.5f%s",vsip_mget_d(X,i,j),(j == NB-1) ? "":",");
	  printf(";\n");
	}
    }

    vsip_malldestroy_d(X);
    vsip_malldestroy_d(A);
    }vsip_finalize((void*)0);return 1;
}
