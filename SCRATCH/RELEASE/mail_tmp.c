/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : mail_tmp
 * @created     : Miercuri Noi 02, 2022 06:58:14 EET
 */

#include <fcntl.h>
#include <openssl/ssl3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define ENC_LEN(_n_) ((_n_ + 2) / 3 * 4)

static inline int upload_m(SSL *s, const char *const filename)
{
  int    fd = open(filename, O_RDWR);
  size_t file_size;

  int         pagesize = getpagesize();
  struct stat fs;
  fstat(fd, &fs);
  int in_size = fs.st_size;
  in_size += fs.st_size & ~(pagesize - 1);
  close(fd);
  size_t out_size = ENC_LEN(in_size);

  int dst = open("map2.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  ftruncate(dst, out_size);

  unsigned char *x = mmap(0, in_size, PROT_READ, MAP_PRIVATE, fd, 0);
  unsigned char *out =
      mmap(0, out_size, PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  /* unsigned char *out_ex = malloc(out_size); */
  /* memcpy(out_ex, x, 10); */
  /* puts("out_ex x works"); */
  /* memcpy(out, "x", 1); */
  /* puts("out \'x' works"); */
  memcpy(out, x, in_size);
  msync(out, out_size, MS_SYNC);
  munmap(x, in_size);
  munmap(out, out_size);
  puts("out x works");

  const int _len = EVP_EncodeBlock(out, x, file_size);
  /* return SSL_write(s, y, out_len); */
  return 0;
}

int main(void)
{
  /* upload_m(NULL, "foaie_parcurs_B-151-VGT_octombrie_2022_Alex_Bora.xlsx"); */
  printf("%lu\t%lu\n", sizeof(int), sizeof(int32_t));
  int   f  = open("seek", O_RDONLY);
  int   sz = lseek(f, 0, SEEK_END);
  FILE *ff = fopen("seek", "r");
  fseek(ff, 0, SEEK_END);
  int szz = ftell(ff);

  printf("%d --- %d\n", sz, szz);
  return 0;
}
