/**
 * @author      : alex (alex@T400)
 * @file        : server
 * @created     : miercuri oct 26, 2022 20:49:14 EEST
 */

#define _GNU_SOURCE

#include <arpa/inet.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sendfile.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

void *foo(void *a) { return NULL; }

int main(int argc, char *argv[]) {

  pthread_t t1;
  pthread_create(&t1, NULL, foo, NULL);

  return EXIT_SUCCESS;
}
