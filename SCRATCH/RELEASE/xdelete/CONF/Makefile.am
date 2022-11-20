bin_PROGRAMS=final 
final_SOURCES=../main.c ../check_alignment.s ../date.c ../days.S ../excel.c ../isleap.S ../mail.c 

AM_CFLAGS=-DSkipmain -DLOG_VERBOSE -D_GNU_SOURCE -DLOG -DMEMORY -DLOG_VERBOSE -DUSE_ASM -DVECTORIZE -std=c11 -fno-plt -m64 -mpreferred-stack-boundary=4 -Wformat=2 -Wshadow -Wdouble-promotion -fno-common -ffunction-sections -fdata-sections -fomit-frame-pointer -mtune=native -fno-PIC -fno-PIE -freg-struct-return -fverbose-asm -falign-functions=16 -malign-double -mno-red-zone `pkg-config --cflags openssl` `pkg-config --cflags xlsxwriter` 

AM_LDFLAGS=-lxlsxwriter -lssl -lcrypto -L/Users/alex/dev/Turbo-Base64 -ltb64 -lpthread


CC=gcc-12


