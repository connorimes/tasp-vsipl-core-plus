/* Created R Judd */
/* Copyright (c) 2006 Randall Judd */
/* MIT style license, see Copyright notice in top level directory */
/* $Id: ccovsol_d.h,v 1.2 2006/05/16 16:45:18 judd Exp $ */

int ccovsol_d() {
   vsip_cmview_d *A = vsip_cmcreate_d(10,6,VSIP_ROW,VSIP_MEM_NONE);
   vsip_cmview_d *BX = vsip_cmcreate_d(6,3,VSIP_ROW,VSIP_MEM_NONE);
   vsip_cmview_d *B = vsip_cmcreate_d(6,3,VSIP_ROW,VSIP_MEM_NONE);
   vsip_cmview_d *X = vsip_cmcreate_d(6,3,VSIP_ROW,VSIP_MEM_NONE);
   vsip_cvview_d *ad = vsip_cmdiagview_d(A,0);
   vsip_vview_d *ad_r = vsip_vrealview_d(ad);
   vsip_vview_d *ad_i = vsip_vimagview_d(ad);
   vsip_cvview_d *ac = vsip_cmcolview_d(A,0);

   vsip_cvview_d *bxr = vsip_cmrowview_d(BX,0);
   
   vsip_cmview_d *AHA = vsip_cmcreate_d(6,6,VSIP_ROW,VSIP_MEM_NONE);
   vsip_cmview_d *AH = vsip_cmcreate_d(6,10,VSIP_ROW,VSIP_MEM_NONE);
   int i;
   vsip_cchol_d *chol = vsip_cchold_create_d(VSIP_TR_LOW,6);
   vsip_cblock_d *ablock = vsip_cblockcreate_d(500,VSIP_MEM_NONE);
   vsip_cmview_d *A1 = vsip_cmbind_d(ablock,200,-3,10,-31,6);
   vsip_cmview_d *BX1 = vsip_cmbind_d(ablock,203,8,6,2,3);
   vsip_cscalar_d a0 = vsip_cmplx_d(0.0,0.0);
   
   vsip_cmfill_d(a0,A);
   vsip_cmfill_d(a0,BX);
   vsip_cmfill_d(a0,AHA);
   
   printf("Test covariance solver vsip_ccovsol_d\n");
   
   /* need to make up some data */
   for(i=0; i<6; i++){
      vsip_cvputoffset_d(ac,i);
      vsip_cvputoffset_d(bxr,i*3); {
         vsip_vview_d *ac_r = vsip_vrealview_d(ac);
         vsip_vview_d *ac_i = vsip_vimagview_d(ac);
         vsip_vview_d *bxr_r = vsip_vrealview_d(bxr);
         vsip_vview_d *bxr_i = vsip_vimagview_d(bxr);
         vsip_vramp_d(.1,(vsip_scalar_d)i/3.0,bxr_r);
         vsip_vramp_d(.1,(vsip_scalar_d)i/4.0,bxr_i);
         vsip_vramp_d(-1.3,1.1,ac_r);
         vsip_vramp_d(+1.3,-1.1,ac_i);
         vsip_vdestroy_d(bxr_r);vsip_vdestroy_d(bxr_i);
         vsip_vdestroy_d(ac_r); vsip_vdestroy_d(ac_i);
      }
   }
   vsip_vramp_d(3,1.2,ad_r);
   vsip_vramp_d(3,-1.2,ad_i);
   vsip_cmherm_d(A,AH);
   vsip_cmprod_d(AH,A,AHA);
   vsip_cmcopy_d_d(BX,B);
   vsip_cmcopy_d_d(BX,BX1);
   vsip_cmcopy_d_d(A,A1);
   
      /* check input data */
   printf("Input data \n");
   printf("A = ");VU_cmprintm_d("4.2",A);
   printf("\nAH * A = ");VU_cmprintm_d("4.2",AHA);
   printf("\nB = ");VU_cmprintm_d("4.2",B);
   
   /* slove using Cholesky and AHA matrix */
   printf("\nSolve using Cholesky and calculated AHA \n (AH * A) X = B \nfor X");
   vsip_cchold_d(chol,AHA);
   vsip_ccholsol_d(chol,BX);
   vsip_cmcopy_d_d(BX,X);
   printf("\nX = ");VU_cmprintm_d("7.5",X);
   
   /* check */
   printf("\ncheck");
   vsip_cmprod_d(AH,A,AHA);
   vsip_cmprod_d(AHA,X,BX);
   printf("\nAHA * X ="); VU_cmprintm_d("4.2",BX);
   vsip_cmsub_d(B,BX,X);
   { 
      float check = (float) vsip_cmmeansqval_d(X);
      if(fabs(check) < .0001)
         printf("check = %f\ncorrect\n",check);
      else
         printf("check = %f\nerror\n",check);
    }
   
   printf("\nsolve using cqrd_d and cqrsol_d with A matrix\n");
   /* slove using cqrsol and A matrix */
   {
      vsip_cqr_d *qr = vsip_cqrd_create_d(vsip_cmgetcollength_d(A),vsip_cmgetrowlength_d(A),VSIP_QRD_NOSAVEQ);
      printf("\nSolve using qr and A\n (AH * A) X = B \nfor X");
      vsip_cqrd_d(qr,A1);
      vsip_cqrsol_d(qr,VSIP_COV,BX);
      vsip_cmcopy_d_d(BX,X);
      printf("\nX = ");VU_cmprintm_d("7.5",X);
   
      /* check */
      printf("\ncheck");
      vsip_cmprod_d(AH,A,AHA);
      vsip_cmprod_d(AHA,X,BX);
      printf("\nAHA * X ="); VU_cmprintm_d("4.2",BX);
      vsip_cmsub_d(B,BX,X);
      { 
         float check = (float) vsip_cmmeansqval_d(X);
         if(fabs(check) < .0001)
            printf("check = %f\ncorrect\n",check);
         else
            printf("check = %f\nerror\n",check);
      }
      vsip_cmcopy_d_d(A,A1);
      vsip_cqrd_destroy_d(qr);
   }
   
   
   /* slove using covsol and A matrix*/
   printf("Solve using ccovsol_d and simple input matrix\n");
   vsip_cmcopy_d_d(B,BX); /* restore BX */
   printf("\nSolve\n (AH * A) X = B \nfor X");
   vsip_ccovsol_d(A,BX);
   vsip_cmcopy_d_d(BX,X);
   printf("\nX = ");VU_cmprintm_d("7.5",X);
   vsip_cmprod_d(AHA,X,BX);
   printf("\nAHA * X ="); VU_cmprintm_d("4.2",BX);
   vsip_cmsub_d(B,BX,X);
   { 
      float check = (float) vsip_cmmeansqval_d(X);
      if(fabs(check) < .0001)
         printf("check = %f\ncorrect\n",check);
      else
         printf("check = %f\nerror\n",check);
    }
   
   /* slove using covsol and A1,BX1 inputs */
   printf("\nSolve using ccovsol_d and nonstandard stride \n (AH * A) X = B \nfor X");
   vsip_ccovsol_d(A1,BX1);
   vsip_cmcopy_d_d(BX1,X);
   printf("\nX = ");VU_cmprintm_d("7.5",X);
   vsip_cmprod_d(AHA,X,BX);
   printf("\nAHA * X ="); VU_cmprintm_d("4.2",BX);
   vsip_cmsub_d(B,BX,X);
   { 
      float check = (float) vsip_cmmeansqval_d(X);
      if(fabs(check) < .0001)
         printf("check = %f\ncorrect\n",check);
      else
         printf("check = %f\nerror\n",check);
   }
   

   vsip_cmdestroy_d(A1);
   vsip_cmdestroy_d(BX1);
   vsip_cblockdestroy_d(ablock);
   vsip_cvdestroy_d(ad);
   vsip_vdestroy_d(ad_r);
   vsip_vdestroy_d(ad_i);
   vsip_cvdestroy_d(ac);
   vsip_cvdestroy_d(bxr);
   vsip_cmdestroy_d(AH);
   vsip_cmalldestroy_d(A);
   vsip_cmalldestroy_d(BX);
   vsip_cmalldestroy_d(X);
   vsip_cmalldestroy_d(B);
   vsip_cmalldestroy_d(AHA);
   vsip_cchold_destroy_d(chol);
   
   return 0;
}
