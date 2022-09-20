/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test1
 * @created     : Luni Aug 01, 2022 16:42:19 EEST
 */

#include <stdlib.h>

int res(int x)
{
  return x % 6;
}

int res2(int x)
{
  if (x < 7 && x > 2)
    return x;
  return 0;
}

int main(int argc, char *argv[])
{
  res(5);
  res2(3);
  return 0;
}
