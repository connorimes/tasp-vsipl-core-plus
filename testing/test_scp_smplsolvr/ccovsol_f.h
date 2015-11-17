/* Created R Judd */
/* Copyright (c) 2006 Randall Judd */
/* MIT style license, see Copyright notice in top level directory */
/* $Id: ccovsol_f.h,v 1.2 2006/05/16 16:45:18 judd Exp $ */

int ccovsol_f() {
   vsip_cmview_f *A = vsip_cmcreate_f(10,6,VSIP_ROW,VSIP_MEM_NONE);
   vsip_cmview_f *BX = vsip_cmcreate_f(6,3,VSIP_ROW,VSIP_MEM_NONE);
   vsip_cmview_f *B = vsip_cmcreate_f(6,3,VSIP_ROW,VSIP_MEM_NONE);
   vsip_cmview_f *X = vsip_cmcreate_f(6,3,VSIP_ROW,VSIP_MEM_NONE);
   vsip_cvview_f *ad = vsip_cmdiagview_f(A,0);
   vsip_vview_f *ad_r = vsip_vrealview_f(ad);
   vsip_vview_f *ad_i = vsip_vimagview_f(ad);
   vsip_cvview_f *ac = vsip_cmcolview_f(A,0);

   vsip_cvview_f *bxr = vsip_cmrowview_f(BX,0);
   
   vsip_cmview_f *AHA = vsip_cmcreate_f(6,6,VSIP_ROW,VSIP_MEM_NONE);
   vsip_cmview_f *AH = vsip_cmcreate_f(6,10,VSIP_ROW,VSIP_MEM_NONE);
   int i;
   vsip_cchol_f *chol = vsip_cchold_create_f(VSIP_TR_LOW,6);
   vsip_cblock_f *ablock = vsip_cblockcreate_f(500,VSIP_MEM_NONE);
   vsip_cmview_f *A1 = vsip_cmbind_f(ablock,200,-3,10,-31,6);
   vsip_cmview_f *BX1 = vsip_cmbind_f(ablock,203,8,6,2,3);
   vsip_cscalar_f a0 = vsip_cmplx_f(0.0,0.0);
   
   vsip_cmfill_f(a0,A);
   vsip_cmfill_f(a0,BX);
   vsip_cmfill_f(a0,AHA);
   
   printf("Test covariance solver vsip_ccovsol_f\n");
   
   /* need to make up some data */
   for(i=0; i<6; i++){
      vsip_cvputoffset_f(ac,i);
      vsip_cvputoffset_f(bxr,i*3); {
         vsip_vview_f *ac_r = vsip_vrealview_f(ac);
         vsip_vview_f *ac_i = vsip_vimagview_f(ac);
         vsip_vview_f *bxr_r = vsip_vrealview_f(bxr);
         vsip_vview_f *bxr_i = vsip_vimagview_f(bxr);
         vsip_vramp_f(.1,(vsip_scalar_f)i/3.0,bxr_r);
         vsip_vramp_f(.1,(vsip_scalar_f)i/4.0,bxr_i);
         vsip_vramp_f(-1.3,1.1,ac_r);
         vsip_vramp_f(+1.3,-1.1,ac_i);
         vsip_vdestroy_f(bxr_r);vsip_vdestroy_f(bxr_i);
         vsip_vdestroy_f(ac_r); vsip_vdestroy_f(ac_i);
      }
   }
   vsip_vramp_f(3,1.2,ad_r);
   vsip_vramp_f(3,-1.2,ad_i);
   vsip_cmherm_f(A,AH);
   vsip_cmprod_f(AH,A,AHA);
   vsip_cmcopy_f_f(BX,B);
   vsip_cmcopy_f_f(BX,BX1);
   vsip_cmcopy_f_f(A,A1);
   
      /* check input data */
   printf("Input data \n");
   printf("A = ");VU_cmprintm_f("4.2",A);
   printf("\nAH * A = ");VU_cmprintm_f("4.2",AHA);
   printf("\nB = ");VU_cmprintm_f("4.2",B);
   
   /* slove using Cholesky and AHA matrix */
   printf("\nSolve using Cholesky and calculated AHA \n (AH * A) X = B \nfor X");
   vsip_cchold_f(chol,AHA);
   vsip_ccholsol_f(chol,BX);
   vsip_cmcopy_f_f(BX,X);
   printf("\nX = ");VU_cmprintm_f("7.5",X);
   
   /* check */
   printf("\ncheck");
   vsip_cmprod_f(AH,A,AHA);
   vsip_cmprod_f(AHA,X,BX);
   printf("\nAHA * X ="); VU_cmprintm_f("4.2",BX);
   vsip_cmsub_f(B,BX,X);
   { 
      float check = (float) vsip_cmmeansqval_f(X);
      if(fabs(check) < .0001)
         printf("check = %f\ncorrect\n",check);
      else
         printf("check = %f\nerror\n",check);
    }
   
   printf("\nsolve using cqrd_f and cqrsol_f with A matrix\n");
   /* slove using cqrsol and A matrix */
   {
      vsip_cqr_f *qr = vsip_cqrd_create_f(vsip_cmgetcollength_f(A),vsip_cmgetrowlength_f(A),VSIP_QRD_NOSAVEQ);
      printf("\nSolve using qr and A\n (AH * A) X = B \nfor X");
      vsip_cqrd_f(qr,A1);
      vsip_cqrsol_f(qr,VSIP_COV,BX);
      vsip_cmcopy_f_f(BX,X);
      printf("\nX = ");VU_cmprintm_f("7.5",X);
   
      /* check */
      printf("\ncheck");
      vsip_cmprod_f(AH,A,AHA);
      vsip_cmprod_f(AHA,X,BX);
      printf("\nAHA * X ="); VU_cmprintm_f("4.2",BX);
      vsip_cmsub_f(B,BX,X);
      { 
         float check = (float) vsip_cmmeansqval_f(X);
         if(fabs(check) < .0001)
            printf("check = %f\ncorrect\n",check);
         else
            printf("check = %f\nerror\n",check);
      }
      vsip_cmcopy_f_f(A,A1);
      vsip_cqrd_destroy_f(qr);
   }
   
   
   /* slove using covsol and A matrix*/
   printf("Solve using ccovsol_f and simple input matrix\n");
   vsip_cmcopy_f_f(B,BX); /* restore BX */
   printf("\nSolve\n (AH * A) X = B \nfor X");
   vsip_ccovsol_f(A,BX);
   vsip_cmcopy_f_f(BX,X);
   printf("\nX = ");VU_cmprintm_f("7.5",X);
   vsip_cmprod_f(AHA,X,BX);
   printf("\nAHA * X ="); VU_cmprintm_f("4.2",BX);
   vsip_cmsub_f(B,BX,X);
   { 
      float check = (float) vsip_cmmeansqval_f(X);
      if(fabs(check) < .0001)
         printf("check = %f\ncorrect\n",check);
      else
         printf("check = %f\nerror\n",check);
    }
   
   /* slove using covsol and A1,BX1 inputs */
   printf("\nSolve using ccovsol_f and nonstandard stride \n (AH * A) X = B \nfor X");
   vsip_ccovsol_f(A1,BX1);
   vsip_cmcopy_f_f(BX1,X);
   printf("\nX = ");VU_cmprintm_f("7.5",X);
   vsip_cmprod_f(AHA,X,BX);
   printf("\nAHA * X ="); VU_cmprintm_f("4.2",BX);
   vsip_cmsub_f(B,BX,X);
   { 
      float check = (float) vsip_cmmeansqval_f(X);
      if(fabs(check) < .0001)
         printf("check = %f\ncorrect\n",check);
      else
         printf("check = %f\nerror\n",check);
   }
   

   vsip_cmdestroy_f(A1);
   vsip_cmdestroy_f(BX1);
   vsip_cblockdestroy_f(ablock);
   vsip_cvdestroy_f(ad);
   vsip_vdestroy_f(ad_r);
   vsip_vdestroy_f(ad_i);
   vsip_cvdestroy_f(ac);
   vsip_cvdestroy_f(bxr);
   vsip_cmdestroy_f(AH);
   vsip_cmalldestroy_f(A);
   vsip_cmalldestroy_f(BX);
   vsip_cmalldestroy_f(X);
   vsip_cmalldestroy_f(B);
   vsip_cmalldestroy_f(AHA);
   vsip_cchold_destroy_f(chol);
   
   return 0;
}
