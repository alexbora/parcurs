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
#include <sys/_types/_ucontext.h>
#endif
#include <assert.h>
#include <time.h>

static inline char *literal_mon(const int month)
{
  return &"ianuarie\0\0\0\0\0\0\0\0februari"
          "e\0\0\0"
          "\0\0\0\0martie\0\0\0\0\0\0\0\0\0\0aprilie\0\0\0\0\0\0\0\0\0mai\0"
          "\0\0\0\0"
          "\0\0\0\0\0\0\0\0iunie\0\0\0\0\0\0\0\0\0\0\0iulie\0\0\0\0\0\0\0\0"
          "\0\0\0au"
          "gust\0\0\0\0\0\0\0\0\0\0septembrie\0\0\0\0\0\0octombrie\0\0\0\0"
          "\0\0\0noi"
          "embrie\0\0\0\0\0\0\0decembrie\0\0\0\0\0\0\0"[16 * month];
}

static const char *mths = "ian feb mar apr mai iun iul aug sep oct noi dec";
static char        longdate[128], *luna;
static unsigned    dayz;
static struct tm   TM;

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

  TM = tm;
  return 1;
}

static int then(char **argv)
{
  char     *m   = strstr(mths, argv[1]);
  struct tm tm2 = {50, 50, 12, 1, (int)((m - mths) / 4), 2000 + atoi(argv[2])};
  mktime(&tm2);
  sprintf(longdate, "%02d.%02d.%d", tm2.tm_mday, tm2.tm_mon + 1, tm2.tm_year);

  TM = tm2;
  return 1;
}

static int cmdl(int argc, char **argv)
{
  if (argc > 2)
    return then(argv);
  return now();
}

static void globals()
{
  luna = literal_mon(TM.tm_mon);
  dayz = days_in_month(TM.tm_mon + 1, TM.tm_year);
}

__attribute__((noreturn)) static void usage()
{
  puts("Usage: <mon> <year> <km>");
  exit(0);
}

int main(int argc, char **argv)
{

  if (argv[1] && (strcmp(argv[1], "-h") == 0 || *argv[1] == 'h'))
    usage();

  cmdl(argc, argv);

  globals();

  puts(longdate);

  puts(luna);

  printf("%d\n", dayz);

  for (unsigned i = 0; i < 7; i++) {
    TM.tm_mday++;
    mktime(&TM);
    printf("%d\n", TM.tm_wday);
  }

  return 0;
}