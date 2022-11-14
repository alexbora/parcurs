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

  int f = open("test.txt", O_CREAT | O_RDWR);

  fd.fd     = f;
  fd.events = POLLIN;

  return EXIT_SUCCESS;
}
