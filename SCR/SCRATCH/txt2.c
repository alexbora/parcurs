/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : txt2
 * @created     : Duminică Apr 17, 2022 13:56:10 EEST
 */

#include <errno.h>
#include <fcntl.h>
#include <openssl/rand.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <time.h>
#include <unistd.h>

int main()
{
  unsigned char bytes[128] = {'\0'};
  RAND_bytes(bytes, sizeof(bytes));

  /* uint64_t int1 = */
  /* bytes[0] + (bytes[1] << 8) + (bytes[2] << 16) + (bytes[3] << 24); */

  /* printf("%llu\n", int1); */

  uint64_t myInt1 = *(uint64_t *)bytes;
  printf("%lld\n", myInt1 % 10);

  struct tm *tm = localtime(&(time_t){time(0)});
  printf("%d  %d %d\n", tm->tm_mon, tm->tm_year + 1900, tm->tm_wday);

  tm->tm_mon = 11;
  if (tm->tm_mon == 11) {
    /* tm->tm_mon--; */
    tm->tm_year--;
  }
  mktime(tm);

  printf("%d  %d %d\n", tm->tm_mon, tm->tm_year + 1900, tm->tm_wday);

  struct Entropy {
    int   which, q;
    char *t;
  } entropy = {0, 0, "t"};

  char *p = (char *)((size_t)&entropy + 4 * sizeof(int));
  puts("---\n");
  puts(p);

  typedef struct {
    int    a, b;
    double c, d;
  } abcd_s;
  abcd_s list;

  list.b    = 11;
  size_t xx = (size_t)&list + sizeof(int);

  printf("%zu\n", xx);

  typedef struct _st_L3 {
    int e;
    int f;
    int bb[5];
    int g;
  } st_L3;

  st_L3 var;
  int   array[5];   // int_data
  void *pnt = &var; // base_address_of_st_L3

  // using operator `[]`
  memcpy(&((char *)pnt)[offsetof(st_L3, bb)], array, sizeof(int) * 5);

  // using pointer arithmetics
  memcpy(((char *)pnt) + offsetof(st_L3, bb), array, sizeof(int) * 5);

  // one variable at a time
  for (int i = 0; i < 5; ++i)
    memcpy(&((char *)pnt)[offsetof(st_L3, bb) + i], &array[i], sizeof(int));

  int o = open("test22", O_RDWR);

  write(o, "test", 4);
  write(2, "test", 4);

#ifdef LOG
#define ab open("xxx", O_RDWR)
#else
#define ab 2
#endif

  write(ab, "abc\n", 4);
  return 0;
}
