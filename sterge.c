/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : sterge
 * @created     : duminică apr 10, 2022 13:08:27 EEST
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static struct tm TM, TM_PREV;
static double km;

static void date_now(void) {
  const time_t t = time(0);
  struct tm *tm = gmtime(&t);
  tm->tm_year += 1900;
  tm->tm_mon += 1;
  TM = *tm;
  tm = NULL;
}

static void date_prev(int year, int mon, int day) {
  struct tm time = {};
  time.tm_mday = day;
  time.tm_mon = mon;
  time.tm_year = year - 1900;
  mktime(&time);
  time.tm_year += 1900;
  TM_PREV = time;
  printf("WDAY: %d\n", time.tm_wday);
}

static void date_cmdl(int year, int mon, int day) {
  struct tm tm = {.tm_year = year - 1900, .tm_mon = mon - 1, .tm_mday = day};

  mktime(&tm);
  tm.tm_mon++;
  tm.tm_year += 1900;
  TM = tm;
}

static void fill_km(double *km) {
  FILE *f = fopen("km", "r");
  fscanf(f, "%lf", km);
  fclose(f);
  f = NULL;
}

static void process_cmdl(int argc, char *argv[restrict argc + 1]) {
  if (argv[1] && *argv[1] == 'h') {
    puts("\nExecute like './prog year month day km', for example './prog "
         "2022 4 10 100'.\nIf 0 km, file km is read.\nIf no arguments, current "
         "date is chosen and file km is read.\n");
    exit(EXIT_SUCCESS);
  }
  if (argv[1] && argv[2] && argv[3])
    date_cmdl(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
  else
    date_now();
  if (argc > 4 && argv[4])
    km = atof(argv[4]);
  else
    fill_km(&km);
}

int main(int argc, char *argv[argc + 1]) {
  process_cmdl(argc, argv);

  printf("%d %d %d %d\n %.lf\n", TM.tm_year, TM.tm_mon, TM.tm_mday, TM.tm_wday,
         km);

  date_prev(2022, 3, 10);
  printf("%d %d %d %d\n %.lf\n", TM_PREV.tm_year, TM_PREV.tm_mon,
         TM_PREV.tm_mday, TM_PREV.tm_wday, km);

  struct tm time = {0};

  time.tm_mday = 10;
  time.tm_mon = 2;
  time.tm_year = 2022 - 1900;

  mktime(&time);

  printf("%d\n", time.tm_wday);

  return 0;
}
