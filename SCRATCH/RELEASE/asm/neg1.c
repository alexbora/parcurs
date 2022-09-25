/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : neg1
 * @created     : Sâmbătă Sep 24, 2022 21:15:04 EEST
 */

#include <stdlib.h>

int neg(int x)
{
  if (x > 5)
    x = 5;
  return x;
}

int main(int argc, char *argv[])
{
  int y = neg(7);
  return 0;
}
