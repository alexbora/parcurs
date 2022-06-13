/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : sterge10
 * @created     : Miercuri Apr 27, 2022 18:20:48 EEST
 */

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
#include <time.h>

#define ONE_DAY (long)(60 * 60 * 24)

static const char *mths = "ian feb mar apr mai iun iul aug sep oct noi dec";
static char longdate[128], *luna;
static unsigned dayz;
static struct tm TM, tmx[32];

static inline char *literal_mon(const int month) {
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

int is_leap3(const int year) {
  unsigned y = year + 16000;
  return (y % 100) ? !(y % 4) : !(y % 16);
}

int last_day_of_mon(int year, int mon) {
  return mon != 2 ? ((mon ^ (mon >> 3))) | 30 : is_leap3(year) ? 29 : 28;
}

static int now() {
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
  tmx[0] = tm;
  return 1;
}

static int then(char **argv) {
  char *m = strstr(mths, argv[1]);
  struct tm tm2 = {50, 50, 12, 1, (int)((m - mths) / 4), 2000 + atoi(argv[2])};
  mktime(&tm2);
  sprintf(longdate, "%02d.%02d.%d", tm2.tm_mday, tm2.tm_mon + 1, tm2.tm_year);

  TM = tm2;
  tmx[0] = tm2;
  return 1;
}

static int cmdl(int argc, char **argv) {
  if (argc > 2)
    return then(argv);
  return now();
}

static void globals() {
  luna = literal_mon(TM.tm_mon);
  /* dayz = days_in_month(TM.tm_mon + 1, TM.tm_year); */
  dayz = last_day_of_mon(TM.tm_year, TM.tm_mon + 1);
}

__attribute__((noreturn)) static void usage() {
  puts("Usage: <mon> <year> <km>");
  exit(0);
}

int days_from_civil(int y, unsigned m, unsigned d) {
  y -= m <= 2;
  const int era = (y >= 0 ? y : y - 399) / 400;
  const unsigned yoe = (y - era * 400); // [0, 399]
  const unsigned doy =
      (153 * (m > 2 ? m - 3 : m + 9) + 2) / 5 + d - 1;        // [0, 365]
  const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy; // [0, 146096]
  return era * 146097 + doe - 719468;
}

static inline unsigned weekday_from_days(unsigned z) { return (z + 4) % 7; }

int main(int argc, char **argv) {
  if (argc > 1 && (*argv[1] == 'h' || strcmp(argv[1], "-h") == 0 ||
                   strcmp(argv[1], "--h") == 0))
    usage();

  cmdl(argc, argv);

  globals();

  printf("current: %s\t last month: %s\t days of last mo: %d\n", longdate, luna,
         dayz);

  int arr[32], arr2[32];

  printf("wday: %d\n", weekday_from_days(time(0) / ONE_DAY));

  time_t ti = time(0);
  int r = ti / ONE_DAY;

  int civil = days_from_civil(2022, 5, 6);

  for (unsigned i = 0; i < 4; i++) {
    printf("wi: %d\n", weekday_from_days(civil + i));
    printf("i: %d\n", weekday_from_days(r++));
  }
  for (unsigned i = 0; i < 7; i++) {
    TM.tm_mday++;
    mktime(&TM);
    tmx[i] = TM;
    printf("wday: %d %s\n", tmx[i].tm_wday, asctime(&tmx[i]));
    arr[i] = tmx[i].tm_wday == 6 ? 0 : tmx[i].tm_wday;
    arr2[i] = tmx[i].tm_wday % 6;
    printf("w: %d %s\n", arr2[i], asctime(&tmx[i]));
  }

  int mm = 9;
  int mx = ((mm ^ (mm >> 3)));
  printf("mx %d\n", mx);

  char *x;

  return 0;
}
