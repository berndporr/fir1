AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = -I m4
lib_LTLIBRARIES = libfir.la
libfir_la_LDFLAGS = -version-info $(FIR_SO_VERSION)
fir_includedir = $(includedir)
nobase_fir_include_HEADERS = Fir1.h Fir1fixed.h

fir_libincludedir = $(libdir)/include
nodist_fir_libinclude_HEADERS = firconfig.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = fir.pc
dist_noinst_SCRIPTS = autogen.sh

libfir_la_SOURCES = Fir1.h Fir1fixed.h \
                    fir/Fir1.cpp fir/Fir1fixed.cpp
