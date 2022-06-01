/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : main
 * @created     : Luni Mai 23, 2022 19:35:52 EEST
 */

#ifndef MAIN_H
#define MAIN_H

#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define STDERR stderr,
#define log_error(message)                                                     \
  fprintf(STDERR "[ERROR][%s:%d]: " message "\n", __FILE__, __LINE__)

#define BLOCK_BEGIN {
#define BLOCK_END   }

static inline void log_debug(char *file, char *fmt, ...)
{
  va_list     argptr     = {0};
  static char data[1024] = {'\0'};
  int         fd         = 0;

  va_start(argptr, fmt);
  vsprintf(data, fmt, argptr);
  va_end(argptr);
  fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
  write(fd, data, strlen(data));
  close(fd);
}

struct Route {
  char    *route;
  unsigned km;
  char    *obs;
};

#endif /* end of include guard MAIN_H */
