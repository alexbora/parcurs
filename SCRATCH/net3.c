
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

#define CON_MSG "\n\x1b[32mConnected.\x1b[0m\n"
#define CONNECT_VERBOSE 1

void InitializeSSL() {
  SSL_load_error_strings();
  SSL_library_init();
  OpenSSL_add_all_algorithms();
}

void DestroySSL() {
  ERR_free_strings();
  EVP_cleanup();
}

static ssize_t fetch(char *buf, const int year, const int flags, SSL *ssl) {
  struct addrinfo hints = {.ai_family = AF_INET,
                           .ai_socktype = SOCK_STREAM,
                           .ai_protocol = IPPROTO_TCP,
                           .ai_flags = AI_PASSIVE},
                  *res = NULL;

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
  sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

  SSL_set_fd(ssl, sockfd);
  SSL_connect(ssl);

  char header[256] = {'\000'};
  const int len_header = sprintf(
      header,
      "GET "
      "/api/v2/"
      "holidays?&api_key=6354938168d76b7df8711085ba5dd4aab9759cd2&country=RO&"
      "year=%d HTTP/1.1\r\nHost: calendarific.com\r\n\r\n",
      year);

  SSL_write(ssl, header, len_header);

  char *p = buf;

  SSL_read(ssl, p, 4096);
  puts(p);

  /* safety */
  memset(res, 0, sizeof(struct addrinfo));
  freeaddrinfo(res);
  res = NULL;

  shutdown(sockfd, SHUT_RDWR);
  close(sockfd);
  return 0;
  /* return received; */
}

int main(int argc, char *argv[]) {
  SSL_library_init();
  InitializeSSL();
  OpenSSL_add_all_algorithms();
  SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());
  SSL_CTX_set_options(ctx, SSL_OP_SINGLE_DH_USE);
  SSL *ssl = SSL_new(ctx);

  char buf[4096];
  fetch(buf, 2022, CONNECT_VERBOSE, ssl);
  return 0;
}
