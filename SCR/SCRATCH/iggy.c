/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : iggy
 * @created     : Luni Feb 21, 2022 20:52:15 EET
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>  //strcasecmp (from POSIX)

bool check_name(char const** in) {
  return (!strcasecmp(in[0], "Iggy") && !strcasecmp(in[1], "Pop")) ||
         (!strcasecmp(in[0], "James") && !strcasecmp(in[1], "Osterberg"));
}

#define N 128
int days[N];
#define ADD(t)           \
  {                      \
    if (i == N) abort(); \
    days[i] = (t);       \
    i++;                 \
  };

#define setup(a) int* a##_list = (int[]){1, 1, 1};
#define add(a, list, idx) list[idx] = a;

int main(int argc, char** argv) {
  /* if (argc < 2) return 0; */
  /* bool x = check_name(&argv[1]); */
  /* printf("%d\n,  x"); */
  int i = 0;
  ADD(1);
  ADD(1);
  for (unsigned i = 0; i < 3; i++) {
    printf("%d\n", days[i]);
  }

  setup(month);
  add(3, month_list, 2);
  for (unsigned i = 0; i < 3; i++) {
    printf("%d\n", month_list[i]);
  }

  return 0;
}
