
all: libdate.a 
	gcc-11 -static libdate.a -o date_ex

libdate.a: date_ex.o 
	ar rcs $@ $^
	ranlib $@

compile:
	gcc-11 -c date_ex.c -o date_ex.o 
