/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : sterge
 * @created     : Duminică Feb 13, 2022 12:09:34 EET
 */

#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int i, n = 10;
  gsl_rng_env_setup();

  gsl_rng* r = gsl_rng_alloc(gsl_rng_default);

  for (i = 0; i < n; i++) {
    unsigned long u = gsl_rng_uniform_int(r, 31);
    printf("%ld\n", u);
  }

  gsl_rng_free(r);

  double a[7], b[16];

  for (i = 0; i < 16; i++) {
    b[i] = (double)i;
  }

  gsl_ran_choose(r, a, 7, b, 16, sizeof(double));

  int j = 7;
  /* while (j--) printf("%f\t", a[j]); */

  for (i = 0; i < 7; i++) {
    a[i] = i;
  }

  gsl_ran_shuffle(r, a, 7, sizeof(int));

  j = 7;
  while (j--) printf("%f\t", a[j]);

  puts("\n");

  int array[128];
  for (int m = 0; m < 128; m++) {  // fill array
    array[m] = m;
  }

  for (int p = 0; p < 128; p++) {  // shuffle array
    int tmp = array[p];
    int get = rand() % 128;
    array[p] = array[get];
    array[get] = tmp;
  }

  for (int q = 0; q < 128; q++) {  // print array
    printf("%d\t", array[q]);
  }
  int add(int, int);
  int (*operations[128])(int, int);
  operations['+'] = add;

  return 0;
};
