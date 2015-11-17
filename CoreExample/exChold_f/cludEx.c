/* $Id: cludEx.c,v 2.0 2003/02/22 15:42:03 judd Exp $ */
/* This should be the same as the ccholdEx example excpept we solve using CLUD instead of CCHOLD */
#include<vsip.h>
#include<VU.h>

/* You can define N to be any number.                          */
/* Be aware that three matrices are created of size N^2        */
/* and a matrix multiply is done with these matrices so memory */
/* usage and/or run time will eventually become obnoxious.     */
#define N 10
#define M 4

/* For best performance if column major chose VSIP_TR_LOW   */
/* if row major chose VSIP_TR_UPP                           */
/* If only the upper or lower part of the matrix is defined */
/* you must use that part                                   */
#define UPORLO VSIP_TR_LOW

int main(){
   int init = vsip_init((void*)0);
   int i,j, cholsol_retval,chold_retval;
   double t0 = VU_ansi_c_clock(); /* for doing some timeing */
   vsip_cscalar_f czero = vsip_cmplx_f((vsip_scalar_f)0.0,(vsip_scalar_f)0.0);
   vsip_cmview_f *A  = vsip_cmcreate_f(N,N,VSIP_COL,0);
   vsip_cmview_f *RU  = vsip_cmcreate_f(N,N,VSIP_COL,0);
   vsip_cmview_f *RL  = vsip_cmcreate_f(N,N,VSIP_COL,0);
   vsip_cmview_f *XB  = vsip_cmcreate_f(N,M,VSIP_ROW,0);
   vsip_clu_f* chol = vsip_clud_create_f(N);   /* NOTE: UPORLO macro above main() */

   /* to make sure we have a valid Positive Symetric define */
   /* an upper triangular (RU) with positive pivots and     */
   /* zero below the main diagonal.                         */
   /* Then initialize RL with hermitian of RU               */
   /* finally create A as the matrix product of RL and RU   */

   /* Initialise matrix RU  */
   /* time this             */
   t0 = VU_ansi_c_clock();
   for (i=0; i<N; i++){
      for(j = i; j < N; j++){
         /* make up some reasonably obnoxious data                */
         vsip_scalar_f a = cos(1.5/((j+1)*(i+1)))+sqrt(i*j);
         vsip_scalar_f b = (i + j + 1) * cos(M_PI * a); 
         if(i == j) /* fill diagonal */
             vsip_cmput_f(RU,i,j, vsip_cmplx_f(sqrt(N) + sqrt(i),0));
         else { /* fill off diagonal */
                vsip_cmput_f(RU,i,j,vsip_cmplx_f(b,a)); 
                vsip_cmput_f(RU,j,i,czero); 
         }
      }
   }
   /* initialize RL */
   vsip_cmherm_f(RU,RL);
   #ifdef PRINT
      VU_cmprintm_f("7.4",RU);
      VU_cmprintm_f("7.4",RL);
   #endif
   printf("Matrix initialize for RU and RL = %f seconds\n",VU_ansi_c_clock() - t0);

   /* initialize A */
   /* this step will take a long time so time it */
   t0 = VU_ansi_c_clock();
   vsip_cmprod_f(RL,RU,A);
   printf("Matrix multiply for initialization of A = %f seconds\n",VU_ansi_c_clock() - t0);

   /* print  A                                                      */
   /* we only want to do this if A is something reasonable to print */
   /* selected as an option in the make file                        */
   #ifdef PRINT
      printf("Matrix A =\n");
      VU_cmprintm_f("7.4",A);
      fflush(stdout);
   #endif

   /* initialise rhs                      */
   /* start out with XB = {1,2,3,...,M}   */
   /* calculate what B must be using A    */
   /* then solve to see if we get XB back */
   {  vsip_index i;
      vsip_cvview_f *y = vsip_cvcreate_f(vsip_cmgetcollength_f(A),VSIP_MEM_NONE);
      vsip_cvview_f *x;
      /* time this */
      t0 = VU_ansi_c_clock();
      for(i=0; i<M; i++){
         vsip_cvfill_f(vsip_cmplx_f((vsip_scalar_f)(i+1),0),y);
         x = vsip_cmcolview_f(XB,i);
         vsip_cmvprod_f(A,y,x);
         vsip_cvdestroy_f(x);
      }
      printf("Matrix init for B = %f seconds\n",VU_ansi_c_clock() - t0);
   }

   /* print  XB                                                      */
   /* we only want to do this if XB is something reasonable to print */
   /* selected as an option in the make file                         */
   #ifdef PRINT
      printf("Matrix B = \n");
      VU_cmprintm_f("7.4",XB);
      fflush(stdout);
   #endif

   if(chol != NULL){
      t0 = VU_ansi_c_clock(); /* we want to time the decomposition */
      chold_retval = vsip_clud_f(chol,A);
      printf("time decomp %f\n",VU_ansi_c_clock() - t0);
      printf("decompostion returns %d\n",chold_retval);
   
      /* now do the solution */
      t0 = VU_ansi_c_clock(); /* we want to time the solution */
      cholsol_retval=vsip_clusol_f(chol,VSIP_MAT_NTRANS,XB);
      printf("time solution %f\n",VU_ansi_c_clock() - t0);
      printf("cholsol returns %d\n",cholsol_retval);

      /* print  XB                                                      */
      /* we only want to do this if XB is something reasonable to print */
      /* selected as an option in the make file; otherwise              */
      /* we print a single row of XB if the matrix is to large since    */
      /* M is usally reasonable. Printed as a column vector             */
      #ifdef PRINT
         printf("Matrix X = \n");
         VU_cmprintm_f("7.4",XB);
         fflush(stdout);
      #else
         {  /* pick a row in the middle */
            vsip_cvview_f *x = vsip_cmrowview_f(XB,N/2);
            printf("This output sould be 1,2,...,M\n");
            VU_cvprintm_f("7.4",x);
            fflush(stdout);
            vsip_cvdestroy_f(x);
         }
      #endif
   } else {
         printf("failed to create cholesky object \n");
   }
   vsip_cmalldestroy_f(XB);
   vsip_cmalldestroy_f(A);
   vsip_cmalldestroy_f(RL);
   vsip_cmalldestroy_f(RU);
   vsip_clud_destroy_f(chol);
   vsip_finalize((void*)0);
   return 1;
}
