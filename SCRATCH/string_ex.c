/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : string
 * @created     : Luni Mar 07, 2022 15:11:29 EET
 */

#include <assert.h>
#include <netdb.h>
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_ssize_t.h>
#include <sys/socket.h> /* socket, connect */
#include <time.h>
#include <unistd.h>

static const char* fetch(ssize_t* len, int year) {
  struct addrinfo hints = {.ai_family = AF_UNSPEC, .ai_socktype = SOCK_STREAM},
                  *res;
  int err = 1;
  char* buf = malloc(1024);
  if (!buf) {
    err = *buf;
    goto exit;
  }

  const char* host = "us-central1-romanian-bank-holidays.cloudfunctions.net";
  int x = getaddrinfo(host, "80", &hints, &res);
  if (0 != x) {
    err = x;
    goto exit;
  }

  int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (sockfd < 0) {
    err = sockfd;
    goto exit;
  }

  x = connect(sockfd, res->ai_addr, res->ai_addrlen);
  if (x != 0) {
    err = x;
    goto exit;
  }

  char header1[256];
  sprintf(header1,
          "GET /romanian_bank_holidays/?year=%d HTTP/1.1\r\nHost: "
          "%s\r\n\r\n",
          year, host);

  ssize_t sent = send(sockfd, header1, strlen(header1), 0);
  if (sent <= 0) {
    err = (int)sent;
    goto exit;
  }

  /* write(sockfd, "GET /\r\n", strlen("GET /\r\n"));  // write(fd, char[]*,
   * len); */
  ssize_t received = recv(sockfd, buf, 2056, 0);
  if (received < 1) {
    err = (int)received;
    goto exit;
  }

  shutdown(sockfd, SHUT_RDWR);
  close(sockfd);
  for (ssize_t i = 0; i < received; i++) {
    if (buf[i] == '[') {
      *len = received - i;
      return &buf[i];
    }
    /* *len = (ssize_t)strlen(&buf[i]); */
  }
exit:
  fprintf(stderr, "%s\n", gai_strerror(err));
  return NULL;
}

__attribute__((unused)) static void parse_buf_bun(char* in, int len) {
  char* p = in;
  while (len--) {
    p = strstr(p, "date");
    if (!p) break;
    printf("%.2s %.2s\n", p + 7, p + 10);
    p++;
  }
}

/* static struct H { char month[2], day[2]; } h[1014]; */
struct H2 {
  int day, month;
};
static struct H2 h2[32];

static char **tmp1, **tmp2;

static void parse_buf(const char* in, ssize_t len, struct H2* h_ptr) {
  struct H2* out = calloc(32, sizeof(*out));

  const char* p = in;
  int i = 0;
  while (len--) {
    p = strstr(p, "date");
    if (!p) break;
    memcpy(tmp1[i], p + 7, 2);
    memcpy(tmp2[i], p + 10, 2);
    h2[i].day = atoi(p + 7);
    h2[i].month = atoi(p + 10);
    /* h_ptr->day = atoi(p + 7); */
    /* (h_ptr->day) = atoi(p + 7); */
    (h_ptr + i)->day = atoi(p + 7);
    (out + i)->day = atoi(p + 7);
    (out + i)->month = atoi(p + 10);
    printf("%d = %d\n", (out + i)->day, (out + i)->month);
    /* memcpy((x + i)->day, p + 7, 2); */
    /* memcpy((x + i)->month, p + 10, 2); */
    /* printf("%.2s.%.2s\n", p + 7, p + 10); */
    p++;
    i++;
  }
}

int main() {
#ifdef LOG
  FILE* log_file = fopen("log", "w++");
#undef stderr
#define stderr log_file
#endif

  tmp1 = malloc(1024);
  for (unsigned i = 0; i < 1024; i++) {
    tmp1[i] = malloc(2);
  }
  tmp2 = malloc(1024);
  for (unsigned i = 0; i < 1024; i++) {
    tmp2[i] = malloc(2);
  }

  ssize_t received = 0;
  const char* in = fetch(&received, 2050);
  struct H2 h3[1014];
  struct H2* h_ptr = h3;
  parse_buf(in, received, h_ptr);
  for (unsigned i = 0; i < 16; i++) {
    /* printf("%s\t", h[i].day); */
    /* printf("%s\n", h[i].month); */
    /* printf("%s\t", tmp1[i]); */
    /* printf("%s\n", tmp2[i]); */

    printf("%d.%d\n", h2[i].day, h2[i].month);
  }
  fprintf(stderr, "h2: %d\n", h_ptr->day);
  fprintf(stderr, "h2: %d\n", h3[10].day);

#ifdef LOG
  fclose(log_file);
#endif
  return 0;
}
