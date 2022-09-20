/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : main3
 * @created     : Vineri Iul 15, 2022 18:36:14 EEST
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int   my_func(int);
char *my_func2(char *, char *);
int   my_func3(void);

int main(int argc, char *argv[])
{
  char bb[16];
  printf("%d\n", my_func(2));
  int z = 0;
  printf("%s\n", my_func2("aaa", bb));
  write(2, &z, 2 * sizeof(char));
  my_func3();
  return 0;
}
