/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : scratch7
 * @created     : Duminică Feb 13, 2022 18:50:39 EET
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void shuffle(int* pattern, int n) {
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

struct T {
  int x;
} t[32] = {1, 2, 3, 4};

int main() {
  srand(time(0));

  int arr[32], arr2[4] = {1, 2, 3, 4};

  for (unsigned i = 0; i < 32; i++) {
    for (unsigned j = 0; j < 4; j++) {
      /* int m = rand() % 4; */
      /* if (m < 4) arr[i] = arr2[m]; */
      arr[i] = arr2[rand() % 4];
    }
  }

  /* shuffle(arr, 32); */
  /* shuffle((int*)&t, 32); */

  for (unsigned i = 0; i < 32; i++) {
    printf("arr: %d\t", arr[i]);
    /* printf("t: %d\t", t[i].x); */
  }

  return 0;
}
