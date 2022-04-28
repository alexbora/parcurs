/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : sterge
 * @created     : duminică apr 10, 2022 13:08:27 EEST
 */

/* time includes */
/* #include "date.h" */
/* definitions are in main, uninclude date.h */
#include "main.h"

#include <stdio.h>
#include <stdlib.h>
/* #include <sys/wait.h> */
#include <time.h>

static struct tm TM;
char             longdate[32], *luna;
int              current_year, array[32];
unsigned         dayz;
static int (*is_holiday)(const int, const int, const int);

static inline char *literal_mon(const int month)
{
  return &"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0ianuarie\0\0\0\0\0\0\0\0februari"
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
  struct tm tm = *(localtime(&(time_t){time(0)}));

  sprintf(longdate, "%02d.%02d.%d", tm.tm_mday, tm.tm_mon + 1,
          tm.tm_year + 1900);

  if (tm.tm_mon == 11) {
    tm.tm_year--;
    mktime(&tm);
  }

  luna = literal_mon(tm.tm_mon);

  current_year = tm.tm_year += 1900;
  TM           = tm;
}

void date_cmdl(const int year, const int mon, const int day)
{
  struct tm tm = {.tm_year = year - 1900, .tm_mon = mon - 1, .tm_mday = day};

  mktime(&tm);

  sprintf(longdate, "%02d.%02d.%d", tm.tm_mday, tm.tm_mon + 1,
          tm.tm_year + 1900);

  luna = literal_mon(tm.tm_mon + 1);

  tm.tm_year += 1900;
  tm.tm_mon += 1;
  current_year = tm.tm_year;
  TM           = tm;
}

static inline int is_weekend(const int day)
{
  return (day == 6) | (day == 0);
}

static inline int is_holiday_static(const int year, const int month,
                                    const int day)
{
  register const int y = year;
  if (y != 2022)
    return 0;

  static const struct {
    int day, month;
  } hol[] = {
      {1, 1}, {2, 1},  {24, 1}, {22, 4}, {24, 4},  {25, 4}, {1, 5},   {1, 5},
      {1, 6}, {12, 6}, {13, 6}, {15, 8}, {30, 11}, {1, 12}, {25, 12}, {26, 12},
  };
  const size_t size = ARRAY_SIZE(hol);
  for (size_t i = 0; i < size; i++)
    if (((month - hol[i].month) | (day - hol[i].day)) == 0)
      return 1;
  return 0;
}

static inline int is_holiday_net(const int year, const int month, const int day)
{
  (void)year;
  const unsigned d = dayz;
  for (unsigned i = 0; i < d; i++)
    if (month == h_ptr[i].month && day == h_ptr[i].day)
      return 1;
  return 0;
}

static inline unsigned days_in_month(const int month, const int year)
{
  if (month == 4 || month == 6 || month == 9 || month == 11)
    return 30;
  else if (month == 2)
    return (((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29
                                                                      : 28);
  return 31;
}

static inline void generate_array(int *const arr)
{
  dayz             = days_in_month(TM.tm_mon, TM.tm_year);
  const unsigned d = dayz;
  for (unsigned i = 1; i <= d; ++i) {
    struct tm ti = {59, 59, 12, (int)i, TM.tm_mon - 1, TM.tm_year - 1900,
                    0,  0,  0,  0,      NULL};
    mktime(&ti);

    arr[i] = is_weekend(ti.tm_wday);
    arr[i] |= is_holiday(ti.tm_year + 1900, ti.tm_mon + 1, ti.tm_mday);

    /* printf("validation: %d %s", arr[i], asctime(&ti)); */
  }
  /* puts("\n"); */
}

void generate_time(void)
{
  fprintf(stderr, "Today is           %s",
          asctime(&*localtime(&(time_t){time(NULL)})));
  is_holiday = h_ptr ? is_holiday_net : is_holiday_static;
  h_ptr ? fprintf(stderr, "\nUsing net.\n")
        : fprintf(stderr, "\nUsing static table.\n");

  generate_array(array);

  /* typedef int (*holiday_check)(const int, const int, const int); */
  /* static holiday_check check = is_holiday_static; */
  /* check                      = is_holiday_net; */
}
