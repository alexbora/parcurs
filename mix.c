/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : mix
 * @created     : sâmbătă apr 16, 2022 16:03:13 EEST
 */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef __linux__
#include <sys/_types/_u_int64_t.h>
#include <sys/_types/_ucontext.h>
#endif
#include "main.h"

#include <sys/types.h>
#include <time.h>

#ifdef HAVE_ARC4RANDOM
#define foo4random_uniform() (arc4random_uniform(((unsigned)RAND_MAX + 1)))
#undef rand
#define rand foo4random_uniform
#endif

#ifdef HAVE_OPENSSL
#include <openssl/rand.h>
#undef rand
#define rand ssl_rand
static uint64_t ssl_rand(void) {
  unsigned char bytes[128] = {'\0'};
  RAND_bytes(bytes, sizeof(bytes));
  uint64_t res = *(uint64_t *)bytes;
  return res % RAND_MAX;
}
#endif

struct Route route_[128];

static void random_shuffle(void) {
  static const struct Route parcurs[16] = {
      {"Cluj-Oradea", 321, "Interes Serviciu"},
      {"Cluj-Turda", 121, "Interes Serviciu"},
      {"Cluj-Zalau", 156, "Interes Serviciu"},
      {"Cluj-Baia-Mare", 356, "Interes Serviciu"},
      {"Cluj-Bistrita", 257, "Interes Serviciu"},
      {"Cluj-Dej", 101, "Interes Serviciu"},
      {"Cluj-Cluj", 47, "Interes Serviciu"},
      {"Acasa-Birou", 30, " "},
      {"Acasa-Birou", 30, " "},
      {"Acasa-Birou", 30, " "},
      {"Acasa-Birou", 30, " "},
      {"Acasa-Birou", 30, " "},
      {"Cluj-Cmp. Turzii", 152, "Interes Serviciu"},
      {"Cluj-Apahida", 85, "Interes Serviciu"},
      {"Cluj-Bontida", 92, "Interes Serviciu"},
      {"Cluj-Satu-Mare", 421, "Interes Serviciu"}};

  /* route_                   = (struct Route[128]){{0}}; */
  static const size_t n = ARRAY_SIZE(parcurs);
  static const size_t m = ARRAY_SIZE(route_);

  for (size_t i = 0; i < m; i++) {
    for (size_t j = 0; j < n; j++) {
      route_[i] = parcurs[(unsigned long)rand() % n];
    }
  }

  unsigned long found, play, cycle, k = 0, recent[128] = {0};
  found = play = cycle = k;

  /* static const unsigned route__size = ARRAY_SIZE(route_); */

  for (; cycle < m; cycle++) {
    do {
      play = (unsigned long)rand() % n;
      found = 0;
      for (k = 0; k < n; k++)
        if (recent[k] == play)
          found = 1;
    } while (found);

    route_[cycle] = parcurs[play];
  }
}

static inline int repeating(const struct Route *in) {
  for (unsigned i = 0; i < 32; i++) {
    if (in[i + 1].km == in[i].km && in[i].km != 30)
      return 1;
  }
  return 0;
}

void mix(void) {
  srand((unsigned)time(0));
  do {
    random_shuffle();
  } while (repeating(route_));
}

#ifndef Skipmain
int main() {
  mix();

  /* struct Route *route__ = (struct Route[128]){0}; */

  for (unsigned i = 0; i < 16; ++i) {
    printf("%s\n", route_[i].route);
  }

  return 0;
}
#endif
