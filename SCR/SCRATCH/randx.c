/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : randxx
 * @created     : Sâmbătă Feb 26, 2022 17:04:01 EET
 */

#include <stdlib.h>
/******************************************************
*************ACCEPTANCE-REJECTION PROBLEM**************
******************************************************/
#include <math.h>
#include <stdio.h>
/**
Probabitlity distribution function acc. to which the randxom nos. are required
**/
double f(double x) { return 3 / 8.0 * (1 + x * x); }
/**Function that generates a randxom number.
Parameters:
r0: initial (first) seed
a: scale factor , so that a*r0 give the first randxom number
m: gives the max. value of randxom numbers that can be generated (m-1)
c: additional displacement(offset) factor
**/
int randx(int r0, int a, int m, int c) {
  double r1 = (a * r0 + c) % m;
  return r1;
}
/**Function that generates randxom numbers given a seed, and stores them in an
array that is passed as an argument. Parameters: r0: initial (first) seed a:
scale factor , so that a*r0 give the first randxom number m: gives the max.
value of randxom numbers that can be generated (m-1) c: additional displacement
factor n: no. of randxom numbers to be generated x[n]: array that will store the
randxom numbers
**/
void randxomNos(int r0, int a, int m, int c, int n, int x[n]) {
  double r1 = randx(r0, a, m, c);
  int i;
  for (i = 0; i < n; i++) {
    x[i] = r1;
    r1 = randx(r1, a, m, c);
  }
}
/**Function that generates randxom numbers in a given range: [min,max], given a
seed r0, and stores them in an array that is passed as an argument. Parameters:
r0: initial (first) seed
a: scale factor , so that a*r0 give the first randxom number
m: gives the max. value of randxom numbers that can be generated (m-1)
c: additional displacement factor
n: no. of randxom numbers to be generated
x[n]: array that will store the randxom numbers
min: lower limit for randxom nos.
max: upper limit for randxom nos.
**/
void randxomNosRange(int n, double r[n], double x[n], double min, double max) {
  int i;
  double r1;
  for (i = 0; i < n; i++) {
    r1 = min + (max - min) * r[i];
    x[i] = r1;
  }
}
int main() {
  int min = -1, max = 1, a = 1093, m = 86436, c = 18257, M = 10;
  double fmax = 3 / 4.0;  // Max value of the function
  int n = 35000;
  int i, j;
  int randx01[n];  // for  n Random Nos from 0 to 86435
  int randx02[n];  // for  n Random Nos from 0 to 86435
  double r1[n];    // for  n Random Nos from 0 to 1
  double r2[n];    // for  n Random Nos from 0 to 1
  double x[n];     // for  n Random Nos from min to max
  randxomNos(43, a, m, c, n,
             randx01);  // gives  n Random Nos from 0 to 86435 and stores them
                        // in randx01
  randxomNos(23, a, m, c, n,
             randx02);  // gives  n Random Nos from 0 to 86435 and stores them
                        // in randx02
  // Normalize randxom nos. in randx01 to [0,1] range and store them r1
  for (i = 0; i < n; i++) {
    r1[i] = (double)randx01[i] / (m - 1);
  }
  // convert the randxom nos. in r1 in the range [0,1] to randxom nos. in the
  // range [min,max] and store them in x array
  randxomNosRange(n, r1, x, min, max);
  // Normalize randxom nos. in randx02 to [0,1] range and store them r2
  for (i = 0; i < n; i++) {
    r2[i] = (double)randx02[i] / (m - 1);
  }
  double y[n];  // for n randxom nos from 0 to fmax
  for (i = 0; i < n; i++) {
    y[i] = r2[i] * fmax;  // get randxom nos from 0 to fmax in y array
  }
  // an array to keep track of the randxom nos lying below the given function
  int Naccept = 0;
  // Arrays that will store the x and y values that are accepted that is lie
  // below the given funvtion f
  double xAccept[n];
  double yAccept[n];
  // Begin acceptance-rejection
  for (i = 0; i < n; i++) {
    if (y[i] <= f(x[i])) {
      Naccept++;
      xAccept[i] = x[i];
      yAccept[i] = y[i];
    }
  }
  FILE* fp = NULL;
  fp = fopen("acceptRejectProb.txt", "w");
  // Store the accepted X and Y in a file
  for (i = 0; i < Naccept; i++) {
    fprintf(fp, "%lf\t%lf\n", xAccept[i], yAccept[i]);
  }
  return 0;
}
