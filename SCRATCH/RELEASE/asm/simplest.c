/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : simplest
 * @created     : Joi Oct 20, 2022 13:31:51 EEST
 */

#include <fcntl.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int fd = open("yyy", O_CREAT | O_RDWR);
  write(fd, "test", 4);
  close(fd);
  return 0;
}
