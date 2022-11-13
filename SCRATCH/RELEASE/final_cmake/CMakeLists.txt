######################################################################
# @author      : alex (alex@mac.local)
# @file        : CMakeLists
# @created     : Duminică Noi 13, 2022 07:31:07 EET
######################################################################

cmake_minimum_required(VERSION 3.8)
project( C)

set (SOURCE_DIR /Users/alex/dev/parcurs/SCRATCH/RELEASE)
set(SOURCES ${SOURCE_DIR}/date.c)
# file(GLOB SOURCES ${SOURCE_DIR} "*.c")
add_executable(main ${SOURCES})



# all: mail.c date.c excel.c main.c main.h days.S isleap.S  check_alignment.s
# 	@gcc-12 -L/Users/alex/dev/Turbo-Base64 -ltb64 -DMEMORY -DVECTORIZE -DLOG_VERBOSE -DUSE_ASM mail.c date.c excel.c main.c days.S isleap.S check_alignment.s -DSkipmain -o final_program -std=c11 -O3 -w -fno-plt -m64 -mpreferred-stack-boundary=4 -Wformat=2 -Wshadow -Wdouble-promotion -fno-common -ffunction-sections -fdata-sections -fomit-frame-pointer  -mtune=native -fno-PIC -fno-PIE  -freg-struct-return -fverbose-asm -falign-functions=16 -malign-double  -mno-red-zone `pkg-config --cflags --libs openssl` `pkg-config --cflags --libs xlsxwriter` `pkg-config --libs gtk+-3.0` `pkg-config --cflags gtk+-3.0` -ldl -pthread && printf '%s\n' "Compiled successfully!"


