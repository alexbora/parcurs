#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/ssl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> /* socket, connect */
#include <unistd.h>

#define h_addr h_addr_list[0] /* for backward compatibility */

static inline int socket_setopt(int sockfd, int level, int optname,
                                int optval) {
  return setsockopt(sockfd, level, optname, (void *)&optval, sizeof(optval));
}

static SSL *init_sock(const char *host, const int port) {
  struct hostent *he = NULL;
  char **ap = NULL;
  he = gethostbyname(host);
  if (he == NULL) {
    fprintf(stderr, "no host\n");
    goto fail;
  }
  int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sockfd < 0) {
    fprintf(stderr, "no socket\n");
    goto fail;
  }
  struct sockaddr_in sa = (struct sockaddr_in){
      .sin_family = AF_INET,
      .sin_port = htons(port),
      .sin_addr.s_addr = *(long *)(he->h_addr),
  };

  int connection =
      connect(sockfd, (const struct sockaddr *)&sa, sizeof(struct sockaddr_in));
  if (connection == -1) {
    fprintf(stderr, "no connection\n");
    goto fail;
  }
  socket_setopt(sockfd, IPPROTO_TCP, SO_SNDLOWAT, 1);

  int n = 0; //#if OPENSSL_VERSION_NUMBER < 0x10100000L //SSL_library_init( );
  n = OPENSSL_init_ssl(OPENSSL_INIT_NO_LOAD_SSL_STRINGS |
                           OPENSSL_INIT_ADD_ALL_DIGESTS |
                           OPENSSL_INIT_NO_LOAD_CONFIG | OPENSSL_INIT_ASYNC |
                           OPENSSL_INIT_NO_ATEXIT,
                       NULL);
  if (n == 0) {
    fprintf(stderr, "ssl init fail\n");
    goto fail;
  } //#endif  // SSL_library_init( );

  const SSL_METHOD *method = TLS_client_method();
  if (!method)
    goto fail;
  SSL_CTX *ctx = SSL_CTX_new(method);
  if (!ctx)
    goto fail;
  SSL *ssl = SSL_new(ctx);
  if (!ssl)
    goto fail;
  SSL_set_read_ahead(ssl, 1);
  SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
  SSL_set_fd(ssl, sockfd);
  SSL_set_tlsext_host_name(ssl, host);
  if (0 < SSL_connect(ssl)) {
    printf("Connected to Coinabse with %s encryption\n", SSL_get_cipher(ssl));
  } else {
    goto fail;
  }
  return ssl;
fail:
  fprintf(stderr, "init failed at line %d\n", __LINE__);
  return NULL;
}

int main(int argc, char *argv[]) {
  SSL *s = init_sock("smtp.gmail.com", 465);
  SSL_shutdown(s);

  return 0;
}
