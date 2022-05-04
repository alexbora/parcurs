/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test1
 * @created     : Miercuri Mai 04, 2022 06:05:36 EEST
 */

#include <openssl/ssl.h>
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

int main(int argc, char *argv[])
{

  data_t d1 = {f1, "test"};
  d1.fn(&d1);

  data_t d2[2] = {{f1, "1"}, {f1, "0"}};
  d2[0].fn(&d2[0]);
  d2[1].fn(&d2[1]);

  return 0;
}
