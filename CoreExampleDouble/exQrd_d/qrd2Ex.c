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
/* $Id: qrd2Ex.c,v 2.0 2003/02/22 15:46:35 judd Exp $ */

/*
 *  vsip/CORE/CoreExample/exQrd/qrd2Ex.c
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
 *                    made changes to work in develpment mode
 *                    as well as more documentation.
 *
 *                    april-13-99 (AP)
 *                    made changes consistent with API changes for saving
 *                    both "skinny" or full Q i.e. Q1 or Q = [Q1 | Q2] as well
 *                    as not saving Q and calling appropriate functions resply.
 *
 *                    april-22-99 (AP)
 *                    made Q^h an invalid operation with real Q, only
 *                    Q^t is valid.
 *
 * -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  
 */

#include<vsip.h>

#define M 8
#define N 7
#define NN 8
#define NB 6
#define QOPT 1 /* NOSAVEQ = 0, SAVEQ = 1, SAVEQ1 = 2 */
#define opQ 1  /* NTRANS = 0, TRANS = 1, HERM = 2 */
#define apQ 0  /* LSIDE = 0, RSIDE = 1 */

int main(){vsip_init((void*)0);
{
    int i,j; 
    vsip_mview_d *A  = vsip_mcreate_d(M,N,VSIP_COL,0);
    vsip_mview_d *X  = vsip_mcreate_d(
                       (NN>= M)?NN:M,
                       (NB>=M)?NB:M,
                       VSIP_ROW,0);

    /* put the appropriate row, col lengths of X */
    X = vsip_mputcollength_d(X,NN);
    X = vsip_mputrowlength_d(X,NB);

    /* Initialise matrix A */
    for (i=0; i<M; i++)
      for (j = 0; j < N; j++)
	if(i == j) 
	  vsip_mput_d(A,i,j, (double)(M+1));
	else
	  vsip_mput_d(A,i,j, -1.0);

    {int i,j; 
    printf("matrix\n A = [\n");
    for(i=0; i<M; i++)
      {
	for(j=0; j< N; j++) 
	  printf("%9.2f%s",vsip_mget_d(A,i,j),(j == N-1) ? "":",");
	  (i == M-1)? printf("]\n") : printf(";\n");
      }
    }
    { int j, k; 
    vsip_vview_d *y = NULL;
    vsip_vview_d *x;
    vsip_length L    = NB;
    for(k=0; k<L; k++)
      {
        x  = vsip_mcolview_d(X,k);
	for (j=0; j<vsip_vgetlength_d(x); j++)
	  {
	    y  = vsip_mrowview_d(A,j);
	    vsip_vput_d(x,j,(double)(k+1)*(vsip_vsumval_d(y)));
	   vsip_vdestroy_d(y);
	  }
        vsip_vdestroy_d(x);
      }
    }
    {int i,j; 
    printf("rhs matrix\n C = [\n");
    for(i=0; i<NN; i++)
      {
	for(j=0; j<NB; j++) 
	  printf("%9.2f%s",vsip_mget_d(X,i,j),(j == NB-1) ? "":",");
	 (i == NN - 1) ? printf("]\n") : printf(";\n");
      }
    }
    {vsip_qr_d* qrAop = vsip_qrd_create_d(M,N, QOPT);
    if(qrAop == NULL) exit(1);

    {int i,j;
    if(QOPT == VSIP_QRD_SAVEQ1)
    {
     printf("qrd };returns %i\n",vsip_qrd_d(qrAop,A));
     printf("matrix A after factorisation: skinny Q explicitly\n Q1 = [\n");
      for(i= 0; i< M ; i++)
	{
	  for(j=0; j< N; j++)
	    printf("%9.5f%s",vsip_mget_d(A,i,j),(j == N-1) ? "":",");
	    (i == M - 1) ? printf("]\n") : printf(";\n");
	}
    } else if(QOPT == VSIP_QRD_SAVEQ)
    {
      printf("qrd returns %i\n",vsip_qrd_d(qrAop,A));
      printf("matrix A after factorisation: R + full Q implicitly\n Q/R = [\n");
      for(i= 0; i<M ; i++)
	{
	  for(j=0; j< N; j++)
	    printf("%9.2f%s",vsip_mget_d(A,i,j),(j == N-1) ? "":",");
	  (i == M-1)? printf("]\n") : printf(";\n");
	}
    } else if(QOPT == VSIP_QRD_NOSAVEQ)
      {
	printf("Q is not saved with this option. \n");
	printf("Product with Q is invalid, exiting\n");
	vsip_qrd_destroy_d(qrAop);
	vsip_malldestroy_d(X);
	vsip_malldestroy_d(A);
	exit(1);
      }
    if (opQ == VSIP_MAT_TRANS || opQ == VSIP_MAT_HERM)
    {
      if(apQ == VSIP_MAT_RSIDE) /*  C * Q^t  */
      {
	printf(" This is a product of type C <- C * Q^t \n");
	if(vsip_qrdprodq_d(qrAop,opQ,apQ,X)) 
	{
	  printf("Size not conformal or invalid operation by Q: -- exiting\n");
	  vsip_qrd_destroy_d(qrAop);
	  vsip_malldestroy_d(X);
	  vsip_malldestroy_d(A);
	  exit(1);
	}
	else
	{
          X = vsip_mputrowlength_d(X,M);  
	}
      }
      else  if(apQ == VSIP_MAT_LSIDE)   /* Q^t  * C  */
      {
	if(QOPT == 1)
	  printf(" This is a product of type C <- Q^t * C \n");
	if(QOPT == 2)
	  printf(" This is a product of type C <- Q_1^t * C \n");
	if(vsip_qrdprodq_d(qrAop,opQ,apQ,X))
	{
	  printf("Size not conformal or invalid operation by Q: -- exiting\n");
	  vsip_qrd_destroy_d(qrAop);
	  vsip_malldestroy_d(X);
	  vsip_malldestroy_d(A);
	  exit(1);
	}
	else
	{
	  if(QOPT == 2)
            X = vsip_mputcollength_d(X,N);
	}
      }
    }
    else if (opQ == VSIP_MAT_NTRANS)
    {
      if(apQ == VSIP_MAT_RSIDE)   /* C  * Q */
      {
	printf(" This is a product of type C <- C * Q \n");
	if(vsip_qrdprodq_d(qrAop,opQ,apQ,X))
	{
	  printf("Size not conformal or invalid operation by Q: -- exiting\n");
	  vsip_qrd_destroy_d(qrAop);
	  vsip_malldestroy_d(X);
	  vsip_malldestroy_d(A);
	  exit(1);
	}
	else
	{
          X = vsip_mputrowlength_d(X,N);
	}
      }
      else if(apQ == VSIP_MAT_LSIDE)   /*  Q  *  C  */
      {
        if(QOPT == 1)
          printf(" This is a product of type C <- Q * C \n");
        if(QOPT == 2)
          printf(" This is a product of type C <- Q_1 * C \n");

	if(vsip_qrdprodq_d(qrAop,opQ,apQ,X))
	{
	  printf("Size not conformal or invalid operation by Q: -- exiting\n");
	  vsip_qrd_destroy_d(qrAop);
	  vsip_malldestroy_d(X);
	  vsip_malldestroy_d(A);
	  exit(1);
	}
	else
	{
          X = vsip_mputcollength_d(X,M);
	}
      }
    }
    }
    vsip_qrd_destroy_d(qrAop);
    }

    {int i,j;
    printf("Soln Matrix\n C = [\n"); 
      for(i=0; i< vsip_mgetcollength_d(X); i++)
	{
	  for(j=0; j< vsip_mgetrowlength_d(X); j++) 
	    printf("%8.4f%s",vsip_mget_d(X,i,j),
		(j == vsip_mgetrowlength_d(X)-1) ? "":",");
		(i == vsip_mgetcollength_d(X)-1) ? 
			printf("]\n") : printf(";\n");
	}
    }

    vsip_malldestroy_d(X);
    vsip_malldestroy_d(A);
    } vsip_finalize((void*)0);return 1;
}
