/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : opt2
 * @created     : Miercuri Mar 02, 2022 16:54:03 EET
 */

#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define CL_N "\x1B[0m"
#define CL_RED "\x1B[31m"
#define CL_GRN "\x1B[32m"
#define CL_YLW "\x1B[33m"
#define CL_BLU "\x1B[34m"
#define CL_MAG "\x1B[35m"
#define CL_CYN "\x1B[36m"
#define CL_WHT "\x1B[01;37m" /* white */
#define CL_GRY "\x1B[90m"    /* dark gray selectable in putty */

enum {
  LOG_ERR,
  LOG_WARNING,
  LOG_NOTICE,
  LOG_INFO,
  LOG_DEBUG,
  /* custom notices */
  LOG_BLUE = 0x10,
};

int use_colors = 1;

void applog(int prio, const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);

  const char* color = "";
  struct tm tm;

  /* time_t now = time(NULL); */
  localtime_r(&(time_t){time(0)}, &tm);

  switch (prio) {
    case LOG_ERR:
      color = CL_RED;
      break;
    case LOG_WARNING:
      color = CL_YLW;
      break;
    case LOG_NOTICE:
      color = CL_WHT;
      break;
    case LOG_INFO:
      color = "";
      break;
    case LOG_DEBUG:
      color = CL_GRY;
      break;

    case LOG_BLUE:
      prio = LOG_NOTICE;
      color = CL_CYN;
      break;
  }
  if (!use_colors) color = "";

  char* f = malloc(64 + strlen(fmt) + 2);
  sprintf(f, "[%d-%02d-%02d %02d:%02d:%02d]%s %s%s\n", tm.tm_year + 1900,
          tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, color,
          fmt, use_colors ? CL_N : "");
  fprintf(stdout, f, ap); /* atomic write to stdout */
  fflush(stdout);
  free(f);
}

int main(int argc, char* argv[]) {
  char* filename = "test";

  applog(LOG_ERR, "SW_ERR: %s:%d, %s", filename, "line_number", "msg");

  return 0;
}
