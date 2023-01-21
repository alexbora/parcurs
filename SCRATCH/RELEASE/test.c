size_t tb64v256enc(const unsigned char *__restrict in, size_t inlen, unsigned char *__restrict out) {
  const unsigned char *ip = in; 
        unsigned char *op = out;
            size_t outlen = TB64ENCLEN(inlen);
  #define EN 256
       const __m256i shuf = _mm256_set_epi8(10,11, 9,10, 7, 8, 6, 7, 4,   5, 3, 4, 1, 2, 0, 1,
                                            10,11, 9,10, 7, 8, 6, 7, 4,   5, 3, 4, 1, 2, 0, 1);
  if(outlen > 64+128) {
      __m256i u0 = _mm256_castsi128_si256(    _mm_loadu_si128((__m128i *) ip    )  );   
              u0 = _mm256_inserti128_si256(u0,_mm_loadu_si128((__m128i *)(ip+12)),1);   
      __m256i u1 = _mm256_castsi128_si256(    _mm_loadu_si128((__m128i *)(ip+24))  );      
              u1 = _mm256_inserti128_si256(u1,_mm_loadu_si128((__m128i *)(ip+36)),1);   
    for(; op < (out+outlen)-(64+EN); op += EN, ip += EN*3/4) {
      ES256(0); 
	    #if EN > 128
	  ES256(1);
	    #endif
	  PREFETCH(ip, 384, 0);
    }
	  #if EN > 128
    if(op < (out+outlen)-(64+128)) { ES256(0); op += 128; ip += 128*3/4; }
      #endif	
  }  
  for(; op < out+outlen-32; op += 32, ip += 32*3/4) {
    __m256i v = _mm256_castsi128_si256(   _mm_loadu_si128((__m128i *) ip    )  );      
            v = _mm256_inserti128_si256(v,_mm_loadu_si128((__m128i *)(ip+12)),1);   
            v = _mm256_shuffle_epi8(v, shuf); v = mm256_unpack6to8(v); v = mm256_map6to8(v);                                                                                                           
                _mm256_storeu_si256((__m256i*) op, v);                                                 
  }
  /*for(; op <= (out+outlen)-16; op += 16, ip += (16/4)*3) {
    const __m128i    shuf = _mm_set_epi8(10,11, 9,10, 7, 8, 6, 7, 4,   5, 3, 4, 1, 2, 0, 1);
    __m128i v0 = _mm_loadu_si128((__m128i*)ip);
            v0 = _mm_shuffle_epi8(v0, shuf);
            v0 = mm_unpack6to8(v0);
            v0 = mm_map6to8(v0);
    _mm_storeu_si128((__m128i*) op, v0);                                          
  }*/
  EXTAIL();
  return outlen;
}
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
#define TB64ENCLEN(_n_) ((_n_ + 2)/3 * 4)

#define EXTAIL() for(; op < (out+outlen)-4; op += 4, ip += 3) { unsigned _u = BSWAP32(ctou32(ip)); stou32(op, XU32(_u)); } ETAIL()

#define BSWAP32(a) bswap32(a)
#define bswap32(x) __builtin_bswap32(x)
#define stou32(_cp_, _x_) (*(unsigned       *)(_cp_) = _x_)
#define XU32(_u_) (tb64lute[(_u_ >>  8) & 0xfff] << 16 |\
                   tb64lute[ _u_ >> 20])

#define ETAIL()\
  unsigned _l = (in+inlen) - ip; \
       if(_l == 3) { unsigned _u = ip[0]<<24 | ip[1]<<16 | ip[2]<<8; stou32(op, SU32(_u)); op+=4; }\
  else if(_l == 2) { op[0] = tb64lutse[(ip[0]>>2)&0x3f]; op[1] = tb64lutse[(ip[0] & 0x3) << 4 | (ip[1] & 0xf0) >> 4]; op[2] = tb64lutse[(ip[1] & 0xf) << 2]; op[3] = '='; op+=4; }\
  else if(_l)      { op[0] = tb64lutse[(ip[0]>>2)&0x3f]; op[1] = tb64lutse[(ip[0] & 0x3) << 4],                       op[2] = '=';                           op[3] = '='; op+=4; }
  
#define SU32(_u_) (tb64lutse[(_u_>> 8) & 0x3f] << 24 |\
                   tb64lutse[(_u_>>14) & 0x3f] << 16 |\
                   tb64lutse[(_u_>>20) & 0x3f] <<  8 |\
                   tb64lutse[(_u_>>26) & 0x3f])

extern unsigned char tb64lutse[];

#define ES256(_i_) {\
  __m256i v0 = _mm256_castsi128_si256(    _mm_loadu_si128((__m128i *)(ip+48+_i_*96+ 0))  );\
          v0 = _mm256_inserti128_si256(v0,_mm_loadu_si128((__m128i *)(ip+48+_i_*96+12)),1);\
  __m256i v1 = _mm256_castsi128_si256(    _mm_loadu_si128((__m128i *)(ip+48+_i_*96+24))  );\
          v1 = _mm256_inserti128_si256(v1,_mm_loadu_si128((__m128i *)(ip+48+_i_*96+36)),1);\
                                                                                           \
  u0 = _mm256_shuffle_epi8(u0, shuf); u0 = mm256_unpack6to8(u0); u0 = mm256_map6to8(u0);\
  u1 = _mm256_shuffle_epi8(u1, shuf); u1 = mm256_unpack6to8(u1); u1 = mm256_map6to8(u1);\
       _mm256_storeu_si256((__m256i*)(op+_i_*128),    u0);                              \
       _mm256_storeu_si256((__m256i*)(op+_i_*128+32), u1);                              \
		                                                                                   \
          u0 = _mm256_castsi128_si256(    _mm_loadu_si128((__m128i *)(ip+48+_i_*96+48))  );\
          u0 = _mm256_inserti128_si256(u0,_mm_loadu_si128((__m128i *)(ip+48+_i_*96+60)),1);\
          u1 = _mm256_castsi128_si256(    _mm_loadu_si128((__m128i *)(ip+48+_i_*96+72))  );\
          u1 = _mm256_inserti128_si256(u1,_mm_loadu_si128((__m128i *)(ip+48+_i_*96+84)),1); \
                                                                                           \
  v0 = _mm256_shuffle_epi8(v0, shuf); v0 = mm256_unpack6to8(v0); v0 = mm256_map6to8(v0);\
  v1 = _mm256_shuffle_epi8(v1, shuf); v1 = mm256_unpack6to8(v1); v1 = mm256_map6to8(v1); \
       _mm256_storeu_si256((__m256i*)(op+_i_*128+64), v0);\
       _mm256_storeu_si256((__m256i*)(op+_i_*128+96), v1);\
}
#define PREFETCH(_ip_,_i_,_rw_) __builtin_prefetch(_ip_+(_i_),_rw_)

#include <immintrin.h>

