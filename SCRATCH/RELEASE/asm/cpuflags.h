typedef enum dt_cpu_flags_t {
  CPU_FLAG_MMX       = 1 << 0,
  CPU_FLAG_SSE       = 1 << 1,
  CPU_FLAG_CMOV      = 1 << 2,
  CPU_FLAG_3DNOW     = 1 << 3,
  CPU_FLAG_3DNOW_EXT = 1 << 4,
  CPU_FLAG_AMD_ISSE  = 1 << 5,
  CPU_FLAG_SSE2      = 1 << 6,
  CPU_FLAG_SSE3      = 1 << 7,
  CPU_FLAG_SSSE3     = 1 << 8,
  CPU_FLAG_SSE4_1    = 1 << 9,
  CPU_FLAG_SSE4_2    = 1 << 10,
  CPU_FLAG_AVX       = 1 << 11
} dt_cpu_flags_t;

dt_cpu_flags_t dt_detect_cpu_features(void);
