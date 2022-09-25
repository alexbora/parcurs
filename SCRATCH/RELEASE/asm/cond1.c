/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : cond1
 * @created     : Sâmbătă Sep 24, 2022 21:26:21 EEST
 */

#include <stdlib.h>

uint32_t ct_select_u32(uint32_t x, uint32_t y, uint32_t bit)
{
  uint32_t m = -(uint32_t)(bit > 4);
  return (x & m) | (y & ~m);
  /* return ((x^y)&m)^y; */
}
