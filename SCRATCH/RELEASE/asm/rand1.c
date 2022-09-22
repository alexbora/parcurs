/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : rand1
 * @created     : Joi Sep 22, 2022 07:23:55 EEST
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
  int randint;
  int bytes_read;
  int fd = open("/dev/urandom", O_RDONLY);
  if (fd != -1) {
    bytes_read = read(fd, &randint, sizeof(randint));
    if (bytes_read != sizeof(randint)) {
      fprintf(stderr, "read() failed (%d bytes read)\n", bytes_read);
      return -1;
    }
  } else {
    fprintf(stderr, "open() failed\n");
    return -2;
  }
  printf("%08x\n", randint); /* assumes sizeof(int) <= 4 */
  close(fd);
  return 0;
}
