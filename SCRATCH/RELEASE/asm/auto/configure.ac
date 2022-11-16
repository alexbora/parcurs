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
LIBADD = -lssl -lcrypto -lxlsxwriter
# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AM_INIT_AUTOMAKE
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

