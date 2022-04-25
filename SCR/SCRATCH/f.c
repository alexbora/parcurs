/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : f
 * @created     : Luni Feb 21, 2022 18:20:06 EET
 */

#define HAVE_ASPRINTF
#ifndef HAVE_ASPRINTF
#error \
    "HAVE_ASPRINTF undefined. I simply refuse to " \
               "compile on a system without asprintf."
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef LOG
#define log f
#else
#define log stderr
#endif

#ifdef L
#undef stderr
#define stderr f
#endif

#define Testclaim(assertion, returnval)     \
  if (!(assertion)) {                       \
    fprintf(stderr, #assertion              \
            " failed to be true.  \
              Returning " #returnval "\n"); \
    return returnval;                       \
  }

#define fileprintf(...) fprintf(f, __VA_ARGS__)
#define doubleprintf(human, machine) \
  do {                               \
    printf human;                    \
    fileprintf machine;              \
  } while (0)

int main(int argc, char* argv[]) {
  FILE* f = fopen("z", "w++");
  double x = 1;
  if (x < 2) doubleprintf(("x is negative (%g)\n", x), ("NEGVAL: x=%g\n", x));
    /* int h = 0; */
    /* Testclaim(h == 1, 7); */

    /* fclose(f); */

#define Blankcheck(a)                                    \
  {                                                      \
    int aval = (#a[0] == '\0') ? 0 : (a + 0);            \
    printf("I understand your input to be %i.\n", aval); \
  }

  int n = 0;
  n = !n;
  Blankcheck(2);
  Blankcheck(0);
  printf("n: %d\n", n);

#if defined __STDC_NO_ATOMICS__
  printf("no_atomics\n");
#else
  printf("atomics available\n");
#endif
  return 0;
}
