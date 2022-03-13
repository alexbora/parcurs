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
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

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

static struct Route {
  char* route;
  long km;
  char* obs;
} tmp[32], parcurs[16] = {{"Cluj-Oradea", 321, "Interes Serviciu"},
                          {"Cluj-Turda", 121, "Interes Serviciu"},
                          {"Cluj-Zalau", 156, "Interes Serviciu"},
                          {"Cluj-Baia-Mare", 356, "Interes Serviciu"},
                          {"Cluj-Bistrita", 257, "Interes Serviciu"},
                          {"Cluj-Dej", 101, "Interes Serviciu"},
                          {"Cluj-Cluj", 47, "Interes Serviciu"},
                          {"Acasa-Birou", 30, " "},
                          {"Acasa-Birou", 30, " "},
                          {"Acasa-Birou", 30, " "},
                          {"Acasa-Birou", 30, " "},
                          {"Acasa-Birou", 30, " "},
                          {"Cluj-Cmp. Turzii", 152, "Interes Serviciu"},
                          {"Cluj-Apahida", 85, "Interes Serviciu"},
                          {"Cluj-Bontida", 92, "Interes Serviciu"},
                          {"Cluj-Satu-Mare", 421, "Interes Serviciu"}};

static inline unsigned days_in_month(const unsigned month,
                                     const unsigned year) {
  if (month == 4 || month == 6 || month == 9 || month == 11)
    return 30;
  else if (month == 2)
    return (((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29
                                                                      : 28);
  return 31;
}

void do_nothing() {}

int main() {
  srand((unsigned)time(0));
label1:
  do_nothing();

  int min = 0, max = 0, n = 0, a = 1093, m = 86436, c = 18257,
      r0 = rand() % 28;  // 43;

  int days = days_in_month(2, 2022);
  n = days;
  max = 15;
  min = 0;

  int random[days];

  randomNos(r0, a, m, c, n, random, min, max);

  int km = 0;
  for (int i = 0; i < days; i++) {
    printf("%d. %s\n", i + 1, parcurs[random[i]].route);
    if (1) {
      tmp[i] = parcurs[random[i]];
      km += tmp[i].km;
    } else {
      tmp[i] = (struct Route){"", 0, ""};
    }
  }

  /* if (km > 4000) goto label1; */
  for (unsigned i = 0; i < days; i++)
    if (tmp[i].km == tmp[i + 1].km && tmp[i].km != 30) goto label1;
  printf("%d\n", km);
  return 0;
}
