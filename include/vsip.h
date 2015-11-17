/* Modified By RJudd */
/* SPAWARSYSCEN D881 */
/* Randall Judd is a US Government Employee.  Work preformed on VSIP
// are part of his official duties.  The US Government has a license
// under these copyrights, and this material may be reproduced and used
// by or for the US Government */
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
/* $Id: vsip.h,v 2.10 2007/04/19 03:27:08 judd Exp $ */
/* Note By RJudd. 
// This header file has been modified, degraded, upgraded, changed
// to fit specification requirements, etc. There have been lot's of changes
// and I have not (and will not) maintained a good log of them. I will try
// to maintain a most recent modification date as part of the RCS Id line above */

/* The original vsip header file was done by Bob Tisdale of Hughes Research
// Lab. This header file does not resemble that one, however the 
// Hughes copyright stuff survives below */
/*
// Copyright (c) Hughes Research Laboratories, Inc. 1997
// A non-exclusive, non-royalty bearing license is hereby granted to all
// persons to copy, modify, distribute and produce derivative works for
// any purpose, provided that this copyright notice and following disclaimer
// appear on all copies.
//
// THIS LICENSE INCLUDES NO WARRANTEES, EXPRESSED OR IMPLIED, WHETHER ORAL
// OR WRITTEN, WITH RESPECT TO THE SOFTWARE OR OTHER MATERIAL, INCLUDING
// BUT NOT LIMITED TO ANY IMPLIED WARRANTIES OF MERCHANTABILITY, OR FITNESS
// FOR A PARTICULAR PURPOSE, OR ARISING FROM A COURSE OF PERFORMANCE, OR
// DEALING, OR FROM USAGE OR TRADE, OR OF NON-INFRINGEMENT OF ANY PATENTS
// OF THIRD PARTIES.
//
// This material is based upon work supported by Ft. Huachuca/DARPA under
// Contract No.  DABT63-96-C-0060.  Any opinions, findings and conclusions
// or recommendations expressed in this material are those of the author(s)
// and do not necessarily reflect the views of Ft. Huachuca/DARPA.
//
// Mar. 28, 1997	Added copyright notice.				*/

#ifndef _vsip_header_h
#define _vsip_header_h 1
#ifndef _vsip_typedefs_h
#define _vsip_typedefs_h 1

#include<stdio.h>
#include<stdlib.h>
#include<float.h>
#include<math.h>
#include<limits.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define VSIP_PI M_PI

/* support flags and hints; enumerated types */
typedef enum {
    VSIP_MEM_NONE          = 0,            /* No Hint           */
    VSIP_MEM_RDONLY        = 1,            /* Read Only         */
    VSIP_MEM_CONST         = 2,            /* Constant          */
    VSIP_MEM_SHARED        = 3,            /* Shared            */
    VSIP_MEM_SHARED_RDONLY = 4,            /* Shared, Read Only */
    VSIP_MEM_SHARED_CONST  = 5             /* Shared, Constant  */
} vsip_memory_hint;

typedef enum {
    VSIP_CMPLX_INTERLEAVED,
    VSIP_CMPLX_SPLIT,
    VSIP_CMPLX_NONE
} vsip_cmplx_mem;

typedef enum{
   VSIP_TVX = 0,    /* X Subvector */
   VSIP_TVY = 1,    /* Y Subvector */
   VSIP_TVZ = 2     /* Z Subvector */
}vsip_tvslice;


typedef enum {
   VSIP_TMYX = 0,   /* Y-X Submatrix */
   VSIP_TMZX = 1,   /* Z-X Submatrix */
   VSIP_TMZY = 2    /* Z-Y Submatrix */
} vsip_tmslice;

typedef enum{
   VSIP_TTRANS_NOP = 0,      /* No transpose            */
   VSIP_TTRANS_YX = 1,       /* Y � X transpose         */
   VSIP_TTRANS_ZY = 2,       /* Z � Y transpose         */
   VSIP_TTRANS_ZX = 3,       /* Z � X transpose         */
   VSIP_TTRANS_YXZY = 4,     /* Y � X & Z � Y transpose */
   VSIP_TTRANS_YXZX = 5      /* Y � X & Z � X transpose */
}vsip_ttrans;

#define VSIP_CMPLX_MEM VSIP_CMPLX_INTERLEAVED

typedef enum {
    VSIP_ROW = 0,
    VSIP_COL = 1 
} vsip_major;

typedef enum {
    VSIP_TRAILING = 0, /* Trailing dimension, C style      */
    VSIP_LEADING = 1   /* Leading dimension, FORTRAN style */
} vsip_tmajor;

/* linalg flags */
typedef enum{
    VSIP_MAT_NTRANS = 0,
    VSIP_MAT_TRANS = 1,
    VSIP_MAT_HERM = 2,
    VSIP_MAT_CONJ = 3
} vsip_mat_op;

typedef enum{
    VSIP_COV = 0,
    VSIP_LLS =1
} vsip_qrd_prob;

typedef enum {
    VSIP_MAT_LSIDE = 0,
    VSIP_MAT_RSIDE =1
} vsip_mat_side;

typedef enum {
    VSIP_QRD_NOSAVEQ = 0,
    VSIP_QRD_SAVEQ  = 1,
    VSIP_QRD_SAVEQ1 = 2
} vsip_qrd_qopt;

typedef enum{
    VSIP_TR_LOW = 0,
    VSIP_TR_UPP = 1
} vsip_mat_uplo;

/* Signal flags */
typedef enum {
    VSIP_FFT_FWD = -1,
    VSIP_FFT_INV = +1
} vsip_fft_dir;

typedef enum {
    VSIP_FFT_IP = 0,
    VSIP_FFT_OP = 1
} vsip_fft_place;

typedef enum {
    VSIP_ALG_SPACE = 0,
    VSIP_ALG_TIME  = 1,
    VSIP_ALG_NOISE = 2
} vsip_alg_hint;

typedef enum {
    VSIP_NONSYM = 0,
    VSIP_SYM_EVEN_LEN_ODD   = 1,
    VSIP_SYM_EVEN_LEN_EVEN  = 2
} vsip_symmetry;

typedef enum {
    VSIP_SUPPORT_FULL  = 0,
    VSIP_SUPPORT_SAME = 1,
    VSIP_SUPPORT_MIN  = 2
} vsip_support_region;

typedef enum {
    VSIP_BIASED = 0,
    VSIP_UNBIASED = 1
} vsip_bias;

typedef enum {
    VSIP_STATE_NO_SAVE = 1,
    VSIP_STATE_SAVE = 2
} vsip_obj_state;

typedef enum {
    VSIP_HIST_RESET = 1,
    VSIP_HIST_ACCUM = 2
} vsip_hist_opt;

/* random number generator flags */
typedef enum {
    VSIP_PRNG = 0,
    VSIP_NPRNG = 1
} vsip_rng;
/* end enumerated types */
/************************************************************************/
/* Boolean type definition						*/
typedef signed int vsip_scalar_bl;
typedef	vsip_scalar_bl	vsip_bool;
#define VSIP_MAX_SCALAR_BL INT_MAX
#define VSIP_FALSE 0
#define VSIP_TRUE !VSIP_FALSE

/*   Index type definitions						*/
typedef unsigned long int vsip_scalar_vi;		/* vector index	*/
typedef struct { vsip_scalar_vi r,c; } vsip_scalar_mi;	/* matrix index	*/
typedef	vsip_scalar_vi vsip_index;
#define VSIP_MAX_SCALAR_VI ULONG_MAX

/* Type for offset, stride and length */
typedef	vsip_scalar_vi	vsip_offset;
typedef	vsip_scalar_vi	vsip_length;
typedef signed long int	vsip_stride;

/*    real scalar type definitions					*/
typedef			double	vsip_scalar_d;
typedef			float	vsip_scalar_f;
typedef   signed	int	vsip_scalar_i;
typedef   signed short	int	vsip_scalar_si;
typedef   unsigned      char	vsip_scalar_uc;

/* vsip_scalar_ue32 should be a 32 bit unsigned int */
/* of exactly 32 bits this is machine dependent     */
/* Used in random number calculation                */
typedef   unsigned      int     vsip_scalar_ue32;

#define	VSIP_MAX_SCALAR_D	  DBL_MAX
#define	VSIP_MAX_SCALAR_F	  FLT_MAX
#define	VSIP_MAX_SCALAR_I	  INT_MAX
#define	VSIP_MAX_SCALAR_SI	  SHRT_MAX

#define	VSIP_MIN_SCALAR_D	  DBL_MIN
#define	VSIP_MIN_SCALAR_F	  FLT_MIN
#define	VSIP_MIN_SCALAR_I	  INT_MIN
#define	VSIP_MIN_SCALAR_SI	  SHRT_MIN

/* complex scalar type definitions					*/
typedef struct { vsip_scalar_d  r, i; } vsip_cscalar_d;
typedef struct { vsip_scalar_f  r, i; } vsip_cscalar_f;

/************************************************************************/
/* Begin incomplete typedefs */
/* Block typedefs */
struct vsip_blockattributes_vi;
typedef struct vsip_blockattributes_vi vsip_block_vi;

struct vsip_blockattributes_mi;
typedef struct vsip_blockattributes_mi vsip_block_mi;

struct vsip_blockattributes_bl;
typedef struct vsip_blockattributes_bl vsip_block_bl;

struct vsip_blockattributes_d;
typedef struct vsip_blockattributes_d vsip_block_d;

struct vsip_cblockattributes_d;
typedef struct vsip_cblockattributes_d vsip_cblock_d;

struct vsip_blockattributes_f;
typedef struct vsip_blockattributes_f vsip_block_f;

struct vsip_cblockattributes_f;
typedef struct vsip_cblockattributes_f vsip_cblock_f;

struct vsip_blockattributes_i;
typedef struct vsip_blockattributes_i vsip_block_i;

struct vsip_blockattributes_si;
typedef struct vsip_blockattributes_si vsip_block_si;

struct vsip_blockattributes_uc;
typedef struct vsip_blockattributes_uc vsip_block_uc;

/* Real vector view typedefs */
struct vsip_vviewattributes_bl;
typedef struct vsip_vviewattributes_bl	vsip_vview_bl;

struct vsip_vviewattributes_vi;
typedef struct vsip_vviewattributes_vi	vsip_vview_vi;

struct vsip_vviewattributes_mi;
typedef struct vsip_vviewattributes_mi	vsip_vview_mi;

struct vsip_vviewattributes_d; 
typedef struct vsip_vviewattributes_d	vsip_vview_d;

struct vsip_vviewattributes_f; 
typedef struct vsip_vviewattributes_f	vsip_vview_f;

struct vsip_vviewattributes_i; 
typedef struct vsip_vviewattributes_i	vsip_vview_i;

struct vsip_vviewattributes_si; 
typedef struct vsip_vviewattributes_si	vsip_vview_si;

struct vsip_vviewattributes_uc; 
typedef struct vsip_vviewattributes_uc	vsip_vview_uc;

/* Real matrix view typedefs */
struct vsip_mviewattributes_d; 
typedef struct vsip_mviewattributes_d	vsip_mview_d;

struct vsip_mviewattributes_f; 
typedef struct vsip_mviewattributes_f	vsip_mview_f;

struct vsip_mviewattributes_bl; 
typedef struct vsip_mviewattributes_bl	vsip_mview_bl;

struct vsip_mviewattributes_i;
typedef struct vsip_mviewattributes_i vsip_mview_i;

struct vsip_mviewattributes_si;
typedef struct vsip_mviewattributes_si vsip_mview_si;

struct vsip_mviewattributes_uc;
typedef struct vsip_mviewattributes_uc vsip_mview_uc;

/* Complex vector view typedefs */
struct vsip_cvviewattributes_d;
typedef struct vsip_cvviewattributes_d	vsip_cvview_d;

struct vsip_cvviewattributes_f;
typedef struct vsip_cvviewattributes_f	vsip_cvview_f;

/* Complex matrix view typedefs */
struct vsip_cmviewattributes_d;
typedef struct vsip_cmviewattributes_d	vsip_cmview_d;

struct vsip_cmviewattributes_f;
typedef struct vsip_cmviewattributes_f	vsip_cmview_f;

/* Random -- Random object type definition */
struct vsip_randobject;
typedef struct vsip_randobject vsip_randstate;

/* linalg -- Linear Algebra object type definitions */
struct vsip_ludattributes_d;
typedef struct vsip_ludattributes_d vsip_lu_d;

struct vsip_ludattributes_f;
typedef struct vsip_ludattributes_f vsip_lu_f;

struct vsip_cludattributes_d;
typedef struct vsip_cludattributes_d vsip_clu_d;

struct vsip_cludattributes_f;
typedef struct vsip_cludattributes_f vsip_clu_f;

typedef struct vsip_choldattributes_d vsip_chol_d;

typedef struct vsip_choldattributes_f vsip_chol_f;

typedef struct vsip_ccholdattributes_d vsip_cchol_d;

typedef struct vsip_ccholdattributes_f vsip_cchol_f;

typedef struct vsip_qrdattributes_d vsip_qr_d;

typedef struct vsip_qrdattributes_f vsip_qr_f;

typedef struct vsip_cqrdattributes_d vsip_cqr_d;

typedef struct vsip_cqrdattributes_f vsip_cqr_f;

/* signal -- Signal Procesing object type definitions */
struct vsip_fftattributes_d;
typedef struct vsip_fftattributes_d vsip_fft_d;

struct vsip_fftattributes_f;
typedef struct vsip_fftattributes_f vsip_fft_f;

struct vsip_fftmattributes_f;
typedef struct vsip_fftmattributes_f vsip_fftm_f;

struct vsip_fftmattributes_d;
typedef struct vsip_fftmattributes_d vsip_fftm_d;

struct vsip_firattributes_f;
typedef struct vsip_firattributes_f vsip_fir_f;

struct vsip_firattributes_d;
typedef struct vsip_firattributes_d vsip_fir_d;

struct vsip_cfirattributes_f;
typedef struct vsip_cfirattributes_f vsip_cfir_f;

struct vsip_cfirattributes_d;
typedef struct vsip_cfirattributes_d vsip_cfir_d;

struct vsip_corr1dattributes_f;
typedef struct vsip_corr1dattributes_f vsip_corr1d_f;

struct vsip_ccorr1dattributes_f;
typedef struct vsip_ccorr1dattributes_f vsip_ccorr1d_f;

struct vsip_corr1dattributes_d;
typedef struct vsip_corr1dattributes_d vsip_corr1d_d;

struct vsip_ccorr1dattributes_d;
typedef struct vsip_ccorr1dattributes_d vsip_ccorr1d_d;

struct vsip_conv1dattributes_f;
typedef struct vsip_conv1dattributes_f vsip_conv1d_f;

struct vsip_conv1dattributes_d;
typedef struct vsip_conv1dattributes_d vsip_conv1d_d;

/* tensor support incomplete typedefs */
struct vsip_tviewattributes_f;
typedef struct vsip_tviewattributes_f vsip_tview_f;

struct vsip_tviewattributes_d;
typedef struct vsip_tviewattributes_d vsip_tview_d;

struct vsip_tviewattributes_i;
typedef struct vsip_tviewattributes_i vsip_tview_i;

struct vsip_tviewattributes_si;
typedef struct vsip_tviewattributes_si vsip_tview_si;

struct vsip_tviewattributes_uc;
typedef struct vsip_tviewattributes_uc vsip_tview_uc;

struct vsip_ctviewattributes_f;
typedef struct vsip_ctviewattributes_f vsip_ctview_f;

struct vsip_ctviewattributes_d;
typedef struct vsip_ctviewattributes_d vsip_ctview_d;



/* End incomplete type definitions */
/************************************************************************/

/* attributes structures */
/* The following are used as arguments to get and put attribute functions */

typedef struct {
       vsip_offset  offset;
       vsip_stride  stride;
       vsip_length  length;
       vsip_block_d* block;
} vsip_vattr_d; /* vector view attributes for double */

typedef struct {
       vsip_offset  offset;
       vsip_stride  stride;
       vsip_length  length;
       vsip_block_f* block;
} vsip_vattr_f; /* vector view attributes for double */

typedef struct {
       vsip_offset  offset;
       vsip_stride  stride;
       vsip_length  length;
       vsip_cblock_d* block;
} vsip_cvattr_d; /* complex vector view attributes for double */

typedef struct {
       vsip_offset  offset;
       vsip_stride  stride;
       vsip_length  length;
       vsip_cblock_f* block;
} vsip_cvattr_f; /* complex vector view attributes for double */

typedef struct {
       vsip_offset  offset;
       vsip_stride  stride;
       vsip_length  length;
       vsip_block_vi* block;
} vsip_vattr_vi; /* vector view attributes for vector index */

typedef struct {
       vsip_offset  offset;
       vsip_stride  stride;
       vsip_length  length;
       vsip_block_mi* block;
} vsip_vattr_mi; /* vector view attributes for vector index */

typedef struct {
       vsip_offset   offset;
       vsip_stride   stride;
       vsip_length   length;
       vsip_block_bl* block;
} vsip_vattr_bl; /* vector view attributes for boolean */

typedef struct {
       vsip_offset   offset;
       vsip_stride   stride;
       vsip_length   length;
       vsip_block_i* block;
} vsip_vattr_i; /* vector view attributes for integer */

typedef struct {
       vsip_offset   offset;
       vsip_stride   stride;
       vsip_length   length;
       vsip_block_si* block;
} vsip_vattr_si; /* vector view attributes for integer */

typedef struct {
       vsip_offset   offset;
       vsip_stride   stride;
       vsip_length   length;
       vsip_block_uc* block;
} vsip_vattr_uc; /* vector view attributes for integer */

typedef struct {
       vsip_offset  offset;
       vsip_stride  row_stride;
       vsip_length  row_length;
       vsip_stride  col_stride;
       vsip_length  col_length;
       vsip_block_d* block;
} vsip_mattr_d; /* matrix view attributes for double */

typedef struct {
       vsip_offset  offset;
       vsip_stride  row_stride;
       vsip_length  row_length;
       vsip_stride  col_stride;
       vsip_length  col_length;
       vsip_block_f* block;
} vsip_mattr_f; /* matrix view attributes for double */

typedef struct {
       vsip_offset  offset;
       vsip_stride  row_stride;
       vsip_length  row_length;
       vsip_stride  col_stride;
       vsip_length  col_length;
       vsip_cblock_d* block;
} vsip_cmattr_d; /* complex matrix attributes for double */

typedef struct {
       vsip_offset  offset;
       vsip_stride  row_stride;
       vsip_length  row_length;
       vsip_stride  col_stride;
       vsip_length  col_length;
       vsip_cblock_f* block;
} vsip_cmattr_f; /* complex matrix attributes for double */

typedef struct {
       vsip_offset  offset;
       vsip_stride  row_stride;
       vsip_length  row_length;
       vsip_stride  col_stride;
       vsip_length  col_length;
       vsip_block_bl* block;
} vsip_mattr_bl; /* complex matrix attributes for double */

typedef struct {
       vsip_offset  offset;
       vsip_stride  row_stride;
       vsip_length  row_length;
       vsip_stride  col_stride;
       vsip_length  col_length;
       vsip_block_i* block;
} vsip_mattr_i; /* complex matrix attributes for double */

typedef struct {
       vsip_offset  offset;
       vsip_stride  row_stride;
       vsip_length  row_length;
       vsip_stride  col_stride;
       vsip_length  col_length;
       vsip_block_si* block;
} vsip_mattr_si; /* complex matrix attributes for double */

typedef struct {
       vsip_offset  offset;
       vsip_stride  row_stride;
       vsip_length  row_length;
       vsip_stride  col_stride;
       vsip_length  col_length;
       vsip_block_uc* block;
} vsip_mattr_uc; /* complex matrix attributes for double */

/* tensor view attribute structures */
typedef struct {
       vsip_offset offset;
       vsip_length z_length;
       vsip_stride z_stride;
       vsip_length y_length;
       vsip_stride y_stride;
       vsip_length x_length;
       vsip_stride x_stride;
       vsip_block_f *block; 
} vsip_tattr_f;

typedef struct {
       vsip_offset offset;
       vsip_length z_length;
       vsip_stride z_stride;
       vsip_length y_length;
       vsip_stride y_stride;
       vsip_length x_length;
       vsip_stride x_stride;
       vsip_block_d *block; 
} vsip_tattr_d;

typedef struct {
       vsip_offset offset;
       vsip_length z_length;
       vsip_stride z_stride;
       vsip_length y_length;
       vsip_stride y_stride;
       vsip_length x_length;
       vsip_stride x_stride;
       vsip_block_i *block; 
} vsip_tattr_i;

typedef struct {
       vsip_offset offset;
       vsip_length z_length;
       vsip_stride z_stride;
       vsip_length y_length;
       vsip_stride y_stride;
       vsip_length x_length;
       vsip_stride x_stride;
       vsip_block_si *block; 
} vsip_tattr_si;

typedef struct {
       vsip_offset offset;
       vsip_length z_length;
       vsip_stride z_stride;
       vsip_length y_length;
       vsip_stride y_stride;
       vsip_length x_length;
       vsip_stride x_stride;
       vsip_block_uc *block; 
} vsip_tattr_uc;

typedef struct {
   vsip_offset offset;
   vsip_length z_length;
   vsip_stride z_stride;
   vsip_length y_length;
   vsip_stride y_stride;
   vsip_length x_length;
   vsip_stride x_stride;
   vsip_cblock_f *block;
} vsip_ctattr_f;

typedef struct {
   vsip_offset offset;
   vsip_length z_length;
   vsip_stride z_stride;
   vsip_length y_length;
   vsip_stride y_stride;
   vsip_length x_length;
   vsip_stride x_stride;
   vsip_cblock_d *block;
} vsip_ctattr_d;


/* linalg attribute structures */
typedef struct{
       vsip_length n;
} vsip_lu_attr_d;

typedef struct{
       vsip_length n;
} vsip_clu_attr_d;

typedef struct{
       vsip_length n;
} vsip_lu_attr_f;

typedef struct{
       vsip_length n;
} vsip_clu_attr_f;

typedef struct {
       vsip_mat_uplo uplo;
       vsip_length n;
}vsip_chol_attr_d;

typedef struct {
       vsip_mat_uplo uplo;
       vsip_length n;
}vsip_chol_attr_f;

typedef struct {
       vsip_mat_uplo uplo;
       vsip_length n;
}vsip_cchol_attr_d;

typedef struct {
       vsip_mat_uplo uplo;
       vsip_length n;
}vsip_cchol_attr_f;

typedef struct {
       vsip_length m;              /* Input Matrix is M by N */
       vsip_length n;
       vsip_qrd_qopt Qopt;         /* Matrix Q is saved/not saved */
}vsip_qr_attr_f;

typedef struct {
       vsip_length m;              /* Input Matrix is M by N */
       vsip_length n;
       vsip_qrd_qopt Qopt;         /* Matrix Q is saved/not saved */
}vsip_qr_attr_d;

typedef struct {
       vsip_length m;              /* Input Matrix is M by N */
       vsip_length n;
       vsip_qrd_qopt Qopt;         /* Matrix Q is saved/not saved */
}vsip_cqr_attr_f;

typedef struct {
       vsip_length m;              /* Input Matrix is M by N */
       vsip_length n;
       vsip_qrd_qopt Qopt;         /* Matrix Q is saved/not saved */
}vsip_cqr_attr_d;

/* signal attributes structures */
typedef struct {
       vsip_scalar_vi input;       /* input length */
       vsip_scalar_vi output;      /* output length */
       vsip_fft_place place;       /* in/out-of-place */
       vsip_scalar_d scale;        /* scale factor */
       vsip_fft_dir dir;           /* Forward or inverse */
} vsip_fft_attr_d;

typedef struct{
       vsip_scalar_vi input;       /* input length */
       vsip_scalar_vi output;      /* output length */
       vsip_fft_place place;       /* in/out-of-place */
       vsip_scalar_f scale;        /* scale factor */
       vsip_fft_dir dir;           /* Forward or inverse */
} vsip_fft_attr_f;

typedef struct{
       vsip_scalar_mi input;       /* input length, M by N */
       vsip_scalar_mi output;      /* output length, P by Q */
       vsip_fft_place place;       /* in/out-of-place */
       vsip_scalar_d scale;        /* scale factor */
       vsip_fft_dir dir;           /* Forward or inverse */
       vsip_major major;           /* By Row/Col */
} vsip_fftm_attr_d;

typedef struct{
       vsip_scalar_mi input;       /* input length, M by N */
       vsip_scalar_mi output;      /* output length, P by Q */
       vsip_fft_place place;       /* in/out-of-place */
       vsip_scalar_f scale;        /* scale factor */
       vsip_fft_dir dir;           /* Forward or inverse */
       vsip_major major;           /* By Row/Col */
} vsip_fftm_attr_f;

typedef struct{
       vsip_scalar_vi kernel_len;    /* Kernel Length */
       vsip_symmetry symm;           /* Kernel symmetry */
       vsip_scalar_vi in_len;        /* Filter input segment length */
       vsip_scalar_vi out_len;       /* filter output segment length */
       vsip_length decimation;
       vsip_obj_state state;
} vsip_fir_attr;

typedef struct{
       vsip_scalar_vi kernel_len;    /* Kernel Length */
       vsip_symmetry symm;           /* Kernel symmetry */
       vsip_scalar_vi in_len;        /* Filter input segment length */
       vsip_scalar_vi out_len;       /* filter output segment length */
       vsip_length decimation;
       vsip_obj_state state;
} vsip_cfir_attr;

typedef struct{
       vsip_scalar_vi ref_len;       /* reference length */
       vsip_scalar_vi data_len;      /* data input length */
       vsip_support_region support;  /* output region of support */
       vsip_scalar_vi lag_len;       /* output (lags) length */
} vsip_corr1d_attr;

typedef struct{
       vsip_scalar_vi kernel_len;
       vsip_symmetry symm;
       vsip_scalar_vi data_len;
       vsip_support_region support;
       vsip_scalar_vi out_len;
       int decimation;
} vsip_conv1d_attr;

#endif /* _vsip_typedefs_h */
#ifndef _vsip_scalar_h
#define _vsip_scalar_h 1

#define vsip_cos_d    cos
#define vsip_sin_d    sin
#define vsip_tan_d    tan
#define vsip_acos_d   acos
#define vsip_asin_d   asin
#define vsip_atan_d   atan
#define vsip_cosh_d   cosh
#define vsip_sinh_d   sinh
#define vsip_tanh_d   tanh
#define vsip_exp_d    exp
#define vsip_log_d    log
#define vsip_log10_d  log10
#define vsip_mag_d    fabs
#define vsip_exp10_d(x) (pow(10,x))
#define vsip_pow_d    pow
#define vsip_atan2_d  atan2
#define vsip_sqrt_d   sqrt
#define vsip_ceil_d   ceil
#define vsip_floor_d  floor
#define vsip_fmod_d(x,y) (vsip_scalar_d)(x - ((long)(x/y))*y)
#define vsip_hypot_d(x,y) (vsip_scalar_d)(sqrt(x * x + y * y))
#define vsip_rsqrt_d(x)   (vsip_scalar_d)(1.0/sqrt(x))
#define vsip_recip_d(x)   (vsip_scalar_d)(1.0/(x))
#define vsip_min_d(x,y) (vsip_scalar_d)((x < y) ? x : y)
#define vsip_max_d(x,y) (vsip_scalar_d)((x < y) ? y : x)

#define vsip_cos_f    (vsip_scalar_f)cos
#define vsip_sin_f    (vsip_scalar_f)sin
#define vsip_tan_f    (vsip_scalar_f)tan
#define vsip_acos_f   (vsip_scalar_f)acos
#define vsip_asin_f   (vsip_scalar_f)asin
#define vsip_atan_f   (vsip_scalar_f)atan
#define vsip_cosh_f   (vsip_scalar_f)cosh
#define vsip_sinh_f   (vsip_scalar_f)sinh
#define vsip_tanh_f   (vsip_scalar_f)tanh
#define vsip_exp_f    (vsip_scalar_f)exp
#define vsip_log_f    (vsip_scalar_f)log
#define vsip_log10_f  (vsip_scalar_f)log10
#define vsip_mag_f    (vsip_scalar_f)fabs
#define vsip_exp10_f(x) (vsip_scalar_f)(pow(10,x))
#define vsip_pow_f    (vsip_scalar_f)pow
#define vsip_atan2_f  (vsip_scalar_f)atan2
#define vsip_sqrt_f   (vsip_scalar_f)sqrt
#define vsip_ceil_f   (vsip_scalar_f)ceil
#define vsip_floor_f  (vsip_scalar_f)floor
#define vsip_fmod_f(x,y) (vsip_scalar_f)(x - ((int)(x/y))*y)
#define vsip_hypot_f(x,y) (vsip_scalar_f)(sqrt(x * x + y * y))
#define vsip_rsqrt_f(x)   (vsip_scalar_f)(1.0/sqrt(x))
#define vsip_recip_f(x)   (vsip_scalar_f)(1.0/(x))
#define vsip_min_f(x,y) (vsip_scalar_f)((x < y) ? x : y)
#define vsip_max_f(x,y) (vsip_scalar_f)((x < y) ? y : x)

/* vsip_scalar_mi */
vsip_scalar_mi (vsip_matindex)(vsip_scalar_vi r, vsip_scalar_vi c);
void (vsip_MATINDEX)(vsip_scalar_vi, vsip_scalar_vi, vsip_scalar_mi*);

#define vsip_rowindex(x) ((x).r)
#define vsip_colindex(x) ((x).c)

/* vsip_random */
vsip_scalar_f (vsip_randu_f)(vsip_randstate*);
vsip_cscalar_f (vsip_crandu_f)(vsip_randstate*);
vsip_scalar_f (vsip_randn_f)(vsip_randstate*);
vsip_cscalar_f (vsip_crandn_f)(vsip_randstate*);
vsip_scalar_d (vsip_randu_d)(vsip_randstate*);
vsip_cscalar_d (vsip_crandu_d)(vsip_randstate*);
vsip_scalar_d (vsip_randn_d)(vsip_randstate*);
vsip_cscalar_d (vsip_crandn_d)(vsip_randstate*);

/* vsip_cscalar_d */
#define vsip_real_d(x) ((x).r)
#define vsip_imag_d(x) ((x).i)

vsip_cscalar_d (vsip_cmplx_d)(vsip_scalar_d x, vsip_scalar_d y);
vsip_cscalar_d (vsip_cneg_d)(vsip_cscalar_d x);		
vsip_cscalar_d (vsip_cmul_d)(vsip_cscalar_d x, vsip_cscalar_d y);
vsip_cscalar_d (vsip_rcmul_d)(vsip_scalar_d x, vsip_cscalar_d y);
vsip_cscalar_d (vsip_cdiv_d)(vsip_cscalar_d x, vsip_cscalar_d y);
vsip_cscalar_d (vsip_rcdiv_d)(vsip_scalar_d x, vsip_cscalar_d y);
vsip_cscalar_d (vsip_crdiv_d)(vsip_cscalar_d x, vsip_scalar_d y);
vsip_cscalar_d (vsip_cadd_d)(vsip_cscalar_d x, vsip_cscalar_d y);
vsip_cscalar_d (vsip_rcadd_d)(vsip_scalar_d x, vsip_cscalar_d y);
vsip_cscalar_d (vsip_csub_d)(vsip_cscalar_d x, vsip_cscalar_d y);
vsip_cscalar_d (vsip_rcsub_d)(vsip_scalar_d x, vsip_cscalar_d y);
vsip_cscalar_d (vsip_crsub_d)(vsip_cscalar_d x, vsip_scalar_d y);
vsip_scalar_bl (vsip_cleq_d)(vsip_cscalar_d x, vsip_cscalar_d y);
vsip_scalar_bl (vsip_clne_d)(vsip_cscalar_d x, vsip_cscalar_d y);
vsip_scalar_d (vsip_cmag_d)(vsip_cscalar_d x);			
vsip_scalar_d (vsip_arg_d)(vsip_cscalar_d x);		
vsip_cscalar_d (vsip_conj_d)(vsip_cscalar_d x);		
vsip_scalar_d (vsip_cmagsq_d)(vsip_cscalar_d x);	
vsip_cscalar_d (vsip_cjmul_d)(vsip_cscalar_d x, vsip_cscalar_d y);
void (vsip_polar_d)(vsip_cscalar_d a, vsip_scalar_d* r, vsip_scalar_d* t);
vsip_cscalar_d (vsip_rect_d)(vsip_scalar_d r, vsip_scalar_d t);
vsip_cscalar_d (vsip_cexp_d)(vsip_cscalar_d x);		
vsip_cscalar_d (vsip_clog_d)(vsip_cscalar_d x);		
vsip_cscalar_d (vsip_cexp10_d)(vsip_cscalar_d x);	
vsip_cscalar_d (vsip_clog10_d)(vsip_cscalar_d x);	
vsip_cscalar_d (vsip_csqrt_d)(vsip_cscalar_d x);	
vsip_cscalar_d (vsip_crecip_d)(vsip_cscalar_d x);	
vsip_cscalar_d (vsip_crsqrt_d)(vsip_cscalar_d x);	

#define vsip_CJMUL_f(x,y, z) ((*(z)).r = (x).r * (y).r + (x).i * (y).i); \
                            ((*(z)).i = -(x).r * (y).i + (x).i * (y).r)
#define vsip_CJMUL_d(x,y, z) ((*(z)).r = (x).r * (y).r + (x).i * (y).i); \
                            ((*(z)).i = -(x).r * (y).i + (x).i * (y).r)

#define vsip_CONJ_f(x, y)    ((*(y)).r = (x).r); ((*(y)).i = -(x).i)
#define vsip_CONJ_d(x, y)    ((*(y)).r = (x).r); ((*(y)).i = -(x).i)

#define vsip_CRSUB_f(x,y,z) ((*(z)).r = (x).r - (y)); ((*(z)).i = (x).i)
#define vsip_CRSUB_d(x,y,z) ((*(z)).r = (x).r - (y)); ((*(z)).i = (x).i)

#define vsip_RCSUB_f(x,y,z) ((*(z)).r = -(y).r + (x)); ((*(z)).i = -(y).i)
#define vsip_RCSUB_d(x,y,z) ((*(z)).r = -(y).r + (x)); ((*(z)).i = -(y).i)

#define vsip_RCADD_f(x,y,z) ((*(z)).r = (y).r + (x)); ((*(z)).i = (y).i)
#define vsip_RCADD_d(x,y,z) ((*(z)).r = (y).r + (x)); ((*(z)).i = (y).i)

#define vsip_CMPLX_f(x,y, z) ((*(z)).r = (x)); ((*(z)).i = (y))
#define vsip_CMPLX_d(x,y, z) ((*(z)).r = (x)); ((*(z)).i = (y))

#define vsip_CNEG_f(x, y)    ((*(y)).r = -(x).r); ((*(y)).i = -(x).i)
#define vsip_CNEG_d(x, y)    ((*(y)).r = -(x).r); ((*(y)).i = -(x).i)

#define vsip_CMUL_f(x,y, z) ((*(z)).r = (x).r * (y).r - (x).i * (y).i); \
                            ((*(z)).i = (x).r * (y).i + (x).i * (y).r)
#define vsip_CMUL_d(x,y, z) ((*(z)).r = (x).r * (y).r - (x).i * (y).i); \
                            ((*(z)).i = (x).r * (y).i + (x).i * (y).r)

#define vsip_RCMUL_f(x,y,z) ((*(z)).r = (x) * (y).r); \
                            ((*(z)).i = (x) * (y).i)
#define vsip_RCMUL_d(x,y,z) ((*(z)).r = (x) * (y).r); \
                            ((*(z)).i = (x) * (y).i)

#define vsip_CRDIV_f(x,y,z)  ((*(z)).r = (x).r / (y)); \
                            ((*(z)).i  = (x).i / (y))
#define vsip_CRDIV_d(x,y,z)  ((*(z)).r = (x).r / (y)); \
                            ((*(z)).i  = (x).i / (y))

#define vsip_CADD_f(x,y,z) ((*(z)).r = (x).r + (y).r); \
                            ((*(z)).i = (x).i + (y).i)
#define vsip_CADD_d(x,y,z) ((*(z)).r = (x).r + (y).r); \
                            ((*(z)).i = (x).i + (y).i)

#define vsip_CSUB_f(x,y,z) ((*(z)).r = (x).r - (y).r); \
                            ((*(z)).i = (x).i - (y).i)
#define vsip_CSUB_d(x,y,z) ((*(z)).r = (x).r - (y).r); \
                            ((*(z)).i = (x).i - (y).i)
                            
void (vsip_CDIV_d)(vsip_cscalar_d x, vsip_cscalar_d y, vsip_cscalar_d* z);
void (vsip_RECT_d)(vsip_scalar_d r, vsip_scalar_d t, vsip_cscalar_d* a);
void (vsip_CEXP_d)(vsip_cscalar_d x, vsip_cscalar_d* y);
void (vsip_CLOG_d)(vsip_cscalar_d x, vsip_cscalar_d* y);
void (vsip_CSQRT_d)(vsip_cscalar_d x, vsip_cscalar_d* y);
void (vsip_CRECIP_d)(vsip_cscalar_d x, vsip_cscalar_d* y);

/* vsip_cscalar_f */
#define vsip_real_f(x) ((x).r)
#define vsip_imag_f(x) ((x).i)

vsip_cscalar_f (vsip_cmplx_f)(vsip_scalar_f x, vsip_scalar_f y);
vsip_cscalar_f (vsip_cneg_f)(vsip_cscalar_f x);		
vsip_cscalar_f (vsip_cmul_f)(vsip_cscalar_f x, vsip_cscalar_f y);
vsip_cscalar_f (vsip_rcmul_f)(vsip_scalar_f x, vsip_cscalar_f y);
vsip_cscalar_f (vsip_cdiv_f)(vsip_cscalar_f x, vsip_cscalar_f y);
vsip_cscalar_f (vsip_rcdiv_f)(vsip_scalar_f x, vsip_cscalar_f y);
vsip_cscalar_f (vsip_crdiv_f)(vsip_cscalar_f x, vsip_scalar_f y);
vsip_cscalar_f (vsip_cadd_f)(vsip_cscalar_f x, vsip_cscalar_f y);
vsip_cscalar_f (vsip_rcadd_f)(vsip_scalar_f x, vsip_cscalar_f y);
vsip_cscalar_f (vsip_csub_f)(vsip_cscalar_f x, vsip_cscalar_f y);
vsip_cscalar_f (vsip_rcsub_f)(vsip_scalar_f x, vsip_cscalar_f y);
vsip_cscalar_f (vsip_crsub_f)(vsip_cscalar_f x, vsip_scalar_f y);
vsip_scalar_bl (vsip_cleq_f)(vsip_cscalar_f x, vsip_cscalar_f y);
vsip_scalar_bl (vsip_clne_f)(vsip_cscalar_f x, vsip_cscalar_f y);
vsip_scalar_f (vsip_cmag_f)(vsip_cscalar_f x);			
vsip_scalar_f (vsip_arg_f)(vsip_cscalar_f x);		
vsip_cscalar_f (vsip_conj_f)(vsip_cscalar_f x);		
vsip_scalar_f (vsip_cmagsq_f)(vsip_cscalar_f x);	
vsip_cscalar_f (vsip_cjmul_f)(vsip_cscalar_f x, vsip_cscalar_f y);
void (vsip_polar_f)(vsip_cscalar_f a, vsip_scalar_f* r, vsip_scalar_f* t);
vsip_cscalar_f (vsip_rect_f)(vsip_scalar_f r, vsip_scalar_f t);
vsip_cscalar_f (vsip_cexp_f)(vsip_cscalar_f x);		
vsip_cscalar_f (vsip_clog_f)(vsip_cscalar_f x);		
vsip_cscalar_f (vsip_cexp10_f)(vsip_cscalar_f x);	
vsip_cscalar_f (vsip_clog10_f)(vsip_cscalar_f x);	
vsip_cscalar_f (vsip_csqrt_f)(vsip_cscalar_f x);	
vsip_cscalar_f (vsip_crecip_f)(vsip_cscalar_f x);	
vsip_cscalar_f (vsip_crsqrt_f)(vsip_cscalar_f x);	
void (vsip_CDIV_f)(vsip_cscalar_f x, vsip_cscalar_f y, vsip_cscalar_f* z);
void (vsip_RECT_f)(vsip_scalar_f r, vsip_scalar_f t, vsip_cscalar_f* a);
void (vsip_CEXP_f)(vsip_cscalar_f x, vsip_cscalar_f* y);
void (vsip_CLOG_f)(vsip_cscalar_f x, vsip_cscalar_f* y);
void (vsip_CSQRT_f)(vsip_cscalar_f x, vsip_cscalar_f* y);
void (vsip_CRECIP_f)(vsip_cscalar_f x, vsip_cscalar_f* y);

#endif /* _vsip_scalar_h */
#ifndef _vsip_support_h
#define _vsip_support_h 1

/* Start init/fin */
int vsip_init(
     void*);

int vsip_finalize(
     void*);

/* Start block */

vsip_cmplx_mem (vsip_cstorage)(
     void);
/* vsip_block_vi */
vsip_block_vi* (vsip_blockcreate_vi)(
     size_t, 
     vsip_memory_hint);

vsip_block_vi* (vsip_blockbind_vi)(
     vsip_scalar_vi *p,
     size_t, 
     vsip_memory_hint);

vsip_scalar_vi* (vsip_blockrebind_vi)(  /* rebind */
     vsip_block_vi*,
     vsip_scalar_vi*);

vsip_scalar_vi* (vsip_blockfind_vi)(
     const vsip_block_vi *b);

int  (vsip_blockadmit_vi)(             /* admit */ 
     vsip_block_vi*,
     vsip_scalar_bl);
  
vsip_scalar_vi* (vsip_blockrelease_vi)( /* release */ 
     vsip_block_vi*,
     vsip_scalar_bl); 

void (vsip_blockdestroy_vi)(
     vsip_block_vi *b);

/* vsip_block_mi */
vsip_block_mi* (vsip_blockcreate_mi)(
     size_t,
     vsip_memory_hint);

vsip_block_mi* (vsip_blockbind_mi)(
     vsip_scalar_vi *p,
     size_t,
     vsip_memory_hint);

vsip_scalar_vi* (vsip_blockrebind_mi)(  /* rebind */
     vsip_block_mi*,
     vsip_scalar_vi*);

vsip_scalar_vi* (vsip_blockfind_mi)(
     const vsip_block_mi *b);

int  (vsip_blockadmit_mi)(             /* admit */
     vsip_block_mi*,
     vsip_scalar_bl);
 
vsip_scalar_vi* (vsip_blockrelease_mi)( /* release */
     vsip_block_mi*,
     vsip_scalar_bl);

void (vsip_blockdestroy_mi)(
     vsip_block_mi *b);

/* vsip_block_bl */
vsip_block_bl* (vsip_blockcreate_bl)(
     size_t, 
     vsip_memory_hint);

vsip_block_bl* (vsip_blockbind_bl)(
     vsip_scalar_bl *p,
     size_t, 
     vsip_memory_hint);

vsip_scalar_bl* (vsip_blockrebind_bl)(  /* rebind */
     vsip_block_bl*,
     vsip_scalar_bl*);
 
vsip_scalar_bl* (vsip_blockfind_bl)(
     const vsip_block_bl *b);

int  (vsip_blockadmit_bl)(             /* admit */
     vsip_block_bl*,
     vsip_scalar_bl);

vsip_scalar_bl* (vsip_blockrelease_bl)( /* release */
     vsip_block_bl*,
     vsip_scalar_bl);

void (vsip_blockdestroy_bl)(
     vsip_block_bl *b);

/* vsip_block_d */
vsip_block_d* (vsip_blockcreate_d)(   /* create */
     size_t, 
     vsip_memory_hint);

vsip_block_d* (vsip_blockbind_d)(     /* bind */
     vsip_scalar_d *p,
     size_t, 
     vsip_memory_hint);

vsip_scalar_d* (vsip_blockrebind_d)(  /* rebind */
     vsip_block_d*, 
     vsip_scalar_d*);

vsip_scalar_d* (vsip_blockfind_d)(    /* find */
     const vsip_block_d *b);

int  (vsip_blockadmit_d)(             /* admit */
     vsip_block_d*,
     vsip_scalar_bl);

vsip_scalar_d* (vsip_blockrelease_d)( /* release */
     vsip_block_d*,
     vsip_scalar_bl);

void (vsip_blockdestroy_d)(           /* destroy */
     vsip_block_d *b);

/* vsip_block_f */
vsip_block_f* (vsip_blockcreate_f)(   /* create */
     size_t,
     vsip_memory_hint);
 
vsip_block_f* (vsip_blockbind_f)(     /* bind */
     vsip_scalar_f *p,
     size_t,
     vsip_memory_hint);
 
vsip_scalar_f* (vsip_blockrebind_f)(  /* rebind */
     vsip_block_f*,
     vsip_scalar_f*);
 
vsip_scalar_f* (vsip_blockfind_f)(    /* find */
     const vsip_block_f *b);
 
int  (vsip_blockadmit_f)(             /* admit */
     vsip_block_f*,
     vsip_scalar_bl);
 
vsip_scalar_f* (vsip_blockrelease_f)( /* release */
     vsip_block_f*,
     vsip_scalar_bl);
 
void (vsip_blockdestroy_f)(           /* destroy */
     vsip_block_f *b);
 
/* vsip_cblock_d */
vsip_cblock_d* (vsip_cblockcreate_d)(
     size_t, 
     vsip_memory_hint);

vsip_cblock_d* (vsip_cblockbind_d)(
     vsip_scalar_d *R,vsip_scalar_d *I,
     size_t, 
     vsip_memory_hint);

void (vsip_cblockrebind_d)(
     vsip_cblock_d*, 
     vsip_scalar_d*, vsip_scalar_d*, /* new */
     vsip_scalar_d**, vsip_scalar_d** /* return old */);

void (vsip_cblockfind_d)(
     const vsip_cblock_d *b,
     vsip_scalar_d**, 
     vsip_scalar_d**);

int  (vsip_cblockadmit_d)(
     vsip_cblock_d*,
     vsip_scalar_bl);

void (vsip_cblockrelease_d)(
     vsip_cblock_d*, 
     vsip_scalar_bl,
     vsip_scalar_d**, vsip_scalar_d**);

void (vsip_cblockdestroy_d)(
     vsip_cblock_d *b);

/* vsip_cblock_f */
vsip_cblock_f* (vsip_cblockcreate_f)(
     size_t,
     vsip_memory_hint);

vsip_cblock_f* (vsip_cblockbind_f)(
     vsip_scalar_f *R,vsip_scalar_f *I,
     size_t,
     vsip_memory_hint);

void (vsip_cblockrebind_f)(
     vsip_cblock_f*,
     vsip_scalar_f*, vsip_scalar_f*, /* new */
     vsip_scalar_f**, vsip_scalar_f** /* return old */);

void (vsip_cblockfind_f)(
     const vsip_cblock_f *b,
     vsip_scalar_f**,
     vsip_scalar_f**);

int  (vsip_cblockadmit_f)(
     vsip_cblock_f*,
     vsip_scalar_bl);

void (vsip_cblockrelease_f)(
     vsip_cblock_f*,
     vsip_scalar_bl,
     vsip_scalar_f**, vsip_scalar_f**);

void (vsip_cblockdestroy_f)(
     vsip_cblock_f *b);

/* vsip_block_i */
vsip_block_i* (vsip_blockcreate_i)(
     size_t, 
     vsip_memory_hint);

vsip_block_i* (vsip_blockbind_i)(
     vsip_scalar_i *p,
     size_t, 
     vsip_memory_hint);

vsip_scalar_i* (vsip_blockrebind_i)(
     vsip_block_i*, 
     vsip_scalar_i*);

vsip_scalar_i* (vsip_blockfind_i)(
     const vsip_block_i *b);

int (vsip_blockadmit_i)(
     vsip_block_i*,
     vsip_scalar_bl);

vsip_scalar_i* (vsip_blockrelease_i)(
     vsip_block_i*,
     vsip_scalar_bl);

void (vsip_blockdestroy_i)(
     vsip_block_i *b);

/* vsip_block_si */
vsip_block_si* (vsip_blockcreate_si)(
     size_t,
     vsip_memory_hint);
 
vsip_block_si* (vsip_blockbind_si)(
     vsip_scalar_si *p,
     size_t,
     vsip_memory_hint);
 
vsip_scalar_si* (vsip_blockrebind_si)(
     vsip_block_si*,
     vsip_scalar_si*);
 
vsip_scalar_si* (vsip_blockfind_si)(
     const vsip_block_si *b);
 
int (vsip_blockadmit_si)(
     vsip_block_si*,
     vsip_scalar_bl);
 
vsip_scalar_si* (vsip_blockrelease_si)(
     vsip_block_si*,
     vsip_scalar_bl);
 
void (vsip_blockdestroy_si)(
     vsip_block_si *b);
 
/* end block */
/********************************************************************/

/* vsip_block_uc */
vsip_block_uc* (vsip_blockcreate_uc)(
     size_t,
     vsip_memory_hint);
 
vsip_block_uc* (vsip_blockbind_uc)(
     vsip_scalar_uc *p,
     size_t,
     vsip_memory_hint);
 
vsip_scalar_uc* (vsip_blockrebind_uc)(
     vsip_block_uc*,
     vsip_scalar_uc*);
 
vsip_scalar_uc* (vsip_blockfind_uc)(
     const vsip_block_uc *b);
 
int (vsip_blockadmit_uc)(
     vsip_block_uc*,
     vsip_scalar_bl);
 
vsip_scalar_uc* (vsip_blockrelease_uc)(
     vsip_block_uc*,
     vsip_scalar_bl);
 
void (vsip_blockdestroy_uc)(
     vsip_block_uc *b);
 
/* end block */
/********************************************************************/
/* vector */
/* vsip_vview_vi */
vsip_vview_vi* (vsip_vcreate_vi)(
     vsip_length n, vsip_memory_hint); 

vsip_vview_vi* (vsip_vcloneview_vi)(
     const vsip_vview_vi*);

vsip_vview_vi* (vsip_vbind_vi)(
     const vsip_block_vi*, 
     vsip_offset, vsip_stride, vsip_length);

vsip_block_vi* (vsip_vdestroy_vi)(
     vsip_vview_vi*);

void (vsip_valldestroy_vi)(
     vsip_vview_vi*);

vsip_vview_vi* (vsip_vsubview_vi)(
     const vsip_vview_vi*, 
     vsip_index, 
     vsip_length);

vsip_block_vi* (vsip_vgetblock_vi)(
     const vsip_vview_vi*);

vsip_offset (vsip_vgetoffset_vi)(
     const vsip_vview_vi*);

vsip_stride (vsip_vgetstride_vi)(
     const vsip_vview_vi*);

vsip_length (vsip_vgetlength_vi)(
     const vsip_vview_vi*);

void (vsip_vgetattrib_vi)(
     const vsip_vview_vi*,
     vsip_vattr_vi*);

vsip_scalar_vi (vsip_vget_vi)(
     const vsip_vview_vi*, vsip_index);

vsip_vview_vi* (vsip_vputoffset_vi)(
     vsip_vview_vi*, vsip_offset);

vsip_vview_vi* (vsip_vputstride_vi)(
     vsip_vview_vi*, vsip_stride);

vsip_vview_vi* (vsip_vputlength_vi)(
     vsip_vview_vi*, vsip_length);

vsip_vview_vi* (vsip_vputattrib_vi)( 
     vsip_vview_vi*,
     const vsip_vattr_vi*);

void (vsip_vput_vi)(
     const vsip_vview_vi*,
     vsip_index, 
     vsip_scalar_vi);

/* vsip_vview_mi */
vsip_vview_mi* (vsip_vcreate_mi)(
  vsip_length, vsip_memory_hint);

vsip_vview_mi* (vsip_vcloneview_mi)(
  const vsip_vview_mi*);

vsip_vview_mi* (vsip_vbind_mi)(
     const vsip_block_mi*, 
     vsip_offset, 
     vsip_stride, 
     vsip_length);

vsip_block_mi* (vsip_vdestroy_mi)(
     vsip_vview_mi*);

void (vsip_valldestroy_mi)(
     vsip_vview_mi*);

vsip_vview_mi* (vsip_vsubview_mi)(
     const vsip_vview_mi*, 
     vsip_index, 
     vsip_length);

vsip_block_mi* (vsip_vgetblock_mi)(
     const vsip_vview_mi*);

vsip_offset (vsip_vgetoffset_mi)(
     const vsip_vview_mi*);

vsip_stride (vsip_vgetstride_mi)(
     const vsip_vview_mi*);

vsip_length (vsip_vgetlength_mi)(
     const vsip_vview_mi*);

void (vsip_vgetattrib_mi)(
     const vsip_vview_mi*,
     vsip_vattr_mi*);

vsip_scalar_mi (vsip_vget_mi)(
     const vsip_vview_mi*, 
     vsip_index);

vsip_vview_mi* (vsip_vputoffset_mi)(
     vsip_vview_mi*, 
     vsip_offset);

vsip_vview_mi* (vsip_vputstride_mi)(
     vsip_vview_mi*, 
     vsip_stride);

vsip_vview_mi* (vsip_vputlength_mi)(
     vsip_vview_mi*, 
     vsip_length);

vsip_vview_mi* (vsip_vputattrib_mi)(
     vsip_vview_mi*,
     const vsip_vattr_mi*);

void (vsip_vput_mi)(
     const vsip_vview_mi*,
     vsip_index, 
     vsip_scalar_mi);

vsip_vview_vi* vsip_vrowindices_mi(
     const vsip_vview_mi*);

vsip_vview_vi* vsip_vcolindices_mi(
     const vsip_vview_mi*);

void (vsip_vmatindices_mi)(
     const vsip_vview_vi*,
     const vsip_vview_vi*,
     const vsip_vview_mi*);

/* vsip_vview_bl */
vsip_vview_bl* (vsip_vcreate_bl)(
  vsip_length, 
vsip_memory_hint);

vsip_vview_bl* (vsip_vcloneview_bl)(
  const vsip_vview_bl*);

vsip_vview_bl* (vsip_vbind_bl)(
  const vsip_block_bl*, 
     vsip_offset, 
     vsip_stride, 
     vsip_length);

vsip_block_bl* (vsip_vdestroy_bl)(
     vsip_vview_bl*);

void (vsip_valldestroy_bl)(
     vsip_vview_bl*);

vsip_vview_bl* (vsip_vsubview_bl)(
     const vsip_vview_bl*, 
     vsip_index, 
     vsip_length);

vsip_block_bl* (vsip_vgetblock_bl)(
     const vsip_vview_bl*);

vsip_offset (vsip_vgetoffset_bl)(
     const vsip_vview_bl*);

vsip_stride (vsip_vgetstride_bl)(
     const vsip_vview_bl*);

vsip_length (vsip_vgetlength_bl)(
     const vsip_vview_bl*);

void (vsip_vgetattrib_bl) (
     const vsip_vview_bl*,
     vsip_vattr_bl*);

vsip_scalar_bl (vsip_vget_bl)(
     const vsip_vview_bl*, 
     vsip_index);

vsip_vview_bl* (vsip_vputoffset_bl)(
     vsip_vview_bl*, vsip_offset);

vsip_vview_bl* (vsip_vputstride_bl)(
     vsip_vview_bl*, vsip_stride);

vsip_vview_bl* (vsip_vputlength_bl)(
     vsip_vview_bl*, vsip_length);

vsip_vview_bl* (vsip_vputattrib_bl)(
     vsip_vview_bl*,
     const vsip_vattr_bl*);

vsip_index vsip_vfirst_f(
     vsip_index,
     vsip_bool(*)(
          vsip_scalar_f, 
          vsip_scalar_f),
     const vsip_vview_f*,
     const vsip_vview_f*);

vsip_index vsip_vfirst_d(
     vsip_index,
     vsip_bool(*)(
          vsip_scalar_d, 
          vsip_scalar_d),
     const vsip_vview_d*,
     const vsip_vview_d*);

vsip_index vsip_vfirst_i(
     vsip_index,
     vsip_bool(*)(
          vsip_scalar_i, 
          vsip_scalar_i),
     const vsip_vview_i*,
     const vsip_vview_i*);

vsip_index vsip_vfirst_bl(
     vsip_index,
     vsip_bool(*)(
          vsip_scalar_bl, 
          vsip_scalar_bl),
     const vsip_vview_bl*,
     const vsip_vview_bl*);

vsip_index vsip_vfirst_vi(
     vsip_index,
     vsip_bool(*)(
          vsip_scalar_vi, 
          vsip_scalar_vi),
     const vsip_vview_vi*,
     const vsip_vview_vi*);

vsip_index vsip_vfirst_mi(
     vsip_index,
     vsip_bool(*)(
          vsip_scalar_mi, 
          vsip_scalar_mi),
     const vsip_vview_mi*,
     const vsip_vview_mi*);

void (vsip_vput_bl)(
     const vsip_vview_bl*,
     vsip_index, 
     vsip_scalar_bl);

/* vsip_vview_d */
vsip_vview_d* (vsip_vcreate_d)(
     vsip_length, 
     vsip_memory_hint);

vsip_vview_d* (vsip_vcloneview_d)(
     const vsip_vview_d*);

vsip_vview_d* (vsip_vbind_d)(
     const vsip_block_d*, 
     vsip_offset, 
     vsip_stride, 
     vsip_length);

vsip_block_d* (vsip_vdestroy_d)(
     vsip_vview_d*);

void (vsip_valldestroy_d)(
     vsip_vview_d*);

vsip_vview_d* (vsip_vsubview_d)(
     const vsip_vview_d*, 
     vsip_index, 
     vsip_length);

vsip_block_d* (vsip_vgetblock_d)(
     const vsip_vview_d*);

vsip_offset (vsip_vgetoffset_d)(
     const vsip_vview_d*);

vsip_stride (vsip_vgetstride_d)(
     const vsip_vview_d*);

vsip_length (vsip_vgetlength_d)(
     const vsip_vview_d*);

void (vsip_vgetattrib_d)(
     const vsip_vview_d*,
     vsip_vattr_d*);

vsip_scalar_d (vsip_vget_d)(
     const vsip_vview_d*, 
     vsip_index);

vsip_vview_d* (vsip_vputoffset_d)(
     vsip_vview_d*, 
     vsip_offset);

vsip_vview_d* (vsip_vputstride_d)(
     vsip_vview_d*, 
     vsip_stride);

vsip_vview_d* (vsip_vputlength_d)(
     vsip_vview_d*, 
     vsip_length);

vsip_vview_d* (vsip_vputattrib_d)(
     vsip_vview_d*,
     const vsip_vattr_d*);

void (vsip_vput_d)(
     const vsip_vview_d*,
     vsip_index, 
     vsip_scalar_d);

/* vsip_vview_f */
vsip_vview_f* (vsip_vcreate_f)(
     vsip_length, 
     vsip_memory_hint);

vsip_vview_f* (vsip_vcloneview_f)(
     const vsip_vview_f*);

vsip_vview_f* (vsip_vbind_f)(
     const vsip_block_f*, 
     vsip_offset, 
     vsip_stride, 
     vsip_length);

vsip_block_f* (vsip_vdestroy_f)(
     vsip_vview_f*);

void (vsip_valldestroy_f)(
     vsip_vview_f*);

vsip_vview_f* (vsip_vsubview_f)(
     const vsip_vview_f*, 
     vsip_index, 
     vsip_length);

vsip_block_f* (vsip_vgetblock_f)(
     const vsip_vview_f*);

vsip_offset (vsip_vgetoffset_f)(
     const vsip_vview_f*);

vsip_stride (vsip_vgetstride_f)(
     const vsip_vview_f*);

vsip_length (vsip_vgetlength_f)(
     const vsip_vview_f*);

void (vsip_vgetattrib_f)(
     const vsip_vview_f*,
     vsip_vattr_f*);

vsip_scalar_f (vsip_vget_f)(
     const vsip_vview_f*, 
     vsip_index);

vsip_vview_f* (vsip_vputoffset_f)(
     vsip_vview_f*, 
     vsip_offset);

vsip_vview_f* (vsip_vputstride_f)(
     vsip_vview_f*, 
     vsip_stride);

vsip_vview_f* (vsip_vputlength_f)(
     vsip_vview_f*, 
     vsip_length);

vsip_vview_f* (vsip_vputattrib_f)(
     vsip_vview_f*,
     const vsip_vattr_f*);

void (vsip_vput_f)(
     const vsip_vview_f*,
     vsip_index, 
     vsip_scalar_f);


/* vsip_vview_i & vsip_mview_i */
vsip_vview_i* (vsip_vcreate_i)(
     vsip_length, 
     vsip_memory_hint);

vsip_vview_i* (vsip_vcloneview_i)(
     const vsip_vview_i*);

vsip_vview_i* (vsip_vbind_i)(
     const vsip_block_i*, 
     vsip_offset, 
     vsip_stride, 
     vsip_length);
   
vsip_block_i* (vsip_vdestroy_i)(
     vsip_vview_i*);

void (vsip_valldestroy_i)(
     vsip_vview_i*);

vsip_vview_i* (vsip_vsubview_i)(
     const vsip_vview_i*, 
     vsip_index, 
     vsip_length);

vsip_block_i* (vsip_vgetblock_i)(
     const vsip_vview_i*);
 
vsip_offset (vsip_vgetoffset_i)(
     const vsip_vview_i*);
 
vsip_stride (vsip_vgetstride_i)(
     const vsip_vview_i*);
 
vsip_length (vsip_vgetlength_i)(
     const vsip_vview_i*);
 
void (vsip_vgetattrib_i)(
     const vsip_vview_i*,
     vsip_vattr_i*);
 
vsip_scalar_i (vsip_vget_i)(
     const vsip_vview_i*, 
     vsip_index);

vsip_vview_i* (vsip_vputoffset_i)(
     vsip_vview_i*, 
     vsip_offset);

vsip_vview_i* (vsip_vputstride_i)(
     vsip_vview_i*, 
     vsip_stride);

vsip_vview_i* (vsip_vputlength_i)(
     vsip_vview_i*, 
     vsip_length);

vsip_vview_i* (vsip_vputattrib_i)(
     vsip_vview_i*,
     const vsip_vattr_i*);

void (vsip_vput_i)(
     const vsip_vview_i*,
     vsip_index, 
     vsip_scalar_i);

void (vsip_madd_i)(
     const vsip_mview_i*,
     const vsip_mview_i*,
     const vsip_mview_i*);

void (vsip_mand_i)(
     const vsip_mview_i*,
     const vsip_mview_i*,
     const vsip_mview_i*);

void (vsip_mclip_i)(
     const vsip_mview_i*,
     vsip_scalar_i,
     vsip_scalar_i,
     vsip_scalar_i,
     vsip_scalar_i,
     const vsip_mview_i*);

void (vsip_mfill_i)(
      vsip_scalar_i,
      const vsip_mview_i* );

void (vsip_mhisto_i)(
    const vsip_mview_i*,
    vsip_scalar_i,
    vsip_scalar_i,
    vsip_hist_opt,
    const vsip_vview_i* );

vsip_scalar_i (vsip_mmaxval_i)(
    const vsip_mview_i*,
    vsip_scalar_mi*);

void (vsip_msub_i)(
    const vsip_mview_i*,
    const vsip_mview_i*,
    const vsip_mview_i*);

void (vsip_smsub_i)(
    vsip_scalar_i,
    const vsip_mview_i*,
    const vsip_mview_i*);

vsip_scalar_i (vsip_vmaxval_i)(
     const vsip_vview_i*,
     vsip_index*);

void (vsip_mcopy_i_f)(
      const vsip_mview_i*,
      const vsip_mview_f* );

void vsip_mcumsum_i(
      const vsip_mview_i*,
      vsip_major,
      const vsip_mview_i*);


/* vsip_vview_si & vsip_mview_si */
vsip_vview_si* (vsip_vcreate_si)(
     vsip_length, vsip_memory_hint); 

vsip_vview_si* (vsip_vcloneview_si)(
     const vsip_vview_si*);

vsip_vview_si* (vsip_vbind_si)(
     const vsip_block_si*, 
     vsip_offset, vsip_stride, vsip_length);

vsip_block_si* (vsip_vdestroy_si)(
     vsip_vview_si*);

void (vsip_valldestroy_si)(
     vsip_vview_si*);

vsip_vview_si* (vsip_vsubview_si)(
     const vsip_vview_si*, 
     vsip_index, 
     vsip_length);

vsip_block_si* (vsip_vgetblock_si)(
     const vsip_vview_si*);

vsip_offset (vsip_vgetoffset_si)(
     const vsip_vview_si*);

vsip_stride (vsip_vgetstride_si)(
     const vsip_vview_si*);

vsip_length (vsip_vgetlength_si)(
     const vsip_vview_si*);

void (vsip_vgetattrib_si)(
     const vsip_vview_si*,
     vsip_vattr_si*);

vsip_scalar_si (vsip_vget_si)(
     const vsip_vview_si*, vsip_index);

vsip_vview_si* (vsip_vputoffset_si)(
     vsip_vview_si*, vsip_offset);

vsip_vview_si* (vsip_vputstride_si)(
     vsip_vview_si*, vsip_stride);

vsip_vview_si* (vsip_vputlength_si)(
     vsip_vview_si*, vsip_length);

vsip_vview_si* (vsip_vputattrib_si)( 
     vsip_vview_si*,
     const vsip_vattr_si*);

void (vsip_vput_si)(
     const vsip_vview_si*,
     vsip_index, 
     vsip_scalar_si);

void (vsip_madd_si)(
     const vsip_mview_si*,
     const vsip_mview_si*,
     const vsip_mview_si*);

void (vsip_mand_si)(
     const vsip_mview_si*,
     const vsip_mview_si*,
     const vsip_mview_si*);
   
void (vsip_mclip_si)(
     const vsip_mview_si*,
     vsip_scalar_si,
     vsip_scalar_si,
     vsip_scalar_si,
     vsip_scalar_si,
     const vsip_mview_si*);

void (vsip_mcopy_si_f)(
      const vsip_mview_si*,
      const vsip_mview_f* );

void (vsip_mfill_si)(
      vsip_scalar_si,
      const vsip_mview_si* );

void (vsip_mhisto_si)(
     const vsip_mview_si*,
     vsip_scalar_si,
     vsip_scalar_si,
     vsip_hist_opt,
     const vsip_vview_si* );

vsip_scalar_si (vsip_mmaxval_si)(
     const vsip_mview_si*,
     vsip_scalar_mi*);
   
void (vsip_msub_si)(
     const vsip_mview_si*,
     const vsip_mview_si*,
     const vsip_mview_si*);

void (vsip_smsub_si)(
     vsip_scalar_si,
     const vsip_mview_si*,
     const vsip_mview_si*);

void (vsip_smsub_si)(
     vsip_scalar_si,
     const vsip_mview_si*,
     const vsip_mview_si*);

void (vsip_vhisto_si)(
     const vsip_vview_si*,
     vsip_scalar_si,
     vsip_scalar_si,
     vsip_hist_opt,
     const vsip_vview_si* );

vsip_scalar_si (vsip_vmaxval_si)(
     const vsip_vview_si*,
     vsip_index*);

/* vsip_vview_uc */
vsip_vview_uc* (vsip_vcreate_uc)(
     vsip_length, vsip_memory_hint); 

vsip_vview_uc* (vsip_vcloneview_uc)(
     const vsip_vview_uc*);

vsip_vview_uc* (vsip_vbind_uc)(
     const vsip_block_uc*, 
     vsip_offset, vsip_stride, vsip_length);

vsip_block_uc* (vsip_vdestroy_uc)(
     vsip_vview_uc*);

void (vsip_valldestroy_uc)(
     vsip_vview_uc*);

vsip_vview_uc* (vsip_vsubview_uc)(
     const vsip_vview_uc*, 
     vsip_index, 
     vsip_length);

vsip_block_uc* (vsip_vgetblock_uc)(
     const vsip_vview_uc*);

vsip_offset (vsip_vgetoffset_uc)(
     const vsip_vview_uc*);

vsip_stride (vsip_vgetstride_uc)(
     const vsip_vview_uc*);

vsip_length (vsip_vgetlength_uc)(
     const vsip_vview_uc*);

void (vsip_vgetattrib_uc)(
     const vsip_vview_uc*,
     vsip_vattr_uc*);

vsip_scalar_uc (vsip_vget_uc)(
     const vsip_vview_uc*, vsip_index);

vsip_vview_uc* (vsip_vputoffset_uc)(
     vsip_vview_uc*, vsip_offset);

vsip_vview_uc* (vsip_vputstride_uc)(
     vsip_vview_uc*, vsip_stride);

vsip_vview_uc* (vsip_vputlength_uc)(
     vsip_vview_uc*, vsip_length);

vsip_vview_uc* (vsip_vputattrib_uc)( 
     vsip_vview_uc*,
     const vsip_vattr_uc*);

void (vsip_vput_uc)(
     const vsip_vview_uc*,
     vsip_index, 
     vsip_scalar_uc);

/* Copy prototypes */
void (vsip_vcopy_d_d)(
  const vsip_vview_d*,
  const vsip_vview_d*);

void (vsip_vcopy_f_f)(
  const vsip_vview_f*,
  const vsip_vview_f*);

void (vsip_vcopy_i_d)(
  const vsip_vview_i*,
  const vsip_vview_d*);

void (vsip_vcopy_bl_bl)(
  const vsip_vview_bl*,
  const vsip_vview_bl*);

void (vsip_vcopy_bl_d)(
  const vsip_vview_bl*,
  const vsip_vview_d*);

void (vsip_vcopy_bl_f)(
  const vsip_vview_bl*,
  const vsip_vview_f*);

void (vsip_vcopy_d_i)(
  const vsip_vview_d*,
  const vsip_vview_i*);

void (vsip_vcopy_d_vi)(
  const vsip_vview_d*,
  const vsip_vview_vi*);

void (vsip_cvcopy_d_f)(
  const vsip_cvview_d*,
  const vsip_cvview_f*);

void (vsip_cvcopy_f_d)(
  const vsip_cvview_f*,
  const vsip_cvview_d*);

void (vsip_cvcopy_d_d)(
  const vsip_cvview_d*,
  const vsip_cvview_d*);

void (vsip_cvcopy_f_f)(
  const vsip_cvview_f*,
  const vsip_cvview_f*);

void (vsip_vcopy_i_uc)(
  const vsip_vview_i*,
  const vsip_vview_uc*);

void (vsip_vcopy_i_vi)(
  const vsip_vview_i*,
  const vsip_vview_vi*);

void (vsip_vcopy_i_i)(
  const vsip_vview_i*,
  const vsip_vview_i*);

void (vsip_vcopy_i_f)(
  const vsip_vview_i*,
  const vsip_vview_f*);

void (vsip_vcopy_f_i)(
  const vsip_vview_f*,
  const vsip_vview_i*);

void (vsip_vcopy_f_vi)(
  const vsip_vview_f*,
  const vsip_vview_vi*);

void (vsip_vcopy_d_bl)(
  const vsip_vview_d*,
  const vsip_vview_bl*);

void (vsip_vcopy_f_bl)(
  const vsip_vview_f*,
  const vsip_vview_bl*);

void (vsip_vcopy_si_si)( 
  const vsip_vview_si*, 
  const vsip_vview_si*);

void (vsip_vcopy_d_f)( 
  const vsip_vview_d*, 
  const vsip_vview_f*);

void (vsip_vcopy_f_d)( 
  const vsip_vview_f*, 
  const vsip_vview_d*);

void (vsip_vcopy_vi_i)( 
  const vsip_vview_vi*, 
  const vsip_vview_i*);

void (vsip_vcopy_vi_vi)( 
  const vsip_vview_vi*, 
  const vsip_vview_vi*);

void (vsip_vcopy_mi_mi)( 
  const vsip_vview_mi*, 
  const vsip_vview_mi*);

void (vsip_vcopy_d_si)( 
  const vsip_vview_d*, 
  const vsip_vview_si*);

void (vsip_vcopy_d_uc)( 
  const vsip_vview_d*, 
  const vsip_vview_uc*);

void (vsip_vcopy_si_d)( 
  const vsip_vview_si*, 
  const vsip_vview_d*);

void (vsip_vcopy_si_f)( 
  const vsip_vview_si*, 
  const vsip_vview_f*);

void (vsip_vcopy_f_si)( 
  const vsip_vview_f*, 
  const vsip_vview_si*);

void (vsip_vcopy_f_uc)( 
  const vsip_vview_f*, 
  const vsip_vview_uc*);

void (vsip_mcopy_d_d)(
  const vsip_mview_d* A,
  const vsip_mview_d* R);

void (vsip_mcopy_f_f)(
  const vsip_mview_f* A,
  const vsip_mview_f* R);

void (vsip_mcopy_f_d)(
  const vsip_mview_f* A,
  const vsip_mview_d* R);

void (vsip_mcopy_d_f)(
  const vsip_mview_d* A,
  const vsip_mview_f* R);

void (vsip_cmcopy_f_d)(
  const vsip_cmview_f* A,
  const vsip_cmview_d* R);

void (vsip_cmcopy_d_f)(
  const vsip_cmview_d* A,
  const vsip_cmview_f* R);

void (vsip_cmcopy_d_d)(
  const vsip_cmview_d* A,
  const vsip_cmview_d* R);

void (vsip_cmcopy_f_f)(
  const vsip_cmview_f* A,
  const vsip_cmview_f* R);

void (vsip_mcopy_bl_f)(
  const vsip_mview_bl* A,
  const vsip_mview_f* R);

void (vsip_mcopy_bl_d)(
  const vsip_mview_bl* A,
  const vsip_mview_d* R);

void (vsip_mcopy_f_bl)(
  const vsip_mview_f* A,
  const vsip_mview_bl* R);

void (vsip_mcopy_f_i)(
  const vsip_mview_f* A,
  const vsip_mview_i* R);

void (vsip_mcopy_f_uc)(
  const vsip_mview_f* A,
  const vsip_mview_uc* R);

void (vsip_mcopy_d_bl)(
  const vsip_mview_d* A,
  const vsip_mview_bl* R);

void (vsip_mcopy_d_i)(
  const vsip_mview_d* A,
  const vsip_mview_i* R);

void (vsip_mcopy_d_uc)(
  const vsip_mview_d* A,
  const vsip_mview_uc* R);

void (vsip_mcopy_bl_bl)(
  const vsip_mview_bl* A,
  const vsip_mview_bl* R);

/* vsip_cvview_d */
vsip_cvview_d* (vsip_cvcreate_d)(
     vsip_length, vsip_memory_hint);

vsip_cvview_d* (vsip_cvcloneview_d)(
     const vsip_cvview_d*);

vsip_cvview_d* (vsip_cvbind_d)(
     const vsip_cblock_d*, 
     vsip_offset, 
     vsip_stride, 
     vsip_length);

vsip_cblock_d* (vsip_cvdestroy_d)(
     vsip_cvview_d*);

void (vsip_cvalldestroy_d)(
     vsip_cvview_d*);

vsip_cvview_d* (vsip_cvsubview_d)(
     const vsip_cvview_d*, 
     vsip_index,
     vsip_length);

vsip_vview_d* (vsip_vrealview_d)(
     const vsip_cvview_d*);

vsip_vview_d* (vsip_vimagview_d)(
     const vsip_cvview_d*);

vsip_cblock_d* (vsip_cvgetblock_d)(
     const vsip_cvview_d*);

vsip_offset (vsip_cvgetoffset_d)(
     const vsip_cvview_d*);

vsip_stride (vsip_cvgetstride_d)(
     const vsip_cvview_d*);

vsip_length (vsip_cvgetlength_d)(
     const vsip_cvview_d*);

void (vsip_cvgetattrib_d)(
     const vsip_cvview_d* ,
     vsip_cvattr_d*);

vsip_cscalar_d (vsip_cvget_d)(
     const vsip_cvview_d*, 
     vsip_index);

vsip_cvview_d* (vsip_cvputoffset_d)(
     vsip_cvview_d*, 
     vsip_offset);

vsip_cvview_d* (vsip_cvputstride_d)(
     vsip_cvview_d*, 
     vsip_stride);

vsip_cvview_d* (vsip_cvputlength_d)(
     vsip_cvview_d*, 
     vsip_length);

vsip_cvview_d* (vsip_cvputattrib_d)(
     vsip_cvview_d*,
     const vsip_cvattr_d*);

void (vsip_cvput_d)(
     const vsip_cvview_d*,
     vsip_index, 
     vsip_cscalar_d);

/* end complex vector double */

/* vsip_cvview_f */
vsip_cvview_f* (vsip_cvcreate_f)(
     vsip_length, vsip_memory_hint);

vsip_cvview_f* (vsip_cvcloneview_f)(
     const vsip_cvview_f*);

vsip_cvview_f* (vsip_cvbind_f)(
     const vsip_cblock_f*, 
     vsip_offset, 
     vsip_stride, 
     vsip_length);

vsip_cblock_f* (vsip_cvdestroy_f)(
     vsip_cvview_f*);

void (vsip_cvalldestroy_f)(
     vsip_cvview_f*);

vsip_cvview_f* (vsip_cvsubview_f)(
     const vsip_cvview_f*, 
     vsip_index,
     vsip_length);

vsip_vview_f* (vsip_vrealview_f)(
     const vsip_cvview_f*);

vsip_vview_f* (vsip_vimagview_f)(
     const vsip_cvview_f*);

vsip_cblock_f* (vsip_cvgetblock_f)(
     const vsip_cvview_f*);

vsip_offset (vsip_cvgetoffset_f)(
     const vsip_cvview_f*);

vsip_stride (vsip_cvgetstride_f)(
     const vsip_cvview_f*);

vsip_length (vsip_cvgetlength_f)(
     const vsip_cvview_f*);

void (vsip_cvgetattrib_f)(
     const vsip_cvview_f* ,
     vsip_cvattr_f*);

vsip_cscalar_f (vsip_cvget_f)(
     const vsip_cvview_f*, 
     vsip_index);

vsip_cvview_f* (vsip_cvputoffset_f)(
     vsip_cvview_f*, 
     vsip_offset);

vsip_cvview_f* (vsip_cvputstride_f)(
     vsip_cvview_f*, 
     vsip_stride);

vsip_cvview_f* (vsip_cvputlength_f)(
     vsip_cvview_f*, 
     vsip_length);

vsip_cvview_f* (vsip_cvputattrib_f)(
     vsip_cvview_f*,
     const vsip_cvattr_f*);

void (vsip_cvput_f)(
     const vsip_cvview_f*,
     vsip_index, 
     vsip_cscalar_f);

/* end complex vector view float */
/********************************************************************/

/* matrix */
/* vsip_mview_d */
vsip_mview_d* (vsip_mcreate_d)(
     vsip_length,
     vsip_length, 
     vsip_major,
     vsip_memory_hint);

vsip_mview_d* (vsip_mcloneview_d)(
     const vsip_mview_d*);

vsip_mview_d* (vsip_mbind_d)(
     const vsip_block_d* , 
     vsip_offset , 
     vsip_stride , vsip_length ,
     vsip_stride , vsip_length );

vsip_block_d* (vsip_mdestroy_d)(
     vsip_mview_d*);

void (vsip_malldestroy_d)(
     vsip_mview_d*);

vsip_mview_d* (vsip_msubview_d)(
     const vsip_mview_d*, 
     vsip_index, vsip_index, 
     vsip_length m,vsip_length);

vsip_vview_d* (vsip_mrowview_d)(
     const vsip_mview_d*, 
     vsip_index);

vsip_vview_d* (vsip_mcolview_d)(
     const vsip_mview_d*, 
     vsip_index);

vsip_vview_d* (vsip_mdiagview_d)(
     const vsip_mview_d* ,
     int);

vsip_mview_d* (vsip_mtransview_d)(
     const vsip_mview_d*);

vsip_block_d* (vsip_mgetblock_d)(
     const vsip_mview_d*);

vsip_offset (vsip_mgetoffset_d)(
     const vsip_mview_d*);

vsip_stride (vsip_mgetrowstride_d)(
     const vsip_mview_d*);

vsip_length (vsip_mgetrowlength_d)(
     const vsip_mview_d*);

vsip_stride (vsip_mgetcolstride_d)(
     const vsip_mview_d*);

vsip_length (vsip_mgetcollength_d)(
     const vsip_mview_d*);

void (vsip_mgetattrib_d)(
     const vsip_mview_d*,
     vsip_mattr_d*);

vsip_scalar_d (vsip_mget_d)(
     const vsip_mview_d*, 
     vsip_index, 
     vsip_index);

vsip_mview_d* (vsip_mputoffset_d)(
     vsip_mview_d*, 
     vsip_offset);

vsip_mview_d* (vsip_mputrowstride_d)(
     vsip_mview_d*, 
     vsip_stride);

vsip_mview_d* (vsip_mputrowlength_d)(
     vsip_mview_d*, 
     vsip_length);

vsip_mview_d* (vsip_mputcolstride_d)(
     vsip_mview_d*, 
     vsip_stride);

vsip_mview_d* (vsip_mputcollength_d)(
     vsip_mview_d*, 
     vsip_length m);

vsip_mview_d* (vsip_mputattrib_d)(
     vsip_mview_d*,
     const vsip_mattr_d*);

void (vsip_mput_d)(
     const vsip_mview_d*,
     vsip_index, 
     vsip_index, 
     vsip_scalar_d);

/* vsip_mview_f */
vsip_mview_f* (vsip_mcreate_f)(
     vsip_length,
     vsip_length, 
     vsip_major,
     vsip_memory_hint);

vsip_mview_f* (vsip_mcloneview_f)(
     const vsip_mview_f*);

vsip_mview_f* (vsip_mbind_f)(
     const vsip_block_f* , 
     vsip_offset, 
     vsip_stride, 
     vsip_length,
     vsip_stride, 
     vsip_length);

vsip_block_f* (vsip_mdestroy_f)(
     vsip_mview_f*);

void (vsip_malldestroy_f)(
     vsip_mview_f*);

vsip_mview_f* (vsip_msubview_f)(
     const vsip_mview_f*, 
     vsip_index, vsip_index, 
     vsip_length m, vsip_length);

vsip_vview_f* (vsip_mrowview_f)(
     const vsip_mview_f*, 
     vsip_index);

vsip_vview_f* (vsip_mcolview_f)(
     const vsip_mview_f*, 
     vsip_index);

vsip_vview_f* (vsip_mdiagview_f)(
     const vsip_mview_f* ,
     int);

vsip_mview_f* (vsip_mtransview_f)(
     const vsip_mview_f*);

vsip_block_f* (vsip_mgetblock_f)(
     const vsip_mview_f*);

vsip_offset (vsip_mgetoffset_f)(
     const vsip_mview_f*);

vsip_stride (vsip_mgetrowstride_f)(
     const vsip_mview_f*);

vsip_length (vsip_mgetrowlength_f)(
     const vsip_mview_f*);

vsip_stride (vsip_mgetcolstride_f)(
     const vsip_mview_f*);

vsip_length (vsip_mgetcollength_f)(
     const vsip_mview_f*);

void (vsip_mgetattrib_f)(
     const vsip_mview_f*,
     vsip_mattr_f*);

vsip_scalar_f (vsip_mget_f)(
     const vsip_mview_f*, 
     vsip_index, 
     vsip_index);

vsip_mview_f* (vsip_mputoffset_f)(
     vsip_mview_f*, 
     vsip_offset);

vsip_mview_f* (vsip_mputrowstride_f)(
     vsip_mview_f*, 
     vsip_stride);

vsip_mview_f* (vsip_mputrowlength_f)(
     vsip_mview_f*, 
     vsip_length);

vsip_mview_f* (vsip_mputcolstride_f)(
     vsip_mview_f*, 
     vsip_stride);

vsip_mview_f* (vsip_mputcollength_f)(
     vsip_mview_f*, 
     vsip_length m);

vsip_mview_f* (vsip_mputattrib_f)(
     vsip_mview_f*,
     const vsip_mattr_f*);

void (vsip_mput_f)(
     const vsip_mview_f*,
     vsip_index, 
     vsip_index, 
     vsip_scalar_f);

/* vsip_mview_bl */
vsip_mview_bl* (vsip_mcreate_bl)(
     vsip_length,
     vsip_length, 
     vsip_major,
     vsip_memory_hint);

vsip_mview_bl* (vsip_mcloneview_bl)(
     const vsip_mview_bl*);

vsip_mview_bl* (vsip_mbind_bl)(
     const vsip_block_bl* , 
     vsip_offset, 
     vsip_stride, 
     vsip_length,
     vsip_stride, 
     vsip_length);

vsip_block_bl* (vsip_mdestroy_bl)(
     vsip_mview_bl*);

void (vsip_malldestroy_bl)(
     vsip_mview_bl*);

vsip_mview_bl* (vsip_msubview_bl)(
     const vsip_mview_bl*, 
     vsip_index,
     vsip_index, 
     vsip_length,
     vsip_length);

vsip_vview_bl* (vsip_mrowview_bl)(
     const vsip_mview_bl*, 
     vsip_index);

vsip_vview_bl* (vsip_mcolview_bl)(
     const vsip_mview_bl*, 
     vsip_index);

vsip_vview_bl* (vsip_mdiagview_bl)(
     const vsip_mview_bl* ,
     int);

vsip_mview_bl* (vsip_mtransview_bl)(
     const vsip_mview_bl*);

vsip_block_bl* (vsip_mgetblock_bl)(
     const vsip_mview_bl*);

vsip_offset (vsip_mgetoffset_bl)(
     const vsip_mview_bl*);

vsip_stride (vsip_mgetrowstride_bl)(
     const vsip_mview_bl*);

vsip_length (vsip_mgetrowlength_bl)(
     const vsip_mview_bl*);

vsip_stride (vsip_mgetcolstride_bl)(
     const vsip_mview_bl*);

vsip_length (vsip_mgetcollength_bl)(
     const vsip_mview_bl*);

void (vsip_mgetattrib_bl)(
     const vsip_mview_bl*,
     vsip_mattr_bl*);

vsip_scalar_bl (vsip_mget_bl)(
     const vsip_mview_bl*, 
     vsip_index, 
     vsip_index);

vsip_mview_bl* (vsip_mputoffset_bl)(
     vsip_mview_bl*, 
     vsip_offset);

vsip_mview_bl* (vsip_mputrowstride_bl)(
     vsip_mview_bl*, 
     vsip_stride);

vsip_mview_bl* (vsip_mputrowlength_bl)(
     vsip_mview_bl*, 
     vsip_length);

vsip_mview_bl* (vsip_mputcolstride_bl)(
     vsip_mview_bl*, 
     vsip_stride);

vsip_mview_bl* (vsip_mputcollength_bl)(
     vsip_mview_bl*, 
     vsip_length);

vsip_mview_bl* (vsip_mputattrib_bl)(
     vsip_mview_bl*,
     const vsip_mattr_bl*);

void (vsip_mput_bl)(
     const vsip_mview_bl*,
     vsip_index, 
     vsip_index, 
     vsip_scalar_bl);

/* vsip_mview_i */
vsip_mview_i* (vsip_mcreate_i)(
     vsip_length,
     vsip_length, 
     vsip_major,
     vsip_memory_hint);

vsip_mview_i* (vsip_mcloneview_i)(
     const vsip_mview_i*);

vsip_mview_i* (vsip_mbind_i)(
     const vsip_block_i* , 
     vsip_offset, 
     vsip_stride, 
     vsip_length,
     vsip_stride, 
     vsip_length);

vsip_block_i* (vsip_mdestroy_i)(
     vsip_mview_i*);

void (vsip_malldestroy_i)(
     vsip_mview_i*);

vsip_mview_i* (vsip_msubview_i)(
     const vsip_mview_i*, 
     vsip_index,
     vsip_index, 
     vsip_length,
     vsip_length);

vsip_vview_i* (vsip_mrowview_i)(
     const vsip_mview_i*, 
     vsip_index);

vsip_vview_i* (vsip_mcolview_i)(
     const vsip_mview_i*, 
     vsip_index);

vsip_vview_i* (vsip_mdiagview_i)(
     const vsip_mview_i* ,
     int);

vsip_mview_i* (vsip_mtransview_i)(
     const vsip_mview_i*);

vsip_block_i* (vsip_mgetblock_i)(
     const vsip_mview_i*);

vsip_offset (vsip_mgetoffset_i)(
     const vsip_mview_i*);

vsip_stride (vsip_mgetrowstride_i)(
     const vsip_mview_i*);

vsip_length (vsip_mgetrowlength_i)(
     const vsip_mview_i*);

vsip_stride (vsip_mgetcolstride_i)(
     const vsip_mview_i*);

vsip_length (vsip_mgetcollength_i)(
     const vsip_mview_i*);

void (vsip_mgetattrib_i)(
     const vsip_mview_i*,
     vsip_mattr_i*);

vsip_scalar_i (vsip_mget_i)(
     const vsip_mview_i*, 
     vsip_index, 
     vsip_index);

vsip_mview_i* (vsip_mputoffset_i)(
     vsip_mview_i*, 
     vsip_offset);

vsip_mview_i* (vsip_mputrowstride_i)(
     vsip_mview_i*, 
     vsip_stride);

vsip_mview_i* (vsip_mputrowlength_i)(
     vsip_mview_i*, 
     vsip_length);

vsip_mview_i* (vsip_mputcolstride_i)(
     vsip_mview_i*, 
     vsip_stride);

vsip_mview_i* (vsip_mputcollength_i)(
     vsip_mview_i*, 
     vsip_length);

vsip_mview_i* (vsip_mputattrib_i)(
     vsip_mview_i*,
     const vsip_mattr_i*);

void (vsip_mput_i)(
     const vsip_mview_i*,
     vsip_index, 
     vsip_index, 
     vsip_scalar_i);

/* vsip_mview_si */
vsip_mview_si* (vsip_mcreate_si)(
     vsip_length,
     vsip_length, 
     vsip_major,
     vsip_memory_hint);

vsip_mview_si* (vsip_mcloneview_si)(
     const vsip_mview_si*);

vsip_mview_si* (vsip_mbind_si)(
     const vsip_block_si* , 
     vsip_offset, 
     vsip_stride, 
     vsip_length,
     vsip_stride, 
     vsip_length);

vsip_block_si* (vsip_mdestroy_si)(
     vsip_mview_si*);

void (vsip_malldestroy_si)(
     vsip_mview_si*);

vsip_mview_si* (vsip_msubview_si)(
     const vsip_mview_si*, 
     vsip_index,
     vsip_index, 
     vsip_length,
     vsip_length);

vsip_vview_si* (vsip_mrowview_si)(
     const vsip_mview_si*, 
     vsip_index);

vsip_vview_si* (vsip_mcolview_si)(
     const vsip_mview_si*, 
     vsip_index);

vsip_vview_si* (vsip_mdiagview_si)(
     const vsip_mview_si* ,
     int);

vsip_mview_si* (vsip_mtransview_si)(
     const vsip_mview_si*);

vsip_block_si* (vsip_mgetblock_si)(
     const vsip_mview_si*);

vsip_offset (vsip_mgetoffset_si)(
     const vsip_mview_si*);

vsip_stride (vsip_mgetrowstride_si)(
     const vsip_mview_si*);

vsip_length (vsip_mgetrowlength_si)(
     const vsip_mview_si*);

vsip_stride (vsip_mgetcolstride_si)(
     const vsip_mview_si*);

vsip_length (vsip_mgetcollength_si)(
     const vsip_mview_si*);

void (vsip_mgetattrib_si)(
     const vsip_mview_si*,
     vsip_mattr_si*);

vsip_scalar_si (vsip_mget_si)(
     const vsip_mview_si*, 
     vsip_index, 
     vsip_index);

vsip_mview_si* (vsip_mputoffset_si)(
     vsip_mview_si*, 
     vsip_offset);

vsip_mview_si* (vsip_mputrowstride_si)(
     vsip_mview_si*, 
     vsip_stride);

vsip_mview_si* (vsip_mputrowlength_si)(
     vsip_mview_si*, 
     vsip_length);

vsip_mview_si* (vsip_mputcolstride_si)(
     vsip_mview_si*, 
     vsip_stride);

vsip_mview_si* (vsip_mputcollength_si)(
     vsip_mview_si*, 
     vsip_length);

vsip_mview_si* (vsip_mputattrib_si)(
     vsip_mview_si*,
     const vsip_mattr_si*);

void (vsip_mput_si)(
     const vsip_mview_si*,
     vsip_index, 
     vsip_index, 
     vsip_scalar_si);

void vsip_mcumsum_si(
     const vsip_mview_si*,
     vsip_major,
     const vsip_mview_si*);

/* vsip_mview_uc */
vsip_mview_uc* (vsip_mcreate_uc)(
     vsip_length,
     vsip_length, 
     vsip_major,
     vsip_memory_hint);

vsip_mview_uc* (vsip_mcloneview_uc)(
     const vsip_mview_uc*);

vsip_mview_uc* (vsip_mbind_uc)(
     const vsip_block_uc* , 
     vsip_offset, 
     vsip_stride, 
     vsip_length,
     vsip_stride, 
     vsip_length);

vsip_block_uc* (vsip_mdestroy_uc)(
     vsip_mview_uc*);

void (vsip_malldestroy_uc)(
     vsip_mview_uc*);

vsip_mview_uc* (vsip_msubview_uc)(
     const vsip_mview_uc*, 
     vsip_index,
     vsip_index, 
     vsip_length,
     vsip_length);

vsip_vview_uc* (vsip_mrowview_uc)(
     const vsip_mview_uc*, 
     vsip_index);

vsip_vview_uc* (vsip_mcolview_uc)(
     const vsip_mview_uc*, 
     vsip_index);

vsip_vview_uc* (vsip_mdiagview_uc)(
     const vsip_mview_uc* ,
     int);

vsip_mview_uc* (vsip_mtransview_uc)(
     const vsip_mview_uc*);

vsip_block_uc* (vsip_mgetblock_uc)(
     const vsip_mview_uc*);

vsip_offset (vsip_mgetoffset_uc)(
     const vsip_mview_uc*);

vsip_stride (vsip_mgetrowstride_uc)(
     const vsip_mview_uc*);

vsip_length (vsip_mgetrowlength_uc)(
     const vsip_mview_uc*);

vsip_stride (vsip_mgetcolstride_uc)(
     const vsip_mview_uc*);

vsip_length (vsip_mgetcollength_uc)(
     const vsip_mview_uc*);

void (vsip_mgetattrib_uc)(
     const vsip_mview_uc*,
     vsip_mattr_uc*);

vsip_scalar_uc (vsip_mget_uc)(
     const vsip_mview_uc*, 
     vsip_index, 
     vsip_index);

vsip_mview_uc* (vsip_mputoffset_uc)(
     vsip_mview_uc*, 
     vsip_offset);

vsip_mview_uc* (vsip_mputrowstride_uc)(
     vsip_mview_uc*, 
     vsip_stride);

vsip_mview_uc* (vsip_mputrowlength_uc)(
     vsip_mview_uc*, 
     vsip_length);

vsip_mview_uc* (vsip_mputcolstride_uc)(
     vsip_mview_uc*, 
     vsip_stride);

vsip_mview_uc* (vsip_mputcollength_uc)(
     vsip_mview_uc*, 
     vsip_length);

vsip_mview_uc* (vsip_mputattrib_uc)(
     vsip_mview_uc*,
     const vsip_mattr_uc*);

void (vsip_mput_uc)(
     const vsip_mview_uc*,
     vsip_index, 
     vsip_index, 
     vsip_scalar_uc);

/* vsip_cmview_d */
vsip_cmview_d* (vsip_cmcreate_d)(
     vsip_length,
     vsip_length, 
     vsip_major,
     vsip_memory_hint);

vsip_cmview_d* (vsip_cmcloneview_d)(
     const vsip_cmview_d*);

vsip_cmview_d* (vsip_cmbind_d)(
     const vsip_cblock_d*, 
     vsip_offset, 
     vsip_stride, 
     vsip_length,
     vsip_stride, 
     vsip_length);

vsip_cblock_d* (vsip_cmdestroy_d)(
     vsip_cmview_d*);

void (vsip_cmalldestroy_d)(
     vsip_cmview_d*);

vsip_cmview_d* (vsip_cmsubview_d)(
     const vsip_cmview_d*, 
     vsip_index, 
     vsip_index, 
     vsip_length, 
     vsip_length);

vsip_cvview_d* (vsip_cmrowview_d)(
     const vsip_cmview_d*, 
     vsip_index);

vsip_cvview_d* (vsip_cmcolview_d)(
     const vsip_cmview_d*, 
     vsip_index);

vsip_cvview_d* (vsip_cmdiagview_d)(
     const vsip_cmview_d* ,
     int);

vsip_cmview_d* (vsip_cmtransview_d)(
     const vsip_cmview_d*);

vsip_mview_d* (vsip_mrealview_d)(
     const vsip_cmview_d*);

vsip_mview_d* (vsip_mimagview_d)(
     const vsip_cmview_d*);

vsip_cblock_d* (vsip_cmgetblock_d)(
     const vsip_cmview_d*);

vsip_offset (vsip_cmgetoffset_d)(
     const vsip_cmview_d*);

vsip_stride (vsip_cmgetrowstride_d)(
     const vsip_cmview_d*);

vsip_length (vsip_cmgetrowlength_d)(
     const vsip_cmview_d*);

vsip_stride (vsip_cmgetcolstride_d)(
     const vsip_cmview_d*);

vsip_length (vsip_cmgetcollength_d)(
     const vsip_cmview_d*);

void (vsip_cmgetattrib_d)(
     const vsip_cmview_d*,
     vsip_cmattr_d*);

vsip_cscalar_d (vsip_cmget_d)(
     const vsip_cmview_d*, 
     vsip_index, 
     vsip_index);

vsip_cmview_d* (vsip_cmputoffset_d)(
     vsip_cmview_d*, 
     vsip_offset);

vsip_cmview_d* (vsip_cmputrowstride_d)(
     vsip_cmview_d*, 
     vsip_stride);

vsip_cmview_d* (vsip_cmputrowlength_d)(
     vsip_cmview_d*, 
     vsip_length);

vsip_cmview_d* (vsip_cmputcolstride_d)(
     vsip_cmview_d*, 
     vsip_stride);

vsip_cmview_d* (vsip_cmputcollength_d)(
     vsip_cmview_d*, 
     vsip_length);

vsip_cmview_d* (vsip_cmputattrib_d)(
     vsip_cmview_d*,
     const vsip_cmattr_d*);

void (vsip_cmput_d)(const vsip_cmview_d*,
     vsip_index, 
     vsip_index, 
     vsip_cscalar_d);

/* vsip_cmview_f */
vsip_cmview_f* (vsip_cmcreate_f)(
     vsip_length,
     vsip_length, 
     vsip_major,
     vsip_memory_hint);

vsip_cmview_f* (vsip_cmcloneview_f)(
     const vsip_cmview_f*);

vsip_cmview_f* (vsip_cmbind_f)(
     const vsip_cblock_f*, 
     vsip_offset,
     vsip_stride,
     vsip_length,
     vsip_stride,
     vsip_length);

vsip_cblock_f* (vsip_cmdestroy_f)(
     vsip_cmview_f*);

void (vsip_cmalldestroy_f)(
     vsip_cmview_f*);

vsip_cmview_f* (vsip_cmsubview_f)(
     const vsip_cmview_f*, 
     vsip_index,
     vsip_index, 
     vsip_length,
     vsip_length);

vsip_cvview_f* (vsip_cmrowview_f)(
     const vsip_cmview_f*, 
     vsip_index);

vsip_cvview_f* (vsip_cmcolview_f)(
     const vsip_cmview_f*, 
     vsip_index);

vsip_cvview_f* (vsip_cmdiagview_f)(
     const vsip_cmview_f* ,
     int);

vsip_cmview_f* (vsip_cmtransview_f)(
     const vsip_cmview_f*);

vsip_mview_f* (vsip_mrealview_f)(
     const vsip_cmview_f*);

vsip_mview_f* (vsip_mimagview_f)(
     const vsip_cmview_f*);

vsip_cblock_f* (vsip_cmgetblock_f)(
     const vsip_cmview_f*);

vsip_offset (vsip_cmgetoffset_f)(
     const vsip_cmview_f*);

vsip_stride (vsip_cmgetrowstride_f)(
     const vsip_cmview_f*);

vsip_length (vsip_cmgetrowlength_f)(
     const vsip_cmview_f*);

vsip_stride (vsip_cmgetcolstride_f)(
     const vsip_cmview_f*);

vsip_length (vsip_cmgetcollength_f)(
     const vsip_cmview_f*);

void (vsip_cmgetattrib_f)(
     const vsip_cmview_f*,
     vsip_cmattr_f*);

vsip_cscalar_f (vsip_cmget_f)(
     const vsip_cmview_f*, 
     vsip_index, 
     vsip_index);

vsip_cmview_f* (vsip_cmputoffset_f)(
     vsip_cmview_f*, 
     vsip_offset);

vsip_cmview_f* (vsip_cmputrowstride_f)(
     vsip_cmview_f*, 
     vsip_stride);

vsip_cmview_f* (vsip_cmputrowlength_f)(
     vsip_cmview_f*, 
     vsip_length);

vsip_cmview_f* (vsip_cmputcolstride_f)(
     vsip_cmview_f*, 
     vsip_stride);

vsip_cmview_f* (vsip_cmputcollength_f)(
     vsip_cmview_f*, 
     vsip_length);

vsip_cmview_f* (vsip_cmputattrib_f)(
     vsip_cmview_f*,
     const vsip_cmattr_f*);

void (vsip_cmput_f)(const vsip_cmview_f*,
     vsip_index, 
     vsip_index, 
     vsip_cscalar_f);

#endif /* _vsip_support_h */
#ifndef _vsip_vview_h
#define _vsip_vview_h 1

/* vsip_vview_bl */
vsip_scalar_bl (vsip_valltrue_bl)(
  const vsip_vview_bl*);

vsip_scalar_bl (vsip_vanytrue_bl)(
  const vsip_vview_bl*);

vsip_length (vsip_vindexbool)( 
  const vsip_vview_bl*, 
  vsip_vview_vi*);

void (vsip_vnot_bl)(
  const vsip_vview_bl*,
  const vsip_vview_bl*);

void (vsip_vand_bl)(
  const vsip_vview_bl*,
  const vsip_vview_bl*,
  const vsip_vview_bl*);

void (vsip_vxor_bl)(
  const vsip_vview_bl*,
  const vsip_vview_bl*,
  const vsip_vview_bl*);

void (vsip_vor_bl)(
  const vsip_vview_bl*,
  const vsip_vview_bl*,
  const vsip_vview_bl*);

vsip_scalar_vi (vsip_vsumval_bl)(
  const vsip_vview_bl*);


/*  vsip_vview_i */
void (vsip_vnot_i)(
     const vsip_vview_i*,
     const vsip_vview_i*);

void (vsip_vand_i)(
     const vsip_vview_i*,
     const vsip_vview_i*,
     const vsip_vview_i*);

void (vsip_vxor_i)(
     const vsip_vview_i*,
     const vsip_vview_i*,
     const vsip_vview_i*);

void (vsip_vor_i)(
     const vsip_vview_i*,
     const vsip_vview_i*,
     const vsip_vview_i*);

void (vsip_vgather_i)(
     const vsip_vview_i* x,
     const vsip_vview_vi*,
     const vsip_vview_i*);

void (vsip_vscatter_i)(
     const vsip_vview_i* x,
     const vsip_vview_i* y,
     const vsip_vview_vi* index);

void (vsip_vmul_i)(
     const vsip_vview_i*,
     const vsip_vview_i*,
     const vsip_vview_i*);

void (vsip_svmul_i)(
     vsip_scalar_i,
     const vsip_vview_i*,
     const vsip_vview_i*);

void (vsip_svadd_i)(
     vsip_scalar_i,
     const vsip_vview_i*,
     const vsip_vview_i*);

void (vsip_vadd_i)(
     const vsip_vview_i*,
     const vsip_vview_i*,
     const vsip_vview_i*);

void (vsip_vmag_i)(
     const vsip_vview_i*,
     const vsip_vview_i*);

void (vsip_vneg_i)(
     const vsip_vview_i*,
     const vsip_vview_i*);

void (vsip_vcumsum_i)(
     const vsip_vview_i*,
     const vsip_vview_i*);

void (vsip_vsub_i)(
     const vsip_vview_i*,
     const vsip_vview_i*,
     const vsip_vview_i*);

void (vsip_svsub_i)(
     vsip_scalar_i,
     const vsip_vview_i*,
     const vsip_vview_i*);

void (vsip_vllt_i)(
     const vsip_vview_i*,
     const vsip_vview_i*,
     const vsip_vview_bl*);

void (vsip_vlle_i)(
     const vsip_vview_i*,
     const vsip_vview_i*,
     const vsip_vview_bl*);

void (vsip_vlgt_i)(
     const vsip_vview_i*,
     const vsip_vview_i*,
     const vsip_vview_bl*);

void (vsip_vlge_i)(
     const vsip_vview_i*,
     const vsip_vview_i*,
     const vsip_vview_bl*);

void (vsip_vleq_i)(
     const vsip_vview_i*,
     const vsip_vview_i*,
     const vsip_vview_bl*);

void (vsip_vlne_i)(
     const vsip_vview_i*,
     const vsip_vview_i*,
     const vsip_vview_bl*);

void (vsip_vclip_i)(
     const vsip_vview_i*,
     vsip_scalar_i,
     vsip_scalar_i,
     vsip_scalar_i,
     vsip_scalar_i,
     const vsip_vview_i*);

void (vsip_vinvclip_i)(
     const vsip_vview_i*,
     vsip_scalar_i,
     vsip_scalar_i,
     vsip_scalar_i,
     vsip_scalar_i,
     vsip_scalar_i,
     const vsip_vview_i*);

void (vsip_vfill_i)(
     vsip_scalar_i,
     const vsip_vview_i*);

void (vsip_vhisto_i)(
     const vsip_vview_i*,
     vsip_scalar_i,
     vsip_scalar_i,
     vsip_hist_opt,
     const vsip_vview_i* ); 

void (vsip_vramp_i)(
     vsip_scalar_i,
     vsip_scalar_i,
     const vsip_vview_i*);

vsip_scalar_i (vsip_vsumval_i)(
     const vsip_vview_i*);

void (vsip_vswap_i)(
     const vsip_vview_i*,
     const vsip_vview_i*);

/* end vsip_vview_i */

/* vsip_vview_vi */
void (vsip_svadd_vi)(
     vsip_scalar_vi,
     const vsip_vview_vi*,
     const vsip_vview_vi*);

void (vsip_vadd_vi)(
     const vsip_vview_vi*,
     const vsip_vview_vi*,
     const vsip_vview_vi*);

void (vsip_svsub_vi)(
     vsip_scalar_vi,
     const vsip_vview_vi*,
     const vsip_vview_vi*);

void (vsip_vramp_vi)(
     vsip_scalar_vi,
     vsip_scalar_vi,
     const vsip_vview_vi*);
/* end vsip_vview_vi */

/*  vsip_vview_si */
void (vsip_vnot_si)(
     const vsip_vview_si*,
     const vsip_vview_si*);

void (vsip_vand_si)(
     const vsip_vview_si*,
     const vsip_vview_si*,
     const vsip_vview_si*);

void (vsip_vxor_si)(
     const vsip_vview_si*,
     const vsip_vview_si*,
     const vsip_vview_si*);

void (vsip_vor_si)(
     const vsip_vview_si*,
     const vsip_vview_si*,
     const vsip_vview_si*);

void (vsip_vgather_si)(
     const vsip_vview_si*,
     const vsip_vview_vi*,
     const vsip_vview_si*);

void (vsip_vscatter_si)(
     const vsip_vview_si*,
     const vsip_vview_si*,
     const vsip_vview_vi*);

void (vsip_vmul_si)(
     const vsip_vview_si*,
     const vsip_vview_si*,
     const vsip_vview_si*);

void (vsip_svmul_si)(
     vsip_scalar_si,
     const vsip_vview_si*,
     const vsip_vview_si*);

void (vsip_svadd_si)(
     vsip_scalar_si,
     const vsip_vview_si*,
     const vsip_vview_si*);

void (vsip_vadd_si)(
     const vsip_vview_si*,
     const vsip_vview_si*,
     const vsip_vview_si*);

void (vsip_vmag_si)(
     const vsip_vview_si*,
     const vsip_vview_si*);

void (vsip_vneg_si)(
     const vsip_vview_si*,
     const vsip_vview_si*);

void (vsip_vcumsum_si)(
     const vsip_vview_si*,
     const vsip_vview_si*);

void (vsip_vsub_si)(
     const vsip_vview_si*,
     const vsip_vview_si*,
     const vsip_vview_si*);

void (vsip_svsub_si)(
     vsip_scalar_si,
     const vsip_vview_si*,
     const vsip_vview_si*);

void (vsip_vllt_si)(
     const vsip_vview_si*,
     const vsip_vview_si*,
     const vsip_vview_bl*);

void (vsip_vlle_si)(
     const vsip_vview_si*,
     const vsip_vview_si*,
     const vsip_vview_bl*);

void (vsip_vlgt_si)(
     const vsip_vview_si*,
     const vsip_vview_si*,
     const vsip_vview_bl*);

void (vsip_vlge_si)(
     const vsip_vview_si*,
     const vsip_vview_si*,
     const vsip_vview_bl*);

void (vsip_vleq_si)(
     const vsip_vview_si*,
     const vsip_vview_si*,
     const vsip_vview_bl*);

void (vsip_vlne_si)(
     const vsip_vview_si*,
     const vsip_vview_si*,
     const vsip_vview_bl*);

void (vsip_vclip_si)(
     const vsip_vview_si*,
     vsip_scalar_si,
     vsip_scalar_si,
     vsip_scalar_si,
     vsip_scalar_si,
     const vsip_vview_si*);

void (vsip_vinvclip_si)(
     const vsip_vview_si*,
     vsip_scalar_si,
     vsip_scalar_si,
     vsip_scalar_si,
     vsip_scalar_si,
     vsip_scalar_si,
     const vsip_vview_si*);

void (vsip_vfill_si)(
     vsip_scalar_si,
     const vsip_vview_si*);

void (vsip_vramp_si)(
     vsip_scalar_si z,
     vsip_scalar_si d,
     const vsip_vview_si*);

vsip_scalar_si (vsip_vsumval_si)(
     const vsip_vview_si*);

void (vsip_vswap_si)(
     const vsip_vview_si*,
     const vsip_vview_si*);

/* end vsip_vview_si */

/*************************************************/
/*  vsip_vview_uc */
void (vsip_vnot_uc)(
     const vsip_vview_uc*,
     const vsip_vview_uc*);

void (vsip_vand_uc)(
     const vsip_vview_uc*,
     const vsip_vview_uc*,
     const vsip_vview_uc*);

void (vsip_vxor_uc)(
     const vsip_vview_uc*,
     const vsip_vview_uc*,
     const vsip_vview_uc*);

void (vsip_vor_uc)(
     const vsip_vview_uc*,
     const vsip_vview_uc*,
     const vsip_vview_uc*);

void (vsip_vgather_uc)(
     const vsip_vview_uc*,
     const vsip_vview_vi*,
     const vsip_vview_uc*);

void (vsip_vscatter_uc)(
     const vsip_vview_uc*,
     const vsip_vview_uc*,
     const vsip_vview_vi*);

void (vsip_vmul_uc)(
     const vsip_vview_uc*,
     const vsip_vview_uc*,
     const vsip_vview_uc*);

void (vsip_svmul_uc)(
     vsip_scalar_uc,
     const vsip_vview_uc*,
     const vsip_vview_uc*);

void (vsip_svadd_uc)(
     vsip_scalar_uc,
     const vsip_vview_uc*,
     const vsip_vview_uc*);

void (vsip_vadd_uc)(
     const vsip_vview_uc*,
     const vsip_vview_uc*,
     const vsip_vview_uc*);

void (vsip_vsub_uc)(
     const vsip_vview_uc*,
     const vsip_vview_uc*,
     const vsip_vview_uc*);

void (vsip_svsub_uc)(
     vsip_scalar_uc,
     const vsip_vview_uc*,
     const vsip_vview_uc*);

void (vsip_vllt_uc)(
     const vsip_vview_uc*,
     const vsip_vview_uc*,
     const vsip_vview_bl*);

void (vsip_vlle_uc)(
     const vsip_vview_uc*,
     const vsip_vview_uc*,
     const vsip_vview_bl*);

void (vsip_vlgt_uc)(
     const vsip_vview_uc*,
     const vsip_vview_uc*,
     const vsip_vview_bl*);

void (vsip_vlge_uc)(
     const vsip_vview_uc*,
     const vsip_vview_uc*,
     const vsip_vview_bl*);

void (vsip_vleq_uc)(
     const vsip_vview_uc*,
     const vsip_vview_uc*,
     const vsip_vview_bl*);

void (vsip_vlne_uc)(
     const vsip_vview_uc*,
     const vsip_vview_uc*,
     const vsip_vview_bl*);

void (vsip_vclip_uc)(
     const vsip_vview_uc*,
     vsip_scalar_uc,
     vsip_scalar_uc,
     vsip_scalar_uc,
     vsip_scalar_uc,
     const vsip_vview_uc*);

void (vsip_vinvclip_uc)(
     const vsip_vview_uc*,
     vsip_scalar_uc,
     vsip_scalar_uc,
     vsip_scalar_uc,
     vsip_scalar_uc,
     vsip_scalar_uc,
     const vsip_vview_uc*);

void (vsip_vfill_uc)(
     vsip_scalar_uc,
     const vsip_vview_uc*);

void (vsip_vramp_uc)(
     vsip_scalar_uc z,
     vsip_scalar_uc d,
     const vsip_vview_uc*);

vsip_scalar_uc (vsip_vsumval_uc)(
     const vsip_vview_uc*);

void (vsip_vswap_uc)(
     const vsip_vview_uc*,
     const vsip_vview_uc*);

/* end vsip_vview_vi */
/*************************************************/
/* vsip_vview_d */
vsip_scalar_d (vsip_vminval_d)(
     const vsip_vview_d*,
     vsip_index* j);

vsip_scalar_d (vsip_vmaxval_d)(
     const vsip_vview_d*,
     vsip_index*);

void (vsip_vgather_d)(
     const vsip_vview_d*,
     const vsip_vview_vi*,
     const vsip_vview_d*);

void (vsip_vscatter_d)(
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_vi*);

void (vsip_vneg_d)(
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vcumsum_d)(
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vmmul_d)(
     const vsip_vview_d*,
     const vsip_mview_d*,
     vsip_major,
     const vsip_mview_d*);

void (vsip_vmul_d)(
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_svmul_d)(
     vsip_scalar_d,
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vdiv_d)(
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_svdiv_d)(
     vsip_scalar_d,
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vsdiv_d)(
     const vsip_vview_d*,
     vsip_scalar_d,
     const vsip_vview_d*);

void (vsip_vadd_d)(
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_svadd_d)(
     vsip_scalar_d,
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vsub_d)(
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_svsub_d)(
     vsip_scalar_d,
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vam_d)(
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vma_d)(
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vsbm_d)(
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vam_d)(
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vma_d)(
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vsbm_d)(
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vmsb_d)(
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vsam_d)(
     const vsip_vview_d*,
     vsip_scalar_d,
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vsma_d)(
     const vsip_vview_d*,
     vsip_scalar_d,
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vmsa_d)(
     const vsip_vview_d*,
     const vsip_vview_d*,
     vsip_scalar_d,
     const vsip_vview_d*);

void (vsip_vsmsa_d)(
     const vsip_vview_d*,
     vsip_scalar_d,
     vsip_scalar_d,
     const vsip_vview_d*);

void (vsip_vllt_d)(
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_bl*);

void (vsip_vlle_d)(
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_bl*);

void (vsip_vlgt_d)(
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_bl*);

void (vsip_vlge_d)(
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_bl*);

void (vsip_vleq_d)(
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_bl*);

void (vsip_vlne_d)(
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_bl*);

void (vsip_vcos_d)(
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vcosh_d)(
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vsin_d)(
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vsinh_d)(
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vtan_d)(
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vtanh_d)(
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vacos_d)(
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vasin_d)(
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vatan_d)(
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vexp_d)(
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vlog_d)(
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vexp10_d)(
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vlog10_d)(
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vsqrt_d)(
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vmag_d)(
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vatan2_d)(
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vhypot_d)(
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vsq_d)(
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vrecip_d)(
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vrsqrt_d)(
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vexpoavg_d)(
     vsip_scalar_d,
     const vsip_vview_d*,
     const vsip_vview_d* c);

void (vsip_vmin_d)(
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vmax_d)(
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vminmg_d)(
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vmaxmg_d)(
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_vview_d*);

vsip_scalar_d (vsip_vminmgval_d)(
     const vsip_vview_d*,
     vsip_index *j);

vsip_scalar_d (vsip_vmaxmgval_d)(
     const vsip_vview_d*,
     vsip_index *j);

void (vsip_vclip_d)(
     const vsip_vview_d*,
     vsip_scalar_d,
     vsip_scalar_d,
     vsip_scalar_d,
     vsip_scalar_d,
     const vsip_vview_d*);
   
void (vsip_vinvclip_d)(
     const vsip_vview_d*,
     vsip_scalar_d,
     vsip_scalar_d,
     vsip_scalar_d,
     vsip_scalar_d,
     vsip_scalar_d,
     const vsip_vview_d*);

void (vsip_vfill_d)(
     vsip_scalar_d,
     const vsip_vview_d*);
   
void (vsip_vramp_d)(
     vsip_scalar_d,
     vsip_scalar_d,
     const vsip_vview_d*);

vsip_scalar_d (vsip_vsumval_d)(
     const vsip_vview_d*);
   
vsip_scalar_d (vsip_vsumsqval_d)(
     const vsip_vview_d*);

vsip_scalar_d (vsip_vmeanval_d)(
     const vsip_vview_d*);

vsip_scalar_d (vsip_vmeansqval_d)(
     const vsip_vview_d*);

vsip_scalar_d (vsip_vdot_d)(
     const vsip_vview_d*,
     const vsip_vview_d*);

void (vsip_vswap_d)(
     const vsip_vview_d*,
     const vsip_vview_d*);

/*************************************************/
/* vsip_vview_f */
vsip_scalar_f (vsip_vminval_f)(
     const vsip_vview_f*,
     vsip_index* j);

vsip_scalar_f (vsip_vmaxval_f)(
     const vsip_vview_f*,
     vsip_index* j);

void (vsip_vgather_f)(
     const vsip_vview_f*,
     const vsip_vview_vi*,
     const vsip_vview_f*);

void (vsip_vscatter_f)(
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_vi*);

void (vsip_vneg_f)(
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vcumsum_f)(
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vmmul_f)(
     const vsip_vview_f*,
     const vsip_mview_f*,
     vsip_major,
     const vsip_mview_f*);

void (vsip_vmul_f)(
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_svmul_f)(
     vsip_scalar_f,
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vdiv_f)(
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_svdiv_f)(
     vsip_scalar_f,
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vsdiv_f)(
     const vsip_vview_f*,
     vsip_scalar_f,
     const vsip_vview_f*);

void (vsip_vadd_f)(
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_svadd_f)(
     vsip_scalar_f,
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vsub_f)(
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_svsub_f)(
     vsip_scalar_f,
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vam_f)(
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vma_f)(
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vsbm_f)(
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vam_f)(
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vma_f)(
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vsbm_f)(
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vmsb_f)(
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vsam_f)(
     const vsip_vview_f*,
     vsip_scalar_f,
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vsma_f)(
     const vsip_vview_f*,
     vsip_scalar_f,
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vmsa_f)(
     const vsip_vview_f*,
     const vsip_vview_f*,
     vsip_scalar_f,
     const vsip_vview_f*);

void (vsip_vsmsa_f)(
     const vsip_vview_f*,
     vsip_scalar_f,
     vsip_scalar_f,
     const vsip_vview_f*);

void (vsip_vllt_f)(
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_bl*);

void (vsip_vlle_f)(
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_bl*);

void (vsip_vlgt_f)(
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_bl*);

void (vsip_vlge_f)(
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_bl*);

void (vsip_vleq_f)(
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_bl*);

void (vsip_vlne_f)(
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_bl*);

void (vsip_vcos_f)(
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vcosh_f)(
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vsin_f)(
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vsinh_f)(
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vtan_f)(
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vtanh_f)(
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vacos_f)(
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vasin_f)(
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vatan_f)(
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vexp_f)(
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vlog_f)(
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vexp10_f)(
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vlog10_f)(
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vsqrt_f)(
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vmag_f)(
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vatan2_f)(
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vhypot_f)(
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vsq_f)(
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vrecip_f)(
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vrsqrt_f)(
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vexpoavg_f)(
     vsip_scalar_f,
     const vsip_vview_f*,
     const vsip_vview_f* c);

void (vsip_vmin_f)(
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vmax_f)(
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vminmg_f)(
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vmaxmg_f)(
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_vview_f*);

vsip_scalar_f (vsip_vminmgval_f)(
     const vsip_vview_f*,
     vsip_index *j);

vsip_scalar_f (vsip_vmaxmgval_f)(
     const vsip_vview_f*,
     vsip_index *j);

void (vsip_vclip_f)(
     const vsip_vview_f*,
     vsip_scalar_f,
     vsip_scalar_f,
     vsip_scalar_f,
     vsip_scalar_f,
     const vsip_vview_f*);
   
void (vsip_vinvclip_f)(
     const vsip_vview_f*,
     vsip_scalar_f,
     vsip_scalar_f,
     vsip_scalar_f,
     vsip_scalar_f,
     vsip_scalar_f,
     const vsip_vview_f*);

void (vsip_vfill_f)(
     vsip_scalar_f,
     const vsip_vview_f*);
   
void (vsip_vramp_f)(
     vsip_scalar_f z,
     vsip_scalar_f d,
     const vsip_vview_f*);

vsip_scalar_f (vsip_vsumval_f)(
     const vsip_vview_f*);
   
vsip_scalar_f (vsip_vsumsqval_f)(
     const vsip_vview_f*);

vsip_scalar_f (vsip_vmeanval_f)(
     const vsip_vview_f*);

vsip_scalar_f (vsip_vmeansqval_f)(
     const vsip_vview_f*);

vsip_scalar_f (vsip_vdot_f)(
     const vsip_vview_f*,
     const vsip_vview_f*);

void (vsip_vswap_f)(
     const vsip_vview_f*,
     const vsip_vview_f*);

/******************************************************************/
/* vsip_cvview_d */
void (vsip_cvgather_d)(
     const vsip_cvview_d*,
     const vsip_vview_vi*,
     const vsip_cvview_d*);

void (vsip_cvscatter_d)(
     const vsip_cvview_d*,
     const vsip_cvview_d*,
     const vsip_vview_vi*);

void (vsip_cvneg_d)(
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_cvmmul_d)(
     const vsip_cvview_d*,
     const vsip_cmview_d*,
     vsip_major,
     const vsip_cmview_d*);

void (vsip_rvcmmul_d)(
     const vsip_vview_d*,
     const vsip_cmview_d*,
     vsip_major,
     const vsip_cmview_d*);

void (vsip_cvmul_d)(
     const vsip_cvview_d*,
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_csvmul_d)(
     vsip_cscalar_d,
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_rcvmul_d)(
     const vsip_vview_d*,
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_rscvmul_d)(
     vsip_scalar_d,
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_cvdiv_d)(
     const vsip_cvview_d*,
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_csvdiv_d)(
     vsip_cscalar_d,
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_rcvdiv_d)(
     const vsip_vview_d*,
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_rscvdiv_d)(
     vsip_scalar_d,
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_crvdiv_d)(
     const vsip_cvview_d*,
     const vsip_vview_d*,
     const vsip_cvview_d*);

void (vsip_cvrsdiv_d)(
     const vsip_cvview_d*,
     vsip_scalar_d,
     const vsip_cvview_d*);

void (vsip_cvadd_d)(
     const vsip_cvview_d*,
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_csvadd_d)(
     vsip_cscalar_d,
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_rcvadd_d)(
     const vsip_vview_d*,
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_rscvadd_d)(
     vsip_scalar_d,
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_cvsub_d)(
     const vsip_cvview_d*,
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_csvsub_d)(
     vsip_cscalar_d,
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_rcvsub_d)(
     const vsip_vview_d*,
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_rscvsub_d)(
     vsip_scalar_d,
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_crvsub_d)(
     const vsip_cvview_d*,
     const vsip_vview_d*,
     const vsip_cvview_d*);

void (vsip_cvam_d)(
     const vsip_cvview_d*,
     const vsip_cvview_d*,
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_cvma_d)(
     const vsip_cvview_d*,
     const vsip_cvview_d*,
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_cvsbm_d)(
     const vsip_cvview_d*,
     const vsip_cvview_d*,
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_cvmsb_d)(
     const vsip_cvview_d*,
     const vsip_cvview_d*,
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_cvsam_d)(
     const vsip_cvview_d*,
     vsip_cscalar_d,
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_cvsma_d)(
     const vsip_cvview_d*,
     vsip_cscalar_d,
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_cvmsa_d)(
     const vsip_cvview_d*,
     const vsip_cvview_d*,
     vsip_cscalar_d,
     const vsip_cvview_d*);

void (vsip_cvsmsa_d)(
     const vsip_cvview_d*,
     vsip_cscalar_d,
     vsip_cscalar_d,
     const vsip_cvview_d*);

void (vsip_cvleq_d)(
     const vsip_cvview_d*,
     const vsip_cvview_d*,
     const vsip_vview_bl*);

void (vsip_cvlne_d)(
     const vsip_cvview_d*,
     const vsip_cvview_d*,
     const vsip_vview_bl*);

void (vsip_cvexp_d)(
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_cvlog_d)(
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_cvsqrt_d)(
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_cvmag_d)(
     const vsip_cvview_d*,
     const vsip_vview_d*);

void (vsip_varg_d)(
     const vsip_cvview_d*,
     const vsip_vview_d*);

void (vsip_veuler_d)(
     const vsip_vview_d*,
     const vsip_cvview_d*);

vsip_scalar_d (vsip_vmodulate_d)(
     const vsip_vview_d*,
     vsip_scalar_d nu,
     vsip_scalar_d phi,
     const vsip_cvview_d*);

vsip_scalar_d (vsip_cvmodulate_d)(
     const vsip_cvview_d*,
     vsip_scalar_d nu,
     vsip_scalar_d phi,
     const vsip_cvview_d*);

void (vsip_cvconj_d)(
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_cvjmul_d)(
     const vsip_cvview_d*,
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_vcmagsq_d)(
     const vsip_cvview_d*,
     const vsip_vview_d*);

void (vsip_vpolar_d)(
     const vsip_cvview_d*,
     const vsip_vview_d* r,
     const vsip_vview_d* t);

void (vsip_vrect_d)(
     const vsip_vview_d*,
     const vsip_vview_d* t,
     const vsip_cvview_d*);

void (vsip_cvsq_d)(
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_cvrecip_d)(
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_cvrsqrt_d)(
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_cvexpoavg_d)(
     vsip_scalar_d,
     const vsip_cvview_d*,
     const vsip_cvview_d* c);

void (vsip_vcminmgsq_d)(
     const vsip_cvview_d*,
     const vsip_cvview_d*,
     const vsip_vview_d*);

void (vsip_vcmaxmgsq_d)(
     const vsip_cvview_d*,
     const vsip_cvview_d*,
     const vsip_vview_d*);

vsip_scalar_d (vsip_vcminmgsqval_d)(
     const vsip_cvview_d*, 
     vsip_index*);

vsip_scalar_d (vsip_vcmaxmgsqval_d)(
     const vsip_cvview_d*, 
     vsip_index*);

void (vsip_cvfill_d)(
     vsip_cscalar_d,
     const vsip_cvview_d*);

vsip_cscalar_d (vsip_cvsumval_d)(
     const vsip_cvview_d*);

vsip_cscalar_d (vsip_cvsumsqval_d)(
     const vsip_cvview_d*);

vsip_cscalar_d (vsip_cvmeanval_d)(
     const vsip_cvview_d*);

vsip_scalar_d (vsip_cvmeansqval_d)(
     const vsip_cvview_d*);

vsip_cscalar_d (vsip_cvdot_d)(
     const vsip_cvview_d*,
     const vsip_cvview_d*);

vsip_cscalar_d (vsip_cvjdot_d)(
     const vsip_cvview_d*,
     const vsip_cvview_d*);

void (vsip_vreal_d)(
     const vsip_cvview_d*,
     const vsip_vview_d*);

void (vsip_vimag_d)(
     const vsip_cvview_d*,
     const vsip_vview_d*);

void (vsip_vcmplx_d)(
     const vsip_vview_d*,
     const vsip_vview_d*,
     const vsip_cvview_d*);

void (vsip_cvswap_d)(
     const vsip_cvview_d*,
     const vsip_cvview_d*);

/* vsip_cvview_f */
void (vsip_cvgather_f)(
     const vsip_cvview_f*,
     const vsip_vview_vi*,
     const vsip_cvview_f*);

void (vsip_cvscatter_f)(
     const vsip_cvview_f*,
     const vsip_cvview_f*,
     const vsip_vview_vi* index);

void (vsip_cvneg_f)(
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_cvmmul_f)(
     const vsip_cvview_f*,
     const vsip_cmview_f*,
     vsip_major,
     const vsip_cmview_f*);

void (vsip_rvcmmul_f)(
     const vsip_vview_f*,
     const vsip_cmview_f*,
     vsip_major,
     const vsip_cmview_f*);

void (vsip_cvmul_f)(
     const vsip_cvview_f*,
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_csvmul_f)(
     vsip_cscalar_f,
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_rcvmul_f)(
     const vsip_vview_f*,
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_rscvmul_f)(
     vsip_scalar_f,
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_cvdiv_f)(
     const vsip_cvview_f*,
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_csvdiv_f)(
     vsip_cscalar_f,
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_rcvdiv_f)(
     const vsip_vview_f*,
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_rscvdiv_f)(
     vsip_scalar_f,
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_crvdiv_f)(
     const vsip_cvview_f*,
     const vsip_vview_f*,
     const vsip_cvview_f*);

void (vsip_cvrsdiv_f)(
     const vsip_cvview_f*,
     vsip_scalar_f,
     const vsip_cvview_f*);

void (vsip_cvadd_f)(
     const vsip_cvview_f*,
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_csvadd_f)(
     vsip_cscalar_f,
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_rcvadd_f)(
     const vsip_vview_f*,
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_rscvadd_f)(
     vsip_scalar_f,
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_cvsub_f)(
     const vsip_cvview_f*,
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_csvsub_f)(
     vsip_cscalar_f,
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_rcvsub_f)(
     const vsip_vview_f*,
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_rscvsub_f)(
     vsip_scalar_f,
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_crvsub_f)(
     const vsip_cvview_f*,
     const vsip_vview_f*,
     const vsip_cvview_f*);

void (vsip_cvam_f)(
     const vsip_cvview_f*,
     const vsip_cvview_f*,
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_cvma_f)(
     const vsip_cvview_f*,
     const vsip_cvview_f*,
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_cvsbm_f)(
     const vsip_cvview_f*,
     const vsip_cvview_f*,
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_cvmsb_f)(
     const vsip_cvview_f*,
     const vsip_cvview_f*,
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_cvsam_f)(
     const vsip_cvview_f*,
     vsip_cscalar_f,
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_cvsma_f)(
     const vsip_cvview_f*,
     vsip_cscalar_f,
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_cvmsa_f)(
     const vsip_cvview_f*,
     const vsip_cvview_f*,
     vsip_cscalar_f,
     const vsip_cvview_f*);

void (vsip_cvsmsa_f)(
     const vsip_cvview_f*,
     vsip_cscalar_f,
     vsip_cscalar_f,
     const vsip_cvview_f*);

void (vsip_cvleq_f)(
     const vsip_cvview_f*,
     const vsip_cvview_f*,
     const vsip_vview_bl*);

void (vsip_cvlne_f)(
     const vsip_cvview_f*,
     const vsip_cvview_f*,
     const vsip_vview_bl*);

void (vsip_cvexp_f)(
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_cvlog_f)(
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_cvsqrt_f)(
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_cvmag_f)(
     const vsip_cvview_f*,
     const vsip_vview_f*);

void (vsip_varg_f)(
     const vsip_cvview_f*,
     const vsip_vview_f*);

void (vsip_veuler_f)(
     const vsip_vview_f*,
     const vsip_cvview_f*);

vsip_scalar_f (vsip_vmodulate_f)(
     const vsip_vview_f*,
     vsip_scalar_f nu,
     vsip_scalar_f phi,
     const vsip_cvview_f*);

vsip_scalar_f (vsip_cvmodulate_f)(
     const vsip_cvview_f*,
     vsip_scalar_f nu,
     vsip_scalar_f phi,
     const vsip_cvview_f*);

void (vsip_cvconj_f)(
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_cvjmul_f)(
     const vsip_cvview_f*,
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_vcmagsq_f)(
     const vsip_cvview_f*,
     const vsip_vview_f*);

void (vsip_vpolar_f)(
     const vsip_cvview_f*,
     const vsip_vview_f*,
     const vsip_vview_f* t);

void (vsip_vrect_f)(
     const vsip_vview_f*,
     const vsip_vview_f* t,
     const vsip_cvview_f*);

void (vsip_cvsq_f)(
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_cvrecip_f)(
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_cvrsqrt_f)(
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_cvexpoavg_f)(
     vsip_scalar_f,
     const vsip_cvview_f*,
     const vsip_cvview_f* c);

void (vsip_vcminmgsq_f)(
     const vsip_cvview_f*,
     const vsip_cvview_f*,
     const vsip_vview_f*);

void (vsip_vcmaxmgsq_f)(
     const vsip_cvview_f*,
     const vsip_cvview_f*,
     const vsip_vview_f*);

vsip_scalar_f (vsip_vcminmgsqval_f)(
     const vsip_cvview_f*, 
     vsip_index *j);

vsip_scalar_f (vsip_vcmaxmgsqval_f)(
     const vsip_cvview_f*, 
     vsip_index *j);

void (vsip_cvfill_f)(
     vsip_cscalar_f,
     const vsip_cvview_f*);

void (vsip_cvramp_f)(
     vsip_cscalar_f,
     vsip_cscalar_f,
     const vsip_cvview_f*);

vsip_cscalar_f (vsip_cvsumval_f)(
     const vsip_cvview_f*);

vsip_cscalar_f (vsip_cvsumsqval_f)(
     const vsip_cvview_f*);

vsip_cscalar_f (vsip_cvmeanval_f)(
     const vsip_cvview_f*);

vsip_scalar_f (vsip_cvmeansqval_f)(
     const vsip_cvview_f*);

vsip_cscalar_f (vsip_cvdot_f)(
     const vsip_cvview_f*,
     const vsip_cvview_f*);

vsip_cscalar_f (vsip_cvjdot_f)(
     const vsip_cvview_f*,
     const vsip_cvview_f*);

void (vsip_vreal_f)(
     const vsip_cvview_f*,
     const vsip_vview_f*);

void (vsip_vimag_f)(
     const vsip_cvview_f*,
     const vsip_vview_f*);

void (vsip_vcmplx_f)(
     const vsip_vview_f*,
     const vsip_vview_f*,
     const vsip_cvview_f*);

void (vsip_cvswap_f)(
     const vsip_cvview_f*,
     const vsip_cvview_f*);

/* Random */
vsip_randstate *vsip_randcreate(
     vsip_index seed,
     vsip_index numseqs,
     vsip_index,
     vsip_rng portable); 

void vsip_vrandu_f(
     vsip_randstate *state,
     const vsip_vview_f*);

void vsip_cvrandu_f(
     vsip_randstate *state,
     const vsip_cvview_f*);

void vsip_vrandn_f(
     vsip_randstate *state,
     const vsip_vview_f*);

void vsip_cvrandn_f(
     vsip_randstate *state,
     const vsip_cvview_f*);

int  vsip_randdestroy(
     vsip_randstate *state);

void vsip_vrandu_d(
     vsip_randstate *state,
     const vsip_vview_d*);

void vsip_cvrandu_d(
     vsip_randstate *state,
     const vsip_cvview_d*);

void vsip_vrandn_d(
     vsip_randstate *state,
     const vsip_vview_d*);

void vsip_cvrandn_d(
     vsip_randstate *state,
     const vsip_cvview_d*);

/* end Random */

#endif /* _vsip_vview_h */
/* Created RJudd March 9, 1998 */
/* SPAWARSYSCEN D881 */
#ifndef  _vsip_linalg_h
#define  _vsip_linalg_h 1

/* vsip_mview_d */
void (vsip_mvprod3_d)(
      const vsip_mview_d *,
      const vsip_vview_d *,
      const vsip_vview_d *);

void (vsip_mvprod4_d)(
      const vsip_mview_d *,
      const vsip_vview_d *,
      const vsip_vview_d *);

void (vsip_mprod3_d)(
       const vsip_mview_d *, 
       const vsip_mview_d *, 
       const vsip_mview_d *);

void (vsip_mprod4_d)(
       const vsip_mview_d *, 
       const vsip_mview_d *, 
       const vsip_mview_d *);

void (vsip_mprod_d)(
       const vsip_mview_d *, 
       const vsip_mview_d *, 
       const vsip_mview_d *);

void (vsip_mprodt_d)(
       const vsip_mview_d *, 
       const vsip_mview_d *, 
       const vsip_mview_d *);

void (vsip_vmprod_d)(
       const vsip_vview_d *, 
       const vsip_mview_d *, 
       const vsip_vview_d *);

void (vsip_mvprod_d)(
       const vsip_mview_d *, 
       const vsip_vview_d *, 
       const vsip_vview_d *);

void (vsip_mkron_d)(
       vsip_scalar_d,
       const vsip_mview_d *,
       const vsip_mview_d *,
       const vsip_mview_d *);

void (vsip_vkron_d)(
       vsip_scalar_d,
       const vsip_vview_d *,
       const vsip_vview_d *,
       const vsip_mview_d *);

void (vsip_vouter_d)(
       vsip_scalar_d,
       const vsip_vview_d *,
       const vsip_vview_d *,
       const vsip_mview_d *);

void (vsip_mtrans_d)(
       const vsip_mview_d *,
       const vsip_mview_d *);
 
void (vsip_gemp_d)(
       vsip_scalar_d,
       const vsip_mview_d *,
       vsip_mat_op,
       const vsip_mview_d *,
       vsip_mat_op,
       vsip_scalar_d,
       const vsip_mview_d *);

void (vsip_gems_d)(
       vsip_scalar_d,
       const vsip_mview_d *,
       vsip_mat_op,
       vsip_scalar_d,
       const vsip_mview_d *);

/* vsip_mview_f */
void (vsip_mvprod3_f)(
      const vsip_mview_f *,
      const vsip_vview_f *,
      const vsip_vview_f *);

void (vsip_mvprod4_f)(
      const vsip_mview_f *,
      const vsip_vview_f *,
      const vsip_vview_f *);

void (vsip_mprod3_f)(
       const vsip_mview_f *, 
       const vsip_mview_f *, 
       const vsip_mview_f *);

void (vsip_mprod4_f)(
       const vsip_mview_f *, 
       const vsip_mview_f *, 
       const vsip_mview_f *);

void (vsip_mprod_f)(
       const vsip_mview_f *, 
       const vsip_mview_f *, 
       const vsip_mview_f *);

void (vsip_mprodt_f)(
       const vsip_mview_f *, 
       const vsip_mview_f *, 
       const vsip_mview_f *);

void (vsip_vmprod_f)(
       const vsip_vview_f *, 
       const vsip_mview_f *, 
       const vsip_vview_f *);

void (vsip_mvprod_f)(
       const vsip_mview_f *, 
       const vsip_vview_f *, 
       const vsip_vview_f *);

void (vsip_mkron_f)(
       vsip_scalar_f,
       const vsip_mview_f *,
       const vsip_mview_f *,
       const vsip_mview_f *);

void (vsip_vkron_f)(
       vsip_scalar_f,
       const vsip_vview_f *,
       const vsip_vview_f *,
       const vsip_mview_f *);

void (vsip_vouter_f)(
       vsip_scalar_f,
       const vsip_vview_f *,
       const vsip_vview_f *,
       const vsip_mview_f *);

void (vsip_mtrans_f)(
       const vsip_mview_f *,
       const vsip_mview_f *);

void (vsip_gemp_f)(
       vsip_scalar_f,
       const vsip_mview_f *,
       vsip_mat_op,
       const vsip_mview_f *,
       vsip_mat_op,
       vsip_scalar_f,
       const vsip_mview_f *);

void (vsip_gems_f)( 
       vsip_scalar_f,
       const vsip_mview_f *, 
       vsip_mat_op, 
       vsip_scalar_f,
       const vsip_mview_f *); 

/* vsip_cmview_d */
void (vsip_cmvprod3_d)(
      const vsip_cmview_d *,
      const vsip_cvview_d *,
      const vsip_cvview_d *);

void (vsip_cmvprod4_d)(
      const vsip_cmview_d *,
      const vsip_cvview_d *,
      const vsip_cvview_d *);

void (vsip_cmprod3_d)(
       const vsip_cmview_d *, 
       const vsip_cmview_d *, 
       const vsip_cmview_d *);

void (vsip_cmprod4_d)(
       const vsip_cmview_d *, 
       const vsip_cmview_d *, 
       const vsip_cmview_d *);

void (vsip_cmprod_d)(
       const vsip_cmview_d *, 
       const vsip_cmview_d *, 
       const vsip_cmview_d *);

void (vsip_cmprodj_d)(
       const vsip_cmview_d *,
       const vsip_cmview_d *,
       const vsip_cmview_d *);

void (vsip_cmprodt_d)(
       const vsip_cmview_d *, 
       const vsip_cmview_d *, 
       const vsip_cmview_d *);

void (vsip_cmprodh_d)(
       const vsip_cmview_d *, 
       const vsip_cmview_d *, 
       const vsip_cmview_d *);

void (vsip_cvmprod_d)(
       const vsip_cvview_d *, 
       const vsip_cmview_d *, 
       const vsip_cvview_d *);

void (vsip_cmvprod_d)(
       const vsip_cmview_d *, 
       const vsip_cvview_d *, 
       const vsip_cvview_d *);

void (vsip_cvkron_d)(
       vsip_cscalar_d,
       const vsip_cvview_d *,
       const vsip_cvview_d *,
       const vsip_cmview_d *);

void (vsip_cmkron_d)(
       vsip_cscalar_d,
       const vsip_cmview_d *,
       const vsip_cmview_d *,
       const vsip_cmview_d *);

void (vsip_cvouter_d)(
       vsip_cscalar_d,
       const vsip_cvview_d *,
       const vsip_cvview_d *,
       const vsip_cmview_d *);

void (vsip_cmtrans_d)(
       const vsip_cmview_d *,
       const vsip_cmview_d *);

void (vsip_cmherm_d)(
       const vsip_cmview_d *,
       const vsip_cmview_d *);

void (vsip_cgemp_d)(
       vsip_cscalar_d,
       const vsip_cmview_d *,
       vsip_mat_op,
       const vsip_cmview_d *,
       vsip_mat_op,
       vsip_cscalar_d,
       const vsip_cmview_d *);

void (vsip_cgems_d)( 
       vsip_cscalar_d,
       const vsip_cmview_d *, 
       vsip_mat_op, 
       vsip_cscalar_d,
       const vsip_cmview_d *); 


/* vsip_cmview_f */
void (vsip_cmvprod3_f)(
      const vsip_cmview_f *,
      const vsip_cvview_f *,
      const vsip_cvview_f *);

void (vsip_cmvprod4_f)(
      const vsip_cmview_f *,
      const vsip_cvview_f *,
      const vsip_cvview_f *);

void (vsip_cmprod3_f)(
       const vsip_cmview_f *, 
       const vsip_cmview_f *, 
       const vsip_cmview_f *);

void (vsip_cmprod4_f)(
       const vsip_cmview_f *, 
       const vsip_cmview_f *, 
       const vsip_cmview_f *);

void (vsip_cmprod_f)(
       const vsip_cmview_f *, 
       const vsip_cmview_f *, 
       const vsip_cmview_f *);

void (vsip_cmprodj_f)(
       const vsip_cmview_f *,
       const vsip_cmview_f *,
       const vsip_cmview_f *);

void (vsip_cmprodt_f)(
       const vsip_cmview_f *, 
       const vsip_cmview_f *, 
       const vsip_cmview_f *);

void (vsip_cmprodh_f)(
       const vsip_cmview_f *, 
       const vsip_cmview_f *, 
       const vsip_cmview_f *);

void (vsip_cvmprod_f)(
       const vsip_cvview_f *, 
       const vsip_cmview_f *, 
       const vsip_cvview_f *);

void (vsip_cmvprod_f)(
       const vsip_cmview_f *, 
       const vsip_cvview_f *, 
       const vsip_cvview_f *);

void (vsip_cvkron_f)(
       vsip_cscalar_f,
       const vsip_cvview_f *,
       const vsip_cvview_f *,
       const vsip_cmview_f *);

void (vsip_cmkron_f)(
       vsip_cscalar_f,
       const vsip_cmview_f *,
       const vsip_cmview_f *,
       const vsip_cmview_f *);

void (vsip_cvouter_f)(
       vsip_cscalar_f,
       const vsip_cvview_f *,
       const vsip_cvview_f *,
       const vsip_cmview_f *);

void (vsip_cmtrans_f)(
       const vsip_cmview_f *,
       const vsip_cmview_f *);

void (vsip_cmherm_f)(
       const vsip_cmview_f *,
       const vsip_cmview_f *);

void (vsip_cgemp_f)(
       vsip_cscalar_f,
       const vsip_cmview_f *,
       vsip_mat_op,
       const vsip_cmview_f *,
       vsip_mat_op,
       vsip_cscalar_f,
       const vsip_cmview_f *);

void (vsip_cgems_f)(
       vsip_cscalar_f,
       const vsip_cmview_f *,
       vsip_mat_op,
       vsip_cscalar_f,
       const vsip_cmview_f *);


/* vsip_chold_d */
int (vsip_chold_d)(
       vsip_chol_d*,
       const vsip_mview_d*);

int (vsip_cchold_d)(
       vsip_cchol_d*,
       const vsip_cmview_d*);

vsip_chol_d* (vsip_chold_create_d)(
       const vsip_mat_uplo, 
       vsip_length);

vsip_cchol_d* (vsip_cchold_create_d)(
       const vsip_mat_uplo, 
       vsip_length);

int (vsip_cholsol_d)(
       const vsip_chol_d*,
       const vsip_mview_d*);

int (vsip_ccholsol_d)(
       const vsip_cchol_d*,
       const vsip_cmview_d*);

int  (vsip_chold_destroy_d)(
      vsip_chol_d*);

int  (vsip_cchold_destroy_d)(
      vsip_cchol_d*);

void (vsip_chold_getattr_d)(
        const vsip_chol_d *,
        vsip_chol_attr_d *);

void (vsip_cchold_getattr_d)(
        const vsip_cchol_d *,
        vsip_cchol_attr_d *);

/* vsip_chold_f */
int (vsip_chold_f)(
       vsip_chol_f*,
       const vsip_mview_f*);

int (vsip_cchold_f)(
       vsip_cchol_f*,
       const vsip_cmview_f*);

vsip_chol_f* (vsip_chold_create_f)(
       const vsip_mat_uplo, 
       vsip_length);

vsip_cchol_f* (vsip_cchold_create_f)(
       const vsip_mat_uplo, 
       vsip_length);

int (vsip_cholsol_f)(
       const vsip_chol_f*,
       const vsip_mview_f*);

int (vsip_ccholsol_f)(
       const vsip_cchol_f*,
       const vsip_cmview_f*);

int  (vsip_chold_destroy_f)(
      vsip_chol_f*);

int  (vsip_cchold_destroy_f)(
      vsip_cchol_f*);

void (vsip_chold_getattr_f)(
        const vsip_chol_f *,
        vsip_chol_attr_f *);
 
void (vsip_cchold_getattr_f)(
        const vsip_cchol_f *,
        vsip_cchol_attr_f *);

/* vsip_qrd_d */
int (vsip_qrd_d)(
       vsip_qr_d*,
       const vsip_mview_d*);

int (vsip_cqrd_d)(
       vsip_cqr_d*,
       const vsip_cmview_d*);

vsip_qr_d* (vsip_qrd_create_d)(
       vsip_length, 
       vsip_length,
       vsip_qrd_qopt);

vsip_cqr_d* (vsip_cqrd_create_d)(
       vsip_length, 
       vsip_length,
       vsip_qrd_qopt);

int (vsip_qrsol_d)(
        const vsip_qr_d*,
	vsip_qrd_prob,
        const vsip_mview_d*);

int (vsip_cqrsol_d)(
        const vsip_cqr_d*,
	vsip_qrd_prob,
        const vsip_cmview_d*);

int (vsip_qrdsolr_d)(
	const vsip_qr_d *,
	vsip_mat_op opR,
	vsip_scalar_d,
	const vsip_mview_d *);

int (vsip_cqrdsolr_d)(
	const vsip_cqr_d *,
	vsip_mat_op opR,
	vsip_cscalar_d,
	const vsip_cmview_d *);

int vsip_qrdprodq_d(
	const vsip_qr_d*,
	vsip_mat_op,
	vsip_mat_side,
	const vsip_mview_d*);

int vsip_cqrdprodq_d(
	const vsip_cqr_d*,
	vsip_mat_op,
	vsip_mat_side,
	const vsip_cmview_d*);

int  (vsip_qrd_destroy_d)(
          vsip_qr_d*);

int  (vsip_cqrd_destroy_d)(
          vsip_cqr_d*);

void (vsip_qrd_getattr_d)(
        const vsip_qr_d *,
        vsip_qr_attr_d *);

void (vsip_cqrd_getattr_d)(
        const vsip_cqr_d *,
        vsip_cqr_attr_d *);

/* vsip_qrd_f */
int (vsip_qrd_f)(
       vsip_qr_f*,
       const vsip_mview_f*);

int (vsip_cqrd_f)(
       vsip_cqr_f*,
       const vsip_cmview_f*);

vsip_qr_f* (vsip_qrd_create_f)(
       vsip_length, 
       vsip_length,
       vsip_qrd_qopt);

vsip_cqr_f* (vsip_cqrd_create_f)(
       vsip_length, 
       vsip_length,
       vsip_qrd_qopt);

int (vsip_qrsol_f)(
        const vsip_qr_f*,
	vsip_qrd_prob,
        const vsip_mview_f*);

int (vsip_cqrsol_f)(
        const vsip_cqr_f*,
	vsip_qrd_prob,
        const vsip_cmview_f*);

int (vsip_qrdsolr_f)(
	const vsip_qr_f *,
	vsip_mat_op opR,
	vsip_scalar_f,
	const vsip_mview_f *);

int (vsip_cqrdsolr_f)(
	const vsip_cqr_f *,
	vsip_mat_op opR,
	vsip_cscalar_f,
	const vsip_cmview_f *);

int vsip_qrdprodq_f(
	const vsip_qr_f*,
	vsip_mat_op,
	vsip_mat_side,
	const vsip_mview_f*);

int vsip_cqrdprodq_f(
	const vsip_cqr_f*,
	vsip_mat_op,
	vsip_mat_side,
	const vsip_cmview_f*);

int  (vsip_qrd_destroy_f)(
       vsip_qr_f*);

int  (vsip_cqrd_destroy_f)(
       vsip_cqr_f*);

void (vsip_qrd_getattr_f)(
        const vsip_qr_f *,
        vsip_qr_attr_f *);

void (vsip_cqrd_getattr_f)(
        const vsip_cqr_f *,
        vsip_cqr_attr_f *);

/* vsip_lud_d */
void vsip_lud_getattr_d(
       const vsip_lu_d*,
       vsip_lu_attr_d*);

void vsip_clud_getattr_d(
       const vsip_clu_d*,
       vsip_clu_attr_d*);

int (vsip_lud_d)(
       vsip_lu_d*,
       const vsip_mview_d*);

int (vsip_clud_d)(
       vsip_clu_d*,
       const vsip_cmview_d*);

vsip_lu_d* (vsip_lud_create_d)(
       vsip_length);

vsip_clu_d* (vsip_clud_create_d)(
       vsip_length);

void (vsip_lusolve_d)(
       const vsip_lu_d*,
       const vsip_vview_d*,
       const vsip_vview_d*);

int (vsip_lusol_d)(
       const vsip_lu_d*,
       vsip_mat_op,
       const vsip_mview_d*);

int (vsip_clusol_d)(
       const vsip_clu_d*,
       vsip_mat_op,
       const vsip_cmview_d*);

int  (vsip_lud_destroy_d)(
      vsip_lu_d*);

int (vsip_clud_destroy_d)(
      vsip_clu_d*);

/* vsip_lud_f */
void vsip_lud_getattr_f(
       const vsip_lu_f*,
       vsip_lu_attr_f*);

void vsip_clud_getattr_f(
       const vsip_clu_f*,
       vsip_clu_attr_f*);

int (vsip_lud_f)(
       vsip_lu_f*,
       const vsip_mview_f*);
 
int (vsip_clud_f)(
       vsip_clu_f*,
       const vsip_cmview_f*);
 
vsip_lu_f* (vsip_lud_create_f)(
       vsip_length);
 
vsip_clu_f* (vsip_clud_create_f)(
       vsip_length);
 
int (vsip_lusol_f)(
       const vsip_lu_f*,
       vsip_mat_op,
       const vsip_mview_f*);
 
int (vsip_clusol_f)(
       const vsip_clu_f*,
       vsip_mat_op,
       const vsip_cmview_f*);
 
int  (vsip_lud_destroy_f)(
      vsip_lu_f*);
        
int (vsip_clud_destroy_f)(
      vsip_clu_f*);

/* special solvers */ 

int (vsip_covsol_f)( 
      const vsip_mview_f*, 
      const vsip_mview_f*); 
int (vsip_ccovsol_f)(   
      const vsip_cmview_f*, 
      const vsip_cmview_f*); 
int (vsip_llsqsol_f)(   
      const vsip_mview_f*, 
      const vsip_mview_f*); 
int (vsip_cllsqsol_f)(   
      const vsip_cmview_f*, 
      const vsip_cmview_f*); 
int (vsip_toepsol_f)(    
      const vsip_vview_f*, 
      const vsip_vview_f*, 
      const vsip_vview_f*, 
      const vsip_vview_f*); 
int (vsip_ctoepsol_f)( 
      const vsip_cvview_f*, 
      const vsip_cvview_f*, 
      const vsip_cvview_f*, 
      const vsip_cvview_f*); 
 
int (vsip_covsol_d)(  
      const vsip_mview_d*,  
      const vsip_mview_d*);  
int (vsip_ccovsol_d)(    
      const vsip_cmview_d*,  
      const vsip_cmview_d*);  
int (vsip_llsqsol_d)(    
      const vsip_mview_d*,  
      const vsip_mview_d*); 
int (vsip_cllsqsol_d)(    
      const vsip_cmview_d*,  
      const vsip_cmview_d*);  
int (vsip_toepsol_d)(     
      const vsip_vview_d*,  
      const vsip_vview_d*,  
      const vsip_vview_d*,  
      const vsip_vview_d*);  
int (vsip_ctoepsol_d)(  
      const vsip_cvview_d*,  
      const vsip_cvview_d*,  
      const vsip_cvview_d*,  
      const vsip_cvview_d*);  

#endif /*_vsip_linalg_h*/
/* Created by RJuddarch 9, 1998 */
/* SPAWARSYSCEN D881 */
#ifndef _vsip_signal_h
#define _vsip_signal_h 1


/* vsip_vview_d */
vsip_vview_d* (vsip_vcreate_hamming_d)(
     vsip_length, 
     vsip_memory_hint);

vsip_vview_d* (vsip_vcreate_hanning_d)(
     vsip_length, 
     vsip_memory_hint);

vsip_vview_d* (vsip_vcreate_blackman_d)(
     vsip_length, 
     vsip_memory_hint);

vsip_vview_d* (vsip_vcreate_kaiser_d)(
     vsip_length, 
     vsip_scalar_d, 
     vsip_memory_hint);

vsip_vview_d* (vsip_vcreate_cheby_d)(
     vsip_length, 
     vsip_scalar_d, 
     vsip_memory_hint);

void (vsip_cvfreqswap_d)(
     const vsip_cvview_d*);

void (vsip_vfreqswap_d)(
     const vsip_vview_d*);
    
void (vsip_vhisto_d)(
     const vsip_vview_d*, /* input vector */
     vsip_scalar_d, /* min */
     vsip_scalar_d, /* max */
     vsip_hist_opt, /* save state option */
     const vsip_vview_d*); /* output vector */

void (vsip_mhisto_d)(
     const vsip_mview_d*, /* input vector */
     vsip_scalar_d, /* min */
     vsip_scalar_d, /* max */
     vsip_hist_opt, /* save state option */
     const vsip_vview_d*); /* output vector */


/* vsip_vview_f */
vsip_vview_f* (vsip_vcreate_hamming_f)(
     vsip_length,
     vsip_memory_hint);
 
vsip_vview_f* (vsip_vcreate_hanning_f)(
     vsip_length,
     vsip_memory_hint);

vsip_vview_f* (vsip_vcreate_blackman_f)(
     vsip_length,
     vsip_memory_hint);

vsip_vview_f* (vsip_vcreate_kaiser_f)(
     vsip_length,
     vsip_scalar_f,
     vsip_memory_hint);

vsip_vview_f* (vsip_vcreate_cheby_f)(
     vsip_length,
     vsip_scalar_f,
     vsip_memory_hint);

void (vsip_cvfreqswap_f)(
     const vsip_cvview_f*);
 
void (vsip_vfreqswap_f)(
     const vsip_vview_f*);
   
void (vsip_vhisto_f)(
     const vsip_vview_f*,
     vsip_scalar_f min,
     vsip_scalar_f max,
     vsip_hist_opt opt,
     const vsip_vview_f*);

void (vsip_mhisto_f)(
     const vsip_mview_f*, /* input vector */
     vsip_scalar_f, /* min */
     vsip_scalar_f, /* max */
     vsip_hist_opt, /* save state option */
     const vsip_vview_f*); /* output vector */

 
/* vsip_fft_d */
void vsip_fft_getattr_d(
     const vsip_fft_d *fft,
     vsip_fft_attr_d *attr);

vsip_fft_d* vsip_ccfftop_create_d(
     vsip_length   length,      /* length of input data */
     vsip_scalar_d scale,       /* scale factor */
     vsip_fft_dir  sign,        /* fft direction */
     unsigned int  ntimes,      /* number of times */
     vsip_alg_hint hint);

vsip_fft_d* vsip_ccfftip_create_d(
     vsip_length   length,      /* length of input data */
     vsip_scalar_d scale,       /* scale factor */
     vsip_fft_dir  sign,        /* fft direction */
     unsigned int  ntimes,      /* number of times */
     vsip_alg_hint hint);

vsip_fft_d* vsip_rcfftop_create_d(
     vsip_length   length,      /* length of input data */
     vsip_scalar_d scale,       /* scale factor */
     unsigned int  ntimes,      /* number of times */
     vsip_alg_hint hint);

vsip_fft_d* vsip_crfftop_create_d(
     vsip_length   length,      /* length of input data */
     vsip_scalar_d scale,       /* scale factor */
     unsigned int  ntimes,      /* number of times */
     vsip_alg_hint hint);
 
void vsip_ccfftop_d(
     const vsip_fft_d    *fft,
     const vsip_cvview_d *x,
     const vsip_cvview_d  *y);

void vsip_ccfftip_d(
     const vsip_fft_d *fft,
     const vsip_cvview_d *xy);

void vsip_rcfftop_d(
     const vsip_fft_d    *fft,
     const vsip_vview_d  *x,
     const vsip_cvview_d *y);
        
void vsip_crfftop_d(
     const vsip_fft_d    *fft,
     const vsip_cvview_d  *x,
     const vsip_vview_d   *y);

int vsip_fft_destroy_d(
     vsip_fft_d *fft);

/* vsip_fft_f */
void vsip_fft_getattr_f(
       const vsip_fft_f *fft,
       vsip_fft_attr_f *attr);

vsip_fft_f* vsip_ccfftop_create_f(
     vsip_length   length,      /* length of input data */
     vsip_scalar_f scale,       /* scale factor */
     vsip_fft_dir  sign,        /* fft direction */
     unsigned int  ntimes,      /* number of times */
     vsip_alg_hint hint);

vsip_fft_f* vsip_rcfftop_create_f(
     vsip_length   length,      /* length of input data */
     vsip_scalar_f scale,       /* scale factor */
     unsigned int  ntimes,      /* number of times */
     vsip_alg_hint hint);

vsip_fft_f* vsip_crfftop_create_f(
     vsip_length   length,      /* length of input data */
     vsip_scalar_f scale,       /* scale factor */
     unsigned int  ntimes,      /* number of times */
     vsip_alg_hint hint);

vsip_fft_f* vsip_ccfftip_create_f(
     vsip_length   length,      /* length of input data */
     vsip_scalar_f scale,       /* scale factor */
     vsip_fft_dir  sign,        /* fft direction */
     unsigned int  ntimes,      /* number of times */
     vsip_alg_hint hint);

void vsip_ccfftop_f(
     const vsip_fft_f    *fft,
     const vsip_cvview_f *x,
     const vsip_cvview_f *y);

void vsip_rcfftop_f(
     const vsip_fft_f    *fft,
     const vsip_vview_f  *x,
     const vsip_cvview_f *y);
        
void vsip_crfftop_f(
     const vsip_fft_f    *fft,
     const vsip_cvview_f  *x,
     const vsip_vview_f   *y);
        
void vsip_ccfftip_f(
     const vsip_fft_f *fft,
     const vsip_cvview_f *xy);
        
int vsip_fft_destroy_f(
     vsip_fft_f *fft);

/* vsip_fftm_f */
void vsip_fftm_getattr_f(
     const vsip_fftm_f*,
     vsip_fftm_attr_f*);

vsip_fftm_f* vsip_ccfftmop_create_f(
     vsip_length,      /* length of input data column*/
     vsip_length,      /* length of input data row*/
     vsip_scalar_f,       /* scale factor */
     vsip_fft_dir,        /* fft direction */
     vsip_major,
     unsigned int,      /* number of times */
     vsip_alg_hint);
 
vsip_fftm_f* vsip_rcfftmop_create_f(
     vsip_length,      /* length of input data */
     vsip_length,      /* length of input data */
     vsip_scalar_f,       /* scale factor */
     vsip_major,
     unsigned int ,      /* number of times */
     vsip_alg_hint);

vsip_fftm_f* vsip_crfftmop_create_f(
     vsip_length,      /* length of input data */
     vsip_length,      /* length of input data */
     vsip_scalar_f,       /* scale factor */
     vsip_major,
     unsigned int,      /* number of times */
     vsip_alg_hint);
 
vsip_fftm_f* vsip_ccfftmip_create_f(
     vsip_length,      /* length of input data */
     vsip_length,      /* length of input data */
     vsip_scalar_f,       /* scale factor */
     vsip_fft_dir,        /* fft direction */
     vsip_major,
     unsigned int,      /* number of times */
     vsip_alg_hint);
 
void vsip_ccfftmop_f(
     const vsip_fftm_f    *fft,
     const vsip_cmview_f *x,
     const vsip_cmview_f *y);

void vsip_rcfftmop_f(
     const vsip_fftm_f    *fft,
     const vsip_mview_f  *x,
     const vsip_cmview_f *y);

void vsip_crfftmop_f(
     const vsip_fftm_f    *fft,
     const vsip_cmview_f  *x,
     const vsip_mview_f   *y);

void vsip_ccfftmip_f(
     const vsip_fftm_f *fft,
     const vsip_cmview_f *xy);

int vsip_fftm_destroy_f(
     vsip_fftm_f *fft);

/* vsip_fftm_d */
void vsip_fftm_getattr_d(
     const vsip_fftm_d *fft,
     vsip_fftm_attr_d *attr);

vsip_fftm_d* vsip_ccfftmop_create_d(
     vsip_length,      /* length of input data column*/
     vsip_length,      /* length of input data row*/
     vsip_scalar_d,       /* scale factor */
     vsip_fft_dir,        /* fft direction */
     vsip_major,
     unsigned int,      /* number of times */
     vsip_alg_hint);
 
vsip_fftm_d* vsip_rcfftmop_create_d(
     vsip_length,      /* length of input data */
     vsip_length,      /* length of input data */
     vsip_scalar_d,       /* scale factor */
     vsip_major,
     unsigned int ,      /* number of times */
     vsip_alg_hint);
 
vsip_fftm_d* vsip_crfftmop_create_d(
     vsip_length,      /* length of input data */
     vsip_length,      /* length of input data */
     vsip_scalar_d,       /* scale factor */
     vsip_major,
     unsigned int,      /* number of times */
     vsip_alg_hint);

vsip_fftm_d* vsip_ccfftmip_create_d(
     vsip_length,      /* length of input data */
     vsip_length,      /* length of input data */
     vsip_scalar_d,       /* scale factor */
     vsip_fft_dir,        /* fft direction */
     vsip_major,
     unsigned int,      /* number of times */
     vsip_alg_hint);

void vsip_ccfftmop_d(
     const vsip_fftm_d    *fft,
     const vsip_cmview_d *x,
     const vsip_cmview_d *y);

void vsip_rcfftmop_d(
     const vsip_fftm_d    *fft,
     const vsip_mview_d  *x,
     const vsip_cmview_d *y);

void vsip_crfftmop_d(
     const vsip_fftm_d    *fft,
     const vsip_cmview_d  *x,
     const vsip_mview_d   *y);

void vsip_ccfftmip_d(
     const vsip_fftm_d *fft,
     const vsip_cmview_d *xy);

int vsip_fftm_destroy_d(
     vsip_fftm_d *fft);

/* vsip_fir_f */
void vsip_fir_getattr_f(
     const vsip_fir_f*,
     vsip_fir_attr*);

vsip_fir_f* vsip_fir_create_f(
     const vsip_vview_f*,
     vsip_symmetry,
     vsip_length,
     vsip_length,
     vsip_obj_state,
     unsigned int,
     vsip_alg_hint);

int vsip_firflt_f(
     vsip_fir_f*,
     const vsip_vview_f*,
     const vsip_vview_f*);

int vsip_fir_destroy_f(
     vsip_fir_f *filt);

void vsip_fir_reset_f(
     vsip_fir_f *filt);

void vsip_cfir_getattr_f(
     const vsip_cfir_f*,
     vsip_cfir_attr*);

vsip_cfir_f* vsip_cfir_create_f(
     const vsip_cvview_f*,
     vsip_symmetry,
     vsip_length,
     vsip_length,
     vsip_obj_state,
     unsigned int,
     vsip_alg_hint);

int vsip_cfirflt_f(
     vsip_cfir_f*,
     const vsip_cvview_f*,
     const vsip_cvview_f*);

int vsip_cfir_destroy_f(
     vsip_cfir_f *filt);

void vsip_cfir_reset_f(
     vsip_cfir_f *filt);

/* vsip_fir_d */
void vsip_fir_getattr_d( 
     const vsip_fir_d*, 
     vsip_fir_attr*);

vsip_fir_d* vsip_fir_create_d(
     const vsip_vview_d*,
     vsip_symmetry,
     vsip_length,
     vsip_length,
     vsip_obj_state,
     unsigned int,
     vsip_alg_hint);

int vsip_firflt_d(
     vsip_fir_d*,
     const vsip_vview_d*,
     const vsip_vview_d*);

int vsip_fir_destroy_d(
     vsip_fir_d *filt);

void vsip_fir_reset_d(
     vsip_fir_d *filt);

void vsip_cfir_getattr_d(
     const vsip_cfir_d*,
     vsip_cfir_attr*);

vsip_cfir_d* vsip_cfir_create_d(
     const vsip_cvview_d*,
     vsip_symmetry,
     vsip_length,
     vsip_length,
     vsip_obj_state,
     unsigned int,
     vsip_alg_hint);

int vsip_cfirflt_d(
     vsip_cfir_d*,
     const vsip_cvview_d*,
     const vsip_cvview_d*);
 
int vsip_cfir_destroy_d(
     vsip_cfir_d *filt);

void vsip_cfir_reset_d(
     vsip_cfir_d *filt);

/* vsip_corr1d_f */
 
vsip_corr1d_f *vsip_corr1d_create_f(
     vsip_length,
     vsip_length,
     vsip_support_region,
     unsigned int,
     vsip_alg_hint);
 
int vsip_corr1d_destroy_f(
      vsip_corr1d_f*);
 
void vsip_correlate1d_f(
      const vsip_corr1d_f*,
      vsip_bias,
      const vsip_vview_f*,
      const vsip_vview_f*,
      const vsip_vview_f*);

void vsip_corr1d_getattr_f(
      const vsip_corr1d_f*,
      vsip_corr1d_attr*);
      
/* vsip_ccorr1d_f */

vsip_ccorr1d_f *vsip_ccorr1d_create_f(
     vsip_length,
     vsip_length,
     vsip_support_region support,
     unsigned int ntimes,
     vsip_alg_hint hint);

int vsip_ccorr1d_destroy_f(
      vsip_ccorr1d_f *cor);

void vsip_ccorrelate1d_f(
      const vsip_ccorr1d_f*,
      vsip_bias,
      const vsip_cvview_f*,
      const vsip_cvview_f*,
      const vsip_cvview_f*);

void vsip_ccorr1d_getattr_f(
      const vsip_ccorr1d_f*,
      vsip_corr1d_attr*);

/* vsip_corr1d_d */

vsip_corr1d_d *vsip_corr1d_create_d(
     vsip_length,
     vsip_length,
     vsip_support_region,
     unsigned int,
     vsip_alg_hint);

int vsip_corr1d_destroy_d(
      vsip_corr1d_d*);

void vsip_correlate1d_d(
      const vsip_corr1d_d*,
      vsip_bias bias,
      const vsip_vview_d*,
      const vsip_vview_d*,
      const vsip_vview_d*);
 
void vsip_corr1d_getattr_d(
      const vsip_corr1d_d*,
      vsip_corr1d_attr*);
      
/* vsip_ccorr1d_d */
 
vsip_ccorr1d_d *vsip_ccorr1d_create_d(
     vsip_length,
     vsip_length,
     vsip_support_region,
     unsigned int,
     vsip_alg_hint);
 
int vsip_ccorr1d_destroy_d(
      vsip_ccorr1d_d*);
 
void vsip_ccorrelate1d_d(
      const vsip_ccorr1d_d*,
      vsip_bias bias,
      const vsip_cvview_d*,
      const vsip_cvview_d*,
      const vsip_cvview_d*);
 
void vsip_ccorr1d_getattr_d(
      const vsip_ccorr1d_d*,
      vsip_corr1d_attr*);

/* vsip_conv1d_f */
 
vsip_conv1d_f *vsip_conv1d_create_f(
     const vsip_vview_f*,
     vsip_symmetry,
     vsip_length,
     int,
     vsip_support_region,
     unsigned int,
     vsip_alg_hint);
 
int vsip_conv1d_destroy_f(
      vsip_conv1d_f*);
 
void vsip_convolve1d_f(
      const vsip_conv1d_f*,
      const vsip_vview_f*,
      const vsip_vview_f*);

void vsip_conv1d_getattr_f(
      const vsip_conv1d_f*,
      vsip_conv1d_attr *attr);

/* vsip_conv1d_d */
vsip_conv1d_d *vsip_conv1d_create_d(
     const vsip_vview_d*,
     vsip_symmetry symm,
     vsip_length,
     int,
     vsip_support_region,
     unsigned int,
     vsip_alg_hint);
 
int vsip_conv1d_destroy_d(
      vsip_conv1d_d*);
 
void vsip_convolve1d_d(
      const vsip_conv1d_d*,
      const vsip_vview_d*,
      const vsip_vview_d*);

void vsip_conv1d_getattr_d(
      const vsip_conv1d_d*,
      vsip_conv1d_attr *attr);

#endif /*_vsip_signal_h*/

/************************************************************************/
/* elementwise matrix functions */

/**************************************************/
/* vsip_mview_f elementary */
void (vsip_macos_f)(
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_masin_f)(
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_matan_f)(
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_mcos_f)(
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_mcosh_f)(
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_msin_f)(
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_msinh_f)(
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_mtan_f)(
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_mtanh_f)(
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_matan2_f)(
     const vsip_mview_f*,
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_mlog_f)(
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_cmlog_f)(
     const vsip_cmview_f*,
     const vsip_cmview_f*);

void (vsip_cmexp_f)(
     const vsip_cmview_f*,
     const vsip_cmview_f*);

void (vsip_mlog10_f)(
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_mexp_f)(
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_mexp10_f)(
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_msqrt_f)(
     const vsip_mview_f*,
     const vsip_mview_f*);
/*************************************************/
/* vsip_mview_f (matrix unary elementwise functions) */
/* argument input, output */

void (vsip_mrecip_f)(
     const vsip_mview_f*,
     const vsip_mview_f*);

vsip_scalar_f (vsip_mmeansqval_f)(
     const vsip_mview_f*);

vsip_scalar_f (vsip_cmmeansqval_f)(
     const vsip_cmview_f*);

vsip_scalar_f (vsip_mmeanval_f)(
     const vsip_mview_f*);

vsip_cscalar_f (vsip_cmmeanval_f)(
     const vsip_cmview_f*);

vsip_scalar_f (vsip_msumsqval_f)(
     const vsip_mview_f*);

vsip_scalar_f (vsip_msumval_f)(
     const vsip_mview_f*);

vsip_cscalar_f (vsip_cmsumval_f)(
     const vsip_cmview_f*);

void (vsip_mrsqrt_f)(
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_mmag_f)(
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_mcmagsq_f)(
     const vsip_cmview_f*,
     const vsip_mview_f*);

void (vsip_msq_f)(
     const vsip_mview_f*,
     const vsip_mview_f*);

/*************************************************/
/* vsip_mview_f (matrix binary elementwise functions) */
/* argument input, input, output */

void (vsip_smadd_f)(
     vsip_scalar_f,
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_madd_f)(
     const vsip_mview_f*,
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_smmul_f)(
     vsip_scalar_f,
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_mmul_f)(
     const vsip_mview_f*,
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_msub_f)(
     const vsip_mview_f*,
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_smsub_f)(
     vsip_scalar_f,
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_mexpoavg_f)(
     vsip_scalar_f,
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_mhypot_f)(
     const vsip_mview_f*,
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_mdiv_f)(
     const vsip_mview_f*,
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_smdiv_f)(
     vsip_scalar_f,
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_msdiv_f)(
     const vsip_mview_f*,
     vsip_scalar_f,
     const vsip_mview_f*);

/*************************************************/
/* vsip_mview_f (matrix logical elementwise functions) */

void vsip_mleq_f(
     const vsip_mview_f*,
     const vsip_mview_f*,
     const vsip_mview_bl*);

void vsip_mlge_f(
     const vsip_mview_f*,
     const vsip_mview_f*,
     const vsip_mview_bl*);

void vsip_mlgt_f(
     const vsip_mview_f*,
     const vsip_mview_f*,
     const vsip_mview_bl*);

void vsip_mlle_f(
     const vsip_mview_f*,
     const vsip_mview_f*,
     const vsip_mview_bl*);

void vsip_mllt_f(
     const vsip_mview_f*,
     const vsip_mview_f*,
     const vsip_mview_bl*);

void vsip_mlne_f(
     const vsip_mview_f*,
     const vsip_mview_f*,
     const vsip_mview_bl*);

/*************************************************/
/* vsip_mview_f (matrix selection elementwise functions) */
/* argument input, output */

vsip_scalar_f (vsip_mminval_f)(
     const vsip_mview_f*,
     vsip_scalar_mi*);

vsip_scalar_f (vsip_mmaxval_f)(
     const vsip_mview_f*,
     vsip_scalar_mi*);

vsip_scalar_f (vsip_mmaxmgval_f)(
     const vsip_mview_f*,
     vsip_scalar_mi*);

vsip_scalar_f (vsip_mminmgval_f)(
     const vsip_mview_f*,
     vsip_scalar_mi*);

void (vsip_mmaxmg_f)(
     const vsip_mview_f*,
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_mminmg_f)(
     const vsip_mview_f*,
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_mmax_f)(
     const vsip_mview_f*,
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_mmin_f)(
     const vsip_mview_f*,
     const vsip_mview_f*,
     const vsip_mview_f*);

vsip_scalar_f (vsip_mcminmgsqval_f)(
     const vsip_cmview_f*, 
     vsip_scalar_mi*);

void (vsip_mcminmgsq_f)(
     const vsip_cmview_f*, 
     const vsip_cmview_f*, 
     const vsip_mview_f*);

vsip_scalar_f (vsip_mcmaxmgsqval_f)(
     const vsip_cmview_f*, 
     vsip_scalar_mi*);

void (vsip_mcmaxmgsq_f)(
     const vsip_cmview_f*, 
     const vsip_cmview_f*, 
     const vsip_mview_f*);

/*************************************************/
/* vsip_mview_f (matrix element generation ) */

void vsip_mfill_f(
     vsip_scalar_f,
     const vsip_mview_f*);

/*************************************************/
/* vsip_mview_f (matrix manipulation elementwise functions) */
/* argument input, output */

void (vsip_mclip_f)(
     const vsip_mview_f*,
     vsip_scalar_f,
     vsip_scalar_f,
     vsip_scalar_f,
     vsip_scalar_f,
     const vsip_mview_f*);

void (vsip_minvclip_f)(
     const vsip_mview_f*,
     vsip_scalar_f,
     vsip_scalar_f,
     vsip_scalar_f,
     vsip_scalar_f,
     vsip_scalar_f,
     const vsip_mview_f*);

void (vsip_mgather_f)(
     const vsip_mview_f*,
     const vsip_vview_mi*,
     const vsip_vview_f*); 
   
void (vsip_cmgather_f)(
     const vsip_cmview_f*,
     const vsip_vview_mi*,
     const vsip_cvview_f*); 
   
void (vsip_mscatter_f)(
     const vsip_vview_f*,
     const vsip_mview_f*,
     const vsip_vview_mi*);

void (vsip_cmscatter_f)(
     const vsip_cvview_f*,
     const vsip_cmview_f*,
     const vsip_vview_mi*);

void (vsip_mswap_f)(
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_mneg_f)(
     const vsip_mview_f*,
     const vsip_mview_f*);

void (vsip_mcumsum_f)(
     const vsip_mview_f*,
     vsip_major,
     const vsip_mview_f*);

/*************************************************/
/* vsip_cmview_f (matrix unary elementwise functions) */
/* argument input, output */

void (vsip_cmswap_f)(
     const vsip_cmview_f*,
     const vsip_cmview_f*);

void (vsip_cmrecip_f)(
     const vsip_cmview_f*,
     const vsip_cmview_f*);

void (vsip_cmsqrt_f)(
     const vsip_cmview_f*,
     const vsip_cmview_f*);

void (vsip_cmfill_f)(
     vsip_cscalar_f,
     const vsip_cmview_f*);

void (vsip_meuler_f)(
     const vsip_mview_f*,
     const vsip_cmview_f*);

void (vsip_marg_f)(
     const vsip_cmview_f*,
     const vsip_mview_f*);

void (vsip_cmneg_f)(
     const vsip_cmview_f*,
     const vsip_cmview_f*);

void (vsip_cmconj_f)(
     const vsip_cmview_f*,
     const vsip_cmview_f*);

void (vsip_cmmag_f)(
     const vsip_cmview_f*,
     const vsip_mview_f*);


/*************************************************/
/* vsip_cmview_f (complex matrix binary elementwise functions) */
/* argument: complex input, complex input, complex output */

void (vsip_cmadd_f)(
     const vsip_cmview_f*,
     const vsip_cmview_f*,
     const vsip_cmview_f*);

void (vsip_csmadd_f)(
     vsip_cscalar_f,
     const vsip_cmview_f*,
     const vsip_cmview_f*);

void (vsip_cmmul_f)(
     const vsip_cmview_f*,
     const vsip_cmview_f*,
     const vsip_cmview_f*);

void (vsip_csmmul_f)(
     vsip_cscalar_f,
     const vsip_cmview_f*,
     const vsip_cmview_f*);

void (vsip_cmdiv_f)(
     const vsip_cmview_f*,
     const vsip_cmview_f*,
     const vsip_cmview_f*);

void (vsip_rcmdiv_f)(
     const vsip_mview_f*,
     const vsip_cmview_f*,
     const vsip_cmview_f*);

void (vsip_crmdiv_f)(
     const vsip_cmview_f*,
     const vsip_mview_f*,
     const vsip_cmview_f*);

void (vsip_rscmdiv_f)(
     vsip_scalar_f,
     const vsip_cmview_f*,
     const vsip_cmview_f*);

void (vsip_csmdiv_f)(
     vsip_cscalar_f,
     const vsip_cmview_f*,
     const vsip_cmview_f*);

void (vsip_cmexpoavg_f)(
     vsip_scalar_f,
     const vsip_cmview_f*,
     const vsip_cmview_f*);

void (vsip_cmjmul_f)(
     const vsip_cmview_f*,
     const vsip_cmview_f*,
     const vsip_cmview_f*);

void (vsip_csmsub_f)(
     vsip_cscalar_f,
     const vsip_cmview_f*,
     const vsip_cmview_f*);

void (vsip_cmrsdiv_f)(
     const vsip_cmview_f*,
     vsip_scalar_f,
     const vsip_cmview_f*);

void (vsip_rcmadd_f)(
     const vsip_mview_f*,
     const vsip_cmview_f*,
     const vsip_cmview_f*);

void (vsip_rscmadd_f)(
     vsip_scalar_f,
     const vsip_cmview_f*,
     const vsip_cmview_f*);

void (vsip_rcmmul_f)(
     const vsip_mview_f*,
     const vsip_cmview_f*,
     const vsip_cmview_f*);

void (vsip_rscmmul_f)(
     vsip_scalar_f,
     const vsip_cmview_f*,
     const vsip_cmview_f*);

void (vsip_rcmsub_f)(
     const vsip_mview_f*,
     const vsip_cmview_f*,
     const vsip_cmview_f*);

void (vsip_crmsub_f)(
     const vsip_cmview_f*,
     const vsip_mview_f*,
     const vsip_cmview_f*);

void (vsip_cmsub_f)(
     const vsip_cmview_f*,
     const vsip_cmview_f*,
     const vsip_cmview_f*);

void (vsip_rscmsub_f)(
     vsip_scalar_f,
     const vsip_cmview_f*,
     const vsip_cmview_f*);


/**************************************************/
/* vsip_mview_d elementary */
void (vsip_macos_d)(
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_masin_d)(
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_matan_d)(
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_mcos_d)(
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_mcosh_d)(
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_msin_d)(
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_msinh_d)(
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_mtan_d)(
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_mtanh_d)(
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_matan2_d)(
     const vsip_mview_d*,
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_mlog_d)(
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_cmlog_d)(
     const vsip_cmview_d*,
     const vsip_cmview_d*);

void (vsip_cmexp_d)(
     const vsip_cmview_d*,
     const vsip_cmview_d*);

void (vsip_mlog10_d)(
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_mexp_d)(
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_mexp10_d)(
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_msqrt_d)(
     const vsip_mview_d*,
     const vsip_mview_d*);
/*************************************************/
/* vsip_mview_d (matrix unary elementwise functions) */
/* argument input, output */

void (vsip_mrecip_d)(
     const vsip_mview_d*,
     const vsip_mview_d*);

vsip_scalar_d (vsip_mmeansqval_d)(
     const vsip_mview_d*);

vsip_scalar_d (vsip_cmmeansqval_d)(
     const vsip_cmview_d*);

vsip_scalar_d (vsip_mmeanval_d)(
     const vsip_mview_d*);

vsip_cscalar_d (vsip_cmmeanval_d)(
     const vsip_cmview_d*);

vsip_scalar_d (vsip_msumsqval_d)(
     const vsip_mview_d*);

vsip_scalar_d (vsip_msumval_d)(
     const vsip_mview_d*);
                     
vsip_cscalar_d (vsip_cmsumval_d)(
     const vsip_cmview_d*);

void (vsip_mmag_d)(
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_mcmagsq_d)(
     const vsip_cmview_d*,
     const vsip_mview_d*);

void (vsip_mrsqrt_d)(
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_msq_d)(
     const vsip_mview_d*,
     const vsip_mview_d*);

/*************************************************/
/* vsip_mview_d (matrix binary elementwise functions) */
/* argument input, input, output */

void (vsip_smadd_d)(
     vsip_scalar_d,
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_madd_d)(
     const vsip_mview_d*,
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_smmul_d)(
     vsip_scalar_d,
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_mmul_d)(
     const vsip_mview_d*,
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_msub_d)(
     const vsip_mview_d*,
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_smsub_d)(
     vsip_scalar_d,
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_mexpoavg_d)(
  vsip_scalar_d,
  const vsip_mview_d*,
  const vsip_mview_d*);

void (vsip_mhypot_d)(
     const vsip_mview_d*,
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_mdiv_d)(
     const vsip_mview_d*,
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_smdiv_d)(
     vsip_scalar_d,
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_msdiv_d)(
     const vsip_mview_d*,
     vsip_scalar_d,
     const vsip_mview_d*);

/*************************************************/
/* vsip_mview_d (matrix logical elementwise functions) */

void vsip_mleq_d(
     const vsip_mview_d*,
     const vsip_mview_d*,
     const vsip_mview_bl*);

void vsip_mlge_d(
     const vsip_mview_d*,
     const vsip_mview_d*,
     const vsip_mview_bl*);

void vsip_mlgt_d(
     const vsip_mview_d*,
     const vsip_mview_d*,
     const vsip_mview_bl*);

void vsip_mlle_d(
     const vsip_mview_d*,
     const vsip_mview_d*,
     const vsip_mview_bl*);

void vsip_mllt_d(
     const vsip_mview_d*,
     const vsip_mview_d*,
     const vsip_mview_bl*);

void vsip_mlne_d(
     const vsip_mview_d*,
     const vsip_mview_d*,
     const vsip_mview_bl*);


/*************************************************/
/* vsip_cmview_d (matrix unary elementwise functions) */
/* argument input, output */

void (vsip_cmswap_d)(
     const vsip_cmview_d*,
     const vsip_cmview_d*);

void (vsip_cmrecip_d)(
     const vsip_cmview_d*,
     const vsip_cmview_d*);

void (vsip_cmsqrt_d)(
     const vsip_cmview_d*,
     const vsip_cmview_d*);

void (vsip_cmfill_d)(
     vsip_cscalar_d,
     const vsip_cmview_d*);

void (vsip_meuler_d)(
     const vsip_mview_d*,
     const vsip_cmview_d*);

void (vsip_marg_d)(
     const vsip_cmview_d*,
     const vsip_mview_d*);

void (vsip_cmneg_d)(
     const vsip_cmview_d*,
     const vsip_cmview_d*);

void (vsip_cmconj_d)(
     const vsip_cmview_d*,
     const vsip_cmview_d*);

void (vsip_cmmag_d)(
     const vsip_cmview_d*,
     const vsip_mview_d*);


/*************************************************/
/* vsip_cmview_d (complex matrix binary elementwise functions) */
/* argument: complex input, complex input, complex output */

void (vsip_cmadd_d)(
     const vsip_cmview_d*,
     const vsip_cmview_d*,
     const vsip_cmview_d*);

void (vsip_csmadd_d)(
     vsip_cscalar_d,
     const vsip_cmview_d*,
     const vsip_cmview_d*);

void (vsip_cmmul_d)(
     const vsip_cmview_d*,
     const vsip_cmview_d*,
     const vsip_cmview_d*);

void (vsip_csmmul_d)(
     vsip_cscalar_d,
     const vsip_cmview_d*,
     const vsip_cmview_d*);

void (vsip_cmdiv_d)(
     const vsip_cmview_d*,
     const vsip_cmview_d*,
     const vsip_cmview_d*);

void (vsip_rcmdiv_d)(
     const vsip_mview_d*,
     const vsip_cmview_d*,
     const vsip_cmview_d*);

void (vsip_crmdiv_d)(
     const vsip_cmview_d*,
     const vsip_mview_d*,
     const vsip_cmview_d*);

void (vsip_rscmdiv_d)(
     vsip_scalar_d,
     const vsip_cmview_d*,
     const vsip_cmview_d*);

void (vsip_csmdiv_d)(
     vsip_cscalar_d,
     const vsip_cmview_d*,
     const vsip_cmview_d*);

void (vsip_cmexpoavg_d)(
     vsip_scalar_d,
     const vsip_cmview_d*,
     const vsip_cmview_d*);

void (vsip_cmjmul_d)(
     const vsip_cmview_d*,
     const vsip_cmview_d*,
     const vsip_cmview_d*);

void (vsip_csmsub_d)(
     vsip_cscalar_d,
     const vsip_cmview_d*,
     const vsip_cmview_d*);

void (vsip_cmrsdiv_d)(
     const vsip_cmview_d*,
     vsip_scalar_d,
     const vsip_cmview_d*);

void (vsip_rcmadd_d)(
     const vsip_mview_d*,
     const vsip_cmview_d*,
     const vsip_cmview_d*);

void (vsip_rscmadd_d)(
     vsip_scalar_d,
     const vsip_cmview_d*,
     const vsip_cmview_d*);

void (vsip_rcmmul_d)(
     const vsip_mview_d*,
     const vsip_cmview_d*,
     const vsip_cmview_d*);

void (vsip_rscmmul_d)(
     vsip_scalar_d,
     const vsip_cmview_d*,
     const vsip_cmview_d*);

void (vsip_rcmsub_d)(
     const vsip_mview_d*,
     const vsip_cmview_d*,
     const vsip_cmview_d*);

void (vsip_crmsub_d)(
     const vsip_cmview_d*,
     const vsip_mview_d*,
     const vsip_cmview_d*);

void (vsip_cmsub_d)(
     const vsip_cmview_d*,
     const vsip_cmview_d*,
     const vsip_cmview_d*);

void (vsip_rscmsub_d)(
     vsip_scalar_d,
     const vsip_cmview_d*,
     const vsip_cmview_d*);

/*************************************************/
/* vsip_mview_d (matrix selection elementwise functions) */
/* argument input, output */

vsip_scalar_d (vsip_mminval_d)(
     const vsip_mview_d*,
     vsip_scalar_mi*);

vsip_scalar_d (vsip_mmaxval_d)(
     const vsip_mview_d*,
     vsip_scalar_mi*);

vsip_scalar_d (vsip_mmaxmgval_d)(
     const vsip_mview_d*,
     vsip_scalar_mi*);

vsip_scalar_d (vsip_mminmgval_d)(
     const vsip_mview_d*,
     vsip_scalar_mi*);

void (vsip_mmaxmg_d)(
     const vsip_mview_d*,
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_mminmg_d)(
     const vsip_mview_d*,
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_mmax_d)(
     const vsip_mview_d*,
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_mmin_d)(
     const vsip_mview_d*,
     const vsip_mview_d*,
     const vsip_mview_d*);

vsip_scalar_d (vsip_mcminmgsqval_d)(
     const vsip_cmview_d*, 
     vsip_scalar_mi*);

void (vsip_mcminmgsq_d)(
     const vsip_cmview_d*, 
     const vsip_cmview_d*, 
     const vsip_mview_d*);

vsip_scalar_d (vsip_mcmaxmgsqval_d)(
     const vsip_cmview_d*, 
     vsip_scalar_mi*);

void (vsip_mcmaxmgsq_d)(
     const vsip_cmview_d*, 
     const vsip_cmview_d*, 
     const vsip_mview_d*);

/*************************************************/
/* vsip_mview_d (matrix element generation ) */

void vsip_mfill_d(
     vsip_scalar_d,
     const vsip_mview_d*);

/*************************************************/
/* vsip_mview_d (matrix manipulation elementwise functions) */

void (vsip_mclip_d)(
     const vsip_mview_d*,
     vsip_scalar_d,
     vsip_scalar_d,
     vsip_scalar_d,
     vsip_scalar_d,
     const vsip_mview_d*);

void (vsip_minvclip_d)(
     const vsip_mview_d*,
     vsip_scalar_d t1,
  vsip_scalar_d t2,
  vsip_scalar_d t3,
  vsip_scalar_d c1,
  vsip_scalar_d c2,
  const vsip_mview_d*);

void (vsip_mgather_d)(
  const vsip_mview_d*,
  const vsip_vview_mi*,
  const vsip_vview_d*);

void (vsip_cmgather_d)(
  const vsip_cmview_d*,
  const vsip_vview_mi*,
  const vsip_cvview_d*);

void (vsip_mscatter_d)(
  const vsip_vview_d*,
  const vsip_mview_d*,
  const vsip_vview_mi*);

void (vsip_cmscatter_d)(
  const vsip_cvview_d*,
  const vsip_cmview_d*,
  const vsip_vview_mi*);

void (vsip_mswap_d)(
  const vsip_mview_d*,
  const vsip_mview_d*);

void (vsip_mneg_d)(
     const vsip_mview_d*,
     const vsip_mview_d*);

void (vsip_mcumsum_d)(
     const vsip_mview_d*,
     vsip_major,
     const vsip_mview_d*);

/*************************************************/
/* vsip_mview_bl (matrix boolean) */
/* argument input, output */
vsip_scalar_vi (vsip_msumval_bl)(
  const vsip_mview_bl*);

vsip_scalar_bl (vsip_manytrue_bl)(
  const vsip_mview_bl*);

vsip_scalar_bl (vsip_malltrue_bl)(
  const vsip_mview_bl*);

vsip_length (vsip_mindexbool)( 
     const vsip_mview_bl*, 
     vsip_vview_mi*);

/***************************************************/
/* tensor view support */
/* */
void vsip_talldestroy_f(
     vsip_tview_f*);

void vsip_talldestroy_d(
     vsip_tview_d*);

void vsip_talldestroy_i(
     vsip_tview_i*);
     
void vsip_talldestroy_si(
     vsip_tview_si*);

void vsip_talldestroy_uc(
     vsip_tview_uc*);

void vsip_ctalldestroy_f(
     vsip_ctview_f*);

void vsip_ctalldestroy_d(
     vsip_ctview_d*);

/* */
vsip_tview_f *vsip_tbind_f(
     const vsip_block_f*,
     vsip_offset,
     vsip_stride,
     vsip_length,
     vsip_stride,
     vsip_length,
     vsip_stride,
     vsip_length);

vsip_tview_d *vsip_tbind_d(
     const vsip_block_d *block,
     vsip_offset,
     vsip_stride,
     vsip_length,
     vsip_stride,
     vsip_length,
     vsip_stride,
     vsip_length);

vsip_tview_i *vsip_tbind_i(
     const vsip_block_i*,
     vsip_offset,
     vsip_stride,
     vsip_length,
     vsip_stride,
     vsip_length,
     vsip_stride,
     vsip_length);

vsip_tview_si *vsip_tbind_si(
     const vsip_block_si*,
     vsip_offset,
     vsip_stride,
     vsip_length,
     vsip_stride,
     vsip_length,
     vsip_stride,
     vsip_length);

vsip_tview_uc *vsip_tbind_uc(
     const vsip_block_uc*,
     vsip_offset,
     vsip_stride,
     vsip_length,
     vsip_stride,
     vsip_length,
     vsip_stride,
     vsip_length);

vsip_ctview_f *vsip_ctbind_f(
     const vsip_cblock_f*,
     vsip_offset,
     vsip_stride,
     vsip_length,
     vsip_stride,
     vsip_length,
     vsip_stride,
     vsip_length);

vsip_ctview_d *vsip_ctbind_d(
     const vsip_cblock_d*,
     vsip_offset,
     vsip_stride,
     vsip_length,
     vsip_stride,
     vsip_length,
     vsip_stride,
     vsip_length);

/* */

vsip_tview_f *vsip_tcloneview_f(
     const vsip_tview_f*);

vsip_tview_d *vsip_tcloneview_d(
     const vsip_tview_d*);

vsip_tview_i *vsip_tcloneview_i(
     const vsip_tview_i*);

vsip_tview_si *vsip_tcloneview_si(
     const vsip_tview_si*);

vsip_tview_uc *vsip_tcloneview_uc(
     const vsip_tview_uc*);

vsip_ctview_f *vsip_ctcloneview_f(
     const vsip_ctview_f*);

vsip_ctview_d *vsip_ctcloneview_d(
     const vsip_ctview_d*);

/* */

vsip_tview_f* vsip_tcreate_f(
     vsip_length,
     vsip_length,
     vsip_length,
     vsip_tmajor,
     vsip_memory_hint);


vsip_tview_d* vsip_tcreate_d(
     vsip_length,
     vsip_length,
     vsip_length,
     vsip_tmajor,
     vsip_memory_hint);


vsip_tview_i* vsip_tcreate_i(
     vsip_length,
     vsip_length,
     vsip_length,
     vsip_tmajor,
     vsip_memory_hint);

vsip_tview_si* vsip_tcreate_si(
     vsip_length,
     vsip_length,
     vsip_length,
     vsip_tmajor,
     vsip_memory_hint);

vsip_tview_uc* vsip_tcreate_uc(
     vsip_length,
     vsip_length,
     vsip_length,
     vsip_tmajor,
     vsip_memory_hint);


vsip_ctview_f* vsip_ctcreate_f(
     vsip_length,
     vsip_length,
     vsip_length,
     vsip_tmajor,
     vsip_memory_hint);


vsip_ctview_d* vsip_ctcreate_d(
     vsip_length,
     vsip_length,
     vsip_length,
     vsip_tmajor,
     vsip_memory_hint);

/* */

vsip_block_f *vsip_tdestroy_f(
     vsip_tview_f*);

vsip_block_d *vsip_tdestroy_d(
     vsip_tview_d*);

vsip_block_i *vsip_tdestroy_i(
     vsip_tview_i*);

vsip_block_si *vsip_tdestroy_si(
     vsip_tview_si*);

vsip_block_uc *vsip_tdestroy_uc(
     vsip_tview_uc*);

vsip_cblock_f *vsip_ctdestroy_f(
     vsip_ctview_f*);

vsip_cblock_d *vsip_ctdestroy_d(
     vsip_ctview_d*);

/* */

vsip_scalar_f vsip_tget_f (
     const vsip_tview_f*,
     vsip_index,
     vsip_index,
     vsip_index);

vsip_scalar_d vsip_tget_d (
     const vsip_tview_d*,
     vsip_index,
     vsip_index,
     vsip_index);

vsip_scalar_i vsip_tget_i (
     const vsip_tview_i*,
     vsip_index,
     vsip_index,
     vsip_index);

vsip_scalar_si vsip_tget_si (
     const vsip_tview_si*,
     vsip_index,
     vsip_index,
     vsip_index);

vsip_scalar_uc vsip_tget_uc (
     const vsip_tview_uc*,
     vsip_index,
     vsip_index,
     vsip_index);

vsip_cscalar_f vsip_ctget_f (
     const vsip_ctview_f*,
     vsip_index,
     vsip_index,
     vsip_index);

vsip_cscalar_d vsip_ctget_d (
     const vsip_ctview_d*,
     vsip_index,
     vsip_index,
     vsip_index);

/* */

void vsip_tgetattrib_f(
     const vsip_tview_f*,
     vsip_tattr_f*);

void vsip_tgetattrib_d(
     const vsip_tview_d*,
     vsip_tattr_d*);

void vsip_tgetattrib_i(
     const vsip_tview_i*,
     vsip_tattr_i*);

void vsip_tgetattrib_si(
     const vsip_tview_si*,
     vsip_tattr_si*);

void vsip_tgetattrib_uc(
     const vsip_tview_uc*,
     vsip_tattr_uc*);

void vsip_ctgetattrib_f(
     const vsip_ctview_f*,
     vsip_ctattr_f*);

void vsip_ctgetattrib_d(
     const vsip_ctview_d*,
     vsip_ctattr_d*);

/* */

vsip_block_f *vsip_tgetblock_f(
     const vsip_tview_f*);

vsip_block_d *vsip_tgetblock_d(
     const vsip_tview_d*);

vsip_block_i *vsip_tgetblock_i(
     const vsip_tview_i*);

vsip_block_si *vsip_tgetblock_si(
     const vsip_tview_si*);

vsip_block_uc *vsip_tgetblock_uc(
     const vsip_tview_uc*);

vsip_cblock_f *vsip_ctgetblock_f(
     const vsip_ctview_f*);

vsip_cblock_d *vsip_ctgetblock_d(
     const vsip_ctview_d*);

/* */

vsip_offset vsip_tgetoffset_f(
     const vsip_tview_f*);

vsip_offset vsip_tgetoffset_d(
     const vsip_tview_d*);

vsip_offset vsip_tgetoffset_i(
     const vsip_tview_i*);

vsip_offset vsip_tgetoffset_si(
     const vsip_tview_si*);

vsip_offset vsip_tgetoffset_uc(
     const vsip_tview_uc*);

vsip_offset vsip_ctgetoffset_f(
     const vsip_ctview_f*);

vsip_offset vsip_ctgetoffset_d(
     const vsip_ctview_d*);

/* */

vsip_length vsip_tgetxlength_f(
     const vsip_tview_f*);

vsip_length vsip_tgetxlength_d(
     const vsip_tview_d*);

vsip_length vsip_tgetxlength_i(
     const vsip_tview_i*);

vsip_length vsip_tgetxlength_si(
     const vsip_tview_si*);

vsip_length vsip_tgetxlength_uc(
     const vsip_tview_uc*);

vsip_length vsip_ctgetxlength_f(
     const vsip_ctview_f*);

vsip_length vsip_ctgetxlength_d(
     const vsip_ctview_d*);

/* */

vsip_length vsip_tgetylength_f(
     const vsip_tview_f*);

vsip_length vsip_tgetylength_d(
     const vsip_tview_d*);

vsip_length vsip_tgetylength_i(
     const vsip_tview_i*);

vsip_length vsip_tgetylength_si(
     const vsip_tview_si*);

vsip_length vsip_tgetylength_uc(
     const vsip_tview_uc*);

vsip_length vsip_ctgetylength_f(
     const vsip_ctview_f*);

vsip_length vsip_ctgetylength_d(
     const vsip_ctview_d*);

/* */

vsip_length vsip_tgetzlength_f(
     const vsip_tview_f*);

vsip_length vsip_tgetzlength_d(
     const vsip_tview_d*);

vsip_length vsip_tgetzlength_i(
     const vsip_tview_i*);

vsip_length vsip_tgetzlength_si(
     const vsip_tview_si*);

vsip_length vsip_tgetzlength_uc(
     const vsip_tview_uc*);

vsip_length vsip_ctgetzlength_f(
     const vsip_ctview_f*);

vsip_length vsip_ctgetzlength_d(
     const vsip_ctview_d*);

/* */

vsip_stride vsip_tgetxstride_f(
     const vsip_tview_f*);

vsip_stride vsip_tgetxstride_d(
     const vsip_tview_d*);

vsip_stride vsip_tgetxstride_i(
     const vsip_tview_i*);

vsip_stride vsip_tgetxstride_si(
     const vsip_tview_si*);

vsip_stride vsip_tgetxstride_uc(
     const vsip_tview_uc*);

vsip_stride vsip_ctgetxstride_f(
     const vsip_ctview_f*);

vsip_stride vsip_ctgetxstride_d(
     const vsip_ctview_d*);

/* */

vsip_stride vsip_tgetystride_f(
     const vsip_tview_f*);

vsip_stride vsip_tgetystride_d(
     const vsip_tview_d*);

vsip_stride vsip_tgetystride_i(
     const vsip_tview_i*);

vsip_stride vsip_tgetystride_si(
     const vsip_tview_si*);

vsip_stride vsip_tgetystride_uc(
     const vsip_tview_uc*);

vsip_stride vsip_ctgetystride_f(
     const vsip_ctview_f*);

vsip_stride vsip_ctgetystride_d(
     const vsip_ctview_d*);

/* */

vsip_stride vsip_tgetzstride_f(
     const vsip_tview_f*);

vsip_stride vsip_tgetzstride_d(
     const vsip_tview_d*);

vsip_stride vsip_tgetzstride_i(
     const vsip_tview_i*);

vsip_stride vsip_tgetzstride_si(
     const vsip_tview_si*);

vsip_stride vsip_tgetzstride_uc(
     const vsip_tview_uc*);

vsip_stride vsip_ctgetzstride_f(
     const vsip_ctview_f*);

vsip_stride vsip_ctgetzstride_d(
     const vsip_ctview_d*);

/* */

vsip_mview_si *vsip_tmatrixview_si(
     const vsip_tview_si*,
     vsip_tmslice,
     vsip_index);

vsip_mview_uc *vsip_tmatrixview_uc(
     const vsip_tview_uc*,
     vsip_tmslice,
     vsip_index);

vsip_mview_i *vsip_tmatrixview_i(
     const vsip_tview_i*,
     vsip_tmslice,
     vsip_index);

vsip_mview_f *vsip_tmatrixview_f(
     const vsip_tview_f*,
     vsip_tmslice,
     vsip_index);

vsip_mview_d *vsip_tmatrixview_d(
     const vsip_tview_d*,
     vsip_tmslice,
     vsip_index);

vsip_cmview_f *vsip_ctmatrixview_f(
     const vsip_ctview_f*,
     vsip_tmslice,
     vsip_index);

vsip_cmview_d *vsip_ctmatrixview_d(
     const vsip_ctview_d*,
     vsip_tmslice,
     vsip_index);

/* */

void vsip_tput_f (
     const vsip_tview_f*,
     vsip_index,
     vsip_index,
     vsip_index,
     vsip_scalar_f);

void vsip_tput_d (
     const vsip_tview_d*,
     vsip_index,
     vsip_index,
     vsip_index,
     vsip_scalar_d);

void vsip_tput_i (
     const vsip_tview_i*,
     vsip_index,
     vsip_index,
     vsip_index,
     vsip_scalar_i);

void vsip_tput_si (
     const vsip_tview_si*,
     vsip_index,
     vsip_index,
     vsip_index,
     vsip_scalar_si);

void vsip_tput_uc (
     const vsip_tview_uc*,
     vsip_index,
     vsip_index,
     vsip_index,
     vsip_scalar_uc);

void vsip_ctput_f (
     const vsip_ctview_f*,
     vsip_index,
     vsip_index,
     vsip_index,
     vsip_cscalar_f);

void vsip_ctput_d (
     const vsip_ctview_d*,
     vsip_index,
     vsip_index,
     vsip_index,
     vsip_cscalar_d);

/* */

void vsip_tputattrib_f(
     vsip_tview_f*,
     const vsip_tattr_f*);

void vsip_tputattrib_d(
     vsip_tview_d*,
     const vsip_tattr_d*);

void vsip_tputattrib_i(
     vsip_tview_i*,
     const vsip_tattr_i*);

void vsip_tputattrib_si(
     vsip_tview_si*,
     const vsip_tattr_si*);

void vsip_tputattrib_uc(
     vsip_tview_uc*,
     const vsip_tattr_uc*);

void vsip_ctputattrib_f(
     vsip_ctview_f*,
     const vsip_ctattr_f*);

void vsip_ctputattrib_d(
     vsip_ctview_d*,
     const vsip_ctattr_d*);

/* */

vsip_tview_f *vsip_tputoffset_f (
     vsip_tview_f*,
     vsip_offset);

vsip_tview_d *vsip_tputoffset_d (
     vsip_tview_d*,
     vsip_offset);

vsip_tview_i *vsip_tputoffset_i (
     vsip_tview_i*,
     vsip_offset);

vsip_tview_si *vsip_tputoffset_si (
     vsip_tview_si*,
     vsip_offset);

vsip_tview_uc *vsip_tputoffset_uc (
     vsip_tview_uc*,
     vsip_offset);


vsip_ctview_f *vsip_ctputoffset_f (
     vsip_ctview_f*,
     vsip_offset);

vsip_ctview_d *vsip_ctputoffset_d (
     vsip_ctview_d*,
     vsip_offset);

/* */

vsip_tview_f *vsip_tputxlength_f(
     vsip_tview_f*,
     vsip_length);

vsip_tview_d *vsip_tputxlength_d(
     vsip_tview_d*,
     vsip_length);

vsip_tview_i *vsip_tputxlength_i(
     vsip_tview_i*,
     vsip_length);

vsip_tview_si *vsip_tputxlength_si(
     vsip_tview_si*,
     vsip_length);

vsip_tview_uc *vsip_tputxlength_uc(
     vsip_tview_uc*,
     vsip_length);

vsip_ctview_f *vsip_ctputxlength_f(
     vsip_ctview_f*,
     vsip_length);

vsip_ctview_d *vsip_ctputxlength_d(
     vsip_ctview_d*,
     vsip_length);

/* */

vsip_tview_f *vsip_tputylength_f(
     vsip_tview_f*,
     vsip_length);

vsip_tview_d *vsip_tputylength_d(
     vsip_tview_d*,
     vsip_length);

vsip_tview_i *vsip_tputylength_i(
     vsip_tview_i*,
     vsip_length);

vsip_tview_si *vsip_tputylength_si(
     vsip_tview_si*,
     vsip_length);

vsip_tview_uc *vsip_tputylength_uc(
     vsip_tview_uc*,
     vsip_length);

vsip_ctview_f *vsip_ctputylength_f(
     vsip_ctview_f*,
     vsip_length);

vsip_ctview_d *vsip_ctputylength_d(
     vsip_ctview_d*,
     vsip_length);

/* */

vsip_tview_f *vsip_tputzlength_f(
     vsip_tview_f*,
     vsip_length);

vsip_tview_d *vsip_tputzlength_d(
     vsip_tview_d*,
     vsip_length);

vsip_tview_i *vsip_tputzlength_i(
     vsip_tview_i*,
     vsip_length);

vsip_tview_si *vsip_tputzlength_si(
     vsip_tview_si*,
     vsip_length);

vsip_tview_uc *vsip_tputzlength_uc(
     vsip_tview_uc*,
     vsip_length);

vsip_ctview_f *vsip_ctputzlength_f(
     vsip_ctview_f*,
     vsip_length);

vsip_ctview_d *vsip_ctputzlength_d(
     vsip_ctview_d*,
     vsip_length);

/* */

vsip_tview_f *vsip_tputxstride_f(
     vsip_tview_f*,
     vsip_stride);

vsip_tview_d *vsip_tputxstride_d(
     vsip_tview_d*,
     vsip_stride);

vsip_tview_i *vsip_tputxstride_i(
     vsip_tview_i*,
     vsip_stride);

vsip_tview_si *vsip_tputxstride_si(
     vsip_tview_si*,
     vsip_stride);

vsip_tview_uc *vsip_tputxstride_uc(
     vsip_tview_uc*,
     vsip_stride);

vsip_ctview_f *vsip_ctputxstride_f(
     vsip_ctview_f*,
     vsip_stride);

vsip_ctview_d *vsip_ctputxstride_d(
     vsip_ctview_d*,
     vsip_stride);

/* */

vsip_tview_f *vsip_tputystride_f(
     vsip_tview_f*,
     vsip_stride);

vsip_tview_d *vsip_tputystride_d(
     vsip_tview_d*,
     vsip_stride);

vsip_tview_i *vsip_tputystride_i(
     vsip_tview_i*,
     vsip_stride);

vsip_tview_si *vsip_tputystride_si(
     vsip_tview_si*,
     vsip_stride);

vsip_tview_uc *vsip_tputystride_uc(
     vsip_tview_uc*,
     vsip_stride);

vsip_ctview_f *vsip_ctputystride_f(
     vsip_ctview_f*,
     vsip_stride);

vsip_ctview_d *vsip_ctputystride_d(
     vsip_ctview_d*,
     vsip_stride);

/* */

vsip_tview_f *vsip_tputzstride_f(
     vsip_tview_f*,
     vsip_stride);

vsip_tview_d *vsip_tputzstride_d(
     vsip_tview_d*,
     vsip_stride);

vsip_tview_i *vsip_tputzstride_i(
     vsip_tview_i*,
     vsip_stride);

vsip_tview_si *vsip_tputzstride_si(
     vsip_tview_si*,
     vsip_stride);

vsip_tview_uc *vsip_tputzstride_uc(
     vsip_tview_uc*,
     vsip_stride);

vsip_ctview_f *vsip_ctputzstride_f(
     vsip_ctview_f*,
     vsip_stride);

vsip_ctview_d *vsip_ctputzstride_d(
     vsip_ctview_d*,
     vsip_stride);

/* */

vsip_tview_f *vsip_tsubview_f(
     const vsip_tview_f*,
     vsip_index,
     vsip_index,
     vsip_index,
     vsip_length,
     vsip_length,
     vsip_length);

vsip_tview_d *vsip_tsubview_d(
     const vsip_tview_d*,
     vsip_index,
     vsip_index,
     vsip_index,
     vsip_length,
     vsip_length,
     vsip_length);

vsip_tview_i *vsip_tsubview_i(
     const vsip_tview_i*,
     vsip_index,
     vsip_index,
     vsip_index,
     vsip_length,
     vsip_length,
     vsip_length);

vsip_tview_si *vsip_tsubview_si(
     const vsip_tview_si*,
     vsip_index,
     vsip_index,
     vsip_index,
     vsip_length,
     vsip_length,
     vsip_length);

vsip_tview_uc *vsip_tsubview_uc(
     const vsip_tview_uc*,
     vsip_index,
     vsip_index,
     vsip_index,
     vsip_length,
     vsip_length,
     vsip_length);

vsip_ctview_f *vsip_ctsubview_f(
     const vsip_ctview_f*,
     vsip_index,
     vsip_index,
     vsip_index,
     vsip_length,
     vsip_length,
     vsip_length);

vsip_ctview_d *vsip_ctsubview_d(
     const vsip_ctview_d*,
     vsip_index,
     vsip_index,
     vsip_index,
     vsip_length,
     vsip_length,
     vsip_length);

/* */

vsip_tview_f *vsip_ttransview_f(
     const vsip_tview_f*,
     vsip_ttrans);

vsip_tview_d *vsip_ttransview_d(
     const vsip_tview_d*,
     vsip_ttrans);

vsip_tview_i *vsip_ttransview_i(
     const vsip_tview_i*,
     vsip_ttrans);

vsip_tview_si *vsip_ttransview_si(
     const vsip_tview_si*,
     vsip_ttrans);

vsip_tview_uc *vsip_ttransview_uc(
     const vsip_tview_uc*,
     vsip_ttrans);

vsip_ctview_f *vsip_cttransview_f(
     const vsip_ctview_f*,
     vsip_ttrans);

vsip_ctview_d *vsip_cttransview_d(
     const vsip_ctview_d*,
     vsip_ttrans);

/* */

vsip_vview_f *vsip_tvectview_f(
     const vsip_tview_f*,
     vsip_tvslice,
     vsip_index,
     vsip_index);

vsip_vview_d *vsip_tvectview_d(
     const vsip_tview_d*,
     vsip_tvslice,
     vsip_index,
     vsip_index);

vsip_vview_i *vsip_tvectview_i(
     const vsip_tview_i*,
     vsip_tvslice,
     vsip_index,
     vsip_index);

vsip_vview_si *vsip_tvectview_si(
     const vsip_tview_si*,
     vsip_tvslice,
     vsip_index,
     vsip_index);

vsip_vview_uc *vsip_tvectview_uc(
     const vsip_tview_uc*,
     vsip_tvslice,
     vsip_index,
     vsip_index);

vsip_cvview_f *vsip_ctvectview_f(
     const vsip_ctview_f*,
     vsip_tvslice,
     vsip_index,
     vsip_index);

vsip_cvview_d *vsip_ctvectview_d(
     const vsip_ctview_d*,
     vsip_tvslice,
     vsip_index,
     vsip_index);

/* */

vsip_tview_f *vsip_trealview_f(
     const vsip_ctview_f*);

vsip_tview_d *vsip_trealview_d(
     const vsip_ctview_d*);

vsip_tview_f *vsip_timagview_f(
     const vsip_ctview_f*);

vsip_tview_d *vsip_timagview_d(
     const vsip_ctview_d*);
                     /* */
                     
void vsip_vcopyto_user_f(
     const vsip_vview_f*,
     vsip_scalar_f* const);
                     
void vsip_cvcopyto_user_f(
     const vsip_cvview_f*,
     vsip_scalar_f* const,
     vsip_scalar_f* const);
                     
void vsip_mcopyto_user_f(
     const vsip_mview_f*,
     vsip_major,
     vsip_scalar_f* const);
                     
void vsip_cmcopyto_user_f(
     const vsip_cmview_f*,
     vsip_major,
     vsip_scalar_f* const,
     vsip_scalar_f* const);
                     
void vsip_vcopyto_user_d(
   const vsip_vview_d*,
   vsip_scalar_d* const);
                     
void vsip_cvcopyto_user_d(
    const vsip_cvview_d*,
    vsip_scalar_d* const,
    vsip_scalar_d* const);
                     
void vsip_mcopyto_user_d(
    const vsip_mview_d*,
    vsip_major,
    vsip_scalar_d* const);
                     
void vsip_cmcopyto_user_d(
    const vsip_cmview_d*,
    vsip_major,
    vsip_scalar_d* const,
    vsip_scalar_d* const);
                     
void vsip_vcopyfrom_user_f(
    vsip_scalar_f* const,
    const vsip_vview_f*);
                     
void vsip_cvcopyfrom_user_f(                             
   vsip_scalar_f* const,
   vsip_scalar_f* const,
   const vsip_cvview_f*);
                     
void vsip_mcopyfrom_user_f(
    vsip_scalar_f* const,
    vsip_major,
    const vsip_mview_f*);
                     
void vsip_cmcopyfrom_user_f(
    vsip_scalar_f* const, 
    vsip_scalar_f* const,
    vsip_major,
    const vsip_cmview_f*);
                     
void vsip_vcopyfrom_user_d(
    vsip_scalar_d* const,
    const vsip_vview_d*);
                     
void vsip_cvcopyfrom_user_d(                             
   vsip_scalar_d* const,
   vsip_scalar_d* const,
   const vsip_cvview_d*);
                     
void vsip_mcopyfrom_user_d(
    vsip_scalar_d* const,
    vsip_major,
    const vsip_mview_d*);
                     
void vsip_cmcopyfrom_user_d(
    vsip_scalar_d* const, 
    vsip_scalar_d* const,
    vsip_major,
    const vsip_cmview_d*);

#endif /*_vsip_header_h*/
