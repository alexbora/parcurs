/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test3_
 * @created     : Marţi Aug 02, 2022 06:50:34 EEST
 */

#include <stdio.h>
#include <stdlib.h>

int res(const int x)
{
  if (x == 0 || x == 6)
    return 0;
  return 1;
}

int main(int argc, char *argv[])
{
  res(4);
  return 0;
}
