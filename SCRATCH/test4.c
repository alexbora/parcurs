/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test4
 * @created     : miercuri mai 18, 2022 20:09:08 EEST
 */

#include <err.h>
#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int Sys_FileOpenRead(char *path, int *handle) {
  int h;
  struct stat fileinfo;

  h = open(path, O_RDONLY, 0666);
  *handle = h;
  if (h == -1)
    return -1;

  if (fstat(h, &fileinfo) == -1)
    fprintf(stderr, "Error fstating %s", path);

  return fileinfo.st_size;
}

int Sys_FileRead(int handle, void *dest, int count) {
  return read(handle, dest, count);
}

int Sys_FileOpenWrite(char *path) {
  int handle;

  umask(0);

  handle = open(path, O_RDWR | O_CREAT | O_TRUNC, 0666);

  if (handle == -1)
    fprintf(stderr, "Error opening %s: %s", path, strerror(errno));

  return handle;
}

int main(int argc, char *argv[]) {
  FILE *f = open("test", "r++");
  struct stat fileinfo;
  fstat(f, &fileinfo);

  char buf[128];

  Sys_FileRead(handle, buf, 128);
  puts(buf);
  return 0;
}
