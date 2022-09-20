/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : main4
 * @created     : Sâmbătă Iul 16, 2022 15:42:19 EEST
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

  char *src      = "test";
  char  dest[16] = {'a', 'b', 'c', 'd'};

  for (int i = 0; i < 4; ++i) {
    dest[i] ^= *(src + i);
  }

  printf("%d\n", *dest);
  printf("%d\n", *(dest + 1));
  puts(src);

  return 0;
}
