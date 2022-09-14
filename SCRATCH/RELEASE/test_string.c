/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test_string
 * @created     : Luni Sep 12, 2022 20:35:15 EEST
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  const char *x = "string";
  /* while (*x) { */
  /* puts(x); */
  /* x++; */
  /* } */

  do {
    puts(x++);
  } while (*x != 't');

  return 0;
}
