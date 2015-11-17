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
SOURCES= VU_mreadf_f.c \
VU_cmreadf_f.c \
VU_vreadf_f.c \
VU_cvreadf_f.c \
VU_mreadf_d.c \
VU_cmreadf_d.c \
VU_vreadf_d.c \
VU_cvreadf_d.c 
OBJECTS= VU_mreadf_f.o \
VU_cmreadf_f.o \
VU_vreadf_f.o \
VU_cvreadf_f.o \
VU_mreadf_d.o \
VU_cmreadf_d.o \
VU_vreadf_d.o \
VU_cvreadf_d.o 

$(ARCHIVE):$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
