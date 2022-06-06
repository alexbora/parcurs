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
#include <sys/mman.h>
#include <sys/socket.h> /* socket, connect */
#include <sys/stat.h>
#include <unistd.h>

#define h_addr h_addr_list[0] /* for backward compatibility */
#define BUF    4096u

static inline void upload(SSL *s, const char *filename)
{
  FILE *fp = fopen(filename, "rb");
  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  rewind(fp);

  unsigned char *buffer = malloc(sizeof(unsigned char) * size);
  fread(buffer, 1, size, fp);

  unsigned char *out_buffer = malloc(sizeof(unsigned char) * size);
  int            out_len    = EVP_EncodeBlock(out_buffer, buffer, size);

  SSL_write(s, out_buffer, out_len);
  /* char *cmd = "\r\n"; */
  /* SSL_write(s, cmd, strlen(cmd)); */

  fclose(fp);
  fp = NULL;
  free(buffer);
  buffer = NULL;
  free(out_buffer);
  out_buffer = NULL;
}

static inline void write_ssl(SSL *s, const char *txt)
{
  const void *buf = (const void *)txt;
  int         n   = (int)strlen(txt);
  SSL_write(s, buf, n);
}

static inline void read_ssl2(SSL *s)
{
  char recvbuf[4096] = {'\0'};
  SSL_read(s, recvbuf, 4096 - 1);
  puts(recvbuf);
}

static inline void read_ssl(SSL *s, char *buf)
{
  bzero(buf, 4096);
  /* *buf = '\0'; */
  /* memset(buf, '\0', 4096); */
  SSL_read(s, buf, 4096 - 1);
  puts(buf);
}

static inline int socket_setopt(int sockfd, int level, int optname, int optval)
{
  return setsockopt(sockfd, level, optname, (void *)&optval, sizeof(optval));
}

static SSL *init_sock(const char *host, const int port)
{
  struct hostent *he = NULL;
  /* char          **ap = NULL; */
  /* *ap                = NULL; */
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
      .sin_family      = AF_INET,
      .sin_port        = htons(port),
      .sin_addr.s_addr = *(long *)(he->h_addr),
  };

  int connection =
      connect(sockfd, (const struct sockaddr *)&sa, sizeof(struct sockaddr_in));
  if (connection == -1) {
    fprintf(stderr, "no connection\n");
    goto fail;
  }
  socket_setopt(sockfd, IPPROTO_TCP, SO_SNDLOWAT | SO_DONTROUTE | SO_DONTTRUNC,
                1);

  /* fd = sockfd; */
  int n = 0; //#if OPENSSL_VERSION_NUMBER < 0x10100000L
             // SSL_library_init( */
  /* * ); *1/ */
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

  /* { */
  /*   sockfd,  host
   *   SSL *s = SSL_new(SSL_CTX_new(TLS_client_method())); */
  /*   SSL_set_read_ahead(s, 1); */
  /*   SSL_set_mode(s, SSL_MODE_AUTO_RETRY); */
  /*   SSL_set_fd(s, sockfd); */
  /*   SSL_set_tlsext_host_name(s, host); */
  /*   SSL_connect(s); */
  /* printf("Connected to %s with %s encryption\n", host, SSL_get_cipher(s));
   */
  /* return s; */
  /* } */

  SSL_set_read_ahead(ssl, 1);
  SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
  SSL_set_fd(ssl, sockfd);
  SSL_set_tlsext_host_name(ssl, host);
  if (0 < SSL_connect(ssl)) {
    printf("Connected to %s with %s encryption\n", host, SSL_get_cipher(ssl));
  } else {
    goto fail;
  }

  return ssl;
fail:
  fprintf(stderr, "init failed at line %d\n", __LINE__);
  return NULL;
}

int main(int argc, char *argv[])
{
  SSL *s = init_sock("smtp.gmail.com", 465);

  char recvbuf[4096] = {'\0'};
  char enc_cmd[4096] = {'\0'};

  char *cmd = "EHLO smtp.gmail.com\r\n";
  SSL_write(s, cmd, strlen(cmd));
  SSL_read(s, recvbuf, 4096 - 1);
  puts(recvbuf);

  /* ---------------------------- */
  cmd = "AUTH LOGIN\r\n";
  SSL_write(s, cmd, strlen(cmd));
  bzero(recvbuf, 4096);
  SSL_read(s, recvbuf, 4096 - 1);
  puts(recvbuf);

  /* -------------------------------- */
  bzero(recvbuf, 4096);
  cmd         = "t400.linux@gmail.com";
  int out_len = EVP_EncodeBlock((unsigned char *)enc_cmd,
                                (const unsigned char *)cmd, strlen(cmd));
  SSL_write(s, enc_cmd, out_len);
  SSL_read(s, recvbuf, 4096 - 1);
  puts(recvbuf);

  /* ---------------------------------------- */
  bzero(recvbuf, 4096);
  cmd = "\r\n";
  SSL_write(s, cmd, strlen(cmd));
  SSL_read(s, recvbuf, 4096 - 1);
  puts(recvbuf);
  /* ----------------------------------------------- */
  bzero(recvbuf, 4096);
  bzero(enc_cmd, 4096);
  cmd     = "Cragger2011";
  out_len = EVP_EncodeBlock((unsigned char *)enc_cmd,
                            (const unsigned char *)cmd, strlen(cmd));
  SSL_write(s, enc_cmd, out_len);
  cmd = "\r\n";
  SSL_write(s, cmd, strlen(cmd));
  SSL_read(s, recvbuf, 4096 - 1);
  puts(recvbuf);
  /* ----------------------------------------------------- */

  cmd = "MAIL FROM:<t400.linux@gmail.com>\r\n";
  SSL_write(s, cmd, strlen(cmd));

  bzero(recvbuf, 4096);
  SSL_read(s, recvbuf, 4096 - 1);
  puts(recvbuf);
  /* ----------------------------------------------- */
  cmd = "RCPT TO:<t400.linux@gmail.com>\r\n";
  SSL_write(s, cmd, strlen(cmd));
  bzero(recvbuf, 4096);
  SSL_read(s, recvbuf, 4096 - 1);
  puts(recvbuf);
  /* ----------------------------------------------------------- */

  cmd = "DATA\r\n";
  SSL_write(s, cmd, strlen(cmd));
  bzero(recvbuf, 4096);
  SSL_read(s, recvbuf, 4096 - 1);
  puts(recvbuf);
  /* ------------------------------------------------ */

  cmd = "MIME-Version: 1.0\r\n";
  SSL_write(s, cmd, strlen(cmd));

  /* ------------------------------------------------------- */

  cmd = "Content-Type:multipart/"
        "mixed;boundary=\"977d81ff9d852ab2a0cad646f8058349\"\r\n";
  SSL_write(s, cmd, strlen(cmd));
  cmd = "Subject: Test Mail\r\n";
  SSL_write(s, cmd, strlen(cmd));
  cmd = "\r\n";
  SSL_write(s, cmd, strlen(cmd));
  cmd = "--977d81ff9d852ab2a0cad646f8058349\r\n";
  SSL_write(s, cmd, strlen(cmd));
  cmd = "Content-Type: text/plain; charset=\"utf-8\"\r\n";
  SSL_write(s, cmd, strlen(cmd));
  cmd = "Content-Transfer-Encoding: quoted-printable\r\n";
  SSL_write(s, cmd, strlen(cmd));
  cmd = "Hi Me,=0A=0AThis is an empty file.\r\n";
  SSL_write(s, cmd, strlen(cmd));
  cmd = "--977d81ff9d852ab2a0cad646f8058349\r\n";
  SSL_write(s, cmd, strlen(cmd));
  cmd = "Content-Type: text/plain\r\n";
  SSL_write(s, cmd, strlen(cmd));
  /* ----------------------------------------------- */
#if 0
  cmd = "Content-Type:multipart/form-data, boundary=xxxxxxxxx";
  SSL_write(s, cmd, strlen(cmd));
  cmd = "--xxxxxxxxx";
  SSL_write(s, cmd, strlen(cmd));
  cmd = "Content-Disposition: form-data; name=\"uploadfile\"; "
        "filename=\"km.txt\"\r\n";
  SSL_write(s, cmd, strlen(cmd));
  cmd = "Content-Type: text/plain";
  SSL_write(s, cmd, strlen(cmd));
#endif
  /* ------------------------------------------------------- */

  cmd = "Content-Transfer-Encoding: base64\r\n";
  SSL_write(s, cmd, strlen(cmd));
#if 0
  cmd = "Content-Disposition: "
        "attachment;filename=\"foaie_parcurs_B-151-VGT_mai_2022_Alex_Bora."
        "xlsx\"\r\n";
  SSL_write(s, cmd, strlen(cmd));
  cmd = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
  SSL_write(s, cmd, strlen(cmd));
#endif
  /* ----------------------------------------------------------- */
#if 0
  struct stat filestat;
  FILE *f = fopen("foaie_parcurs_B-151-VGT_mai_2022_Alex_Bora.xlsx", "r");
  int fd = open("km", O_RDONLY);
  fstat(fd, &filestat);
  char *data = mmap(NULL, filestat.st_size, PROT_READ, MAP_SHARED, fd, 0);
  out_len = EVP_EncodeBlock(enc_cmd, data, filestat.st_size);
  SSL_write(s, enc_cmd, out_len);
#endif
  cmd = "Content-Disposition:attachment;filename=\"km.txt\"\r\n";
  SSL_write(s, cmd, strlen(cmd));
  upload(s, "km.txt");
  /* FILE *f = fopen("km", "r"); */
  /* char  buf[4096]; */
  /* int   n = 0; */
  /* while (4096 == (n = fread(&buf, sizeof(*buf), 6, f))) */
  /*   ; */
  /* out_len = EVP_EncodeBlock(enc_cmd, buf, n); */
  /* SSL_write(s, enc_cmd, out_len); */
  cmd = "\r\n";
  SSL_write(s, cmd, strlen(cmd));
#if 0
  while (fgets(FileBuffer, sizeof(FileBuffer), MailFilePtr)) {
    sprintf(buf, "%s", FileBuffer);
    buf[strlen(buf) - 1] = 0;
    SSL_write(s, buf, strlen(buf));
    memset(FileBuffer, 0, sizeof(FileBuffer));
    memset(buf, 0, sizeof(buf));
  }

  sprintf(buf, "\r\n");
  SSL_write(s, buf, strlen(buf));
#endif
  /* --------------------------------------------------------------- */
  cmd = "U2FtcGxlIFRleHQu\r\n";
  SSL_write(s, cmd, strlen(cmd));
  cmd = "\r\n--977d81ff9d852ab2a0cad646f8058349--\r\n";
  SSL_write(s, cmd, strlen(cmd));
  /* ------------------------------------------------------------------- */
  cmd = "\r\n.\r\n";
  SSL_write(s, cmd, strlen(cmd));
  cmd = "QUIT\r\n";
  SSL_write(s, cmd, strlen(cmd));

  bzero(recvbuf, 4096);
  SSL_read(s, recvbuf, 4096 - 1);
  puts(recvbuf);

  /* ------------------------------------- */

  /* SSL_CTX_free(ctx); */
  /* shutdown(fd, SHUT_RDWR); */
  /* SSL_shutdown(s); */
  return 0;
}

#if 0
iResult = connect(sock, (struct sockaddr *)&sin, sizeof(sin));

  bzero(recvbuf, 4096);
  iResult = recv(sock, recvbuf, 4096 - 1, 0);

  cmd = "EHLO smtp.gmail.com\r\n";
  iResult = send(sock, cmd, strlen(cmd), 0);

  bzero(recvbuf, 4096);
  iResult = recv(sock, recvbuf, 4096 - 1, 0);

  cmd = "STARTTLS\r\n";
  iResult = send(sock, cmd, strlen(cmd), 0);

  bzero(recvbuf, 4096);
  iResult = recv(sock, recvbuf, 4096 - 1, 0);

  SSL_CTX *ctx = SSL_CTX_new(SSLv23_client_method());

  SSL *ssl = SSL_new(ctx);
  SSL_set_fd(ssl, sock);
  iResult = SSL_connect(ssl);

  cmd = "EHLO smtp.gmail.com\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));

  bzero(recvbuf, 4096);
  SSL_read(ssl, recvbuf, 4096 - 1);

  cmd = "AUTH LOGIN\r\n";
  SSL_write(ssl, cmd, strlen(cmd));

  bzero(recvbuf, 4096);
  SSL_read(ssl, recvbuf, 4096 - 1);

  cmd = "t400.linux@gmail.com";
  EVP_EncodeBlock((unsigned char *)enc_cmd, (const unsigned char *)cmd,
                  strlen(cmd));
  iResult = SSL_write(ssl, enc_cmd, out_len);

  cmd = "\r\n";
  SSL_write(ssl, cmd, strlen(cmd));

  bzero(recvbuf, 4096);
  iResult = SSL_read(ssl, recvbuf, 4096 - 1);

  cmd = "Cragger2011";
  out_len = strlen(cmd);
  EVP_EncodeBlock((unsigned char *)enc_cmd, (const unsigned char *)cmd,
                  out_len);
  iResult = SSL_write(ssl, enc_cmd, out_len);

  cmd = "\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));

  bzero(recvbuf, 4096);
  iResult = SSL_read(ssl, recvbuf, 4096 - 1);

  cmd = "MAIL FROM: t400.linux@gmail.com\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));

  bzero(recvbuf, 4096);
  iResult = SSL_read(ssl, recvbuf, 4096 - 1);

  cmd = "RCPT TO: t400.linux@gmail.com\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));

  bzero(recvbuf, 4096);
  iResult = SSL_read(ssl, recvbuf, 4096 - 1);

  cmd = "DATA\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));

  bzero(recvbuf, 4096);
  iResult = SSL_read(ssl, recvbuf, 4096 - 1);

  cmd = "MIME-Version: 1.0\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));

  cmd = "Content-Type:multipart/"
        "mixed;boundary=\"977d81ff9d852ab2a0cad646f8058349\"\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));

  cmd = "Subject: Test Mail\r\n";

  cmd = "--977d81ff9d852ab2a0cad646f8058349\r\n";
  cmd = "Content-Type: text/plain; charset=\"utf-8\"\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));

  cmd = "Content-Transfer-Encoding: quoted-printable\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));

  cmd = "Hi Me,=0A=0AThis is an empty file.=0A=0ARegards,=0A<ME>=0A=0A---- "
        "=0ASent using Guerrillamail.com =0ABlock or report abuse : "
        "https://www.guerrillamail.com//abuse/"
        "?a=3DUVJzDA8SW6Q1mwa14nUTcwfCX9ne0dhd=0A\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));
  //
  cmd = "--977d81ff9d852ab2a0cad646f8058349\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));

  cmd = "Content-Type: text/plain\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));
  //
  cmd = "Content-Transfer-Encoding: base64\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));
  if (iResult <= 0) {
    printf("SSL_write failed\n");
    ERR_print_errors_fp(stderr);
    return -1;
  }
  //
  cmd = "Content-Disposition: attachment; filename=\"km\"\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));
  if (iResult <= 0) {
    printf("SSL_write failed\n");
    ERR_print_errors_fp(stderr);
    return -1;
  }
  //
  cmd = "U2FtcGxlIFRleHQu\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));
  if (iResult <= 0) {
    printf("SSL_write failed\n");
    ERR_print_errors_fp(stderr);
    return -1;
  }
  //
  cmd = "\r\n--977d81ff9d852ab2a0cad646f8058349--\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));
  if (iResult <= 0) {
    printf("SSL_write failed\n");
    ERR_print_errors_fp(stderr);
    return -1;
  }
  //
  cmd = "\r\n.\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));
  if (iResult <= 0) {
    printf("SSL_write failed\n");
    ERR_print_errors_fp(stderr);
    return -1;
  }
  bzero(recvbuf, 4096);
  iResult = SSL_read(ssl, recvbuf, 4096 - 1);
  if (iResult <= 0) {
    printf("SSL_read failed: %d\n", errno);
    ERR_print_errors_fp(stderr);
    return -1;
  }
  printf("Byte(s) received: %d\n", iResult);
  printf("%s\n", recvbuf);
  //
  cmd = "QUIT\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));
  if (iResult <= 0) {
    printf("SSL_write failed\n");
    ERR_print_errors_fp(stderr);
    return -1;
  }
  bzero(recvbuf, 4096);
  iResult = SSL_read(ssl, recvbuf, 4096 - 1);
  if (iResult <= 0) {
    printf("SSL_read failed: %d\n", errno);
    ERR_print_errors_fp(stderr);
    return -1;
  }
  printf("Byte(s) received: %d\n", iResult);
  printf("%s\n", recvbuf);
  //
  SSL_CTX_free(ctx);
  printf("SSL closed!\n");
  iResult = SSL_shutdown(ssl);
  if (iResult == 0) {
    printf("SSL shutdown in progress...\n");
  }
  iResult = SSL_shutdown(ssl);
  if (iResult == 1) {
    printf("SSL shutdown succeeded\n");
  }
  if (iResult == -1) {
    printf("SSL shutdown failed!\n");
  }
  //
  iResult = shutdown(sock, SHUT_RDWR);
  if (iResult == -1) {
    printf("shutdown failed: %d\n", errno);
    // return -1;
  }
  printf("shutdown succeeded\n");
  iResult = close(sock);
  if (iResult < 0) {
    printf("Error occurred while closing socket\n");
    return -1;
  }
  //
  return 0;
}
#endif
