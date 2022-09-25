/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : neg2
 * @created     : Sâmbătă Sep 24, 2022 21:30:16 EEST
 */

#include <stdio.h>
#include <stdlib.h>

unsigned int a(int unsigned x)
{
  unsigned mask = -(unsigned)(x > 5); // 0x00000000 or 0xFFFFFFFF
  x             = (x & ~mask) | (5 & mask);
  return x;
}

unsigned int b(int unsigned x)
{
  return x > 5 ? 5 : x;
}

unsigned int c(int unsigned x)
{
  return (unsigned[2]){x, 5}[x > 5];
}

unsigned int d(int unsigned x)
{
  x = x < 5 ? x : 5;
  return x;
}

unsigned int e(unsigned x)
{
  x <<= (32 - 5);
  x = x >> (32 - 5);
  return x;
}

int main(int argc, char *argv[])
{
  printf("%d\n", e(5));
  return 0;
}
