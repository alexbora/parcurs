/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : sterge
 * @created     : duminică apr 10, 2022 13:08:27 EEST
 */

/* time includes */
#include "date.h"

#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_DAYS 32

static struct tm TM;
static double    km;
static char      longdate[64];
static char      luna[64];
static int       dayz;
/* static int parcursi; */
int array[MAX_DAYS];
static int (*is_holiday)(int, int, int);
/* static char *tmp_luna; */
int current_year;

void date_now(void)
{
  const time_t t  = time(0);
  struct tm   *tm = gmtime(&t);
  strftime(longdate, 64, "%d.%m.%Y", tm);
  tm->tm_mon--;
  strftime(luna, 64, "%B", tm);
  *luna |= ' ';

  tm->tm_year += 1900;
  current_year = tm->tm_year;
  tm->tm_mon += 2;
  TM = *tm;
  tm = NULL;
}

static void date_cmdl(const int year, const int mon, const int day)
{
  struct tm tm = {.tm_year = year - 1900, .tm_mon = mon - 1, .tm_mday = day};
  mktime(&tm);

  strftime(longdate, 64, "%d.%m.%Y", &tm);
  tm.tm_mon--;
  strftime(luna, 64, "%B", &tm);
  *luna |= ' ';

  tm.tm_mon += 2;
  tm.tm_year += 1900;
  current_year = tm.tm_year;
  TM           = tm;
}

static void get_km(double *km)
{
  FILE *f = fopen("km", "r");
  fscanf(f, "%lf", km);
  fclose(f);
  f = NULL;
}

static void write_km(double *const km)
{
  FILE *f = fopen("km", "w++");
  fprintf(f, "%lf", *km);
  fclose(f);
  f = NULL;
}

void usage(int argc, char **argv)
{
  puts("\nExecute like './prog year month day km', for example './prog "
       "2022 4 10 100'.\nIf 0 km, file km is read.\nIf no arguments, "
       "current "
       "date is chosen and file km is read.\n");
  exit(EXIT_SUCCESS);
}

void process_cmdl(int argc, char *argv[restrict argc + 1])
{
  if (argv[1] && *argv[1] == 'h')
    usage(argc, argv);

  if (argv[1] && argv[2] && argv[3])
    date_cmdl(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
  else
    date_now();
  if (argc > 4 && argv[4])
    km = atof(argv[4]);
  else
    get_km(&km);
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
    unsigned day, month;
  } hol[] = {
      {1, 1}, {2, 1},  {24, 1}, {22, 4}, {24, 4},  {25, 4}, {1, 5},   {1, 5},
      {1, 6}, {12, 6}, {13, 6}, {15, 8}, {30, 11}, {1, 12}, {25, 12}, {26, 12},
  };

  for (int i = 0; i < (int)(sizeof(hol) / sizeof(hol[0])); i++)
    if (month == hol[i].month && day == hol[i].day)
      return 1;
  return 0;
}

static int is_holiday_net(const int year, const int month, const int day)
{
  /* h_ptr = hh; */
  for (int i = 0; i < MAX_DAYS; i++)
    if (month == h_ptr[i].month && day == h_ptr[i].day)
      return 1;
  return 0;
}

static unsigned days_in_month(const int month, const int year)
{
  if (month == 4 || month == 6 || month == 9 || month == 11)
    return 30;
  else if (month == 2)
    return (((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29
                                                                      : 28);
  return 31;
}

void generate_array(int *arr)
{
  dayz = days_in_month(TM.tm_mon, TM.tm_year + 1900);
  for (int i = 1; i <= dayz; ++i) {
    struct tm ti = {59, 59, 12, i, TM.tm_mon - 1, TM.tm_year - 1900};
    mktime(&ti);

    arr[i] = is_weekend(ti.tm_wday);
    arr[i] |= is_holiday(ti.tm_year + 1900, ti.tm_mon + 1, ti.tm_mday);

    printf("wday: %d %s wk: %d\t hol: %d %d\n", ti.tm_wday, asctime(&ti),
           is_weekend(ti.tm_wday),
           is_holiday(ti.tm_year + 1900, ti.tm_mon + 1, ti.tm_mday), arr[i]);
  }
}

void generate_time(int argc, char *argv[])
{
  setlocale(LC_TIME, "ro_RO.UTF-8");
  process_cmdl(argc, argv);
  /* net        = 0; */
  is_holiday = h_ptr ? is_holiday_net : is_holiday_static;
  generate_array(array);
}

#define Skipmain
#ifndef Skipmain
int main(int argc, char *argv[argc + 1])
{
  /* setlocale(LC_TIME, "ro_RO.UTF-8"); */
  /* process_cmdl(argc, argv); */

  generate_time(argc, argv);

  printf("CURRENT: %d %d %d weekday today: %d\tkm: %.lf\n", TM.tm_year,
         TM.tm_mon, TM.tm_mday, TM.tm_wday, km);

  puts(longdate);
  puts(luna);

  /* generate_array(array); */
  write_km();

  return 0;
}
#endif
