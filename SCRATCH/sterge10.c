/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : sterge10
 * @created     : Miercuri Apr 27, 2022 17:50:52 EEST
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int mon = 4, year = 2022;

int main()
{

  struct tm ti = {59, 59, 12, 28, mon, year, 0, 0, 0, 0, NULL};
  mktime(&ti);

  printf("mday %d mon %d wday %d year %d\n", ti.tm_mday, ti.tm_mon, ti.tm_wday,
         ti.tm_year);
  return 0;
}
