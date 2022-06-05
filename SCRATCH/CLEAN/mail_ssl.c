static int socket_setopt(int sockfd, int level, int optname, int optval) {
  return setsockopt(sockfd, level, optname, (void *)&optval, sizeof(optval));
}

SSL *init_sock(struct fix_cfg *cfg, const char *host, const int port) {
  struct hostent *he = NULL;
  char **ap = NULL;
  he = gethostbyname(host);
  if (he == NULL) {
    fprintf(stderr, "no host\n");
    goto fail;
  }
  cfg->sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (cfg->sockfd < 0) {
    fprintf(stderr, "no socket\n");
    goto fail;
  }
  struct sockaddr_in sa;
  sa = (struct sockaddr_in){
      .sin_family = AF_INET,
      .sin_port = htons(port),
      .sin_addr.s_addr = *(long *)(he->h_addr),
  };

  int connection = connect(cfg->sockfd, (const struct sockaddr *)&sa,
                           sizeof(struct sockaddr_in));
  if (connection == -1) {
    fprintf(stderr, "no connection\n");
    goto fail;
  }
  socket_setopt(cfg->sockfd, IPPROTO_TCP,
                TCP_NODELAY | SO_SNDLOWAT | SO_KEEPALIVE,
                1); // SSL *ssl = NULL;

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
  SSL_set_fd(ssl, cfg->sockfd);
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
MAILTO=t400.linux@gmail.com
35 10 * * * /home/alex/tmp/parcurs/SCRATCH/CLEAN/./foaie_5
