/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : vector1
 * @created     : Luni Oct 03, 2022 16:57:17 EEST
 */

#include <immintrin.h>
#include <stdalign.h>

int main(int argc, char *argv[])
{
  /* __m128i                 arr; */
  /* alignas(16) const float x[10] = {2}; */
  /* arr                           = _mm_loadu_ps(x); */

  __m128i y = {1, 2};

  /* union { */
  /*   alignas(16) int x[2]; */
  /*   __m128i v; */
  /* } u; */

  /* u.v = (__m128i){1, 2}; */
  /* printf("%d\n", u.x[0]); */

  /* __m128i v2 = {3, 4}; */
  /* printf("%lld\n", v2[0]); */

  alignas(16) union {
    alignas(16) long long z[4];
    __m128i v3[2];
  } u2;

  /* u2.v3[0] = (__m128i){1, 7}; */
  /* u2.v3[1] = (__m128i){2, 6}; */
  printf("%lld\n", u2.z[2]);

  return 0;
}
