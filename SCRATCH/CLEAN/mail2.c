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

#define BUF 4096u

static inline void upload(SSL *s, const char *filename) {
  FILE *fp = fopen(filename, "rb");
  if (!fp) return;
  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  rewind(fp);

  unsigned char buffer[sizeof(unsigned char) * size];
  memset(buffer, '\0', sizeof(buffer));

  fread(buffer, 1, size, fp);

  /* unsigned char out_buffer[(sizeof(unsigned char) * size) * 2]; */
  size_t len = 4 * ((sizeof(unsigned char) * size + 2) / 3);
  unsigned char out_buffer[len];
  memset(out_buffer, '\0', sizeof(buffer));

  int out_len = EVP_EncodeBlock(out_buffer, buffer, size);

  SSL_write(s, out_buffer, out_len);

  fclose(fp);
  fp = NULL;
  /* memset(buffer, '\0', sizeof(buffer)); */
  /* memset(out_buffer, '\0', sizeof(buffer)); */
}

static inline void write_ssl(SSL *s, const char *txt) {
  const void *buf = (const void *)txt;
  int n = (int)strlen(txt);
  SSL_write(s, buf, n);
}

#define WRITE(b) write_ssl(s, b)
#define WRITE_ENC(b) write_base64(s, b)
#define UPLOAD(b) upload(s, b);
#define READ read_ssl2(s)
#define NEW_LINE "\r\n"

static inline void write_base64(SSL *s, const void *txt) {
  unsigned char enc_cmd[128] = {'\0'};
  int out_len = EVP_EncodeBlock((unsigned char *)enc_cmd, txt, strlen(txt));
  SSL_write(s, enc_cmd, out_len);
}

static inline void read_ssl2(SSL *s) {
  char recvbuf[BUF] = {'\0'};
  /* *recvbuf = '\0'; */
  SSL_read(s, recvbuf, BUF - 1);
  /* puts(recvbuf); */
}

static inline int read_ssl(SSL *s, char *buf) {
  *buf = '\0';
  return SSL_read(s, buf, BUF - 1);
}

static SSL *init_sock(const char *host, const int port) {
  struct sockaddr_in sa = {
      .sin_family = AF_INET,
      .sin_port = htons(port),
#define h_addr h_addr_list[0]
      .sin_addr.s_addr = *(long *)((gethostbyname(host))->h_addr),
#undef h_addr
  };

  int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (0 >
      connect(sockfd, (const struct sockaddr *)&sa, sizeof(struct sockaddr_in)))
    return NULL;

  /* Openssl */
  /* ------------------------ */
  SSL *s = SSL_new(SSL_CTX_new(TLS_client_method()));
  if (!s) puts("s");
  SSL_set_fd(s, sockfd);

  SSL_connect(s);
  printf("Connected with %s\n%s%s\n", SSL_get_cipher(s), SSL_get_cipher_name(s),
         SSL_get_cipher_version(s));
  ;
  return s;
}

int mail_me(const char *attachment) {
  SSL *s = init_sock("smtp.gmail.com", 465);

  WRITE("EHLO smtp.gmail.com\r\n");
  READ;

  WRITE("AUTH LOGIN\r\n");
  READ;

  WRITE_ENC("t400.linux@gmail.com");

  WRITE("\r\n");
  READ;

  WRITE_ENC("cvdb beak ovwl rece");
  READ;

  WRITE(NEW_LINE);
  READ;

  WRITE("MAIL FROM:<t400.linux@gmail.com>\r\n");
  READ;

  WRITE("RCPT TO:<t400.linux@gmail.com>\r\n");
  READ;

  WRITE("DATA\r\n");
  READ;

  WRITE("MIME-Version: 1.0\r\n");

  WRITE(
      "Content-Type:multipart/"
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

  char attach[128];
  sprintf(attach,
          "Content-Disposition: attachment; "
          "filename=\"%s\"\r\n\r\n",
          attachment);

  WRITE(attach);

  UPLOAD(attachment);

  WRITE(NEW_LINE);

  WRITE("U2FtcGxlIFRleHQu\r\n");

  WRITE("\r\n--977d81ff9d852ab2a0cad646f8058349--\r\n");

  WRITE("\r\n.\r\n");

  WRITE("QUIT\r\n");

  SSL_shutdown(s);

  return 0;
}
#if 0
int main(int argc, char *argv[]) {

  char *attachment = "foaie_parcurs_B-151-VGT_mai_2022_Alex_Bora.xlsx";
  mail_me(attachment);
  return 0;
}
#endif
