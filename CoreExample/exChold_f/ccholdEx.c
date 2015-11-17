/* $Id: ccholdEx.c,v 2.0 2003/02/22 15:42:03 judd Exp $ */
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
   vsip_cchol_f* chol = vsip_cchold_create_f(UPORLO,N);   /* NOTE: UPORLO macro above main() */

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
         #ifdef OBNOXIOUS
         /* make up some reasonably obnoxious data                */
         vsip_scalar_f a = cos(1.5/((j+1)*(i+1)))+sqrt(i*j);
         vsip_scalar_f b = (i + j + 1) * cos(M_PI * a);
         #else
         /* the above was to obnoxious for bigger than about N = 10 */
         /* the following works for N > 100 */
         vsip_scalar_f a = 1; vsip_scalar_f b = 1; 
         #endif
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
   #ifdef OBNOXIOUS
      for(i=0; i<N; i++){
         vsip_cvview_f *aview = vsip_cmrowview_f(A,i);
         vsip_cvrsdiv_f(aview,vsip_cmag_f(vsip_cvmeanval_f(aview)),aview);
         vsip_cvdestroy_f(aview);
      }
   #endif
   printf("Matrix multiply for initialization of A = %f seconds\n",VU_ansi_c_clock() - t0);

   /* print  A                                                      */
   /* we only want to do this if A is something reasonable to print */
   /* selected as an option in the make file                        */
   #ifdef PRINT
      printf("Matrix A =\n");
      VU_cmprintm_f("4.2",A);
      fflush(stdout);
   #endif

   /* initialise rhs                      */
   /* start out with XB = {1,2,3,...,M}   */
   /* calculate what B must be using A    */
   /* then solve to see if we get XB back */
   {  vsip_index i;
      vsip_vview_f *y = vsip_vcreate_f(vsip_cmgetcollength_f(A),VSIP_MEM_NONE);
      vsip_vview_f *x_r,*x_i;
      vsip_cvview_f *x;
      vsip_mview_f *A_r = vsip_mrealview_f(A),
                   *A_i = vsip_mimagview_f(A);
      /* time this */
      t0 = VU_ansi_c_clock();
      for(i=0; i<M; i++){
         vsip_vfill_f((vsip_scalar_f)i+1.0,y);
         x = vsip_cmcolview_f(XB,i);
         x_r = vsip_vrealview_f(x);
         x_i = vsip_vimagview_f(x);
         vsip_mvprod_f(A_r,y,x_r);
         vsip_mvprod_f(A_i,y,x_i);
         vsip_cvdestroy_f(x);
         vsip_vdestroy_f(x_r);
         vsip_vdestroy_f(x_i);
      }
      vsip_mdestroy_f(A_r);
      vsip_mdestroy_f(A_i);
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
      chold_retval = vsip_cchold_f(chol,A);
      printf("time decomp %f\n",VU_ansi_c_clock() - t0);
      printf("decompostion returns %d\n",chold_retval);
   
      /* now do the solution */
      t0 = VU_ansi_c_clock(); /* we want to time the solution */
      cholsol_retval=vsip_ccholsol_f(chol,XB);
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
   vsip_cchold_destroy_f(chol);
   vsip_finalize((void*)0);
   return 1;
}
