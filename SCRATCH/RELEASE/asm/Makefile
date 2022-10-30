LIBS=-lpthread
FLAGS=-O3 -fno-plt

server: 
	gcc-12 $(LIBS) $(FLAGS) server.c -o server

server1: 
	gcc-12 $(LIBS) $(FLAGS) server1.c -o server

server_original: 
	gcc-12 $(LIBS) $(FLAGS) server_original.c -o server

server_bogo: 
	gcc-12 $(LIBS) $(FLAGS) server_bogo.c -o server
server_bogo_log: 
	gcc-12 -DNDEBUG -DLOG $(LIBS) $(FLAGS) server_bogo.c -o server
clean: 
	@rm -rf server *.dSYM  && printf 'Cleaned.\n'
