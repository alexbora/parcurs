/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test2_
 * @created     : Luni Aug 01, 2022 19:12:09 EEST
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  printf("%u\n", UINT32_MAX / 6);
  printf("%u\n", UINT32_MAX);
  printf("%ld\n", (5 * (4294967296 / 6)) >> 32);
  return 0;
}
