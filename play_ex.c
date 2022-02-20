/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : play
 * @created     : Miercuri Feb 16, 2022 17:35:14 EET
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
/* #include <xlsxwriter.h> */
#include <stdbool.h>
static inline int isholiday(const int day, const int month, const int year) {
  struct tm tm = {.tm_year = year - 1900,
                  .tm_mon = month - 1,
                  .tm_mday = day,
                  .tm_isdst = -1};
  mktime(&tm);
  static const struct {
    int day, mon;
  } hol[] = {{1, 1},  {2, 1},   {24, 1}, {30, 4},  {1, 5},
             {2, 5},  {3, 5},   {1, 6},  {20, 6},  {21, 6},
             {15, 8}, {30, 11}, {1, 12}, {25, 12}, {26, 12}};
  if (tm.tm_wday == 0 || tm.tm_wday == 6) return 1;
  size_t size = (sizeof(hol) / sizeof(hol[0]));
  for (size_t i = 0; i < size; i++)
    if (day == hol[i].day && month == hol[i].mon) return 1;
  return 0;
}

#define TOTAL 32
#define COUNT 20
#define RANGE 7

struct Route {
  char* route;
  int km;
  char* obs;
};

void shuffle1(void) { printf("shuffle 1\n"); }
void shuffle2(void) { printf("shuffle 2\n"); }

static inline void shuffle(int* pattern, const int n) {
  int i;
  for (i = 0; i < n; i++) {
    pattern[i] = i;
  }
  for (i = n - 1; i > 0; i--) {
    int j;
    j = rand() % (i + 1);
    if (j != i) {
      int swap;
      swap = pattern[j];
      pattern[j] = pattern[i];
      pattern[i] = swap;
    }
  }
}

bool repeating(struct Route in[]) {
  for (unsigned i = 0; i < TOTAL; i++) {
    if (in[i + 1].km == in[i].km && in[i].km != 0) return true;
  }
  return false;
}

void generate_struct(struct Route in[]) {
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

  int recent[COUNT] = {};
  int t, play, cycle = 0, found;

shuffle:
  while (cycle < COUNT) {
    do {
      play = rand() % COUNT;
      found = 0;
      for (t = 0; t < RANGE; t++)
        if (recent[t] == play) found = 1;
    } while (found);

    for (t = COUNT - 1; t > 0; t--) {
      recent[t] = recent[t - 1];
    }
    recent[0] = play;
    cycle++;
  }

  struct Route tmp[TOTAL] = {};
  int iSource = 0;
  for (int i = iSource; i < COUNT; i++) {
    if (iSource >= RANGE) {
      iSource = 0;  // reset if at end of source
    }
    tmp[i] = tune[recent[i]];
  }

  if (repeating(tmp)) goto shuffle;

  for (unsigned i = 0; i < TOTAL; i++) {
    in[i] = tmp[i];
  }
}

struct Write_Data {
  void* data;
  void (*func)(void);
};

void validate_data(struct Write_Data in[], struct Route route[]) {
  struct Write_Data tmp[COUNT];
  for (unsigned i = 0; i < COUNT; i++) {
    if (isholiday(i, 1, 2000)) {
      tmp[i].data = NULL;
      tmp[i].func = &shuffle2;
    } else {
      tmp[i].data = (struct Route*)route + i;
      tmp[i].func = &shuffle1;
    }
  }
  for (unsigned i = 0; i < COUNT; i++) {
    in[i] = tmp[i];
  }
}

void func1(struct Route in[]) {
  static int i = 0;
  printf("%s\n", in[i].route);
  i++;
  /* for (unsigned i = 0; i < COUNT; i++) printf("%s\n", in[i].route); */
}
void func2(struct Route in[]) { puts("---\n"); }

int main() {
  /* varianta 1 */
  /* openssl style */
  struct Route out[TOTAL];
  struct Write_Data data[COUNT];
  do {
    generate_struct(out);
  } while (repeating(out));
  validate_data(data, out);

  puts("\nvarianta 1");
  for (unsigned i = 0; i < COUNT; i++) {
    printf("%s\n", out[i].route);
    data[i].func();
  }

  /* varianta 2 */
  puts("\nvarianta 2");
  void (*fp[COUNT])(struct Route[]);
  for (unsigned i = 0; i < COUNT; i++) {
    if (isholiday(i, 1, 2022))
      fp[i] = &func2;
    else {
      fp[i] = &func1;
    }
  }

  for (unsigned i = 0; i < COUNT; i++) {
    fp[i](out);
  }

  /* varianta 3 */
  /* probabil cea mai buna */
  /* shoot the ducks,  simply zero the array elements that are either holiday or
   * vacation,  the write function will write null,  or blank,  or "" */
  puts("\nvarianta 3");
  struct Final {
    char *route, km[4], *obs;
  } final[TOTAL];
  for (unsigned i = 0; i < TOTAL; i++) {
    if (isholiday(i, 2, 2022)) out[i] = (struct Route){"---\n", 0, NULL};
  }
  /* core is above */
  for (unsigned i = 0; i < TOTAL; i++) {
    final[i].route = out[i].route;
    final[i].obs = out[i].obs;
    if (out[i].km == 0)
      strcpy(final[i].km, "");
    else {
      sprintf(final[i].km, "%d", out[i].km);
    }
  }

  for (unsigned i = 0; i < TOTAL; i++) {
    printf("%s\t%s\n", out[i].route, final[i].km);
  }

  return 0;

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

  int recent[COUNT];
  int t, play, cycle = 0, found;

  /* initialize stuff */
  srand((unsigned)time(NULL)); /* seed the randomizer */

  /* Randomly play the tunes and keep track */
  while (cycle < COUNT) {
    do {
      play = rand() % COUNT;
      found = 0;
      for (t = 0; t < RANGE; t++)
        if (recent[t] == play) found = 1;
    } while (found);

    for (t = COUNT - 1; t > 0; t--) {
      recent[t] = recent[t - 1];
    }
    recent[0] = play;
    cycle++;
  }

  struct Route tmp[COUNT];
  int iSource = 0;
  for (int i = iSource; i < COUNT; i++) {
    if (iSource >= RANGE) {
      iSource = 0;  // reset if at end of source

      //      shuffle1();
      /* shuffle(recent, RANGE); */
    }
    /* shuffle(recent, RANGE); */
    tmp[i] = tune[recent[i]];
    //  shuffle2();
  }

  for (unsigned i = 0; i < COUNT; i++) {
    printf("route: %s\n", tmp[i].route);
  }

  /* shuffle(recent, 7); */
  /* for (unsigned i = 0; i < COUNT; i++) { */
  /*   tmp[i] = tune[recent[i]]; */
  /* } */
  /* puts("------\n"); */
  /* for (unsigned i = 0; i < COUNT; i++) { */
  /*   printf("route: %s\n", tmp[i].route); */
  /* } */

  return 0;
  void (*pf[7])(void);

  for (unsigned i = 0; i < 7; i++) {
    if (isholiday(i, 2, 2022))
      pf[i] = &shuffle1;
    else {
      pf[i] = &shuffle2;
    }
  }
  for (unsigned i = 0; i < 7; i++) {
    pf[i]();
  }

  return (0);
}
