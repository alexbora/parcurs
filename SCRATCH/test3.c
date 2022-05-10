/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test3
 * @created     : marţi mai 10, 2022 19:21:17 EEST
 */

#include <stdio.h>
#include <stdlib.h>

static inline int fn1(void) { return 0; }

int fn(void) { return fn1(); }

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

  return 0;
}
