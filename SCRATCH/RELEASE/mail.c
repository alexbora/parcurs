#include "main.h"

#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <openssl/evp.h>
#include <openssl/ssl3.h>
#include <pthread.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_iovec_t.h>
#include <sys/fcntl.h>
#include <sys/socket.h> /* socket, connect */
#include <sys/wait.h>
#include <unistd.h>

#define VECTORIZE 0
#ifdef VECTORIZE
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#endif

/* #define TURBO 0 */
/* #ifdef TURBO */
/* #include "turbob64.h" */
/* #endif */

inline size_t next_pow2(size_t n)
{
  return n < 2 ? 1 : (~(size_t){0} >> __builtin_clzll(n - 1)) + 1;
}

#define BUF          4096u
#define WRITE(b)     write_ssl(s, b)
#define WRITE_ENC(b) write_base64(s, b)
#define UPLOAD(b)    upload(s, b)
#define READ         read_ssl2(s)
#define NEW_LINE     "\r\n"

_NOPLT _FLATTEN static inline int upload_v(SSL *s, const char *const filename)
{
  FILE *fp = fopen(filename, "rb");
  if (UNLIKELY(!fp)) {
    PRINT_("no attachment\n");
    return -1;
  }
  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  rewind(fp);
  fclose(fp);
  fp = NULL;

  size_t        size_io = (sizeof(unsigned char) * size);
  unsigned char buffer[size_io];
  memset(buffer, '\0', sizeof(buffer));

  struct iovec io[64000 / 8] = {buffer, 8};

  int f = open(filename, O_RDONLY);

  /* fread(io.iov_base, 1, size, f); */
  for (int i = 0; i < 64000 / 8; i++) {
    readv(f, io[i].iov_base, 64000 / 8);
  }
  char *b = malloc(64000 + 8);
  int   j = 0;
  for (int i = 0; i < (64000 / 8); i++) {
    memcpy(b + j, io[i].iov_base, 8);
    /* j += 1; */
  }

  /* unsigned char out_buffer[(sizeof(unsigned char) * size) * 2]; */
  const size_t len = 4 * ((size_io + 2) / 3);
#ifndef __STDC_NO_VLA__
  alignas(16) unsigned char out_buffer[(len + 16) & 0xffffffffffff0000];
#else
  unsigned char *out_buffer = calloc(1, len);
#endif
  memset(out_buffer, '\0', sizeof(buffer));
  printf("%ld %ld\n", size, io[0].iov_len);

  const int out_len =
      EVP_EncodeBlock(out_buffer, io[0].iov_base, strlen(io[0].iov_base));
  return SSL_write(s, out_buffer, out_len);

  /* memset(buffer, '\0', sizeof(buffer)); */
  /* memset(out_buffer, '\0', sizeof(buffer)); */
}

static inline int upload(SSL *s, const char *const filename)
{
#ifdef VECTORIZE
  return upload_v(s, filename);
#else

  FILE *fp = fopen(filename, "rb");
  if (!fp) {
    PRINT_("no attachment\n");
    return -1;
  }
  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  rewind(fp);

  unsigned char buffer[sizeof(unsigned char) * size];
  memset(buffer, '\0', sizeof(buffer));

  fread(buffer, 1, size, fp);
  fclose(fp);
  fp = NULL;

  /* unsigned char out_buffer[(sizeof(unsigned char) * size) * 2]; */
  const size_t  len = 4 * ((sizeof(unsigned char) * size + 2) / 3);
#ifndef __STDC_NO_VLA__
  unsigned char out_buffer[len];
#else
  unsigned char *out_buffer = malloc(len);
#endif
  memset(out_buffer, '\0', sizeof(buffer));

  const int out_len = EVP_EncodeBlock(out_buffer, buffer, size);
  return SSL_write(s, out_buffer, out_len);

  /* memset(buffer, '\0', sizeof(buffer)); */
  /* memset(out_buffer, '\0', sizeof(buffer)); */
#endif
}

static inline void write_ssl(SSL *const restrict s, const char *txt)
{
  const void *buf = (const void *)txt;
  const int   n   = (const int)strlen(txt);
  SSL_write(s, buf, n);
}

static inline int write_base64(SSL *const restrict s, const void *txt)
{
  unsigned char enc_cmd[128] = {'\0'};
  const int     out_len =
      EVP_EncodeBlock((unsigned char *)enc_cmd, txt, (const int)strlen(txt));
  return SSL_write(s, enc_cmd, out_len);
}

static inline void read_ssl2(SSL *restrict const s)
{
  unsigned char recvbuf[BUF] = {'\0'};
  /* *recvbuf = '\0'; */
  /* SSL_peek(s, recvbuf, BUF - 1); */
  SSL_read(s, recvbuf, BUF - 1);
  /* puts(recvbuf); */
}

static inline int read_ssl(SSL *s, char *buf)
{
  *buf = '\0';
  return SSL_read(s, buf, BUF - 1);
}

static SSL *init_sock(const char *host, const int port)
{
  struct sockaddr_in sa = {
      .sin_family = AF_INET,
      .sin_port   = htons(port),
#define h_addr h_addr_list[0]
      .sin_addr.s_addr = *(long *)((gethostbyname(host))->h_addr),
#undef h_addr
  };

  int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (0 > connect(sockfd, (const struct sockaddr *)&sa,
                  sizeof(struct sockaddr_in))) {
    PRINT_("Sock not connected\n");
    return NULL;
  }
  /* Openssl */
  /* ------------------------ */
  SSL *const s = SSL_new(SSL_CTX_new(TLS_client_method()));
  SSL_set_fd(s, sockfd);

  SSL_connect(s);

#if defined LOG_VERBOSE || LOG
  fprintf(
      stderr,
      "--- Connected using OpenSSL with %s\n--- Cipher name: %s\n--- Cipher "
      "version: %s\n",
      SSL_get_cipher(s), SSL_get_cipher_name(s), SSL_get_cipher_version(s));
#endif
  return s;
}

void mail_me(void)
{
  while (cond == 0)
    pthread_cond_wait(&c1, &m1);

  SSL *const restrict s = init_sock("smtp.gmail.com", 465);

  WRITE("EHLO smtp.gmail.com\r\n");
  READ;

  WRITE("AUTH LOGIN\r\n");
  READ;

  WRITE_ENC("t400.linux@gmail.com");
  WRITE(NEW_LINE);
  READ;

  /* int f = open("pass", O_RDONLY); */
  {
    char x[32];
    if (!read(open("pass_2", O_RDONLY), x, 21))
      PRINT_("fisier parola negasit\n");
    WRITE_ENC(x);
    memset(&x, 'x', 32);
  }

  /* WRITE_ENC("cvdb beak ovwl rece"); */
  READ;

  WRITE(NEW_LINE);
  READ;

  WRITE("MAIL FROM:<t400.linux@gmail.com>\r\n");
  READ;

  WRITE("RCPT TO:<t400.linux@gmail.com>\r\n");
  READ;
  WRITE("RCPT TO:<alexbora@gmail.com>\r\n");
  READ;
  /* WRITE("RCPT TO:<alexandru.bora@renault-trucks.com>\r\n"); */
  /* READ; */
  // WRITE("RCPT TO:<alin.muresan@renault-trucks.com>\r\n");
  // READ;

  WRITE("DATA\r\n");
  READ;

  WRITE("MIME-Version: 1.0\r\n");

  WRITE("Content-Type:multipart/"
        "mixed;boundary=\"977d81ff9d852ab2a0cad646f8058349\"\r\n");

  char subject[128] = {[0 ... 127] = '\0'};
  memcpy(subject, "Subject:", 8u);

  // char *p = attachment;
  // while (*p++)
  //;
  // p -= 5;
  //*p = '\0';

  // attachment[strlen(attachment) - 5] = '\0';
  // attachment -= 5;

  memcpy(subject + 8, attachment, strlen(attachment) - 5);

  WRITE(subject);

  WRITE(NEW_LINE);

  WRITE("--977d81ff9d852ab2a0cad646f8058349\r\n");

  WRITE(
      "Content-Type: "
      "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet\r\n");

  WRITE("Content-Transfer-Encoding: base64\r\n");

  char attach[128] = {[0 ... 127] = '\0'};
  sprintf(attach,
          "Content-Disposition: attachment; "
          "filename=\"%s\"\r\n\r\n",
          attachment);

  WRITE(attach);

  UPLOAD(attachment);

  WRITE(NEW_LINE);

  WRITE("U2FtcGxlIFRleHQu\r\n");
  /* WRITE("U2FtcGxlIFRleHQuNEW_LINE"); */

  WRITE("NEW_LINE--977d81ff9d852ab2a0cad646f8058349--\r\n");

  WRITE("\r\n.\r\n");

  WRITE("QUIT\r\n");

  SSL_shutdown(s);

  PRINT_("Mail sent... OK\n");
  /* write(2, "Mail sent.\n", 11); */
}
#if 0
int main(int argc, char *argv[]) {

  char *attachment = "foaie_parcurs_B-151-VGT_mai_2022_Alex_Bora.xlsx";
  mail_me(attachment);
  return 0;
}
#endif
