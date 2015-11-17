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
/* $Id: cqrd2Ex.c,v 2.0 2003/02/22 15:37:47 judd Exp $ */

/*
 *  vsip/CORE/CoreExample/exQrd/cqrd2Ex.c
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
 *  created:          june-25-98 (AP) (originally from R.Judds version
 *                    for luEx2.c)
 *  last update:      july 13-98 (AP)
 *                    changed to call functions fitting the spec API
 *
 *                    october-1-98 (AP)
 *                    made changes to work in development mode.
 *
 *                    april-15-99 (AP)
 *                    made changes consistent with API changes for saving
 *                    both "skinny" or full Q i.e. Q1 or Q = [Q1 | Q2] as well
 *                    as not saving Q and calling appropriate functions resply.
 *
 *                    april-22-99 (AP)
 *                    made Q^t an invalid operation for complex Q, only 
 *                    Q^h being valid.
 *
 * -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  
 */

#include<vsip.h>

#define M 8
#define N 8
#define NN 8
#define NB 6
#define QOPT 2 /* NOSAVEQ = 0, SAVEQ = 1, SAVEQ1 = 2 */
#define opQ  0  /* NTRANS = 0, TRANS = 1, HERM = 2*/
#define apQ  0  /* LSIDE = 0, RSIDE = 1 */

int main(){vsip_init((void*)0);
{
    int i,j;
    vsip_cmview_f *A  = vsip_cmcreate_f(M,N,VSIP_COL,0);
    vsip_cmview_f *X  = vsip_cmcreate_f(
                        (NN>= M)?NN:M,
                        (NB>=M)?NB:M,
                        VSIP_ROW,0);

    /* put the appropriate row, col lengths of X */
    /* X = vsip_cmputcollength_f(X,NN);
       X = vsip_cmputrowlength_f(X,NB);*/
    X = vsip_cmputcollength_f(X,M);
    X = vsip_cmputrowlength_f(X,NB);

    /* Initialise matrix A */
    for (i=0; i<M; i++)
      for (j = 0; j < N; j++)
	if(i == j) 
	  vsip_cmput_f(A,i,j,vsip_cmplx_f(M+1, 0));
        else if(i > j)
          vsip_cmput_f(A,i,j, vsip_cmplx_f(1,1));
        else if(i < j)
	  vsip_cmput_f(A,i,j,vsip_cmplx_f(1,-1));

    {int i,j; 
    printf("A matrix\nA = [\n");
    for(i=0; i<M; i++)
      {
	for(j=0; j< N; j++) 
	  printf("%6.2f+%6.2fi%s",
                     vsip_real_f(vsip_cmget_f(A,i,j)),
                     vsip_imag_f(vsip_cmget_f(A,i,j)),(j == N-1) ? "":",");
                   (i == M - 1) ? printf("]\n") : printf(";\n");
      }
    }
    { int j, k; 
    vsip_cvview_f *y = NULL;
    vsip_cvview_f *x;
    vsip_vview_f *yr = NULL, *yi = NULL;

    vsip_length L    = NB;
    for(k=0; k<L; k++)
      {
        x  = vsip_cmcolview_f(X,k);
	for (j=0; j< vsip_cvgetlength_f(x); j++)
	  {
	    y  = vsip_cmrowview_f(A,j);
            yr = vsip_vrealview_f(y);
            yi = vsip_vimagview_f(y);
	    vsip_cvput_f(x,j,vsip_cmplx_f((double)(k+1)*(vsip_vsumval_f(yr)),
                             (float) (k+1)*(vsip_vsumval_f(yi))));
	    /* vsip_vput_f(x,j,(vsip_vsumval_f(y)));*/
	   vsip_cvdestroy_f(y);
           vsip_vdestroy_f(yr);
           vsip_vdestroy_f(yi);
	  }
        vsip_cvdestroy_f(x);
      }
    }
    {int i,j; 
    printf("rhs matrix\n C = [\n");
    for(i=0; i<NN; i++)
      {
	for(j=0; j<NB; j++) 
	  printf("%7.3f+%7.3fi%s",
                     vsip_real_f(vsip_cmget_f(X,i,j)),
                     vsip_imag_f(vsip_cmget_f(X,i,j)),(j == NB-1) ? "":",");
                   (i == NN - 1) ? printf("]\n") : printf(";\n");
      }
    }
    {vsip_cqr_f* qrAop = vsip_cqrd_create_f(M,N, QOPT);
    if(qrAop == NULL) exit(1);

    {int i,j;
    if(QOPT == VSIP_QRD_SAVEQ1)
    {
      printf("qrd returns %i\n",vsip_cqrd_f(qrAop,A));
      printf("matrix A after factorisation: skinny Q explicitly\n Q1 = [\n");
      for(i= 0; i< M ; i++)
	{
	  for(j=0; j< N; j++)
	    printf("%8.4f+%8.4fi%s",
                     vsip_real_f(vsip_cmget_f(A,i,j)),
                     vsip_imag_f(vsip_cmget_f(A,i,j)),(j == N-1) ? "":",");
                   (i == M - 1) ? printf("]\n") : printf(";\n");
	}

    } else if(QOPT == VSIP_QRD_SAVEQ)
    {
      printf("qrd returns %i\n",vsip_cqrd_f(qrAop,A));
      printf("matrix A after fact.: R + full Q implicitly\n Q/R = [\n");
      for(i= 0; i<M ; i++)
	{
	  for(j=0; j< N; j++)
	    printf("%8.4f+%8.4fi%s", 
	               vsip_real_f(vsip_cmget_f(A,i,j)),
                     vsip_imag_f(vsip_cmget_f(A,i,j)),(j == N-1) ? "":",");
                   (i == M - 1) ? printf("]\n") : printf(";\n");
	}
    } else if(QOPT == VSIP_QRD_NOSAVEQ)
      {
        printf("Q is not saved with this option. \n");
        printf("Product with Q is invalid, exiting\n");
        vsip_cqrd_destroy_f(qrAop);
        vsip_cmalldestroy_f(X);
        vsip_cmalldestroy_f(A);
        exit(1);
      }
    }
    if (opQ == VSIP_MAT_HERM || opQ == VSIP_MAT_TRANS)
    {
      if(apQ == VSIP_MAT_RSIDE) /*  C * Q^t  */
      {
	printf(" This is a product of type C <- C * Q^h \n");
	if(vsip_cqrdprodq_f(qrAop,opQ,apQ,X)) 
	{
	  printf("Size not conformal or invalid operation by Q: -- exiting\n");
          vsip_cqrd_destroy_f(qrAop);
          vsip_cmalldestroy_f(X);
          vsip_cmalldestroy_f(A);
	  exit(1);
	}
	else
	{
	  X = vsip_cmputrowlength_f(X,M);
	}
      }
      else  if(apQ == VSIP_MAT_LSIDE)   /* Q^t  * C  */
      {
	if(QOPT == 1)
	  printf(" This is a product of type C <- Q^h * C \n");
	if(QOPT == 2)
          printf(" This is a product of type C <- Q_1^h * C \n");
	if(vsip_cqrdprodq_f(qrAop,opQ,apQ,X))
	{
	  printf("size not conformal or invalid operation by Q: -- exiting\n");
          vsip_cqrd_destroy_f(qrAop);
          vsip_cmalldestroy_f(X);
          vsip_cmalldestroy_f(A);
	  exit(1);
	}
	else
	{
	  if(QOPT == 2)
	    X = vsip_cmputcollength_f(X,N);
	}
      }
    }
    else if (opQ == VSIP_MAT_NTRANS)
    {
      if(apQ == VSIP_MAT_RSIDE)   /* C  * Q */
      {
	printf(" This is a product of type C <- C * Q \n");
	if(vsip_cqrdprodq_f(qrAop,opQ,apQ,X))
	{
	  printf("Size not conformal or invalid operation by Q: -- exiting\n");
          vsip_cqrd_destroy_f(qrAop);
          vsip_cmalldestroy_f(X);
          vsip_cmalldestroy_f(A);
	  exit(1);
	}
	else
	{
	  X = vsip_cmputrowlength_f(X,N);
	}
      }
      else if(apQ == VSIP_MAT_LSIDE)   /*  Q  *  C  */
      {
        if(QOPT == 1)
	  printf(" This is a product of type C <- Q * C \n");
        if(QOPT == 2)
	  printf(" This is a product of type C <- Q_1 * C \n");

	if(vsip_cqrdprodq_f(qrAop,opQ,apQ,X))
	{
	  printf("Size not conformal or invalid operation by Q: -- exiting\n");
          vsip_cqrd_destroy_f(qrAop);
          vsip_cmalldestroy_f(X);
          vsip_cmalldestroy_f(A);
	  exit(1);
	}
	else
	{
	  X = vsip_cmputcollength_f(X,M);
	}
      }
    } 
  
    vsip_cqrd_destroy_f(qrAop);
    }

    {int i,j;
    printf("Soln Matrix\n C = [\n"); 
      for(i=0; i<vsip_cmgetcollength_f(X); i++)
	{
	  for(j=0; j<vsip_cmgetrowlength_f(X); j++) 
	    printf("%8.4f +%8.4fi%s",
                     vsip_real_f(vsip_cmget_f(X,i,j)),
                     vsip_imag_f(vsip_cmget_f(X,i,j)),
		   (j == vsip_cmgetrowlength_f(X)-1) ? "":",");
                   (i == vsip_cmgetcollength_f(X) - 1) ? 
			printf("]\n") : printf(";\n");
	}
    }

    vsip_cmalldestroy_f(X);
    vsip_cmalldestroy_f(A);
    } vsip_finalize((void*)0); return 1;
}
