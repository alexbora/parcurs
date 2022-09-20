/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : mask
 * @created     : Marţi Sep 20, 2022 19:36:35 EEST
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

unsigned xx(unsigned x)
{
  unsigned mask = -(unsigned)(x > 5);
  x &= (~mask) | (2 & mask);
  return x;
}

int main(void)
{
  return 0;
}
