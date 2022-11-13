######################################################################
# @author      : alex (alex@mac.local)
# @file        : CMakeLists
# @created     : Duminică Noi 13, 2022 09:33:30 EET
######################################################################

cmake_minimum_required (VERSION 3.0)
project (final_program)

set (PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/RELEASE/final_cmake2)
set (HELLO_SOURCES ${PROJECT_SOURCE_DIR}/main.c)

# These are the corresponding output paths
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/output)

add_executable (hello ${HELLO_SOURCES})
