/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test2
 * @created     : Sâmbătă Oct 01, 2022 18:37:34 EEST
 */

#include <mach/i386/vm_param.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>

#if DEBUG_MODE
#define DEBUG printf
#else
#define DEBUG                                                                  \
  while (0)                                                                    \
  printf
#endif

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/user.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  DEBUG("%d\n", __LINE__);

  printf("%d\n", PAGE_SIZE);
  if (argc < 2) {
    puts("provide args");
    return 0;
  }
  int         fd = open(argv[1], O_RDONLY);
  struct stat fs;
  fstat(fd, &fs);

  /* if (I_ISREG(fs.st_mode)) */
  /* puts("regular\n"); */
  /* else { */
  /* puts("not a file\n"); */
  /* } */

  return 0;
}
