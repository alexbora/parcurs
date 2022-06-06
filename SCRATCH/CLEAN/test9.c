/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test9
 * @created     : Luni Iun 06, 2022 09:03:08 EEST
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

int main()
{
  FILE *fp = fopen("foaie_parcurs_B-151-VGT_mai_2022_Alex_Bora.xlsx", "rb");

  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  rewind(fp);

  unsigned char *buffer = malloc(sizeof(char) * size);
  /* unsigned char *content = calloc(size + 1, sizeof(char)); */

  /* fread(content, sizeof(char), size, fp); */
  fread(buffer, 1, size, fp);

  printf("%ld = %s\n", size, buffer);
  /* printf("%ld = %s\n", size, content); */

  int fd2 = open("x", O_RDWR | O_CREAT);
  write(fd2, buffer, size);
  close(fd2);

  fclose(fp);
  free(buffer);
  return 0;
}
