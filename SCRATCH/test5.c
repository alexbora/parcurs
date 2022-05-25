/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test5
 * @created     : Miercuri Mai 25, 2022 17:09:21 EEST
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct R {
  char *a;
};
struct W {
  struct R r;
  int      x;
};

int main(int argc, char *argv[])
{

  struct R r_arr[2] = {{"a"}, {"b"}};
  struct W w_arr[2] = {};

  memcpy(w_arr, r_arr, 2 * sizeof(struct R));

  puts(w_arr[0].r.a);
  puts(w_arr[1].r.a);

  int x = 30;
  int y = 30;
  printf("%d\n", (x ^ y) ^ (y ^ 30));

  return 0;
}
