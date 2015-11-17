/* Created RJudd */
/* SPAWARSYSCEN D857 */
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
/* $Id: msubview_d.h,v 2.0 2003/02/22 15:23:34 judd Exp $ */
static void msubview_d(){
   printf("********\nTEST msubview_d\n");
   {
      vsip_scalar_d data[10][4] = { 0,   1,  2,  3, 
                                    10, 11, 12, 13,
                                    20, 21, 22, 23,
                                    30, 31, 32, 33,
                                    40, 41, 42, 43,
                                    50, 51, 52, 53,
                                    60, 61, 62, 63,
                                    70, 71, 72, 73,
                                    80, 81, 82, 83,
                                    90, 91, 92, 93};
      vsip_offset           o = 4;
      vsip_stride          rs = 2, cs = 8;
      vsip_length           m = 10, n = 4;
      vsip_block_d         *b = vsip_blockcreate_d(100,VSIP_MEM_NONE);
      vsip_mview_d         *v = vsip_mbind_d(b,o,cs,m,rs,n);
      vsip_index           si = 2, sj = 1;
      vsip_length          sm = 5, sn = 3;
      vsip_mview_d        *sv = vsip_msubview_d(v,si,sj,sm,sn);
      vsip_scalar_d chk = 0;
      int i,j;
      for(i=0; i< (int)m; i++)
         for(j=0; j< (int)n; j++)
            vsip_mput_d(v,i,j,data[i][j]);
      for(i=0; i< (int)sm; i++)
         for(j=0; j< (int)sn; j++)
            chk += fabs(vsip_mget_d(sv,i,j) - data[si+i][sj+j]);
      (chk > .0001) ?    printf("error \n") :
                         printf("correct \n");
      fflush(stdout);
      vsip_mdestroy_d(sv);
      vsip_malldestroy_d(v);
   }
   return;
}
