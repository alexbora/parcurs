all: mail2.c date2.c excel2.c main.c main.h
	gcc-11 mail2.c date2.c excel2.c main.c -DSkipmain -o final_program -w -std=c11 -O3  `pkg-config --cflags --libs openssl` -lxlsxwriter -ldl -pthread -fstrict-aliasing -DPRINT_STDERR
	@echo	# gcc-11 date2.c excel2.c -o final_program -O3 -std=c11 -w -lxlsxwriter


log:
	gcc-11 mail2.c date2.c excel2.c main.c -DSkipmain -o final_program -w -std=c11 -O3  `pkg-config --cflags --libs openssl` -lxlsxwriter -ldl -pthread -fstrict-aliasing -DLOG
	@echo	# gcc-11 date2.c excel2.c -o final_program -O3 -std=c11 -w -lxlsxwriter


mail:
	gcc-11 mail2.c -o mail -O3 -std=c11 -w -lcrypto -lssl -ldl -pthread

y: x 
	./final_program
	gcc-11 mail2.c date2.c excel2.c main.c -DSkipmain -o final_program -w -std=c11 -Ofast  `pkg-config --cflags --libs openssl` -lxlsxwriter -ldl -pthread -fno-threadsafe-statics -fno-exceptions -funsigned-char -fmerge-all-constants -fdevirtualize-speculatively -ftree-parallelize-loops=2 -fdelete-null-pointer-checks -fprofile-arcs -falign-functions=32 -falign-loops=32 -falign-jumps=32 -flto -ffast-math -fno-math-errno -funsafe-math-optimizations -ffinite-math-only -fno-rounding-math -fno-signaling-nans -fcx-limited-range -fexcess-precision=fast -fsingle-precision-constant -fcx-fortran-rules -fprofile-use -fprofile-correction -fbranch-probabilities -fdata-sections -ffunction-sections -fdce -Wl,--gc-sections

x: date2.c excel2.c mail2.c main.c main.h
	gcc-11 mail2.c date2.c excel2.c main.c -DSkipmain -o final_program -w -std=c11 -Ofast  `pkg-config --cflags --libs openssl` -lxlsxwriter -ldl -pthread -fno-threadsafe-statics -fno-exceptions -funsigned-char -fmerge-all-constants -fdevirtualize-speculatively -ftree-parallelize-loops=2 -fdelete-null-pointer-checks -fprofile-arcs -falign-functions=32 -falign-loops=32 -falign-jumps=32 -flto -ffast-math -fno-math-errno -funsafe-math-optimizations -ffinite-math-only -fno-rounding-math -fno-signaling-nans -fcx-limited-range -fexcess-precision=fast -fsingle-precision-constant -fcx-fortran-rules 

clean:
	@echo Done.
	@rm -rf *.dSYM row string_ex2 sterge1 sterge2 sterge7 sterge8 find sterge8 sterge9 sterge10 sterge11 sterge13 net2 net3 sock2 test1 test2 test2.s date_ex cachegrind.out* test3 funcs3 path libdate.a date_ex.o test4 date2 date2.o excel2.o *.xlsx test5 test6 test7 callgrind.out.* perf.data log_file main mail_ssl test8 test9 final_program mail *.gcda


