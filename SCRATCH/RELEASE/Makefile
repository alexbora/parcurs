all: mail.c date.c excel.c main.c main.h days.S isleap.S  check_alignment.s
	@gcc-12 -DLOG_VERBOSE -DUSE_ASM mail.c date.c excel.c main.c days.S isleap.S check_alignment.s -DSkipmain -o final_program -std=c11 -O3 -w -fno-plt -m64 -mpreferred-stack-boundary=4 -Wformat=2 -Wshadow -Wdouble-promotion -fno-common -ffunction-sections -fdata-sections -fomit-frame-pointer  -mtune=native -fno-PIC -fno-PIE  -freg-struct-return -fverbose-asm -falign-functions=16 -malign-double  -mno-red-zone `pkg-config --cflags --libs openssl` `pkg-config --cflags --libs xlsxwriter` `pkg-config --cflags tb64` `pkg-config --libs tb64` -ldl -pthread && printf '%s\n' "Compiled successfully!"
	@# -v to see output of gcc


clean:
	@printf '%s\n' "Cleaning up ..."
	@# @echo Done cleaning.
	@rm -rf *.dSYM row string_ex2 sterge1 sterge2 sterge7 sterge8 find sterge8 sterge9 sterge10 sterge11 sterge13 net2 net3 sock2 test1 test2 test2.s date_ex cachegrind.out* test3 funcs3 path libdate.a date_ex.o test4 date2 date2.o excel2.o *.xlsx test5 test6 test7 callgrind.out.* perf.data log_file main mail_ssl test8 test9 final_program mail *.gcda

# /opt/local/lib*/llvm-14/bin/clang 
