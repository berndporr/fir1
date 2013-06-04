AC_INIT([LibFIR], [1.0], [mail@berndporr.me.uk], [fir],
        [http://www.berndporr.me.uk])
AC_PREREQ([2.59])
AM_INIT_AUTOMAKE([1.10 -Wall no-define])

AC_CONFIG_HEADERS([config.h firconfig.h])
AC_CONFIG_MACRO_DIR([m4])
AC_PROG_CXX
LT_INIT([disable-static])

AC_SUBST([FIR_SO_VERSION], [1:0:0])

AC_CONFIG_FILES([Makefile
                 fir.pc:fir.pc.in])
AC_OUTPUT
