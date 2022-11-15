/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : main
 * @created     : Duminică Noi 13, 2022 09:42:17 EET
 */

#include <fcntl.h>
#include <poll.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/poll.h>
#include <unistd.h>

#define _GNU_SOURCE

int main(void)
{
  struct pollfd fd;

  int f = open("test.txt", O_TRUNC | O_CREAT | O_RDWR, 0666);

  fd.fd     = f;
  fd.events = POLLIN;

  poll(&fd, 1, 1000);

  if (fd.revents & POLLIN)
    printf("stdin is readable\n");
  if (fd.revents & POLLOUT)
    printf("stdout is writable\n");
  size_t len = 0;
  write(f, "1\n", 2);
  pwrite(f, "2\n", 2, 2);
  close(f);
  return EXIT_SUCCESS;
}
