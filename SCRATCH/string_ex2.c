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
#include <sys/uio.h>
#include <time.h>
#include <unistd.h>

__pure __const __attribute__((malloc)) static char* fetch(
    ssize_t* restrict const len, const int year) {
  struct addrinfo hints = {.ai_family = AF_INET,
                           .ai_socktype = SOCK_STREAM,
                           .ai_protocol = IPPROTO_TCP},
                  *res = NULL;
  int err = 0, line = 0;
  char* buf = malloc(1024);
  if (buf == 0) {
    err = *buf;
    line = __LINE__;
    /* return buf; */
    goto exit;
  }

  const char* restrict const host =
      "us-central1-romanian-bank-holidays.cloudfunctions.net";
  int x = getaddrinfo(host, "80", &hints, &res);
  if (0 != x) {
    line = __LINE__;
    err = x;
    goto exit;
  }

  int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (sockfd < 0) {
    err = sockfd;
    line = __LINE__;
    goto exit;
  }

  x = connect(sockfd, res->ai_addr, res->ai_addrlen);
  if (x != 0) {
    err = x;
    line = __LINE__;
    goto exit;
  }

  char header1[256] = {'\0'};
  const int len_header =
      sprintf(header1,
              "GET /romanian_bank_holidays/?year=%d HTTP/1.1\r\nHost: "
              "%s\r\n\r\n",
              year, host);

  /* char foo[1024] = {'\0'}; */
  /* struct iovec iov[2] = {{&header1[0], strlen(header1)}, {&foo[0], 1024}};
   */
  /* ssize_t sentx = writev(sockfd, &iov[0], 1); */
  /* if (sentx == -1) { */
  /*   err = sentx; */
  /*   goto exit; */
  /* } */
  /* int receivedx = readv(sockfd, &iov[1], 1); */
  /* memcpy(buf, foo, 1024); */

  ssize_t sent = send(sockfd, header1, (size_t)len_header, 0);
  if (sent <= 0) {
    err = (int)sent;
    line = __LINE__;
    goto exit;
  }

  /* write(sockfd, "GET /\r\n", strlen("GET /\r\n"));  // write(fd, char[]*,
   * len); */

  ssize_t received = recv(sockfd, buf, 4 * 1024, 0);
  if (received < 1) {
    err = (int)received;
    line = __LINE__;
    goto exit;
  }

  /* char foo[1024]; */
  /* struct iovec* reading = &(struct iovec){&foo[0], 1024}; */
  /* int received = readv(sockfd, reading, 1); */
  /* memcpy(buf, foo, 1024); */

  /* char response[1024]; */
  /* ssize_t total, received = 0, bytes = 0; */
  /* memset(response, 0, strlen(response)); */
  /* total = sizeof(buf) - 1; */
  /* do { */
  /*   bytes = read(sockfd, response + received, total - received); */
  /*   if (bytes < 0) { */
  /*     err = bytes; */
  /*     goto exit; */
  /*   } */
  /*   if (bytes == 0) break; */
  /*   received += bytes; */
  /* } while (received < total); */
  /* strcpy(buf, response); */
  shutdown(sockfd, SHUT_RDWR);
  close(sockfd);

  /* char* p; */
  /* while (received--) { */
  /*   if (buf[received] == '[') p = &buf[received]; */
  /* } */
  /* puts(p); */

  for (ssize_t i = 0; i < received; i++) {
    if (buf[i] == '[') {
      *len = received - i;
      /* *len = (ssize_t)strlen(&buf[i]); */
      return &buf[i];  // return buf + i;
    }
    /* *len = (ssize_t)strlen(&buf[i]); */
  }
exit:
  fprintf(stderr, "ERROR: line %d, [%d] %s\n", line, err, gai_strerror(err));
  return NULL;
}

__unused static void parse_buf_bun(char* in, int len) {
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
/* static struct H2 h2[32]; */

static char **tmp1, **tmp2;
static int* y;
static struct H2* parse_buf(const char in[static restrict 1], ssize_t len) {
  struct H2* out = calloc(32, sizeof(*out));
  const char* p = in;
  int i = 0;
  while (len--) {
    p = strstr(p, "date");
    if (!p) break;
    /* memcpy(tmp1[i], p + 7, 2); */
    /* memcpy(tmp2[i], p + 10, 2); */
    /* h2[i].day = atoi(p + 7); */
    /* h2[i].month = atoi(p + 10); */
    /* h_ptr->day = atoi(p + 7); */
    /* (h_ptr->day) = atoi(p + 7); */
    /* (h_ptr + i)->day = atoi(p + 7); */
    (out + i)->day = atoi(p + 7);
    (out + i)->month = atoi(p + 10);
    /* memcpy((x + i)->day, p + 7, 2); */
    /* memcpy((x + i)->month, p + 10, 2); */
    /* printf("%.2s.%.2s\n", p + 7, p + 10); */
    p++;
    i++;
  }
  *y = i;
  return out;
}

__pure static void display2DArrayUnknownSize(int* arr, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      fprintf(stderr, "%d ", *(arr + (i * cols) + j));
    }
    fprintf(stderr, "\n");
  }
}
#include <stdbool.h>
__pure static inline bool vacation(int* arr, int rows, int cols) {
  if (rows != (*(arr + 4) * rows)) return false;
  for (unsigned i = 0; i < 4; i++) {
    if (*(arr + (4 * rows) + i) == cols) return true;
  }
  return false;
}

int main() {
#ifdef LOG
  FILE* log_file = fopen("log_file", "w++");
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
  if (!in) return 0;
  /* struct H2 h3[1014]; */
  /* struct H2* h_ptr = h3; */
  /* parse_buf_bun(in, strlen(in)); */
  y = malloc(sizeof(int));
  struct H2* res = parse_buf(in, received);
  for (int i = 0; i < *y; i++) {
    /* printf("%s\t", h[i].day); */
    /* printf("%s\n", h[i].month); */
    /* printf("%s\t", tmp1[i]); */
    /* printf("%s\n", tmp2[i]); */
    fprintf(stderr, "%d\t%d\n", (res + i)->day, (res + i)->month);
    /* printf("%d.%d\n", h2[i].day, h2[i].month); */
  }
  free(res);
  /* fprintf(stderr, "h2: %d\n", h_ptr->day); */
  /* fprintf(stderr, "h2: %d\n", h3[10].day); */

#ifdef LOG
  fclose(log_file);
#endif
  /* return 0; */
#define MONTH 13
#define DAY 4

  int row[MONTH][DAY] = {{0}};
  /* int i, j; */
  /* memset(row, 0, sizeof(row)); */
  /* for (i = 0; i < 12; i++) { */
  /*   for (j = 0; j < 4; j++) { */
  /*     row[i][j] = 0; */
  /*   } */
  /* } */
#if 0
  for (i = 0; i < strlen(in); i++) {
    if (i == atoi(strstr(in, "date") + 10)) {
      row[i][j] = atoi(strstr(in, "date") + 7);
      /* for (j = 0; j < DAY; j++) { */
      /*   row[i][j] = atoi(strstr(in, "date") + 7); */
      /* } */
    }
  }
#endif
  const char* x = (const char*)in;
  int k = 0;
  do {
    x = strstr(x, "date");
    if (!x) break;
    int m = atoi(x + 10);
    int n = atoi(x + 7);
    /* printf("n: %d\n", n); */
    while (row[m][k]) k++;
    row[m][k] = n;
    k = 0;
    /* k = (k > 3) ? 0 : k; */
  } while (x++);
  /* free((void*)x); */
  /* i = j = 0; */
  /* char* p = (char*)in; */
  /* while (p++) { */
  /*   p = strstr(p, "date"); */
  /*   if (!p) break; */
  /*   for (i = 0; i < MONTH; i++) { */
  /*     if (i == atoi(p + 10)) { */
  /*       row[i][j] = atoi(p + 7); */
  /*     } */
  /*   } */
  /* } */

  /* for (i = 0; i < MONTH; i++) { */
  /*   for (j = 0; j < DAY; j++) { */
  /*     printf("arr[%d] [%d] = %d \n", i, j, row[i][j]); */
  /*   } */
  /* } */

  display2DArrayUnknownSize(&row[0][0], MONTH, DAY);
  fprintf(stderr, "%c\n", "nd"[vacation(&row[0][0], 12, 26)]);

  return 0;
}
