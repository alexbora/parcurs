CC=gcc-11 -O3 -std=c11


all: libdate.a 
	gcc-11 -static libdate.a -o date_ex

libdate.a: date_ex.o 
	ar rcs $@ $^
	ranlib $@

