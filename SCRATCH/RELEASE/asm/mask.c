/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : mask
 * @created     : Marţi Sep 20, 2022 19:36:35 EEST
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef __STDC_WANT_LIB_EXT1__
#define __STDC_WANT_LIB_EXT1__ 1
#endif
#include <string.h>

unsigned xx(unsigned x)
{
  unsigned mask = -(unsigned)(x > 5);
  x &= (~mask) | (2 & mask);
  return x;
}

int main(void)
{
  char *buf = malloc(16);

  memset_s(buf, 16, 0, 16);
  void *(*volatile memset_volatile)(void *, int, size_t) = memset;

  char bf[247];
  memcpy(bf, "aaa", 3);
  int len = bf[0];
  printf("%d %s\n", len, bf);
  return 0;
}
