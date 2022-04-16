/**
 * @author      : alex (alex@T460)
 * @file        : main
 * @created     : miercuri apr 13, 2022 19:52:58 EEST
 */

#include "date.h"

#include <stdio.h>
#include <stdlib.h>
/* int net; */

/* struct Net hh[32], *h_ptr; */
struct Net *h_ptr;

int main(int argc, char **argv) {
  /* h_ptr = (struct Net[32]){{4, 1}}; */
  if (argv[1] && *argv[1] == 'h')
    usage();
  net_fetch();
  generate_time(argc, argv);
  printf("current: %d\n", current_year);
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
