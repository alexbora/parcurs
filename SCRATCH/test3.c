/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test3
 * @created     : marţi mai 10, 2022 19:21:17 EEST
 */

#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static inline int fn1(void) { return 0; }

int fn(void) { return fn1(); }

void sys_error(char *error, ...) {
  va_list argptr;
  char string[1024];

  // change stdin to non blocking
  fcntl(0, F_SETFL, fcntl(0, F_GETFL, 0) & ~FNDELAY);

  va_start(argptr, error);
  vsprintf(string, error, argptr);
  va_end(argptr);
  fprintf(stderr, "Error: %s\n", string);

  exit(1);
}

int main(int argc, char *argv[]) {

  struct Route {
    char *a;
    int x;
    void (*fn)(struct Route *);
  };

  typedef struct work_s {
    struct Route route;
  } work_t;

  work_t w1;
  struct work_s w2 = {{}};

  w1.route = (struct Route){"a", 1, NULL};

  sys_error("error");

  return 0;
}
