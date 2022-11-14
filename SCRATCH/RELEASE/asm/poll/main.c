/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : main
 * @created     : Duminică Noi 13, 2022 09:42:17 EET
 */

#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/poll.h>
#include <unistd.h>

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
  write(f, "1\n", 2);

  close(f);
  return EXIT_SUCCESS;
}
