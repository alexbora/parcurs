all: libs 
	gcc-12 -L./libs -ltest -o main main.c 

libs: clean 
	mkdir -p libs
	gcc-12 -c -o ./libs/libtest.o libtest.c 
	ar -rcs ./libs/libtest.a ./libs/libtest.o

clean: 
	rm -rf ./libs
