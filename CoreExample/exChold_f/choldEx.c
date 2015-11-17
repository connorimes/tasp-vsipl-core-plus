
/* Modified RJudd September 20, 1998 */
/* From double to test float version */
/* RJudd April 21, 1998 */
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
/* $Id: choldEx.c,v 2.0 2003/02/22 15:42:03 judd Exp $ */
/* A "feel good" test for lud */
/*
 *  vsip/CORE/CoreExample/exChold/choldEx.c
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
 *  last update:      july-13-98 (AP)
 *                    changed to call functions fitting the spec API.
 *
 * -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - 
 */

#include<vsip.h>

#define N 20
#define M 8
#define UPP_LOW 0

int main(){vsip_init((void*)0);
{
    int i,j, solretval;
    vsip_mview_f *A  = vsip_mcreate_f(N,N,VSIP_COL,0);
    vsip_mview_f *X  = vsip_mcreate_f(N+1,M,VSIP_ROW,0);

     /* Nullify the data-space */
    for (i=0; i <  vsip_mgetcollength_f(A); i++)
      for(j=0; j < vsip_mgetrowlength_f(A); j++)
        vsip_mput_f(A,i,j,(double)0);

    for (i=0; i <  vsip_mgetcollength_f(X); i++)
      for(j=0; j <  vsip_mgetrowlength_f(X); j++)
        vsip_mput_f(X,i,j,(double)0);

    /* Initialise matrix A */
    for (i=0; i<N; i++)
      for (j = 0; j < N; j++)
	if(i == j) 
	  vsip_mput_f(A,i,j, (double)(N+1));
	else
	  vsip_mput_f(A,i,j, -1.0);

    /* print A */
    {int i,j; 
    printf("matrix\n");
    for(i=0; i<N; i++)
      {
	for(j=0; j< N; j++) 
	  printf("%9.2f%s",vsip_mget_f(A,i,j),(j == N-1) ? "":",");
	printf(";\n");
      }
    }
    /* Initialise rhs */
    { int j, k; 
    vsip_vview_f *y = NULL;
    vsip_vview_f *x;
    vsip_length L    = vsip_mgetrowlength_f(X);
    vsip_length m    = vsip_mgetcollength_f(A);
    for(k=0; k<L; k++)
      {
        x  = vsip_mcolview_f(X,k);
	for (j=0; j<m; j++)
	  {
	    y  = vsip_mrowview_f(A,j);
	    vsip_vput_f(x,j,(double)(k+1)*(vsip_vsumval_f(y)));
	    /* vsip_vput_f(x,j,(vsip_vsumval_f(y)));*/
	   vsip_vdestroy_f(y);
	  }
        vsip_vdestroy_f(x);
      }
    }
    /* print rhs matrix */
    {int i,j; 
    printf("rhs matrix\n");
    for(i=0; i<N; i++)
      {
	for(j=0; j<M; j++) 
	  printf("%9.2f%s",vsip_mget_f(X,i,j),(j == M-1) ? "":",");
	printf(";\n");
      }
    }
    {vsip_chol_f* cholAop = vsip_chold_create_f(UPP_LOW,N);
    if(cholAop == NULL) exit(1);
    printf("chold } returns %i\n",vsip_chold_f(cholAop,A));
    {int i,j;
    printf("matrix A after factorisation\n");
    for(i=0; i<N; i++)
      {
	for(j=0; j< N; j++)
	  printf("%9.2f%s",vsip_mget_f(A,i,j),(j == N-1) ? "":",");
	printf(";\n");
      }
    }
    if((solretval=vsip_cholsol_f(cholAop,X)))
    {
      printf("Cholesky sol function returns %i\n",solretval);
      printf("Upper triang. mat R, is possibly singular\n");
    }
    else
    {
      printf("Cholesky sol function returns %i\n",solretval);
    }

    vsip_chold_destroy_f(cholAop);
    }

    {int i,j;
    printf("Soln Matrix\n"); 
    for(i=0; i<N; i++)
      {
	for(j=0; j<M; j++) 
	  printf("%9.2f%s",vsip_mget_f(X,i,j),(j == M-1) ? "":",");
	printf(";\n");
      }
    }

    vsip_malldestroy_f(X);
    vsip_malldestroy_f(A);
    } vsip_finalize((void*)0);return 1;
}
