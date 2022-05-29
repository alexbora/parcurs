# all:
	 # gcc -O3 -std=c11 date2.c excel2.c -o date2 `pkg-config --cflags --libs xlsxwriter`

HOST=$(shell hostname)
TARGET:=final_program
CC= #:=gcc-10.1
CFLAGS:=-O3 -ggdb3 -lgcc #-v#-static
CFLAGS+=-std=c11 -fstrict-aliasing -fopenmp -m64 -mavx -ffunction-sections -fsanitize=address -fno-omit-frame-pointer -static-libstdc++ -static-libgcc #/home/linuxbrew/.linuxbrew/Cellar/gcc@12/12.1.0/lib/gcc/12/gcc/x86_64-pc-linux-gnu/12/libgcc.a
CFLAGS+=-D_POSIX_C_SOURCE=200112L
LDLIBS:= `pkg-config --cflags --libs xlsxwriter` 
LDLIBS+= `pkg-config --cflags --libs openssl` 
LDFLAGS:=-lgcc -lxlsxwriter -lasan
# LDFLAGS+=-fno-strict-aliasing
# LDFLAGS+=-mavx
# LDFLAGS+=-ffunction-sections
# LDFLAGS+=-fno-rtti
# LDFLAGS+=-fno-unwind-tables
# LDFLAGS+=-Winline


.DELETE_ON_ERROR:
$(TARGET): date2.o excel2.o 
	 $(CC) $(CFLAGS) $(LDLIBS) $(LDFLAGS) date2.o excel2.o -o $(TARGET) 
	 @# gcc-11 $(CFLAGS) $(LDLIBS) date2.o excel2.o -o date2 `pkg-config --cflags --libs xlsxwriter` 

# date2.o: date2.c 
# 	gcc-11 -O3 -c date2.c -o date2.o 
# excel2.o: excel2.c 
# 	gcc-11 -O3 -c excel2.c -o excel2.o `pkg-config --cflags --libs xlsxwriter`

ifeq ($(HOST),  mac.local)
CC:=/usr/local/Cellar/gcc@12/12*/bin/gcc-12
endif
ifeq ($(HOST), T460)
CC:=gcc-12
endif
ifeq ($(HOST),  T400)
CC:=gcc-10.1
endif


.PHONY: clean
clean:
	rm -rf *.dSYM row string_ex2 sterge1 sterge2 sterge7 sterge8 find sterge8 sterge9 sterge10 sterge11 sterge13 net2 net3 sock2 test1 test2 test2.s date_ex cachegrind.out* test3 funcs3 path libdate.a date_ex.o test4 date2 date2.o excel2.o $(TARGET) *.xlsx test5 test6 test7 callgrind.out.* perf.data
