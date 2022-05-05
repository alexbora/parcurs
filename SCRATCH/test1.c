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

void f(data_t *in)
{
  puts(in->user);
}

struct ssl_async_args {
  SSL   *s;
  void  *buf;
  size_t num;
  enum { READFUNC, WRITEFUNC, OTHERFUNC } type;
  union {
    int (*func_read)(SSL *, void *, size_t, size_t *);
    int (*func_write)(SSL *, const void *, size_t, size_t *);
    int (*func_other)(SSL *);
  } f;
};

static int ssl_io_intern(void *vargs)
{
  struct ssl_async_args *args;
  SSL                   *s;
  void                  *buf;
  size_t                 num;

  args = (struct ssl_async_args *)vargs;
  s    = args->s;
  buf  = args->buf;
  num  = args->num;
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

bool is_multiple_of_100_ex(int32_t n)
{
  const uint32_t multiplier   = 42949673;
  const uint32_t bound        = 42949669;
  const uint32_t max_dividend = 1073741799;

  const uint32_t offset = max_dividend / 2 / 100 * 100; //  536870800

  return multiplier * (n + offset) < bound;
}

bool is_multiple_100(int year)
{
  return year % 100 == 0;
}

bool is_leap(int year)
{
  return (year & (is_multiple_of_100_ex(year) ? 15 : 3)) == 0;
}

bool is_leap3(int year)
{
  unsigned y = year + 16000;
  return (y % 100) ? !(y % 4) : !(y % 16);
}

int last_day_of_mon(int year, int mon)
{
  return mon != 2 ? ((mon ^ (mon >> 3))) | 30 : is_leap3(year) ? 29 : 28;
}

int main(int argc, char *argv[])
{
  printf("%d\n", last_day_of_mon(2022, 3));

  printf("t %d\n", (8 >> 3));
  printf("t %d\n", 8 ^ (8 >> 3));
  printf("t %d\n", 8 | 30);
  printf("tx %d\n", 2 | 1);

  data_t d1 = {f, "test"};
  d1.fn(&d1);

  data_t d2[2] = {{f, "1"}, {f, "0"}};
  d2[0].fn(&d2[0]);
  d2[1].fn(&d2[1]);

  printf(">> %d\n", 0x7FFFFFFF);
  return 0;
}
