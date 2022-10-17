CC=gcc-12

all: 
	gcc-12 vector1.c -o vector `pkg-config --libs gtk+-3.0` `pkg-config --cflags gtk+-3.0`

gtk:
	gcc-12 gtk4.c -o gtk4 -fno-plt -O3 `pkg-config --libs gtk+-3.0` `pkg-config --cflags gtk+-3.0` -w

static: libgtk4.a 
	$(CC) gtk4.c libgtk4.a -o gtk4 -fno-plt -O3 `pkg-config --libs gtk+-3.0` `pkg-config --cflags gtk+-3.0` -w
libgtk4.a: gtk4.o 
	ar -rcs libgtk4.a gtk4.o 
gtk4.o: gtk4.c 	
	$(CC) gtk4.c -c -o gtk4.o -fno-plt -O3 `pkg-config --libs gtk+-3.0` `pkg-config --cflags gtk+-3.0` -w
