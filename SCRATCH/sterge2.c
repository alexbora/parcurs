/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : sterge2
 * @created     : Duminică Apr 03, 2022 13:35:37 EEST
 */

#include <stdlib.h>
#include <sys/_types/_u_int8_t.h>
#if defined(_WINDOWS) || defined(_WIN32) || defined(_WIN64)
#error "Leave Bill alone, get an Unix box.\n"
#endif
#include <arpa/inet.h>
#include <assert.h>
#include <limits.h>
#include <locale.h>
#include <netdb.h>
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_size_t.h>
#include <sys/_types/_ssize_t.h>
#include <sys/ioctl.h>  /* ioctl()  */
#include <sys/socket.h> /* socket, connect */
#include <sys/uio.h>
#include <time.h>
#include <unistd.h>
#ifdef __APPLE__
#include <sys/_types/_ucontext.h>
#include <sys/syslimits.h>
#endif
#include <unistd.h>

#define LAST_ARG_MUST_BE_NULL __attribute__((sentinel))
__pure static const ssize_t fetch(const uint_fast64_t year,
                                  const char buf[static const restrict 1])
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

#define alloc_nr(x) (((x) + 16) * 3 / 2)
#define HAS_MULTI_BITS(i)                                                      \
  ((i) & ((i)-1)) /* checks if an integer has more than 1 bit set */

#define DIV_ROUND_UP(n, d) (((n) + (d)-1) / (d))

static inline int skip_prefix(const char *str, const char *prefix,
                              const char **out)
{
  do {
    if (!*prefix) {
      *out = str;
      return 1;
    }
  } while (*str++ == *prefix++);
  return 0;
}

int main()
{

  const char *out = malloc(16);
  printf("TEST: %d %s\n", skip_prefix("test", "tes", &out), out);

  char   *buf      = malloc(4096);
  char  **buf_p    = &buf;
  ssize_t received = fetch((uint_fast64_t)2022, *buf_p);
  free(*buf_p);

  int y = 3;
  printf("%d\n", alloc_nr(y));
  y = alloc_nr(y);
  printf("%d\n", 2 * 3 / 2);
  printf("multi: %d\n", HAS_MULTI_BITS(y));

  printf("%d\n", DIV_ROUND_UP(3, 4));
  return 0;
}
