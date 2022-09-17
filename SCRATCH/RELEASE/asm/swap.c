/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : swap
 * @created     : Sâmbătă Sep 17, 2022 14:23:45 EEST
 */

#include <stdio.h>
#include <stdlib.h>

unsigned short SwapSHORT(unsigned short x)
{
  return (x >> 8) | (x << 8);
}

int main(int argc, char *argv[])
{
  printf("%d\n", SwapSHORT(1));
  return 0;
}
