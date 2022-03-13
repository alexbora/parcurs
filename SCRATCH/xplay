/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : play
 * @created     : Miercuri Feb 16, 2022 17:35:14 EET
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COUNT 20
#define RANGE 7

struct Route {
  char* route;
  int km;
  char* obs;
};

int main() {
  struct Route tune[COUNT] = {
      {"Brandy", 1, "obs"},  {"Respect", 2, "obs"}, {"Hey Jude", 3, "obs"},
      {"The Twist", 4},      {"Uptown Funk", 5},    {"Macarena", 6},
      {"Killer Queen", 7},   {"Lady", 0},           {"Foolish Games", 0},
      {"Call Me", 0},        {"Royals", 0},         {"The Sign", 0},
      {"Happy", 0},          {"Billie Jean", 0},    {"My Sharona", 0},
      {"Family Affair", 0},  {"Hurts So Good", 0},  {"Smooth", 0},
      {"Mack The Knife", 0}, {"No One", 0}};

  int frequency[COUNT], recent[COUNT];
  int t, play, cycle = 0, found;

  /* initialize stuff */
  srand((unsigned)time(NULL)); /* seed the randomizer */
  for (t = 0; t < COUNT; t++) {
    /* frequency[t] = 0;      /1* zero frequency counter *1/ */
    recent[t] = COUNT + 1; /* initialize recent buffer */
  }

  /* Randomly play the tunes and keep track */
  while (cycle < COUNT) {
    do {
      play = rand() % COUNT;
      found = 0;
      for (t = 0; t < RANGE; t++)
        if (recent[t] == play) found = 1;
    } while (found);

    /* printf("Playing %d: %s\n", cycle + 1, tune[play].route); */
    /* shift the recent list */
    for (t = COUNT - 1; t > 0; t--) {
      recent[t] = recent[t - 1];
    }
    recent[0] = play;
    /* update frequency array */
    /* frequency[play]++; */
    cycle++;
  }

  int km = 0;
  /* Display frequency list */
  /* puts("Play Frequency:"); */
  for (t = 0; t < COUNT; t++) {
    printf("%d\t%s\t%d\t%s\n", t, tune[t].route, tune[t].km, tune[t].obs);
    km += tune[t].km;
  }
  printf("total: %d\n", km);

  unsigned h, g, k;
  struct Route tmp[COUNT];
  for (g = 0; g < COUNT; g++) {
    for (h = 0; h < RANGE; h++) {
      tmp[h] = tune[h];
    }
    tmp[7] = tune[0];
  }

  for (k = 0; k < COUNT; k++) {
    printf("%d\t%s\n", k, tmp[k].route);
  }

  return (0);
}
