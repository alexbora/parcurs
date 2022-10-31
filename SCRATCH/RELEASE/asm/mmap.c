/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : mmap
 * @created     : Luni Oct 31, 2022 18:35:07 EET
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int
main(int argc, char* argv[])
{

  int fd = creat("mmap.txt", 0777);
  fd     = open("mmap.txt", O_CREAT | O_RDWR);
  struct stat f;
  fstat(fd, &f);

  int* x =
      mmap(0, f.st_size, PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED, fd, 0);
  write(*x, "1", 1);

  msync(x, f.st_size, MS_ASYNC);
  munmap(x, f.st_size);
  close(fd);
  return 0;
}
