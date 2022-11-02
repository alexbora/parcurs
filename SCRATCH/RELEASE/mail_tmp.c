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
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define ENC_LEN(_n_) ((_n_ + 2) / 3 * 4)

static inline int upload_m(SSL *s, const char *const filename)
{
  int    fd = open(filename, O_RDONLY);
  size_t file_size;

  /* int         pagesize = getpagesize(); */
  struct stat fs;
  fstat(fd, &fs);
  int in_size = fs.st_size;
  /* in_size += fs.st_size & ~(pagesize - 1); */
  close(fd);

  unsigned char *restrict x = mmap(0, in_size, PROT_READ, MAP_PRIVATE, fd, 0);

  size_t out_size = ENC_LEN(in_size);

  unsigned char *restrict out = mmap(0, out_size, PROT_READ | PROT_WRITE,
                                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  unsigned char *out_ex = malloc(out_size);
  memcpy(out_ex, x, 10);
  memcpy(out, "x", 1);
  memcpy(out, x, 1);
  return 1;

  unsigned char *y = malloc(out_size);

  const int out_len = EVP_EncodeBlock(y, x, file_size);
  return SSL_write(s, y, out_len);
}

int main(void)
{
  upload_m(NULL, "foaie_parcurs_B-151-VGT_octombrie_2022_Alex_Bora.xlsx");
  return 0;
}
