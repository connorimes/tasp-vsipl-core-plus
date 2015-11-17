struct VI_ludattributes_f;
typedef struct VI_ludattributes_f VI_lu_f;

int (VI_lud_f)(
       VI_lu_f*,
       const vsip_mview_f*);

VI_lu_f *(VI_lud_create_f)(
       vsip_length);

int (VI_lusol_f)(
       const VI_lu_f*,
       const vsip_mview_f*);

int  (VI_lud_destroy_f)(
      VI_lu_f*);

