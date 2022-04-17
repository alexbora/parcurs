/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : txt2
 * @created     : Duminică Apr 17, 2022 13:56:10 EEST
 */

#include <errno.h>
#include <openssl/rand.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

  return 0;
}
