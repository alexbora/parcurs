#include <immintrin.h>

size_t _tb64v256enc(const unsigned char* in, size_t inlen, unsigned char *out) {
  const unsigned char *ip = in; 
        unsigned char *op = out;
        size_t   outlen = TB64ENCLEN(inlen);
  if(outlen >= 32+4) { 
    const __m256i    shuf = _mm256_set_epi8(10,11, 9,10, 7, 8, 6, 7, 4,   5, 3, 4, 1, 2, 0, 1,
                                            10,11, 9,10, 7, 8, 6, 7, 4,   5, 3, 4, 1, 2, 0, 1);

    for(; op <= (out+outlen)-32; op += 32, ip += (32/4)*3) {
      __m256i v0 = _mm256_castsi128_si256(    _mm_loadu_si128((__m128i *) ip));      
              v0 = _mm256_inserti128_si256(v0,_mm_loadu_si128((__m128i *)(ip+12)),1);   
      v0 = _mm256_shuffle_epi8(v0, shuf); v0 = mm256_unpack6to8(v0); v0 = mm256_map6to8(v0);                                                                                                           
      _mm256_storeu_si256((__m256i*) op,     v0);                                            
    }
  }
  if(op <= (out+outlen)-(16+4)) {
    const __m128i    shuf = _mm_set_epi8(10,11, 9,10, 7, 8, 6, 7, 4,   5, 3, 4, 1, 2, 0, 1);

    __m128i v0 = _mm_loadu_si128((__m128i*)ip);
            v0 = _mm_shuffle_epi8(v0, shuf);
            v0 = mm_unpack6to8(v0);
            v0 = mm_map6to8(v0);
    _mm_storeu_si128((__m128i*) op, v0);                                          
    op += 16; ip += (16/4)*3;
  }
  EXTAIL();
  return outlen;
}
