AC_INIT([muparser-tests], [0.1])
AC_CONFIG_SRCDIR([Makefile.am])
AC_CONFIG_MACRO_DIR([m4])
AC_LANG(C++)

AM_INIT_AUTOMAKE([dist-bzip2 -Wno-portability])
AM_MAINTAINER_MODE

AC_PROG_CC
AC_PROG_CXX
AC_PROG_CXXCPP

AC_HEADER_STDC

AX_CXX_HAVE_STD
AX_CXX_NAMESPACE_STD
AX_CXX_HAVE_STL
AX_CXX_TEMPLATES

PKG_CHECK_MODULES(MUPARSER, muparser)
AC_SUBST(MUPARSER_CFLAGS)
AC_SUBST(MUPARSER_LIBS)

PKG_CHECK_MODULES(CPPUNIT, cppunit)
AC_SUBST(CPPUNIT_CFLAGS)
AC_SUBST(CPPUNIT_LIBS)

AC_PATH_PROG(VALGRIND, valgrind, no)
AM_CONDITIONAL(HAVE_VALGRIND, test "x$VALGRIND" != "xno")

have_valgrind_3_4_0=no
if test "x$VALGRIND" != "xno"; then
  valgrind_version=0
  valgrind_version="`$VALGRIND --version | head -n 1 |  sed 's/^[[^0-9]]*//' | sed 's/[[^0-9]]*$//' | cut -d' ' -f1`"
  AC_MSG_CHECKING([for valgrind version $valgrind_version >= 3.4.0])
  if perl -we "exit ((v$valgrind_version ge v3.4.0) ? 0 : 1)"; then
    have_valgrind_3_4_0=yes
    AC_MSG_RESULT([yes])
  else
    AC_MSG_RESULT([no])
  fi
fi
AM_CONDITIONAL(HAVE_VALGRIND_3_4_0, test "x$have_valgrind_3_4_0" = "xyes")

AC_PATH_PROG(GDB, gdb, no)
AM_CONDITIONAL(HAVE_GDB, test ! "x$GDB" = "xno")

CFLAGS="$CFLAGS -g -O0 -Wall"
CXXFLAGS="$CXXFLAGS -g -O0 -Wall"

AC_CONFIG_FILES([
  Makefile
  testsuite-1/Makefile
  testsuite-2/Makefile
  testsuite-3/Makefile
])

AC_OUTPUT
