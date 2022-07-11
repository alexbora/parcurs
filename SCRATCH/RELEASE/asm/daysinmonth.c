/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : daysinmonth
 * @created     : Luni Iul 11, 2022 09:15:06 EEST
 */

#include <stdio.h>
#include <stdlib.h>

extern int daysinmonth(int);

int main(int argc, char *argv[])
{
  printf("%d\n", daysinmonth(atoi(argv[1])));
  return 0;
}
