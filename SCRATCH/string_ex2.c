/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : string
 * @created     : Luni Mar 07, 2022 15:11:29 EET
 */
#include <arpa/inet.h>
#include <assert.h>
#include <limits.h>
#include <netdb.h>
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_size_t.h>
#include <sys/_types/_ssize_t.h>
#include <sys/ioctl.h>  /* ioctl()  */
#include <sys/socket.h> /* socket, connect */
#include <sys/uio.h>
#include <time.h>
#include <unistd.h>

#ifdef LOG
static FILE *log_file;
#undef stderr
#define stderr log_file
#endif

#define CONNECT_VERBOSE (1u << 0)

#define NORETURN __attribute__((__noreturn__))
__attribute__((format(printf, 4, 5))) NORETURN void
BUG_(const char *file, int line, const char *func, const char *fmt, ...) {
  fprintf(stderr, "%s - %d - %s\n", file, line, func);
  exit(1);
};
#define BUG(...) BUG_(__FILE__, __LINE__, __FUNC__, __VA_ARGS__)

__pure static inline bool internet(int flag) {
  char const *host = "test";
  if (flag & CONNECT_VERBOSE)
    fprintf(stderr, ("Looking up %s ... \n"), host);

  int                sockfd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in addr   = {
        AF_INET, .sin_port = htons(80), {inet_addr("142.250.185.206")}};

  if (flag & CONNECT_VERBOSE)
    fprintf(stderr, ("done.\nConnecting to %s (port %s) ... \n"), "se->s_name",
            "se->s_port");

  if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) != 0)
    return false;
  close(sockfd);
  return true;
}

__pure __const __attribute__((malloc)) static char *
fetch(ssize_t *restrict const len, const int year) {
  struct addrinfo hints = {.ai_family   = AF_INET,
                           .ai_socktype = SOCK_STREAM,
                           .ai_protocol = IPPROTO_TCP,
                           .ai_flags    = AI_PASSIVE},
                  *res  = NULL;
  int err = 0, line = 0;
  char *const restrict buf = malloc(1024);
  if (buf == 0) {
    err  = *buf;
    line = __LINE__;
    /* return buf; */
    goto exit;
  }

  const char *restrict const host =
      "us-central1-romanian-bank-holidays.cloudfunctions.net";
  int x = getaddrinfo(host, "80", &hints, &res);
  if (x == EAI_SYSTEM) {
    fprintf(stderr, "looking up %s => %s\n", host, strerror(x));
    return NULL;
  } else if (0 != x) {
    line = __LINE__;
    err  = x;
    goto exit;
  }
  struct servent *se = getservent();
  printf("PORT: %d\n", se->s_port);
  printf("proto: %s\n", se->s_proto);
  printf("name: %s\n", se->s_name);
  /* for (struct addrinfo* rp = res; rp != NULL; rp = rp->ai_next) { */
  /*   int sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
   */
  /*   if (sfd == -1) continue; */

  /*   if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1) break; /1*
   * Success *1/ */

  /*   close(sfd); */
  /* } */
  int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (sockfd < 0) {
    err  = sockfd;
    line = __LINE__;
    goto exit;
  }

  x = connect(sockfd, res->ai_addr, res->ai_addrlen);
  if (x) {
    err  = x;
    line = __LINE__;
    goto exit;
  }
  puts("\x1b[32mConnected.\x1b[0m\n");

  char      header1[256] = {'\0'};
  const int len_header =
      sprintf(header1,
              "GET /romanian_bank_holidays/?year=%d HTTP/1.1\r\nHost: "
              "%s\r\n\r\n",
              year, host);

  /* char foo[1024] = {'\0'}; */
  /* struct iovec iov[2] = {{&header1[0], strlen(header1)}, {&foo[0],
   * 1024}};
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
    err  = (int)sent;
    line = __LINE__;
    goto exit;
  }

  /* write(sockfd, "GET /\r\n", strlen("GET /\r\n"));  // write(fd,
   * char[]*, len); */

  ssize_t received = recv(sockfd, buf, 4 * 1024, 0);
  if (received < 1) {
    err  = (int)received;
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
  freeaddrinfo(res);
  res = NULL;
  shutdown(sockfd, SHUT_RDWR);
  close(sockfd);

  /* char* p; */
  /* while (received--) { */
  /*   if (buf[received] == '[') p = &buf[received]; */
  /* } */
  /* puts(p); */
  /* printf("received: %ld\n", received); */
  /* printf("strlen: %ld\n", strlen(buf)); */

  /* puts(&buf[received - 1000]); */
  /* printf("%c\n", buf[received - 1000]); */

  char *ss = (char *)buf;
  while (ss++)
    if (*ss == ']') {
      *--ss = '\0';
      break;
    }
  received -= 14;

  while (received--)
    if (buf[received] == '[')
      return &buf[received];

  printf("buf: %c\n", buf[received - 14]);

  char *t = (char *)buf;
  while (t++) {
    /* received--; */
    if (*t == '[')
      return t;
  }
  /* puts(t); */

  for (ssize_t register i = 0; i < received; i++) {
    if (buf[i] == '[') {
      *len = received - i;
      /* *len = (ssize_t)strlen(&buf[i]); */
      return &buf[i]; // return buf + i;
    }
    /* *len = (ssize_t)strlen(&buf[i]); */
  }
#define SAY(a, b, c) fprintf(stderr, a, b, c);
#define SAY2(a)      fprintf(stderr, "%d %s\n", __LINE__, a);
exit:
  SAY("ERROR %.*s", line, gai_strerror(err));
  SAY2("");
  fprintf(stderr, "ERROR: line %d, [%d] %s\n", line, err, gai_strerror(err));
  freeaddrinfo(res);
  res = NULL;
  return NULL;
}

__unused static void parse_buf_bun(char *in, int len) {
  char *p = in;
  while (len--) {
    p = strstr(p, "date");
    if (!p)
      break;
    printf("%.2s %.2s\n", p + 7, p + 10);
    p++;
  }
}

/* static struct H { char month[2], day[2]; } h[1014]; */
struct H2 {
  int day, month;
};
/* static struct H2 h2[32]; */

static char     **tmp1, **tmp2;
static int       *y;
static struct H2 *parse_buf(const char in[static restrict 1], ssize_t len) {
  struct H2  *out = calloc(32, sizeof(*out));
  const char *p   = in;
  int         i   = 0;
  while (len--) {
    p = strstr(p, "date");
    if (!p)
      break;
    /* memcpy(tmp1[i], p + 7, 2); */
    /* memcpy(tmp2[i], p + 10, 2); */
    /* h2[i].day = atoi(p + 7); */
    /* h2[i].month = atoi(p + 10); */
    /* h_ptr->day = atoi(p + 7); */
    /* (h_ptr->day) = atoi(p + 7); */
    /* (h_ptr + i)->day = atoi(p + 7); */
    (out + i)->day   = atoi(p + 7);
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

__pure static void display2DArrayUnknownSize(const int *const restrict arr,
                                             const uint_fast8_t rows,
                                             const uint_fast8_t cols) {
  for (uint_fast8_t i = 0; i < rows; i++) {
    for (uint_fast8_t j = 0; j < cols; j++) {
      fprintf(stderr, "%d ", *(arr + (i * cols) + j));
    }
    fprintf(stderr, "\n");
  }
}
#include <stdbool.h>
__pure static inline bool vacation(const int *const restrict arr,
                                   const int rows, const int cols) {
  if (rows != (*(arr + 4) * rows))
    return false;
  for (unsigned i = 0; i < 4; i++) {
    if (*(arr + (4 * rows) + i) == cols)
      return true;
  }
  return false;
}

static char *color(char *out, int flag) {
  switch (flag) {
    case 1:
    case 2:
      out = "no out";
      break;
  }
  return out;
}

static inline int no_date(struct tm *tm) {
  return (tm->tm_hour & tm->tm_min);
}

int main() {
  /* int er = 11; */
  /* FILE *test = fopen("er", "w++"); */
  // write(test, er, 2);

#ifdef LOG
  log_file = fopen("log_file", "w++");
#endif

  tmp1 = malloc(1024);
  for (unsigned i = 0; i < 1024; i++) {
    tmp1[i] = malloc(2);
  }
  tmp2 = malloc(1024);
  for (unsigned i = 0; i < 1024; i++) {
    tmp2[i] = malloc(2);
  }

  ssize_t     received = 0;
  const char *in       = fetch(&received, 2050);
  if (!in)
    return 0;
  /* struct H2 h3[1014]; */
  /* struct H2* h_ptr = h3; */
  /* parse_buf_bun(in, strlen(in)); */
  y              = malloc(sizeof(int));
  struct H2 *res = parse_buf(in, received);
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

  /* return 0; */
#define MONTH 13
#define DAY   4

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
  const char *x = (const char *)in;
  int         k = 0;
  do {
    x = strstr(x, "date");
    if (!x)
      break;
    int m = atoi(x + 10);
    int n = atoi(x + 7);
    /* printf("n: %d\n", n); */
    while (row[m][k])
      k++;
    row[m][k] = n;
    k ^= k;
    /* k = (k > 3) ? 0 : k; */
  } while (x++);
  x = (void *)0;
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
  fprintf(stderr, "is it vacation? %c\n", "nd"[vacation(&row[0][0], 3, 1)]);
  printf("internet: %s\n", &"nu\0da, este net"[3 * internet(CONNECT_VERBOSE)]);
  /* printf("internet: %s\n", "nu\0da, este" + (3 * internet())); */
/* note: use array indexing to silence this warning */
#ifdef LOG
  if (log_file)
    fclose(log_file);
#endif
  if (!internet(CONNECT_VERBOSE)) {
    puts("really,  no net...\n");
    return 1;
  }
  int *arr = NULL;
  int  z = __builtin_types_compatible_p(__typeof__(arr), __typeof__(&(arr)[0]));

  printf("z: %d\n", z);

#define BUILD_ASSERT_OR_ZERO(cond) (sizeof(char[1 - 2 * !(cond)]) - 1)

  printf("asseert: %d\n", (int)BUILD_ASSERT_OR_ZERO(arr == NULL));
  int w = 1;
  printf("w: %d\n", !w);

  char *ww = "test";
  printf("size of char 1: %ld\n", sizeof(char[1]) - 1);
  printf("size ww: %ld\n", sizeof(ww[0]) - 1);
  printf("size if char 0: %ld\n", sizeof(ww[0]) - 1);
  printf("size of arr: %ld\n", sizeof(arr[1] - 1));

  BUILD_ASSERT_OR_ZERO(z == 1);
  char wx = '\0';
  printf("char bit %d\n", CHAR_BIT * wx);

  int cond = 1;
  printf("cond: %d\n", !cond);
  printf("cond: %ld\n", (sizeof(char[1 - 2 * !(cond)]) - 1));
  printf("cond: %c\n", ww[1 - 2 * !(cond)]);

#define STR_(x) #x
#define STR(x)  STR_(x)

  printf("%s\n", STR(2022));
  char conc[16];
  memcpy(&conc[0], "test", 4);
  memcpy(conc + 4, STR(2023), 4);
  printf("%s\n", conc);

  char *ep = "malloc(8)";
  char *pe = "malloc(8)";

  printf("ep: %d\n", ep == pe);
  printf("%p %p\n", (void *)ep, (void *)pe);
  printf("%d\n", *ep);
  cond      = 1;
  int cond2 = dup(cond);
  printf("%d\n", cond2);

  struct Test {
    char *name;
    int   len;
  } test[] = {
#define ARR(n, l) {n, strlen(n)}
      ARR("test", ), ARR("test", ), ARR(STR(7), )
#undef ARR
  };
  printf("%s %d\n", test[0].name, test[0].len);
  printf("%s %d\n", test[1].name, test[1].len);
  printf("%s %d\n", test[2].name, test[2].len);
  /* BUG("cond2"); */

  printf("%s\n", color("no color", 0));
  struct tm t = {.tm_min = -1, .tm_hour = -1};
  printf("%d\n", no_date(&t));
  return 0;
}
