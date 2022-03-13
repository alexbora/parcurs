/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : dice
 * @created     : Sâmbătă Feb 26, 2022 16:00:01 EET
 */

#include <stdlib.h>

/***********************************************
*******************DICE THROW*******************
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
int randx(int r0, int a, int m, int c) {
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
void randomNos(int r0, int a, int m, int c, int n, int x[n], int min, int max) {
  int r1 = randx(r0, a, m, c);
  int r2 = min + ((max - min + 1) * r1) / m;
  int i;
  for (i = 0; i < n; i++) {
    x[i] = r2;
    r1 = randx(r1, a, m, c);
    r2 = min + ((max - min + 1) * r1) / m;
  }
}
int main() {
  int min = 1, max = 6, n;  // For dice the range of random Nos. needed is 1-6
  int a = 1093, m = 86436, c = 18257,
      r0 = 43;  // Constants for random number generation
  printf("Enter the no. of dice throws required:\n");
  scanf("%d", &n);
  int random[n];  // array that stores the dice throw results
  randomNos(r0, a, m, c, n, random, min, max);
  int i;
  printf("The dice throws are:\n");
  for (i = 0; i < n; i++) {
    printf("%d\n", random[i]);
  }
  return 0;
}
