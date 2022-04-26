/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : sterge7
 * @created     : duminică apr 24, 2022 11:06:02 EEST
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TM_INIT                                                                \
  { .a = "test", .x = 1 }

struct T {
  char *a;
  int x;
};

char *arr[] = {"OK", [8] = "FAIL"};

int update(void) {
  puts("updated\n");
  return 0;
}

struct strm {
  char *msg;
};

char *z_errmsg[10] = {"ok", "fail"}; /* indexed by 2-zlib_error */

#define ERR_MSG(err) z_errmsg[2 - (err)]

#define ERR_RETURN(strm, err) return (strm->msg = (char *)ERR_MSG(err), (err))

int main(int argc, char *argv[]) {

  struct strm *m = (struct strm *){0};
  ERR_RETURN(m, 2);

  int x = 30, update();
  void foo() { printf("You can do this in GCC. %d\n", x); }
  foo();

  struct T t = TM_INIT;
  struct T t2[] = {
#define AT(a) {(a), (strlen(a))}
      AT("w"), AT("x")
#undef AT
  };
  int z = 9;
  puts(arr[(z)-1]);

  return 0;
}
