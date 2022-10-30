/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : server_bogo
 * @created     : Sunday Oct 30, 2022 14:17:30 UTC
 */

/* The port number is passed as an argument */
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <netinet/in.h>
/* #define _GNU_SOURCE */

#include <arpa/inet.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef __linux__
#include <sys/sendfile.h>
#endif
#include <errno.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

FILE* error_log;
#ifdef NDEBUG
#define STOP_IF                                                                \
  {                                                                            \
  }
FILE* error_log = NULL;
#else

#define STOP_IF(expression, action, error_code, ...)                           \
  {                                                                            \
    if (expression) {                                                          \
      fprintf(error_log ? error_log : stderr, __VA_ARGS__);                    \
      fprintf(error_log ? error_log : stderr, "\n");                           \
      if (error_code == 1)                                                     \
        abort();                                                               \
      else {                                                                   \
        action;                                                                \
      }                                                                        \
    }                                                                          \
  }
#endif

static void
error(const char* msg)
{
  perror(msg);
  exit(1);
}

#define PORT 8080

int
main(int argc, char* argv[])
{
#ifdef LOG
  error_log = fopen("server.log", "wb++");
#else
  error_log = NULL;
#endif
  int                sockfd, newsockfd, portno;
  socklen_t          clilen;
  char               buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  int                n;
  if (argc < 2) {
    fprintf(stderr, "ERROR, no port provided\n");
    fprintf(stderr, "defaulting to: %d\n", PORT);
    /* exit(1); */
  }
  // create a socket
  // socket(int domain, int type, int protocol)
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int[]){1}, sizeof(int));
  if (sockfd < 0) error("ERROR opening socket");

  // clear address structure
  bzero((char*) &serv_addr, sizeof(serv_addr));

  portno = (argc == 2) ? atoi(argv[1]) : PORT;

  /* setup the host_addr structure for use in bind call */
  // server byte order
  serv_addr.sin_family = AF_INET;

  // automatically be filled with current host's IP address
  serv_addr.sin_addr.s_addr = INADDR_ANY;

  // convert short integer value for port must be converted into network byte
  // order
  serv_addr.sin_port = htons(portno);

  // bind(int fd, struct sockaddr *local_addr, socklen_t addr_length)
  // bind() passes file descriptor, the address structure,
  // and the length of the address structure
  // This bind() call will bind  the socket to the current IP address on port,
  // portno
  if (bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
    error("ERROR on binding");

  // This listen() call tells the socket to listen to the incoming connections.
  // The listen() function places all incoming connection into a backlog queue
  // until accept() call accepts the connection.
  // Here, we set the maximum size for the backlog queue to 5.
  listen(sockfd, 5);

  // The accept() call actually accepts an incoming connection
  clilen = sizeof(cli_addr);

  // This accept() function will write the connecting client's address info
  // into the the address structure and the size of that structure is clilen.
  // The accept() returns a new socket file descriptor for the accepted
  // connection. So, the original socket file descriptor can continue to be used
  // for accepting new connections while the new socker file descriptor is used
  // for communicating with the connected client.
  newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);
  if (newsockfd < 0) error("ERROR on accept");
  fprintf(error_log, "%s\n", "accepting");
  printf("server: got connection from %s port %d\n",
         inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));

  // This send() function sends the 13 bytes of the string to the new socket
  send(newsockfd, "Hello, world!\n", 13, 0);

  bzero(buffer, 256);

  n = read(newsockfd, buffer, 255);
  if (n < 0) error("ERROR reading from socket");
  STOP_IF(n < 0, error("read"), 0, "read failed");
  printf("Here is the message: %s\n", buffer);

  shutdown(sockfd, 2);
  shutdown(newsockfd, 2);
  close(newsockfd);
  close(sockfd);
#ifdef LOG
  fclose(error_log);
#endif
  return 0;
}
