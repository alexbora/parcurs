#include "main.h"
#include <stdio.h>
#include <stdlib.h>

extern int dayz_in_mon;
extern char attachment[128];
extern unsigned char arr[32];

int main(int argc, char *argv[]) {
  init_time(argc, argv);
  mix();
  /* yap, works */
  for (unsigned i = 1; i <= dayz_in_mon; ++i) {
    printf("%d %d\n", i, arr[i]);
  }

  /* if (argc > 3) */
  /* get_km(argv[argc - 1]); */
  /* else */
  get_km(argc > 3 ? argv[argc - 1] : NULL);

  /* printf("%f\n", km); */
  /* gen(); */

  write_excel();

  write_km();
  mail_me(attachment);
  return 0;
}
