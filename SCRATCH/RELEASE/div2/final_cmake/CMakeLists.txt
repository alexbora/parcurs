######################################################################
# @author      : alex (alex@mac.local)
# @file        : CMakeLists
# @created     : Duminică Noi 13, 2022 07:31:07 EET
######################################################################

cmake_minimum_required(VERSION 3.8)
project(final)
enable_language(C ASM)
set (MAJOR 1)
set (MINOR 0)

find_package (PkgConfig REQUIRED)
pkg_check_modules (OpenSSL REQUIRED openssl)
pkg_check_modules (libxlsxwriter REQUIRED xlsxwriter)

# set(SOURCE_FILES /..)
set (SOURCE_DIR /Users/alex/dev/parcurs/SCRATCH/RELEASE)
set(SOURCES ${SOURCE_DIR}/date.c)
set(SOURCES ${SOURCE_DIR}/mail.c)
set(SOURCES ${SOURCE_DIR}/excel.c)
set(SOURCES ${SOURCE_DIR}/main.c)



set(SOURCES ${SOURCE_DIR}/days.S)
set_property(SOURCE days.S APPEND PROPERTY COMPILE_OPTIONS "-e _start -macosx_version_min 10.13 -lSystem") 

set(SOURCES ${SOURCE_DIR}/isleap.S)
set_property(SOURCE is_leap.S APPEND PROPERTY COMPILE_OPTIONS "-e _start -macosx_version_min 10.13 -lSystem") 

set(SOURCES ${SOURCE_DIR}/check_alignment.s)
set_property(SOURCE check_alignment.s APPEND PROPERTY COMPILE_OPTIONS "-e _start -macosx_version_min 10.13 -lSystem") 

# file(GLOB SOURCES ${SOURCE_DIR} "*.c")
include_directories(SOURCES, ${SOURCE_DIR})

# set_target_properties(main PROPERTIES LINKER_LANGUAGE C)

SET(CMAKE_C_FLAGS  "-L/Users/alex/dev/Turbo-Base64 -ltb64 -DMEMORY -DVECTORIZE -DLOG_VERBOSE -DUSE_ASM mail.c date.c excel.c main.c days.S isleap.S check_alignment.s -DSkipmain -fno-plt -m64 -mpreferred-stack-boundary=4 -Wformat=2 -Wshadow -Wdouble-promotion -fno-common -ffunction-sections -fdata-sections -fomit-frame-pointer -mtune=native -fno-PIC -fno-PIE -freg-struct-return -fverbose-asm -falign-functions=16 -malign-double  -mno-red-zone `pkg-config --cflags --libs openssl` `pkg-config --cflags --libs xlsxwriter` `pkg-config --libs gtk+-3.0` `pkg-config --cflags gtk+-3.0` -ldl -pthread")

set(CMAKE_C_FLAGS_DEBUG_INIT "-fsanitize=address,undefined -fsanitize-undefined-trap-on-error")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-fsanitize=address,undefined -static-libasan")

include_directories (${OpenSSL_INCLUDE_DIRS})
link_directories (${OpenSSL_LIBRARY_DIRS})
include_directories (${libxlsxwriter_INCLUDE_DIRS})
link_directories (${libxlsxwriter_LIBRARY_DIRS})
add_definitions (${libxlsxwriter_CFLAGS_OTHER})
add_definitions (${OpenSSL_CFLAGS_OTHER})

add_executable(final ${SOURCES})
target_link_libraries (final ${libxlsxwriter_LIBRARIES})
target_link_libraries (final ${OpenSSL_LIBRARIES})

# all: mail.c date.c excel.c main.c main.h days.S isleap.S  check_alignment.s
# 	@gcc-12 -L/Users/alex/dev/Turbo-Base64 -ltb64 -DMEMORY -DVECTORIZE -DLOG_VERBOSE -DUSE_ASM mail.c date.c excel.c main.c days.S isleap.S check_alignment.s -DSkipmain -o final_program -std=c11 -O3 -w -fno-plt -m64 -mpreferred-stack-boundary=4 -Wformat=2 -Wshadow -Wdouble-promotion -fno-common -ffunction-sections -fdata-sections -fomit-frame-pointer  -mtune=native -fno-PIC -fno-PIE  -freg-struct-return -fverbose-asm -falign-functions=16 -malign-double  -mno-red-zone `pkg-config --cflags --libs openssl` `pkg-config --cflags --libs xlsxwriter` `pkg-config --libs gtk+-3.0` `pkg-config --cflags gtk+-3.0` -ldl -pthread && printf '%s\n' "Compiled successfully!"


