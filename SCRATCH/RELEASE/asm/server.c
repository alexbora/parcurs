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

pthread_t t1;

void *foo(void *in) {
  puts("connected\n");
  return NULL;
}

int main(int argc, char *argv[]) {

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  const struct sockaddr_in server = {.sin_family = AF_INET,
                                     .sin_addr.s_addr = INADDR_ANY,
                                     .sin_port = htons(8080)};

  struct sockaddr_in client;

  bind(sock, (const struct sockaddr *)&server, sizeof(server));
  listen(sock, 3);
  while (1) {
    accept(sock, (struct sockaddr *)&client,
           (socklen_t *)(sizeof(struct in_addr)));
    pthread_create(&t1, NULL, foo, NULL);
    pthread_join(t1, NULL);
  }

  return EXIT_SUCCESS;
}
