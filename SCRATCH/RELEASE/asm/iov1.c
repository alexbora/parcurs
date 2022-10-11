/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : iov1
 * @created     : Marţi Oct 11, 2022 17:56:26 EEST
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_iovec_t.h>
#include <sys/fcntl.h>
#include <sys/uio.h>
#include <unistd.h>

int main(void)
{

  int fd = open("test.txt", O_RDONLY);

  char buf[1024 * 2];

  struct iovec io[4];

  io[0].iov_base = buf;
  io[1].iov_base = buf;
  io[2].iov_base = buf;
  io[3].iov_base = buf;

  io[0].iov_len = 1024 * 2;

  readv(fd, io, 3);
  /* puts(buf[2]); */
  /* for (int i = 0; i < 3; i++) */
  /* printf("%s", (char *)io[i].iov_base); */
  /* printf(" ----------- %s\n", buf + 0); */
  /* printf(" ----------- %s\n", buf); */

  /* for (int i = 0; i < 3; ++i) { */
  /* puts(buf[i]); */
  /* } */

  fd = open("test.txt", O_RDONLY);
  char         foo[1024 / 4], bar[1024 / 4], baz[1024 / 4], zet[1024 / 4];
  struct iovec i2[4] = {
      {foo, 1024 / 4}, {bar, 1024 / 4}, {baz, 1024 / 4}, {zet, 1024 / 4}};
  readv(fd, i2, 4);

  for (int i = 0; i < 4; i++) {
    /* printf("%d: %s", i, (char *)i2[i].iov_base); */
    memcpy(buf + (i * 1024 / 4), i2[i].iov_base, 1024 / 4);
  }
  puts("-----------------\n");
  puts(buf);
  puts("-----------------\n");

  return 0;
}
