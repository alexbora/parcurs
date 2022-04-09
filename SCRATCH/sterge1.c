/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : sterge1
 *
 * @created     : Sâmbătă Apr 02, 2022 10:20:09 EEST
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
static void advice(const char *text)
{
  const char *fmt = "text %s\n";
  fprintf(stderr, fmt, text);
}

void BUG_fl(const char *file, int line, const char *fmt)
{
  fprintf(stderr, "file: %s, line: %d,  errno: %d,  info: %s\n", file, line,
          errno, fmt);
};
#define BUG(...) BUG_fl(__FILE__, __LINE__, __VA_ARGS__)

int trace2_cmd_exit_fl(const char *file, int line, int code)
{
  fprintf(stderr, "%s %d %d\n", file, line, code);
  return code;
};

#define trace2_cmd_exit(code) (trace2_cmd_exit_fl(__FILE__, __LINE__, (code)))

int main()
{

  BUG("test\n");
  trace2_cmd_exit(1);

  return 0;
  struct Repo {
    char *a;
    int   x;
    int   dummy;
  };

#define REPO_INIT                                                              \
  {                                                                            \
    .a = NULL, .x = -1, .dummy = 0,                                            \
  }

  struct Repo repo = REPO_INIT;

  advice("exiting");

#define say(a, b, c) fprintf(stderr, a, b, c)
  say("%.*s\n", __LINE__, "err");
  BUG("test");
  return 0;
}
