/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : sterge
 * @created     : duminică apr 10, 2022 13:08:27 EEST
 */

/* time includes */
#include "date.h"
#include "main.h"

#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_DAYS 32

static struct tm TM;
static double    km;
char             longdate[64];
char            *luna;
static int       dayz;
/* static int parcursi; */
static int (*is_holiday)(int, int, int);
/* static char *tmp_luna; */
int current_year;

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

void date_now(void)
{
  /* const time_t t = time(0); */
  struct tm *tm = localtime(&(time_t){time(0)});

  strftime(longdate, 64, "%d.%m.%Y", tm);

  if (tm->tm_mon == 11) {
    tm->tm_year--;
    mktime(tm);
  }

  luna = literal_mon(tm->tm_mon);

  /* tm->tm_mon--; */
  /* strftime(luna, 64, "%B", tm); */
  /* *luna |= ' '; // convert lowercase */

  /* current_year = tm->tm_year; */
  /* tm->tm_mon = 1; */

  /* if (tm->tm_mon == 1) { */
  /*   /1* tm->tm_year--; *1/ */
  /*   tm->tm_mon -= 2; */
  /*   mktime(tm); */
  /* } */

  printf("tm mon %s\n", asctime(tm));
  printf("%d %d\n", tm->tm_mday, tm->tm_wday);

  current_year = tm->tm_year += 1900;
  tm->tm_mon += 1;
  TM = *tm;
  tm = NULL;
}

static void date_cmdl(const int year, const int mon, const int day)
{
  struct tm tm = {.tm_year = year - 1900, .tm_mon = mon - 1, .tm_mday = day};

  mktime(&tm);

  strftime(longdate, 64, "%d.%m.%Y", &tm);
  /* tm.tm_mon--; */
  /* strftime(luna, 64, "%B", &tm); */
  /* *luna |= ' '; */
  luna = literal_mon(tm.tm_mon + 1);

  tm.tm_year += 1900;
  tm.tm_mon += 1;
  current_year = tm.tm_year;
  TM           = tm;
}

static void get_km(void)
{
  FILE *f = fopen("km", "r");
  if (fscanf(f, "%lf", &km))
    fclose(f);
  f = NULL;
}

static void write_km(void)
{
  FILE *f = fopen("km", "w++");
  fprintf(f, "%lf", km);
  fclose(f);
  f = NULL;
}

__attribute__((noreturn)) void usage(void)
{
  puts("\nExecute like './prog year month day km', for example './prog "
       "2022 4 10 100'.\nIf 0 km, file km is read.\nIf no arguments, "
       "current "
       "date is chosen and file km is read.\n");
  exit(EXIT_SUCCESS);
}

void process_cmdl(int argc, char **argv)
{
  if (argv[1] && *argv[1] == 'h')
    usage();

  if (argv[1] && argv[2] && argv[3])
    date_cmdl(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
  else
    date_now();
  if (argc > 4 && argv[4])
    km = atof(argv[4]);
  else
    get_km();
}

static int is_weekend(const int day)
{
  return (day == 6) | (day == 0);
}

static int is_holiday_static(const int year, const int month, const int day)
{
  if (year != 2022)
    return 0;
  static const struct {
    int day, month;
  } hol[] = {
      {1, 1}, {2, 1},  {24, 1}, {22, 4}, {24, 4},  {25, 4}, {1, 5},   {1, 5},
      {1, 6}, {12, 6}, {13, 6}, {15, 8}, {30, 11}, {1, 12}, {25, 12}, {26, 12},
  };

  for (size_t i = 0; i < sizeof(hol) / sizeof(hol[0]); i++)
    if (month == hol[i].month && day == hol[i].day)
      return 1;
  return 0;
}

static int is_holiday_net(const int year, const int month, const int day)
{
  /* h_ptr = hh; */
  (void)year;
  for (int i = 0; i < dayz; i++)
    if (month == h_ptr[i].month && day == h_ptr[i].day)
      return 1;
  return 0;
}

static int days_in_month(const int month, const int year)
{
  if (month == 4 || month == 6 || month == 9 || month == 11)
    return 30;
  else if (month == 2)
    return (((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29
                                                                      : 28);
  return 31;
}

static void generate_array(int *arr)
{
  dayz = days_in_month(TM.tm_mon, TM.tm_year);
  printf("%d\n", dayz);
  printf("%d\n", TM.tm_year);
  printf("%d\n", TM.tm_mon);
  for (int i = 1; i <= dayz; ++i) {
    struct tm ti = {59, 59, 12, i, TM.tm_mon - 1, TM.tm_year - 1900,
                    0,  0,  0,  0, NULL};
    mktime(&ti);

    arr[i] = is_weekend(ti.tm_wday);
    arr[i] |= is_holiday(ti.tm_year + 1900, ti.tm_mon + 1, ti.tm_mday);

    printf("validation: %d %s", arr[i], asctime(&ti));
#if 0
    arr[i] = is_weekend(ti.tm_wday);
    arr[i] |= is_holiday(ti.tm_year + 1900, ti.tm_mon + 1, ti.tm_mday);
    printf("%d\t", arr[i]);
    printf("weekday: %d\t is weekend? %d\t is_holiday?: %d\t validation array: "
           "%d\t %s",
           ti.tm_wday, is_weekend(ti.tm_wday),
           is_holiday(ti.tm_year + 1900, ti.tm_mon + 1, ti.tm_mday), arr[i],
           asctime(&ti));
#endif
  }
  puts("\n");
}

void generate_time(void)
{
  setlocale(LC_TIME, "ro_RO.UTF-8");
  /* process_cmdl(argc, argv); */
  /* net        = 0; */
  is_holiday = h_ptr ? is_holiday_net : is_holiday_static;
  if (h_ptr)
    fprintf(stderr, "%s\n", "using net\n");
  generate_array(array);
  write_km();
}

/* #define Skipmain */
#ifndef Skipmain
int main(int argc, char *argv[argc + 1])
{
  /* setlocale(LC_TIME, "ro_RO.UTF-8"); */
  /* process_cmdl(argc, argv); */

  generate_time();

  printf("CURRENT: %d %d %d weekday today: %d\tkm: %.lf\n", TM.tm_year,
         TM.tm_mon, TM.tm_mday, TM.tm_wday, km);

  puts(longdate);
  puts(luna);

  /* generate_array(array); */
  write_km();
  return 0;
}
#endif
