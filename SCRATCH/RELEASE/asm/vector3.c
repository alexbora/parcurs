/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : vector3
 * @created     : Marţi Oct 04, 2022 21:33:39 EEST
 */

#include <emmintrin.h>
#include <stdio.h>
#include <stdlib.h>

static long long volatile mul(const __m128i *a, __m128i *b)
{
  __m128i f = _mm_load_si128(a);
  _mm_store_si128(b, f);
  return b[0][0];
}

static void mul2(void)
{
  __m128i a, b;
  a = _mm_load_si128(&(__m128i){9, 1});
}

int main(void)
{

  __m128i a; // = (__m128i){1, 2};
  __m128i b; //= (__m128i){0, 0};

  mul(&a, &b);

  fprintf(stderr, "%lld\n", b[0]);

  return 0;
}
