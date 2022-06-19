/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : main
 * @created     : Luni Mai 23, 2022 19:35:52 EEST
 */

#ifndef MAIN_H
#define MAIN_H

#if 0
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
#endif

#define _GNU_SOURCE

struct Route {
  char    *route;
  unsigned km;
  char    *obs;
};

int  init_time(int argc, char **argv);
void mix(void);
void get_km(char *argv);
int  write_excel(void);
void write_km(void);
void mail_me(const char *attachment);

#define BLOCK_BEGIN {
#define BLOCK_END   }

#ifdef LOG
#include <fcntl.h>
#include <unistd.h>

extern int fd_;
#define INIT_FD  init_fd();
#define CLOSE_FD close_fd();
void init_fd(void);
void close_fd(void);

#define PRINT_(a) write(fd_, a, strlen(a));

#elif defined LOG_VERBOSE
#define INIT_FD
#define CLOSE_FD
#define PRINT_(a) write(2, a, strlen(a));
#else
#define INIT_FD
#define CLOSE_FD
#define PRINT_(a)
#endif

#endif /* end of include guard MAIN_H */
