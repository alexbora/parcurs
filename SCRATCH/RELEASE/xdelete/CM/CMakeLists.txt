######################################################################
# @author      : alex (alex@mac.local)
# @file        : CMakeLists
# @created     : Duminică Noi 20, 2022 13:38:42 EET
######################################################################

cmake_minimum_required(VERSION 3.0)
project(parcurs C)


get_filename_component(DIR_ONE_ABOVE ../ ABSOLUTE ) 
message(STATUS ${DIR_ONE_ABOVE})
set (SOURCES ${DIR_ONE_ABOVE})
set (EXECUTABLE_OUTPUT_PATH output)

set(CMAKE_C_FLAGS "-DSkipmain -D_GNU_SOURCE -DLOG -DMEMORY -DVECTORIZE -DLOG_VERBOSE -DUSE_ASM") 

add_executable(main ${SOURCES}/main.c ${SOURCES}/check_alignment.s ${SOURCES}/date.c ${SOURCES}/days.S ${SOURCES}/excel.c ${SOURCES}/isleap.S ${SOURCES}/libt64.a ${SOURCES}/mail.c ${SOURCES}/main.c ${SOURCES}/main.h)
target_link_libraries(main PRIVATE -lssl -lcrypto -lxlsxwriter -lptread -L/Users/alex/dev/Turbo-Base64 -ltb64)

