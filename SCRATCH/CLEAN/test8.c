/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test8
 * @created     : Duminică Iun 05, 2022 20:41:58 EEST
 */

#include <openssl/evp.h>
#include <openssl/ssl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{

  FILE *file;
  char *file_name = "foaie_parcurs_B-151-VGT_mai_2022_Alex_Bora.xlsx";
  file            = fopen(file_name, "r+b");
  char buffer[4096];

  while (fread(buffer, sizeof *buffer, 4096, file) == 4)
    ;
  puts(buffer);

#define BUFSIZE BUFSIZ
  int           num_bytes_read;
  int           cipher_block_size = 4096;
  unsigned char in_buf[BUFSIZE], out_buf[BUFSIZE + cipher_block_size];
  FILE         *ifp = file;

  while (1) {
    num_bytes_read = fread(in_buf, sizeof(unsigned char), BUFSIZE, ifp);
    if (num_bytes_read == BUFSIZE)
      break;
  }

  num_bytes_read = fread(in_buf, sizeof(unsigned char), BUFSIZE, ifp);

  puts(in_buf);

  return 0;
}
