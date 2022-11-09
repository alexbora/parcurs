######################################################################
# @author      : alex (alex@mac.local)
# @file        : CMakeLists
# @created     : Miercuri Noi 09, 2022 18:15:10 EET
######################################################################

cmake_minimum_required(VERSION 2.8)
project(C)
add_executable(main test2.c)
# add_library(test2 test2.c)
add_library(test2 SHARED test2.c)
target_link_libraries(main test2)

