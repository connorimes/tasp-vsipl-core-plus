## Created RJudd
## SPAWARSYSCEN D881
## $Id: Makefile,v 2.2 2007/04/18 19:37:08 judd Exp $

## use gnu's make if possible
MAKE=make

## Any ansi C compiler here
CC=gcc

## To improve the usability of this implementation
## I have added some code options which are selected
## with the -D preprocessor directive. I expect that this
## list will increase as time goes by. By default no macros
## are defined and you get the default library. You can not
## willey-nilley chose optional macros. You must chose a set
## that makes sense. So I have defined them in a seprate readme
## file. Currently there are not that many choices but I can 
## imagine a fair number being implemented at some time in
## the future. The purpose is to help people trying to improve 
## performance or incorporate native librarys with VSIPL as a 
## middle-ware wrapper. If you are just starting out and trying VSIPL 
## just ignore this for now. OPTMACROS is for "implementors" not "users".
OPTMACROS=
##
## -DVSIP_ALWAYS_INTERLEAVED
## -DVSIP_DEFAULT_SPLIT
## -DVSIP_ALWAYS_SPLIT
## -DVSIP_ASSUME_COMPLEX_IS_INTERLEAVED
## -DVSIP_USE_FFTW_FOR_FFT_F
## -DVSIP_USE_FFTW_FOR_FFT_D
## -DVSIP_USE_FFT_FOR_FFTM_F
## -DVSIP_USE_FFT_FOR_FFTM_D
#
#
## Options appropriate for compiler
OPTIONS= -O3 -Wall -std=c89 -pedantic $(OPTMACROS)
##OPTIONS= -O3 -Wall -std=c89 -pedantic -ftree-vectorize $(OPTMACROS)
## OPTIONS= -Wall -ansi -pedantic -g $(OPTMACROS)
## OPTIONS= -Wall -ansi -pedantic $(OPTMACROS)

## Archiver
AR=ar
## Archiver options
AR_OPTIONS=rcvs

## What you want to call the VSIPL library
ARLIB=libvsip.a

## What you want to call the VSIPL User library
## The VSIPL user library is just VSIPL code. 
## It is not connected with the VSIPL Specification or Forum
## The subroutines are needed to run many of the examples.
ARLIB_VU=libVU.a

## The base directory for library and header installation
INSTALL_PREFIX ?= /usr/local

## The last-level directory where headers are installed
INSTALL_HEADER_DIR ?= tasp-vsipl-core-plus

all:
	(cd src; $(MAKE) MAKE='$(MAKE)' CC='$(CC)' OPTIONS='$(OPTIONS)' \
AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIB)';)
	(cd src_VU; $(MAKE) MAKE='$(MAKE)' CC='$(CC)' OPTIONS='$(OPTIONS)' \
AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIB_VU)';)

install: all
	install -m 0644 lib/${ARLIB} lib/${ARLIB_VU} ${INSTALL_PREFIX}/lib
	install -m 0755 -d ${INSTALL_PREFIX}/include/${INSTALL_HEADER_DIR}
	install -m 0644 include/vsip.h include/VU.h include/VUX.h ${INSTALL_PREFIX}/include/${INSTALL_HEADER_DIR}

clean:
	(cd src; $(MAKE) MAKE='$(MAKE)' clean;)
	(cd src_VU; $(MAKE) MAKE='$(MAKE)' clean;)
