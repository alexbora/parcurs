/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : sterge10
 * @created     : Miercuri Apr 27, 2022 18:20:48 EEST
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef __linux__
#include <sys/_types/_off_t.h>
#endif
#include <time.h>

static const char *mths = "ian feb mar apr mai iun iul aug sep oct noi dec";

int main(int argc, char **argv) {
  /* normal time */
  struct tm tm = *localtime(&(time_t){time(NULL)});
  /* printf("Today is           %s", asctime(&tm)); */
  printf("Today is           %s", asctime(&*localtime(&(time_t){time(NULL)})));
  char longdate[128];
  sprintf(longdate, "%02d.%02d.%d", tm.tm_mday, tm.tm_mon + 1,
          tm.tm_year + 1900);
  puts(longdate);

  /* goto previous */
  tm.tm_mon -= 1;
  /* reset to the first of month */
  tm.tm_mday = 1;
  /* adjust year to jump to previous if december */
  tm.tm_year = tm.tm_mon != 11 ? tm.tm_year : tm.tm_year - 1;
  /* tm.tm_mon -= 1; // tm_mon is now outside its normal range */
  mktime(&tm); // tm_isdst is not set to -1; today's DST status is used
  printf("1 month ago was %d - %s", tm.tm_wday, asctime(&tm));

  /* time input */
  struct tm tm2 = {50, 50, 12, 1, 3, 2022};
  mktime(&tm2);
  printf("1 month ago was %d - %s", tm2.tm_wday, asctime(&tm2));

  /* ---------------------------------------------------------- */
  if (argc > 1) {
    char *m = strstr(mths, argv[1]);
    /* int   offset = (m - mths) >> 2; */
    /* printf("%d\n", offset); */
    struct tm tm3 = {50, 50, 12, 1, (int)((m - mths) / 4), 2022};
    mktime(&tm3);
    printf("1 month ago was %d - %s", tm3.tm_wday, asctime(&tm3));
    tm = tm3;
  }

  return 0;
}
