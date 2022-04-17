/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : txt2
 * @created     : Duminică Apr 17, 2022 13:56:10 EEST
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  struct tm *tm = localtime(&(time_t){time(0)});
  printf("%d  %d %d\n", tm->tm_mon, tm->tm_year + 1900, tm->tm_wday);

  tm->tm_mon = 11;
  if (tm->tm_mon == 11) {
    /* tm->tm_mon--; */
    tm->tm_year--;
  }
  mktime(tm);

  printf("%d  %d %d\n", tm->tm_mon, tm->tm_year + 1900, tm->tm_wday);

  return 0;
}
