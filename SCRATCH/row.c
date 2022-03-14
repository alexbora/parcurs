#include <stdio.h>
#include <stdlib.h>

void func1(int *arr, int rows, int cols) {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      printf("%d ", *(arr + (i * cols) + j));
    }
    puts("\n");
  }
}

void func2(int *arr, int i, int j) {
  int cols = 4;
  *(arr + (i * cols) + j) = 7;
}

int main() {
  int arr[13][4] = {{}};

  func2(&arr[0][0], 0, 0);
  func2(&arr[0][0], 0, 1);
  func2(&arr[0][0], 0, 2);
  func2(&arr[0][0], 1, 3);
  func2(&arr[0][0], 0, 5);
  func1(&arr[0][0], 12, 4);

  return 0;
}
