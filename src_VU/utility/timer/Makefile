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
SOURCES= VU_ansi_c_clock.c
OBJECTS= VU_ansi_c_clock.o

$(ARCHIVE):$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
