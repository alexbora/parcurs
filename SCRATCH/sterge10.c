/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : sterge10
 * @created     : Miercuri Apr 27, 2022 18:20:48 EEST
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_off_t.h>
#include <time.h>

char mths[] = "ian feb mar apr mai iun iul aug sep oct noi dec";

int main(int argc, char *argv[argc + 1])
{
  /* normal time */
  struct tm tm = *localtime(&(time_t){time(NULL)});
  /* printf("Today is           %s", asctime(&tm)); */
  printf("Today is           %s", asctime(&*localtime(&(time_t){time(NULL)})));
  tm.tm_mon -= 1; // go previous
  tm.tm_mday = 1; // reset to 1st
  mktime(&tm);    // tm_isdst is not set to -1; today's DST status is used
  printf("1 month ago was %d - %s", tm.tm_wday, asctime(&tm));

  /* time input */
  struct tm tm2 = {50, 50, 12, 1, 3, 2022};
  mktime(&tm2);
  printf("1 month ago was %d - %s", tm2.tm_wday, asctime(&tm2));

  if (argc > 1) {
    char *m = strstr(mths, argv[1]);
    /* int   offset = (m - mths) >> 2; */
    /* printf("%d\n", offset); */
    struct tm tm = {0, 0, -1, 1, (m - mths) / 4, 2022};
    mktime(&tm);
    printf("1 month ago was %d - %s", tm.tm_wday, asctime(&tm));
  }

  return 0;
}
