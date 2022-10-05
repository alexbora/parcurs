/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : stop
 * @created     : Miercuri Oct 05, 2022 20:11:23 EEST
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int error_mode;

FILE *error_log;

#define Stopif(assertion, error_action, ...)                                   \
  {                                                                            \
    if (assertion) {                                                           \
      fprintf(error_log ? error_log : stderr, __VA_ARGS__);                    \
      fprintf(error_log ? error_log : stderr, "\n");                           \
      if (error_mode == 's')                                                   \
        abort();                                                               \
      else {                                                                   \
        error_action;                                                          \
      }                                                                        \
    }                                                                          \
  }

int main(int argc, char *argv[])
{
  error_mode = 's';
  int x      = 0;
  Stopif(x == 0, return 0,
         "x has value %i, but it should be between zero and one.", x);
  return 0;
}
