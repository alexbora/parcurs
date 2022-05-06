/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test2
 * @created     : Vineri Mai 06, 2022 17:21:27 EEST
 */

#include <stdio.h>
#include <stdlib.h>

void p(int y)
{
  int z = y % 6;
  printf("%d\n", z);
}

int main(int argc, char *argv[])
{
  p(*argv[1]);
  return 0;
}
