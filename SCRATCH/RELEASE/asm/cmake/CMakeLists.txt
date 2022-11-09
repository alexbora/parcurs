######################################################################
# @author      : alex (alex@mac.local)
# @file        : CMakeLists
# @created     : Miercuri Noi 09, 2022 18:15:10 EET
######################################################################

cmake_minimum_required(VERSION 3.0)
# project(myproject LANGUAGES C)
# set(CMAKE_C_COMPILER /usr/local/Cellar/gcc/12.2.0/bin/gcc-12)
project(C)
add_executable(main test2.c)

enable_language(C)
# add_library(test2 test2.c)
add_library(test2 SHARED test2.c)
add_library(test_static test2.c)
target_link_libraries(main test2)

