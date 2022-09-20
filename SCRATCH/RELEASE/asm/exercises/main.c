/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : main
 * @created     : Marţi Iul 05, 2022 18:35:52 EEST
 */

#include "sha1.h"

#include <openssl/evp.h>
#include <openssl/ssl3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xlsxwriter.h>

extern void test1();
extern void test();
int         days(int);

#define x 1

int bs(int y)
{
  int result;
  __asm__("bswap %0" : "=r"(result) : "0"(y));
  return result;
}

int main(int argc, char *argv[])
{

  blk_SHA_CTX   *ctx     = malloc(sizeof(blk_SHA_CTX));
  unsigned char *hashout = malloc(8096);

  const char *in = "text";
  blk_SHA1_Init(ctx);
  blk_SHA1_Update(ctx, in, strlen(in));
  blk_SHA1_Final(hashout, ctx);
  printf("%s\n", hashout);
  printf("%d\n", __builtin_constant_p(x));

  const SSL_METHOD *meth = TLS_method();
  SSL_CTX          *c    = SSL_CTX_new(meth);
  SSL              *s    = SSL_new(c);

  SSL_set_cipher_list(s,
                      "RC4-MD5:RC4-SHA:AES128-SHA:AES256-SHA:HIGH:!DSS:!aNULL");

  printf("%s\n", SSL_get_cipher_list(s, 2));

  /* fprintf(stderr, "Connected with %s\n%s%s\n", SSL_get_cipher(s), */
  /* SSL_get_cipher_name(s), SSL_get_cipher_version(s)); */

  int y = 1;
  printf("%d\n", __builtin_constant_p(y));

  printf("%d\n", bs(y));
  printf("%llu\n", 0x0000000000ff0000ULL);
  printf("1 %d\n", 0xff000000);
  printf("2 %d\n", 0x00ff0000);

  char       *dest = malloc(16);
  const char *src  = "test";

  lxw_strcpy(dest, src);
  puts(dest);

  for (int i = 0; i < 7; ++i)
    printf("%d - %d\n", i, (i % 6) == 0);

  /* test(); */
  /* days(atoi(argv[1])); */

  return EXIT_SUCCESS;
}
