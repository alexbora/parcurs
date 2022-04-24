/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : net
 * @created     : Joi Apr 14, 2022 18:32:41 EEST
 */

/* #define __POSIX_C_SOURCE = 200112L */
#include "date.h"

#include <arpa/inet.h>
#include <assert.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> /* socket, connect */
#include <unistd.h>

/* void net_fetch(void); */

#ifdef LOG
#define fd open("log", O_CREAT | O_RDWR | O_APPEND, 0777)
#else
#define fd 2 // stderr
#endif

#define CON_MSG "\n\x1b[32mConnected.\x1b[0m\n"

#define ATTENTION_REQ_FLAG    0x0008
#define DATA_RECEIVE_COMPLETE 0x0001

uint16_t event;

static ssize_t fetch(char *buf, const int year)
{
  struct addrinfo hints = {.ai_family   = AF_INET,
                           .ai_socktype = SOCK_STREAM,
                           .ai_protocol = IPPROTO_TCP,
                           .ai_flags    = AI_PASSIVE},
                  *res  = NULL;

  const char *const host =
      "us-central1-romanian-bank-holidays.cloudfunctions.net";
  int x = getaddrinfo(host, "80", &hints, &res);
  if (x)
    return 0;

  const int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (sockfd < 0)
    return 0;
  x = connect(sockfd, res->ai_addr, res->ai_addrlen);
  if (x)
    return 0;

  /* fprintf(stderr, "\n\x1b[32mConnected.\x1b[0m\n"); */
  fprintf(stderr, CON_MSG);

  char      header[256] = {'\0'};
  const int len_header =
      sprintf(header,
              "GET /romanian_bank_holidays/?year=%d HTTP/1.1\r\nHost: "
              "%s\r\n\r\n",
              year, host);

  const ssize_t sent = send(sockfd, header, (size_t)len_header, 0);
  if (sent <= 0)
    return 0;

  char *p                = buf;
  *p                     = '\0';
  const ssize_t received = recv(sockfd, p, 4 * 1024, 0);
  if (received < 1)
    return 0;

  /* fprintf(stderr, "%s\n", p); */
  write(fd, p, strlen(p));

  if (strstr(p, "500"))
    return 0;
  /* safety */
  memset(res, 0, sizeof(struct addrinfo));
  freeaddrinfo(res);
  res = NULL;

  shutdown(sockfd, SHUT_RDWR);
  close(sockfd);
  event = DATA_RECEIVE_COMPLETE;

  return received;
}

static inline char *parse(char *in)
{
  while (*in++ != '[')
    ;
  return in;
}

static inline void fill_struct(char *const in, struct Net *const h)
{
  char *x = in;
  int   i = 0;
  while (x++) {
    x = strstr(x, "date");
    if (!x)
      break;
    h[i].day   = atoi(x + 7);
    h[i].month = atoi(x + 10);
    i++;
  }
}

void net_fetch(void)
{
  char *buf = calloc(1, 4 * 1024);

  fetch(buf, current_year);
  if (event & DATA_RECEIVE_COMPLETE) {
    char *result = parse(buf);
    /* h_ptr = (struct Net[32]){{0}}; */
    fill_struct(result, h_ptr);
    event &= ~DATA_RECEIVE_COMPLETE;
  } else {
    event = ATTENTION_REQ_FLAG;
  }
  fprintf(stderr, "event: %d\n", event);
  /* safety */
  memset(buf, '\0', 4 * 1024);
  free(buf);
  buf = NULL;
}
