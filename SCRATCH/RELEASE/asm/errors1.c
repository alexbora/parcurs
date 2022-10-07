/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : errors1
 * @created     : Vineri Oct 07, 2022 16:03:09 EEST
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

FILE *error_log;

#define die(fmt, args...)                                                      \
  do {                                                                         \
    fprintf(error_log ? error_log : stderr, fmt, ##args);                      \
    fprintf(error_log ? error_log : stderr, "\n");                             \
    fflush(stderr);                                                            \
    exit(-1);                                                                  \
  } while (0)

#define AC(expr, fmt, args...)                                                 \
  do {                                                                         \
    if (!(expr)) {                                                             \
      fflush(stdout);                                                          \
      fprintf(error_log ? error_log : stderr, "%s:%s:%d:", __FILE__,           \
              __FUNCTION__, __LINE__);                                         \
      fprintf(error_log ? error_log : stderr, fmt, ##args);                    \
      fflush(stderr);                                                          \
      exit(-1);                                                                \
    }                                                                          \
  } while (0)

int main(int argc, char *argv[])
{

  error_log = fopen("errors1.txt", "a++");
  /* die("%s", "die"); */
  AC(0, "%s\n", "AC");
  return 0;
}
