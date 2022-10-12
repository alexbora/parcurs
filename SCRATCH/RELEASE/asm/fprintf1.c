/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : fprintf1
 * @created     : Miercuri Oct 12, 2022 11:49:19 EEST
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int *f = malloc(64 * sizeof(int)); // open(dst, O_RDWR);
  write(*f, "test", 4);
  /* fclose(f); */

  return 0;
}
