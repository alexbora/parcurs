/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : net
 * @created     : Joi Apr 14, 2022 18:32:41 EEST
 */

#include "date.h"

#include <arpa/inet.h>
#include <assert.h>
#include <netdb.h>
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> /* socket, connect */
#include <unistd.h>

static const ssize_t fetch(const uint_fast64_t year,
                           const char          buf[static const restrict 1])
{
  struct addrinfo hints = {.ai_family   = AF_INET,
                           .ai_socktype = SOCK_STREAM,
                           .ai_protocol = IPPROTO_TCP,
                           .ai_flags    = AI_PASSIVE},
                  *res  = NULL;

  const char *restrict const host =
      "us-central1-romanian-bank-holidays.cloudfunctions.net";
  int register x = getaddrinfo(host, "80", &hints, &res);
  if (x)
    return 0;

  const int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (sockfd < 0)
    return 0;
  x = connect(sockfd, res->ai_addr, res->ai_addrlen);
  if (x)
    return 0;
  puts("\n\x1b[32mConnected.\x1b[0m\n");

  char      header[256] = {'\0'};
  const int len_header =
      sprintf(header,
              "GET /romanian_bank_holidays/?year=%llu HTTP/1.1\r\nHost: "
              "%s\r\n\r\n",
              year, host);

  const ssize_t sent = send(sockfd, header, (size_t)len_header, 0);
  if (sent <= 0)
    return 0;

  char *restrict p       = (char *restrict)buf;
  const ssize_t received = recv(sockfd, p, 4 * 1024, 0);
  if (received < 1)
    return 0;
  freeaddrinfo(res);
  res = NULL;
  shutdown(sockfd, SHUT_RDWR);
  close(sockfd);
  return received;
}

static ssize_t parse(char **in, ssize_t received)
{
  received -= 14;
  char *tmp = *in;
  while (received--) {
    if (*tmp++ == '[')
      break;
  }
  return received;
}

int main(int argc, char *argv[])
{
  char *buf = malloc(4096);
  int   r;
  if ((r = fetch(2022, buf)) > 0)
    parse(&buf, r);
  puts(buf);

  return 0;
}
