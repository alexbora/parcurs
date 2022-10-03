/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : vector1
 * @created     : Luni Oct 03, 2022 16:57:17 EEST
 */

#include <emmintrin.h>
#include <immintrin.h>
#include <mmintrin.h>
#include <stdalign.h>
#include <stdio.h>
#include <stdlib.h>
#include <xmmintrin.h>

int main(int argc, char *argv[]) {
  __m128i arr;
  alignas(16) const float x[10] = {2};
  arr = _mm_loadu_ps(x);

  __m128i y = {1, 2};

  return 0;
}
