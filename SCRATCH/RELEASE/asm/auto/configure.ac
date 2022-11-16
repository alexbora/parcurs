#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([main], [1.0], [])
AC_CONFIG_SRCDIR([main.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.

AC_PROG_CC
AM_CFLAGS=-g -Wall -O3
# AC_CHECK_LIB([ssl], [SSL_library_init], [], [AC_MSG_FAILURE([could not find ssl])])
AC_CHECK_LIB([ssl], [SSL_library_init])
AC_CHECK_LIB([xlsxwriter], [])
AC_SEARCH_LIBS([dlopen], [dl dld], [], [
  AC_MSG_ERROR([unable to find the dlopen() function])
])
LIBADD = -lssl -lcrypto -lxlsxwriter
AC_CHECK_HEADERS([stdint.h inttypes.h sys/types.h],
        [mypj_found_int_headers=yes; break;])
# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_PROG_LIBTOOL
# Checks for library functions.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AM_PROG_AR
AM_INIT_AUTOMAKE
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

