/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test_string
 * @created     : Luni Sep 12, 2022 20:35:15 EEST
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  /* argc          = 1; */
  const char *x = argv[1];
  /* const char *x = "strimg"; */
  /* while (*x) { */
  /* puts(x); */
  /* x++; */
  /* } */

  do {
    puts(x++);
  } while (*x != '\0');

  return 0;
}
