#include "cpuflags.h"

#include <cpuid.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

dt_cpu_flags_t dt_detect_cpu_features()
{
  unsigned              ax, bx, cx, dx;
  static dt_cpu_flags_t cpuflags;

  if (__get_cpuid(0x00000000, &ax, &bx, &cx, &dx)) {
    /* Request for standard features */
    if (__get_cpuid(0x00000001, &ax, &bx, &cx, &dx)) {
      if (dx & 0x00800000)
        cpuflags |= CPU_FLAG_MMX;
      if (dx & 0x02000000)
        cpuflags |= CPU_FLAG_SSE;
      if (dx & 0x04000000)
        cpuflags |= CPU_FLAG_SSE2;
      if (dx & 0x00008000)
        cpuflags |= CPU_FLAG_CMOV;

      if (cx & 0x00000001)
        cpuflags |= CPU_FLAG_SSE3;
      if (cx & 0x00000200)
        cpuflags |= CPU_FLAG_SSSE3;
      if (cx & 0x00040000)
        cpuflags |= CPU_FLAG_SSE4_1;
      if (cx & 0x00080000)
        cpuflags |= CPU_FLAG_SSE4_2;

      if (cx & 0x08000000)
        cpuflags |= CPU_FLAG_AVX;
    }

    /* Are there extensions? */
    if (__get_cpuid(0x80000000, &ax, &bx, &cx, &dx)) {
      /* Ask extensions */
      if (__get_cpuid(0x80000001, &ax, &bx, &cx, &dx)) {
        if (dx & 0x80000000)
          cpuflags |= CPU_FLAG_3DNOW;
        if (dx & 0x40000000)
          cpuflags |= CPU_FLAG_3DNOW_EXT;
        if (dx & 0x00400000)
          cpuflags |= CPU_FLAG_AMD_ISSE;
      }
    }
    fprintf(stderr, "\nfound cpuid instruction, dtflags %x", cpuflags);
  }
  return cpuflags;
}

int main()
{
  dt_detect_cpu_features();
  return 0;
}
