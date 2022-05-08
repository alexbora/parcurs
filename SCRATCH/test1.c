/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test1
 * @created     : Miercuri Mai 04, 2022 06:05:36 EEST
 */

#include <openssl/ssl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Data {
  void (*fn)(struct Data *in);
  char *user;
} data_t;

void f(data_t *in) { puts(in->user); }

struct ssl_async_args {
  SSL *s;
  void *buf;
  size_t num;
  enum { READFUNC, WRITEFUNC, OTHERFUNC } type;
  union {
    int (*func_read)(SSL *, void *, size_t, size_t *);
    int (*func_write)(SSL *, const void *, size_t, size_t *);
    int (*func_other)(SSL *);
  } f;
};

static int ssl_io_intern(void *vargs) {
  struct ssl_async_args *args;
  SSL *s;
  void *buf;
  size_t num;

  args = (struct ssl_async_args *)vargs;
  s = args->s;
  buf = args->buf;
  num = args->num;
  switch (args->type) {
  case READFUNC:
    /* return args->f.func_read(s, buf, num, &s->asyncrw); */
  case WRITEFUNC:
    /* return args->f.func_write(s, buf, num, &s->asyncrw); */
  case OTHERFUNC:
    return args->f.func_other(s);
  }
  return -1;
}

bool is_multiple_of_100_ex(int32_t n) {
  const uint32_t multiplier = 42949673;
  const uint32_t bound = 42949669;
  const uint32_t max_dividend = 1073741799;

  const uint32_t offset = max_dividend / 2 / 100 * 100; //  536870800

  return multiplier * (n + offset) < bound;
}

bool is_multiple_100(int year) { return year % 100 == 0; }

bool is_leap(int year) {
  return (year & (is_multiple_of_100_ex(year) ? 15 : 3)) == 0;
}

bool is_leap3(int year) {
  unsigned y = year + 16000;
  return (y & 15) ? !(y & 3) : !(y % 16);
}

int last_day_of_mon(int year, int mon) {
  return mon != 2 ? ((mon ^ (mon >> 3))) | 30 : is_leap3(year) ? 29 : 28;
}

int days_from_civil(int y, unsigned m, unsigned d) {
  y -= m <= 2;
  const int era = (y >= 0 ? y : y - 399) / 400;
  const unsigned yoe = (y - era * 400); // [0, 399]
  const unsigned doy =
      (153 * (m > 2 ? m - 3 : m + 9) + 2) / 5 + d - 1;        // [0, 365]
  const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy; // [0, 146096]
  return era * 146097 + doe - 719468;
}

unsigned weekday_from_days(int z) { return (z + 4) % 7; }

#define ONE_DAY (long)(60 * 60 * 24)

int main(int argc, char *argv[]) {

  printf("days from civil: %d %ld\n", days_from_civil(2022, 5, 6),
         time(0) / ONE_DAY);
  printf("days in mon: %d\n", last_day_of_mon(2022, 3));

  int civil = days_from_civil(2022, 5, 6);
  printf("wday: %d\n", weekday_from_days(civil - 1));
  printf("wday: %d\n", weekday_from_days(time(0) / ONE_DAY));

  for (unsigned i = 0; i < 4; i++)
    printf("wi: %d\n", weekday_from_days(civil + i));

  printf("t %d\n", (8 >> 3));
  printf("t %d\n", 8 ^ (8 >> 3));
  printf("t %d\n", 8 | 30);
  printf("tx %d\n", 2 | 1);

  data_t d1 = {f, "test"};
  d1.fn(&d1);

  data_t d2[2] = {{f, "1"}, {f, "0"}};
  d2[0].fn(&d2[0]);
  d2[1].fn(&d2[1]);

  int t = (5 - 6) >> 31;
  int t2 = ~t & 7;
  printf("%d\n", t2);

  int z = 1, y = 3;
  printf("%d\n", z ^ y);

  printf(">>>>>> %d\n", (-1 >> 31));
  printf("%d\n", 4 >> 2);

  int w = z > 1 ? 1 : y == 3 ? 0 : 0;

  printf("----- %d\n", (6 >> 2)); // 110
  printf("----- %d\n", (5 >> 2)); // 101
  printf("----- %d\n", (4 >> 2)); // 100
  printf("----- %d\n", (3 >> 2)); // 011
  printf("----- %d\n", (2 >> 2)); // 010
  printf("----- %d\n", (1 >> 2)); // 001

  printf("%d\n", (3 ^ (3 >> 3)) | 30);

  int tt = (130 - 128) >> 31;
  printf("%d\t %d\t %d\n", tt, ~tt, (~tt & 130));

  printf("%% %d %d %d\n", 6 % 6, 0 % 6, 2 % 6);
  printf("%d %d %d\n", ~(6 % 6), ~(0 % 6), ~(2 % 6));
  printf("%d\n", 6);
  int v = 5;
  int vv = (1 << 6) >> v;
  printf("vv: %d\n", vv);

  printf("FU: %d\n", 0xFFF);

  int ww = 0;
  ww |= 1 << 0;
  ww |= 1 << 1;

  printf("%d %d %d\n", ww, ww | 4, ww >> 1);

  return 0;
}
