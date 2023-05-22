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
#include <sys/mman.h>
#include <unistd.h>

int
main()
{
  char   buff[1024];
  size_t nread;

#ifdef _MSC_VER
  _set_fmode(_O_BINARY); // default to binary I/O
#endif

  /* FILE* fd1 = fopen("test.mp3", "rb++"); */
  /* FILE* fd2 = fopen("test_copy.mp3", "wb++"); */

  while ((nread = fread(buff, 1, sizeof buff, stdin)) != 0) {
    if (fwrite(buff, 1, nread, stdout) != nread) {
      fprintf(stderr, "error writing to stdout: %s\n", strerror(errno));
      return 1;
    }
  }

  /* fclose(fd1); */
  /* fclose(fd2); */

  /*   char*  data; */
  int    fd = open("excel2.c", O_RDONLY);
  size_t sz = lseek(fd, 0, SEEK_END);
  lseek(fd, 0, fd);
  /* size_t page_size = getpagesize(); */
  /*   /1* ftruncate(fd, page_size); *1/ */

  /*   data = mmap(NULL, sz, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0); */
  /*   if (data == MAP_FAILED) */
  /*     puts("failed\n"); */
  /*   else { */
  /*     for (unsigned long i = 0; i < 10; i++) { printf("[%lu]=%X ", i,
   * data[i]); } */
  /*     printf("\n"); */
  /*   } */

  /*   int fd3 = open("test4.mp3", O_WRONLY | O_CREAT, 0666); */
  /*   write(fd3, data, sz); */
  /*   close(fd3); */
  /*   munmap(data, sz); */
  return 0;
}
