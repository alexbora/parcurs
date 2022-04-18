/**
 * @author      : alex (alex@T460)
 * @file        : main
 * @created     : miercuri apr 13, 2022 19:52:58 EEST
 */

#include "date.h"
#include "main.h"

#include <stdio.h>
#include <stdlib.h>
/* int net; */

#ifdef LOG
#undef stderr
#define stderr l
#endif

struct Net *h_ptr;
double      km;

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

void usage(void)
{
  puts("\nExecute like './prog year month day km', for example './prog "
       "2022 4 10 100'.\nIf 0 km, file km is read.\nIf no arguments, "
       "current "
       "date is chosen and file km is read.\n");
  exit(EXIT_SUCCESS);
}

void get_km(void)
{
  FILE *f = fopen("km", "r");
  if (fscanf(f, "%lf", &km))
    fclose(f);
  f = NULL;
}

void write_km(void)
{
  FILE *f = fopen("km", "w++");
  fprintf(f, "%lf", km);
  fclose(f);
  f = NULL;
}

int main(int argc, char **argv)
{
#ifdef LOG
  FILE *l = fopen("log", "w++");
#endif

  h_ptr = (struct Net[32]){{0}};

  process_cmdl(argc, argv);

  /* if (argv[1] && *argv[1] == 'h') */
  /* usage(); */
  net_fetch();
  generate_time();
  mix();
  printf("current: %d %s %s\n", current_year, luna, longdate);
  h_ptr = NULL;

#if 0
  FILE *f = fopen("config.h", "r");
  rewind(f);
  int  i = 0;
  char bb[4096];
  while (!feof(f))
    bb[i++] = getc(f);
  puts(bb);
#endif

#ifdef LOG
  fclose(stderr);
#endif
  return 0;
}
