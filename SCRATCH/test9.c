/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test9
 * @created     : Miercuri Iun 15, 2022 08:08:23 EEST
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <unistd.h>

#ifdef LOG
static int fd;
#define INIT_FD  init_fd();
#define CLOSE_FD close_fd();

static void init_fd(void)
{
  fd = open("log", O_CREAT | O_APPEND | O_RDWR | O_TRUNC | O_EXLOCK, 0664);
}

static void close_fd(void)
{
  close(fd);
}

#else
#define INIT_FD
#define CLOSE_FD
#define fd 2
#endif

#define PRINT_(a) write(fd, a, strlen(a));

int main()
{
  /* fd = open("log", O_CREAT | O_APPEND | O_RDWR | O_TRUNC, 0666); */
  INIT_FD
  write(fd, "a\n", 2);
  write(fd, "b\n", 2);
  PRINT_("c")
  CLOSE_FD

  return 0;
}
