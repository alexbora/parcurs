/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : wplay
 * @created     : Duminică Feb 27, 2022 15:36:41 EET
 */

#include <stdlib.h>

/**********************************************
****GENERATE RANDOM NUMBERS IN A GIVEN RANGE***
***********************************************/
#include <math.h>
#include <stdio.h>
/**Function that generates a random number.
Parameters:
r0: initial (first) seed
a: scale factor , so that a*r0 give the first random number
m: gives the max. value of random numbers that can be generated (m-1)
c: additional displacement(offset) factor
**/
static int randx(int r0, int a, int m, int c) {
  int r1 = (a * r0 + c) % m;
  return r1;
}
/**Function that generates random numbers in a given range: [min,max], given a
seed r0, and stores them in an array that is passed as an argument. Parameters:
r0: initial (first) seed
a: scale factor , so that a*r0 give the first random number
m: gives the max. value of random numbers that can be generated (m-1)
c: additional displacement factor
n: no. of random numbers to be generated
x[n]: array that will store the random numbers
min: lower limit for random nos.
max: upper limit for random nos.
**/
static void randomNos(int r0, int a, int m, int c, int n, int x[n], int min,
                      int max) {
  int r1 = randx(r0, a, m, c);
  int r2 = min + ((max - min + 1) * r1) / m;
  for (int i = 0; i < n; i++) {
    x[i] = r2;
    r1 = randx(r1, a, m, c);
    r2 = min + ((max - min + 1) * r1) / m;
  }
}

int main() {
  int min = 0, max = 0, n = 0, a = 1093, m = 86436, c = 18257, r0 = 43;
  printf("Enter the lower limit:\n");
  scanf("%d", &min);
  printf("Enter the higher limit:\n");
  scanf("%d", &max);
  printf("Enter the no. of random numbers required:\n");
  scanf("%d", &n);

  int random[n];
  randomNos(r0, a, m, c, n, random, min, max);

  printf("The random numbers between %d and %d are:\n", min, max);
  for (int i = 0; i < n; i++) {
    printf("%d\n", random[i]);
  }
  return 0;
}
