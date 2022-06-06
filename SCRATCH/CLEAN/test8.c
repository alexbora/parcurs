/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test8
 * @created     : Duminică Iun 05, 2022 20:41:58 EEST
 */

#include <fcntl.h>
#include <openssl/evp.h>
#include <openssl/ssl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{

  FILE *file;
  /* char *file_name = "foaie_parcurs_B-151-VGT_mai_2022_Alex_Bora.xlsx"; */
  char *file_name = "km";
  file            = fopen(file_name, "r+b");
  char buffer[4096];

  while (fread(buffer, sizeof *buffer, 4096, file) == 4)
    ;
  puts(buffer);

  struct stat sz;
  int         fd = open(file_name, O_RDONLY);
  fstat(fd, &sz);
  printf("%llu\n", sz.st_size);

  int length = lseek(fd, 0, SEEK_END) + 1;
  printf("%d\n", length);
  rewind(file);

  fseek(file, 0, SEEK_END); // seek to end of file
  int size = ftell(file);   // get current file pointer
  fseek(file, 0, SEEK_SET); // seek back to beginning of file
  // proceed with allocating memory and reading the file
  printf("%d\n", size);

  char *tmp = malloc(length);
  scanf(tmp, "%d", file);
  fread(tmp, sz.st_size, 1, file);
  puts(tmp);

  FILE *f2 = fopen("x", "w++");
  fprintf(f2, "%d", 1);
  fclose(f2);

  int         fd2 = open(file_name, O_RDONLY);
  struct stat st;
  fstat(fd2, &st);
  uint8_t *byte_ptr =
      mmap(NULL, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  uint8_t byte = byte_ptr[0];
  printf("%d\n", byte);
  return 0;
}
