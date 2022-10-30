/**
 * @author      : alex (alex@T400)
 * @file        : server
 * @created     : miercuri oct 26, 2022 20:49:14 EEST
 */

#ifdef __linux__
#include <bits/pthreadtypes.h>
#endif
#include <netinet/in.h>
/* #define _GNU_SOURCE */

#include <arpa/inet.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
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
  {}
#else
static FILE *error_log;
static unsigned char error_mode;
#define STOP_IF(assertion, error_action, ...)                                  \
  {                                                                            \
    if (assertion) {                                                           \
      fprintf(error_log ? error_log : stderr, __VA_ARGS__);                    \
      fprintf(error_log ? error_log : stderr, "\n");                           \
      if (error_mode == 'x')                                                   \
        abort();                                                               \
      else {                                                                   \
        error_action;                                                          \
      }                                                                        \
    }                                                                          \
  }
#endif

static pthread_t t1;
static pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t c1 = PTHREAD_COND_INITIALIZER;
static uint8_t connections;
static int sock;

static void *foo(void *in) {

  int sockfd = *(int *)in;
  char client_request[BUFSIZ] = {[0 ... BUFSIZ - 1] = 0};
  memset(client_request, '\0', BUFSIZ);
  recv(sockfd, client_request, 8192, 0);
  while (!connections) {
    pthread_cond_wait(&c1, &m1);
  }

  puts("connected\n");
  return NULL;
}

static void getip(int s, int *ip) {
  socklen_t size = sizeof(struct sockaddr_in);
  struct sockaddr_in addr;
  getsockname(s, (struct sockaddr *)&addr, &size);

  char *host = inet_ntoa(addr.sin_addr);
  sscanf(host, "%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]);
}

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  connections = 0;
  pthread_mutex_lock(&m1);
  pthread_create(&t1, NULL, foo, &sock);

  sock = socket(AF_INET, SOCK_STREAM, 0);
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &(int[]){1}, sizeof(int));

  const struct sockaddr_in server = {.sin_family = AF_INET,
                                     .sin_addr.s_addr = INADDR_ANY,
                                     .sin_port = htons(8080)};

  struct sockaddr_in client;

  int b = bind(sock, (const struct sockaddr *)&server, sizeof(server));

  STOP_IF(b < 0, return EXIT_FAILURE, "could not bind to socket\n");

  listen(sock, 3);

  while (1) {
    int conn = accept(sock, (struct sockaddr *)&client,
                      (socklen_t *)(sizeof(struct in_addr)));
    if (conn) {
      write(conn, "200 \n", 5);
      connections++;
      pthread_mutex_unlock(&m1);
      pthread_cond_broadcast(&c1);
    } /* int ip[4] = {[0 ... 3] = 0}; */
    /* getip(sock, ip); */
    /* printf("Connection from: [%d.%d.%d.%d]\n", ip[0], ip[1], ip[2], ip[3]);
     */

    pthread_join(t1, NULL);
    /* int pid = fork(); */
  }

  shutdown(sock, 2);
  close(sock);

  return EXIT_SUCCESS;
}
