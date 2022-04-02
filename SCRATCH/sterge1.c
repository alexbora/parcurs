/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : sterge1
 *
 * @created     : Sâmbătă Apr 02, 2022 10:20:09 EEST
 */
#include <stdio.h>
#include <stdlib.h>

static void advice(const char *text) {
  const char *fmt = "text %s\n";
  fprintf(stderr, fmt, text);
}

int main() {
  struct Repo {
    char *a;
    int   x;
    int   dummy;
  };

#define REPO_INIT                                                              \
  { .a = NULL, .x = -1, .dummy = 0, }

  struct Repo repo = REPO_INIT;

  advice("exiting");

#define say(a, b, c) fprintf(stderr, a, b, c)
  int err = 8;
  say("%.*s\n", __LINE__, "err");

  return 0;
}
