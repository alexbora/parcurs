/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : opt
 * @created     : Luni Feb 21, 2022 10:05:52 EET
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define Peval(cmd) printf(#cmd ": %g\n", cmd)

int main(int argc, char* argv[]) {
  int flags, opt;
  int nsecs, tfnd;

  nsecs = 0;
  tfnd = 0;
  flags = 0;
  while ((opt = getopt(argc, argv, "cn:")) != -1) {
    switch (opt) {
      case 'n':
        flags = 1;
        break;
      case 'c':
        nsecs = atoi(optarg);
        tfnd = 1;
        break;
      default: /* '?' */
        fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n", argv[0]);
        exit(EXIT_FAILURE);
    }
  }

  printf("flags=%d; tfnd=%d; nsecs=%d; optind=%d\n", flags, tfnd, nsecs,
         optind);

  if (optind >= argc) {
    fprintf(stderr, "Expected argument after options\n");
    exit(EXIT_FAILURE);
  }

  printf("name argument = %s\n", argv[optind]);

  /* Other code omitted */

  double* plist = (double[]){1, 2, 3};
  Peval(sizeof(plist) / (sizeof(double) + 0.0));

  int ENOMEM = 0;

  FILE* f;
  f = fopen("test", "w+");

#define xxx (f)
#ifdef DLOG
#undef stderr
#define stderr xxx
#endif

#define Testclaim(assertion, returnval)     \
  if (!(assertion)) {                       \
    fprintf(stderr, #assertion              \
            " failed to be true.  \
              Returning " #returnval "\n"); \
    return returnval;                       \
  }
  int x = 0;
  /* Testclaim(x == 1, ENOMEM) */

  char* z = "test";
  fprintf(f, "%s", z);
  fclose(f);

#if __STDC_NO_VLA__
#error "no vla"
#endif

  exit(EXIT_SUCCESS);
}
