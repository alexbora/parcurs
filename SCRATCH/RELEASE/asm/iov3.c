/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : iov3
 * @created     : Marţi Oct 11, 2022 22:28:30 EEST
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int   fdout = open("iov3.txt", O_RDWR | O_CREAT | O_TRUNC, 0x0640);
  char *dst = mmap(0, 64 * 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, 0);
  memcpy(dst, "test", 4);
  msync(dst, 64, MS_ASYNC);

  /* puts(dst); */

  return 0;
}
