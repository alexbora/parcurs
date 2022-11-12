######################################################################
# @author      : alex (alex@mac.local)
# @file        : CMakeLists
# @created     : Miercuri Noi 09, 2022 18:15:10 EET
######################################################################

cmake_minimum_required(VERSION 3.0)
# SET (CMAKE_C_COMPILER_WORKS 1)
project(myproject LANGUAGES C)
# set(CMAKE_C_COMPILER /usr/local/Cellar/gcc/12.2.0/bin/gcc-12)
# set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
# set(CMAKE_C_COMPILER:FILEPATH gcc-12)
# set(CMAKE_CXX_COMPILER:FILEPATH g++-12)
# SET (CMAKE_CXX_COMPILER_WORKS 1)

project(C_Only C)
enable_language(C)
# add_executable(main test2.c)
set(CMAKE_C_COMPILER:FILEPATH=/usr/local/bin/gcc-12)

# set(CMAKE_C_COMPILER_WORKS 1)
# set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# set(CMAKE_C_COMPILER gcc-12)

find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK3 REQUIRED gtk+-3.0)
include_directories (${GTK3_INCLUDE_DIRS})
link_directories (${GTK3_LIBRARY_DIRS})
add_definitions (${GTK3_CFLAGS_OTHER})

 enable_language(C)
# add_library(test2 test2.c)
# add_library(test2 SHARED test2.c)
# add_library(test_static test2.c)
# target_link_libraries(main test2)
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

set(namefile "gtk")
# add_executable(gtk gtk.c)
add_executable( ${namefile} ${namefile}.c ) 
target_link_libraries (gtk ${GTK3_LIBRARIES})

