/**
 * @author      : alex (alex@T460)
 * @file        : main
 * @created     : miercuri apr 13, 2022 19:52:58 EEST
 */

#include "main.h"
#include "date.h"

#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

FILE *l;

/* struct Net *h_ptr = (struct Net[32]){{0}}; */
struct Net *h_ptr;
double km;

__attribute__((noreturn)) static void usage(void) {
  puts("\nExecute like './prog year month day km', for example './prog "
       "2022 4 10 100'.\nIf 0 km, file km is read.\nIf no arguments, "
       "current "
       "date is chosen and file km is read.\n");
  exit(EXIT_SUCCESS);
}

static void get_km(void) {
  FILE *f = fopen("km", "r");
  if (fscanf(f, "%lf", &km))
    fclose(f);
  f = NULL;
}

static void write_km(void) {
  FILE *f = fopen("km", "w++");
  fprintf(f, "%lf", km);
  fclose(f);
  f = NULL;
}

static void process_cmdl(int argc, char **argv) {
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

int main(int argc, char **argv) {
#ifdef LOG
  l = fopen("log", "w++");
#endif

  h_ptr = (struct Net[32]){{0}};

  get_km();

  process_cmdl(argc, argv);

  net_fetch(2);

  generate_time();

  mix();

  write_excel();

  write_km();

#ifdef LOG
  fclose(stderr);
#endif

  fprintf(stderr, "current: %d %s %s\n", current_year, luna, longdate);
  write(fd, longdate, 10);
  puts(FIN_MSG);

  return 0;
}
