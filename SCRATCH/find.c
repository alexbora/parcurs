/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : find
 * @created     : luni apr 25, 2022 09:47:53 EEST
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *str = "test";

int find(const char *p) {
  char *pf = strstr(str, p);
  printf("%ld\n", pf - str);
  return (pf) ? (pf - str) : -1;
}

#define MEM_BLOCKSIZE 4096
void *blockmalloc(size_t size) {
  // round up to threshold
  int aloc_size = size % MEM_BLOCKSIZE;
  if (aloc_size)
    size += MEM_BLOCKSIZE - aloc_size;

  printf("%ld\n", size);
  void *b = calloc(1, size + 1);
  return b;
}

int get_length() { return (str) ? strlen(str) : 0; }

typedef struct player_s {
  int x;
} player_t;

int main(int argc, char *argv[]) {
  printf("%d\n", find("st"));

  void *b = blockmalloc(1);

  player_t p1 = {2};
  struct player_s p4 = {1};
  struct player_s {
    int xy;
    int z;
  };

  struct player_s p3 = {1, 2};

  return 0;
}
