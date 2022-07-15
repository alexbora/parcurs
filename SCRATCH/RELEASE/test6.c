/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test6
 * @created     : vineri iul 15, 2022 14:56:21 EEST
 */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd = open("pass", O_RDONLY);
  char x[32];
  read(fd, x, 21);
  puts(x);
  return 0;
}
