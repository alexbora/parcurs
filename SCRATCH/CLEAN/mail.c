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

static inline void upload(SSL *s, const char *filename)
{
  FILE *fp = fopen(filename, "rb");
  if (!fp)
    return;
  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  rewind(fp);

  unsigned char buffer[sizeof(unsigned char) * size];

  fread(buffer, 1, size, fp);

  unsigned char out_buffer[(sizeof(unsigned char) * size) * 2];
  int           out_len = EVP_EncodeBlock(out_buffer, buffer, size);

  SSL_write(s, out_buffer, out_len);

  fclose(fp);
  fp = NULL;
  memset(buffer, '\0', sizeof(buffer));
  memset(out_buffer, '\0', sizeof(buffer));
}

static inline void write_ssl(SSL *s, const char *txt)
{
  const void *buf = (const void *)txt;
  int         n   = (int)strlen(txt);
  SSL_write(s, buf, n);
}

static inline void write_base64(SSL *s, const void *txt)
{
  unsigned char enc_cmd[128] = {'\0'};
  int out_len = EVP_EncodeBlock((unsigned char *)enc_cmd, txt, strlen(txt));
  SSL_write(s, enc_cmd, out_len);
}

static inline void read_ssl2(SSL *s)
{
  char recvbuf[BUF] = {'\0'};
  SSL_read(s, recvbuf, BUF - 1);
  puts(recvbuf);
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
  if (0 >
      connect(sockfd, (const struct sockaddr *)&sa, sizeof(struct sockaddr_in)))
    return NULL;

  /* Openssl */
  /* ------------------------ */
  SSL *s = SSL_new(SSL_CTX_new(TLS_client_method()));
  SSL_set_fd(s, sockfd);
  SSL_connect(s);

  return s;
}

int main(int argc, char *argv[])
{
  char *attachment = "foaie_parcurs_B-151-VGT_mai_2022_Alex_Bora.xlsx";
  SSL  *s          = init_sock("smtp.gmail.com", 465);

  char recvbuf[BUF] = {'\0'};
  char enc_cmd[BUF] = {'\0'};

  char *cmd = "EHLO smtp.gmail.com\r\n";

  write_ssl(s, "EHLO smtp.gmail.com\r\n");
  read_ssl2(s);

  /* ---------------------------- */
  write_ssl(s, "AUTH LOGIN\r\n");
  read_ssl2(s);

  /* -------------------------------- */
  write_base64(s, "t400.linux@gmail.com");

  /* ---------------------------------------- */
  /* bzero(recvbuf, 4096); */
  cmd = "\r\n";
  /* SSL_write(s, cmd, strlen(cmd)); */
  /* SSL_read(s, recvbuf, 4096 - 1); */
  /* puts(recvbuf); */

  write_ssl(s, cmd);
  read_ssl2(s);
  /* ----------------------------------------------- */
  cmd = "cvdb beak ovwl rece";
  write_base64(s, cmd);
  read_ssl2(s);
  /* -------------------------- */
  cmd = "\r\n";
  write_ssl(s, cmd);
  read_ssl2(s);
  /* ----------------------------------------------------- */

  cmd = "MAIL FROM:<t400.linux@gmail.com>\r\n";
  /* SSL_write(s, cmd, strlen(cmd)); */

  /* bzero(recvbuf, 4096); */
  /* SSL_read(s, recvbuf, 4096 - 1); */
  /* puts(recvbuf); */

  write_ssl(s, cmd);
  read_ssl2(s);
  /* ----------------------------------------------- */
  cmd = "RCPT TO:<t400.linux@gmail.com>\r\n";
  SSL_write(s, cmd, strlen(cmd));
  bzero(recvbuf, 4096);
  SSL_read(s, recvbuf, 4096 - 1);
  /* puts(recvbuf); */
  /* ----------------------------------------------------------- */
  cmd = "DATA\r\n";
  /* SSL_write(s, cmd, strlen(cmd)); */
  /* bzero(recvbuf, 4096); */
  /* SSL_read(s, recvbuf, 4096 - 1); */
  /* puts(recvbuf); */
  write_ssl(s, cmd);
  read_ssl2(s);
  /* aici nu modifica */
  /* ------------------------------------------------ */
  cmd = "MIME-Version: 1.0\r\n";
  SSL_write(s, cmd, strlen(cmd));
  /* ------------------------------------------------------- */
  cmd = "Content-Type:multipart/"
        "mixed;boundary=\"977d81ff9d852ab2a0cad646f8058349\"\r\n";
  SSL_write(s, cmd, strlen(cmd));

  char subject[128];
  sprintf(subject, "Subject: %s", attachment);
  /* cmd = "Subject: Test Mail\r\n"; */
  SSL_write(s, subject, strlen(subject));

  cmd = "\r\n";
  SSL_write(s, cmd, strlen(cmd));
  cmd = "--977d81ff9d852ab2a0cad646f8058349\r\n";
  SSL_write(s, cmd, strlen(cmd));

  /* cmd = "--977d81ff9d852ab2a0cad646f8058349\r\n"; */
  /* SSL_write(s, cmd, strlen(cmd)); */
  cmd = "Content-Type: "
        "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet\r\n";
  SSL_write(s, cmd, strlen(cmd));
  cmd = "Content-Transfer-Encoding: base64\r\n";
  SSL_write(s, cmd, strlen(cmd));

  cmd = "Content-Disposition: attachment; "
        "filename=\"foaie_parcurs_B-151-VGT_mai_2022_Alex_Bora.xlsx\"\r\n\r\n";
  SSL_write(s, cmd, strlen(cmd));
  upload(s, "foaie_parcurs_B-151-VGT_mai_2022_Alex_Bora.xlsx");

  cmd = "\r\n";
  SSL_write(s, cmd, strlen(cmd));
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

  SSL_shutdown(s);
  return 0;
}
