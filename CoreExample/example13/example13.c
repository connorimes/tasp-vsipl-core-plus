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
/* $Id: example13.c,v 2.0 2003/02/22 15:27:28 judd Exp $ */

#include<vsip.h>
void VU_madd_f(vsip_mview_f* A,
               vsip_mview_f* B,
               vsip_mview_f* C){
  vsip_mattr_f Aa,Ba,Ca; /* Matrix attributes */
  int c_bl = 0;
  vsip_mgetattrib_f(A,&Aa); vsip_mgetattrib_f(B,&Ba);
  vsip_mgetattrib_f(C,&Ca);
  { /* decide if this can be done can done with one vector */
    int check  = (Aa.row_stride < Aa.col_stride) ? 1 : 0;
        check += (Ba.row_stride < Ba.col_stride) ? 1 : 0;
        check += (Ca.row_stride < Ca.col_stride) ? 1 : 0;
    printf("%d\n",check);
    if((check != 3) && (check != 0)){ c_bl = 0;
    } else { 
       vsip_stride A_c, B_c, C_c;
       if(check){
            A_c = Aa.col_stride - Aa.row_stride * (Aa.row_length - 1) , 
            B_c = Ba.col_stride - Ba.row_stride * (Ba.row_length - 1) , 
            C_c = Ca.col_stride - Ca.row_stride * (Ca.row_length - 1) ; 
            if( (A_c == Aa.row_stride) && (B_c == Ba.row_stride) 
                 && (C_c == Ca.row_stride)) c_bl=1;
       } else {
            A_c = Aa.row_stride - Aa.col_stride * (Aa.col_length - 1),
            B_c = Ba.row_stride - Ba.col_stride * (Ba.col_length - 1),
            C_c = Ca.row_stride - Ca.col_stride * (Ca.col_length - 1);
            if( (A_c == Aa.col_stride) && (B_c == Ba.col_stride) 
                 && (C_c == Ca.col_stride)) c_bl=1;
       }
    }
  }
  if(c_bl){ /* everything can be made into a vector */
     vsip_vview_f *a = (Aa.row_stride < Aa.col_stride) ?
                       vsip_mrowview_f(A,0) : vsip_mcolview_f(A,0),
                  *b = (Ba.row_stride < Ba.col_stride) ?
                       vsip_mrowview_f(B,0) : vsip_mcolview_f(B,0),  
                  *c = (Ca.row_stride < Ca.col_stride) ?
                       vsip_mrowview_f(C,0) : vsip_mcolview_f(C,0);
     vsip_length Nlength = Aa.row_length * Aa.col_length;
     vsip_vputlength_f(a,Nlength);vsip_vputlength_f(b,Nlength);
     vsip_vputlength_f(c,Nlength);
     vsip_vadd_f(a,b,c);
     vsip_vdestroy_f(a);vsip_vdestroy_f(b);
     vsip_vdestroy_f(c);
     printf("method 1\n");
  }else{/* add by columns */
     vsip_index i;
     vsip_vview_f *a = vsip_mcolview_f(A,0),
                  *b = vsip_mcolview_f(B,0),
                  *c = vsip_mcolview_f(C,0);
     vsip_offset a_o = Aa.offset,
                 b_o = Ba.offset,
                 c_o = Ca.offset;
     vsip_vadd_f(a,b,c);
     for(i=1; i<Aa.row_length; i++){
       a_o += Aa.row_stride; b_o += Ba.row_stride;
       c_o += Ca.row_stride;
       vsip_vputoffset_f(a,a_o);vsip_vputoffset_f(b,b_o);
       vsip_vputoffset_f(c,c_o);
       vsip_vadd_f(a,b,c);
     }
     vsip_vdestroy_f(a);vsip_vdestroy_f(b);
     vsip_vdestroy_f(c);
     printf("method 2\n");
  }
  return;
}
void VU_mprintm_f(char format[],vsip_mview_f *X)
{ vsip_length RL = vsip_mgetrowlength_f(X),
              CL = vsip_mgetcollength_f(X),
              row,col;
  vsip_scalar_f x;
  printf("[\n");
  for(row=0; row<CL; row++){
    for(col=0; col<RL; col++){
      x=vsip_mget_f(X,row,col);
      printf(format,x,((col==(RL-1)) ? ";" : " "));
    } printf("\n");
  }printf("];\n");
  return;
}
int main(){vsip_init((void*)0);
{   vsip_vview_f *a = vsip_vcreate_f(50,0),
                *b = vsip_vcreate_f(50,0),
                *c = vsip_vcreate_f(50,0);
   vsip_mview_f 
      *A = vsip_mbind_f(vsip_vgetblock_f(a),3,3,3,10,4),
      *B = vsip_mbind_f(vsip_vgetblock_f(b),0,8,3,2,4),
      *C = vsip_mbind_f(vsip_vgetblock_f(c),10,4,3,1,4);
   vsip_vramp_f(0.0,.01,a); vsip_vramp_f(0.0,1.0,b);
   VU_madd_f(A,B,C);
   printf("A = \n");VU_mprintm_f("%5.2f ",A);
   printf("B = \n");VU_mprintm_f("%5.2f ",B);
   printf("A + B = C = \n");VU_mprintm_f("%5.2f ",C);
   vsip_mdestroy_f(A); vsip_mdestroy_f(B);
   vsip_mdestroy_f(C);
   A = vsip_mbind_f(vsip_vgetblock_f(a),3,2,3,6,4),
   B = vsip_mbind_f(vsip_vgetblock_f(b),0,1,3,3,4),
   C = vsip_mbind_f(vsip_vgetblock_f(c),10,1,3,3,4);
   VU_madd_f(A,B,C);
   printf("A = \n");VU_mprintm_f("%5.2f ",A);
   printf("B = \n");VU_mprintm_f("%5.2f ",B);
   printf("A + B = C = \n");VU_mprintm_f("%5.2f ",C);
   vsip_mdestroy_f(A); vsip_mdestroy_f(B);
   vsip_mdestroy_f(C);
   vsip_valldestroy_f(a); vsip_valldestroy_f(b);
   vsip_valldestroy_f(c);
   }vsip_finalize((void*)0);return 0;
}        
