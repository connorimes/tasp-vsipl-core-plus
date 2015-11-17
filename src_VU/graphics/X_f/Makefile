# Makefile Created By RJudd
# SPAWARSYSCEN D881
#
## Directory where X distribution is
RXDIR = /usr/X11R6
## Directory where VSIPL is
RDIR = ../../..
CC=cc
INCLUDE=-I$(RDIR)/include -I$(RXDIR)/include
DEFINES=
OPTIONS=
AR=ar
AR_OPTIONS=rcvs
ARLIB=libVUX.a
ARCHIVE=$(RDIR)/lib/$(ARLIB)
COMPILE=$(CC) $(DEFINES) $(OPTIONS)
SOURCES= VUX_vxyplot_f.c \
VUX_vxyplotopen_f.c \
VUX_vxyplotclose_f.c \
VUX_vxyplotsize_f.c \
VUX_vxyplottitle_f.c \
VUX_vxyplotxtitle_f.c \
VUX_vxyplotytitle_f.c \
VUX_vxyplotaxis_f.c \
VUX_vxyplotinit_f.c \
VUX_mgram_f.c \
VUX_mgramupdate_f.c \
VUX_mgramopen_f.c \
VUX_mgramaxis_f.c \
VUX_mgramclose_f.c \
VUX_mgramtitle_f.c \
VUX_mgramxtitle_f.c \
VUX_mgramytitle_f.c \
VUX_mgram_colorarray_f.c \
VUX_mgram_gsarray_f.c \
VUX_mgraminit_f.c

OBJECTS= VUX_vxyplot_f.o \
VUX_vxyplotopen_f.o \
VUX_vxyplotclose_f.o \
VUX_vxyplotsize_f.o \
VUX_vxyplottitle_f.o \
VUX_vxyplotxtitle_f.o \
VUX_vxyplotytitle_f.o \
VUX_vxyplotaxis_f.o \
VUX_vxyplotinit_f.o \
VUX_mgram_f.o \
VUX_mgramupdate_f.o \
VUX_mgramopen_f.o \
VUX_mgramaxis_f.o \
VUX_mgramclose_f.o \
VUX_mgramtitle_f.o \
VUX_mgramxtitle_f.o \
VUX_mgramytitle_f.o \
VUX_mgram_colorarray_f.o \
VUX_mgram_gsarray_f.o \
VUX_mgraminit_f.o

$(ARCHIVE):$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)                                          
