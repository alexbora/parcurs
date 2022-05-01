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

static const char *mths = "ian feb mar apr mai iun iul aug sep oct noi dec";
static char longdate[128], *luna;
static unsigned dayz;
static struct tm TM;

struct Data;
typedef void (*fp)(struct Data *);

struct Data {
  void *data;
  fp func;
};

void func1(struct Data *in) { puts((char *)in->data); }

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

static inline unsigned days_in_month(const int month, const int year) {
  if (month == 4 || month == 6 || month == 9 || month == 11)
    return 30;
  else if (month == 2)
    return (((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29
                                                                      : 28);
  return 31;
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
  return 1;
}

static int then(char **argv) {
  char *m = strstr(mths, argv[1]);
  struct tm tm2 = {50, 50, 12, 1, (int)((m - mths) / 4), 2000 + atoi(argv[2])};
  mktime(&tm2);
  sprintf(longdate, "%02d.%02d.%d", tm2.tm_mday, tm2.tm_mon + 1, tm2.tm_year);

  TM = tm2;
  return 1;
}

static int cmdl(int argc, char **argv) {
  if (argc > 2)
    return then(argv);
  return now();
}

static void globals() {
  luna = literal_mon(TM.tm_mon);
  dayz = days_in_month(TM.tm_mon + 1, TM.tm_year);
}

__attribute__((noreturn)) static void usage() {
  puts("Usage: <mon> <year> <km>");
  exit(0);
}

int main(int argc, char **argv) {

  if (argc > 1 && (*argv[1] == 'h' || strcmp(argv[1], "-h") == 0 ||
                   strcmp(argv[1], "--h") == 0))
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

  struct Data d = {"func1", func1};
  d.func(&d);

  static const struct {
    int day, month;
  } hol[] = {
      {1, 1},  {2, 1},  {24, 1}, {22, 4},  {24, 4}, {25, 4},  {1, 5},   {1, 6},
      {12, 6}, {13, 6}, {15, 8}, {30, 11}, {1, 12}, {25, 12}, {26, 12},
  };

  enum { ian = 1, feb = 2, mar = 3, apr = 4 } mon;
  int arr_hol[][4] = {[ian] = {1, 2, 24}, [apr] = {22, 24, 24}};

  if (TM.tm_mon == ian && TM.tm_mday == arr_hol[0][0])
    puts(" whatever\n");

  printf("%d\n", *arr_hol[4]);
  printf("%d\n", arr_hol[4][0]);

  return 0;
}
