/* Created by RJudd October 4, 1999*/
/* SPAWARSYSCEN D859 */
#ifndef _VI_ludattributes_f_h  
#define _VI_ludattributes_f_h 1

struct VI_ludattributes_f{
       vsip_mview_f* LU;
       vsip_mview_f  LLU;
       vsip_index *P;
       vsip_length   N;
       };

#endif /*_VI_ludattributes_f_h */
