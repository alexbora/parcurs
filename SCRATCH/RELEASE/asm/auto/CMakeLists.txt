######################################################################
# @author      : alex (alex@mac.local)
# @file        : CMakeLists
# @created     : Miercuri Noi 16, 2022 19:21:17 EET
######################################################################

cmake_minimum_required(VERSION 2.8)
project( C)


add_executable(main main.c)
add_library(say SHARED lib.c)
target_link_libraries(main say)


