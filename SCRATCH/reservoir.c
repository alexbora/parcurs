/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : reservoir
 * @created     : Luni Feb 14, 2022 10:50:25 EET
 */

#include <stdlib.h>

// An efficient program to randomly select k items from a stream of items

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int* result;
// A utility function to print an array
static void printArray(int stream[], int n) {
  for (int i = 0; i < n; i++) printf("%d ", stream[i]);
  printf("\n");
}

// A function to randomly select k items from stream[0..n-1].

static inline void selectKItems(int stream[], int n, int k) {
  int i = 0;  // index for elements in stream[]

  // reservoir[] is the output array. Initialize it with
  // first k elements from stream[]
  int reservoir[k];
  for (; i < k; i++) reservoir[i] = stream[i];

  // Use a different seed value so that we don't get
  // same result each time we run this program
  srand((unsigned)time(NULL));

  // Iterate from the (k+1)th element to nth element
  for (; i < n; i++) {
    // Pick a random index from 0 to i.
    int j = rand() % (i + 1);

    // If the randomly picked index is smaller than k, then replace
    // the element present at the index with new element from stream
    if (j < k) reservoir[j] = stream[i];
  }

  /* printf("Following are k randomly selected items \n"); */
  /* printArray(reservoir, k); */

  memcpy(result, &reservoir, sizeof(reservoir));
  /* !!!!!! youé're overwriting pointer'*/
  /* result = reservoir; */
}

// Driver program to test above function.
int main() {
  result = malloc(10 * (sizeof(int)));

  int stream[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  int n = sizeof(stream) / sizeof(stream[0]);
  int k = 7;
  selectKItems(stream, n, k);
  printArray(stream, k);
  printArray(result, k);
  /* dealocating an overitten pointer !!!!! */
  free(result);
  return 0;
}
