/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : net
 * @created     : Joi Apr 14, 2022 18:32:41 EEST
 */

/* #define __POSIX_C_SOURCE = 200112L */
#include "date.h"
#include "main.h"
#include <arpa/inet.h>
#include <assert.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> /* socket, connect */
#include <unistd.h>

#ifdef LOG
#define fd open("log", O_CREAT | O_RDWR | O_APPEND, 0777)
#undef stderr
#define stderr l
#else
#define fd 2 // stderr
#endif

#define CON_MSG "\n\x1b[32mConnected.\x1b[0m\n"

/* extern int current_year; */
/* extern struct Net *h_ptr; */

static ssize_t fetch(char *buf, const int year, const int flags) {
  struct addrinfo hints = {.ai_family = AF_INET,
                           .ai_socktype = SOCK_STREAM,
                           .ai_protocol = IPPROTO_TCP,
                           .ai_flags = AI_PASSIVE},
                  *res = NULL;

  const char *const host =
      "us-central1-romanian-bank-holidays.cloudfunctions.net";

  if (flags & CONNECT_VERBOSE)
    fprintf(stderr, "Looking up %s ... ", host);

  int x = getaddrinfo(host, "80", &hints, &res);
  if (x)
    return 0;

  if (flags & CONNECT_VERBOSE)
    fprintf(stderr, "done.\nConnecting to %s (port %s) ... ", host, "80");

  int sockfd = -1;
  sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

  if (sockfd < 0)
    return 0;

  x = connect(sockfd, res->ai_addr, res->ai_addrlen);
  if (x)
    return 0;

  if (flags & CONNECT_VERBOSE) {
    fprintf(stderr, "done.");
    fprintf(stderr, CON_MSG);
  }

  char header[256] = {'\000'};
  const int len_header =
      sprintf(header,
              "GET /romanian_bank_holidays/?year=%d HTTP/1.1\r\nHost: "
              "%s\r\n\r\n",
              year, host);

  const ssize_t sent = send(sockfd, header, (size_t)len_header, 0);
  if (sent <= 0)
    return 0;

  char *p = buf;
  const ssize_t received = recv(sockfd, p, 4 * 1024, 0);
  if (received < 1)
    return 0;

  if (flags & CONNECT_VERBOSE)
    fprintf(stderr, "%s\n", p);

  /* safety */
  memset(res, 0, sizeof(struct addrinfo));
  freeaddrinfo(res);
  res = NULL;

  shutdown(sockfd, SHUT_RDWR);
  close(sockfd);

  return received;
}

static inline char *parse(char in[const static 1]) {
  char *p = in;
  if (strstr(p, "500"))
    return NULL;

  while (p++) {
    if (*p == '[') {
      break;
      return p;
    }
  }
  return NULL;
}

static inline void fill_struct(char in[const static 1], struct Net *h) {
  char *x = in;
  int i = 0;
  struct Net tmp[32] = {{0}};
  while (x++) {
    x = strstr(x, "date");
    if (!x)
      break;
    tmp[i].day = atoi(x + 7);
    tmp[i].month = atoi(x + 10);
    i++;
  }
  memcpy(h, tmp, sizeof(tmp));
}

void net_fetch(const int flags) {

  char buf[4 * 1024] = {'\0'};

  ssize_t f = fetch(buf, current_year, flags);

  if (!f)
    return;

  char *result = parse(buf);

  if (!result || *result == '\0') {
    h_ptr = NULL;
    return;
  }

  h_ptr = (struct Net[32]){{0}};
  fill_struct(result, h_ptr);

  result = NULL;

  /* safety */
  memset(buf, '\0', 4 * 1024);
  f = 0;
}
