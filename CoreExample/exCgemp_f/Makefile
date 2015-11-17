## CREATED RJudd 
## SPAWARSYSCEN D881 
## $Id: Makefile,v 2.0 2003/02/22 15:42:44 judd Exp $

## Top Level of library distribution
## RDIR=$(HOME)/local
RDIR=../..
## C compiler
CC=cc
INCLUDEDIR=-I$(RDIR)/include
LIBDIR=-L$(RDIR)/lib
LIBS=-lVU -lvsip -lm
OPTIONS=-O2

OBJECTS = cgempEx cgempNTEx cgempTNEx cgempTTEx cgempNHEx cgempHNEx cgempHHEx cgempCHEx cgempHCEx cgempCCEx

all:$(OBJECTS)

cgempEx:cgempEx.c
	$(CC) -o cgempEx cgempEx.c $(OPTIONS) $(INCLUDEDIR) $(LIBDIR) $(LIBS)

cgempNTEx:cgempNTEx.c
	$(CC) -o cgempNTEx cgempNTEx.c $(OPTIONS) $(INCLUDEDIR) $(LIBDIR) $(LIBS)

cgempTNEx:cgempTNEx.c
	$(CC) -o cgempTNEx cgempTNEx.c $(OPTIONS) $(INCLUDEDIR) $(LIBDIR) $(LIBS)

cgempTTEx:cgempTTEx.c
	$(CC) -o cgempTTEx cgempTTEx.c $(OPTIONS) $(INCLUDEDIR) $(LIBDIR) $(LIBS)

cgempNHEx:cgempNHEx.c
	$(CC) -o cgempNHEx cgempNHEx.c $(OPTIONS) $(INCLUDEDIR) $(LIBDIR) $(LIBS)

cgempHNEx:cgempHNEx.c
	$(CC) -o cgempHNEx cgempHNEx.c $(OPTIONS) $(INCLUDEDIR) $(LIBDIR) $(LIBS)

cgempHHEx:cgempHHEx.c
	$(CC) -o cgempHHEx cgempHHEx.c $(OPTIONS) $(INCLUDEDIR) $(LIBDIR) $(LIBS)

cgempCHEx:cgempCHEx.c
	$(CC) -o cgempCHEx cgempCHEx.c $(OPTIONS) $(INCLUDEDIR) $(LIBDIR) $(LIBS)

cgempHCEx:cgempHCEx.c
	$(CC) -o cgempHCEx cgempHCEx.c $(OPTIONS) $(INCLUDEDIR) $(LIBDIR) $(LIBS)

cgempCCEx:cgempCCEx.c
	$(CC) -o cgempCCEx cgempCCEx.c $(OPTIONS) $(INCLUDEDIR) $(LIBDIR) $(LIBS)

clean:
	rm -f \
cgempEx cgempNTEx cgempTNEx cgempTTEx cgempNHEx cgempHNEx cgempHHEx cgempCHEx cgempHCEx cgempCCEx \
cgempEx.exe cgempNTEx.exe cgempTNEx.exe cgempTTEx.exe cgempNHEx.exe cgempHNEx.exe cgempHHEx.exe \
cgempCHEx.exe cgempHCEx.exe cgempCCEx.exe
