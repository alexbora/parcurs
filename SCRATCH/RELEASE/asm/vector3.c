/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : vector3
 * @created     : Marţi Oct 04, 2022 21:33:39 EEST
 */

#include <emmintrin.h>
#include <stdio.h>
#include <stdlib.h>

static void mul(const __m128i *a, __m128i *b)
{
  __m128i f = _mm_load_si128(a);
  _mm_store_si128(b, f);
}

int main(void)
{

  __m128i a = (__m128i){1, 2};
  __m128i b = (__m128i){0, 0};

  mul(&a, &b);

  fprintf(stderr, "%lld\n", b[0]);

  return 0;
}
