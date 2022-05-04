//#include "/home/alex/tech/include/allheaders.h"
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <openssl/evp.h>
#include <openssl/ssl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define h_addr h_addr_list[0] /* for backward compatibility */

#ifndef INADDR_NONE
#define INADDR_NONE 0xffffffff
#endif

static inline int sockfd(const char hostname[static 1], const int port)
{
  struct sockaddr_in servAddr = {.sin_family = AF_INET,
                                 .sin_port   = htons(port)};

  int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  struct hostent *host     = gethostbyname(hostname);
  servAddr.sin_addr.s_addr = *(long *)(host->h_addr);
  memcpy(&servAddr.sin_addr.s_addr, host->h_addr, host->h_length);

  int err = connect(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr));

  return sockfd;
}

static inline SSL *ssl_conn(const int sockfd, const char *hostname)
{
  SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());
  SSL     *ssl = SSL_new(ctx);
  SSL_set_fd(ssl, sockfd);
  SSL_set_tlsext_host_name(ssl, (const char *)hostname);
  SSL_connect(ssl);
  return ssl;
}

int main(void)
{
  char *hostname = "calendarific.com";
  int   port     = 443;
  int   sock     = sockfd(hostname, port);

  /* int ofcmode = fcntl(sock, F_GETFL, 0); */
  /* ofcmode |= O_NDELAY; */
  //   fcntl(sock,F_SETFL,ofcmode);

  SSL *s = ssl_conn(sock, hostname);
  printf("SSL connection on socket %x,Version: %s, Cipher: %s\n", sock,
         SSL_get_version(s), SSL_get_cipher(s));
  char buf[4096 * 4];

  char HEADER[256];
  int  len = sprintf(
       HEADER,
       "GET "
        "/api/v2/"
        "holidays?&api_key=6354938168d76b7df8711085ba5dd4aab9759cd2&country=RO&"
        "year=%d HTTP/1.1\r\nHost: %s\r\nUser-Agent: OpenSSL\r\n\r\n",
       2022, hostname);

  SSL_write(s, HEADER, len);
  SSL_read(s, buf, 4096 * 2);
  /* puts(buf); */

  char *p = strstr(buf, "iso");

  printf("%d\n", atoi(p + 6));

  /* while (1 < SSL_read(s, buf, 4096)) */
  /* printf("%s\n", buf); */
}