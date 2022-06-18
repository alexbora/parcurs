all: mail.c date.c excel.c main.c main.h
	gcc-11 mail.c date.c excel.c main.c -DSkipmain -o final_program -w -std=c11 -O3  `pkg-config --cflags --libs openssl` -lxlsxwriter -ldl -pthread -DLOG_VERBOSE

clean:
	@echo Done.
	@rm -rf *.dSYM row string_ex2 sterge1 sterge2 sterge7 sterge8 find sterge8 sterge9 sterge10 sterge11 sterge13 net2 net3 sock2 test1 test2 test2.s date_ex cachegrind.out* test3 funcs3 path libdate.a date_ex.o test4 date2 date2.o excel2.o *.xlsx test5 test6 test7 callgrind.out.* perf.data log_file main mail_ssl test8 test9 final_program mail *.gcda

# /opt/local/lib*/llvm-14/bin/clang 
