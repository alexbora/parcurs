/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test7
 * @created     : Sâmbătă Mai 28, 2022 13:34:18 EEST
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void f1(void *p)
{
  printf("1: %s\n", (char *)p);
}

void f2(void *p)
{
  printf("2: %s\n", (char *)p);
}

struct Work {
  void *data;
  void (*fn)(void *);
};

struct Method {
  union {
    void (*f1)(void *in);
    void (*f2)(void *in);
  };
};

struct Process {
  struct Route  *r;
  lxw_worksheet *ws;
  uint32_t       row;
  uint16_t       col;
  double         parcursi;
  lxw_format    *format;
};

int main(int argc, char *argv[])
{

  struct Work w1 = {"test", f1};
  w1.fn(w1.data);

  long array[] = {&&foo - &&foo, &&bar - &&foo};

  long arr[] = {1, 1, 1, 0, 1, 0};

  unsigned i = 0;
  while (i++ < 5) {
    goto *(&&foo + array[arr[i]]);
  foo:
    f1(w1.data);
  bar:
    f2(w1.data);
  }
  return 0;
}
