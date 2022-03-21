#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

static inline int func1(const int* arr, const int rows, const int cols) {
  int err = 1;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      printf("%d ", *(arr + (i * cols) + j));
    }
    puts("\n");
  }
  return err;
}

static inline void func2(int* arr, int i, const int val) {
  int cols = 4, j = 0;
  while (*(arr + (i * cols) + j)) {
    j++;
  }
  if (j > 3) j = 0;
  *(arr + (i * cols) + j) = val;
}

__attribute__((unused)) static char* verify(int buffer[restrict static 17]) {
  (void)buffer;
  static char buf[64];
  memcpy(buf, "te", 2);
  return "buf";
}

static inline bool leapyear(unsigned year) {
  return !(year % 4) && ((year % 100) || !(year % 400));
}

typedef struct rat rat;
struct rat {
  int x;
};
int main(void) {
  __attribute__((unused)) rat r = {0};

  /* char b[16]; */
  printf("is: %d\n", leapyear(2022));

  static int arr[13][4] = {{0}};

  func2(&arr[0][0], 0, 1);
  func2(&arr[0][0], 0, 1);

  char* in = "date7mon8date6mon6";
  func2(&arr[0][0], atoi(in + 4), 9);
  func2(&arr[atoi(in + 8)][0], 0, 8);

  func1(&arr[0][0], 12, 4);

  return 0;
}
