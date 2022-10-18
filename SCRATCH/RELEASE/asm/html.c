/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : html
 * @created     : Luni Oct 17, 2022 17:24:41 EEST
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  fprintf(stderr, "html\n");
  int fd = open("xxx__", O_CREAT | O_RDWR);
  write(fd, "a", 2);
  close(fd);
  return 0;
}
