/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test2
 * @created     : Sâmbătă Oct 01, 2022 18:37:34 EEST
 */

#include <stdio.h>
#include <stdlib.h>

#if DEBUG_MODE
#define DEBUG printf
#else
#define DEBUG                                                                  \
  while (0)                                                                    \
  printf
#endif

int main(int argc, char *argv[])
{
  DEBUG("%d\n", __LINE__);
  return 0;
}
