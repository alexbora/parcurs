/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test1
 * @created     : Miercuri Mai 04, 2022 06:05:36 EEST
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Data {
  void (*fn)(struct Data *in);
  char *user;
} data_t;

void f1(data_t *in)
{
  puts(in->user);
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
