/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : sterge10
 * @created     : Miercuri Apr 27, 2022 18:20:48 EEST
 */

#include <immintrin.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmpare()
{
  int32_t __attribute__((aligned(16))) vector1[4] = {1, 2, 3, 4};
  int32_t __attribute__((aligned(16))) vector2[4] = {1, 2, 2, 2};

  __m128i  v1     = _mm_load_si128((__m128i *)vector1);
  __m128i  v2     = _mm_load_si128((__m128i *)vector2);
  __m128i  vcmp   = _mm_cmpeq_epi32(v1, v2);
  uint16_t mask   = _mm_movemask_epi8(vcmp);
  int      result = (mask == 0xffff);
  return result;
}

int main(int argc, char *argv[])
{

  /* normal time */
  struct tm tm = *localtime(&(time_t){time(NULL)});
  /* printf("Today is           %s", asctime(&tm)); */
  printf("Today is           %s", asctime(&*localtime(&(time_t){time(NULL)})));
  tm.tm_mon -= 1; // go previous
  tm.tm_mday = 1; // reset to 1st
  /* tm.tm_mon -= 1; // tm_mon is now outside its normal range */
  mktime(&tm); // tm_isdst is not set to -1; today's DST status is used
  printf("1 month ago was %d - %s", tm.tm_wday, asctime(&tm));

  /* time input */
  struct tm tm2 = {50, 50, 12, 1, 3, 2022};
  mktime(&tm2);
  printf("1 month ago was %d - %s", tm.tm_wday, asctime(&tm));

  struct tm TM = tm;
  TM           = tm2;

  for (unsigned i = 0; i < 7; i++) {
    if (((tm.tm_wday + i) - 6) * tm.tm_wday <= 0)
      puts("hol\n");
    else
      puts("no hol\n");
  }

  printf("%d\n", cmpare());

  return 0;
}
