/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : copy_test
 * @created     : Luni Mai 22, 2023 12:47:48 EEST
 */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <unistd.h>

int
main()
{
  char   buff[1024];
  size_t nread;

#ifdef _MSC_VER
  _set_fmode(_O_BINARY); // default to binary I/O
#endif

  FILE* fd1 = fopen("test.mp3", "rb++");
  FILE* fd2 = fopen("test_copy.mp3", "wb++");

  while ((nread = fread(buff, 1, sizeof buff, stdin)) != 0) {
    if (fwrite(buff, 1, nread, stdout) != nread) {
      fprintf(stderr, "error writing to stdout: %s\n", strerror(errno));
      return 1;
    }
  }

  fclose(fd1);
  fclose(fd2);

  return 0;
}
