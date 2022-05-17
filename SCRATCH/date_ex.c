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

/* WORKS ONLY FOR DATES AFERR 1970-01-01, FOR OBVIOUS REASONS */
/* INPUT WORKS ONLY FOR YEARS AFTER 2000 */
/* NO ERROR CHECKING, WATCH THE INPUT */

#ifndef __linux__
#include <sys/_types/_u_int32_t.h>
#endif
#define _POSIX_C_SOURCE 200112L // for setenv on gcc
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define ONE_DAY (time_t)(60 * 60 * 24)

#define __isleap(year)                                                         \
  ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0))

/* typedef struct lxw_struct lxw_struct; */
/* extern struct Route       route; */
/* void                      write(lxw_struct *p, struct Route *r){}; */

/* typedef struct lxw_worksheet lxw_worksheet; */
/* typedef struct lxw_format    lxw_format; */
/* typedef void (*fx)(const struct Route *, lxw_worksheet *, unsigned *, */
/*                    const unsigned, double *, lxw_format *); */

/* static const char *mths = "ian feb mar apr mai iun iul aug sep oct noi
 * dec";
 */
static time_t    global_time;
static struct tm TM;

static char longdate[128], *luna;
static int  dayz_in_mon;
static int  days_past;

static int arr[32];

static struct Route {
  char  *r;
  double km;
  char  *obs;
} route_[128];

struct Work {
  char          longdate[128];
  char         *luna;
  int           dayz_in_mon;
  int           arr[32];
  struct Route *routes;
  void (*f)(void);
};

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

static inline unsigned long is_multiple_of_100(unsigned n)
{
  const unsigned long multiplier   = 42949673;
  const unsigned long bound        = 42949669;
  const unsigned long max_dividend = 1073741799;
  const unsigned long offset       = max_dividend / 2 / 100 * 100; //  536870800
  return multiplier * (n + offset) < bound;
}

static inline int is_leap(int y)
{
  // Originally, the ternary expression was similar to
  //   is_multiple_of_100(y) ? y % 16 == 0 : y % 4 == 0;
  // and Ulrich Drepper suggested the following twist.
  return (y & (is_multiple_of_100(y) ? 15 : 3)) == 0;
}

static inline int is_leap3(const int year)
{
  int y = year + 16000;
  return (y % 100) ? !(y % 4) : !(y % 16);
  /* return (is_multiple_of_100((unsigned)y)) ? !(y >> 2) : !(y >> 4); */
}

static inline int last_day_of_mon(int year, int mon)
{
  /* return mon != 2 ? ((mon ^ (mon >> 3))) | 30 : is_leap3(year) ? 29 : 28; */
  return mon != 2 ? ((mon ^ (mon >> 3))) | 30 : is_leap(year) ? 29 : 28;
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
  /* struct tm tm = *localtime(&(time_t){time(NULL)}); */
  struct tm tm = *localtime(&global_time);
  /* printf("Today is           %s", asctime(&tm)); */
  /* printf("Today is           %s",
   * asctime(&*localtime(&(time_t){time(NULL)}))); */
  sprintf(longdate, "%02d.%02d.%d", 1, tm.tm_mon + 1, tm.tm_year + 1900);
  /* goto previous */
  tm.tm_mon -= 1;
  /* reset to the first of month */
  tm.tm_mday = 1;
  /* adjust year to jump to previous if december */
  tm.tm_year = tm.tm_mon != 11 ? tm.tm_year : tm.tm_year - 1;
  /* make time again, referencing the previous month */
  mktime(&tm); // tm_isdst is not set to -1; today's DST status is used

  TM = tm;
  return 1;
}

static int then(char **argv)
{
  /* shorten year to two digits, in case you enter 2022 instead of 22 */
  char *p = argv[2];
  while (*p++ != '\0') // forward to the end
    ;
  p -= 3; // rewind back two characters, +1 for the '\0'
  argv[2] = p;

  /* shorten the month name to three charachters, case is entered ianuarie
   * instead of ian */
  argv[1][3]              = '\0';
  static const char *mths = "ian feb mar apr mai iun iul aug sep oct noi dec ";
  /* char *m = strstr("ian feb mar apr mai iun iul aug sep oct noi dec",
     argv[1]); */
  char     *m    = strstr(mths, argv[1]);
  int       mon  = (int)((m - mths) / 4);
  int       year = atoi(argv[2]); // atoi(p) ?
  struct tm tm2  = {.tm_sec  = 50,
                    .tm_min  = 50,
                    .tm_hour = 12,
                    .tm_mday = 1,
                    .tm_mon  = mon,
                    .tm_year = year + 100};
  mktime(&tm2);
  sprintf(longdate, "%02d.%02d.%d", tm2.tm_mday, tm2.tm_mon + 1,
          tm2.tm_year + 1900);

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
  /* printf("date recoderd: %d %d\n", TM.tm_year, TM.tm_mon); */
  /* printf("date recoderd: %d %d\n", TM.tm_year + 1900, TM.tm_mon + 1); */

  days_past   = days_from_civil(TM.tm_year + 1900, TM.tm_mon + 1, 1);
  dayz_in_mon = last_day_of_mon(TM.tm_year + 1900, TM.tm_mon + 1);
  /* arr[0]      = arr[1]; */
  /* fill starting with 1, so you can avoid branching in holiday loop */

#pragma omp parallel for
  for (int i = 1; i < dayz_in_mon; i++)
    arr[i] = ((weekday_from_days(days_past + i - 1)) % 6) != 0;
  /* otherwise the days past will not be correct */

  enum months { ian, feb, mar, apr, mai, iun, iul, aug, sep, oct, noi, dec };
  static const int hol[12][4] = {
      [ian] = {1, 2, 24},  [apr] = {22, 24, 25}, [mai] = {1, 5},
      [iun] = {1, 12, 13}, [aug] = {15},         [noi] = {30},
      [dec] = {25, 26}};

#pragma omp parallel for
  for (unsigned i = 0; i < 4; ++i)
    /* arr[hol[TM.tm_mon][i]] = hol[TM.tm_mon][i]; */
    arr[hol[TM.tm_mon][i]] = 0;
}

__attribute__((noreturn)) static void usage()
{
  puts("Usage: <mon> <year> <km>\ne.g. iun 22 80000\n");
  /* puts("No error checking whatsoever, you're on your own\n"); */
  exit(0);
}

static int init_time(int argc, char **argv)
{
  if (argc > 1 && (*argv[1] == 'h' || strcmp(argv[1], "-h") == 0 ||
                   strcmp(argv[1], "--h") == 0))
    usage();

  setenv("TZ", "/usr/share/zoneinfo/Europe/Bucharest", 1); // POSIX-specific

  global_time = time(0);

  cmdl(argc, argv);

  globals();

  return 0;
}

static void random_shuffle(void)
{
  static const struct Route parcurs[16] = {
      {"Cluj-Oradea", 321, "Interes Serviciu"},
      {"Cluj-Turda", 121, "Interes Serviciu"},
      {"Cluj-Zalau", 156, "Interes Serviciu"},
      {"Cluj-Baia-Mare", 356, "Interes Serviciu"},
      {"Cluj-Bistrita", 257, "Interes Serviciu"},
      {"Cluj-Dej", 101, "Interes Serviciu"},
      {"Cluj-Cluj", 47, "Interes Serviciu"},
      {"Acasa-Birou", 30, " "},
      {"Acasa-Birou", 30, " "},
      {"Acasa-Birou", 30, " "},
      {"Acasa-Birou", 30, " "},
      {"Acasa-Birou", 30, " "},
      {"Cluj-Cmp. Turzii", 152, "Interes Serviciu"},
      {"Cluj-Apahida", 85, "Interes Serviciu"},
      {"Cluj-Bontida", 92, "Interes Serviciu"},
      {"Cluj-Satu-Mare", 421, "Interes Serviciu"}};

  /* route_                   = (struct Route[128]){{0}}; */
  static const size_t n = ARRAY_SIZE(parcurs);
  static const size_t m = ARRAY_SIZE(route_);

  for (size_t i = 0; i < m; i++) {
    for (size_t j = 0; j < n; j++) {
      route_[i] = parcurs[(unsigned long)rand() % n];
    }
  }

  unsigned long found, play, cycle, k = 0, recent[128] = {[0 ... 127] = 0};
  found = play = cycle = k;

  /* static const unsigned route__size = ARRAY_SIZE(route_); */

  for (; cycle < m; cycle++) {
    do {
      play  = (unsigned long)rand() % n;
      found = 0;
      for (k = 0; k < n; k++)
        if (recent[k] == play)
          found = 1;
    } while (found);

    route_[cycle] = parcurs[play];
  }
}

__attribute__((const)) static inline unsigned
repeating(const struct Route *const in)
{
#pragma optimize "align-loops=32"
#pragma omp parallel for
  for (unsigned i = 0; i < 32; i++) {
    if (in[i + 1].km == in[i].km && in[i].km != 30)
      return 1;
  }
  return 0;
}

void mix(void)
{
  srand(global_time);
  do {
    random_shuffle();
  } while (repeating(route_));
}

#ifndef Skipmain
int main(int argc, char *argv[])
{

  init_time(argc, argv);
  mix();
  /* yap, works */
  for (unsigned i = 1; i < 30; ++i) {
    printf("%d %d\n", i, arr[i]);
  }

/* SCRATCH CODE */
#if 0
  /* printf("current: %s\t last month: %s\t days of last mo: %d\n", longdate,
   * luna, */
  /*        dayz_in_mon); */

  /* printf("long: %s\n", longdate); */
  /* printf("past: %d\n", days_past); */
  /* printf("past days till today,  not the 1st: %ld\n", global_time / ONE_DAY);
   */
  /* printf("ARR: %d %d %s", arr[1], TM.tm_wday, asctime(&TM)); */
  /* printf("weekday: %d\n", weekday_from_days(days_past)); */

  /* printf("%d\n", arr[1]); */
  /* printf("%d\n", arr[2]); */
  /* printf("%d\n", arr[3]); */
  /* printf("%d\n", arr[4]); */
  /* printf("%d\n", arr[5]); */
  /* printf("%d\n", arr[6]); */

  /* x |= 1 << 0; */
  /* x |= 1 << 1; */

  enum months { ian, feb, mar, apr, mai, iun, iul, aug, sep, oct, noi, dec };
  int hol[12][4] = {[ian] = {1, 2, 24},  [apr] = {22, 24, 25}, [mai] = {1, 5},
                    [iun] = {1, 12, 13}, [aug] = {15},         [noi] = {30},
                    [dec] = {25, 26}};

  printf("mon: %d\n", TM.tm_mon);
  arr[hol[TM.tm_mon][0]] = hol[TM.tm_mon][0];
  printf("mon: %d\n", arr[1]);

  for (unsigned i = 0; i < 4; ++i) {
    arr[hol[TM.tm_mon][i]] = hol[TM.tm_mon][i];
  }
  /* arr[hol[TM.tm_mon][0]] = hol[TM.tm_mon][0]; */
  printf("mon: %d\n", arr[24]);

  int *arr_ptr = hol[TM.tm_mon];
  arr[0] = *(arr_ptr + 0);
  arr[*(arr_ptr + 0)] = 1;

  /* void (*fp[32])(void); */
  /* for (unsigned i = 0; i < 4; i++) { */
  /*   arr[hol[2][i]]   = hol[2][i] > 0; */
  /*   arr[hol[ian][i]] = hol[ian][i] > 0; */
  /* } */

  /* arr[hol[ian][4]] = hol[ian][2]; */
  printf("ARR2: %d %d %d %d %s", arr[0], TM.tm_wday, TM.tm_mday, TM.tm_mon,
         asctime(&TM));



  /* DO NOT DELETE!!! */


  int *h1 = hol[0];
  int arrr[32] = {0};
  for (unsigned i = 0; i < 4; ++i) {
    printf("%d\n", hol[0][i]);
    arrr[i] = hol[0][i];
    arr[hol[ian][i]] = hol[ian][i];
  }
  printf("\n\n%d\n", arr[hol[ian][0]]);
#endif
  return 0;
}
#endif
