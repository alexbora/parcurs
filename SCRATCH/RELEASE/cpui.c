static inline void cpuid(int reg[4], int id) {
      #if defined (_MSC_VER) //|| defined (__INTEL_COMPILER)
  __cpuidex(reg, id, 0);
      #elif defined(__i386__) || defined(__x86_64__)
  __asm("cpuid" : "=a"(reg[0]),"=b"(reg[1]),"=c"(reg[2]),"=d"(reg[3]) : "a"(id),"c"(0) : );
      #endif
}
static inline void cpuid(int reg[4], int id) {
      #if defined (_MSC_VER) //|| defined (__INTEL_COMPILER)
  __cpuidex(reg, id, 0);
      #elif defined(__i386__) || defined(__x86_64__)
  __asm("cpuid" : "=a"(reg[0]),"=b"(reg[1]),"=c"(reg[2]),"=d"(reg[3]) : "a"(id),"c"(0) : );
      #endif
}
static inline void cpuid(int reg[4], int id) {
      #if defined (_MSC_VER) //|| defined (__INTEL_COMPILER)
  __cpuidex(reg, id, 0);
      #elif defined(__i386__) || defined(__x86_64__)
  __asm("cpuid" : "=a"(reg[0]),"=b"(reg[1]),"=c"(reg[2]),"=d"(reg[3]) : "a"(id),"c"(0) : );
      #endif
}
 9:22  up 6 days, 15:47, 7 users, load averages: 18,97 18,77 10,14
USER     TTY      FROM              LOGIN@  IDLE WHAT
alex     console  -                Dum17   6days -
alex     s000     -                Dum17   17:37 vim main.c
alex     s001     -                Dum22   14:58 vim sterge.c
alex     s002     -                Lun20   17:37 vim encode.c
alex     s003     -                Mar17       - w
alex     s004     -                Mar20   14:58 vim Makefile +75
alex     s005     -                Vin23   33:48 zsh
