/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : sterge10
 * @created     : Miercuri Apr 27, 2022 18:20:48 EEST
 */

/* references: */
/* https://stackoverflow.com/questions/11227809/why-is-processing-a-sorted-array-faster-than-processing-an-unsorted-array/11227902#11227902
 */
/* http://howardhinnant.github.io/date_algorithms.html#last_day_of_month_leap_year
 */
/* https://stackoverflow.com/questions/25955425/compare-if-between-with-bitwise-operators-instead-of-logical
 */
/* https://stackoverflow.com/questions/3220163/how-to-find-leap-year-programmatically-in-c/60646967#60646967
 */
/* https://stackoverflow.com/questions/53920169/last-day-of-a-month/66430992#66430992
 */

/* https://github.com/cassioneri/calendar/blob/master/fast_eaf.cpp */

/* https://en.cppreference.com/w/c/chrono/mktime */

#include <sys/_types/_u_int32_t.h>
#define _POSIX_C_SOURCE 200112L // for setenv on gcc
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#ifndef __linux__
#include <sys/_types/_off_t.h>
#include <sys/_types/_ucontext.h>
#endif
#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <time.h>

#define ONE_DAY (time_t)(60 * 60 * 24)

static time_t ti;
static int    arr[32];

static const char *mths = "ian feb mar apr mai iun iul aug sep oct noi dec";
static char        longdate[128], *luna;
static int         dayz;
static struct tm   TM;
static int         days_past;

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
          /* "embrie\0\0\0\0\0\0\0decembrie\0\0\0\0\0\0\0"[16 * month]; */
          "embrie\0\0\0\0\0\0\0decembrie\0\0\0\0\0\0\0"[month << 4];
}

/* static inline unsigned days_in_month(const int month, const int year) */
/* { */
/*   if (month == 4 || month == 6 || month == 9 || month == 11) */
/*     return 30; */
/*   else if (month == 2) */
/*     return (((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29 */
/*                                                                       : 28);
 */
/*   return 31; */
/* } */

static inline int is_leap3(const int year)
{
  int y = year + 16000;
  return (y % 100) ? !(y % 4) : !(y % 16);
}

static inline int last_day_of_mon(int year, int mon)
{
  return mon != 2 ? ((mon ^ (mon >> 3))) | 30 : is_leap3(year) ? 29 : 28;
}

static inline int days_from_civil(int y, const int m, const int d)
{
  y -= m <= 2;
  const int era = (y >= 0 ? y : y - 399) / 400;
  const int yoe = (y - era * 400);                                 // [0, 399]
  const int doy = (153 * (m > 2 ? m - 3 : m + 9) + 2) / 5 + d - 1; // [0, 365]
  const int doe = yoe * 365 + yoe / 4 - yoe / 100 + doy; // [0, 146096]
  return era * 146097 + doe - 719468;
}

static inline int weekday_from_days(const int z)
{
  return (z + 4) % 7;
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
  /* days_past = days_from_civil(TM.tm_year + 1900, TM.tm_mon + 1, 1); */
  days_past = days_from_civil(tm.tm_year + 1900, tm.tm_mon + 1, 1);
  /* days_past = (int)(ti / ONE_DAY); */
  return 1;
}

static int then(char **argv)
{
  char     *m    = strstr(mths, argv[1]);
  int       mon  = (int)((m - mths) / 4);
  int       year = 2000 + atoi(argv[2]);
  struct tm tm2  = {.tm_sec  = 50,
                    .tm_min  = 50,
                    .tm_hour = 12,
                    .tm_mday = 1,
                    .tm_mon  = mon,
                    .tm_year = year};
  mktime(&tm2);
  sprintf(longdate, "%02d.%02d.%d", tm2.tm_mday, tm2.tm_mon + 1, tm2.tm_year);

  TM        = tm2;
  days_past = days_from_civil(year, mon + 1, 1);
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
  /* dayz = days_in_month(TM.tm_mon + 1, TM.tm_year); */
  dayz = last_day_of_mon(TM.tm_year, TM.tm_mon + 1);
  for (int i = 0; i < dayz; i++) {
    arr[i] = (weekday_from_days(days_past++));
  }
}

__attribute__((noreturn)) static void usage()
{
  puts("Usage: <mon> <year> <km>\ne.g. iun 22 80000\n");
  exit(0);
}

static int init_time(int argc, char **argv)
{
  if (argc > 1 && (*argv[1] == 'h' || strcmp(argv[1], "-h") == 0 ||
                   strcmp(argv[1], "--h") == 0))
    usage();

  setenv("TZ", "/usr/share/zoneinfo/Europe/Bucharest", 1); // POSIX-specific
  ti = time(0);

  cmdl(argc, argv);

  globals();

  return 0;
}

int main(int argc, char *argv[])
{
  init_time(argc, argv);
  printf("current: %s\t last month: %s\t days of last mo: %d\n", longdate, luna,
         dayz);

  printf("past: %d\n", days_past);
  printf("%d %d %s", arr[0], TM.tm_wday, asctime(&TM));
  /* printf("%d\n", arr[1]); */
  /* printf("%d\n", arr[2]); */
  /* printf("%d\n", arr[3]); */
  /* printf("%d\n", arr[4]); */
  /* printf("%d\n", arr[5]); */
  /* printf("%d\n", arr[6]); */

  /* x |= 1 << 0; */
  /* x |= 1 << 1; */

  return 0;
}
