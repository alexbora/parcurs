/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : mmap2
 * @created     : Luni Oct 31, 2022 20:28:18 EET
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{

  int         fd = open("mmap.txt", O_RDONLY);
  struct stat fs;
  fstat(fd, &fs);

  /* IMPORTANT: alignes to pagesize! */
  fs.st_size += fs.st_size & ~(getpagesize() - 1);

  char *x = mmap(0, fs.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);

  printf("%c\n", x[0]);
  printf("%c\n", x[1]);
  return 0;
}
