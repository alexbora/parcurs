/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : mix
 * @created     : sâmbătă apr 16, 2022 16:03:13 EEST
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

static struct Route {
  char *route;
  float km;
  char *obs;
} tmp[128];

static void random_shuffle(void) {
  struct Route parcurs[16] = {{"Cluj-Oradea", 321, "Interes Serviciu"},
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

  static const size_t n = sizeof(parcurs) / sizeof(parcurs[0]);

  for (unsigned i = 0; i < 128; i++) {
    for (unsigned j = 0; j < n; j++) {
      tmp[i] = parcurs[(unsigned long)rand() % n];
    }
  }

  unsigned found, play, cycle, k = 0, recent[128] = {0};
  found = play = cycle = k;

  static const unsigned tmp_size = sizeof(tmp) / sizeof(tmp[0]);

  for (; cycle < tmp_size; cycle++) {
    do {
      play = rand() % n;
      found = 0;
      for (k = 0; k < n; k++)
        if (recent[k] == play)
          found = 1;
    } while (found);

    tmp[cycle] = parcurs[play];
  }
}

static int repeating(struct Route *in) {
  for (unsigned i = 0; i < 32; i++) {
    if (in[i + 1].km == in[i].km && in[i].km != 30)
      return 1;
  }
  return 0;
}

static void mix(struct Route *in) {
  srand(time(0));
  do {
    random_shuffle();
  } while (repeating(tmp));
}

#ifndef Skipmain
int main(int argc, char *argv[]) {
  mix(tmp);

  for (unsigned i = 0; i < 32; ++i) {
    printf("%s\n", tmp[i].route);
  }

  return 0;
}
#endif
