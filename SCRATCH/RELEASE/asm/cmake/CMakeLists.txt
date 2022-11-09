######################################################################
# @author      : alex (alex@T400)
# @file        : CMakeLists
# @created     : vineri oct 28, 2022 13:02:02 EEST
######################################################################

cmake_minimum_required (VERSION 3.6)
project (HelloCMake)
add_executable (hello test2.c)
add_library (greeter test2.c)
target_link_libraries (hello greeter)
message("Hello world!")
