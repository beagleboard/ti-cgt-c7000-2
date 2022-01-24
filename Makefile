DESTDIR ?= /

bindir = bin
incdir = inc
libdir = lib

all:

install:
	mkdir -p ${DESTDIR}${bindir}
	mkdir -p ${DESTDIR}${incdir}
	mkdir -p ${DESTDIR}${libdir}
	cp -ar ./${bindir}/* ${DESTDIR}${bindir}
	cp -ar ./${incdir}/* ${DESTDIR}${incdir}
	cp -ar ./${libdir}/* ${DESTDIR}${libdir}
