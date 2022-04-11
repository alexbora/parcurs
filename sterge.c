/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : sterge
 * @created     : duminică apr 10, 2022 13:08:27 EEST
 */

#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static struct tm TM, TM_PREV;
static double    km;
static char      longdate[64];
static char      luna[64];
static int       dayz;
static int       parcursi;
typedef void (*write_body_fn)(void);
int array[32];

static void date_now(void)
{
  const time_t t  = time(0);
  struct tm   *tm = gmtime(&t);
  strftime(longdate, 64, "%d.%m.%Y", tm);
  tm->tm_mon--;
  strftime(luna, 64, "%B", tm);
  *luna |= ' ';

  tm->tm_year += 1900;
  tm->tm_mon += 2;
  TM = *tm;
  tm = NULL;
}

static void date_prev(int year, int mon, int day)
{
  struct tm ti    = {59, 59, 12, day, mon - 2, year - 1900};
  time_t    epoch = mktime(&ti);
  /* printf("%s", asctime(gmtime(&epoch))); */
  /* printf("W: %d\n", ti.tm_wday); */

  TM_PREV = ti;
  TM_PREV.tm_year += 1900;
  TM_PREV.tm_mon++;
  if (TM_PREV.tm_mon == 0)
    TM_PREV.tm_year--;
}

static void date_cmdl(int year, int mon, int day)
{
  if (year < 1970) {
    puts("Invalid year\n");
    exit(EXIT_SUCCESS);
  }
  struct tm tm = {.tm_year = year - 1900, .tm_mon = mon - 1, .tm_mday = day};
  mktime(&tm);

  strftime(longdate, 64, "%d.%m.%Y", &tm);
  tm.tm_mon--;
  strftime(luna, 64, "%B", &tm);
  *luna |= ' ';

  tm.tm_mon += 2;
  tm.tm_year += 1900;
  TM = tm;
}

static void fill_km(double *km)
{
  FILE *f = fopen("km", "r");
  fscanf(f, "%lf", km);
  fclose(f);
  f = NULL;
}

static void process_cmdl(int argc, char *argv[restrict argc + 1])
{
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

static int is_weekend(int day)
{
  if (day == 0 || day == 6)
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

void fn(void)
{
  puts("fn\n");
}
void fe(void)
{
  puts("fe\n");
}

void generate_array(int *arr)
{
  arr[0] = 9;
  int *p = arr;
  printf("%d\n\n", *(p++));

  for (int i = 1; i <= 32; ++i) {
    struct tm ti = {59, 59, 12, i, TM.tm_mon - 1, TM.tm_year - 1900};
    mktime(&ti);
    printf("wday: %d %s %d\n", ti.tm_wday, asctime(&ti),
           is_weekend(ti.tm_wday));
    arr[i] = is_weekend(ti.tm_wday) ? 0 : 1;
  }
}

int main(int argc, char *argv[argc + 1])
{

  setlocale(LC_TIME, "ro_RO.UTF-8");
  process_cmdl(argc, argv);

  printf("CURRENT: %d %d %d weekday today: %d\tkm: %.lf\n", TM.tm_year,
         TM.tm_mon, TM.tm_mday, TM.tm_wday, km);
  /* date_prev(TM.tm_year, TM.tm_mon, TM.tm_mday); */

  /* printf("PREV: %d %d %d weekday prev: %d\n", TM_PREV.tm_year,
   * TM_PREV.tm_mon, */
  /* TM_PREV.tm_mday, TM_PREV.tm_wday); */

  /* printf("weekday today: %d\n", TM.tm_wday); */
  /* printf("FREE previous month: %d\n", is_weekend(TM_PREV.tm_wday)); */
  /* printf("FREE today: %d\n", is_weekend(TM.tm_wday)); */

  /* int row[32] = {0}; */

  puts(longdate);
  puts(luna);

  generate_array(array);
  array[31] = 7;
  for (unsigned i = 0; i < 32; i++) {
    printf("arr: %d\n", array[i]);
  }

  return 0;
  /* return 0; */
  void (*fp[11])(void);
  write_body_fn f[32];
  f[0] = fn;

  for (int i = 1; i <= 10; ++i) {
    struct tm ti = {59, 59, 12, i, TM.tm_mon - 1, TM.tm_year - 1900};
    /* struct tm ti = {59, 59, 12, i, 3, 2022 - 1900}; */
    mktime(&ti);
    printf("wday: %d %s %d\n", ti.tm_wday, asctime(&ti),
           is_weekend(ti.tm_wday));
    /* row[i] = !is_weekend(ti.tm_wday); */
    fp[i] = is_weekend(ti.tm_wday) ? fn : fe;
  }

  /* int d = 5, i = 0; */
  /* while (d--) { */
  /*   fp[++i](); */
  /* } */

  /* return 0; */
  for (unsigned i = 1; i <= 10; ++i) {
    fp[i]();
  }

  /* printf("%d\n", row[1]); */

  return 0;
}
