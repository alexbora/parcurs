/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test3
 * @created     : marţi mai 10, 2022 19:21:17 EEST
 */

#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

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

void debug_log(char *file, char *fmt, ...) {
  va_list argptr = {};
  static char data[1024] = {'\0'};
  int fd = 0;

  va_start(argptr, fmt);
  vsprintf(data, fmt, argptr);
  va_end(argptr);
  fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
  write(fd, data, strlen(data));
  close(fd);
}

double Sys_FloatTime(void) {
  struct timeval tp;
  struct timezone tzp;
  static int secbase;

  gettimeofday(&tp, &tzp);

  if (!secbase) {
    secbase = tp.tv_sec;
    return tp.tv_usec / 1000000.0;
  }

  return (tp.tv_sec - secbase) + tp.tv_usec / 1000000.0;
}

int main(int argc, char *argv[]) {

  printf("%f\n", Sys_FloatTime());

  debug_log("test", "1\n");
  debug_log("test", "2\n");

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

  /* sys_error("error"); */

  return 0;
}
