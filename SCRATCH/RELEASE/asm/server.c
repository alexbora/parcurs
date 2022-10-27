/**
 * @author      : alex (alex@T400)
 * @file        : server
 * @created     : miercuri oct 26, 2022 20:49:14 EEST
 */

#include <netinet/in.h>
#define _GNU_SOURCE

#include <arpa/inet.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __linux__
#include <sys/sendfile.h>
#endif
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

#ifdef NDEBUG
#define STOP_IF                                                                \
  {                                                                            \
  }
#else
FILE*         error_log;
unsigned char error_mode;
#define STOP_IF(assertion, error_action, ...)                                  \
  {                                                                            \
    if (assertion) { fprintf(error_log ? error_log : stderr, __VA_ARGS__); }   \
    if (error_mode == 'x') {                                                   \
      abort();                                                                 \
    } else {                                                                   \
      error_action;                                                            \
    }                                                                          \
  }
#endif

pthread_t t1;
int       sock;

void*
foo(void* in)
{
  int  sockfd = *(int*) in;
  char client_request[BUFSIZ];
  recv(sockfd, client_request, 8192, 0);
  puts("connected\n");
  return NULL;
}

int
main(int argc, char* argv[])
{

  sock                            = socket(AF_INET, SOCK_STREAM, 0);
  const struct sockaddr_in server = {.sin_family      = AF_INET,
                                     .sin_addr.s_addr = INADDR_ANY,
                                     .sin_port        = htons(8080)};

  struct sockaddr_in client = {};

  int b = bind(sock, (const struct sockaddr*) &server, sizeof(server));

  STOP_IF(b < 0, return -1, "could not bind to socket\n");

  listen(sock, 3);
  while (1) {
    accept(sock, (struct sockaddr*) &client,
           (socklen_t*) (sizeof(struct in_addr)));
    pthread_create(&t1, NULL, foo, &sock);
    pthread_join(t1, NULL);
  }

  return EXIT_SUCCESS;
}
