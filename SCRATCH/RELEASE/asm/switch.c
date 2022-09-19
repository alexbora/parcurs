/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : switch
 * @created     : Duminică Sep 18, 2022 20:41:32 EEST
 */

#include <stdio.h>
#include <stdlib.h>

static int sw(int x)
{
  int f = 0;
  switch (x) {
    case 0:
    case 1:
    default:
      if (!x)
        return 1;
      f = 3;
  }

  return f;
}

int main()
{
  int f = sw(6);
  printf("%d\n", f);
  return 0;
}
