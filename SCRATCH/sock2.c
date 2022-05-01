//#include "/home/alex/tech/include/allheaders.h"
#include <fcntl.h>
#include <netdb.h>
/* #include <openssl/evp.h> */
#include <openssl/ssl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
/* #include<netinet/in.h> */
/* #include<netinet/tcp.h> */
/* #include<sys/types.h> */

#include <sys/signal.h>
#ifdef WIN32
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#define close closesocket
#else
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#define h_addr h_addr_list[0] /* for backward compatibility */

#ifndef INADDR_NONE
#define INADDR_NONE 0xffffffff
#endif

static inline int sockfd(const char hostname[], const int port)
{
  register int       sockfd   = 0;
  struct sockaddr_in servAddr = {0};

#ifdef WIN32
  WSADATA wsaData;
  int     initwsa = WSAStartup(MAKEWORD(2, 0), &wsaData);
  if (initwsa != 0) {
    printf("WSAStartup failed: %d\n", initwsa);
    return 1;
  }
#endif

  sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  /* memset(&servAddr, 0, sizeof(servAddr)); */
  servAddr.sin_family = AF_INET;
  servAddr.sin_port   = htons(port); // 443

  struct hostent *host     = NULL;
  host                     = gethostbyname(hostname);
  servAddr.sin_addr.s_addr = *(long *)(host->h_addr);
  memcpy(&servAddr.sin_addr.s_addr, host->h_addr, host->h_length);

  setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (int[]){1}, sizeof(int));
  setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, (int[]){1}, sizeof(int));
  // setsockopt(sockfd, IPPROTO_TCP, TCP_QUICKACK, (int[]){1}, sizeof(int));
  setsockopt(sockfd, SOL_SOCKET, SO_SNDLOWAT, (int[]){2}, sizeof(int));

  int err = connect(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr));

#ifdef WIN32
  WSACleanup();
#endif

  return sockfd;
}

static inline SSL *ssl_conn(const int sockfd, const char *hostname)
{
  SSL *ssl = NULL;
  SSL_library_init();
  const SSL_METHOD *method = TLS_client_method();
  SSL_CTX          *ctx    = SSL_CTX_new(method);
  ssl                      = SSL_new(ctx);
  SSL_set_fd(ssl, sockfd);
  SSL_set_tlsext_host_name(ssl, hostname);
  SSL_connect(ssl);
  return ssl;
}

int main(void)
{
  char *hostname = "gmail.com";
  int   port     = 443;
  int   sock     = sockfd(hostname, port);

  int ofcmode = fcntl(sock, F_GETFL, 0);
  ofcmode |= O_NDELAY;
  //   fcntl(sock,F_SETFL,ofcmode);

  SSL *s = ssl_conn(sock, hostname);
  /* printf("SSL connection on socket %x,Version: %s, Cipher: %s\n", sockfd, */
  /* SSL_get_version(s), SSL_get_cipher(s)); */
  char buf[4096];

  const char *HEADERS =
      "GET / HTTP/1.1\r\nHost: gmail.com\r\nUser-Agent: OpenSSL\r\n\r\n";

  SSL_write(s, HEADERS, strlen(HEADERS));
  SSL_read(s, buf, 4096);
  puts(buf);

  /* while (1 < SSL_read(s, buf, 4096)) */
  /* printf("%s\n", buf); */
}
