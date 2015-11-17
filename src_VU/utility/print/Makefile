## RJudd October 11, 1998 
## SPAWARSYSCEN D881 

CC=cc
INCLUDE=-I../../../include
OPTIONS=-O2 -Wall -ansi -pedantic
AR=ar
AR_OPTIONS=rcvs
ARLIB=libVU_c.a
ARCHIVE=../../../lib/$(ARLIB)
COMPILE=$(CC) $(DEFINES) $(OPTIONS)
SOURCES= VU_mprintm_f.c \
VU_cmprintm_f.c \
VU_vprintm_f.c \
VU_vprintm_mi.c \
VU_vprintm_vi.c \
VU_cvprintm_f.c \
VU_mprintm_d.c \
VU_cmprintm_d.c \
VU_vprintm_d.c \
VU_cvprintm_d.c  \
VU_tprintm_f.c \
VU_ctprintm_f.c \
VU_tprintm_d.c \
VU_ctprintm_d.c \
VU_tprintm_i.c \
VU_mprintm_i.c \
VU_tprintm_si.c \
VU_mprintm_si.c \
VU_vprintm_i.c \
VU_vprintm_si.c \
VU_vprintm_bl.c 
OBJECTS= VU_mprintm_f.o \
VU_cmprintm_f.o \
VU_vprintm_f.o \
VU_vprintm_mi.o \
VU_vprintm_vi.o \
VU_cvprintm_f.o \
VU_mprintm_d.o \
VU_cmprintm_d.o \
VU_vprintm_d.o \
VU_cvprintm_d.o \
VU_tprintm_f.o  \
VU_ctprintm_f.o \
VU_tprintm_d.o \
VU_ctprintm_d.o \
VU_tprintm_i.o \
VU_mprintm_i.o \
VU_tprintm_si.o \
VU_mprintm_si.o \
VU_vprintm_i.o \
VU_vprintm_si.o \
VU_vprintm_bl.o 

$(ARCHIVE):$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
