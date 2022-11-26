/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : rand2
 * @created     : Sâmbătă Oct 01, 2022 14:52:16 EEST
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int x = random() % 128;
  /* printf("%d\n", x); */
  return 0;
}
