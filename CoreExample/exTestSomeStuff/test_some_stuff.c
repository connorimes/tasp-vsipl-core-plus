/* Created by RJudd */
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
/* $Id: test_some_stuff.c,v 2.0 2003/02/22 16:15:03 judd Exp $ */

/* Test of split, interleaved */
 
#include<stdio.h>
#include<vsip.h>

#define L 7                   /*length*/

int main(){vsip_init((void*)0);
{
    /* create some user data space */
    vsip_scalar_f ud_il[2 * L];
    vsip_scalar_f ud_r[L];
    vsip_scalar_f ud_i[L];
    /* create a vsipl vector of the same size as user data space */
    vsip_cvview_f *a = vsip_cvcreate_f(L,0);
    /* bind the user data to  blocks */
      /* bind interleaved */
    vsip_cblock_f *b_il = vsip_cblockbind_f(ud_il,NULL,L,0);
      /* bind split */
    vsip_cblock_f *b_sp = vsip_cblockbind_f(ud_r,ud_i,L,0);
    vsip_vview_f *r,*i;
    vsip_cvview_f *v_il,*v_sp;
    vsip_vattr_f attr_r;
    vsip_vattr_f attr_i;
    vsip_cblockadmit_f(b_il,VSIP_FALSE);
    vsip_cblockadmit_f(b_sp,VSIP_FALSE);
    v_il = vsip_cvbind_f(b_il,0,1,L);
    v_sp = vsip_cvbind_f(b_sp,0,1,L);
    r = vsip_vrealview_f(v_il);
    i = vsip_vimagview_f(v_il);
    vsip_vgetattrib_f(r,&attr_r);
    vsip_vgetattrib_f(i,&attr_i);
    printf("interleaved\n");
    printf("offsets %li, %li\n",attr_r.offset, attr_i.offset);
    printf("strides %li, %li\n",attr_r.stride, attr_i.stride);
    printf("lengths %li, %li\n",attr_r.length, attr_i.length);
    /* put data in interleaved */
    vsip_vramp_f(0,1,r); /* real = 1, 2, ..., L-1 */
    vsip_vfill_f(1,i);   /* image = 1 */
    vsip_vdestroy_f(r); vsip_vdestroy_f(i);
    r = vsip_vrealview_f(v_sp);
    i = vsip_vimagview_f(v_sp);
    vsip_vgetattrib_f(r,&attr_r);
    vsip_vgetattrib_f(i,&attr_i);
    printf("split\n");
    printf("offsets %li, %li\n",attr_r.offset, attr_i.offset);
    printf("strides %li, %li\n",attr_r.stride, attr_i.stride);
    printf("lengths %li, %li\n",attr_r.length, attr_i.length);
    /* put data in split */
    vsip_vramp_f(0,1,i); /* imag = 1, 2, ..., L-1 */
    vsip_vfill_f(1,r);   /* real = 1 */
    vsip_vdestroy_f(r); vsip_vdestroy_f(i);
    { int i;
      printf("interleaved user data, bound and admitted; v_il\n");
      printf("split user data, bound and admitted; v_sp\n");
      for(i=0; i<L; i++){ printf("v_il %5.2f + %5.2fi  ",(vsip_cvget_f(v_il,i)).r, (vsip_cvget_f(v_il,i)).i);
           printf("v_sp %5.2f + %5.2fi\n",(vsip_cvget_f(v_sp,i)).r, (vsip_cvget_f(v_sp,i)).i);
      }
      vsip_cvcopy_f_f(v_il,a);
      printf("copy v_il to a, print a\n");
      for(i=0; i<L; i++) printf("%5.2f + %5.2fi\n",
                       vsip_real_f(vsip_cvget_f(a,i)), vsip_imag_f(vsip_cvget_f(a,i)));
      vsip_cvcopy_f_f(v_sp,a);
      printf("copy v_sp to a, print a\n");
      for(i=0; i<L; i++) printf("%5.2f + %5.2fi \n",
                       vsip_real_f(vsip_cvget_f(a,i)), vsip_imag_f(vsip_cvget_f(a,i)));
    }
    { printf("We change the interleaved block to split and the split block\n");
      printf("to interleaved by rebinding the user data.\n");
      vsip_scalar_f *d1, *d2;/*change interleaved to split and split to interleaved */
      vsip_cblockrelease_f(b_il,VSIP_TRUE,&d1,&d2);
      vsip_cblockrelease_f(b_sp,VSIP_TRUE,&d1,&d2);
      vsip_cblockrebind_f(b_il,ud_r,ud_i,&d1,&d2);
      vsip_cblockrebind_f(b_sp,ud_il,NULL,&d1,&d2);
      vsip_cblockadmit_f(b_il,VSIP_TRUE);
      vsip_cblockadmit_f(b_sp,VSIP_TRUE);
    }
    { printf( "Check to see if the answers have reversed \n");
      int i; /* check to see if the answers have reversed */
      printf("release and rebind v_il and v_sp in oposite order\n");
      printf("v_il now split, v_sp now interleaved\n");
      for(i=0; i<L; i++){ printf("v_il %5.2f + %5.2fi  ",(vsip_cvget_f(v_il,i)).r, (vsip_cvget_f(v_il,i)).i);
           printf("v_sp %5.2f + %5.2fi\n",(vsip_cvget_f(v_sp,i)).r, (vsip_cvget_f(v_sp,i)).i);
      }  
      vsip_cvcopy_f_f(v_il,a);
      printf("copy v_il to a, print a\n");
      for(i=0; i<L; i++) printf("%5.2f + %5.2fi\n",
                       vsip_real_f(vsip_cvget_f(a,i)), vsip_imag_f(vsip_cvget_f(a,i)));
      vsip_cvcopy_f_f(v_sp,a);
      printf("copy v_sp to a, print a\n");
      for(i=0; i<L; i++) printf("%5.2f + %5.2fi \n",
                       vsip_real_f(vsip_cvget_f(a,i)), vsip_imag_f(vsip_cvget_f(a,i)));
    }
    {
      int i;
      vsip_cvview_f *q = vsip_cvsubview_f(v_il,1,3);
      vsip_cvview_f *s = vsip_cvsubview_f(v_sp,0,3);
      vsip_cvview_f *r = vsip_cvsubview_f(a,0,3);
      vsip_cvputstride_f(q,2);
      vsip_cvputstride_f(s,2);
      vsip_cvmul_f(q,s,r);
      printf("\n");
      printf("Do some subviews, and test mul,add, and sub \n");
      for(i=0; i<3; i++){ printf("(%5.2f + %5.2fi) * (%5.2f + %5.2fi) = %5.2f + %5.2fi\n",
                   vsip_real_f(vsip_cvget_f(q,i)), vsip_imag_f(vsip_cvget_f(q,i)),
                   vsip_real_f(vsip_cvget_f(s,i)), vsip_imag_f(vsip_cvget_f(s,i)),
                   vsip_real_f(vsip_cvget_f(a,i)), vsip_imag_f(vsip_cvget_f(a,i)));
      }
      vsip_cvadd_f(q,s,r);
      printf("\n");
      for(i=0; i<3; i++){ printf("(%5.2f + %5.2fi) + (%5.2f + %5.2fi) = %5.2f + %5.2fi\n",
                   vsip_real_f(vsip_cvget_f(q,i)), vsip_imag_f(vsip_cvget_f(q,i)),
                   vsip_real_f(vsip_cvget_f(s,i)), vsip_imag_f(vsip_cvget_f(s,i)),
                   vsip_real_f(vsip_cvget_f(a,i)), vsip_imag_f(vsip_cvget_f(a,i)));
      }
      vsip_cvsub_f(q,s,r);
      printf("\n");
      for(i=0; i<3; i++){ printf("(%5.2f + %5.2fi) - (%5.2f + %5.2fi) = %5.2f + %5.2fi\n",
                   vsip_real_f(vsip_cvget_f(q,i)), vsip_imag_f(vsip_cvget_f(q,i)),
                   vsip_real_f(vsip_cvget_f(s,i)), vsip_imag_f(vsip_cvget_f(s,i)),
                   vsip_real_f(vsip_cvget_f(a,i)), vsip_imag_f(vsip_cvget_f(a,i)));
      }
      vsip_cvdestroy_f(q);
      vsip_cvdestroy_f(s);
      vsip_cvdestroy_f(r);
    }
    vsip_cvalldestroy_f(a);
    vsip_cvalldestroy_f(v_il);
    vsip_cvalldestroy_f(v_sp);
    } vsip_finalize((void*)0); return 1;
}
/*output*/
