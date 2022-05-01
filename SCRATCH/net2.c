#define __POSIX_C_SOURCE = 200112L
#include <arpa/inet.h>
#include <assert.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <openssl/ssl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> /* socket, connect */
#include <unistd.h>

#define CON_MSG         "\n\x1b[32mConnected.\x1b[0m\n"
#define CONNECT_VERBOSE 1

static ssize_t fetch(char *buf, const int year, const int flags, SSL *ssl)
{
  struct addrinfo hints = {.ai_family   = AF_INET,
                           .ai_socktype = SOCK_STREAM,
                           .ai_protocol = IPPROTO_TCP,
                           .ai_flags    = AI_PASSIVE},
                  *res  = NULL;

  const char *const host = "www.calendarific.com";

  if (flags & CONNECT_VERBOSE)
    fprintf(stderr, "Looking up %s ... ", host);

  int x = getaddrinfo(host, "443", &hints, &res);
  if (x) {
    puts(gai_strerror(x));
    return 0;
  }

  if (flags & CONNECT_VERBOSE)
    fprintf(stderr, "done.\nConnecting to %s (port %s) ... ", host, "443");

  int sockfd = -1;
  sockfd     = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

  if (sockfd < 0)
    return 0;

  SSL_set_fd(ssl, sockfd);
  if (SSL_connect(ssl) == 1)
    puts("connect\n");

  x = connect(sockfd, res->ai_addr, res->ai_addrlen);
  if (x)
    return 0;

  if (flags & CONNECT_VERBOSE) {
    fprintf(stderr, "done.");
    fprintf(stderr, CON_MSG);
  }

  char      header[256] = {'\000'};
  const int len_header  = sprintf(
       header,
       "GET /"
        "/api/v2/"
        "holidays?&api_key=6354938168d76b7df8711085ba5dd4aab9759cd2&country=RO&"
        "year=%d HTTP/1.1\r\nHost: calendarific.com\r\n\r\n",
       year);

  int err = SSL_write(ssl, header, len_header);
  printf("%d\n", err);
  int e = SSL_get_error(ssl, err);
  printf("%d\n", e);

  const ssize_t sent = send(sockfd, header, (size_t)len_header, 0);
  {
    if (sent <= 0)
      return 0;
  }

  char *p = buf;

  SSL_read(ssl, p, 4096);
  puts(" ---\n ");
  puts(p);
  /* const ssize_t received = recv(sockfd, p, 4 * 1024, 0); */
  /* if (received < 1) */
  /* return 0; */

  if (flags & CONNECT_VERBOSE)
    fprintf(stderr, "%s\n", p);

  /* safety */
  memset(res, 0, sizeof(struct addrinfo));
  freeaddrinfo(res);
  res = NULL;

  shutdown(sockfd, SHUT_RDWR);
  close(sockfd);
  return 0;
  /* return received; */
}

int main(int argc, char *argv[])
{
  SSL_library_init();
  OpenSSL_add_all_algorithms();
  SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());
  SSL_CTX_set_options(ctx, SSL_OP_SINGLE_DH_USE);
  SSL *ssl = SSL_new(ctx);

  char buf[4096];
  fetch(buf, 2022, CONNECT_VERBOSE, ssl);
  puts(buf);
  return 0;
}
