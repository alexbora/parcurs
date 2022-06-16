/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test9
 * @created     : Miercuri Iun 15, 2022 08:08:23 EEST
 */

#include "test9.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <unistd.h>

#ifdef LOG
int fd;
void init_fd(void) {
  fd = open("log", O_CREAT | O_APPEND | O_RDWR | O_TRUNC | F_EXLCK, 0664);
}
void close_fd(void) { close(fd); }
#endif

int main() {
  /* fd = open("log", O_CREAT | O_APPEND | O_RDWR | O_TRUNC, 0666); */
  INIT_FD
  write(fd, "a\n", 2);
  write(fd, "b\n", 2);
  PRINT_("c\n")
  PRINT_("d\n")
  f1();
  CLOSE_FD

  return 0;
}
