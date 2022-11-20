#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AC_CONFIG_SRCDIR([../main.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC([gcc-12])
AM_PROG_AS
AC_PROG_CXX 
AC_PROG_F77
# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h netdb.h netinet/in.h stdint.h sys/socket.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_INCLUDES_DEFAULT
AC_C_INLINE
AC_C_VOLATILE
AC_TYPE_INT32_T
AC_C_RESTRICT
AC_TYPE_SIZE_T
AC_TYPE_UINT32_T 
AC_C_FLEXIBLE_ARRAY_MEMBER 
AC_C_VARARRAYS
AC_CHECK_SIZEOF([int *]) 
AC_CHECK_SIZEOF([int]) 
AC_CHECK_SIZEOF([char]) 
AC_CHECK_SIZEOF([UINT_MAX]) 
AC_OPENMP
AC_CHECK_TOOL([RANLIB], [ranlib], [:]) 
AC_CHECK_FILE("logo.png")
AC_CHECK_FILE("pass_2")
AC_CHECK_LIB(xlsxwriter)
AC_CHECK_LIB([ssl]) 
# AC_CHECK_LIB(ssl, SSL_library_init, [], [AC_MSG_ERROR([library 'ssl' is required for OpenSSL])])
# ACCEPT_SSL_LIB="no"
# AC_CHECK_LIB(ssl, OPENSSL_init_ssl, [ACCEPT_SSL_LIB="yes"])
# AC_CHECK_LIB(ssl, SSL_library_init, [ACCEPT_SSL_LIB="yes"])
# AS_IF([test "x$ACCEPT_SSL_LIB" = xno], [AC_MSG_ERROR([library 'ssl' is required for OpenSSL])])
AC_CHECK_LIB(crypto)
AC_HEADER_ASSERT 
AC_HEADER_STAT 
AC_HEADER_STDBOOL 
AC_HEADER_SYS_WAIT 
AC_HEADER_TIME
AC_PROG_CC_C_O 
AC_PROG_LEX 
AC_FUNC_MMAP 
AC_FUNC_MEMCMP 
AC_FUNC_STRCOLL 
AC_FUNC_STRFTIME 
AC_FUNC_VPRINTF 
AC_MEMORY_H 
AC_UNISTD_H 
AC_STRUCT_ST_BLKSIZE 
AC_STRUCT_ST_BLOCKS 
AC_STRUCT_TM 
AC_STRUCT_TIMEZONE 
AC_TYPE_OFF_T 
AC_TYPE_PID_T 
AC_TYPE_SIGNAL 
AC_C_LONG_DOUBLE 
AC_LONG_64_BITS 
AC_SYS_RESTARTABLE_SYSCALLS 


DIALECT="-std=c++14"
echo 'int main() {return 0;}' > ./log.cpp && $CXX -std=c++14 ./log.cpp || $DIALECT="no"

if test $DILAECT = no; then
    AC_MSG_ERROR([c++ compiler does not support c++14])
else
    echo $DILAECT
fi

AC_LANG(C) 


# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_MKTIME
AC_FUNC_MMAP
AC_CHECK_FUNCS([ftruncate getcwd gethostbyname getpagesize memset munmap select setenv socket strstr])

AC_PREFIX_DEFAULT(bin)
AC_CONFIG_FILES([Makefile])
AM_INIT_AUTOMAKE(foreign subdir-objects)
AC_OUTPUT
