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
int  mail_me(const char *attachment);

#define BLOCK_BEGIN {
#define BLOCK_END   }

#ifdef LOG
static int fd_;
#define INIT_FD  init_fd();
#define CLOSE_FD close_fd();

static void init_fd(void)
{
  fd_ = open("log", O_CREAT | O_APPEND | O_RDWR | O_TRUNC | O_EXLOCK, 0664);
}

static void close_fd(void)
{
  close(fd_);
}

#else
#define INIT_FD
#define CLOSE_FD
#define fd_ 2
#endif

#define PRINT_(a) write(fd_, a, strlen(a));

#endif /* end of include guard MAIN_H */
