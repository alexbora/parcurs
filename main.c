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

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

/* struct Net hh[32], *h_ptr; */
struct Net *h_ptr;

int main(int argc, char **argv)
{
  h_ptr = (struct Net[32]){{0}};

  process_cmdl(argc, argv);

  /* if (argv[1] && *argv[1] == 'h') */
  /* usage(); */
  net_fetch();
  mix();
  generate_time();
  printf("current: %d %s %s\n", current_year, luna, longdate);
  h_ptr = NULL;

  printf("%d\n", array[0]);
  printf("%d\n", array[1]);
  printf("%d\n", array[2]);
  printf("%d\n", array[3]);
  printf("%d\n", array[4]);
  printf("%d\n", array[5]);

#if 0
  FILE *f = fopen("config.h", "r");
  rewind(f);
  int  i = 0;
  char bb[4096];
  while (!feof(f))
    bb[i++] = getc(f);
  puts(bb);
#endif
  return 0;
}
