/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : sockmail
 * @created     : Sâmbătă Iun 04, 2022 15:00:39 EEST
 */

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

int main(int argc, char *argv[])
{

  int    sock;
  char  *host, *cmd, *ip;
  char  *enc_cmd;
  char   recvbuf[4096];
  int    iResult;
  size_t out_len;

  struct hostent    *hent = gethostbyname(host);
  struct sockaddr_in sin;

  host = "smtp.gmail.com";

  printf("Attempting to connect to %s...\n", host);
  //
  if (hent == NULL) {
    printf("gethostbyname failed: %d\n", errno);
    return -1;
  }
  printf("gethostbyname succeeded!\n");
  ip = inet_ntoa(*(struct in_addr *)hent->h_addr_list[0]);
  printf("Host IP: %s\n", ip);
  //
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    printf("socket failed: %d\n", errno);
    return -1;
  }
  printf("socket succeeded!\n");
  //
  bzero(&sin, sizeof(sin));
  sin.sin_family      = AF_INET;
  sin.sin_port        = htons(465);
  sin.sin_addr.s_addr = inet_addr(ip);
  //
  iResult = connect(sock, (struct sockaddr *)&sin, sizeof(sin));
  if (iResult < 0) {
    printf("connect failed: %d\n", errno);
    return -1;
  }
  printf("connect succeeded\n");
  //
  bzero(recvbuf, 4096);
  iResult = recv(sock, recvbuf, 4096 - 1, 0);
  if (iResult <= 0) {
    printf("recv failed: %d\n", errno);
    return -1;
  }
  printf("Byte(s) received: %d\n", iResult);
  printf("%s\n", recvbuf);
  //
  cmd     = "EHLO smtp.gmail.com\r\n";
  iResult = send(sock, cmd, strlen(cmd), 0);
  if (iResult <= 0) {
    printf("send failed: %d\n", errno);
    return -1;
  }
  printf("Byte(s) sent: %d\n", iResult);
  //
  bzero(recvbuf, 4096);
  iResult = recv(sock, recvbuf, 4096 - 1, 0);
  if (iResult <= 0) {
    printf("recv failed: %d\n", errno);
    return -1;
  }
  printf("Byte(s) received: %d\n", iResult);
  printf("%s\n", recvbuf);
  //
  cmd     = "STARTTLS\r\n";
  iResult = send(sock, cmd, strlen(cmd), 0);
  if (iResult <= 0) {
    printf("send failed: %d\n", errno);
    return -1;
  }
  printf("Byte(s) sent: %d\n", iResult);
  //
  bzero(recvbuf, 4096);
  iResult = recv(sock, recvbuf, 4096 - 1, 0);
  if (iResult <= 0) {
    printf("recv failed: %d\n", errno);
    return -1;
  }
  printf("Byte(s) received: %d\n", iResult);
  printf("%s\n", recvbuf);
  //
  // OpenSLL region
  /* OpenSSL_add_all_algorithms(); */
  /* ERR_load_BIO_strings(); */
  /* ERR_load_crypto_strings(); */
  /* SSL_load_error_strings(); */
  if (SSL_library_init() < 0) {
    printf("Could not initialise SSL library!\n");
    /* ERR_print_errors_fp(stderr); */
    return -1;
  }
  printf("SSL Library initialised\n");
  SSL_CTX *ctx = SSL_CTX_new(SSLv23_client_method());
  if (ctx == NULL) {
    printf("ctx failed: %d\n", errno);
    /* ERR_print_errors_fp(stderr); */
    return -1;
  }
  printf("ctx done!\n");
  SSL *ssl = SSL_new(ctx);
  if (ssl == NULL) {
    printf("ssl failed: %d\n", errno);
    /* ERR_print_errors_fp(stderr); */
    return -1;
  }
  printf("ssl done!\n");
  SSL_set_fd(ssl, sock);
  iResult = SSL_connect(ssl);
  if (iResult < 0) {
    printf("SSL connect failed!\n");
    ERR_print_errors_fp(stderr);
    return -1;
  }
  printf("SSL connect succeeded!\n");
  cmd     = "EHLO smtp.gmail.com\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));
  if (iResult <= 0) {
    printf("SSL_write failed: %d\n", errno);
    ERR_print_errors_fp(stderr);
    return -1;
  }
  printf("Byte(s) sent: %d\n", iResult);
  //
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
  cmd     = "AUTH LOGIN\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));
  if (iResult <= 0) {
    printf("SSL_write faile\n");
    ERR_print_errors_fp(stderr);
    return -1;
  }
  printf("Byte(s) sent: %d\n", iResult);
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
  cmd     = "t400.linux@gmail.com";
  enc_cmd = EVP_EncodeBlock(enc_cmd, cmd, strlen(cmd));
  iResult = SSL_write(ssl, enc_cmd, out_len);
  if (iResult <= 0) {
    printf("SSL_write failed\n");
    ERR_print_errors_fp(stderr);
    return -1;
  }
  printf("Byte(s) sent: %d\n", iResult);
  cmd = "\r\n";
  SSL_write(ssl, cmd, strlen(cmd));
  if (iResult <= 0) {
    printf("SSL_write failed\n");
    ERR_print_errors_fp(stderr);
    return -1;
  }
  printf("Byte(s) sent: %d\n", iResult);
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
  cmd     = "Cragger2011";
  out_len = strlen(cmd);
  EVP_EncodeBlock(enc_cmd, cmd, out_len);
  iResult = SSL_write(ssl, enc_cmd, out_len);
  if (iResult <= 0) {
    printf("SSL_write failed\n");
    ERR_print_errors_fp(stderr);
    return -1;
  }
  printf("Byte(s) sent: %d\n", iResult);
  cmd     = "\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));
  if (iResult <= 0) {
    printf("SSL_write failed\n");
    ERR_print_errors_fp(stderr);
    return -1;
  }
  printf("Byte(s) sent: %d\n", iResult);
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
  cmd     = "MAIL FROM: t400.linux@gmail.com\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));
  if (iResult <= 0) {
    printf("SSL_write failed\n");
    ERR_print_errors_fp(stderr);
    return -1;
  }
  printf("Byte(s) sent: %d\n", iResult);
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
  cmd     = "RCPT TO: t400.linux@gmail.com\r\n";
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
  cmd     = "DATA\r\n";
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
  cmd     = "MIME-Version: 1.0\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));
  if (iResult <= 0) {
    printf("SSL_write failed\n");
    ERR_print_errors_fp(stderr);
    return -1;
  }
  //
  cmd     = "Content-Type:multipart/"
            "mixed;boundary=\"977d81ff9d852ab2a0cad646f8058349\"\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));
  if (iResult <= 0) {
    printf("SSL_write failed\n");
    ERR_print_errors_fp(stderr);
    return -1;
  }
  //
  cmd     = "Subject: Test Mail\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));
  if (iResult <= 0) {
    printf("SSL_write failed\n");
    ERR_print_errors_fp(stderr);
    return -1;
  }
  //
  cmd     = "--977d81ff9d852ab2a0cad646f8058349\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));
  if (iResult <= 0) {
    printf("SSL_write failed\n");
    ERR_print_errors_fp(stderr);
    return -1;
  }
  //
  cmd     = "Content-Type: text/plain; charset=\"utf-8\"\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));
  if (iResult <= 0) {
    printf("SSL_write failed\n");
    ERR_print_errors_fp(stderr);
    return -1;
  }
  //
  cmd     = "Content-Transfer-Encoding: quoted-printable\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));
  if (iResult <= 0) {
    printf("SSL_write failed\n");
    ERR_print_errors_fp(stderr);
    return -1;
  }
  //
  cmd     = "Hi Me,=0A=0AThis is an empty file.=0A=0ARegards,=0A<ME>=0A=0A---- "
            "=0ASent using Guerrillamail.com =0ABlock or report abuse : "
            "https://www.guerrillamail.com//abuse/"
            "?a=3DUVJzDA8SW6Q1mwa14nUTcwfCX9ne0dhd=0A\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));
  if (iResult <= 0) {
    printf("SSL_write failed\n");
    ERR_print_errors_fp(stderr);
    return -1;
  }
  //
  cmd     = "--977d81ff9d852ab2a0cad646f8058349\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));
  if (iResult <= 0) {
    printf("SSL_write failed\n");
    ERR_print_errors_fp(stderr);
    return -1;
  }
  //
  cmd     = "Content-Type: text/plain\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));
  if (iResult <= 0) {
    printf("SSL_write failed\n");
    ERR_print_errors_fp(stderr);
    return -1;
  }
  //
  cmd     = "Content-Transfer-Encoding: base64\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));
  if (iResult <= 0) {
    printf("SSL_write failed\n");
    ERR_print_errors_fp(stderr);
    return -1;
  }
  //
  cmd     = "Content-Disposition: attachment; filename=\"km\"\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));
  if (iResult <= 0) {
    printf("SSL_write failed\n");
    ERR_print_errors_fp(stderr);
    return -1;
  }
  //
  cmd     = "U2FtcGxlIFRleHQu\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));
  if (iResult <= 0) {
    printf("SSL_write failed\n");
    ERR_print_errors_fp(stderr);
    return -1;
  }
  //
  cmd     = "\r\n--977d81ff9d852ab2a0cad646f8058349--\r\n";
  iResult = SSL_write(ssl, cmd, strlen(cmd));
  if (iResult <= 0) {
    printf("SSL_write failed\n");
    ERR_print_errors_fp(stderr);
    return -1;
  }
  //
  cmd     = "\r\n.\r\n";
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
  cmd     = "QUIT\r\n";
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
