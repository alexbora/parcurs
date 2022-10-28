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
FILE         *error_log;
unsigned char error_mode;
#define STOP_IF(assertion, error_action, ...)                                  \
  {                                                                            \
    if (assertion) {                                                           \
      fprintf(error_log ? error_log : stderr, __VA_ARGS__);                    \
    }                                                                          \
    if (error_mode == 'x') {                                                   \
      abort();                                                                 \
    } else {                                                                   \
      error_action;                                                            \
    }                                                                          \
  }
#endif

pthread_t t1;
int       sock;

void *foo(void *in)
{
  int  sockfd = *(int *)in;
  char client_request[BUFSIZ];
  recv(sockfd, client_request, 8192, 0);
  puts("connected\n");
  return NULL;
}

void getip(int sock, int *ip)
{
  socklen_t          addr_size = sizeof(struct sockaddr_in);
  struct sockaddr_in addr;
  getsockname(sock, (struct sockaddr *)&addr, &addr_size);

  char *host = inet_ntoa(addr.sin_addr);
  sscanf(host, "%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]);
}

int main(int argc, char *argv[])
{
  sock = socket(AF_INET, SOCK_STREAM, 0);
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &(int[]){1}, sizeof(int));

  const struct sockaddr_in server = {.sin_family      = AF_INET,
                                     .sin_addr.s_addr = INADDR_ANY,
                                     .sin_port        = htons(8080)};

  struct sockaddr_in client = {};

  int b = bind(sock, (const struct sockaddr *)&server, sizeof(server));

  STOP_IF(b < 0, return -1, "could not bind to socket\n");

  listen(sock, 3);

  while (1) {
    int conn = accept(sock, (struct sockaddr *)&client,
                      (socklen_t *)(sizeof(struct in_addr)));
    write(conn, "200 \n", 5);

    pthread_create(&t1, NULL, foo, &sock);
    pthread_join(t1, NULL);
    int pid = fork();
  }

  shutdown(sock, 2);
  close(sock);

  return EXIT_SUCCESS;
}
