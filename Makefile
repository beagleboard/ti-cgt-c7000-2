DESTDIR ?= /

bindir = usr/bin
incdir = usr/share/ti/cgt-c7x/include
libdir = usr/share/ti/cgt-c7x/lib

all:

install:
	mkdir -p ${DESTDIR}${bindir}
	mkdir -p ${DESTDIR}${incdir}
	mkdir -p ${DESTDIR}${libdir}
	cp -ar ./bin/* ${DESTDIR}${bindir}
	cp -ar ./include/* ${DESTDIR}${incdir}
	cp -ar ./lib/* ${DESTDIR}${libdir}
