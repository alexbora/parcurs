bin_PROGRAMS=main 
main_SOURCES=main.c 
lib_LTLIBRARIES=


TESTS=$(check_PROGRAMS) 
check_PROGRAMS=main


noinst_LIBRARIES = libcpio.a
libcpio_a_SOURCES =lib.c 
libcpio_a_LDFLAGS=-static

main_LDADD = libcpio.a
