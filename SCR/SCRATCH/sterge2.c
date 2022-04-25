/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : sterge2
 * @created     : Duminică Apr 03, 2022 13:35:37 EEST
 */

#include <stdlib.h>
#include <sys/_types/_timeval.h>
#ifndef __linux__
#include <sys/_types/_u_int8_t.h>
#endif
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
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

__pure static ssize_t fetch(const uint_fast64_t year,
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

static int csprng_bytes(void *buf, size_t len)
{
#if defined(HAVE_ARC4RANDOM) || defined(HAVE_ARC4RANDOM_LIBBSD)
  /* This function never returns an error. */
  puts("arcrandom");
  arc4random_buf(buf, len);
  return 0;
#elif defined(HAVE_GETRANDOM)
  puts("get random");
  ssize_t res;
  char   *p = buf;
  while (len) {
    res = getrandom(p, len, 0);
    if (res < 0)
      return -1;
    len -= res;
    p += res;
  }
  return 0;
#elif defined(HAVE_GETENTROPY)
  puts("entropy");
  int   res;
  char *p = buf;
  while (len) {
    /* getentropy has a maximum size of 256 bytes. */
    size_t chunk = len < 256 ? len : 256;
    res          = getentropy(p, chunk);
    if (res < 0)
      return -1;
    len -= chunk;
    p += chunk;
  }
  return 0;
#elif defined(HAVE_RTLGENRANDOM)
  puts("rtl");
  if (!RtlGenRandom(buf, len))
    return -1;
  return 0;
#elif defined(HAVE_OPENSSL_CSPRNG)
  puts("openssl");
  int res = RAND_bytes(buf, len);
  if (res == 1)
    return 0;
  if (res == -1)
    errno = ENOTSUP;
  else
    errno = EIO;
  return -1;
#else
  puts("else");
  ssize_t res;
  char   *p = buf;
  int     fd, err;
  fd = open("/dev/urandom", O_RDONLY);
  if (fd < 0)
    return -1;
  while (len) {
    res = read(fd, p, len);
    if (res < 0) {
      err = errno;
      close(fd);
      errno = err;
      return -1;
    }
    len -= res;
    p += res;
  }
  close(fd);
  return 0;
#endif
}

int trace2_cmd_exit_fl(const char *file, int line, int code)
{
  fprintf(stderr, "%s %d %d", file, line, code);
  exit(code);
}

#define exit(code) exit(trace2_cmd_exit_fl(__FILE__, __LINE__, (code)))
#include <sys/time.h>
int main()
{
  struct timeval now;
  gettimeofday(&now, NULL);
  printf("%d\n", now.tv_usec);
  int  er = 0;
  int *e  = &er;

  printf("PATH : %s\n", getenv("GIT_TEST_DATE_NOW"));
  struct Tmp {
    char *a;
    int   x;
  } tmp[] = {{"test", 1}, {"test2", 2}, {"test3", 3}, {NULL}};

  struct Tmp *t = tmp;
  while (t->a) {
    printf("%s %d\n", t->a, t->x);
    t++;
  }

  char *b = malloc(16);
  printf("prng: %d\n", csprng_bytes(b, 16));
  printf("%s\n", b);

  const char *out = malloc(16);
  printf("TEST: %d %s\n", skip_prefix("date", "da", &out), out);

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
