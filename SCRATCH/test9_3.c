/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test9_3
 * @created     : miercuri iul 06, 2022 20:40:38 EEST
 */

#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  char data[] = "Hello!";
  size_t length = strlen(data);

  unsigned char hash[SHA_DIGEST_LENGTH];
  SHA1(data, length, hash);
  // hash now contains the 20-byte SHA-1 hash

  puts(hash);
  return 0;
}
