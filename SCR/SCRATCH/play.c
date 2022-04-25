/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : play
 * @created     : Miercuri Feb 16, 2022 17:35:14 EET
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

/* #include <xlsxwriter.h> */
#define COUNT 20
#define RANGE 7

struct Route {
  char* route;
  int km;
  char* obs;
};

int** res() {
  int cycle, play, found, t;
  int** recent = malloc(32 * sizeof(int));
  while (cycle < COUNT) {
    do {
      play = rand() % COUNT;
      found = 0;
      for (t = 0; t < RANGE; t++)
        if (*recent[t] == play) found = 1;
    } while (found);

    /* printf("Playing %d: %s\n", cycle + 1, tune[play].route); */
    /* shift the recent list */
    for (t = COUNT - 1; t > 0; t--) {
      recent[t] = recent[t - 1];
    }
    *recent[0] = play;
    /* update frequency array */
    /* frequency[play]++; */
    cycle++;
  }
  return recent;
}

void shuffle1() { printf("shuffle 1\n"); }
void shuffle2() { printf("shuffle 2\n"); }

int main() {
  struct Route tune[COUNT] = {
      {"Brandy", 1, "obs"},         {"Respect", 2, "obs"},
      {"Hey Jude", 3, "obs"},       {"The Twist", 4, "obs"},
      {"Uptown Funk", 5, "obs"},    {"Macarena", 6, "obs"},
      {"Killer Queen", 7, "obs"},   {"Lady", 0, "obs"},
      {"Foolish Games", 0, "obs"},  {"Call Me", 0, "obs"},
      {"Royals", 0, "obs"},         {"The Sign", 0, "obs"},
      {"Happy", 0, "obs"},          {"Billie Jean", 0, "obs"},
      {"My Sharona", 0, "obs"},     {"Family Affair", 0, "obs"},
      {"Hurts So Good", 0, "obs"},  {"Smooth", 0, "obs"},
      {"Mack The Knife", 0, "obs"}, {"No One", 0, "obs"}};

  /* int frequency[COUNT]; */
  int recent[COUNT];
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

  /* int k; */
  struct Route tmp[COUNT];

  /* int y = RANGE; */
  /* for (int i = 0; i < y; i++) { */
  /*   tmp[i] = tune[i]; */
  /* } */

  /* for (int i = y - 1, j = 0; j < RANGE; i++, j++) { */
  /*   tmp[i] = tune[j]; */
  /*   y++; */
  /* } */

  /* for (int i = y - 1, j = 0; j < y; i++, j++) { */
  /*   tmp[i] = tune[j]; */
  /* } */

  /* for (k = 0; k < COUNT; k++) { */
  /*   printf("%d\t%s\n", k, tmp[k].route); */
  /* } */

  int arr1[6], arr2[3] = {1, 2, 3};

  int iSource = 0;
  for (int i = 0; i < 6; i++) {
    if (iSource >= 3) {
      iSource = 0;  // reset if at end of source
    }
    arr1[i] = arr2[iSource++];
  }

  for (int i = 0; i < COUNT; i++) {
    if (iSource >= RANGE) {
      iSource = 0;  // reset if at end of source
      shuffle1();
    }
    tmp[i] = tune[iSource++];
    shuffle2();
  }

  for (unsigned i = 0; i < 6; i++) {
    printf("%d\n", arr1[i]);
  }
  puts("\n\n");

  for (unsigned i = 0; i < COUNT; i++) {
    printf("%s\n", tmp[i].route);
  }

  char dir[32];
  const char* month = "ianuarie";
  const int year = 2022;
  sprintf(dir, "%s_%d", month, year);
  mkdir(dir, S_IRWXU);

  return (0);
}
