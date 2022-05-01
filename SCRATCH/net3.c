
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/x509.h>
#include <openssl/x509_vfy.h>
#include <resolv.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
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

const char *const host = "example.org";

static int sock(const int flags)
{
  struct addrinfo hints = {.ai_family   = AF_INET,
                           .ai_socktype = SOCK_STREAM,
                           .ai_protocol = IPPROTO_TCP,
                           .ai_flags    = AI_PASSIVE},
                  *res  = NULL;

  if (flags & CONNECT_VERBOSE)
    fprintf(stderr, "Looking up %s ... ", host);

  int x = getaddrinfo(host, "80", &hints, &res);
  if (x) {
    puts(gai_strerror(x));
    return 0;
  }

  if (flags & CONNECT_VERBOSE)
    fprintf(stderr, "done.\nConnecting to %s (port %s) ... ", host, "443");

  int sockfd = -1;
  sockfd     = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  int c      = connect(sockfd, res->ai_addr, res->ai_addrlen);
  if (sockfd == 3 && flags & CONNECT_VERBOSE)
    fprintf(stderr, "done.\n");

  char      header[256] = {'\000'};
  const int len_header  = sprintf(header,
                                  "GET /index.html HTTP/1.1\r\nHost: "
                                   "%s\r\n\r\n",
                                  host);

  send(sockfd, header, len_header, 0);
  char buf[4096] = {'\1'};
  recv(sockfd, buf, 4096, 0);
  puts(buf);
  /* safety */
  memset(res, 0, sizeof(struct addrinfo));
  freeaddrinfo(res);
  res = NULL;

  return sockfd;
}

int main(int argc, char *argv[])
{
  /* SSL_library_init(); */
  /* OpenSSL_add_all_algorithms(); */
  /* SSL_CTX *ctx = SSL_CTX_new(SSLv23_client_method()); */
  /* SSL_CTX_set_options(ctx, SSL_OP_SINGLE_DH_USE | SSL_OP_NO_TLSv1_3); */
  /* SSL *ssl = SSL_new(ctx); */

  int s = sock(CONNECT_VERBOSE);

  /* send(s, "GET host HTTP/1.1\r\n\r\n", strlen("GET host HTTP/1.1\r\n\r\n"),
   * 0); */
  /* SSL_set_fd(ssl, s); */
  /* SSL_write(ssl, "GET host HTTP/1.1\r\n\r\n", */
  /* strlen("GET host HTTP/1.1\r\n\r\n")); */

  /* char buf[4096]; */
  /* recv(s, buf, 4096, 0); */
  /* SSL_read(ssl, buf, 4096); */

  /* puts(buf); */
  return 0;
}
