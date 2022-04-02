/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : sterge1
 *
 *
 * @created     : Sâmbătă Apr 02, 2022 10:20:09 EEST
 */
#include <stdlib.h>

int main(int argc, char *argv[]) {
  struct Repo {
    int   x;
    char *a;
  } repo;
#define REPO_INIT                                                              \
  (struct Repo){                                                               \
      .x = -1,                                                                 \
      .a = NULL,                                                               \
  }

  repo = REPO_INIT;

  return 0;
}
