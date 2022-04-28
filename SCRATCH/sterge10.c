/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : sterge10
 * @created     : Miercuri Apr 27, 2022 18:20:48 EEST
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{

  struct tm tm = *localtime(&(time_t){time(NULL)});
  printf("Today is           %s", asctime(&tm));
  printf("Today is           %s", asctime(&*localtime(&(time_t){time(NULL)})));

  tm.tm_mon -= 1; // go previous
  tm.tm_mday = 1; // reset to 1st
  /* tm.tm_mon -= 1; // tm_mon is now outside its normal range */

  mktime(&tm); // tm_isdst is not set to -1; today's DST status is used

  printf("1 months ago was %s", asctime(&tm));
  printf("%d\n", tm.tm_wday);

  struct tm tm2 = {50, 50, 12, 1, *argv[1] - 1, 2022};

  mktime(&tm2);

  puts("----\n");
  printf("1 months ago was %s", asctime(&tm2));
  printf("%d\n", tm2.tm_wday);

  return 0;
}
