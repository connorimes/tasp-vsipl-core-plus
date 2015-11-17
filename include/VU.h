/* Created RJudd     */
/* SPAWARSYSCEN D881 */
/* These functions are for testing and general utility */
/* They are not designed to be robust or useful        */
/* for anything except quick and dirty analysis        */
/* they may not be complete. I only wrote what I       */
/* needed for the task at hand                         */
#ifndef _vsip_VU_h
#define _vsip_VU_h
/* read an "indexed" asci data file                   */ 
/* format for vector <index> <value>                  */
/* for matrix <row_index> <col_index> <value>         */
/* for tensor <z_index> <y_index> <x_index> <value>   */
/* for complex <value> is <<real_value> <imag_value>> */
void VU_mreadf_f( FILE*, vsip_mview_f*);
void VU_cmreadf_f( FILE*, vsip_cmview_f*);
void VU_vreadf_f( FILE*, vsip_vview_f*);
void VU_cvreadf_f( FILE*, vsip_cvview_f*);
void VU_mreadf_d( FILE*, vsip_mview_d*);
void VU_cmreadf_d( FILE*, vsip_cmview_d*);
void VU_vreadf_d( FILE*, vsip_vview_d*);
void VU_cvreadf_d( FILE*, vsip_cvview_d*);

/* print something easy to past into matlab */ 
void VU_vprintm_f( char*, vsip_vview_f*); 
void VU_vprintm_d( char*, vsip_vview_d*);
void VU_cvprintm_f( char*, vsip_cvview_f*); 
void VU_cvprintm_d( char*, vsip_cvview_d*);
void VU_vprintm_i( char*, vsip_vview_i*);
void VU_vprintm_si( char*, vsip_vview_si*);

void VU_mprintm_f( char*, vsip_mview_f*); 
void VU_mprintm_d( char*, vsip_mview_d*);
void VU_cmprintm_f( char*, vsip_cmview_f*); 
void VU_cmprintm_d( char*, vsip_cmview_d*);
void VU_mprintm_i( char*, vsip_mview_i*);
void VU_mprintm_si( char*, vsip_mview_si*);

void VU_tprintm_f( char*, vsip_tview_f*); 
void VU_tprintm_d( char*, vsip_tview_d*);
void VU_ctprintm_f( char*, vsip_ctview_f*);
void VU_ctprintm_d( char*, vsip_ctview_d*);
void VU_tprintm_i( char*, vsip_tview_i*);
void VU_tprintm_si( char*, vsip_tview_si*);

void VU_vprintm_vi( char*, vsip_vview_vi*); 
void VU_vprintm_mi( char*, vsip_vview_mi*); 

/* Note no format needed for boolean print */
/* 1 (true) or 0 (false) printed           */
void VU_vprintm_bl( vsip_vview_bl*);
void VU_mprintm_bl( vsip_vview_bl*);

/* A simple timer dependent only on ANSI C */
/* needs time.h                            */
double VU_ansi_c_clock();

/* some macros to set view attibutes */
/* this macro sets the attributes of a vector */
/* o => offset; s => stride l => length */
#define VU_VSET_F(v, o, s, l) { \
   vsip_vattr_f attr; \
   vsip_vgetattrib_f(v,&attr); \
   attr.offset = o; attr.stride = s; attr.length = l; \
   vsip_vputattrib_f(v,&attr);\
}
#define VU_VSET_D(v, o, s, l) { \
   vsip_vattr_d attr; \
   vsip_vgetattrib_d(v,&attr); \
   attr.offset = o; attr.stride = s; attr.length = l; \
   vsip_vputattrib_d(v,&attr);\
}
#define VU_CVSET_F(v, o, s, l) { \
   vsip_cvattr_f attr; \
   vsip_cvgetattrib_f(v,&attr); \
   attr.offset = o; attr.stride = s; attr.length = l; \
   vsip_cvputattrib_f(v,&attr);\
}

#define VU_CVSET_D(v, o, s, l) { \
   vsip_cvattr_d attr; \
   vsip_cvgetattrib_d(v,&attr); \
   attr.offset = o; attr.stride = s; attr.length = l; \
   vsip_cvputattrib_d(v,&attr);\
}

/* This macro sets the attributes of a matrix */ 
/* o => offset; cs => column stride; rs => rowstride; cl =>column length; rl => rowlength */
#define VU_MSET_F(v, o, cs, rs, cl, rl) { \
   vsip_mattr_f attr; \
   vsip_mgetattrib_f(v,&attr); \
   attr.offset = o; attr.row_stride = rs; attr.row_length = rl; \
   attr.col_stride = cs; attr.col_length = cl; \
   vsip_mputattrib_f(v,&attr);\
}

#define VU_MSET_D(v, o, cs, rs, cl, rl) { \
   vsip_mattr_d attr; \
   vsip_mgetattrib_d(v,&attr); \
   attr.offset = o; attr.row_stride = rs; attr.row_length = rl; \
   attr.col_stride = cs; attr.col_length = cl; \
   vsip_mputattrib_d(v,&attr);\
}

#define VU_CMSET_F(v, o, cs, rs, cl, rl) { \
   vsip_cmattr_f attr; \
   vsip_cmgetattrib_f(v,&attr); \
   attr.offset = o; attr.row_stride = rs; attr.row_length = rl; \
   attr.col_stride = cs; attr.col_length = cl; \
   vsip_cmputattrib_f(v,&attr);\
}

#define VU_CMSET_D(v, o, cs, rs, cl, rl) { \
   vsip_cmattr_d attr; \
   vsip_cmgetattrib_d(v,&attr); \
   attr.offset = o; attr.row_stride = rs; attr.row_length = rl; \
   attr.col_stride = cs; attr.col_length = cl; \
   vsip_cmputattrib_d(v,&attr);\
}

/* This macro modivies a view (v2) to be a subview of v1. */
/* NOTE THAT HERE offset, stride are through the view, NOT the block */ 
/* and length(s) must be compliant with the size of the block and the parent view. */
/* v1 is the input view and is not modified. v2 is the output view */
/* and must be defined on the same block as v1. v2 is modified as requested */
/* Note v2's data is NOT a copy of v1's data. v2 references data in v1 since */
/* they are on the same block */

#define VU_VGETSUB_D(v1, v2, o, s, l) { \
   vsip_vattr_d attr; \
   vsip_vgetattrib_d((v1),&attr); \
   attr.offset = attr.offset + o * attr.stride; \
   attr.stride *= s; attr.length = l; \
   vsip_vputattrib_d((v2),&attr);\
}

#define VU_VGETSUB_F(v1, v2, o, s, l) { \
   vsip_vattr_f attr; \
   vsip_vgetattrib_f((v1),&attr); \
   attr.offset = attr.offset + o * attr.stride; \
   attr.stride *= s; attr.length = l; \
   vsip_vputattrib_f((v2),&attr);\
}

#define VU_CVGETSUB_D(v1, v2, o, s, l) { \
   vsip_cvattr_d attr; \
   vsip_cvgetattrib_d((v1),&attr); \
   attr.offset = attr.offset + o * attr.stride; \
   attr.stride *= s; attr.length = l; \
   vsip_cvputattrib_d((v2),&attr);\
}

#define VU_CVGETSUB_F(v1, v2, o, s, l) { \
   vsip_cvattr_f attr; \
   vsip_cvgetattrib_f((v1),&attr); \
   attr.offset = attr.offset + o * attr.stride; \
   attr.stride *= s; attr.length = l; \
   vsip_cvputattrib_f((v2),&attr);\
}

/* same as above but now v1 and v2 are matrix views */
#define VU_MGETSUB_D(v1, v2, i,j, cs,rs, cl,rl) { \
   vsip_mattr_d attr; \
   vsip_mgetattrib_d((v1),&attr); \
   attr.offset = attr.offset + i * attr.col_stride + j * attr.row_stride; \
   attr.row_stride *= rs; attr.col_stride *= cs; \
   attr.row_length = rl; attr.col_length = cl;\
   vsip_mputattrib_d((v2),&attr);\
}

#define VU_MGETSUB_F(v1, v2, i,j, cs,rs, cl,rl) { \
   vsip_mattr_f attr; \
   vsip_mgetattrib_f((v1),&attr); \
   attr.offset = attr.offset + i * attr.col_stride + j * attr.row_stride; \
   attr.row_stride *= rs; attr.col_stride *= cs; \
   attr.row_length = rl; attr.col_length = cl;\
   vsip_mputattrib_f((v2),&attr);\
}

#define VU_CMGETSUB_D(v1, v2, i,j, cs,rs, cl,rl) { \
   vsip_cmattr_d attr; \
   vsip_cmgetattrib_d((v1),&attr); \
   attr.offset = attr.offset + i * attr.col_stride + j * attr.row_stride; \
   attr.row_stride *= rs; attr.col_stride *= cs; \
   attr.row_length = rl; attr.col_length = cl;\
   vsip_cmputattrib_d((v2),&attr);\
}

#define VU_CMGETSUB_F(v1, v2, i,j, cs,rs, cl,rl) { \
   vsip_cmattr_f attr; \
   vsip_cmgetattrib_f((v1),&attr); \
   attr.offset = attr.offset + i * attr.col_stride + j * attr.row_stride; \
   attr.row_stride *= rs; attr.col_stride *= cs; \
   attr.row_length = rl; attr.col_length = cl;\
   vsip_cmputattrib_f((v2),&attr);\
}

/* below we just pass in the input (in_attr) attributes of a matrix. */
/* since in_attr is the original parent attributes then we don't need two matrix views */
/* the idea here is that in_attr can be reapplied to v2 at any time to get back */
/* the original matrix and only one matrix view is required (so IP stands for inplace) */
#define VU_MGETIPSUB_D(in_attr, v2, i,j, cs,rs, cl,rl) { \
   vsip_mattr_d attr = in_attr; \
   attr.offset = attr.offset + i * attr.col_stride + j * attr.row_stride; \
   attr.row_stride *= rs; attr.col_stride *= cs; \
   attr.row_length = rl; attr.col_length = cl;\
   vsip_mputattrib_d((v2),&attr);\
}

#define VU_MGETIPSUB_F(in_attr, v2, i,j, cs,rs, cl,rl) { \
   vsip_mattr_f attr = in_attr; \
   attr.offset = attr.offset + i * attr.col_stride + j * attr.row_stride; \
   attr.row_stride *= rs; attr.col_stride *= cs; \
   attr.row_length = rl; attr.col_length = cl;\
   vsip_mputattrib_f((v2),&attr);\
}

#define VU_CMGETIPSUB_D(in_attr, v2, i,j, cs,rs, cl,rl) { \
   vsip_cmattr_d attr = in_attr; \
   attr.offset = attr.offset + i * attr.col_stride + j * attr.row_stride; \
   attr.row_stride *= rs; attr.col_stride *= cs; \
   attr.row_length = rl; attr.col_length = cl;\
   vsip_cmputattrib_d((v2),&attr);\
}

#define VU_CMGETIPSUB_F(in_attr, v2, i,j, cs,rs, cl,rl) { \
   vsip_cmattr_f attr = in_attr; \
   attr.offset = attr.offset + i * attr.col_stride + j * attr.row_stride; \
   attr.row_stride *= rs; attr.col_stride *= cs; \
   attr.row_length = rl; attr.col_length = cl;\
   vsip_cmputattrib_f((v2),&attr);\
}

/* row and colview of matrix */
/* v1 input matrix view; */
/* v2 output vector view (must be defined on block associated with v1 */
/* Note stride is through row/col of matrix (not block) */

#define VU_MGETROW_F(v1, v2, i,j, s, l) { \
   vsip_mattr_f mattr; vsip_vattr_f vattr; \
   vsip_mgetattrib_f((v1),&mattr); \
   vattr.offset = mattr.offset + i * mattr.col_stride + j * mattr.row_stride; \
   vattr.stride = s * mattr.row_stride; vattr.length = l; \
   vsip_vputattrib_f((v2),&vattr);\
}

#define VU_MGETROW_D(v1, v2, i,j, s, l) { \
   vsip_mattr_d mattr; vsip_vattr_d vattr; \
   vsip_mgetattrib_d((v1),&mattr); \
   vattr.offset = mattr.offset + i * mattr.col_stride + j * mattr.row_stride; \
   vattr.stride = s * mattr.row_stride; vattr.length = l; \
   vsip_vputattrib_d((v2),&vattr);\
}

#define VU_MGETCOL_F(v1, v2, i,j, s, l) { \
   vsip_mattr_f mattr; vsip_vattr_f vattr; \
   vsip_mgetattrib_f((v1),&mattr); \
   vattr.offset = mattr.offset + i * mattr.col_stride + j * mattr.row_stride; \
   vattr.stride = s * mattr.col_stride; vattr.length = l; \
   vsip_vputattrib_f((v2),&vattr);\
}

#define VU_MGETCOL_D(v1, v2, i,j, s, l) { \
   vsip_mattr_d mattr; vsip_vattr_d vattr; \
   vsip_mgetattrib_d((v1),&mattr); \
   vattr.offset = mattr.offset + i * mattr.col_stride + j * mattr.row_stride; \
   vattr.stride = s * mattr.col_stride; vattr.length = l; \
   vsip_vputattrib_d((v2),&vattr);\
}

#define VU_CMGETROW_F(v1, v2, i,j, s, l) { \
   vsip_cmattr_f mattr; vsip_cvattr_f vattr; \
   vsip_cmgetattrib_f((v1),&mattr); \
   vattr.offset = mattr.offset + i * mattr.col_stride + j * mattr.row_stride; \
   vattr.stride = s * mattr.row_stride; vattr.length = l; \
   vsip_cvputattrib_f((v2),&vattr);\
}

#define VU_CMGETROW_D(v1, v2, i,j, s, l) { \
   vsip_cmattr_d mattr; vsip_cvattr_d vattr; \
   vsip_cmgetattrib_d((v1),&mattr); \
   vattr.offset = mattr.offset + i * mattr.col_stride + j * mattr.row_stride; \
   vattr.stride = s * mattr.row_stride; vattr.length = l; \
   vsip_cvputattrib_d((v2),&vattr);\
}

#define VU_CMGETCOL_F(v1, v2, i,j, s, l) { \
   vsip_cmattr_f mattr; vsip_cvattr_f vattr; \
   vsip_cmgetattrib_f((v1),&mattr); \
   vattr.offset = mattr.offset + i * mattr.col_stride + j * mattr.row_stride; \
   vattr.stride = s * mattr.col_stride; vattr.length = l; \
   vsip_cvputattrib_f((v2),&vattr);\
}

#define VU_CMGETCOL_D(v1, v2, i,j, s, l) { \
   vsip_cmattr_d mattr; vsip_cvattr_d vattr; \
   vsip_cmgetattrib_d((v1),&mattr); \
   vattr.offset = mattr.offset + i * mattr.col_stride + j * mattr.row_stride; \
   vattr.stride = s * mattr.col_stride; vattr.length = l; \
   vsip_cvputattrib_d((v2),&vattr);\
}

#endif /*_vsip_VU_h */
