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
static char        longdate[128], *luna;

static inline unsigned days_in_month(const int month, const int year)
{
  if (month == 4 || month == 6 || month == 9 || month == 11)
    return 30;
  else if (month == 2)
    return (((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29
                                                                      : 28);
  return 31;
}

static int now()
{
  /* normal time */
  struct tm tm = *localtime(&(time_t){time(NULL)});
  /* printf("Today is           %s", asctime(&tm)); */
  printf("Today is           %s", asctime(&*localtime(&(time_t){time(NULL)})));
  sprintf(longdate, "%02d.%02d.%d", tm.tm_mday, tm.tm_mon + 1,
          tm.tm_year + 1900);
  /* goto previous */
  tm.tm_mon -= 1;
  /* reset to the first of month */
  tm.tm_mday = 1;
  /* adjust year to jump to previous if december */
  tm.tm_year = tm.tm_mon != 11 ? tm.tm_year : tm.tm_year - 1;
  mktime(&tm); // tm_isdst is not set to -1; today's DST status is used

  return 1;
}

static int then(char **argv)
{
  char     *m   = strstr(mths, argv[1]);
  struct tm tm2 = {50, 50, 12, 1, (int)((m - mths) / 4), 2000 + atoi(argv[2])};
  mktime(&tm2);
  sprintf(longdate, "%02d.%02d.%d", tm2.tm_mday, tm2.tm_mon + 1, tm2.tm_year);
  return 1;
}

int cmdl(int argc, char **argv)
{
  if (argc > 2)
    return then(argv);
  return now();
}

int main(int argc, char **argv)
{

  cmdl(argc, argv);

  puts(longdate);
  return 0;
}
